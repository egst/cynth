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
        return [index] (CompleteValue const & value) -> SingleExpressionProcessingResult {
            // Comp-time array pointer.
            auto arrayResult = value.get<sem::value::Array>();
            if (!arrayResult)
                return esl::result_error{"Subscript can only be performed on an array."};
            auto & array = *arrayResult;
            // TODO: target::reference_result?

            auto type = array.valueType;
            if (index >= type.size)
                return esl::result_error{"Subscript index out of bounds."};

            return [index, &type] (ArrayAllocation * alloc) -> SingleExpressionProcessingResult {
                // Comp-time array allocation.
                return comptimeArraySubscript(*type.type, index, *alloc);

            } | [index, &type] (std::string const & alloc) -> SingleExpressionProcessingResult {
                // Run-time array allocation.
                return runtimeArraySubscript(*type.type, index, alloc); // Subscript directly from the allocation variable.

            } || target::variant{} <<= array.allocation;

        } | [index] (TypedExpression const & value) -> SingleExpressionProcessingResult {
            // Run-time array pointer.
            auto typeResult = value.type.get<sem::type::Array>();
            if (!typeResult)
                return esl::result_error{"Subscript can only be performed on an array."};
            auto & type = *typeResult;

            if (index >= type.size)
                return esl::result_error{"Subscript index out of bounds."};
            return runtimeArraySubscript(*type.type, index, value.expression);

        } || target::category{} <<= array;
    }

    SingleExpressionProcessingResult processVerifiedSubscript (
        context::C & ctx,
        std::string const & index,
        sem::ResolvedValue const & array
    ) {
        return [&] (CompleteValue const & value) -> SingleExpressionProcessingResult {
            // Comp-time array pointer.
            auto arrayResult = value.get<sem::value::Array>();
            if (!arrayResult)
                return esl::result_error{"Subscript can only be performed on an array."};
            auto & array = *arrayResult;
            auto type = array.valueType;

            return [&] (ArrayAllocation * alloc) -> SingleExpressionProcessingResult {
                // Comp-time array allocation.
                return [&] (auto alloc) {
                    return runtimeSubscript(*type.type, index, alloc);
                } || target::result{} <<= alloc->allocate(ctx);

            } | [&] (std::string const & alloc) -> SingleExpressionProcessingResult {
                // Run-time array allocation.
                return runtimeSubscript(*type.type, index, alloc);

            } || target::variant{} <<= array.allocation;

        } | [&] (TypedExpression const & value) -> SingleExpressionProcessingResult {
            // Run-time array pointer.
            auto typeResult = value.type.get<sem::type::Array>();
            if (!typeResult)
                return esl::result_error{"Subscript can only be performed on an array."};
            auto & type = *typeResult;

            return runtimeSubscript(*type.type, index, value.expression);

        } || target::category{} <<= array;
    };

    SingleExpressionProcessingResult processSubscript (
        context::C & ctx,
        sem::TypedExpression const & index,
        sem::ResolvedValue   const & array
    ) {
        // Run-time index.

        // Note: There will be no implicit conversions in the first version.
        if (!index.type.get<sem::type::Int>())
            return esl::result_error{"Only integers can be used as subscript indices."};
        return processVerifiedSubscript(ctx, index.expression, array);

        /*
        return [&] (auto index) {
            return processVerifiedSubscript(ctx, index.expression, array);

        } || target::result{} <<= translateConversion(ctx, index)(sem::type::Int{});
        */
    }

}
