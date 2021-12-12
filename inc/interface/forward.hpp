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
    // Fully declared.
    using DisplayResult = std::string;

    // Compile time:
    // For full declarations, #include "interface/comptime.hpp"
    using StatementResolutionResult        = esl::result<void>;
    using ExpressionResolutionResult       = esl::result<esl::tiny_vector<sem::ResolvedValue>>;
    using TypeResolutionResult             = esl::result<esl::tiny_vector<sem::CompleteType>>;
    using ArrayElementResolutionResult     = esl::result<std::vector<esl::tiny_vector<sem::ResolvedValue>>>;
    using DeclarationResolutionResult      = esl::result<esl::tiny_vector<sem::CompleteDeclaration>>;
    using RangeDeclarationResolutionResult = esl::result<esl::tiny_vector<sem::CompleteRangeDeclaration>>;
    using TargetResolutionResult           = esl::result<esl::tiny_vector<sem::ResolvedTargetValue>>;

    // TODO...
    // Runtime:
    // For full declarations, #include "interface/runtime.hpp"
    using ExpressionTranslationResult = esl::result<esl::tiny_vector<sem::ResolvedValue>>;
    using StatementTranslationResult  = esl::result<void>;
    using DefinitionTranslationResult = esl::result<std::optional<std::string>>;

    // Type results:
    // For full declarations, #include "interface/types.hpp"
    using CommonTypeResult      = esl::result<sem::CompleteType>;
    using SameTypeResult        = bool;
    using TypeCompletionResult  = esl::result<sem::CompleteType>;
    using TypeDecayResult       = std::optional<sem::CompleteType>;
    using TypeNameConstant      = char const * const;
    using TypeNameResult        = esl::result<std::string>;
    using TypeTranslationResult = esl::result<std::string>;

    // Value results:
    // For full declarations, #include "interface/values.hpp"
    template <typename T>
    using GetResult              = esl::optional_result<T>;
    using ConversionResult       = esl::optional_result<sem::CompleteValue>;
    using ValueTypeResult        = sem::CompleteType;

}
