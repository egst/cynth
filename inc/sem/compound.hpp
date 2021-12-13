#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <variant>

#include "esl/lift.hpp"

#include "context/forward.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"

// TODO: Create the incomplete/complete pair for these declarations too.

namespace cynth::sem {

    struct Variable {
        CompleteType                 type;
        // TODO: Can I statically enforce presence of a value in at least one of the optionals?
        std::optional<CompleteValue> value;
        std::optional<std::string>   variable;
    };

    // TODO: Probably won't be needed.
    struct RuntimeValue {
        CompleteType type;
        std::string  expression;
    };

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

    struct CapturedValue {
        using Variant = std::variant<
            CompleteValue, // comp-time or static value => capture the value
            CompleteType   // run-time non-static value => capture the type only
        >;
        Variant value;
    };

    /**
     *  values:
     *  * comp-time or static value => capture the value
     *  * run-time non-static value => capture the type only
     */
    struct Capture {
        std::unordered_map<std::string, esl::tiny_vector<CompleteType>>  types;
        std::unordered_map<std::string, esl::tiny_vector<CapturedValue>> values;
    };

    /**
     *  values:
     *  * comp-time or static value => the captured value
     *  * run-time non-static value => name of a runtime context member
     */
    struct KnownCapture {
        std::unordered_map<std::string, esl::tiny_vector<CompleteType>>  types;
        std::unordered_map<std::string, esl::tiny_vector<ResolvedValue>> values;
    };

}
