#pragma once

#include <string>
#include <unordered_map>
#include <variant>

#include "esl/category.hpp"
#include "esl/tiny_vector.hpp"

#include "context/forward.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"

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
        CompleteType type;
        std::string  expression;
    };

    struct ReturnedType {
        bool always;
        esl::tiny_vector<CompleteType> type;
    };

    struct ReturnedValue {
        esl::tiny_vector<CompleteValue> value;
    };

    namespace detail::compound {

        using ReturnedVariant = std::variant<
            std::monostate, // never
            ReturnedValue,  // returned
            ReturnedType    // maybe (sometimes | always)
        >;

    }

    using NoReturn = std::monostate;

    struct Returned: esl::category<Returned, detail::compound::ReturnedVariant> {
        using base = esl::category<Returned, detail::compound::ReturnedVariant>;
        using base::base;

        // TODO: This might not be needed.
        enum Kind: int {
            never,    // Never returns
            returned, // Returned a compile-time value
            maybe     // Might return a run-time value
        };
        constexpr Kind kind () const {
            return static_cast<Kind>(value.index());
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

    namespace detail::compound {

        using ResolvedCaptureVariant = std::variant<
            CompleteValue, // Comp-time or static value => The captured value
            TypedName      // Run-time non-static value => Typed name of a runtime context member
        >;

    };

    struct ResolvedCapture: esl::category<ResolvedCapture, detail::compound::ResolvedCaptureVariant> {
        using base = esl::category<ResolvedCapture, detail::compound::ResolvedCaptureVariant>;
        using base::base;
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
