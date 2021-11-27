#pragma once

#include "esl/iterator.hpp"
#include "esl/zip.hpp"
#include "esl/ranges.hpp"
#include "esl/type_manip.hpp"
#include "esl/functional.hpp"
#include "esl/result.hpp"

#include <optional>
#include <variant>
#include <vector>
#include <string>
#include <type_traits>
#include <concepts>
#include <utility>
#include <algorithm>
#include <iterator>

namespace esl {

    template <template <typename...> typename> struct lift_specialization_map;

    template <template <typename, typename> typename S>
    struct lift_implementation {
        template <typename Derived, typename F>
        using tpl = S<Derived, F>;
    };

    template <template <typename...> typename Tag, typename Derived, typename F>
    using specialization = typename lift_specialization_map<Tag>::template tpl<Derived, F>;

    namespace detail::lift {

        // TODO: Deprecate detail::lift::lift.
        template <
            typename Derived,
            typename F,
            template <typename...> typename... Tags
        >
        struct base: esl::specialization<Tags, Derived, F>... {
            F fun;

            constexpr base (F &&      f): fun{std::move(f)} {}
            constexpr base (F const & f): fun{f}            {}

            /** Overload this method in the derived classes if needed. */
            template <typename...>
            constexpr auto const & function () const {
                return fun;
            }

            template <typename... Ts>
            constexpr decltype(auto) invoke (Ts &&... args) const {
                return derived().template function<Ts...>()(std::forward<Ts>(args)...);
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

    }

    // TODO: Some mess with nested results here or in the next overload below...
    /** A helper for lift implementations over ranges. */
    template <template <typename...> typename V, typename F, typename T>
    constexpr auto lift_on_range (F const & functor, T && target) {
        using value_type  = decltype(*esl::make_forwarding_iterator<T>(target.begin()));
        using result_type = decltype(functor.invoke(std::declval<value_type>()));
        if constexpr (std::same_as<result_type, void>) {
            for (auto && val : std::forward<T>(target))
                functor.invoke(std::forward<value_type>(val));
            return esl::result<void>{};
        } else {
            using vector = V<result_type>;
            vector result;
            if constexpr (esl::reservable_range<vector>)
                result.reserve(target.size());
            std::transform (
                esl::make_forwarding_iterator<T>(target.begin()),
                esl::make_forwarding_iterator<T>(target.end()),
                std::back_inserter(result),
                [&functor] (value_type v) {
                    return functor.invoke(std::forward<value_type>(v));
                }
            );
            return result;
        }
    }

    template <template <typename...> typename V, typename F, typename T, typename U>
    constexpr auto lift_on_range (F const & functor, T && first, U && second) {
        using first_type  = decltype(*esl::make_forwarding_iterator<T>(first.begin()));
        using second_type = decltype(*esl::make_forwarding_iterator<U>(second.begin()));
        using result_type = decltype(functor.invoke(std::declval<first_type>(), std::declval<second_type>()));
        using final_type  = std::conditional_t<std::same_as<result_type, void>, void, V<result_type>>;
        if (first.size() != second.size())
            return esl::result<final_type>{esl::result_error{
                "Binary tuple operation values count mismatch. -- " +
                std::to_string(first.size()) +
                " and " +
                std::to_string(second.size()) +
                "."
            }};
        if constexpr (std::same_as<result_type, void>) {
            for (auto && [a, b] : esl::zip(std::forward<T>(first), std::forward<U>(second)))
                functor.invoke(std::forward<first_type>(a), std::forward<second_type>(b));
            return esl::result<void>{};
        } else {
            using vector = final_type;
            vector result;
            if constexpr (esl::reservable_range<vector>)
                result.reserve(first.size());
            std::transform (
                esl::make_forwarding_iterator<T>(first.begin()),
                esl::make_forwarding_iterator<T>(first.end()),
                esl::make_forwarding_iterator<U>(second.begin()),
                std::back_inserter(result),
                [&functor] (first_type a, second_type b) {
                    return functor.invoke(std::forward<first_type>(a), std::forward<second_type>(b));
                }
            );
            return esl::result{result};
        }
    }

