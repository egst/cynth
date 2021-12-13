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

    // Note: The following three have the same structure.
    // They are used in related but still pretty different contexts,
    // so I'd like to keep them separated to better describe their semantic intent.

    struct TypedExpression {
        CompleteType type;
        std::string  expression;
    };

    struct TypedName {
        CompleteType type;
        std::string  name;
    };

    /** E.g. `var`, `*var`, `var[2]` */
    struct TypedTargetExpression {
        CompleteType type;
        std::string  expression;
    };

    struct Variable {
        using Variant = std::variant<
            CompleteValue, // Value known at compile time
            TypedName      // Corresponding runtime C variable
        >;
        Variant value;
    };

    struct ResolvedValue {
        using Variant = std::variant<
            CompleteValue,  // Value known at compile time
            TypedExpression // C expression
        >;
        Variant value;
    };

    struct ResolvedTarget {
        using Variant = std::variant<
            CompleteValue *,      // Compconst variable only available at compile time
            TypedTargetExpression // C variable name or other lvalue expression
        >;
        Variant target;
    };

    struct Capture {
        using Variant = std::variant<
            CompleteValue, // Comp-time or static value => Capture the value
            CompleteType   // Run-time non-static value => Capture the type only
        >;
        Variant value;
    };

    struct ResolvedCapture {
        using Variant = std::variant<
            CompleteValue, // Comp-time or static value => The captured value
            TypedName      // Run-time non-static value => Typed name of a runtime context member
        >;
        Variant value;
    };

    struct CapturedContext {
        std::unordered_map<std::string, esl::tiny_vector<CompleteType>> types;
        std::unordered_map<std::string, esl::tiny_vector<Capture>>      values;
    };

    struct ResolvedCapturedContext {
        std::unordered_map<std::string, esl::tiny_vector<CompleteType>>    types;
        std::unordered_map<std::string, esl::tiny_vector<ResolvedCapture>> values;
    };

}
