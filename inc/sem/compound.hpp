#pragma once

#include <string>
#include <variant>

#include "sem/types.hpp"
#include "sem/values.hpp"

namespace cynth::sem {

    struct ResolvedValue {
        using Variant = std::variant<
            CompleteValue, // Value known at compile time
            std::string    // C expression
        >;

        Variant value;
    };

    struct TypedResolvedValue {
        CompleteType type;
        ResolvedValue::Variant value;
    };

    struct ResolvedTarget {
        using Variant = std::variant<
            CompleteValue *, // Compconst variable only available at compile time
            std::string      // C variable name or other lvalue expression
        >;

        Variant target;
    };

    struct TypedResolvedTarget {
        CompleteType type;
        ResolvedTarget::Variant target;
    };

    /* TODO?
    struct ResolvedTargetValue {
        CompleteType               type;
        CompleteValue *            value; // Might be null on purpose.
        std::optional<std::string> variable;

        esl::result<void> assign (ValueVector && values) {
            return esl::lift<esl::target::tiny_vector>(
                [] (CompleteValue * target, CompleteValue && value) {
                    *target = std::move(value);
                }
            )(value, std::move(values));
        }
    };
    */

}
