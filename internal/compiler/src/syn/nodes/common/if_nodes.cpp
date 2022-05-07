#include "syn/nodes/common/if_nodes.hpp"

#include <string>

#include "esl/lift.hpp"
#include "esl/sugar.hpp"
#include "esl/component.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/zip.hpp"
#include "esl/result.hpp"
#include "esl/concepts.hpp"
#include "esl/type_manip.hpp"

#include "config.hpp"
#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/translation.hpp"
#include "syn/categories/expression.hpp"
#include "syn/categories/statement.hpp"

namespace cynth::syn::if_nodes {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::StatementProcessingResult;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::NoReturn;
    using sem::ReturnedValues;
    using sem::TypedExpression;

    namespace {

        struct StatementResult {
            interface::StatementProcessingResult returnResult;
            // Returned compile-time values:
            esl::tiny_vector<std::string> posReturnStmts;
            esl::tiny_vector<std::string> negReturnStmts;
        };

        template <typename Branch>
        StatementResult processBranches (
            context::Main & outerScope,
            context::Main & posBranchScope,
            context::Main & negBranchScope,
            Branch const  & positiveBranch,
            Branch const  * negativeBranch
        ) {
            esl::tiny_vector<std::string> posReturnStmts;
            esl::tiny_vector<std::string> negReturnStmts;

            auto returnResult = [&] (sem::Return pos, sem::Return neg) -> StatementProcessingResult {
                // Both branches return.
                if (pos.returned.size() != neg.returned.size())
                    return esl::result_error{"Returning a different number of values in each branch."};

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
                            if (posVals.size() == 0 || negVals.size() == 0) // Implementation error.
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

                        } | [&] (auto const &, auto const &) -> esl::result<void> {
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

                        } | [&, i = i] (auto const &) -> esl::result<void> {
                            // Compile-time value:
                            if (values.size() > 1) // Implementation error.
                                return esl::result_error{"Returning multiple compile-time values in a run-time if statement."};
                            if (values.size() == 0) // Implementation error.
                                return esl::result_error{"Returning empty compile-time values in a run-time if statement."};
                            auto const & value = values.front();

                            return [&] (auto expr) -> esl::result<void> {
                                returnStmts.push_back(c::returnValue(i, expr.expression));
                                returnResult.returned.emplace_back(expr.type);
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
                interface::processStatement(posBranchScope) || target::category{} <<= positiveBranch,
                interface::processStatement(negBranchScope) ||
                    target::nested<target::pointer, target::category>{} <<= negativeBranch
                    // This way, the second argument will be simply handled like NoReturn for the `while` statement,
                    // as if it was `if (<cond>) <pos> else {}`.
            );

            return {
                returnResult,
                posReturnStmts,
                negReturnStmts,
            };
        }

    }

    template <typename Branch>
    StatementProcessingResult processStatement (
        context::Main              & outerScope,
        category::Expression const & condition,
        Branch               const & positiveBranch,
        Branch               const * negativeBranch
    ) {
        return [&] (CompleteValue cond) -> StatementProcessingResult {
            // Compile-time condition value:

            // Note: No implicit conversions of the if condition will be implemented in the first version.
            auto boolResult = cond.template get<sem::value::Bool>();
            if (!boolResult)
                return esl::result_error{"If condition must be a boolean value."};

            auto branchScope = outerScope.makeScopeChild();

            auto returnResult = [&] (auto cond) -> StatementProcessingResult {
                // if..else:
                if (negativeBranch) {
                    auto const & branch = cond ? positiveBranch : *negativeBranch;
                    return interface::processStatement(branchScope) || target::category{} <<= branch;

                // when:
                } else if (cond) {
                    return interface::processStatement(branchScope) || target::category{} <<= positiveBranch;
                } else {
                    return NoReturn{};
                }

            } || target::result{} <<= interface::get<bool>(*boolResult);

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
            outerScope.mergeChild(branchScope);
            outerScope.insertStatement(end);

            return returnResult;

        } | [&] (TypedExpression cond) -> StatementProcessingResult {
            // Run-time condition value:

            // Note: No implicit conversions of the if condition will be implemented in the first version.
            if (!cond.type.template holds_alternative<sem::type::Bool>())
                return esl::result_error{"If condition must be an boolean value."};

            auto posBranchScope = outerScope.makeScopeChild();
            auto negBranchScope = outerScope.makeScopeChild();

            auto result = processBranches(
                outerScope,
                posBranchScope,
                negBranchScope,
                positiveBranch,
                negativeBranch
            );

            auto ifHead   = c::ifBegin(cond.expression);
            auto elseHead = c::cuddledElse();
            auto end      = c::end();
            auto jump     = c::returnJump();

            /***
            if (<cond>) {
                result.e<n> = <value> # for all comp-time values
                <pos>
                goto ret; # if ayways returns
            ***/
            outerScope.insertStatement(ifHead);
            for (auto const & ret: result.posReturnStmts)
                outerScope.insertStatement(c::indented(ret));
            outerScope.mergeChild(posBranchScope);
            if (result.returnResult)
                outerScope.insertStatement(c::indented(jump));

            /***
            } else {
                <neg>
                goto ret; # if ayways returns
            ***/
            if (negativeBranch) {
                // if..else:
                outerScope.insertStatement(elseHead);
                for (auto const & ret: result.negReturnStmts)
                    outerScope.insertStatement(c::indented(ret));
                outerScope.mergeChild(negBranchScope);
                if (result.returnResult)
                    outerScope.insertStatement(c::indented(jump));
            }

            /***
            }
            ***/
            outerScope.insertStatement(end);

            return result.returnResult;

        } || target::nested<target::result, target::category>{} <<=
            esl::single || target::result{} <<=
            interface::processExpression(outerScope) || target::category{} <<= condition;
    }

    template
    StatementProcessingResult processStatement (
        context::Main              &,
        category::Expression const &,
        category::Expression const &,
        category::Expression const *
    );

    template
    StatementProcessingResult processStatement (
        context::Main              &,
        category::Expression const &,
        category::Statement  const &,
        category::Statement  const *
    );

}
