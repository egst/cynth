#include "syn/nodes/common/for_nodes.hpp"

#include <string>
#include <utility>

#include "esl/category.hpp"
#include "esl/containers.hpp"
#include "esl/result.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"

#include "config.hpp"
#include "context/main.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/compound.hpp"
#include "sem/translation.hpp"
#include "syn/categories/expression.hpp"
#include "syn/categories/range_declaration.hpp"
#include "syn/categories/statement.hpp"

namespace cynth::syn::for_nodes {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::StatementProcessingResult;
    using interface::DisplayResult;
    using sem::ArrayAllocation;
    using sem::CompleteValue;
    using sem::NoReturn;
    using sem::ResolvedValue;
    using sem::TypedExpression;
    using sem::TypedName;
    using sem::Variable;

    esl::result<void> processRuntimeArray (
        State                   & state,
        std::string       const & name,
        sem::CompleteType const & type,
        std::string       const & value
    ) {
        return [&] (auto translType) -> esl::result<void> {
            auto memberName = c::variableName(c::id(state.ctx.nextId()));
            // TODO: This should be in translation.hpp
            //auto expr = c::memberAccess(def::iteration, c::variableName(c::id(state.ctx.nextId())));
            auto varname = c::variableName(c::id(state.ctx.nextId()));
            state.variables.emplace_back(
                name,
                Variable{TypedName{.type = type, .name = varname}}
            );
            state.assignments.push_back(c::definition(translType, varname, value));
            return {};

        } || target::result{} <<= interface::translateType || target::category{} <<= type;
    }

    esl::result<void> processAllocation (
        State             & state,
        std::string const & name,
        ArrayAllocation   & alloc
    ) {
        auto type = alloc.type();
        if (alloc.sequence) {
            // Comp-time atithmetic sequence:

            return [&] (auto translType, auto by, auto from) -> esl::result<void> {
                auto memberName     = c::variableName(c::id(state.ctx.nextId()));
                // TODO: This should be in translation.hpp
                auto expr           = c::memberAccess(def::iteration, memberName);
                auto declaration    = c::declaration(translType, memberName);
                auto initialization = from.expression;
                auto advancement    = c::advance(expr, by.expression);

                state.variables.emplace_back(
                    name,
                    Variable{TypedName{.type = type, .name = expr}}
                );
                state.declarations.push_back(declaration);
                state.initializations.push_back(initialization);
                state.advancements.push_back(advancement);

                return {};

            } || target::result{} <<= args(
                interface::translateType             || target::category{} <<= type,
                interface::translateValue(state.ctx) || target::category{} <<= alloc.sequence->by(),
                interface::translateValue(state.ctx) || target::category{} <<= alloc.sequence->from()
            );
        }

        // Comp-time general case array:
        auto valName = alloc.allocate(state.ctx);
        return processRuntimeArray(state, name, type, valName);
    }

    esl::result<void> State::processAllocations () {
        for (auto & [name, alloc]: allocations) {
            auto result = processAllocation(*this, name, *alloc);
            if (!result) return result.error();
        }
        allocations = {};
        return {};
    }

    bool State::comptime () const {
        return
            // Everything but the allocations must be empty:
            ctx.empty()                 && // Empty context means that no local statements were added.
            variables.empty()           && // No variables that require run-time representation.
            assignments.empty()         &&
            declarations.empty()        &&
            initializations.size() <= 1 && // One initialization and advancement is for the position.
            advancements.size()    <= 1;
    }

    esl::result<void> processArray (
        State                   & state,
        std::string       const & name,
        sem::CompleteType const & type,
        ResolvedValue     const & array
    ) {
        return [&] (CompleteValue const & value) -> esl::result<void> {
            // Comp-time range array:
            auto arrayResult = value.get<sem::value::Array>();
            if (!arrayResult) return arrayResult.error();
            auto & arrayValue = *arrayResult;
            auto elemType = *arrayValue.valueType.type;

            if (!(interface::sameTypes || target::category{} <<= args(type, elemType)))
                return esl::result_error{"Incompatible range declaration element and array types."};

            return [&] (ArrayAllocation * alloc) -> esl::result<void> {
                // Comp-time allocation:

                auto allocType = alloc->type();
                if (!(interface::sameTypes || target::category{} <<= args(type, allocType)))
                    return esl::result_error{"Incompatible range declaration element and sequence types."};

                state.allocations.emplace_back(name, alloc);
                return {}; // The allocation can be later translated to a run-time allocation or used directly in comp-time evaluation.

            } | [&] (std::string const & expr) -> esl::result<void> {
                // Run-time array allocation:
                return processRuntimeArray(state, name, elemType, expr);

            } || target::variant{} <<= arrayValue.allocation;

        } | [&] (TypedExpression const & expr) -> esl::result<void> {
            // Run-time range array:
            auto arrayResult = expr.type.get<sem::type::Array>();
            if (!arrayResult) return arrayResult.error();
            auto const & arrayType = *arrayResult;
            auto elemType = *arrayType.type;

            if (!(interface::sameTypes || target::category{} <<= args(type, elemType)))
                return esl::result_error{"Incompatible range declaration element and array types."};

            return processRuntimeArray(state, name, elemType, expr.expression);

        } || target::category{} <<= array;
    }

