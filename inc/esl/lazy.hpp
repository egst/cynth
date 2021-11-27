#pragma once

#include "esl/concepts.hpp"
#include "esl/result.hpp"

#include <utility>

namespace esl {

    template <typename F>
    struct lazy {
        F fun;

        using value_type = decltype(std::declval<F>()());

        lazy (F const & fun): fun{fun} {}
        lazy (F && fun): fun{std::move(fun)} {}

        value_type eval () const {
            return fun();
        }

        operator value_type () const {
            return eval();
        }

    };

    /** Short circuit logical and for scalar types. */
    template <typename T, typename U>
    requires
        esl::scalar<typename lazy<T>::value_type> &&
        esl::scalar<typename lazy<U>::value_type>
    bool operator && (lazy<T> const & first, lazy<U> const & second) {
        return first.eval() && second.eval();
    }

    /** Short circuit logical and overload for scalar esl::result. */
    template <typename T, typename U>
    requires
        esl::same_template <typename lazy<T>::value_type, esl::result> &&
        esl::same_template <typename lazy<U>::value_type, esl::result> &&
        esl::scalar        <typename lazy<T>::value_type::value_type> &&
        esl::scalar        <typename lazy<U>::value_type::value_type>
    esl::result<bool> operator && (lazy<T> const & first, lazy<U> const & second) {
        auto first_result = first.eval();
        if (!first_result)
            return {first_result.error()};
        auto first_value = *first_result;
        if (!first_value)
            return {false};
        auto second_result = second.eval();
        if (!second_result)
            return {second_result.error()};
        auto second_value = *second_result;
        return {static_cast<bool>(second_value)};
    }

    /** Short circuit logical or for scalar types. */
    template <typename T, typename U>
    requires
        esl::scalar<typename lazy<T>::value_type> &&
        esl::scalar<typename lazy<U>::value_type>
    bool operator || (lazy<T> const & first, lazy<U> const & second) {
        return first.eval() || second.eval();
    }

    /** Short circuit logical or overload for esl::result. */
    template <typename T, typename U>
    requires
        esl::same_template <typename lazy<T>::value_type, esl::result> &&
        esl::same_template <typename lazy<U>::value_type, esl::result> &&
        esl::scalar        <typename lazy<T>::value_type::value_type> &&
        esl::scalar        <typename lazy<U>::value_type::value_type>
    esl::result<bool> operator || (lazy<T> const & first, lazy<U> const & second) {
        auto first_result = first.eval();
        if (!first_result)
            return {first_result.error()};
        auto first_value = *first_result;
        if (first_value)
            return {true};
        auto second_result = second.eval();
        if (!second_result)
            return {second_result.error()};
        auto second_value = *second_result;
        return {static_cast<bool>(second_value)};
    }

}
