#pragma once

#include "result.hpp"
#include "util/general.hpp"

#include <variant>
#include <string>
#include <concepts>

namespace cynth {

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
        util::scalar<typename lazy<T>::value_type> &&
        util::scalar<typename lazy<U>::value_type>
    bool operator && (lazy<T> const & first, lazy<U> const & second) {
        return first.eval() && second.eval();
    }

    /** Short circuit logical and overload for scalar cynth::result. */
    template <typename T, typename U>
    requires
        util::is     <typename lazy<T>::value_type, result> &&
        util::is     <typename lazy<U>::value_type, result> &&
        util::scalar <typename lazy<T>::value_type::value_type> &&
        util::scalar <typename lazy<U>::value_type::value_type>
    result<bool> operator && (lazy<T> const & first, lazy<U> const & second) {
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
        util::scalar<typename lazy<T>::value_type> &&
        util::scalar<typename lazy<U>::value_type>
    bool operator || (lazy<T> const & first, lazy<U> const & second) {
        return first.eval() || second.eval();
    }

    /** Short circuit logical or overload for cynth::result. */
    template <typename T, typename U>
    requires
        util::is     <typename lazy<T>::value_type, result> &&
        util::is     <typename lazy<U>::value_type, result> &&
        util::scalar <typename lazy<T>::value_type::value_type> &&
        util::scalar <typename lazy<U>::value_type::value_type>
    result<bool> operator || (lazy<T> const & first, lazy<U> const & second) {
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
