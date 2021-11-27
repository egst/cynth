#pragma once

#include <concepts>
#include <type_traits>

namespace esl {

    template <typename T, typename U>
    concept same_but_cvref = std::same_as<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;

    template <typename T>
    concept scalar = std::is_scalar_v<T>;

    /** Is possibly a temporary value - is an rvalue reference or a direct value. */
    template <typename T>
    concept temporary = std::is_rvalue_reference_v<T> || !std::is_reference_v<T>;

    namespace detail::concepts {

        template <typename, typename>
        struct matching_template: std::false_type {};

        template <template <typename...> typename T, typename... Ts, typename... Us>
        struct matching_template<T<Ts...>, T<Us...>>: std::true_type {};

    }

    /** matchingTemplate<Vector<int>, Vector<float>> */
    template <typename T, typename U>
    concept matching_template = detail::concepts::matching_template<std::remove_cvref_t<T>, std::remove_cvref_t<U>>::value;

    /** same_template<Vector<int>, Vector> */
    template <typename T, template <typename...> typename Tpl>
    concept same_template = matching_template<T, Tpl<void>>;

    namespace detail::concepts {

        template <typename...> struct some_same_as;

        template <typename T, typename U, typename... Us>
        struct some_same_as<T, U, Us...> {
            static constexpr bool value = std::same_as<T, U> || some_same_as<T, Us...>::value;
        };

        template <typename T, typename U>
        struct some_same_as<T, U> {
            static constexpr bool value = std::same_as<T, U>;
        };

        template <typename T>
        struct some_same_as<T> {
            static constexpr bool value = false;
        };

    }

    /** At least one type is the same. */
    template <typename T, typename... Ts>
    concept some_same_as = detail::concepts::some_same_as<T, Ts...>::value;

    /** None of the types are the same. */
    template <typename T, typename... Ts>
    concept none_same_as = !some_same_as<T, Ts...>;

    namespace detail::concepts {

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
    concept variant_member = detail::concepts::element<std::remove_cvref_t<T>, Variant>;

    /** First variant containable in the other.
        e.g. compatible_variant<source, target>
        or   compatible_variant<target> source */
    template <typename T, typename U>
    concept compatible_variant = detail::concepts::subset<T, U> || detail::concepts::subset<typename T::variant, U>;

}
