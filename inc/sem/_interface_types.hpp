#pragma once

#include <string>
#include <optional>

#include "esl/result.hpp"

#include "sem/forward.hpp"
// TODO: I probably should include the needed definitions as well.
// Providing declarations depending on other declarations
// that were only forward-declared proved cumbersome in many cases on this project.

namespace cynth::sem {

    // Types:
    using CommonTypeResult            = esl::result<CompleteType>;
    using SameTypeResult              = bool;
    using TypeDecayResult             = std::optional<CompleteType>;
    using TypeCompletionResult        = esl::result<CompleteType>;
    using TypeNameResult              = esl::result<std::string>;
    using TypeNameConstant            = char const * const;

    // Values:
    // Note: Returning nullopt result means the value depends on a runtime value and must be translated instead.
    using ConversionResult            = esl::optional_result<CompleteValue>;
    using TargetResolutionResult      = esl::optional_result<TypedTargetValue>;
    template <typename T>
    using GetResult                   = esl::optional_result<T>;
    using ValueTypeResult             = CompleteType;

}
