#pragma once

#include <forward_list>
#include <optional>
#include <string>

#include "sem/types.hpp"
#include "sem/values.hpp"

namespace cynth::sem {

    struct ResolvedValue {
        CompleteType type;
        std::optional<CompleteValue> value;      // Compilation constant value.
        std::optional<std::string>   expression; // Translated C expression - a name or a literal or something...
    };

    struct LocalValue {
        CompleteType type;
        std::optional<CompleteValue> value;    // Compilation constant value.
        std::optional<std::string>   variable; // Runtime variable name.
    };

    // TODO: AllocatedValue/StaticValue/GlobalValue?

    struct ResolvedTargetValue {
        CompleteType               type;
        CompleteValue *            value; // Might be null on purpose.
        std::optional<std::string> variable;

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
