#pragma once

#include "config.hpp"
#include "sem/context_types.hpp"
#include "sem/declarations.hpp"
#include "sem/values.hpp"
#include "sem/types.hpp"
#include "sem/targets.hpp"
#include "util/general.hpp"
#include "util/container.hpp"

#include <string>
#include <vector>

namespace cynth::ast {

    // TODO: Sort out the vector<result<T>> vs result<vector<T>> mess.
    using execution_result       = optional_result<tuple_vector<sem::complete_value>>;
    using single_eval_result     = result<sem::complete_value>;
    using evaluation_result      = tuple_vector<single_eval_result>;
    using type_eval_result       = tuple_vector<result<sem::type::incomplete>>;
    using array_elem_eval_result = result<tuple_vector<sem::complete_value>>; // TODO
    using decl_eval_result       = tuple_vector<result<sem::incomplete_decl>>;
    using range_decl_eval_result = tuple_vector<result<sem::incomplete_range_decl>>;
    using target_eval_result     = result<tuple_vector<sem::any_target>>;
    using translation_result     = tuple_vector<result<sem::typed_value>>;

    template <util::is<result> T>
    constexpr auto make_single_eval_result (T && value) {
        return std::forward<T>(value);
    }

    template <util::is_not<result> T>
    constexpr auto make_single_eval_result (T && value) {
        return result<sem::complete_value>{std::forward<T>(value)};
    }

    template <util::is<result> T>
    constexpr auto make_evaluation_result (T && value) {
        return util::init<tuple_vector>(std::forward<T>(value));
    }

    template <util::is_not<result> T>
    constexpr auto make_evaluation_result (T && value) {
        return util::init<tuple_vector>(result<sem::complete_value>{std::forward<T>(value)});
    }

    template <util::is<result> T>
    constexpr auto make_type_eval_result (T && value) {
        return util::init<tuple_vector>(std::forward<T>(value));
    }

    template <util::is_not<result> T>
    constexpr auto make_type_eval_result (T && value) {
        return util::init<tuple_vector>(result<sem::type::incomplete>{std::forward<T>(value)});
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
        return util::init<tuple_vector>(result<sem::incomplete_decl>{std::forward<T>(value)});
    }

    template <util::is<result> T>
    constexpr auto make_range_decl_eval_result (T && value) {
        return util::init<tuple_vector>(std::forward<T>(value));
    }

    template <util::is_not<result> T>
    constexpr auto make_range_decl_eval_result (T && value) {
        return util::init<tuple_vector>(result<sem::incomplete_range_decl>{std::forward<T>(value)});
    }

    template <typename T> requires (!util::same_as_no_cvref<T, result_error>)
    constexpr auto make_execution_result (T && value) {
        return execution_result{util::init<tuple_vector>(std::forward<T>(value))};
    }

    template <util::same_as_no_cvref<result_error> T>
    constexpr auto make_execution_result (T && value) {
        return execution_result{std::forward<T>(value)};
    }

    template <util::same_as_no_cvref<result_error> T>
    constexpr auto make_target_eval_result (T && value) {
        return target_eval_result{std::forward<T>(value)};
    }

    template <typename T> requires (!util::same_as_no_cvref<T, result_error>)
    constexpr auto make_target_eval_result (T && value) {
        return target_eval_result{util::init<tuple_vector>(std::forward<T>(value))};
    }

    template <typename T>
    constexpr auto make_translation_result (T && value) {
        return translation_result{std::forward<T>(value)};
    }

    template <util::is<result> T>
    constexpr auto make_translation_result (T && value) {
        return util::init<tuple_vector>(std::forward<T>(value));
    }

    template <util::is_not<result> T>
    constexpr auto make_translation_result (T && value) {
        return util::init<tuple_vector>(result<sem::typed_value>{std::forward<T>(value)});
    }

}
