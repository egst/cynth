#pragma once

#include <concepts>
#include <utility>
#include <tuple>

#include "esl/concepts.hpp"
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
[] (A) {} <<= a                                           // ([] (A) {})(a)
[] (A, B) {} <<= args{a, b}                               // ([] (A, B) {})(a, b)

// Note: I prefer `f <<= arg` over `arg >>= f` as it feels syntactically closer to f(arg)
// and also allows chaining with no parentheses:
// `f(g(arg))` vs `f <<= g <<= arg` vs `(arg >>= g) >>= f`
// So I might remove `>>=` later.

// lift:
[] (A) {} || target::a                                    // lift_nested<target::a>([] (A) {})

// nested lift:
[] (A) {} || target::nested{target::a, target::b}         // lift_nested<target::a, target::b>([] (A) {})

// nary lift:
[] (A) {} || target::nary{target::a, target::b}           // lift_nary<target::a, target::b>([] (A) {})

// Combined lift:
[] (A) {} || target::nary{target::nested{target::a, target::b}, target::c}

// examples:

[] (value::Bool const &) -> string {
    return "bool";
} | [] (value::Int const &) -> string {
    return "int";
} | [] (auto const &) -> string {
    return "other";
} || target::category{} <<= value

[] (value::Bool const &, type::Bool const &) -> string {
    return "bool, bool";
} | [] (value::Int const &, type::Float const &) -> string {
    return "int, float";
} | [] (auto const &, auto const &) -> string {
    return "other";
} || target::category{} <<= args(value, type)

auto fooResult = getFoo();
if (!fooResult) return fooResult.error();
auto foo = *fooResult;
// ...

[] (auto foo) {
    // ...
} || target::result{} <<= getFoo();
***/

/**
 *  Use this namespace explicitly to enable all the syntax sugar.
 *  The provided operators are sometimes very useful to write deeply nested visitor applications to branch over variants
 *  without excessive unreadable parentheses all over the place.
 *  However, some of these operators operate on any functions, rather than on some specific types.
 *  So to minimize any risk of unnecessary polution of the user's code with possibly conflicting operators,
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

    template <typename F, detail::targetable T>
    constexpr auto operator || (F && f, T && t) {
        return esl::lift_nested<T>(std::forward<F>(f));
    }

    template <typename F, detail::targetable... Ts>
    constexpr auto operator || (F && f, esl::target::nested<Ts...> &&) {
        return esl::lift_nested<Ts...>(std::forward<F>(f));
    }

    //template <typename F, detail::targetable... Ts>
    template <typename F, typename... Ts>
    constexpr auto operator || (F && f, esl::target::nary<Ts...> &&) {
        return esl::lift_nary<Ts...>(std::forward<F>(f));
    }

    template <typename... Ts>
    struct args_type: std::tuple<Ts...> {
        using base = std::tuple<Ts...>;
        using base::base;

        base &       tuple ()       { return *static_cast<base       *>(this); }
        base const & tuple () const { return *static_cast<base const *>(this); }
    };

    template <typename... Ts>
    args_type<Ts &&...> args (Ts &&... vals) {
        return {std::forward<Ts>(vals)...};
    }

    template <typename T, detail::callable F>
    constexpr auto operator >>= (T && arg, F && f) {
        return std::forward<F>(f)(std::forward<T>(arg));
    }

    template <typename... Ts, typename F>
    constexpr auto operator >>= (esl::sugar::args_type<Ts...> const & args, F && f) {
        return esl::apply_forward(std::forward<F>(f), args.tuple());
    }

    template <typename... Ts, typename F>
    constexpr auto operator >>= (esl::sugar::args_type<Ts...> & args, F && f) {
        return esl::apply_forward(std::forward<F>(f), args.tuple());
    }

    template <typename T, detail::callable F> requires (!esl::same_template<T, args_type>)
    constexpr auto operator <<= (F && f, T && arg) {
        return std::forward<F>(f)(std::forward<T>(arg));
    }

    template <typename... Ts, typename F>
    constexpr auto operator <<= (F && f, esl::sugar::args_type<Ts...> const & args) {
        return esl::apply_forward(std::forward<F>(f), args.tuple());
        //return std::apply(std::forward<F>(f), args.tuple());
    }

    template <typename... Ts, typename F>
    constexpr auto operator <<= (F && f, esl::sugar::args_type<Ts...> & args) {
        return esl::apply_forward(std::forward<F>(f), args.tuple());
        //return std::apply(std::forward<F>(f), args.tuple());
    }

}
