#include "syn/nodes/incomplete/expressions/expr_if.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include <string>

#include "esl/category.hpp"
#include "esl/type_manip.hpp"
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
#include "syn/categories/expression.hpp"

// TODO:
// Surely there must be a way to generalize the algohithms used here.
// I guess I won't be able to get rid of all the branches,
// not without too much runtime polymorphism and repeated
// "packing" and "unpacking" of abstractions and indirections.
// But I'll try to generalize the main ideas in some generic helper functions
// and just delegate to those in the different braeches.

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::StatementProcessingResult;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::FunctionDefinition;
    using sem::Integral;
    using sem::NoReturn;
    using sem::ResolvedValue;
    using sem::ReturnedValues;
    using sem::TypedExpression;

    interface::DisplayResult syn::node::ExprIf::display () const {
        return
            "if "    + esl::parenthesized(interface::display || target::category{} <<= *condition) +
            " "      + (interface::display || target::category{} <<= *positiveBranch) +
            " else " + (interface::display || target::category{} <<= *negativeBranch);
    }

    ExpressionProcessingResult syn::node::ExprIf::processExpression (context::Main & ctx) const {
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
                        if (!(interface::sameTypes || target::category{} <<= args(posType, negType)))
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
                            if (!(interface::sameTypes || target::category{} <<= args(pos.type, neg.type)))
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
    }

    namespace {

        struct StatementResult {
            StatementProcessingResult returnResult;
            // Returned compile-time values:
            esl::tiny_vector<std::string> posReturnStmts;
            esl::tiny_vector<std::string> negReturnStmts;
        };

        StatementResult processIfStatement (
            context::Main & outerScope,
            context::Main & posBranchScope,
            context::Main & negBranchScope,
            esl::component<category::Expression> positiveBranch,
            esl::component<category::Expression> negativeBranch
        ) {
            esl::tiny_vector<std::string> posReturnStmts;
            esl::tiny_vector<std::string> negReturnStmts;

            auto returnResult = [&] (sem::Return pos, sem::Return neg) -> StatementProcessingResult {
                // Both branches return.

                sem::Return returnResult;
                returnResult.always = pos.always && neg.always;

                for (auto const & [i, posRet, negRet]: esl::enumerate(pos.returned, neg.returned)) {
                    auto result = [&, i = i] (ReturnedValues posVals, ReturnedValues negVals) {
                        // Both comp-time values:
                        return [&] (
                            sem::type::Function const & posType,
                            sem::type::Function const & negType
                        ) -> esl::result<void> {
                            // Partially run-time function values:
                            if (!interface::sameTypes(posType, negType))
                                return esl::result_error{"Different function types in an if statement."};
                            posVals.insert_back(negVals.begin(), negVals.end());
                            returnResult.returned.emplace_back(posVals);
                            return {};

                        } | [&, i = i] <typename T> (T const & posType, T const & negType) -> esl::result<void>
                        requires (!esl::same_but_cvref<T, sem::type::Function>) {
                            if (!interface::sameTypes(posType, negType))
                                return esl::result_error{"Different types in an if statement."};

                            // Compile-time value:
                            if (posVals.size() > 1 || negVals.size() > 1) // Implementation error.
                                return esl::result_error{"Returning multiple compile-time values in a run-time if statement."};
                            if (posVals.size() == 0 || negVals.size() == 1) // Implementation error.
                                return esl::result_error{"Returning empty compile-time values in a run-time if statement."};
                            auto const & posVal = posVals.front();
                            auto const & negVal = negVals.front();

                            returnResult.returned.emplace_back(CompleteType{posType});

                            return [&] (auto posExpr, auto negExpr) -> esl::result<void> {
                                posReturnStmts.push_back(c::returnValue(i, posExpr.expression));
                                negReturnStmts.push_back(c::returnValue(i, negExpr.expression));
                                return {};

                            } || target::result{} <<= args(
                                interface::translateValue(outerScope) || target::category{} <<= posVal,
                                interface::translateValue(outerScope) || target::category{} <<= negVal
                            );

                        } | [&, i = i] (auto const &, auto const &) -> esl::result<void> {
                            // Implementation error.
                            return esl::result_error{"Returning invalid types in an if statement."};

                        } || target::category{} <<= args(
                            interface::returnedValuesType(posVals),
                            interface::returnedValuesType(negVals)
                        );

                    } | [&] (CompleteType posType, CompleteType negType) -> esl::result<void> {
                        // Both run-time values:
                        if (!(interface::sameTypes || target::category{} <<= args(posType, negType)))
                            return esl::result_error{"Returning different types in an if statement."};
                        returnResult.returned.emplace_back(posType);
                        return {};

                    } | [&, i = i] <typename Pos, typename Neg> (Pos pos, Neg neg) -> esl::result<void> {
                        // One comp-time one run-time:
                        auto compVals = esl::first_of<ReturnedValues>(pos, neg);
                        auto runType  = esl::first_of<CompleteType>(pos, neg);
                        auto & returnStmts = esl::same_but_cvref<CompleteType, Neg>
                            ? posReturnStmts
                            : negReturnStmts;

                        if (compVals.size() > 1) // Implementation error.
                            return esl::result_error{"Returning multiple compile-time values in a run-time if statement."};
                        if (compVals.size() == 0) // Implementation error.
                            return esl::result_error{"Returning empty compile-time values in a run-time if statement."};
                        auto const & compVal = compVals.front();

                        auto compType = interface::valueType || target::category{} <<= compVal;
                        if (!(interface::sameTypes || target::category{} <<= args(compType, runType)))
                            return esl::result_error{"Returning different types in an if statement."};

                        returnResult.returned.emplace_back(compType);
                        return [&] (auto compExpr) -> esl::result<void> {
                            returnStmts.push_back(c::returnValue(i, compExpr.expression));
                            return {};

                        } || target::result{} <<=
                            interface::translateValue(outerScope) || target::category{} <<= compVal;


                    } || target::category{} <<= args(posRet, negRet);
                    if (!result) return result.error();
                }
                return returnResult;

            } | [&] <typename Pos, typename Neg> (Pos pos, Neg neg) -> StatementProcessingResult
            requires (
                (esl::same_but_cvref<Pos, NoReturn> || esl::same_but_cvref<Neg, NoReturn>) &&
                (esl::same_but_cvref<Pos, sem::Return> || esl::same_but_cvref<Neg, sem::Return>)
            ) {
                // One branch returns one doesn't.
                auto returningBranch = esl::first_of<sem::Return>(pos, neg);
                auto & returnStmts = esl::same_but_cvref<NoReturn, Neg>
                    ? posReturnStmts
                    : negReturnStmts;

                sem::Return returnResult;
                returnResult.always = false;

                for (auto const & [i, returned]: esl::enumerate(returningBranch.returned)) {
                    auto result = [&, i = i] (ReturnedValues values) {
                        // A comp-time value:
                        return [&] (sem::type::Function const &) -> esl::result<void> {
                            // Partially run-time function values:
                            returnResult.returned.emplace_back(values);
                            return {};

                        } | [&, i = i] (auto const & type) -> esl::result<void> {
                            // Compile-time value:
                            if (values.size() > 1) // Implementation error.
                                return esl::result_error{"Returning multiple compile-time values in a run-time if statement."};
                            if (values.size() == 0) // Implementation error.
                                return esl::result_error{"Returning empty compile-time values in a run-time if statement."};
                            auto const & value = values.front();

                            return [&] (auto expr) -> esl::result<void> {
                                returnStmts.push_back(c::returnValue(i, expr.expression));
                                return {};

                            } || target::result{} <<=
                            interface::translateValue(outerScope) || target::category{} <<= value;

                        } || target::category{} <<= interface::returnedValuesType <<= values;

                    } | [&] (CompleteType type) -> esl::result<void> {
                        // A run-time value:
                        returnResult.returned.emplace_back(type);
                        return {};

                    } || target::category{} <<= returned;
                    if (!result) return result.error();
                }

                return returnResult;

            } | [] (NoReturn, NoReturn) -> StatementProcessingResult {
                // No branches return.
                return NoReturn{};

            } || target::optional_result{} <<= args(
                interface::processStatement(posBranchScope) || target::category{} <<= *positiveBranch,
                interface::processStatement(negBranchScope) || target::category{} <<= *negativeBranch
            );

            return {
                returnResult,
                posReturnStmts,
                negReturnStmts,
            };
        }

    }

    StatementProcessingResult syn::node::ExprIf::processStatement (context::Main & outerScope) const {
        return [&] (CompleteValue cond) -> StatementProcessingResult {
            // Compile-time condition value:

            // Note: No implicit conversions of the if condition will be implemented in the first version.
            auto boolResult = cond.template get<sem::value::Bool>();
            if (!boolResult)
                return esl::result_error{"If condition must be an integer value."};

            auto branchScope = outerScope.makeScopeChild();

            auto returnResult = [&] (auto cond) -> StatementProcessingResult {
                auto const & branch = cond ? *positiveBranch : *negativeBranch;
                return interface::processStatement(branchScope) || target::category{} <<= branch;

            } || target::result{} <<= interface::get<Integral>(*boolResult);

            auto head = c::blockBegin();
            auto end  = c::end();

            /***
            {
                <branch>
            }
            ***/
            outerScope.insertStatement(head);
            /* TODO: Do I need to do this here too?
            for (auto const & ret: returnStmts)
                outerScope.insertStatement(c::indented(ret));
            */
            outerScope.mergeNestedChild(branchScope);
            outerScope.insertStatement(end);

            return returnResult;

        } | [&] (TypedExpression cond) -> StatementProcessingResult {
            // Run-time condition value:

            // Note: No implicit conversions of the if condition will be implemented in the first version.
            if (!cond.type.template holds_alternative<sem::type::Bool>())
                return esl::result_error{"If condition must be an integer value."};

            auto posBranchScope = outerScope.makeScopeChild();
            auto negBranchScope = outerScope.makeScopeChild();

            auto result = processIfStatement(
                outerScope,
                posBranchScope,
                negBranchScope,
                positiveBranch,
                negativeBranch
            );

            auto ifHead   = c::ifBegin(cond.expression);
            auto elseHead = c::cuddledElse();
            auto end      = c::end();

            /***
            if (<cond>) {
                result.e<n> = <value> # for all comp-time values
                <pos>
            } else {
                <neg>
            }
            ***/
            outerScope.insertStatement(ifHead);
            for (auto const & ret: result.posReturnStmts)
                outerScope.insertStatement(c::indented(ret));
            outerScope.mergeNestedChild(negBranchScope);
            outerScope.insertStatement(elseHead);
            for (auto const & ret: result.negReturnStmts)
                outerScope.insertStatement(c::indented(ret));
            outerScope.mergeNestedChild(posBranchScope);
            outerScope.insertStatement(end);

            return result.returnResult;

        } || target::nested<target::result, target::category>{} <<=
        esl::single || target::result{} <<=
        interface::processExpression(outerScope) || target::category{} <<= *condition;
    }

}
