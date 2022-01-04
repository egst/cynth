#include "syn/nodes/common/array_nodes.hpp"

#include <optional>

#include "esl/category.hpp"
#include "esl/lift.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"

#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/compound.hpp"
#include "sem/numeric_types.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"

namespace cynth::syn::array_nodes {

    namespace target = esl::target;
    using namespace esl::sugar;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::TypedExpression;
    using sem::Integral;
    using sem::ArrayAllocation;
    using sem::ResolvedValue;
    using sem::CompleteValue;

    esl::result<ElementsResult> processElements (
        context::Main & ctx,
        esl::component_vector<category::ArrayElement> const & elements
    ) {
        return [&] (auto elems) -> esl::result<ElementsResult> {
            Integral arraySize = elems.size();
            esl::tiny_vector<CompleteValue> compVals;
            std::optional<CompleteType> elemType;
            bool runtime = false;

            for (auto elem: elems) {
                // Check types:
                auto type = interface::resolvedValueType || target::category{} <<= elem;
                if (!(interface::isSimple || target::category{} <<= type))
                    return esl::result_error{"Arrays of compound or referential types are not supported yet."};
                if (!elemType)
                    elemType = type;
                else if (!(interface::sameTypes || target::category{} <<= args(type, *elemType)))
                    // Note: Conversions to a common type are not supported yet.
                    return esl::result_error{"Incompatible types of values in an array literal."};
                // Extract comp-time values:
                [&] (CompleteValue const & value) {
                    // Continue extracting only if no run-time values have been found yet:
                    if (!runtime) compVals.push_back(value);

                } | [&] (TypedExpression const &) {
                    runtime = true;

                } || target::category{} <<= elem;
            }

            /*
            if (!elemType) // Either an empty array literal, or an implementation error.
                return esl::result_error{"Couldn't infer element type of an array."};
            */
            std::optional<sem::type::Array> arrayType;
            if (elemType)
                arrayType = {*elemType, arraySize};

            if (runtime || static_cast<Integral>(compVals.size()) != arraySize)
                compVals.clear();

            return ElementsResult{
                .arraySize  = arraySize,
                .compValues = compVals,
                .values     = elems,
                .arrayType  = arrayType
            };

        } || target::result{} <<= interface::processArrayElementCategories(ctx)(elements);

    }

    namespace {

        /***
        Int const [3] const a = [1, 2, 3];
        a[1]; # compile-time array
        ***/
        constexpr auto comptimeArraySubscript =
            [] (
                CompleteType const &, Integral index, ArrayAllocation const & alloc
            ) -> SingleExpressionProcessingResult {
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

    SingleExpressionProcessingResult processVerifiedSubscriptExpression (
        context::Main & ctx,
        std::string const & index,
        ResolvedValue const & array
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
                auto allocName = alloc->allocate(ctx);
                return runtimeSubscript(*type.type, index, allocName);

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

    SingleExpressionProcessingResult processSubscriptExpression (
        context::Main & ctx,
        TypedExpression const & index,
        ResolvedValue   const & array
    ) {
        // Run-time index.

        // Note: There will be no implicit conversions in the first version.
        if (!index.type.get<sem::type::Int>())
            return esl::result_error{"Only integers can be used as subscript indices."};
        return processVerifiedSubscriptExpression(ctx, index.expression, array);

        /*
        return [&] (auto index) {
            return processVerifiedSubscriptExpression(ctx, index.expression, array);

        } || target::result{} <<= translateConversion(ctx, index)(sem::type::Int{});
        */
    }

    SingleExpressionProcessingResult processSubscript (
        context::Main & ctx,
        sem::ResolvedValue const & index,
        sem::ResolvedValue const & array
    ) {
        return [&] (CompleteValue const & index) -> SingleExpressionProcessingResult {
            // Note: There will be no implicit conversions in the first version.
            auto valueResult = index.get<sem::value::Int>();
            if (!valueResult) return valueResult.error();
            auto intResult = interface::get<sem::Integral>(*valueResult);
            return processStaticSubscript(*intResult)(array);

        } | [&] (TypedExpression const & index) -> SingleExpressionProcessingResult {
            return processSubscriptExpression(ctx, index, array);

        } || target::category{} <<= index;
    }

    // TODO: The following hepers should be somewhere more generic than in syn/nodes/common.

    std::string arrayAllocation (
        context::Main            & ctx,
        tpl::TypeSpecifier const & type,
        sem::Integral              size
    ) {
        auto valType = ctx.global.instantiateType(tpl::Array{
            .elemType = type,
            .size     = size
        }); // cth_arr$<size>$<type>
        auto valName = c::valueName(c::id(ctx.nextId()));
        auto valInit = c::zeroInitialization();
        auto alloc   = c::statement(c::definition(valType, valName, valInit));
        ctx.function.insertAllocation(alloc);
        return valName;
    }

    namespace test {

        template <esl::range T>
        std::string arrayIndividualInitialization (std::string const & array, T const & values) {
            std::vector<std::string> result;
            result.reserve(values.size());
            for (auto const & [i, value]: esl::enumerate(values)) {
                auto assgn = c::statement(c::assignment(value, c::arraySubscript(array, std::to_string(i))));
                result.push_back(assgn);
            }
            return c::join(c::newLine(), result);
        }

    }

    void individualArrayInitialization (
        context::Main                       & ctx,
        std::string                   const & allocation,
        esl::tiny_vector<std::string> const & elements
    ) {
        //auto init = c::arrayIndividualInitialization(allocation, elements);
        auto init = test::arrayIndividualInitialization(allocation, elements);
        ctx.insertStatement(init);
    }

    void bulkArrayInitialization (
        context::Main        & ctx,
        std::string    const & allocation,
        std::string    const & source
    ) {
        auto init = c::arrayBulkInitialization(allocation, source);
        ctx.insertStatement(init);
    }

}
