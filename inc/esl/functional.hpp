#pragma once

#include "esl/tuple.hpp"
#include "esl/concepts.hpp"

#include <utility>
#include <type_traits>
#include <tuple>

namespace esl {

    /** Overload set from lambda functions. */
    template <typename... Fs> struct overload_type: Fs... {
        using Fs::operator()...;
    };
    template <typename... Fs> overload_type(Fs...) -> overload_type<Fs...>;

    template <typename... Fs>
    constexpr auto overload (Fs &&... fs) {
        return overload_type{std::forward<Fs>(fs)...};
    }

    template <typename... Fs>
    using overloaded = decltype(esl::overload(std::declval<Fs>()...));

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

}
