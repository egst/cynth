#pragma once

#include <concepts>
#include <utility>
#include <tuple>

#include "esl/functional.hpp"
#include "esl/lift.hpp"
#include "esl/tuple.hpp"

/***
// overload:
[] (A) {} | [] (B) {}                                     // overload([] (A) {}, [] (B) {})

// compose:
[] (A) {} & [] (B) {}                                     // compose([] (A) {}, [] (B) {})

// call:
a >>= [] (A) {}                                           // ([] (A) {})(a)
args{a, b} >>= [] (A, B) {}                               // ([] (A, B) {})(a, b)

// nested lift:
target::a{} && [] (A) {}                                  // lift<target::a>([] (A) {})
target::a{} && target::b{}                                // nested_target<target::a, target::b>{}
nested_target<target::a, target::b>{} && [] (A) {}        // lift<target::a, target::b>([] (A) {})
target::a{} && target::b{} && [] (A) {}                   // lift<target::a, target::b>([] (A) {})

// n-ary lift:
target::a{} || [] (A) {}                                  // lift_nary<target::a>([] (A) {})
target::a{} || target::b{}                                // nary_target<target::a, target::b>{}
nary_target<target::a, target::b>{} & [] (A, B) {}        // lift_nary<target::a, target::b>([] (A, B) {})
target::a{} || target::b{} || [] (A, B) {}                // lift_nary<target::a, target::b>([] (A, B) {})
target::a{} && target::b{} || target::c{} || [] (A, B) {} // lift_nary<nested_target<target::a, target::b>, target::c>([] (A, B) {})

// examples:

value >>
target::component{} | target::category{} |
[] (value::Bool const &) -> string {
    return "bool";
} ||
[] (value::Int const &) -> string {
    return "int";
} ||
[] (auto const &) -> string {
    return "other";
};

args{value, type} >>=
target::component{} && target::category{} || target::category &&
[] (value::Bool const &, type::Bool const &) -> string {
    return "bool, bool";
} |
[] (value::Int const &, type::Float const &) -> string {
    return "int, float";
} |
[] (auto const &, auto const &) -> string {
    return "other";
};
***/

/**
 *  Use this namespace explicitly to enable all the crazy syntax sugar.
 *  The provided operators are sometimes very useful to write deeply nested visitor applications to branch over variants.
 *  However, to minimize any risk of unnecessary polution of the user's code with possibly conflicting operators,
 *  this feature requires explicit opt-in - `using namespace esl::sugar`.
 */
namespace esl::sugar {

    namespace detail {

        template <typename F, typename... Fs>
        concept composable = requires (F && f, Fs &&... fs) {
            esl::compose(std::forward<F>(f), std::forward<Fs>(fs)...);
        };

        template <typename F, typename... Fs>
        concept overloadable = requires (F && f, Fs &&... fs) {
            esl::overload(std::forward<F>(f), std::forward<Fs>(fs)...);
        };

        template <typename F>
        concept callable = overloadable<F>;

        template <typename T>
        concept targetable = requires () {
            { T::tag } -> std::same_as<esl::lift_target_tag const>;
        };

    }

    template <typename F, detail::overloadable<F> G>
    constexpr auto operator | (F && f, G && g) {
        return esl::overload(f, g);
    }

    template <typename F, detail::composable<F> G>
    constexpr auto operator & (F && f, G && g) {
        return esl::compose(f, g);
    }

    template <detail::targetable T, detail::targetable U>
    constexpr auto operator && (T &&, U &&) {
        return esl::target::nested<T, U>{};
    }

    template <detail::targetable T, typename F>
    constexpr auto operator && (T &&, F && f) {
        return esl::lift_nested<T>(std::forward<F>(f));
    }

    template <typename... Ts, typename F>
    constexpr auto operator && (esl::target::nested<Ts...> &&, F && f) {
        return esl::lift_nested<Ts...>(std::forward<F>(f));
    }

    template <detail::targetable T, detail::targetable U>
    constexpr auto operator || (T &&, U &&) {
        return esl::target::nary<T, U>{};
    }

    template <detail::targetable T, typename F>
    constexpr auto operator || (T &&, F && f) {
        return esl::lift_nary<T>(std::forward<F>(f));
    }

    template <typename... Ts, typename F>
    constexpr auto operator || (esl::target::nary<Ts...> &&, F && f) {
        return esl::lift_nary<Ts...>(std::forward<F>(f));
    }

    template <typename T, detail::callable F>
    constexpr auto operator >>= (T && arg, F && f) {
        return std::forward<F>(f)(std::forward<T>(arg));
    }

    template <typename... Ts>
    struct args: std::tuple<Ts...> {
        using base = std::tuple<Ts...>;
        using base::base;

        base &       tuple ()       { return *static_cast<base       *>(this); }
        base const & tuple () const { return *static_cast<base const *>(this); }
    };

    template <typename... Ts, typename F>
    constexpr auto operator >>= (esl::sugar::args<Ts...> const & args, F && f) {
        return esl::apply_forward(std::forward<F>(f), args.tuple());
    }

    template <typename... Ts, typename F>
    constexpr auto operator >>= (esl::sugar::args<Ts...> & args, F && f) {
        return esl::apply_forward(std::forward<F>(f), args.tuple());
    }

}
