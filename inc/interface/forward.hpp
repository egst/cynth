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
    using NameExtractionResult             = esl::result<std::vector<std::string>>;
    using TypeNameExtractionResult         = esl::result<std::vector<std::string>>;
    // TODO: Do I really need a TypedResolvedValue for exrpession resolution?
    // Maybe it should be more like variant<struct { CompleteType type; string expression }, CompleteValue>,
    // not struct { CompleteType type; variant<CompleteValue, string> }
    // The first option more represents the information more precisely (more tightly) and saves a little bit of space
    // while the second one needs a little more space, but might save some time by caching the type.

    // Types:
    // For full declarations, #include "interface/types.hpp"
    using TypeNameConstant            = char const * const;
    using TypeNameResult              = esl::result<std::string>;
    using SameTypeResult              = bool;
    using CommonTypeResult            = esl::result<sem::CompleteType>;
    using ConstTypeResult             = bool;
    using TypeCompletionResult        = esl::result<sem::CompleteType>;
    using TypeTranslationResult       = esl::result<std::string>;
    using DefinitionTranslationResult = esl::result<sem::Variable>;
    using AllocationTranslationResult = esl::result<std::string>;
    using ConversionTranslationResult = esl::result<sem::ResolvedValue>;
    // TODO: Will `translateAllocation` only translate C allocations, or the compile-time ones as well?

    // Values:
    // For full declarations, #include "interface/values.hpp"
    template <typename T>
    using GetResult               = esl::result<T>;
    using ConversionResult        = esl::result<sem::CompleteValue>;
    using ValueTypeResult         = sem::CompleteType;
    using ValueTranslationResult  = esl::result<std::string>;
    using TargetTranslationResult = esl::result<std::string>;

}
