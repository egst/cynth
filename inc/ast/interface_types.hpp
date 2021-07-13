#pragma once

#include "config.hpp"
#include "asg/declarations.hpp"
#include "asg/values.hpp"
#include "asg/types.hpp"
#include "util/general.hpp"
#include "util/container.hpp"

namespace cynth::ast {

    using display_result         = std::string;
    using execution_result       = optional_result<tuple_vector<asg::value::complete>>;
    using single_eval_result     = result<asg::value::complete>;
    using evaluation_result      = tuple_vector<single_eval_result>;
    using type_eval_result       = tuple_vector<result<asg::type::incomplete>>;
    using array_elem_eval_result = result<tuple_vector<asg::value::complete>>; // TODO
    using decl_eval_result       = tuple_vector<result<asg::incomplete_decl>>;

    template <util::is<result> T>
    constexpr auto make_single_eval_result (T && value) {
        return std::forward<T>(value);
    }

    template <util::is_not<result> T>
    constexpr auto make_single_eval_result (T && value) {
        return result<asg::value::complete>{std::forward<T>(value)};
    }

    template <util::is<result> T>
    constexpr auto make_evaluation_result (T && value) {
        return util::init<tuple_vector>(std::forward<T>(value));
    }

    template <util::is_not<result> T>
    constexpr auto make_evaluation_result (T && value) {
        return util::init<tuple_vector>(result<asg::value::complete>{std::forward<T>(value)});
    }

    template <util::is<result> T>
    constexpr auto make_type_eval_result (T && value) {
        return util::init<tuple_vector>(std::forward<T>(value));
    }

    template <util::is_not<result> T>
    constexpr auto make_type_eval_result (T && value) {
        return util::init<tuple_vector>(result<asg::type::incomplete>{std::forward<T>(value)});
    }

    template <typename T>
    constexpr auto make_array_elem_eval_result (T && value) {
        return array_elem_eval_result{std::forward<T>(value)};
    }

    template <util::is<result> T>
    constexpr auto make_decl_eval_result (T && value) {
        return util::init<tuple_vector>(std::forward<T>(value));
    }

    template <util::is_not<result> T>
    constexpr auto make_decl_eval_result (T && value) {
        return util::init<tuple_vector>(result<asg::incomplete_decl>{std::forward<T>(value)});
    }

    template <typename T> requires (!util::same_as_no_cvref<T, result_error>)
    constexpr auto make_execution_result (T && value) {
        return execution_result{util::init<tuple_vector>(std::forward<T>(value))};
    }

    template <util::same_as_no_cvref<result_error> T>
    constexpr auto make_execution_result (T && value) {
        return execution_result{std::forward<T>(value)};
    }

}
