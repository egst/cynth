#include "syn/nodes/statements.hpp"

#include <string>
#include <utility>

#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/view.hpp"
#include "esl/zip.hpp"

// TODO: Clean this up, when I'm done.
#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/misc.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/compound.hpp"
#include "sem/translation.hpp"
#include "sem/numeric_types.hpp"

namespace cynth::syn {

    using namespace esl::sugar;

    namespace target = esl::target;

    using interface::StatementProcessingResult;
    using interface::DisplayResult;
    using sem::CompleteValue;
    using sem::NoReturn;
    using sem::TypedExpression;
    using sem::ArrayAllocation;

    interface::DisplayResult node::For::display () const {
        return
            "for " + esl::parenthesized(interface::display || target::category{} <<= *declarations) +
            " "    + (interface::display || target::category{} <<= *body);
    }

    namespace {

        esl::result<void> runtimeArray (
            context::Main                             & ctx,
            esl::tiny_vector<std::string>             & elementAssignments,
            sem::CompleteType                   const & elemType,
            esl::tiny_vector<sem::CompleteType> const & declType,
            std::string                         const & value
        ) {
            return [&] (auto declType) -> esl::result<void> {
                if (!(interface::sameType(declType) || target::category{} <<= elemType))
                    return esl::result_error{"Incompatible range declaration element and array types."};

                return [&] (auto type) -> esl::result<void> {
                    elementAssignments.push_back(c::definition(type, c::variableName(c::id(ctx.nextId())), value));
                    return {};

                } || target::result{} <<= interface::translateType(declType);

            } || target::nested<target::result, target::category>{} <<= esl::single(declType);

        }
    }

    interface::StatementProcessingResult node::For::processStatement (context::Main & ctx) const {
        return [&] (auto decl) -> StatementProcessingResult {
            auto & [size, iterDecls] = (decl);

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

                    return [&] (ArrayAllocation * alloc) -> esl::result<void> {
                        if (alloc->sequence) {
                            // Comp-time atithmetic sequence:

                            auto seqType = alloc->sequence->type();
                            if (!(interface::sameTypes || target::category{} <<= args(seqType, elemType)))
                                return esl::result_error{"Incompatible range declaration element and sequence types."};

                            return [&] (auto type, auto by, auto from) -> esl::result<void> {
                                auto name           = c::variableName(c::id(ctx.nextId()));
                                auto declaration    = c::declaration(type, name);
                                auto initialization = from.expression;
                                auto advancement    = c::advance(name, by.expression);

                                iteratorDeclarations.push_back(declaration);
                                iteratorInitializations.push_back(advancement);
                                iteratorAdvancements.push_back(initialization);

                                return {};

                            } || target::result{} <<= args(
                                interface::translateType || target::category{} <<= elemType,
                                interface::translateValue(ctx) || target::category{} <<= alloc->sequence->by(),
                                interface::translateValue(ctx) || target::category{} <<= alloc->sequence->from()
                            );
                        }

                        // Comp-time general case array:
                        return [&] (auto name) {
                            return runtimeArray(ctx, elementAssignments, elemType, decl.type, name);
                        } || target::result{} <<= alloc->allocate(ctx);

                    } | [&, &decl = decl] (std::string const & expr) -> esl::result<void> {
                        // Run-time array allocation:
                        return runtimeArray(ctx, elementAssignments, elemType, decl.type, expr);

                    } || target::variant{} <<= arrayValue.allocation;

                } | [&, &decl = decl] (TypedExpression const & expr) -> esl::result<void> {
                    // Run-time range array:
                    auto arrayResult = expr.type.get<sem::type::Array>();
                    if (!arrayResult) return arrayResult.error();
                    auto const & arrayType = *arrayResult;
                    auto elemType = *arrayType.type;
                    return runtimeArray(ctx, elementAssignments, elemType, decl.type, expr.expression);

                } || target::category{} <<= array;

                if (!result) return result.error();

            }

            auto loopScope = ctx.makeScopeChild();

            //elementAssignments;      // `cth_int var_e = var_a`
            //iteratorDeclarations;    // `cth_int var_i`
            //iteratorInitializations; // `1`
            //iteratorAdvancements;    // `var_i += 2`

            //if ()

#if 0
            auto intType = sem::type::Int{}.translateType();
            auto iterVar = c::iterationVariableName(c::id(ctx.nextId()));
            //auto iterExpr = TypedExpression{.type = sem::type::Int{}, .expression = iterVar};

            auto head = c::forBegin(
                c::definition(intType, iterVar, c::increment(iterVar)),
                c::lt(iterVar, c::intLiteral(size)),
                c::increment(iterVar)
            );

            /***
            for (cth_int itervar_i = 0; itervar_i < <size>; ++itervar_i) {
            ***/
            ctx.insertStatement(head);

            auto scope = ctx.makeScopeChild();

            for (auto & [decl, array]: iterDecls) {
                /***
                <decl> = <array>[itervar_i];
                ***/
                auto declResult = [&, &array = array, &decl = decl] (auto var) {
                    return scope.lookup.insertValue(decl.name, esl::init<esl::tiny_vector>(std::move(var)));

                } || target::result{} <<= [&, &array = array] (auto elem, auto type) {
                    return interface::processDefinition(ctx)(elem) || target::category{} <<= type;

                } || target::result{} <<= args(
                    interface::processVerifiedSubscript(ctx, iterVar, array),
                    esl::single(decl.type)
                );
                if (!declResult) return declResult.error();
            }

            /***
            <body>
            ***/
            auto bodyResult = interface::processStatement(scope) || target::category{} <<= *body;

            /***
            }
            ***/
            ctx.insertStatement(c::end());

            return bodyResult;
#endif

            return {}; // TODO

        } || target::result{} <<= interface::resolveRangeDeclarations(ctx, *declarations);
    }

}
