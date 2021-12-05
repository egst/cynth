#pragma once

#include <optional>
#include <string>
#include <forward_list>
//#include <utility>

#include "esl/result.hpp"
#include "esl/lift.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/containers.hpp"

#include "sem/forward.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"

namespace cynth::sem {

    using ValueVector      = esl::tiny_vector<CompleteValue>;
    using TypedValueVector = esl::tiny_vector<TypedValue>;
    using TargetVector     = esl::tiny_vector<CompleteValue *>;
    using TypeVector       = esl::tiny_vector<CompleteType>;

    template <typename T>
    using RefvalContainer = std::forward_list<T>;

    // TODO: There probably won't be cases of having both value and expression.
    // There might be cases of having neither one though.
    // So value and expression could be combined in optional<variant<value, string>>
    // Update: What about functions? They'll have a runtime C expression - the context struct
    // (probably just its name), as well as a compile time value - the C function name.
    struct TypedValue {
        CompleteType                 type;
        std::optional<CompleteValue> value;      // Compilation constant value.
        std::optional<std::string>   expression; // Translated C expression - usually a name.
    };

    // TODO: vector<struct{value *, type}> instead of struct{vector<value *>, vector<type>}
    struct TypedTargetValue {
        //TargetVector value;
        //TypeVector   type;
        CompleteValue * value;
        CompleteType    type;

        esl::result<void> assign (ValueVector && values) {
            // TODO
            /*
            return esl::lift<esl::target::tiny_vector>(
                [] (CompleteValue * target, CompleteValue && value) {
                    *target = std::move(value);
                }
            )(value, std::move(values));
            */
            return {};
        }
    };

    inline TargetVector makeTargetVector (ValueVector & values) {
        return esl::lift<esl::target::tiny_vector>(
            [] (CompleteValue & value) -> CompleteValue * { return &value; }
        )(values);
    }

    inline TargetVector makeTargetVector (CompleteValue & value) {
        return esl::init<esl::tiny_vector>(&value);
    }

    inline TypeVector makeTypeVector (CompleteType const & type) {
        return esl::init<esl::tiny_vector>(type);
    }

    inline ValueVector makeValueVector (CompleteValue const & value) {
        return esl::init<esl::tiny_vector>(value);
    }

}
