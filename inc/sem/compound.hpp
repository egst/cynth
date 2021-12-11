#pragma once

#include <forward_list>
#include <optional>
#include <string>

#include "sem/types.hpp"
#include "sem/values.hpp"

namespace cynth::sem {

    struct TranslatedValue {
        CompleteType type;
        std::optional<CompleteValue> value;      // Compilation constant value.
        std::optional<std::string>   expression; // Translated C expression - a name or a literal or something...
    };

    struct TypedValue {
        CompleteType type;
        std::optional<CompleteValue> value;    // Compilation constant value.
        std::optional<std::string>   variable; // Runtime variable name.
    };

    struct TypedTargetValue {
        CompleteValue * value;
        CompleteType    type;

        /*
        esl::result<void> assign (ValueVector && values) {
            return esl::lift<esl::target::tiny_vector>(
                [] (CompleteValue * target, CompleteValue && value) {
                    *target = std::move(value);
                }
            )(value, std::move(values));
        }
        */
    };

}
