#pragma once

#include <string>
#include <optional>

#include "esl/result.hpp"

#include "sem/forward.hpp"

namespace cynth::sem {

    // Types:
    using CommonTypeResult            = esl::result<CompleteType>;
    using SameTypeResult              = bool;
    using ExpressionTranslationResult = esl::result<TranslatedExpression>;
    using StatementTranslationResult  = esl::result<void>;
    using TypeNameResult              = esl::result<std::string>;
    using TypeNameConstant            = char const * const;
    using TypeCompletionResult        = esl::result<CompleteType>;
    using TypeDecayResult             = std::optional<CompleteType>;
    // Values:
    using ConversionResult            = esl::result<CompleteValue>;
    template <typename T>
    using GetResult                   = esl::result<T>;
    using ValueTypeResult             = CompleteType;
    using TargetResolutionResult      = esl::result<TypedTargetValue>;

}
