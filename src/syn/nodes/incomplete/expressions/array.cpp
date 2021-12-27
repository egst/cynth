#include "syn/nodes/incomplete/expressions/array.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include <optional>

#include "esl/category.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"

#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/compound.hpp"
#include "sem/numeric_types.hpp"
#include "sem/translation.hpp"
#include "sem/values.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::TypedExpression;
    using sem::ArrayAllocation;
    using sem::ResolvedValue;
    using sem::Integral;

    DisplayResult node::Array::display () const {
        using Target = target::nested<target::component_vector, target::category>;
        return "[" + esl::join(", ", interface::display || Target{} <<= elements) + "]";
    }

    ExpressionProcessingResult node::Array::processExpression (context::Main & ctx) const {
        return [&] (auto elems) -> ExpressionProcessingResult {
            Integral arraySize = elems.size();

            esl::tiny_vector<CompleteValue> compVals;
            std::optional<CompleteType>     elemType;
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

                } | [&] (TypedExpression const & expr) {
                    runtime = true;

                } || target::category{} <<= elem;
            }

            if (!elemType) // Either an empty array literal, or an implementation error.
                return esl::result_error{"Couldn't infer element type of an array."};
            sem::type::Array arrayType = {*elemType, arraySize};

            if (compVals.size() == arraySize) {
                // All values comp-time:
                auto & alloc = ctx.function.storeValue(ArrayAllocation{esl::make_component_vector(compVals)});
                alloc.sequentialize();
                return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{sem::value::Array{
                    .allocation = &alloc,
                    .valueType  = arrayType
                }}});
            }

            // Some values run-time:
            // TODO: The allocation process should be separated and generalized to be reused in other locations.
            return [&] (auto translType, auto translElems) {
                auto valType = ctx.global.instantiate(tpl::Array{.elemType = translType, .size = arraySize}); // cth_arr$<size>$<type>
                auto valName = c::valueName(c::id(ctx.nextId()));
                auto valInit = c::zeroInitialization();
                auto alloc   = c::definition(valType, valName, valInit);
                auto init    = c::arrayIndividualInitialization(valName, translElems);

                ctx.function.insertAllocation(alloc);
                ctx.insertStatement(init);

                return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{sem::value::Array{
                    .allocation = valName,
                    .valueType  = arrayType
                }}});

            } || target::result{} <<= args(
                interface::translateType || target::category{} <<= *elemType,
                interface::expression || target::nested<target::result, target::tiny_vector>{} <<=
                    esl::unite_results <<= interface::translateResolvedValue(ctx) || target::tiny_vector{} <<= elems
            );

        } || target::result{} <<= interface::processArrayElementCategories(ctx)(elements);
    }

}
