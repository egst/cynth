#pragma once

#include <optional>
#include <string>
#include <vector>

#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"

// Forward declarations that might need to be resolved:
#include "sem/forward.hpp"
#include "sem/translation.hpp"

namespace cynth::interface {

    // Common results:
    // Fully declared. ("interface/common.hpp")
    using DisplayResult = std::string;

    // Nodes:
    // For full declarations, #include "interface/nodes.hpp"
    using StatementProcessingResult        = esl::optional_result<sem::Return>;
    using ExpressionProcessingResult       = esl::result<esl::tiny_vector<sem::ResolvedValue>>;
    template <typename T>
    //using ArrayElementVector               = std::vector<T>; // Optimized for general case array values. (e.g. array[i, j, k], [a, b, c], etc.)
    using ArrayElementVector               = esl::tiny_vector<T>; // Optimized for single-valued array elements. (e.g. array[index], [a], etc.)
    using ArrayElementProcessingResult     = esl::result<ArrayElementVector<sem::ResolvedValue>>; // Assuming single-valued array elements.
    using TypeResolutionResult             = esl::result<esl::tiny_vector<sem::CompleteType>>;
    using DeclarationResolutionResult      = esl::result<esl::tiny_vector<sem::CompleteDeclaration>>;
    using RangeDeclarationResolutionResult = esl::result<esl::tiny_vector<sem::CompleteRangeDeclaration>>;
    using TargetResolutionResult           = esl::result<esl::tiny_vector<sem::ResolvedTarget>>;
    using NameExtractionResult             = esl::result<std::vector<std::string>>;
    using TypeNameExtractionResult         = esl::result<std::vector<std::string>>;

    // Types:
    // For full declarations, #include "interface/types.hpp"
    using TypeNameConstant               = char const * const;
    using TypeNameResult                 = esl::result<std::string>;
    using SameTypeResult                 = bool;
    using CommonTypeResult               = esl::result<sem::CompleteType>;
    using ConstTypeResult                = bool;
    using TypeTranslationResult          = std::string;
    using TypeSpecifierTranslationResult = tpl::TypeSpecifier;
    using TypeCompletionResult           = esl::result<sem::CompleteType>;
    using ConversionTranslationResult    = esl::result<sem::TypedExpression>;
    using DefinitionProcessingResult     = esl::result<sem::Variable>;
    using DeclarationProcessingResult    = DefinitionProcessingResult;
    //using AllocationTranslationResult = esl::result<sem::TypedExpression>;

    // Values:
    // For full declarations, #include "interface/values.hpp"
    template <typename T>
    using GetResult               = esl::result<T>;
    //using ConversionResult        = esl::result<sem::CompleteValue>;
    template <typename T>
    using ConversionResult        = esl::result<typename T::Value>;
    using DynamicConversionResult = esl::result<sem::CompleteValue>;
    using ValueTypeResult         = sem::CompleteType;
    using ValueTranslationResult  = esl::result<sem::TypedExpression>;
    using TargetTranslationResult = esl::result<sem::TypedTargetExpression>;

    // Compound:
    // Fully declared. ("interface/compound.hpp")
    using AssignmentProcessingResult = esl::result<void>;

}
