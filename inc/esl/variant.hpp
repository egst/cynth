#pragma once

#include "esl/concepts.hpp"
#include "esl/type_manip.hpp"

#include <variant>
#include <concepts>
#include <type_traits>
#include <utility>
#include <memory>

namespace esl {

    template <typename T, typename V>
    constexpr esl::match_constness<V, T> * getNullable (V & v) {
        return std::holds_alternative<T>(v)
            ? std::addressof(std::get<T>(v))
            : nullptr;
    }

    namespace detail::variant {

        template <typename, typename>
        inline constexpr bool element = false;

        template <template <typename...> typename C, typename T, typename... Ts>
        inline constexpr bool element<T, C<Ts...>> = (std::same_as<T, Ts> || ...);

        template <typename, typename>
        inline constexpr bool subset = false;

        template <template <typename...> typename C, typename... Ts, typename... Us>
        inline constexpr bool subset<C<Ts...>, C<Us...>> = (element<Ts, C<Us...>> && ...);

    }

    /** Item containable in the variant.
        e.g. variant_member<item, variant>
        or   variant_member<variant> item */
    template <typename T, typename Variant>
    concept variant_member = detail::variant::element<std::remove_cvref_t<T>, Variant>;

    /** First variant containable in the other.
        e.g. compatible_variant<source, target>
        or   compatible_variant<target> source */
    template <typename T, typename U>
    concept compatible_variant = detail::variant::subset<T, U> || detail::variant::subset<typename T::variant, U>;

    /** Category containable in the variant.
        e.g. compatible_category<target_variant, source_category>
        or   compatible_category<target_variant> source_category */
    /*template <typename Category, typename Variant>
    concept compatible_category = category::interface<Category> && compatible_variant<decltype(Category::node), Variant>;*/

    template <typename To, compatible_variant<To> From>
    constexpr To variant_cast (From && source) {
        return std::visit([] <typename T> (T && val) -> To { return {esl::forward_like<From>(val)}; }, std::forward<From>(source));
    }

}
