#pragma once

#include <concepts>
#include <utility>

namespace esl {

    /**
     *  Dereference the optional if it has_value() or keep the raw fallback otherwise.
     *  For short-circuit behavior use the unary overload of this function.
     */
    template <typename T, std::convertible_to<T> U, template <typename...> typename O>
    constexpr T coalesce (O<T> const & opt, U && fallback) {
        return opt.has_value()
            ? *opt
            : std::forward<U>(fallback);
    }

    template <typename T, std::convertible_to<T> U, template <typename...> typename O>
    constexpr T coalesce (O<T> && opt, U && fallback) {
        return opt.has_value()
            ? *std::move(opt)
            : std::forward<U>(fallback);
    }

    /**
     *  Intended use: `esl::coalesce(opt ?: fallback)`
     *  The `opt ?: fallback` expression returns `opt` only when it has_value() and `fallback` otherwise.
     *  This function then dereferences the optional or leaves the raw value.
     */
    template <typename T, template <typename...> typename O>
    constexpr T coalesce (O<T> opt) {
        return *opt;
    }

    template <typename T>
    constexpr T coalesce (T fallback) {
        return fallback;
    }

}
