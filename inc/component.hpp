#pragma once

#include "config.hpp"
#include "util/debug.hpp"

#include <cstddef>
//#include <array>
#include <utility>
#include <memory>

namespace cynth {

    template <typename T>
    struct component_deleter {
        void operator () (T * ptr) const;
    };

    template <typename T>
    struct component_allocator {
        // TODO: What if a type is non-copyable?
        T * operator () (T const & ptr) const;
        T * operator () (T &&      ptr) const;
    };

    namespace detail {

        template <typename Derived, typename T> //requires std::copy_constructible<T>
        struct component_base {
            using pointer_type = T *;
            using value_type   = T;

            constexpr component_base ():
                ptr{nullptr} {
                util::dout << "component{}\n";
            }

            // Copy-construct from a reference.
            constexpr component_base (T const & val):
                ptr{component_allocator<T>{}(val)} {
                util::dout << "component{ref val}\n";
            }

            constexpr Derived & operator = (T const & val) {
                reset(component_allocator<T>{}(val));
                util::dout << "component = ref val\n";
                return derived();
            }

            // Move-construct from a temporary reference.
            constexpr component_base (T && val):
                ptr{component_allocator<T>{}(std::move(val))} {
                util::dout << "component{tmp val}\n";
            }

            constexpr Derived & operator = (T && val) {
                reset(component_allocator<T>{}(std::move(val)));
                util::dout << "component = tmp val\n";
                return derived();
            }

            // Move-construct and take ownership from a temporary reference.
            // The original component loses its pointer value and can no longer manage the underlying object.
            component_base (component_base && other):
                ptr{other.get()} {
                other.ptr = nullptr;
                util::dout << "component{tmp component}\n";
            }

            Derived & operator = (component_base && other) {
                reset(other.get());
                other.release();
                util::dout << "component = tmp component\n";
                return derived();
            }

            // Copy-construct ("clone") from a reference.
            // The original component remains the opwner of the underlying object.
            // The new component is an owner of a newly allocated object.
            component_base (component_base const & other):
                ptr{other.get() ? component_allocator<T>{}(other.value()) : nullptr} {
                util::dout << "component{component}\n";
            }

            Derived & operator = (component_base const & other) {
                reset(other.get() ? component_allocator<T>{}(other.value()) : nullptr);
                util::dout << "component = component\n";
                return derived();
            }

            /** Free the allocated memory. */
            ~component_base () {
                component_deleter<T>{}(ptr);
                util::dout << "~component\n";
            }

            /** Release the underlying object ownership. */
            constexpr T * release () {
                T * copy = ptr;
                ptr = nullptr;
                return copy;
            }

            /** Free the allocated memory and set a new pointer value. */
            void reset (T * other_ptr = nullptr) {
                component_deleter<T>{}(ptr);
                ptr = other_ptr;
            }

            constexpr T const & value () const & {
                return *ptr;
            }

            constexpr T & value () & {
                return *ptr;
            }

            constexpr T && value () && {
                return *ptr;
            }

            constexpr T * get () {
                return ptr;
            }

            constexpr T const * get () const {
                return ptr;
            }

            constexpr T &       operator *  () &       { return value(); }
            constexpr T const & operator *  () const & { return value(); }
            // TODO: Look more into move-related rules and stuff and decide whether this is the way it should be done, and whether I even need this:
            constexpr T &&      operator *  () &&      { return std::move(value()); }
            constexpr T *       operator -> ()         { return get(); }
            constexpr T const * operator -> () const   { return get(); }

        private:
            constexpr Derived & derived () {
                return *static_cast<Derived *>(this);
            }

            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }

