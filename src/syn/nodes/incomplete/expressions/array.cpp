#include "syn/nodes/incomplete/expressions/array.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include "esl/category.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"

#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "sem/compound.hpp"
#include "sem/numeric_types.hpp"
#include "sem/translation.hpp"
#include "sem/values.hpp"
#include "syn/nodes/common/array_nodes.hpp"

// TMP
#include "esl/debug.hpp"
#include "esl/macros.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::NameExtractionResult;
    using interface::TypeNameExtractionResult;
    using sem::CompleteValue;
    using sem::ArrayAllocation;
    using sem::ResolvedValue;
    using sem::Integral;

    DisplayResult node::Array::display () const {
        using Target = target::nested<target::component_vector, target::category>;
        return "[" + esl::join(", ", interface::display || Target{} <<= elements) + "]";
    }

    ExpressionProcessingResult node::Array::processExpression (context::Main & ctx) const {
        return [&] (auto elemsResult) -> ExpressionProcessingResult {
            if (!elemsResult.arrayType)
                return esl::result_error{"Array cannot be empty."};

            if (elemsResult.compValues.size() == elemsResult.arraySize) {
                // All values comp-time:
                auto & alloc = ctx.function.storeValue(ArrayAllocation{
                    esl::make_component_vector(elemsResult.compValues)
                });
                alloc.sequentialize();
                return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{sem::value::Array{
                    .allocation = &alloc,
                    .valueType  = *elemsResult.arrayType
                }}});
            }

            // Some values run-time:
            return [&] (auto translType, auto translElems) {
                auto allocName = array_nodes::arrayAllocation(ctx, translType, elemsResult.arraySize);
                array_nodes::individualArrayInitialization(ctx, allocName, translElems);

                return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{sem::value::Array{
                    .allocation = allocName,
                    .valueType  = *elemsResult.arrayType
                }}});

            } || target::result{} <<= args(
                interface::translateTypeSpecifier || target::category{} <<= *elemsResult.arrayType->type,
                interface::expression || target::nested<target::result, target::tiny_vector>{} <<=
                    esl::unite_results <<=
                    interface::translateResolvedValue(ctx) || target::tiny_vector{} <<= elemsResult.values
            );

        } || target::result{} <<= array_nodes::processElements(ctx, elements);
    }

    NameExtractionResult node::Array::extractNames (context::Lookup & ctx) const {
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::extractNames(ctx) || target::nested<target::component_vector, target::category>{} <<=
            elements;
    }

    TypeNameExtractionResult node::Array::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::extractTypeNames(ctx) || target::nested<target::component_vector, target::category>{} <<=
            elements;
    }

}
