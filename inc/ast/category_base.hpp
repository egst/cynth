#pragma once

#include "ast/category_interface.hpp"
#include "util/config.hpp"

#include <type_traits>
#include <concepts>
#include <utility>

namespace cynth::ast::category {

    namespace detail {

        template <typename T>
        concept temporary = std::is_rvalue_reference_v<T> || !std::is_reference_v<T>;

        template <typename, typename>
        inline constexpr bool element = false;

        template <template <typename...> typename C, typename T, typename... Ts>
        inline constexpr bool element<T, C<Ts...>> = (std::same_as<T, Ts> || ...);

        template <typename, typename>
        inline constexpr bool subset = false;

        template <template <typename...> typename C, typename... Ts, typename... Us>
        inline constexpr bool subset<C<Ts...>, C<Us...>> = (element<Ts, C<Us...>> && ...);

        /*template <typename, typename>
        struct is_variant_member;

        template <typename T, typename... Ts>
        struct is_variant_member<T, util::variant<Ts...>>: public std::disjunction<std::is_same<std::remove_cvref<T>, std::remove_cvref<Ts>>...> {};*/

        /*template <typename, typename>
        struct is_compatible_variant;

        template <typename... Ts, typename... Us>
        struct is_compatible_variant<util::variant<Ts...>, util::variant<Us...>>: public std::disjunction<std::is_same<std::remove_cvref<Us>, std::remove_cvref<Ts>>...> {};*/

        /** Item containable in the variant.
            e.g. variant_member<item, variant>
            or   variant_member<variant> item */
        template <typename T, typename Variant>
        concept variant_member = element<T, Variant>;

        /** First variant containable in the other.
            e.g. compatible_variant<source, target>
            or   compatible_variant<target> source */
        template <typename T, typename U>
        concept compatible_variant = subset<T, U>;

        /** Category containable in the variant.
            e.g. compatible_category<target_variant, source_category>
            or   compatible_category<target_variant> source_category */
        template <typename Category, typename Variant>
        concept compatible_category = category::interface<Category> && compatible_variant<decltype(Category::node), Variant>;

        template <typename To, compatible_variant<To> From> requires detail::temporary<From>
        To variant_cast (From && source) {
            return std::visit([] <detail::temporary T> (T && val) -> To { return {std::move(val)}; }, std::move(source));
        }

        /*template <typename To, compatible_variant<To> From>
        To variant_cast (From && source) {
            return std::visit([] <typename T> (T && val) -> To { return {val}; }, source);
        }*/

    }

    namespace detail {

        template <typename Derived, typename Variant>
        struct category_base {
            using derived = Derived;
            using variant = Variant;

            category_base () = delete;

            template <detail::variant_member<variant> T> requires detail::temporary<T>
            category_base (T && other):
                node{std::move(other)} {}

            template <detail::variant_member<variant> T> requires detail::temporary<T>
            Derived & operator = (T && other) {
                node = std::move(other);
                return *static_cast<derived *>(this);
            }

            template <detail::compatible_category<variant> T>
            category_base (T && other):
                node{detail::variant_cast<variant>(std::move(other.node))} {}

            template <detail::compatible_category<variant> T> requires detail::temporary<T>
            Derived & operator = (T && other) {
                std::visit([this] <detail::temporary U> (U && val) { node = std::move(val); }, std::move(other.node));
                return *static_cast<derived *>(this);
            }

            variant node;
        };

    }

}