        protected:
            pointer_type ptr;
        };

    }

    template <typename> struct optional_component;

    template <typename T>
    struct component: detail::component_base<component<T>, T> {
        using base = detail::component_base<component<T>, T>;
        using base::base;
        using base::operator=;

        /** A component cannot be default constructed. */
        constexpr component () = delete;

        /** A component cannot be constructed from an optional component. */
        constexpr component (optional_component<T> const &) = delete;
        constexpr component (optional_component<T> &&)      = delete;

        /** A component cannot be assigned from an optional component. */
        constexpr component & operator = (optional_component<T> const &) = delete;
        constexpr component & operator = (optional_component<T> &&)      = delete;

        /** A component cannot be copied. */
        /*constexpr component              (component const &) = delete;
        constexpr component & operator = (component const &) = delete;*/
        // It can now.

        // Copy and move constructors and assignment operators must be inherited manually.

        constexpr component & operator = (component &&      other) { return base::operator=(std::move(other)); };
        constexpr component & operator = (component const & other) { return base::operator=(other); };

        constexpr component (component &&      other): base{std::move(other)} {}
        constexpr component (component const & other): base{other} {}

        /** A component may be implicitly converted to the undelying type. */
        /*constexpr operator T &       ()       { return value(); }
        constexpr operator T const & () const { return value(); }*/
        // Nope, I don't like this.
    };

    template <typename T>
    struct optional_component: detail::component_base<optional_component<T>, T> {
        using base = detail::component_base<optional_component<T>, T>;
        using base::base;
        using base::operator=;
        using base::get;
        using base::value;

        // Copy and move constructors and assignment operators must be inherited manually.

        /* An optional component cannot be copied. */
        /*constexpr optional_component              (optional_component const &) = delete;
        constexpr optional_component & operator = (optional_component const &) = delete;*/
        // Nope, it can now.

        // Copy and move constructors and assignment operators must be inherited manually.

        constexpr optional_component & operator = (optional_component &&      other) { return base::operator=(std::move(other)); };
        constexpr optional_component & operator = (optional_component const & other) { return base::operator=(other); };

        constexpr optional_component (optional_component &&      other): base{std::move(other)} {}
        constexpr optional_component (optional_component const & other): base{other} {}

        /** An optional component is default-constructible to represent a missing component. */
        constexpr optional_component (): base{} {};

        constexpr bool has_value () const { return get(); }

        /** An optional component may not be implicitly converted to the undelying type.
            Instead it has a boolean conversion to signify the presence of a value. */
        constexpr operator bool () const { return has_value(); }

        constexpr T value_or (T const & fallback) const {
            return has_value()
                ? value()
                : fallback;
        }
    };

    constexpr auto make_component = [] <typename T> (T && value) {
        return component<std::remove_reference_t<T>>{std::forward<T>(value)};
    };

    namespace detail {

        template <typename V, typename T>
        concept compatible_vector =
            (util::is<V, std::vector> || util::is<V, tuple_vector>) &&
            std::convertible_to<typename std::remove_cvref_t<V>::value_type, T> &&
            std::convertible_to<T, typename std::remove_cvref_t<V>::value_type>;

    }

    template <typename T>
    struct component_vector: std::vector<T> {
        using base = std::vector<T>;

        //using base::base;
        //using base::operator=;
        using base::push_back;
        using base::reserve;
        using base::size;

        using typename base::value_type;
        // TODO: Other typedefs.

        // TODO: Ensure that the constructors and assignments that are not valid for this use-case cannot be called.

        /*constexpr component_vector              (component_vector const &) = delete;
        constexpr component_vector & operator = (component_vector const &) = delete;*/

        constexpr component_vector (component_vector &&      other): base{std::move(other)} {}
        constexpr component_vector (component_vector const & other): base{other} {}
        //component_vector (component_vector &&      other);
        //component_vector (component_vector const & other);

        constexpr component_vector & operator = (component_vector &&      other) { base::operator=(std::move(other)); return *this; }
        constexpr component_vector & operator = (component_vector const & other) { base::operator=(other);            return *this; }
        //component_vector & operator = (component_vector &&      other);
        //component_vector & operator = (component_vector const & other);

        //~component_vector ();

        // std::initializer_list doesn't support move semantics.
        template <std::same_as<T>... U>
        constexpr component_vector (U &&... items): base{} {
            (push_back(std::forward<U>(items)), ...);
        }

        /** Construct from a compatible vector type. */
        template <detail::compatible_vector<T> V>
        constexpr component_vector (V && other) {
            reserve(other.size());
            for (auto & item : other)
                //push_back(component<T>{std::move(item)});
                //push_back(std::move(item));
                push_back(std::move(static_cast<T>(item)));
        }

        /** Convert to a compatible vector type. */
        template <detail::compatible_vector<T> V>
        constexpr operator V () const {
            V copy;
            copy.reserve(size());
            for (auto & item : *this)
                //copy.push_back(*item);
                //copy.push_back(item);
                copy.push_back(static_cast<typename V::value_type>(item));
            return copy;
        }
    };

    constexpr auto make_component_vector = [] <util::range T> (T && values) {
        using value_type = util::range_value_type<T>;
        return component_vector<value_type>{std::forward<T>(values)};
    };

    /*template <typename T, std::size_t SIZE>
    using component_array = std::array<component<T>, SIZE>;*/

}
