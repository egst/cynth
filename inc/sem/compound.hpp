#pragma once

#include <string>
#include <variant>

#include "esl/lift.hpp"

#include "context/forward.hpp"
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

        /** This assumes already checked and converted type of the value. */
        esl::result<void> assign (context::C &, ResolvedValue const &);
        // TODO: Or maybe the conversion should happen here?
    };

}
