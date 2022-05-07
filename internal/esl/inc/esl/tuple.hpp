#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

#include "esl/concepts.hpp"

namespace esl {

    //// TUPLE ////

    /**
     *  Equivalent of std::get for tuples with forwarding (std::froward) of the result regardless of the tuple reference type.
     *  e.g. the first type of tuple<T &&> & remains T && even though the whole tuple is an lvalue.
     */
    template <std::size_t I, esl::same_template<std::tuple> T>
    constexpr decltype(auto) get_forward (T && t) {
        return std::forward<std::tuple_element_t<I, std::remove_reference_t<T>>>(std::get<I>(std::forward<T>(t)));
    }

    namespace detail::tuple {

        template <typename F, typename T, std::size_t... IS>
        constexpr decltype(auto) apply_forward (F && f, T && t, std::index_sequence<IS...>) {
            return std::invoke(std::forward<F>(f), esl::get_forward<IS>(std::forward<T>(t))...);
        }

    }

    /**
     *  Equivalent of std::apply that forwards references inside of the tuple,
     *  See esl::get_forward.
     */
    template <typename F, typename T>
    constexpr decltype(auto) apply_forward (F && f, T && t) {
        return detail::tuple::apply_forward (
            std::forward<F>(f),
            std::forward<T>(t),
            std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<T>>>{}
        );
    }

    namespace detail::tuple {

        template <std::size_t SIZE, typename... Ts>
        consteval auto make_indices () {
            constexpr std::size_t sizes [] = {std::tuple_size_v<std::remove_reference_t<Ts>>...};
            using arr_t = std::array<std::size_t, SIZE>;
            std::pair<arr_t, arr_t> ret{};
            for (std::size_t c = 0, i = 0; i < sizeof...(Ts); ++i) for (std::size_t j = 0; j < sizes[i]; ++j, ++c) {
                ret.first[c] = i;
                ret.second[c] = j;
            }
            return ret;
        }

        template <bool FORWARD, typename F, typename... Tuples, std::size_t... OUTER_IS, std::size_t... INNER_IS>
        constexpr decltype(auto) multi_apply_impl2 (std::index_sequence<OUTER_IS...>, std::index_sequence<INNER_IS...>, F && f, std::tuple<Tuples...> && t) {
            if constexpr (FORWARD)
                return std::invoke(std::forward<F>(f), esl::get_forward<INNER_IS>(esl::get_forward<OUTER_IS>(std::move(t)))...);
            else
                return std::invoke(std::forward<F>(f), std::get<INNER_IS>(std::get<OUTER_IS>(std::move(t)))...);
        }

        template <bool FORWARD, typename F, typename... Tuples, std::size_t... IS>
        constexpr decltype(auto) multi_apply_impl1 (std::index_sequence<IS...>, F && f, std::tuple<Tuples...> && t) {
            constexpr auto indices = make_indices<sizeof...(IS), Tuples...>();
            return multi_apply_impl2<FORWARD>(std::index_sequence<indices.first[IS]...>{}, std::index_sequence<indices.second[IS]...>{}, std::forward<F>(f), std::move(t));
        }

        template <bool FORWARD, typename F, typename... Tuples>
        constexpr decltype(auto) multi_apply_impl (F && f, Tuples &&... ts) {
            constexpr std::size_t flatSize = (std::size_t{0} + ... + std::tuple_size_v<std::remove_reference_t<Tuples>>);
            if constexpr (flatSize != 0)
                return multi_apply_impl1<FORWARD>(std::make_index_sequence<flatSize>{}, std::forward<F>(f), std::forward_as_tuple(std::forward<Tuples>(ts)...));
            else
                return std::forward<F>(f)();
        }

    }

    /**
     *  Taken from https://newbedev.com/applying-multiple-tuples-to-the-same-function-i-e-apply-f-tuples-without-recursion-or-tuple-cat
     *  along with the implementation details above.
     *  Equivalent of std::apply extended to accept multiple tuples.
     *  This takes care of possible copy/move problems that would arise when using the standard std::apply with std::tuple_cat instead.
     */
    template <typename F, typename... Tuples>
    constexpr decltype(auto) multi_apply_forward (F && f, Tuples &&... ts) {
        return detail::tuple::multi_apply_impl<true>(std::forward<F>(f), std::forward<Tuples>(ts)...);
    }

    /** Equivalent of esl::multi_apply with forwarding of the tuple items (esl::get_forward). */
    template <typename F, typename... Tuples>
    constexpr decltype(auto) multi_apply (F && f, Tuples &&... ts) {
        return detail::tuple::multi_apply_impl<false>(std::forward<F>(f), std::forward<Tuples>(ts)...);
    }

    namespace detail::tuple {

        template <typename First, typename... Rest>
        constexpr decltype(auto) head_forward (First && first, Rest &&...) {
            return std::forward<First>(first);
        }

        template <typename First, typename... Rest>
        constexpr auto tail_forward (First &&, Rest &&... rest) {
            return std::forward_as_tuple(std::forward<Rest>(rest)...);
        }

        template <typename First, typename... Rest>
        constexpr auto const & head_tie_const (First const & first, Rest &...) {
            return first;
        }

        template <typename First, typename... Rest>
        constexpr auto & head_tie (First & first, Rest &...) {
            return first;
        }

        template <typename First, typename... Rest>
        constexpr auto tail_tie (First &, Rest &... rest) {
            return std::tie(rest...);
        }

    }

    /** Tuple head with forwarding (std::forward). */
    template <typename... Ts>
    constexpr decltype(auto) head_forward (std::tuple<Ts...> const & t) {
        return esl::apply_forward(detail::tuple::head_forward<Ts...>, t);
        //return esl::get_forward<0>(t);
    }

    /** Tuple tail with forwarding (std::forward). */
    template <typename... Ts>
    constexpr auto tail_forward (std::tuple<Ts...> const & t) {
        return esl::apply_forward(detail::tuple::tail_forward<Ts...>, t);
    }

    /** Tuple head by reference. (similar to std::tie) */
    template <typename... Ts>
    constexpr auto const & head_tie (std::tuple<Ts...> const & t) {
        return std::apply(detail::tuple::head_tie_const<std::add_const_t<Ts>...>, t);
        //return std::get<0>(t);
    }

    template <typename... Ts>
    constexpr auto & head_tie (std::tuple<Ts...> & t) {
        return std::apply(detail::tuple::head_tie<Ts...>, t);
        //return std::get<0>(t);
    }

    /** Tuple tail by reference. (similar to std::tie) */
    template <typename... Ts>
    constexpr auto tail_tie (std::tuple<Ts...> const & t) {
        return std::apply(detail::tuple::tail_tie<std::add_const_t<Ts>...>, t);
    }

    template <typename... Ts>
    constexpr auto tail_tie (std::tuple<Ts...> & t) {
        return std::apply(detail::tuple::tail_tie<Ts...>, t);
    }

    /** std::tie from an existing tuple. */
    template <typename... Ts>
    constexpr auto tie (std::tuple<Ts...> & t) {
        return esl::apply_forward(std::tie<Ts...>, t);
    }

    template <typename... Ts>
    constexpr auto tie (std::tuple<Ts...> const & t) {
        return esl::apply_forward(std::tie<std::add_const_t<Ts>...>, t);
    }

}
