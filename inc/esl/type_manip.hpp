#pragma once

#include <type_traits>
#include <utility>

namespace esl {

    template <typename T, typename First, typename... Rest>
    constexpr decltype(auto) first_of (First && first, Rest &&... rest) {
        if constexpr (std::same_as<First, T>)
            return std::forward<First>(first);
        else
            return first_of<T>(std::forward<Rest>(rest)...);
    }

    template <typename Ref>
    struct arrow_proxy {
        using value_type = Ref;

        value_type * operator -> () {
            return &ref;
        }

    private:
        value_type ref;
    };

    template <typename T>
    using lref_or_val = std::conditional_t<
        std::is_lvalue_reference_v<T>,
        T,                         // Keep lvalue references.
        std::remove_reference_t<T> // Remove rvalue references (and keep direct values untouched).
    >;

    template <typename T>
    struct holder {
        using value_type      = esl::lref_or_val<T>;
        using reference       = std::add_lvalue_reference_t<value_type>;
        using const_reference = std::add_lvalue_reference_t<std::add_const_t<value_type>>;
        using pointer         = esl::arrow_proxy<value_type>;
        using const_pointer   = esl::arrow_proxy<std::add_const_t<value_type>>;

        template <std::same_as<T> U>
        constexpr holder (U && value): value_{std::forward<T>(value)} {}

        const_reference value       () const { return value_; }
        reference       value       ()       { return value_; }
        const_reference operator *  () const { return value(); }
        reference       operator *  ()       { return value(); }
        const_pointer   operator -> () const { return {value()}; }
        pointer         operator -> ()       { return {value()}; }

    protected:
        value_type value_;
    };

    template <typename T> holder(T &&) -> holder<T>;

    template <typename T>
    constexpr holder<T> hold (T && value) {
        return {std::forward<T>(value)};
    }

    /** Add/remove any kind of reference to mimic another type. */
    template <typename T, typename U>
    using match_reference = std::conditional_t <
        std::is_reference_v<T>,
        std::conditional_t <
            std::is_rvalue_reference_v<T>,
            std::add_rvalue_reference_t<std::remove_reference_t<U>>,
            std::add_lvalue_reference_t<std::remove_reference_t<U>>
        >,
        std::remove_reference_t<U>
    >;

    /** Add/remove const to mimic another type. */
    template <typename T, typename U>
    using match_constness = std::conditional_t <
        std::is_const_v<std::remove_reference_t<T>>,
        // Remove reference, match constness, then add the reference back:
        esl::match_reference<U, std::add_const_t<std::remove_reference_t<U>>>,
        std::remove_const_t<U>
    >;

    /** Add/remove const and any kind of reference to mimic another type. TODO: volatile */
    template <typename T, typename U>
    using match_cvref = esl::match_reference<T, esl::match_constness<T, U>>;

    /** std::forward based on a different type. */
    template <typename T, typename U>
    constexpr decltype(auto) forward_like (U && x) {
        return std::forward<esl::match_cvref<T, U>>(x);
    }

    /**
     *  Cast constness away.
     *  Useful with std::as_const to avoid code duplication in const/non-const method overloads.
     */
    template <typename T>
    constexpr T & as_nonconst (T const & value) {
        return const_cast<T &>(value);
    }
    /*template <typename T>
    constexpr T * as_nonconst (T const * value) noexcept {
        return const_cast<T *>(value);
    }*/
    /*template <typename T>
    constexpr T & as_nonconst (T & value) noexcept {
        return value;
    }*/
    /*template <typename T>
    constexpr T * as_nonconst (T * value) noexcept {
        return value;
    }*/
    template <typename T>
    void as_nonconst (T const &&) = delete;

    namespace detail::type_manip {

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

        template <typename, typename...> struct replace;

        template <template <typename...> typename Tpl, typename... From, typename... To>
        struct replace<Tpl<From...>, To...> {
            using type = Tpl<To...>;
        };

    }

    /** Concatenate template parameters of any type template (of the form template <typename...>). */
    template <typename... Ts>
    using concat = typename detail::type_manip::concat<Ts...>::type;

    /** Add more template parameters to any type template (of the form template <typename...>). */
    template <typename T, typename... More>
    using extend = typename detail::type_manip::extend<T, More...>::type;

    /** Replace all template parameters of any type template (of the form template <typename...>). */
    template <typename T, typename... By>
    using replace = typename detail::type_manip::replace<std::remove_cvref_t<T>, By...>::type;

    namespace detail::type_manip {

        template <typename First, typename... Rest>
        struct last {
            using type = typename last<Rest...>::type;
        };

        template <typename T>
        struct last<T> {
            using type = T;
        };

        template <typename, typename> struct append;

        template <typename T, typename... Ts>
        struct append<std::tuple<Ts...>, T> {
            using type = std::tuple<Ts..., T>;
        };

        template <typename Tup, typename First, typename... Rest>
        struct drop_last {
            using type = typename drop_last<typename append<Tup, First>::type, Rest...>::type;
        };

        template <typename Tup, typename Last>
        struct drop_last<Tup, Last> {
            using type = Tup;
        };

    }

    template <typename... Ts>
    using last = typename detail::type_manip::last<Ts...>::type;

    template <typename... Ts>
    using drop_last = typename detail::type_manip::drop_last<Ts...>::type;

}
