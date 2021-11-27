#pragma once

#include "util/general.hpp"

namespace Cynth {

    namespace Detail::General {

        template <typename Arg>
        constexpr decltype(auto) comp (Arg && arg) {
            return std::forward<Arg>(arg);
        }

        template <typename Arg, typename First, typename... Rest>
        constexpr decltype(auto) comp (Arg && arg, First && first, Rest &&... rest) {
            return comp(first(std::forward<Arg>(arg)), std::forward<Rest>(rest)...);
        }

        template <typename Arg, typename... Fs>
        constexpr decltype(auto) compTuple (Arg && arg, std::tuple<Fs...> const & fs) {
            return Util::multiApply(comp<Arg &&, Fs...>, std::forward_as_tuple(std::forward<Arg>(arg)), fs);
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
    struct Composition {
        Tuple<Fs...> fs;

        constexpr Composition (Composition const &) = default;
        constexpr Composition (Composition &&)      = default;

        // At least two functions:
        template <typename First, typename Second, typename... Rest>
        constexpr Composition (First && first, Second && second, Rest &&... rest):
            //fs{std::forward_as_tuple (
            fs{std::make_tuple (
                (std::forward<First>(first)),
                (std::forward<Second>(second)),
                (std::forward<Rest>(rest))...
            )} {}

        // One function - cannot be confused with a copy/move constructor:
        template <typename F> requires (!Util::sameTemplate<std::remove_cvref_t<F>, Composition>)
        constexpr Composition (F && f):
            //fs{std::forward_as_tuple (
            fs{std::make_tuple (
                (std::forward<F>(f))
            )} {}

        template <typename... Ts>
        constexpr auto operator () (Ts &&... args) const {
            return Detail::General::compTuple(Util::headTie(fs)(std::forward<Ts>(args)...), Util::tailTie(fs));
        }
    };

    template <typename First, typename Second, typename... Rest>
    Composition(First &&, Second &&, Rest &&...) -> Composition<std::remove_cvref_t<First>, std::remove_cvref_t<Second>, std::remove_cvref_t<Rest>...>;
    template <typename F> requires (!Util::sameTemplate<F, Composition>)
    Composition(F &&) -> Composition<std::remove_cvref_t<F>>;

    template <typename... Fs>
    constexpr auto compose (Fs &&... fs) {
        return Composition{std::forward<Fs>(fs)...};
    }

    template <typename... Fs>
    using Composed = decltype(compose(std::declval<Fs>()...));

}
