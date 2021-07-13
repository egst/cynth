#pragma once

#include <type_traits>
#include <concepts>
#include <utility>
#include <memory>

namespace cynth::util {

    namespace detail {

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
        using difference_type = std::conditional_t <
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
        using value_type = std::conditional_t <
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
        concept random_access = input<I> && distance<I> && advance<I>; // Equals, increment and decrement are not necessary.

        template <input I>
        using category = std::conditional_t <
            random_access<I>,
            std::random_access_iterator_tag,
            std::conditional_t <
                bidirectional<I>,
                std::bidirectional_iterator_tag,
                std::conditional_t <
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
            Equals, increment and decrement are not necessary.
    **/
    //template <detail::input Derived>
    template <typename Derived>
    struct iterator {

        decltype(auto) operator * () const /*requires detail::input<Derived>*/ {
            return derived().dereference();
        }

        auto operator -> () const /*requires detail::input<Derived>*/ {
            decltype(auto) ref = **this;
            if constexpr (std::is_reference_v<decltype(ref)>) {
                return std::addressof(ref);
            } else {
                return detail::arrow_proxy{std::move(ref)};
            }
        }

        friend bool operator == (Derived const & first, Derived const & second) /*requires detail::forward<Derived>*/ {
            if constexpr (detail::forward<Derived>)
                return first.equals(second);
            else
                return first.distance(second) == 0;
        };

        Derived & operator ++ () /*requires detail::forward<Derived>*/ {
            if constexpr (detail::random_access<Derived>) {
                derived().advance(1);
            } else {
                derived().increment();
            }
            return derived();
        }

        Derived operator ++ (int) /*requires detail::forward<Derived>*/ {
            auto copy = derived();
            ++*this;
            return copy;
        }

        Derived & operator -- () /*requires detail::bidirectional<Derived>*/ {
            if constexpr (detail::random_access<Derived>) {
                derived().advance(-1);
            } else {
                derived().decrement();
            }
            return derived();
        }

        Derived operator -- (int) /*requires detail::bidirectional<Derived>*/ {
            auto copy = derived();
            --*this;
            return copy;
        }

        friend auto operator <=> (Derived const & first, Derived const & second) /*requires detail::random_access<Derived>*/ {
            return (first - second) <=> 0;
        }

        Derived & operator += (detail::difference_type_param<Derived> auto offset) /*requires detail::random_access<Derived>*/ {
            derived().advance(offset);
            return derived();
        }

        Derived & operator -= (detail::difference_type_param<Derived> auto offset) /*requires detail::random_access<Derived>*/ {
            return *this += -offset;
        }

        friend Derived operator + (Derived iter, detail::difference_type_param<Derived> auto offset) /*requires detail::random_access<Derived>*/ {
            return iter += offset;
        }

        friend Derived operator + (detail::difference_type_param<Derived> auto offset, Derived iter) /*requires detail::random_access<Derived>*/ {
            return iter += offset;
        }

        friend Derived operator - (Derived iter, detail::difference_type_param<Derived> auto offset) /*requires detail::random_access<Derived>*/ {
            return iter -= offset;
        }

        friend Derived operator - (detail::difference_type_param<Derived> auto offset, Derived iter) /*requires detail::random_access<Derived>*/ {
            return iter -= offset;
        }

        decltype(auto) operator [] (detail::difference_type_param<Derived> auto offset) const /*requires detail::random_access<Derived>*/ {
            return *(*this + offset);
        }

        auto operator - (Derived other) const /*requires detail::random_access<Derived>*/ {
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

template <cynth::util::detail::input I> requires std::derived_from<I, cynth::util::iterator<I>>
struct std::iterator_traits<I> {

    using reference         = decltype(*std::declval<I>());
    using pointer           = decltype(std::declval<I>().operator->());
    using difference_type   = cynth::util::detail::difference_type<I>;
    using value_type        = cynth::util::detail::value_type<I>;
    using iterator_category = cynth::util::detail::category<I>;
    using iterator_concept  = iterator_category;

};
