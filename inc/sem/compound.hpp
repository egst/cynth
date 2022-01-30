#pragma once

#include <string>
#include <unordered_map>
#include <variant>

#include "esl/category.hpp"
#include "esl/tiny_vector.hpp"

#include "context/forward.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"
#include "sem/numeric_types.hpp"

// TODO: Maybe create the incomplete/complete pair for these declarations too?

namespace cynth::sem {

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
        CompleteType  type;
        std::string   expression;
        bool          values = false; // Assigning to array values.
        //sem::Integral size; // The previous solution for array value assignments.
        // I don't really like this way of dealing with array value assignments, but for now it's the simplest approach.
    };

#if 0
    /***
    # runtime Bool x, Int y
    if (true) return y; # returning a run-time value always => .always = true
    if (x)    return y; # returning a run-time value, depending on a runtime value => .always = false
    ***/
    struct ReturnedType {
        bool always;
        CompleteType type;
    };

    /***
    # runtime Bool x
    if (true) return 1; # returning a compile-time value always => .always = true
    if (x)    return 1; # returning a compile-time value, depending on a runtime value => .always = false
    ***/
    struct ReturnedValue {
        bool always;
        CompleteValue value;
    };
#endif

    template <typename T>
    //using ReturnVector = std::vector<T>;
    using ReturnVector = esl::tiny_vector<T>; // Optimized for single-return blocks.

    using ReturnedValues = ReturnVector<CompleteValue>;

    namespace detail::compound {

        // Invariant: ReturnVector<...> alternative contains all same types
        // Invariant: ReturnVector<...> alternative is always non-empty.
        // (TODO: Enforce this statically.)
        using ReturnedVariant = std::variant<
            ReturnedValues, // comp-time
            CompleteType    // run-time
        >;

    }

    struct Returned: esl::category<Returned, detail::compound::ReturnedVariant> {
        using base = esl::category<Returned, detail::compound::ReturnedVariant>;
        using base::base;
    };

    struct Return {
        esl::tiny_vector<Returned> returned;
        bool always;

        static Return makeVoid (bool always = false) {
            return {
                .returned = {},
                .always   = always
            };
        }
    };

    namespace detail::compound {

        using VariableVariant = std::variant<
            CompleteValue, // Value known at compile time
            TypedName      // Corresponding runtime C variable
        >;

    }

    struct Variable: esl::category<Variable, detail::compound::VariableVariant> {
        using base = esl::category<Variable, detail::compound::VariableVariant>;
        using base::base;
    };

    namespace detail::compound {

        using ResolvedValueVariant = std::variant<
            CompleteValue,  // Value known at compile time
            TypedExpression // C expression
        >;

    }

    struct ResolvedValue: esl::category<ResolvedValue, detail::compound::ResolvedValueVariant> {
        using base = esl::category<ResolvedValue, detail::compound::ResolvedValueVariant>;
        using base::base;
    };

    namespace detail::compound {

        // TODO: Maybe it should be a reference (or a reference_wrapper) instead of a pointer?
        // For now, let's assume a non-empty vector here to be an invariant.
        using ResolvedTargetVariant = std::variant<
            CompleteValue *,      // Compconst variable only available at compile time
            TypedTargetExpression // C variable name or other lvalue expression
        >;

    }

    struct ResolvedTarget: esl::category<ResolvedTarget, detail::compound::ResolvedTargetVariant> {
        using base = esl::category<ResolvedTarget, detail::compound::ResolvedTargetVariant>;
        using base::base;
    };

    /*
    namespace detail::compound {

        using CaptureVariant = std::variant<
            CompleteValue, // Comp-time or static value => Capture the value
            CompleteType   // Run-time non-static value => Capture the type only
        >;

    }

    struct Capture: esl::category<Capture, detail::compound::CaptureVariant> {
        using base = esl::category<Capture, detail::compound::CaptureVariant>;
        using base::base;
    };
    */

    namespace detail::compound {

        using ResolvedCaptureVariant = std::variant<
            CompleteValue, // Comp-time or static value => The captured value
            TypedName      // Run-time non-static value => Typed name of a runtime context member
        >;

    }

    struct ResolvedCapture: esl::category<ResolvedCapture, detail::compound::ResolvedCaptureVariant> {
        using base = esl::category<ResolvedCapture, detail::compound::ResolvedCaptureVariant>;
        using base::base;
    };

    template <typename T>
    using CaptureVector = esl::tiny_vector<T>;

    struct Closure {
        using TypeMap       = std::unordered_map<std::string, CaptureVector<CompleteType>>;
        using ValueMap      = std::unordered_map<std::string, CaptureVector<ResolvedCapture>>;
        //using UnresolvedMap = std::unordered_map<std::string, CaptureVector<Capture>>; // TODO: Might be not needed.

        TypeMap  types;
        ValueMap values;
    };

}
