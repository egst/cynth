#pragma once

#include <optional>
#include <string>
#include <vector>

#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"

// Forward declarations that might need to be resolved:
#include "sem/forward.hpp"

namespace cynth::interface {

    // Common results:
    // Fully declared. ("interface/common.hpp")
    using DisplayResult = std::string;

    // Nodes:
    // For full declarations, #include "interface/nodes.hpp"
    using ExpressionResolutionResult       = esl::result<esl::tiny_vector<sem::TypedResolvedValue>>;
    using ArrayElementResolutionResult     = esl::result<std::vector<esl::tiny_vector<sem::TypedResolvedValue>>>;
    using TypeResolutionResult             = esl::result<esl::tiny_vector<sem::CompleteType>>;
    using StatementResolutionResult        = esl::result<void>;
    using DeclarationResolutionResult      = esl::result<esl::tiny_vector<sem::CompleteDeclaration>>;
    using RangeDeclarationResolutionResult = esl::result<esl::tiny_vector<sem::CompleteRangeDeclaration>>;
    using TargetResolutionResult           = esl::result<esl::tiny_vector<sem::TypedResolvedTarget>>;

    // Types:
    // For full declarations, #include "interface/types.hpp"
    using TypeNameConstant            = char const * const;
    using TypeNameResult              = esl::result<std::string>;
    using SameTypeResult              = bool;
    using CommonTypeResult            = esl::result<sem::CompleteType>;
    using ConstTypeResult             = bool;
    using TypeCompletionResult        = esl::result<sem::CompleteType>;
    using TypeTranslationResult       = esl::result<std::string>;
    using DefinitionTranslationResult = esl::result<sem::ResolvedValue>;
    using AllocationTranslationResult = esl::result<std::string>;
    using ConversionTranslationResult = esl::result<std::string>;

    // Values:
    // For full declarations, #include "interface/values.hpp"
    template <typename T>
    using GetResult              = esl::result<T>;
    using ConversionResult       = esl::result<sem::CompleteValue>;
    using ValueTypeResult        = sem::CompleteType;
    using ValueTranslationResult = esl::result<std::string>;

}
