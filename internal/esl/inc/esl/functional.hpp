#pragma once

#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

#include "esl/concepts.hpp"
#include "esl/result.hpp"
#include "esl/tuple.hpp"
#include "esl/type_manip.hpp"

namespace esl {

    template <typename F>
    struct functor_type {
        template <std::same_as<F> T>
        constexpr functor_type (T && f): function{std::forward<T>(f)} {}

        template <typename... Args>
        constexpr decltype(auto) operator () (Args &&... args) const {
            return function(std::forward<Args>(args)...);
        }

    private:
        esl::lref_or_val<F> function;
    };

    template <typename F> functor_type(F &&) -> functor_type<F>;

    template <typename F> requires (std::is_class_v<std::remove_reference_t<F>>)
    constexpr F && functor (F && f) {
        return std::forward<F>(f);
    }

    template <typename F>
    constexpr functor_type<F> functor (F && f) {
        return {std::forward<F>(f)};
    }

    /** Overload set from lambda functions. */
    template <typename... Fs>
    struct overload_type: Fs... {
        using Fs::operator()...;
    };
    template <typename... Fs> overload_type(Fs...) -> overload_type<Fs...>;

    template <typename... Fs>
    constexpr auto overload (Fs &&... fs) {
        return overload_type{esl::functor(std::forward<Fs>(fs))...};
    }

    template <typename... Fs>
    using overloaded = decltype(esl::overload(std::declval<Fs>()...));

    template <typename F>
    constexpr auto flip (F && f) {
        return [fun = esl::functor(f)] <typename A, typename B> (A && a, B && b) -> decltype(auto) {
            return fun(std::forward<A>(a))(std::forward<B>(b));
        };
    }

    template <typename F>
    constexpr auto flip_bin (F && f) {
        return [fun = esl::functor(f)] <typename A, typename B> (A && a, B && b) -> decltype(auto) {
            return fun(std::forward<A>(a), std::forward<B>(b));
        };
    }

    template <typename F>
    constexpr auto curry (F && f) {
        return [fun = esl::functor(f)] <typename A> (A && a) -> decltype(auto) {
            return [a = esl::hold(std::forward<A>(a)), fun = esl::forward_like<F>(fun)] <typename B> (B && b)
            -> decltype(auto) {
                return fun(esl::forward_like<A>(*a), std::forward<B>(b));
            };
        };
    }

    template <typename F>
    constexpr auto curry_flip (F && f) {
        return flip(curry(std::forward<F>(f)));
    }

    // Note: Flip and curry are nice to use, but I'm not sure if they bring some overhead.
    // Usually even this kind of crazy lambda nesting and such gets optimized away completely
    // (with the -O2 setting currently used) but I haven't tested these exact functions yet.
    // Anyways, it'll probably be better to use std::bind or the following two functions.

    template <typename F, typename T>
    constexpr auto bind_first (F && f, T && arg) {
        using namespace std::placeholders;
        return std::bind(std::forward<F>(f), std::forward<T>(arg), _2);
    }

    template <typename F, typename T>
    constexpr auto bind_second (F && f, T && arg) {
        using namespace std::placeholders;
        return std::bind(std::forward<F>(f), _1, std::forward<T>(arg));
    }

    namespace detail::functional {

        template <typename Arg>
        constexpr decltype(auto) comp (Arg && arg) {
            return std::forward<Arg>(arg);
        }

        template <typename Arg, typename First, typename... Rest>
        constexpr decltype(auto) comp (Arg && arg, First && first, Rest &&... rest) {
            return comp(first(std::forward<Arg>(arg)), std::forward<Rest>(rest)...);
        }

        template <typename Arg, typename... Fs>
        constexpr decltype(auto) comp_tuple (Arg && arg, std::tuple<Fs...> const & fs) {
            return esl::multi_apply(comp<Arg &&, Fs...>, std::forward_as_tuple(std::forward<Arg>(arg)), fs);
        }

        template <typename F>
        constexpr auto wrap (F && f) {
            return [f = std::forward<F>(f)] <typename... Args> (Args... args) {
                return f(std::forward<Args>(args)...);
            };
        }

    }

    /** Compose multiple functions. */
    template <typename... Fs>
    struct composition_type {
        std::tuple<Fs...> fs;

        constexpr composition_type (composition_type const &) = default;
        constexpr composition_type (composition_type &&)      = default;

        // At least two functions:
        template <typename First, typename Second, typename... Rest>
        constexpr composition_type (First && first, Second && second, Rest &&... rest):
            //fs{std::forward_as_tuple (
            fs{std::make_tuple (
                (std::forward<First>(first)),
                (std::forward<Second>(second)),
                (std::forward<Rest>(rest))...
            )} {}

        // One function - cannot be confused with a copy/move constructor:
        template <typename F> requires (!esl::same_template<std::remove_cvref_t<F>, composition_type>)
        constexpr composition_type (F && f):
            //fs{std::forward_as_tuple (
            fs{std::make_tuple (
                (std::forward<F>(f))
            )} {}

        template <typename... Ts>
        constexpr auto operator () (Ts &&... args) const {
            return detail::functional::comp_tuple(esl::head_tie(fs)(std::forward<Ts>(args)...), esl::tail_tie(fs));
        }
    };

    template <typename First, typename Second, typename... Rest>
    composition_type(First &&, Second &&, Rest &&...) -> composition_type<std::remove_cvref_t<First>, std::remove_cvref_t<Second>, std::remove_cvref_t<Rest>...>;
    template <typename F> requires (!esl::same_template<F, composition_type>)
    composition_type(F &&) -> composition_type<std::remove_cvref_t<F>>;

    template <typename... Fs>
    constexpr auto compose (Fs &&... fs) {
        return composition_type{std::forward<Fs>(fs)...};
    }

    template <typename... Fs>
    using composed = decltype(compose(std::declval<Fs>()...));

    namespace detail::functional {

        template <typename...> struct all_same_impl;

        template <typename Single>
        struct all_same_impl<Single> {
            constexpr static bool value = true;
        };

        template <typename First, typename Second, typename... Rest>
        struct all_same_impl<First, Second, Rest...> {
            constexpr static bool value = std::same_as<First, Second> && all_same_impl<Second, Rest...>::value;
        };

        template <typename... Ts>
        concept all_same = all_same_impl<Ts...>::value;

        template <typename F>
        using result_type = decltype(std::declval<F>()());

        template <typename...> struct same_result_type_impl;

        template <typename First, typename... Rest>
        requires (all_same<result_type<First>, result_type<Rest>...>)
        struct same_result_type_impl<First, Rest...> {
            using type = result_type<First>;
        };

        template <typename... Ts>
        using same_result_type = typename same_result_type_impl<Ts...>::type;

    }

    template <typename First, typename... Rest>
    constexpr auto chain_results (First && first, Rest &&... rest) {
        using result_type = detail::functional::same_result_type<First, Rest...>;
        result_type result = std::forward<First>(first)();
        ((
            !result.has_error() ? (
                result = std::forward<Rest>(rest)(),
                0
            ) : 0
        ), ...);
        return result;
    }

}
