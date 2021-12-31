#include "syn/nodes/common/for_nodes.hpp"

#include <string>
#include <utility>

#include "esl/category.hpp"
#include "esl/containers.hpp"
#include "esl/result.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"

#include "context/main.hpp"
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
    using sem::TypedExpression;
    using sem::TypedName;
    using sem::Variable;
    using sem::ResolvedValue;

    esl::result<void> processRuntimeArray (
        State                   & state,
        std::string       const & name,
        sem::CompleteType const & type,
        std::string       const & value
    ) {
        return [&] (auto translType) -> esl::result<void> {
            auto varName = c::variableName(c::id(state.ctx.nextId()));
            state.variables.emplace_back(
                name,
                Variable{TypedName{.type = type, .name = varName}}
            );
            state.assignments.push_back(c::definition(translType, name, value));
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
                auto name           = c::variableName(c::id(state.ctx.nextId()));
                auto declaration    = c::declaration(translType, name);
                auto initialization = from.expression;
                auto advancement    = c::advance(name, by.expression);

                state.variables.emplace_back(
                    name,
                    Variable{TypedName{.type = type, .name = name}}
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
            ctx.empty()             && // Empty context means that no local statements were added.
            variables.empty()       && // No variables that require run-time representation.
            assignments.empty()     &&
            declarations.empty()    &&
            initializations.empty() &&
            advancements.empty();
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
                // Comp-time allocations:
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
        return [&] (auto decl) -> StatementProcessingResult {
            auto & [size, iterDecls] = decl;

            State state = {.ctx = outerScope};

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
            for (auto const & [name, var]: std::move(state.variables))
                loopScope.lookup.insertValue(name, esl::init<esl::tiny_vector>(std::move(var)));
            auto bodyResult = interface::processStatement(loopScope) || target::category{} <<= body;
            if (!bodyResult) return bodyResult.error();

            auto head = c::forBegin(
                c::iterationStructure(state.declarations, state.initializations),
                c::lt(c::iterationPosition(), c::integralLiteral(size)),
                c::join(",", state.advancements)
            );
            for (auto & assgn: state.assignments)
                assgn += c::brackets(c::iterationPosition());
            auto assgn = c::indentedTerminatedJoin(";", state.assignments);
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
            outerScope.mergeNestedChild(loopScope);

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

}
