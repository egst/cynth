#include "interface/misc.hpp"

#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/sugar.hpp"

#include "context/c.hpp"
#include "interface/values.hpp"
#include "sem/compound.hpp"
#include "sem/numeric_types.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"

namespace cynth::interface {

    using namespace esl::sugar;

    namespace target = esl::target;

    using sem::ArrayAllocation;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::Integral;
    using sem::ResolvedValue;
    using sem::TypedExpression;

    namespace {

        /***
        Int const [3] const a = [1, 2, 3];
        a[1]; # compile-time array
        ***/
        constexpr auto comptimeArraySubscript =
            [] (CompleteType const & type, Integral index, ArrayAllocation const & alloc)
            -> SingleExpressionProcessingResult {
                // TODO: type probably not needed.
                return ResolvedValue{
                    alloc.value[index]
                };
            };

        /***
        Int [3] a = [1, 2, 3];
        a[1]; # run-time array
        ***/
        constexpr auto runtimeArraySubscript =
            [] (CompleteType const & type, Integral index, std::string const & expr) {
                return ResolvedValue{TypedExpression{
                    .type       = type,
                    .expression = c::arraySubscript(expr, std::to_string(index))
                }};
            };

        /***
        Int [3] a = [1, 2, 3];
        Int i = 1;
        a[1]; # run-time array and index
        ***/
        constexpr auto runtimeSubscript =
            [] (CompleteType const & type, std::string const & index, std::string const & expr) {
                return ResolvedValue{TypedExpression{
                    .type       = type,
                    .expression = c::arraySubscript(expr, index)
                }};
            };

    }

    // TODO: No array value type conversions are assumed here.
    // TODO: Constness?
    SingleExpressionProcessingResult detail::misc::processStaticSubscript (
        Integral index,
        ResolvedValue const & array
    ) {
        return array >>= target::category{} &&
        // Comp-time array pointer:
        [index] (CompleteValue const & value) -> SingleExpressionProcessingResult {
            auto arrayResult = value.get<sem::value::Array>();
            if (!arrayResult)
                return esl::result_error{"Subscript can only be performed on an array."};
            auto & array = *arrayResult;

            auto type = array.valueType;
            if (index >= type.size)
                return esl::result_error{"Subscript index out of bounds."};

            return array.allocation >>= target::variant{} &&
            // Comp-time array allocation:
            [index, &type] (ArrayAllocation * alloc) -> SingleExpressionProcessingResult {
                return comptimeArraySubscript(*type.type, index, *alloc);
            } |
            // Run-time array allocation:
            [index, &type] (std::string const & alloc) -> SingleExpressionProcessingResult {
                return runtimeArraySubscript(*type.type, index, alloc); // Subscript directly from the allocation variable.
            };

        } |
        // Run-time array pointer:
        [index] (TypedExpression const & value) -> SingleExpressionProcessingResult {
            auto typeResult = value.type.get<sem::type::Array>();
            if (!typeResult)
                return esl::result_error{"Subscript can only be performed on an array."};
            auto & type = *typeResult;

            if (index >= type.size)
                return esl::result_error{"Subscript index out of bounds."};
            return runtimeArraySubscript(*type.type, index, value.expression);
        };
    }

    SingleExpressionProcessingResult processSubscript (
        context::C & ctx,
        sem::ResolvedValue const & index,
        sem::ResolvedValue const & array
    ) {
        return index >>= target::category{} &&
        // Comp-time index:
        [&array] (CompleteValue const & index) -> SingleExpressionProcessingResult {
            auto conversionResult = index >>= target::category{} && convertSimpleValueTo(sem::type::Int{});
            auto indexResult = conversionResult >>= target::result{} && get<Integral>;
            if (!indexResult) return indexResult.error();
            auto integralIndex = *indexResult;

            return processStaticSubscript(integralIndex)(array);
        } |
        // Run-time index:
        [&ctx, &array] (TypedExpression const & index) -> SingleExpressionProcessingResult {
            auto indexResult = translateConversion(ctx, index)(sem::type::Int{});
            if (!indexResult) return indexResult.error();
            auto indexExpr = std::move(indexResult)->expression;

            return array >>= target::category{} &&
            // Comp-time array pointer:
            [&ctx, indexExpr] (CompleteValue const & value) -> SingleExpressionProcessingResult {
                auto arrayResult = value.get<sem::value::Array>();
                if (!arrayResult)
                    return esl::result_error{"Subscript can only be performed on an array."};
                auto & array = *arrayResult;
                auto type = array.valueType;

                return array.allocation >>= target::variant{} &&
                // Comp-time array allocation:
                [&ctx, &indexExpr, &type] (ArrayAllocation * alloc) -> SingleExpressionProcessingResult {
                    auto allocResult = alloc->allocate(ctx);
                    if (!allocResult) return allocResult.error();
                    return runtimeSubscript(*type.type, indexExpr, *allocResult);
                } |
                // Run-time array allocation:
                [&indexExpr, &type] (std::string const & alloc) -> SingleExpressionProcessingResult {
                    return runtimeSubscript(*type.type, indexExpr, alloc);
                };
            } |
            // Run-time array pointer:
            [indexExpr] (TypedExpression const & value) -> SingleExpressionProcessingResult {
                auto typeResult = value.type.get<sem::type::Array>();
                if (!typeResult)
                    return esl::result_error{"Subscript can only be performed on an array."};
                auto & type = *typeResult;

                return runtimeSubscript(*type.type, indexExpr, value.expression);
            };
        };
    }

}
