#include "syn/nodes/incomplete/expressions/expr_if.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include <string>

#include "esl/category.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/zip.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/numeric_types.hpp"
#include "sem/translation.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::StatementProcessingResult;
    using sem::CompleteValue;
    using sem::FunctionDefinition;
    using sem::Integral;
    using sem::ResolvedValue;
    using sem::TypedExpression;

    interface::DisplayResult syn::node::ExprIf::display () const {
        return
            "if "    + esl::parenthesized(interface::display || target::category{} <<= *condition) +
            " "      + (interface::display || target::category{} <<= *positiveBranch) +
            " else " + (interface::display || target::category{} <<= *negativeBranch);
    }

    interface::ExpressionProcessingResult syn::node::ExprIf::processExpression (context::Main & ctx) const {
        return [&] (CompleteValue cond) -> ExpressionProcessingResult {
            // Compile-time condition value:
            // Note: No implicit conversions of the if condition will be implemented in the first version.
            auto boolResult = cond.template get<sem::value::Bool>();
            if (!boolResult) return boolResult.error();

            return [&] (auto cond) -> ExpressionProcessingResult {
                auto const & branch = cond ? *positiveBranch : *negativeBranch;
                return interface::processExpression(ctx) || target::category{} <<= branch;

            } || target::result{} <<= interface::get<Integral>(*boolResult);

        } | [&] (TypedExpression cond) -> ExpressionProcessingResult {
            // Run-time condition value:

            // Note: No implicit conversions of the if condition will be implemented in the first version.
            if (!cond.type.template holds_alternative<sem::value::Bool>())
                return esl::result_error{"If condition must be a boolean value."};

            auto tupleVar = c::tupleVariableName(c::id(ctx.nextId()));

            return [&] (auto posVals, auto negVals) -> ExpressionProcessingResult {

                esl::tiny_vector<tpl::TypeSpecifier> tupleTypes;
                esl::tiny_vector<std::string>        posTupleVals;
                esl::tiny_vector<std::string>        negTupleVals;
                esl::tiny_vector<ResolvedValue>      resolved;

                for (auto const & [i, pos, neg]: esl::enumerate(posVals, negVals)) {
                    auto tupleElement = c::tupleElement(tupleVar, i);

                    auto result = [&] (CompleteValue const & pos, CompleteValue const & neg) -> esl::result<void> {
                        // Both comp-time values:
                        auto posType = interface::valueType || target::category{} <<= pos;
                        auto negType = interface::valueType || target::category{} <<= pos;
                        // Note: No conversion to a common type will be implemented in the first version.
                        if (!(interface::sameType || target::category{} <<= args(posType, negType)))
                            return esl::result_error{"Incompatible types in if expression branches."};

                        return [&] (sem::type::Function const & type) -> esl::result<void> {
                            // Two partially run-time function values:

                            auto posResult = pos.template get<sem::value::Function>();
                            auto negResult = pos.template get<sem::value::Function>();
                            if (!posResult) return posResult.error();
                            if (!negResult) return negResult.error();
                            auto & posFun = *posResult;
                            auto & negFun = *negResult;

                            auto contextType = c::contextVariableType(c::id(ctx.nextId()));
                            auto & def = ctx.global.storeValue<FunctionDefinition>(FunctionDefinition{
                                .implementation = FunctionDefinition::Switch{posFun, negFun},
                                .type           = type,
                                .contextType    = contextType,
                                .name           = c::functionName(c::id(ctx.nextId()))
                            });
                            auto newFun = sem::value::Function{
                                .definition      = def,
                                .contextVariable = tupleElement
                            };

                            auto posExpr = c::contextLiteral(contextType, 0, posFun.contextVariable);
                            auto negExpr = c::contextLiteral(contextType, 1, negFun.contextVariable);
                            posTupleVals.push_back(posExpr);
                            negTupleVals.push_back(negExpr);
                            tupleTypes.push_back(tpl::TypeSpecifier{.type = contextType, .structure = true});
                            resolved.push_back(CompleteValue{newFun});

                            return {};

                        } | [&] (auto type) -> esl::result<void> {
                            // Two comp-time values:
                            return [&] (auto type) -> esl::result<void> {
                                tupleTypes.push_back(type);
                                return {};

                            } || target::result{} <<=
                            [&] (auto pos, auto neg) {
                                resolved.push_back(TypedExpression{
                                    .type       = type,
                                    .expression = tupleElement
                                });
                                posTupleVals.push_back(pos.expression);
                                negTupleVals.push_back(neg.expression);

                                return interface::translateTypeSpecifier(type);

                            } || target::result{} <<= args(
                                interface::translateValue(ctx) || target::category{} <<= pos,
                                interface::translateValue(ctx) || target::category{} <<= neg
                            );

                        } || target::category{} <<= posType;

                        return {};

                    } | [&] (auto const & pos, auto const & neg) -> esl::result<void> {
                        // At least one of them run-time:
                        return [&] (auto pos, auto neg) -> esl::result<void> {
                            // Note: No conversion to a common type will be implemented in the first version.
                            if (!(interface::sameType || target::category{} <<= args(pos.type, neg.type)))
                                return esl::result_error{"Incompatible types in if expression branches."};

                            resolved.push_back(TypedExpression{
                                .type       = pos.type,
                                .expression = tupleElement
                            });
                            posTupleVals.push_back(pos.expression);
                            negTupleVals.push_back(neg.expression);

                            return [&] (auto x) -> esl::result<void> {
                                tupleTypes.push_back(x);
                                return {};
                            } || target::result{} <<=
                            interface::translateTypeSpecifier || target::category{} <<= pos.type;

                        } || target::result{} <<= args(
                            interface::translateResolvedValue(ctx, pos),
                            interface::translateResolvedValue(ctx, neg)
                        );

                    } || target::category{} <<= args(pos, neg);
                    if (!result) return result.error();
                }

                auto tupleSpec = tpl::Tuple{tupleTypes};
                auto tupleType = ctx.global.instantiate(tupleSpec);
                auto posExpr   = c::structureLiteral(tupleType, posTupleVals);
                auto negExpr   = c::structureLiteral(tupleType, negTupleVals);
                auto expr      = c::ternary(cond.expression, posExpr, negExpr);
                auto tupleDef  = c::definition(c::autoType(), tupleVar, expr);

                /***
                __auto_type <tupvar> = <cond> ? (struct cth_tup$...) {
                    <pos1>,
                    ...
                } : (struct cth_tup$...) {
                    <neg1>,
                    ...
                };
                ***/
                ctx.insertStatement(tupleDef);

                return resolved;

            } || target::result{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *positiveBranch,
                interface::processExpression(ctx) || target::category{} <<= *negativeBranch
            );

        } || target::nested<target::result, target::category>{} <<=
        esl::single || target::result{} <<=
        interface::processExpression(ctx) || target::category{} <<= *condition;

        /*
        return [&] (NoReturn const &) -> ExpressionProcessingResult {
            return esl::result_error{"If expression never returns."};

        } | [&] (sem::Return const & result) -> ExpressionProcessingResult {
            if (!result.always)
                return esl::result_error{"If expression does not always return."};

        } || target::optional_result{} <<=
        */

        /*
        auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(syn::evaluate(ctx)(condition))));
        if (!result)
            return syn::make_evaluation_result(result.error());
        if (*result)
            return syn::evaluate(ctx)(positive_branch);
        else
            return syn::evaluate(ctx)(negative_branch);
        */
    }

    interface::StatementProcessingResult syn::node::ExprIf::processStatement (context::Main & ctx) const {
        return [&] (CompleteValue cond) -> StatementProcessingResult {
            // Compile-time condition value:
            // Note: No implicit conversions of the if condition will be implemented in the first version.
            auto boolResult = cond.template get<sem::value::Bool>();
            if (!boolResult) return boolResult.error();

            return [&] (auto cond) -> StatementProcessingResult {
                auto const & branch = cond ? *positiveBranch : *negativeBranch;
                return interface::processStatement(ctx) || target::category{} <<= branch;

            } || target::result{} <<= interface::get<Integral>(*boolResult);

        } | [&] (TypedExpression cond) -> StatementProcessingResult {
            // Run-time condition value:

            return [&] (auto posVals, auto negVals) -> StatementProcessingResult {

            } || target::result{} <<= args(
                interface::processExpression(ctx) || target::category{} <<= *positiveBranch,
                interface::processExpression(ctx) || target::category{} <<= *negativeBranch
            );

        } || target::nested<target::result, target::category>{} <<=
        esl::single || target::result{} <<=
        interface::processExpression(ctx) || target::category{} <<= *condition;

        /*
        auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(syn::evaluate(ctx)(condition))));
        if (!result)
            return syn::make_execution_result(result.error());
        if (*result) {
            auto branch_scope = make_child_context(ctx);
            return syn::execute(branch_scope)(positive_branch);
        } else {
            auto branch_scope = make_child_context(ctx);
            return syn::execute(branch_scope)(negative_branch);
        }
        */
    }

}
