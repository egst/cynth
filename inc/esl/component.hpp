#pragma once

#include <concepts>
#include <type_traits>
#include <utility>
#include <vector>

#include "esl/concepts.hpp"
#include "esl/debug.hpp"
#include "esl/lift.hpp"
#include "esl/ranges.hpp"
#include "esl/tiny_vector.hpp"

namespace esl {

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

    namespace detail::component {

        template <typename Derived, typename T> //requires std::copy_constructible<T>
        struct base {
            using pointer_type = T *;
            using value_type   = T;

            constexpr base ():
                ptr{nullptr} {
                esl::dout << "component{}\n";
            }

            // Copy-construct from a reference.
            constexpr base (T const & val):
                ptr{component_allocator<T>{}(val)} {
                esl::dout << "component{ref val}\n";
            }

            constexpr Derived & operator = (T const & val) {
                reset(component_allocator<T>{}(val));
                esl::dout << "component = ref val\n";
                return derived();
            }

            // Move-construct from a temporary reference.
            constexpr base (T && val):
                ptr{component_allocator<T>{}(std::move(val))} {
                esl::dout << "component{tmp val}\n";
            }

            constexpr Derived & operator = (T && val) {
                reset(component_allocator<T>{}(std::move(val)));
                esl::dout << "component = tmp val\n";
                return derived();
            }

            // Move-construct and take ownership from a temporary reference.
            // The original component loses its pointer value and can no longer manage the underlying object.
            base (base && other):
                ptr{other.get()} {
                other.ptr = nullptr;
                esl::dout << "component{tmp component}\n";
            }

            Derived & operator = (base && other) {
                reset(other.get());
                other.release();
                esl::dout << "component = tmp component\n";
                return derived();
            }

            // Copy-construct ("clone") from a reference.
            // The original component remains the opwner of the underlying object.
            // The new component is an owner of a newly allocated object.
            base (base const & other):
                ptr{other.get() ? component_allocator<T>{}(other.value()) : nullptr} {
                esl::dout << "component{component}\n";
            }

            Derived & operator = (base const & other) {
                reset(other.get() ? component_allocator<T>{}(other.value()) : nullptr);
                esl::dout << "component = component\n";
                return derived();
            }

