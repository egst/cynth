#pragma once

#include <utility>

namespace cynth::ast::node {

    namespace detail {

        template <typename T> //requires std::copy_constructible<T>
        struct component_base {

            constexpr component_base ():
                ptr{nullptr} {}

            // Copy-construct from a reference.
            constexpr component_base (T const & val):
                ptr{new T{val}} {}

            constexpr component_base & operator = (T const & val) {
                reset(new T{val});
                return *this;
            }

            // Move-construct from a temporary reference.
            constexpr component_base (T && val):
                ptr{new T{std::move(val)}} {}

            constexpr component_base & operator = (T && val) {
                reset(new T{std::move(val)});
                return *this;
            }

            // Copy-construct from a reference.
            constexpr component_base (component_base const & other):
                ptr{new T{*other.ptr}} {}

            constexpr component_base & operator = (component_base const & other) {
                reset(new T{*other.ptr});
                return *this;
            }

            // Move-construct and take ownership from a temporary reference.
            // The original component loses its pointer value and can no longer manage the underlying object.
            constexpr component_base (component_base && other):
                ptr{other.ptr} {
                other.ptr = nullptr;
            }

            constexpr component_base & operator = (component_base && other) {
                reset(other.ptr);
                other.release();
            }

            /** Release the allocated memory. */
            constexpr ~ component_base () {
                if (ptr) delete ptr;
            }

            /** Release the underlying object ownership. */
            constexpr void release () {
                ptr = nullptr;
            }

            /** Free the allocated memory and set a new pointer value. */
            constexpr void reset (T * other_ptr = nullptr) {
                if (ptr) delete ptr;
                ptr = other_ptr;
            }

            constexpr T & get () {
                return *ptr;
            }

            constexpr T const & get () const {
                return *ptr;
            }

            constexpr operator T &       ()       { return get(); }
            constexpr operator T const & () const { return get(); }

        protected:
            T * ptr;
        };

    }

    template <typename> struct optional_component;

    template <typename T>
    struct component: detail::component_base<T> {
        using base = detail::component_base<T>;
        using base::base;
        using base::operator=;

        /** A component cannot be constructed from an optional component. */
        constexpr component (optional_component<T> const &) = delete;
        constexpr component (optional_component<T> &&)      = delete;

        /** A component cannot be assigned from an optional component. */
        constexpr component & operator = (optional_component<T> const &) = delete;
        constexpr component & operator = (optional_component<T> &&)      = delete;

        // Copy and move constructors and assignment operators must be inherited manually.

        constexpr component & operator = (component<T> const & other) { base::operator=(other);            };
        constexpr component & operator = (component<T> &&      other) { base::operator=(std::move(other)); };

        constexpr component (component<T> const & other): base{other} {}
        constexpr component (component<T> &&      other): base{other} {}

        /** A component may be reinterpreted as an optional component. */
        // TODO: Test this.
        constexpr operator optional_component<T> const & () const { return *static_cast<optional_component<T> const *>(this); }
        constexpr operator optional_component<T> &       ()       { return *static_cast<optional_component<T>       *>(this); }
    };

    // TODO: Maybe not needed anymore.
    template <typename T> component(T const &) -> component<T>;

    template <typename T>
    struct optional_component: detail::component_base<T> {
        using base = detail::component_base<T>;
        using base::base;
        using base::operator=;
        using base::ptr;

        // Copy and move constructors and assignment operators must be inherited manually.

        constexpr optional_component & operator = (optional_component<T> const & other) { base::operator=(other);            };
        constexpr optional_component & operator = (optional_component<T> &&      other) { base::operator=(std::move(other)); };

        constexpr optional_component (optional_component<T> const & other): base{other} {}
        constexpr optional_component (optional_component<T> &&      other): base{other} {}

        /** An optional component is default-constructible to represent a missing component. */
        constexpr optional_component (): base{} {};

        constexpr bool has_value () const {
            return ptr;
        }
    };

    // TODO: Maybe not needed anymore.
    template <typename T> optional_component(T const &) -> optional_component<T>;

}
