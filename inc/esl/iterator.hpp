#pragma once

#include "esl/concepts.hpp"

#include <type_traits>
#include <concepts>
#include <utility>
#include <memory>
#include <iterator>

namespace esl {

    /** std::make_move_iterator or keep the same iterator - similar to std::forward<T>. */
    template <typename T, typename I>
    constexpr auto make_forwarding_iterator (I && i) {
        if constexpr (esl::temporary<T>)
            return std::make_move_iterator(i);
        else
            return i;
    }

    namespace detail::iterator {

        template <typename Ref>
        struct arrow_proxy {
            Ref * operator -> () {
                return &ref;
            }

        private:
            Ref ref;
        };

        template <typename I>
        concept dereference = requires (I const c) {
            c.dereference();
        };

        template <typename I>
        concept equals = requires (I const c) {
            c.equals(c);
        };

        template <typename I>
        concept increment = requires (I m) {
            m.increment();
        };

        template <typename I>
        concept decrement = requires (I m) {
            m.decrement();
        };

        template <typename I>
        concept distance = requires (I const c) {
            c.distance(c);
        };

        template <typename I>
        using difference_type = std::conditional_t<
            distance<I>,
            decltype(std::declval<I>().distance(std::declval<I>())),
            std::ptrdiff_t
        >;

        template <typename T, typename I>
        concept difference_type_param = std::convertible_to<T, difference_type<I>>;

        template <typename I>
        concept advance = requires (I const c, I m, difference_type<I> o) {
            m.advance(o);
        };

        template <typename I>
        concept custom_value_type = requires {
            typename I::value_type;
        };

        template <typename I>
        using value_type = std::conditional_t<
            custom_value_type<I>,
            typename I::value_type,
            std::remove_cvref_t<decltype(std::declval<I>().dereference())>
        >;

        template <typename I>
        concept input = dereference<I>;

        template <typename I>
        concept forward = input<I> && equals<I> && increment<I>;

        template <typename I>
        concept bidirectional = forward<I> && decrement<I>;

        template <typename I>
        concept random_access = input<I> && distance<I> && advance<I>; // equals, increment and decrement are not necessary.

        template <input I>
        using category = std::conditional_t<
            random_access<I>,
            std::random_access_iterator_tag,
            std::conditional_t<
                bidirectional<I>,
                std::bidirectional_iterator_tag,
                std::conditional_t<
                    forward<I>,
                    std::forward_iterator_tag,
                    std::input_iterator_tag
                >
            >
        >;

    }

    /**
        Inspired by https://vector-of-bool.github.io/2020/06/13/cpp20-iter-facade.html.

        Required implementation:
        * For an input iterator:
            reference dereference () const
        * For a forward iterator:
            bool equals (I const &) const
            void increment ()
        * For a bidirectional iterator:
            void decrement ()
        * For a random access iterator:
            difference_type distance (I const &) const
            void advance (difference_type)
            equals, increment and decrement are not necessary.
    **/
    template <typename Derived>
    struct iterator {

        decltype(auto) operator * () const {
            return derived().dereference();
        }

        auto operator -> () const {
            decltype(auto) ref = **this;
            if constexpr (std::is_reference_v<decltype(ref)>) {
                return std::addressof(ref);
            } else {
                return detail::iterator::arrow_proxy{std::move(ref)};
            }
        }

        friend bool operator == (Derived const & first, Derived const & second) {
            if constexpr (detail::iterator::forward<Derived>)
                return first.equals(second);
            else
                return first.distance(second) == 0;
        };

        Derived & operator ++ () {
            if constexpr (detail::iterator::random_access<Derived>) {
                derived().advance(1);
            } else {
                derived().increment();
            }
            return derived();
        }

        Derived operator ++ (int) {
            auto copy = derived();
            ++*this;
            return copy;
        }

        Derived & operator -- () {
            if constexpr (detail::iterator::random_access<Derived>) {
                derived().advance(-1);
            } else {
                derived().decrement();
            }
            return derived();
        }

        Derived operator -- (int) {
            auto copy = derived();
            --*this;
            return copy;
        }

        friend auto operator <=> (Derived const & first, Derived const & second) {
            return (first - second) <=> 0;
        }

        Derived & operator += (detail::iterator::difference_type_param<Derived> auto offset) {
            derived().advance(offset);
            return derived();
        }

        Derived & operator -= (detail::iterator::difference_type_param<Derived> auto offset) {
            return *this += -offset;
        }

        friend Derived operator + (Derived iter, detail::iterator::difference_type_param<Derived> auto offset) {
            return iter += offset;
        }

        friend Derived operator + (detail::iterator::difference_type_param<Derived> auto offset, Derived iter) {
            return iter += offset;
        }

        friend Derived operator - (Derived iter, detail::iterator::difference_type_param<Derived> auto offset) {
            return iter -= offset;
        }

        friend Derived operator - (detail::iterator::difference_type_param<Derived> auto offset, Derived iter) {
            return iter -= offset;
        }

        decltype(auto) operator [] (detail::iterator::difference_type_param<Derived> auto offset) const {
            return *(*this + offset);
        }

        auto operator - (Derived other) const {
            return derived().distance(other);
        }

    private:
        Derived & derived () {
            return *static_cast<Derived *>(this);
        }

        Derived const & derived () const {
            return *static_cast<Derived const *>(this);
        }
    };

}

template <esl::detail::iterator::input I> requires (std::derived_from<I, esl::iterator<I>>)
struct std::iterator_traits<I> {

    using reference         = decltype(*std::declval<I>());
    using pointer           = decltype(std::declval<I>().operator->());
    using difference_type   = esl::detail::iterator::difference_type<I>;
    using value_type        = esl::detail::iterator::value_type<I>;
    using iterator_category = esl::detail::iterator::category<I>;
    using iterator_concept  = iterator_category;

};