            /** Free the allocated memory. */
            ~base () {
                component_deleter<T>{}(ptr);
                esl::dout << "~component\n";
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
            // TODO: Look more into move-related rules and stuff
            // and decide whether this is the way it should be done, and whether I even need this:
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
    struct component: detail::component::base<component<T>, T> {
        using base = detail::component::base<component<T>, T>;
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
    struct optional_component: detail::component::base<optional_component<T>, T> {
        using base = detail::component::base<optional_component<T>, T>;
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

        constexpr optional_component & operator = (optional_component && other) {
            return base::operator=(std::move(other));
        };
        constexpr optional_component & operator = (optional_component const & other) {
            return base::operator=(other);
        };

        constexpr optional_component (optional_component &&      other): base{std::move(other)} {}
        constexpr optional_component (optional_component const & other): base{other} {}

        /** An optional component is default-constructible to represent a missing component. */
        constexpr optional_component (): base{} {};

        constexpr bool has_value () const { return get(); }

        /** An optional component may not be implicitly converted to the undelying type.
            Instead it has a boolean conversion to signify the presence of a value. */
        constexpr explicit operator bool () const { return has_value(); }

        constexpr T value_or (T const & fallback) const {
            return has_value()
                ? value()
                : fallback;
        }
    };

    constexpr auto make_component = [] <typename T> (T && value) {
        return component<std::remove_reference_t<T>>{std::forward<T>(value)};
    };

    namespace detail::component {

        template <typename V, typename T/*, typename B*/>
        concept compatible_vector =
            //!std::derived_from<V, B> &&
            //!esl::matching_template<V, B> &&
            //TODO: Check if this isn't ambiguous without explicit "V is not a B (the component vector)"
            esl::reservable_range<V> && esl::back_pushable_range<V> &&
            std::convertible_to<esl::range_value_type<V>, T> &&
            std::convertible_to<T, typename esl::range_value_type<V>>;

        template <template <typename...> typename Base>
        struct vector_param {
            template <typename T>
            struct component_vector: Base<T> {
                using base = Base<T>;

                //using base::base;
                //using base::operator=;
                using base::push_back;
                using base::reserve;
                using base::size;

                using typename base::value_type;
                // TODO: Other typedefs.

                // TODO: Ensure that the constructors and assignments that are not valid for this use-case cannot be called.

                constexpr component_vector (): base{} {}

                /*constexpr component_vector              (component_vector const &) = delete;
                constexpr component_vector & operator = (component_vector const &) = delete;*/

                template <esl::same_but_cvref<T>... Ts> requires (sizeof...(Ts) > 1)
                constexpr component_vector (Ts &&... vals): base{std::forward<Ts>(vals)...} {}

                template <esl::same_but_cvref<T> U>
                constexpr component_vector (U && val): base(1, std::forward<U>(val)) {}

                constexpr component_vector (component_vector &&      other): base{std::move(other)} {}
                constexpr component_vector (component_vector const & other): base{other} {}
                //component_vector (component_vector &&      other);
                //component_vector (component_vector const & other);

                constexpr component_vector & operator = (component_vector && other) {
                    base::operator=(std::move(other));
                    return *this;
                }
                constexpr component_vector & operator = (component_vector const & other) {
                    base::operator=(other);
                    return *this;
                }
                //component_vector & operator = (component_vector &&      other);
                //component_vector & operator = (component_vector const & other);

                //~component_vector ();

                // std::initializer_list doesn't support move semantics.
                /*
                template <std::same_as<value_type>... U>
                constexpr component_vector (U &&... items): base{} {
                    (push_back(std::forward<U>(items)), ...);
                }
                */

                /** Construct from a compatible vector type. */
                //template <detail::component::compatible_vector<value_type> V>
                template <typename V>
                // TODO: This doesn't work as a constructor. (It requires a complete type.)
                constexpr static component_vector make (V && other) {
                    component_vector v;
                    v.reserve(other.size());
                    for (auto const & item: other)
                        //v.push_back(component<value_type>{std::move(item)});
                        //v.push_back(std::move(item));
                        v.push_back(std::move(static_cast<value_type>(item)));
                    return v;
                }

                /** Convert to a compatible vector type. */
                template <detail::component::compatible_vector<value_type> V>
                constexpr operator V () const {
                    V copy;
                    copy.reserve(size());
                    for (auto const & item: *this)
                        //copy.push_back(*item);
                        //copy.push_back(item);
                        copy.push_back(static_cast<typename V::value_type>(item));
                    return copy;
                }
            };
        };

    }

    template <typename T, template <typename...> typename Base>
    using basic_component_vector = typename detail::component::vector_param<Base>::template component_vector<T>;

    template <template <typename...> typename Base>
    constexpr auto make_basic_component_vector = [] <esl::range T> (T && values) {
        using value_type = std::remove_cvref_t<esl::range_value_type<T>>;
        //return basic_component_vector<value_type, Base>{std::forward<T>(values)};
        return basic_component_vector<value_type, Base>::make(std::forward<T>(values));
    };

    template <typename T> using component_vector      = basic_component_vector<T, std::vector>;
    template <typename T> using tiny_component_vector = basic_component_vector<T, esl::tiny_vector>;

    constexpr auto make_component_vector      = make_basic_component_vector<std::vector>;
    constexpr auto make_tiny_component_vector = make_basic_component_vector<esl::tiny_vector>;

    /*template <typename T, std::size_t SIZE>
    using component_array = std::array<component<T>, SIZE>;*/

    namespace detail::component {

        template <typename Derived, typename F>
        struct lift_component_impl {
            /** Operate on any number of components. */
            template <esl::same_template<esl::component>... Ts>
            constexpr decltype(auto) operator () (Ts &&... target) const {
                return derived().invoke(*std::forward<Ts>(target)...);
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename Derived, typename F>
        struct lift_optional_component_impl {
            /** Operate on a single optional component. Returns an optional. */
            template <esl::same_template<esl::optional_component> T>
            constexpr auto operator () (T && target) const {
                using result_type = decltype(derived().invoke(*std::forward<T>(target)));
                if (target)
                    return std::optional<result_type>{derived().invoke(*std::forward<T>(target))};
                else
                    return std::optional<result_type>{};
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        /*
        template <typename, template <typename, template <typename...> typename> typename>
        struct matching_template_impl: std::false_type {};

        template <
            template <typename, template <typename...> typename> typename T,
            typename U, template <typename...> typename V
        >
        struct matching_template_impl<T<U, V>, T>: std::true_type {};

        template <typename T, template <typename, template <typename...> typename> typename Tpl>
        concept matching_template = matching_template_impl<T, Tpl>::value;
        */

        template <template <typename...> typename C, bool TinyResult = false>
        struct lift_component_vector {
            template <typename Derived, typename F>
            struct impl {
                template <typename T>
                using vector_type = std::conditional_t<
                    TinyResult,
                    esl::tiny_vector<T>,
                    typename C<T>::base
                >;

                //template <matching_template<esl::basic_component_vector> T>
                template <esl::same_template<C> T>
                constexpr auto operator () (T && target) const {
                    return esl::lift_on_range<vector_type>(derived(), std::forward<T>(target));
                }
                template <esl::same_template<C> T, esl::same_template<C> U>
                constexpr auto operator () (T && first, U && second) const {
                    return esl::lift_on_range<vector_type>(derived(), std::forward<T>(first), std::forward<U>(second));
                }

            private:
                constexpr Derived const & derived () const {
                    return *static_cast<Derived const *>(this);
                }
            };
        };

    }

    namespace target {

        struct component                    { constexpr static lift_target_tag tag = {}; };
        struct optional_component           { constexpr static lift_target_tag tag = {}; };
        struct component_vector             { constexpr static lift_target_tag tag = {}; };
        struct tiny_component_vector        { constexpr static lift_target_tag tag = {}; };
        struct component_vector_tiny_result { constexpr static lift_target_tag tag = {}; };

    }

    template <> struct lift_specialization_map<target::component>:
        lift_implementation<esl::detail::component::lift_component_impl> {};

    template <> struct lift_specialization_map<target::optional_component>:
        lift_implementation<esl::detail::component::lift_optional_component_impl> {};

    template <> struct lift_specialization_map<target::component_vector>:
        lift_implementation<esl::detail::component::lift_component_vector<esl::component_vector>::impl> {};

    template <> struct lift_specialization_map<target::tiny_component_vector>:
        lift_implementation<esl::detail::component::lift_component_vector<esl::component_vector>::impl> {};

    template <> struct lift_specialization_map<target::component_vector_tiny_result>:
        lift_implementation<esl::detail::component::lift_component_vector<esl::component_vector, true>::impl> {};

}