    namespace detail::lift {

        template <typename Derived, typename F>
        struct direct_impl {
            template <typename... Ts> requires /*std::invocable<F, Ts...>*/ std::invocable<F, Ts...>
            constexpr decltype(auto) operator () (Ts &&... args) const {
                return derived().fun(std::forward<Ts>(args)...); // Note: This ends any possible recursion.
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename Derived, typename F>
        struct sized_range_impl {
            template <typename T>
            using vector_type = std::vector<T>;

            template <esl::sized_range T>
            constexpr auto operator () (T && target) const {
                return esl::lift_on_range<vector_type>(derived(), std::forward<T>(target));
            }

            // TODO: This was limited for use on different container types only. Is it still relevant?
            template <esl::sized_range T, esl::sized_range U> //requires (!esl::same_template<T, U>)
            constexpr auto operator () (T && first, U && second) const {
                return esl::lift_on_range<vector_type>(derived(), std::forward<T>(first), std::forward<U>(second));
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename Derived, typename F>
        struct variant_impl {
            /** Operate on any number of variants. */
            template <esl::same_template<std::variant>... Ts>
            constexpr decltype(auto) operator () (Ts &&... target) const {
                return std::visit (
                    //derived().template function<>(), // Note: This ends a possible recursion.
                    [this] <typename... Us> (Us &&... value) { return derived().invoke(std::forward<Us>(value)...); },
                    std::forward<Ts>(target)...
                );
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename Result>
        static constexpr auto handle_one_error =
            [] (esl::result_error e) { return esl::result<Result>{e}; };

        template <typename First, typename Second, typename Result>
        static constexpr auto handle_two_errors = esl::overload(
            [] (esl::result_error   e, Second const &)      { return esl::result<Result>{e}; },
            [] (First const &,         esl::result_error e) { return esl::result<Result>{e}; },
            [] (esl::result_error   a, esl::result_error)   { return esl::result<Result>{a}; } // TODO: Combining multiple errors...
        );

        template <typename Derived, typename F>
        struct result_impl {
            /** Operate on a single result. */
            template <esl::same_template<esl::result> T>
            constexpr decltype(auto) operator () (T && target) const {
                using value_type  = typename std::remove_cvref_t<T>::value_type;
                using result_type = std::remove_cvref_t<decltype(derived().invoke(std::declval<value_type>()))>;

                if constexpr (esl::same_template<result_type, esl::result>) {
                    using nested_type = typename result_type::value_type;
                    return std::visit(esl::overload(
                        [this] <esl::same_but_cvref<value_type> Value> (Value && value) {
                            return derived().invoke(std::forward<Value>(value));
                        },
                        handle_one_error<nested_type>
                    ), esl::forward_like<T>(target.content));

                } else
                    return std::visit(esl::overload(
                        [this] <esl::same_but_cvref<value_type> Value> (Value && value) {
                            return esl::result<result_type>{derived().invoke(std::forward<Value>(value))};
                        },
                        handle_one_error<result_type>
                    ), esl::forward_like<T>(target.content));
            }

            /** Operate on two results. */
            template <esl::same_template<esl::result> T, esl::same_template<esl::result> U>
            constexpr decltype(auto) operator () (T && first, U && second) const {
                using first_type  = typename std::remove_cvref_t<T>::value_type;
                using second_type = typename std::remove_cvref_t<U>::value_type;
                using result_type = std::remove_cvref_t<decltype(derived().invoke(std::declval<first_type>(), std::declval<second_type>()))>;

                if constexpr (esl::same_template<result_type, esl::result>) {
                    using nested_type = typename result_type::value_type;
                    return std::visit(esl::overload(
                        [this] <esl::same_but_cvref<first_type> First, esl::same_but_cvref<second_type> Second> (First && a, Second && b) {
                            return derived().invoke(std::forward<First>(a), std::forward<Second>(b));
                        },
                        handle_two_errors<first_type, second_type, nested_type>
                    ), esl::forward_like<T>(first.content), esl::forward_like<U>(second.content));

                } else
                    return std::visit(esl::overload(
                        [this] <esl::same_but_cvref<first_type> First, esl::same_but_cvref<second_type> Second> (First && a, Second && b) {
                            return esl::result<result_type>{derived().invoke(std::forward<First>(a), std::forward<Second>(b))};
                        },
                        handle_two_errors<first_type, second_type, result_type>
                    ), esl::forward_like<T>(first.content), esl::forward_like<U>(second.content));
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename Derived, typename F>
        struct optional_impl {
            /** Operate on any number of optionals. */
            template <esl::same_template<std::optional>... Ts>
            constexpr decltype(auto) operator () (Ts &&... target) const {
                return derived().invoke(*std::forward<Ts>(target)...);
            }

            /** Operate on a single optional. Returns an optional. */
            template <esl::same_template<std::optional> T>
            constexpr auto operator () (T && target) const {
                using Result = decltype(derived().invoke(*std::forward<T>(target)));
                if (target)
                    return std::optional<Result>{derived().invoke(*std::forward<T>(target))};
                else
                    return std::optional<Result>{};
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

    }

    // For generic constructs that do not have a corresponding type,
    // these "fake" types are used to specify a particular lift.
    namespace target {

        /** deprecated */
        template <typename...> struct any {};
        /** deprecated */
        template <typename...> struct any_once {};
        /** deprecated */
        template <typename...> struct any_asymetric {};

        template <typename...> struct direct {};
        template <typename...> struct sized_range {};

        // Just an experiment:
        template <typename...> struct asymetric {};

    }

    // Only std containers (vector, variant and such), generic containers (sized_range) and esl::result
    // are implemented here. Other esl containers have their implementation in their respective headers.
    // Custom implementations may be added for any contiainer.
    // Note: esl::result is implemented here, because it's a dependency of the sized_range implementation.
    template <> struct lift_specialization_map<target::direct>:      lift_implementation<detail::lift::direct_impl>       {};
    template <> struct lift_specialization_map<target::sized_range>: lift_implementation<detail::lift::sized_range_impl>  {};
    template <> struct lift_specialization_map<std::vector>:         lift_implementation<detail::lift::sized_range_impl>  {};
    template <> struct lift_specialization_map<std::optional>:       lift_implementation<detail::lift::optional_impl>     {};
    template <> struct lift_specialization_map<std::variant>:        lift_implementation<detail::lift::variant_impl>      {};
    template <> struct lift_specialization_map<esl::result>:         lift_implementation<detail::lift::result_impl>       {};

    // User-defined: (TODO)
    /*
    template <> struct lift_specialization_map<target::tuple_vector>:      lift_implementation<tuple_vector> {};
    template <> struct lift_specialization_map<cynth::tuple_vector>:       lift_implementation<tuple_vector> {};
    template <> struct lift_specialization_map<target::category>:          lift_implementation<category>     {};
    template <> struct lift_specialization_map<target::component>:         lift_implementation<component>    {};
    template <> struct lift_specialization_map<cynth::component>:          lift_implementation<component>    {};
    template <> struct lift_specialization_map<cynth::optional_component>: lift_implementation<component>    {};
    template <> struct lift_specialization_map<cynth::component_vector>:   lift_implementation<component>    {};
    // TODO: Do I really want lift over component, optional_component and component_vector to do the same thing?
    */

    template <typename, template <typename...> typename... Rest> struct lift_type;

    // Nested target:
    template <typename F, template <typename...> typename First, template <typename...> typename... Rest>
    struct lift_type<F, First, Rest...>: detail::lift::base<lift_type<F, First, Rest...>, lift_type<F, Rest...>, First> {
        using base = detail::lift::base<lift_type<F, First, Rest...>, lift_type<F, Rest...>, First>;

        constexpr lift_type (F const & f): base{lift_type<F, Rest...>{f}}            {}
        constexpr lift_type (F &&      f): base{lift_type<F, Rest...>{std::move(f)}} {}
    };

    // Single target:
    template <typename F, template <typename...> typename T>
    struct lift_type<F, T>: detail::lift::base<lift_type<F, T>, F, T> {
        using base = detail::lift::base<lift_type<F, T>, F, T>;

        constexpr lift_type (F const & f): base{f}            {}
        constexpr lift_type (F &&      f): base{std::move(f)} {}
    };

    // Direct target:
    template <typename F>
    struct lift_type<F>: detail::lift::base<lift_type<F, target::direct>, F, target::direct> {
        using base = detail::lift::base<lift_type<F, target::direct>, F, target::direct>;

        constexpr lift_type (F const & f): base{f}            {}
        constexpr lift_type (F &&      f): base{std::move(f)} {}
    };

    namespace detail::lift {

        template <typename T, typename F>
        using any_base = detail::lift::base <
            T,
            F,
            target::sized_range,
            std::variant,
            esl::result,
            target::direct
        >;

    }

    /** deprecated */
    template <typename F>
    struct lift_type<F, target::any_once>: detail::lift::any_base<lift_type<F, target::any_once>, F> {
        using base = detail::lift::any_base<lift_type<F, target::any_once>, F>;

        constexpr lift_type (F const & f): base{f}            {}
        constexpr lift_type (F &&      f): base{std::move(f)} {}
    };

    /** deprecated */
    template <typename F>
    struct lift_type<F, target::any>: detail::lift::any_base<lift_type<F, target::any>, F> {
        using base = detail::lift::any_base<lift_type<F, target::any>, F>;

        constexpr lift_type (F const & f): base{f}            {}
        constexpr lift_type (F &&      f): base{std::move(f)} {}

        using detail::lift::sized_range_impl  <lift_type<F, target::any>, F>::operator();
        using detail::lift::variant_impl      <lift_type<F, target::any>, F>::operator();
        using detail::lift::result_impl       <lift_type<F, target::any>, F>::operator();
        using detail::lift::direct_impl       <lift_type<F, target::any>, F>::operator();

        template <typename... Ts>
        constexpr auto function () const {
            return [this] (Ts &&... args) {
                return operator()(std::forward<Ts>(args)...);
            };
        }
    };

    /**
     *  deprecated
     *
     *  Provides two overloads:
     *  f(w{a}, w{b})
     *  f(b)(w{a})
     *  where w is any abstraction that is supported by lift<target::any_once>.
     */
    template <typename F>
    struct lift_type<F, target::any_asymetric> {
        F fun;

        constexpr lift_type (F const & fun): fun{fun}            {}
        constexpr lift_type (F &&      fun): fun{std::move(fun)} {}

        template <typename T, typename U>
        constexpr decltype(auto) operator () (T && a, U && b) const {
            return lift_type<F, target::any>{fun}(std::forward<T>(a), std::forward<U>(b));
        }

        template <typename U>
        constexpr auto operator () (U && b) const {
            return lift_type<F, target::any>{
                [this, &b] <typename T> (T && a) /*-> decltype(auto)*/ requires std::invocable<F, T, U> {
                    return fun(std::forward<T>(a), std::forward<U>(b));
                }
            };
        }
    };

    template <template <typename...> typename... Ts, typename... Fs>
    constexpr lift_type<esl::overloaded<Fs...>, Ts...> lift (Fs &&... fs) {
        return {esl::overload(std::forward<Fs>(fs)...)};
    }

}

#if 0

        template <typename Derived, typename F>
        struct tuple_vector {
            template <esl::same_template<cynth::tuple_vector> T>
            constexpr auto operator () (T && target) const {
                return esl::lift_on_range<cynth::tuple_vector>(derived(), std::forward<T>(target));
            }

            template <esl::same_template<cynth::tuple_vector> T, esl::same_template<cynth::tuple_vector> U>
            constexpr auto operator () (T && first, U && second) const {
                return esl::lift_on_range<cynth::tuple_vector>(derived(), std::forward<T>(first), std::forward<U>(second));
            }

        private:

            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

#endif
