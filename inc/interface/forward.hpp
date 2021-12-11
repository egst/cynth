#pragma once

#include <optional>
#include <string>

#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"

// Forward declarations that might need to be resolved:
#include "sem/forward.hpp"

namespace cynth::interface {

    // Common results:
    // Fully declared.
    using DisplayResult = std::string;

    // Compile time:
    // For full declarations, #include "interface/comptime.hpp"
    using StatementExecutionResult         = esl::optional_result<esl::tiny_vector<sem::CompleteValue>>;
    using ExpressionEvaluationResult       = esl::result<esl::tiny_vector<sem::CompleteValue>>;
    using TypeResolutionResult             = esl::result<esl::tiny_vector<sem::IncompleteType>>;
    using ArrayElementEvaluationResult     = esl::result<esl::tiny_vector<sem::CompleteValue>>;
    using DeclarationResolutionResult      = esl::result<esl::tiny_vector<sem::IncompleteDeclaration>>;
    using RangeDeclarationResolutionResult = esl::result<esl::tiny_vector<sem::IncompleteRangeDeclaration>>;
    using TargetEvaluationResult           = esl::result<esl::tiny_vector<sem::Target>>;
    // TODO: Is this still needed?
    using SingleEvaluationResult           = esl::result<sem::CompleteValue>;

    // Runtime:
    // For full declarations, #include "interface/runtime.hpp"
    using ExpressionTranslationResult = esl::result<esl::tiny_vector<sem::TranslatedValue>>;
    using StatementTranslationResult  = esl::result<void>;
    using DefinitionTranslationResult = esl::result<std::optional<std::string>>;

    // Type results:
    // For full declarations, #include "interface/types.hpp"
    using CommonTypeResult     = esl::result<sem::CompleteType>;
    using SameTypeResult       = bool;
    using TypeDecayResult      = std::optional<sem::CompleteType>;
    using TypeCompletionResult = esl::result<sem::CompleteType>;
    using TypeNameResult       = esl::result<std::string>;
    using TypeNameConstant     = char const * const;

    // Value results:
    // For full declarations, #include "interface/values.hpp"
    template <typename T>
    using GetResult              = esl::optional_result<T>;
    using ConversionResult       = esl::optional_result<sem::CompleteValue>;
    using TargetResolutionResult = esl::optional_result<sem::TypedTargetValue>;
    using ValueTypeResult        = sem::CompleteType;

}
