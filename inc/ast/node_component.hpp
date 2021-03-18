#pragma once

#include "util/config.hpp"

#include <cstddef>
//#include <array>
#include <utility>

namespace cynth::ast::node {

    namespace detail {

        template <typename T, template <typename> typename Derived> //requires std::copy_constructible<T>
        struct component_base {
            using derived = Derived<T>;

            constexpr component_base ():
                ptr{nullptr} {
                util::dout << "component{}\n";
            }

            // Copy-construct from a reference.
            constexpr component_base (T const & val):
                ptr{new T{val}} {
                util::dout << "component{ref val}\n";
            }

            constexpr derived & operator = (T const & val) {
                reset(new T{val});
                util::dout << "component = ref val\n";
                return *static_cast<derived *>(this);
            }

            // Move-construct from a temporary reference.
            constexpr component_base (T && val):
                ptr{new T{std::move(val)}} {
                util::dout << "component{tmp val}\n";
            }

            constexpr derived & operator = (T && val) {
                reset(new T{std::move(val)});
                util::dout << "component = tmp val\n";
                return *static_cast<derived *>(this);
            }

            // Move-construct and take ownership from a temporary reference.
            // The original component loses its pointer value and can no longer manage the underlying object.
            constexpr component_base (component_base && other):
                ptr{other.ptr} {
                other.ptr = nullptr;
                util::dout << "component{tmp component}\n";
            }

            constexpr derived & operator = (component_base && other) {
                reset(other.ptr);
                other.release();
                util::dout << "component = tmp component\n";
                return *static_cast<derived *>(this);
            }

            /** Release the allocated memory. */
            constexpr ~ component_base () {
                if (ptr) delete ptr;
                util::dout << "~component\n";
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

            constexpr T &       operator *  ()       { return get(); }
            constexpr T const & operator *  () const { return get(); }
            constexpr T *       operator -> ()       { return ptr;   }
            constexpr T const * operator -> () const { return ptr;   }

        protected:
            T * ptr;
        };

    }

    template <typename> struct optional_component;

    template <typename T>
    struct component: detail::component_base<T, component> {
        using base = detail::component_base<T, component>;
        using base::base;
        using base::operator=;
        using base::get;

        /** A component cannot be default constructed. */
        constexpr component () = delete;

        /** A component cannot be constructed from an optional component. */
        constexpr component (optional_component<T> const &) = delete;
        constexpr component (optional_component<T> &&)      = delete;

        /** A component cannot be assigned from an optional component. */
        constexpr component & operator = (optional_component<T> const &) = delete;
        constexpr component & operator = (optional_component<T> &&)      = delete;

        /** A component cannot be copied. */
        constexpr component              (component const &) = delete;
        constexpr component & operator = (component const &) = delete;

        // Copy and move constructors and assignment operators must be inherited manually.

        constexpr component & operator = (component && other) { return base::operator=(std::move(other)); };

        constexpr component (component && other): base{std::move(other)} {}

        /** A component may be implicitly converted to the undelying type. */
        constexpr operator T &       ()       { return get(); }
        constexpr operator T const & () const { return get(); }
    };

    template <typename T>
    struct optional_component: detail::component_base<T, optional_component> {
        using base = detail::component_base<T, optional_component>;
        using base::base;
        using base::operator=;
        using base::ptr;

        // Copy and move constructors and assignment operators must be inherited manually.

        /* An optional component cannot be copied. */
        constexpr optional_component              (optional_component const &) = delete;
        constexpr optional_component & operator = (optional_component const &) = delete;

        constexpr optional_component & operator = (optional_component && other) { return base::operator=(std::move(other)); };

        constexpr optional_component (optional_component && other): base{std::move(other)} {}

        /** An optional component is default-constructible to represent a missing component. */
        constexpr optional_component (): base{} {};

        constexpr bool has_value () const { return ptr; }

        /** An optional component may not be implicitly converted to the undelying type.
            Instead it has a boolean conversion to signify the presence of a value. */
        constexpr operator bool () const { return has_value(); }
    };

    template <typename T>
    struct component_vector: util::vector<component<T>> {
        using base = util::vector<component<T>>;
        //using base::base;
        //using base::operator=;
        using base::push_back;
        // TODO: Ensure that the constructors and assignments that are not valid for this use-case cannot be called.

        constexpr component_vector              (component_vector const &) = delete;
        constexpr component_vector & operator = (component_vector const &) = delete;

        constexpr component_vector (component_vector && other): base{std::move(other)} {}

        constexpr component_vector & operator = (component_vector && other) { base::operator=(std::move(other)); return *this; }

        // std::initializer_list doesn't support move semantics.
        template <std::same_as<T>... U>
        constexpr component_vector (U &&... items): base{} {
            (push_back(std::move(items)), ...);
        }
    };

    /*template <typename T, std::size_t SIZE>
    using component_array = std::array<component<T>, SIZE>;*/

}