    template <typename Body>
    interface::StatementProcessingResult processStatement (
        context::Main                    & outerScope,
        category::RangeDeclaration const & declarations,
        Body                       const & body
    ) {
        // TODO: helperScope as in ExprFor::processExpression.
        return [&] (auto decl) -> StatementProcessingResult {
            auto & [size, iterDecls] = decl;

            // TODO: Add a State constructor that takes care of this.
            State state = {
                .ctx             = outerScope,
                .initializations = {c::integralLiteral(0)},
                .advancements    = {c::increment(c::iterationPosition())},
            };

            for (auto & [decl, array]: iterDecls) {
                auto result = [&, &decl = decl, &array = array] (auto type) {
                    return processArray(state, decl.name, type, array);
                } || target::result{} <<= esl::single(decl.type);
                if (!result) return result.error();
            }

            /*
            if (state.comptime()) {
                // All range arrays comp-time:

                // TODO: Compile-time execution of the for loop could be performed here,
                // but this is not an essetial compile-time execution flow and I'll omit it in the first version,
                // since for loop doen't produce or influence any compconst values except for some rarely useful cases.
                // For example:
                // Int const a = {
                //     for (...) {
                //         return 1;
                //     }
                // }
                // Creates a compconst variable a with a compile-time value of 1.
                // This won't be possible until I implement this compile-time for loop execution.
                return {};
            }
            */

            // At least some range arrays run-time:

            state.processAllocations();
            auto loopScope = outerScope.makeScopeChild();
            for (auto const & [name, var]: std::move(state.variables)) {
                auto result = loopScope.lookup.insertValue(name, esl::init<esl::tiny_vector>(std::move(var)));
                if (!result) return result.error();
            }

            auto bodyResult = interface::processStatement(loopScope) || target::category{} <<= body;
            if (bodyResult.has_error()) return bodyResult.error();

            auto head = c::forBegin(
                c::iterationStructure(state.declarations,  state.initializations),
                c::lt(c::iterationPosition(), c::integralLiteral(size)),
                c::join(",", state.advancements)
            );
            for (auto & assgn: state.assignments)
                assgn += c::brackets(c::iterationPosition());
            auto assgn = c::indented(c::terminatedJoin(";", state.assignments));
            auto end   = c::end();

            /***
            for (
                struct {
                    cth_int pos;
                    <decl1>;
                    <decl2>;
                    ...
                } iter = {0, <init1>, <init2>, ...};
                iter.pos < <size>;
                ++iter.pos,
                <advancement1>,
                <advancement2>,
                ...
            ) {
                <assignment1>[iter.pos];
                <assignment2>[iter.pos];
            ***/
            outerScope.insertStatement(head);
            outerScope.insertStatement(assgn);

            /***
                <body>
            ***/
            outerScope.mergeChild(loopScope);

            /***
            }
            ***/
            outerScope.insertStatement(end);

            return bodyResult;

        } || target::result{} <<= resolveRangeDeclarations(outerScope, declarations);
    }

    template
    interface::StatementProcessingResult processStatement (
        context::Main                    &,
        category::RangeDeclaration const &,
        category::Expression       const &
    );

    template
    interface::StatementProcessingResult processStatement (
        context::Main                    &,
        category::RangeDeclaration const &,
        category::Statement        const &
    );

    esl::result<std::pair<Integral, RangeVector>> resolveRangeDeclarations (
        context::Main & ctx,
        syn::category::RangeDeclaration declaration
    ) {
        std::optional<Integral> size;

        RangeVector ranges;

        //auto result = [&] (auto decl) -> esl::result<void> {
        auto result = [&] (auto decls) -> esl::result<void> {

            for (auto const & decl: decls) {

                auto arrayResult = interface::resolvedValueType(*decl.range).template get<sem::type::Array>();
                if (!arrayResult)
                    return esl::result_error{"Only arrays can be used as for loop ranges."};
                auto const & arrayType = *arrayResult;
                auto arraySize = arrayType.size;

                auto const & declTypes = decl.declaration->type;
                if (declTypes.size() == 0)
                    return esl::result_error{"Less types than values in a range declaration."};
                if (declTypes.size() > 1)
                    return esl::result_error{"More types than values in a range declaration."};
                auto const & declType = declTypes.front();
                if (!(interface::sameTypes || target::category{} <<= args(declType, *arrayType.type)))
                    return esl::result_error{"Incompatible type in a range declaration."};

                if (!size)
                    size = arraySize;
                else if (*size != arraySize)
                    return esl::result_error{"All ranges in a for loop must be of the same size."};

                ranges.emplace_back(*decl.declaration, *decl.range);

            }

            return {};

        //} || target::nested<target::result, target::tiny_vector>{} <<=
        } || target::result{} <<=
            interface::resolveRangeDeclaration(ctx) || target::category{} <<= declaration;
        if (!result) return result.error();

        return std::make_pair(*size, ranges);
    }

}
