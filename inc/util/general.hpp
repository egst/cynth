#pragma once

#include "util/config.hpp"

#include <string>
#include <optional>
#include <variant>
#include <vector>
#include <type_traits>
#include <concepts>
#include <utility>

namespace cynth::util {

    /** Overload set from lambda functions. */
    template <typename... Fs> struct overload: Fs... { using Fs::operator()...; };
    template <typename... Fs> overload(Fs...) -> overload<Fs...>;

    namespace detail {

        template <typename, typename...> struct concat;
        template <template <typename...> typename T, typename... First, typename... Second, typename... Rest>
        struct concat<T<First...>, T<Second...>, Rest...> {
            using type = typename concat<T<First..., Second...>, Rest...>::type;
        };
        template <template <typename...> typename T, typename... First, typename... Rest>
        struct concat<T<First...>, T<Rest...>> {
            using type = T<First..., Rest...>;
        };
        template <typename, typename...> struct extend;
        template <template <typename...> typename T, typename... First, typename... Rest>
        struct extend<T<First...>, Rest...> {
            using type = T<First..., Rest...>;
        };

    }

    /** Concatenate template parameters of any variadic type template. */
    template <typename... Ts>
    using concat = typename detail::concat<Ts...>::type;
    /** Add more template parameters to any variadic type template. */
    template <typename T, typename... More>
    using extend = typename detail::extend<T, More...>::type;

    /** A standard range. */
    template <typename T>
    concept range = requires (T range) { *range.begin(); *range.end(); ++range.begin(); };
    /** A standard range with the .size() method. */
    template <typename T>
    concept sized_range = range<T> && requires (T range) { range.size(); };

    /** Get value type of any range. */
    template <range T>
    using range_value_type = std::remove_reference_t<decltype(*std::declval<T>().begin())>;

    /** A range containing a specific type. */
    template <typename T, typename U>
    concept range_of = range<T> && std::convertible_to<range_value_type<T>, U>;
    /** A sized range containing a specific type. */
    template <typename T, typename U>
    concept sized_range_of = sized_range<T> && std::convertible_to<range_value_type<T>, U>;

    /** A range containing a type constrained by the given type trait. */
    template <typename T, template <typename> typename Constraint>
    concept constrained_range = range<T> && Constraint<range_value_type<T>>::value;
    /** A sized range containing a type constrained by the given type trait. */
    template <typename T, template <typename> typename Constraint>
    concept constrained_sized_range = sized_range<T> && Constraint<range_value_type<T>>::value;

    /** A standard range with the .push_back() method. */
    template <typename T>
    concept push_back_range = range<T> && requires (T target, range_value_type<T> const & ref, range_value_type<T> && tmp) {
        target.push_back(ref);
        target.push_back(tmp);
    };

    /** Dereference the optional if it has_value() or keep the raw fallback otherwise.
        For short-circuit behavior use the unary overload of this function. */
    template <typename T, std::convertible_to<T> U>
    constexpr T coalesce (std::optional<T> opt, U fallback) {
        return opt.has_value()
            ? *opt
            : fallback;
    }

    /** Intended use: `util::coalesce(opt ?: fallback)`
        The `opt ?: fallback` expression returns `opt` only when it has_value() and `fallback` otherwise.
        This function then dereferences the optional or leaves the raw value. */
    template <typename T>
    constexpr T coalesce (std::optional<T> opt) {
        return *opt;
    }
    template <typename T>
    constexpr T coalesce (T fallback) {
        return fallback;
    }

    /** vector::push_back in a free function for convenience is some specific cases. */
    template <push_back_range T>
    T & push_back (range_value_type<T> const & value, T & target) {
        target.push_back(value);
        return target;
    }
    template <push_back_range T>
    T push_back (range_value_type<T> const & value, T && target) {
        target.push_back(value);
        return std::move(target);
    }
    template <push_back_range T>
    T & push_back (range_value_type<T> && value, T & target) {
        target.push_back(std::move(value));
        return target;
    }
    template <push_back_range T>
    T push_back (range_value_type<T> && value, T && target) {
        target.push_back(std::move(value));
        return std::move(target);
    }

}
