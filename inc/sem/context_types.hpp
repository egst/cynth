#pragma once

#include "config.hpp"
#include "sem/forward.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"
#include "lift.hpp"

#include <optional>
#include <string>
#include <forward_list>

namespace cynth::sem {

    // TODO: Move this to sem::
    using value_vector       = tuple_vector<value::complete>;
    using typed_value_vector = tuple_vector<typed_value>;
    using target_vector      = tuple_vector<value::complete *>;
    using type_vector        = tuple_vector<type::complete>;

    template <typename T>
    using refval_container = std::forward_list<T>;

    // TODO: There probably won't be cases of having both value and expression.
    // There might be cases of having neither one thouhg.
    // So value and expression could be combined in optional<variant<value, string>>
    struct typed_value {
        type::complete                 type;
        std::optional<value::complete> value;      // Compilation constant value.
        std::optional<std::string>     expression; // Translated C expression - usually a name.
    };

    // TODO: vector<struct{value *, type}> instead of struct{vector<value *>, vector<type>}
    struct typed_target_value {
        target_vector value;
        type_vector   type;

        result<void> assign (value_vector && values) {
            // TODO
            /*
            return lift::tuple_vector {
                [] (value::complete * target, value::complete && value) {
                    *target = std::move(value);
                }
            } (value, std::move(values));
            */
            return {};
        }
    };

    inline target_vector make_target_vector (value_vector & values) {
        return lift::tuple_vector {
            [] (value::complete & value) -> value::complete * { return &value; }
        } (values);
    }

    inline target_vector make_target_vector (value::complete & value) {
        return util::init<tuple_vector>(&value);
    }

    inline type_vector make_type_vector (type::complete const & type) {
        return util::init<tuple_vector>(type);
    }

    inline value_vector make_value_vector (value::complete const & value) {
        return util::init<tuple_vector>(value);
    }

    /*
    inline opt_value_vector make_opt_value_vector (value::complete const & value) {
        return util::init<tuple_vector>(std::make_optional(value));
    }

    inline opt_expr_vector make_opt_expr_vector (std::string const & expr) {
        return util::init<tuple_vector>(std::make_optional(expr));
    }
    */

}
