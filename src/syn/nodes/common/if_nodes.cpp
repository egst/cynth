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

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/numeric_types.hpp"
#include "sem/translation.hpp"
#include "syn/categories/expression.hpp"

namespace cynth::syn::if_nodes {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::StatementProcessingResult;
    using sem::CompleteType;
    using sem::Integral;
    using sem::NoReturn;
    using sem::ReturnedValues;

    StatementResult processStatement (
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
