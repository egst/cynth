#include "syn/nodes/statements.hpp"

#include <string>
#include <utility>

#include "esl/category.hpp"
#include "esl/containers.hpp"
#include "esl/result.hpp"
#include "esl/lift.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/zip.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/misc.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/compound.hpp"
#include "sem/translation.hpp"

namespace cynth::syn {

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

    interface::DisplayResult node::For::display () const {
        return
            "for " + esl::parenthesized(interface::display || target::category{} <<= *declarations) +
            " "    + (interface::display || target::category{} <<= *body);
    }

    namespace {

        esl::result<void> runtimeArray (
            context::Main                             & ctx,
            esl::tiny_vector<Variable>                & variables,
            esl::tiny_vector<std::string>             & elementAssignments,
            sem::CompleteType                   const & elemType,
            esl::tiny_vector<sem::CompleteType> const & declType,
            std::string                         const & value
        ) {
            return [&] (auto declType) -> esl::result<void> {
                if (!(interface::sameType(declType) || target::category{} <<= elemType))
                    return esl::result_error{"Incompatible range declaration element and array types."};

                return [&] (auto type) -> esl::result<void> {
                    auto name = c::variableName(c::id(ctx.nextId()));
                    variables.emplace_back(TypedName{.type = declType, .name = name});
                    elementAssignments.push_back(c::definition(type, name, value));
                    return {};

                } || target::result{} <<= interface::translateType(declType);

            } || target::nested<target::result, target::category>{} <<= esl::single(declType);

        }
    }

    interface::StatementProcessingResult node::For::processStatement (context::Main & outerScope) const {
        return [&] (auto decl) -> StatementProcessingResult {
            auto & [size, iterDecls] = (decl);

            esl::tiny_vector<std::string> names;
            esl::tiny_vector<Variable>    variables;
            esl::tiny_vector<std::string> elementAssignments;      // `cth_int var_e = var_a`
            esl::tiny_vector<std::string> iteratorDeclarations;    // `cth_int var_i`
            esl::tiny_vector<std::string> iteratorInitializations; // `1`
            esl::tiny_vector<std::string> iteratorAdvancements;    // `var_i += 2`

            for (auto & [decl, array]: iterDecls) {

                auto result = [&, &decl = decl] (CompleteValue const & value) -> esl::result<void> {
                    // Comp-time range array:
                    auto arrayResult = value.get<sem::value::Array>();
                    if (!arrayResult) return arrayResult.error();
                    auto & arrayValue = *arrayResult;
                    auto elemType = *arrayValue.valueType.type;

                    names.push_back(decl.name);

                    return [&] (ArrayAllocation * alloc) -> esl::result<void> {
                        if (alloc->sequence) {
                            // Comp-time atithmetic sequence:

                            auto seqType = alloc->sequence->type();
                            if (!(interface::sameTypes || target::category{} <<= args(seqType, elemType)))
                                return esl::result_error{"Incompatible range declaration element and sequence types."};

                            return [&] (auto declType) -> esl::result<void> {
                                return [&] (auto type, auto by, auto from) -> esl::result<void> {
                                    auto name           = c::variableName(c::id(outerScope.nextId()));
                                    auto declaration    = c::declaration(type, name);
                                    auto initialization = from.expression;
                                    auto advancement    = c::advance(name, by.expression);

                                    variables.emplace_back(TypedName{.type = declType, .name = name});
                                    iteratorDeclarations.push_back(declaration);
                                    iteratorInitializations.push_back(advancement);
                                    iteratorAdvancements.push_back(initialization);

                                    return {};

                                } || target::result{} <<= args(
                                    interface::translateType(declType),
                                    interface::translateValue(outerScope) || target::category{} <<= alloc->sequence->by(),
                                    interface::translateValue(outerScope) || target::category{} <<= alloc->sequence->from()
                                );
                            } || target::nested<target::result, target::category>{} <<= esl::single(decl.type);
                        }

                        // Comp-time general case array:
                        return [&] (auto name) {
                            return runtimeArray(outerScope, variables, elementAssignments, elemType, decl.type, name);
                        } || target::result{} <<= alloc->allocate(outerScope);

                    } | [&, &decl = decl] (std::string const & expr) -> esl::result<void> {
                        // Run-time array allocation:
                        return runtimeArray(outerScope, variables, elementAssignments, elemType, decl.type, expr);

                    } || target::variant{} <<= arrayValue.allocation;

                } | [&, &decl = decl] (TypedExpression const & expr) -> esl::result<void> {
                    // Run-time range array:
                    auto arrayResult = expr.type.get<sem::type::Array>();
                    if (!arrayResult) return arrayResult.error();
                    auto const & arrayType = *arrayResult;
                    auto elemType = *arrayType.type;
                    return runtimeArray(outerScope, variables, elementAssignments, elemType, decl.type, expr.expression);

                } || target::category{} <<= array;

                if (!result) return result.error();

            }

            /*
            if (elementAssignments.empty()) {
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

            auto loopScope = outerScope.makeScopeChild();

            for (auto const & [name, var]: esl::zip(std::move(names), variables))
                loopScope.lookup.insertValue(name, esl::init<esl::tiny_vector>(std::move(var)));

            auto bodyResult = interface::processStatement(loopScope) || target::category{} <<= *body;
            if (!bodyResult) return bodyResult.error();

            auto head = c::forBegin(
                c::iterationStructure(iteratorDeclarations, iteratorInitializations),
                c::lt(c::iterationPosition(), c::intLiteral(size)),
                c::join(",", iteratorAdvancements)
            );
            for (auto assgn: elementAssignments)
                assgn += c::brackets(c::iterationPosition());
            auto assgn = c::indentedTerminatedJoin(";", elementAssignments);
            auto end = c::end();

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
            }
            ***/
            outerScope.mergeNestedChild(loopScope);

            /***
            }
            ***/
            outerScope.insertStatement(end);

            return bodyResult;

        } || target::result{} <<= interface::resolveRangeDeclarations(outerScope, *declarations);
    }

}
