#pragma once

#include <string>
#include <optional>

#include "esl/result.hpp"

#include "sem/forward.hpp"

namespace cynth::sem {

    // Types:
    using CommonTypeResult       = esl::result<CompleteType>;
    using SameTypeResult         = bool;
    using TypeTranslationResult  = esl::result<std::string>;
    using TypeCompletionResult   = esl::result<CompleteType>;
    using TypeDecayResult        = std::optional<CompleteType>;
    // Values:
    using ConversionResult       = esl::result<CompleteValue>;
    template <typename T>
    using GetResult              = esl::result<T>;
    using ValueTypeResult        = CompleteType;
    using TargetResolutionResult = esl::result<TypedTargetValue>;

}
