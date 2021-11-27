#pragma once
// TODO: return decltype(auto)

#include "config.hpp"
#include "component.hpp"
#include "category_base.hpp"
#include "result.hpp"
#include "lazy.hpp"
#include "view.hpp"
#include "util/general.hpp"
#include "util/container.hpp"
#include "util/tiny_vector.hpp"

#include <optional>
#include <vector>
#include <type_traits>
#include <concepts>
#include <utility>
#include <algorithm>

// TODO: Move this to cynth::
namespace cynth {

    namespace detail::lift {

        // TODO: Some mess with nested results here or in the next overload below...
        template <template <typename...> typename V, typename F, typename T>
        constexpr auto on_vector (F const & functor, T && target) {
            using value_type  = decltype(*util::make_forwarding_iterator<T>(target.begin()));
            using result_type = decltype(functor.invoke(std::declval<value_type>()));
            if constexpr (std::same_as<result_type, void>) {
                util::for_each (
                    util::make_forwarding_iterator<T>(target.begin()),
                    util::make_forwarding_iterator<T>(target.end()),
                    [&functor] (value_type v) {
                        return functor.invoke(std::forward<value_type>(v));
                    }
                );
                return cynth::result<void>{};
            } else {
                using vector = V<result_type>;
                vector result;
                if constexpr (util::reservable_range<vector>)
                    result.reserve(target.size());
                std::transform (
                    util::make_forwarding_iterator<T>(target.begin()),
                    util::make_forwarding_iterator<T>(target.end()),
                    std::back_inserter(result),
                    [&functor] (value_type v) {
                        return functor.invoke(std::forward<value_type>(v));
                    }
                );
                return result;
            }
        }

        template <template <typename...> typename V, typename F, typename T, typename U>
        constexpr auto on_vector (F const & functor, T && first, U && second) {
            using first_type  = decltype(*util::make_forwarding_iterator<T>(first.begin()));
            using second_type = decltype(*util::make_forwarding_iterator<U>(second.begin()));
            using result_type = decltype(functor.invoke(std::declval<first_type>(), std::declval<second_type>()));
            using final_type  = std::conditional_t<std::same_as<result_type, void>, void, V<result_type>>;
            if (first.size() != second.size())
                return cynth::result<final_type>{result_error{
                    "Binary tuple operation values count mismatch. -- " +
                    std::to_string(first.size()) +
                    " and " +
                    std::to_string(second.size()) +
                    "."
                }};
            if constexpr (std::same_as<result_type, void>) {
                util::for_each (
                    util::make_forwarding_iterator<T>(first.begin()),
                    util::make_forwarding_iterator<T>(first.end()),
                    util::make_forwarding_iterator<U>(second.begin()),
                    [&functor] (first_type a, second_type b) {
                        return functor.invoke(std::forward<first_type>(a), std::forward<second_type>(b));
                    }
                );
                return cynth::result<void>{};
            } else {
                using vector = final_type;
                vector result;
                if constexpr (util::reservable_range<vector>)
                    result.reserve(first.size());
                std::transform (
                    util::make_forwarding_iterator<T>(first.begin()),
                    util::make_forwarding_iterator<T>(first.end()),
                    util::make_forwarding_iterator<U>(second.begin()),
                    std::back_inserter(result),
                    [&functor] (first_type a, second_type b) {
                        return functor.invoke(std::forward<first_type>(a), std::forward<second_type>(b));
                    }
                );
                return cynth::result{result};
            }
        }

        // All needed functionality is separated into the following CRTP mixins.

        template <typename Derived, typename F>
        struct sized_range {
            template <typename T>
            //using vector_type = std::vector<T>;
            using vector_type = cynth::tuple_vector<T>;

            template <util::sized_range T>
            constexpr auto operator () (T && target) const {
                return on_vector<vector_type>(derived(), std::forward<T>(target));
            }

            // TODO: This was limited for use on different container types only. Is it still relevant?
            template <util::sized_range T, util::sized_range U> //requires (!util::same_template<T, U>)
            constexpr auto operator () (T && first, U && second) const {
                return on_vector<vector_type>(derived(), std::forward<T>(first), std::forward<U>(second));
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename Derived, typename F>
        struct view {
            template <typename T>
            using vector_type = cynth::tuple_vector<T>;

            template <util::is<cynth::view> T>
            constexpr auto operator () (T && target) const {
                return on_vector<vector_type>(derived(), std::forward<T>(target));
            }

            template <util::is<cynth::view> T, util::is<cynth::view> U> requires (!util::same_template<T, U>)
            constexpr auto operator () (T && first, U && second) const {
                return on_vector<vector_type>(derived(), std::forward<T>(first), std::forward<U>(second));
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename Derived, typename F>
        struct tuple_vector {
            template <util::is<cynth::tuple_vector> T>
            constexpr auto operator () (T && target) const {
                return on_vector<cynth::tuple_vector>(derived(), std::forward<T>(target));
            }

            template <util::is<cynth::tuple_vector> T, util::is<cynth::tuple_vector> U>
            constexpr auto operator () (T && first, U && second) const {
                return on_vector<cynth::tuple_vector>(derived(), std::forward<T>(first), std::forward<U>(second));
            }

        private:

            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename Derived, typename F>
        struct variant {
            /** Operate on any number of variants. */
            template <util::is<std::variant>... Ts>
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
            [] (result_error e) { return result<Result>{e}; };

        template <typename First, typename Second, typename Result>
        static constexpr auto handle_two_errors = util::overload {
            [] (result_error   e, Second const &) { return cynth::result<Result>{e}; },
            [] (First const &,    result_error e) { return cynth::result<Result>{e}; },
            [] (result_error   a, result_error)   { return cynth::result<Result>{a}; } // TODO: Combining multiple errors...
        };

        template <typename Derived, typename F>
        struct result {
            /** Operate on a single result. */
            template <util::is<cynth::result> T>
            constexpr decltype(auto) operator () (T && target) const {
                using value_type  = typename std::remove_cvref_t<T>::value_type;
                using result_type = std::remove_cvref_t<decltype(derived().invoke(std::declval<value_type>()))>;

                if constexpr (util::is<result_type, cynth::result>) {
                    using nested_type = typename result_type::value_type;
                    return std::visit(util::overload{
                        [this] <util::same_as_no_cvref<value_type> Value> (Value && value) {
                            return derived().invoke(std::forward<Value>(value));
                        },
                        handle_one_error<nested_type>
                    }, util::forward_like<T>(target.content));

                } else
                    return std::visit(util::overload{
                        [this] <util::same_as_no_cvref<value_type> Value> (Value && value) {
                            return cynth::result<result_type>{derived().invoke(std::forward<Value>(value))};
                        },
                        handle_one_error<result_type>
                    }, util::forward_like<T>(target.content));
            }


            /** Operate on two results. */
            template <util::is<cynth::result> T, util::is<cynth::result> U>
            constexpr decltype(auto) operator () (T && first, U && second) const {
                using first_type  = typename std::remove_cvref_t<T>::value_type;
                using second_type = typename std::remove_cvref_t<U>::value_type;
                using result_type = std::remove_cvref_t<decltype(derived().invoke(std::declval<first_type>(), std::declval<second_type>()))>;

                if constexpr (util::is<result_type, cynth::result>) {
                    using nested_type = typename result_type::value_type;
                    return std::visit(util::overload{
                        [this] <util::same_as_no_cvref<first_type> First, util::same_as_no_cvref<second_type> Second> (First && a, Second && b) {
                            return derived().invoke(std::forward<First>(a), std::forward<Second>(b));
                        },
                        handle_two_errors<first_type, second_type, nested_type>
                    }, util::forward_like<T>(first.content), util::forward_like<U>(second.content));

                } else
                    return std::visit(util::overload{
                        [this] <util::same_as_no_cvref<first_type> First, util::same_as_no_cvref<second_type> Second> (First && a, Second && b) {
                            return cynth::result<result_type>{derived().invoke(std::forward<First>(a), std::forward<Second>(b))};
                        },
                        handle_two_errors<first_type, second_type, result_type>
                    }, util::forward_like<T>(first.content), util::forward_like<U>(second.content));
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename Derived, typename F>
        struct category {
            /** Operate on any number of categories. */
            template <categorial... Ts> /*requires (!std::invocable<F, Ts...>)*/
            // TODO: requires !invocable everywhere but on the direct call?
            constexpr decltype(auto) operator () (Ts &&... target) const {
                return std::visit (
                    //derived().template function<>(), // Note: This ends a possible recursion.
                    [this] <typename... Us> (Us &&... value) { return derived().invoke(std::forward<Us>(value)...); },
                    util::forward_like<Ts>(target.value)...
                );
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename Derived, typename F>
        struct component {
            /** Operate on any number of components. */
            template <util::is<cynth::component>... Ts>
            constexpr decltype(auto) operator () (Ts &&... target) const {
                return derived().invoke(*std::forward<Ts>(target)...);
            }

            /** Operate on a single optional component. Returns an optional. */
            template <util::is<optional_component> T>
            constexpr auto operator () (T && target) const {
                using Result = decltype(derived().invoke(*std::forward<T>(target)));
                if (target)
                    return std::optional<Result>{derived().invoke(*std::forward<T>(target))};
                else
                    return std::optional<Result>{};
            }

            template <typename T>
            //using vector_type = std::vector<T>;
            using vector_type = cynth::tuple_vector<T>;

            // TODO: It doesn't make much sense to treat both component and component_vector the same.
            // Or does it?
            template <util::is<component_vector> T>
            constexpr auto operator () (T && target) const {
                return on_vector<vector_type>(derived(), std::forward<T>(target));
            }
            template <util::is<component_vector> T, util::is<component_vector> U>
            constexpr auto operator () (T && first, U && second) const {
                return on_vector<vector_type>(derived(), std::forward<T>(first), std::forward<U>(second));
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename Derived, typename F>
        struct optional {
            /** Operate on any number of optionals. */
            template <util::is<cynth::optional>... Ts>
            constexpr decltype(auto) operator () (Ts &&... target) const {
                return derived().invoke(*std::forward<Ts>(target)...);
            }

            /** Operate on a single optional. Returns an optional. */
            template <util::is<cynth::optional> T>
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

        template <typename Derived, typename F>
        struct direct {
            template <typename... Ts> requires /*util::callable<F, Ts...>*/ std::invocable<F, Ts...>
            constexpr decltype(auto) operator () (Ts &&... args) const {
                return derived().fun(std::forward<Ts>(args)...); // Note: This ends any possible recursion.
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <template <typename...> typename> struct specialization_map;

        template <template <typename, typename> typename S>
        struct specialization_map_base {
            template <typename Derived, typename F>
            using tpl = S<Derived, F>;
        };

        template <template <typename...> typename Tag, typename Derived, typename F>
        using specialization = typename specialization_map<Tag>::template tpl<Derived, F>;

        // TODO: Deprecate detail::lift::lift.
        template <
            typename Derived,
            typename F,
            template <typename...> typename... Tags
        >
        struct base: specialization<Tags, Derived, F>... {
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

    namespace target {

        template <typename...> struct any {};
        template <typename...> struct any_once {};
        template <typename...> struct any_asymetric {};
        template <typename...> struct direct {};
        template <typename...> struct tuple_vector {};
        template <typename...> struct vector {};
        template <typename...> struct sized_range {};
        template <typename...> struct view {};
        template <typename...> struct variant {};
        template <typename...> struct optional {};
        template <typename...> struct category {};
        template <typename...> struct component {};
        template <typename...> struct result {};

        // TODO?
        // evaluation:        tuple_vector<result<category>>
        // single_evaluation: result<category>

    }

    namespace detail::lift {

        template <> struct specialization_map<target::direct>:            specialization_map_base<direct>       {};
        template <> struct specialization_map<target::tuple_vector>:      specialization_map_base<tuple_vector> {};
        template <> struct specialization_map<cynth::tuple_vector>:       specialization_map_base<tuple_vector> {};
        template <> struct specialization_map<target::sized_range>:       specialization_map_base<sized_range>  {};
        template <> struct specialization_map<target::vector>:            specialization_map_base<sized_range>  {};
        template <> struct specialization_map<cynth::vector>:             specialization_map_base<sized_range>  {};
        template <> struct specialization_map<target::view>:              specialization_map_base<view>         {};
        template <> struct specialization_map<cynth::view>:               specialization_map_base<view>         {};
        template <> struct specialization_map<target::optional>:          specialization_map_base<optional>     {};
        template <> struct specialization_map<cynth::optional>:           specialization_map_base<optional>     {};
        template <> struct specialization_map<target::variant>:           specialization_map_base<variant>      {};
        template <> struct specialization_map<cynth::variant>:            specialization_map_base<variant>      {};
        template <> struct specialization_map<target::category>:          specialization_map_base<category>     {};
        template <> struct specialization_map<target::component>:         specialization_map_base<component>    {};
        template <> struct specialization_map<cynth::component>:          specialization_map_base<component>    {};
        template <> struct specialization_map<cynth::optional_component>: specialization_map_base<component>    {};
        template <> struct specialization_map<cynth::component_vector>:   specialization_map_base<component>    {};
        template <> struct specialization_map<target::result>:            specialization_map_base<result>       {};
        template <> struct specialization_map<cynth::result>:             specialization_map_base<result>       {};
        // TODO: Do I really want lift over component, optional_component and component_vector to do the same thing?

    }

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
            target::tuple_vector,
            target::variant,
            target::result,
            target::component,
            target::category,
            target::direct
        >;

    }

    /** Lift a callable to operate on containers and other composite values. */
    template <typename F>
    struct lift_type<F, target::any_once>: detail::lift::any_base<lift_type<F, target::any_once>, F> {
        using base = detail::lift::any_base<lift_type<F, target::any_once>, F>;

        constexpr lift_type (F const & f): base{f}            {}
        constexpr lift_type (F &&      f): base{std::move(f)} {}
    };

    /** Lift a callable to operate on containers and other composite values recursively until a direct call is possible. */
    template <typename F>
    struct lift_type<F, target::any>: detail::lift::any_base<lift_type<F, target::any>, F> {
        using base = detail::lift::any_base<lift_type<F, target::any>, F>;

        constexpr lift_type (F const & f): base{f}            {}
        constexpr lift_type (F &&      f): base{std::move(f)} {}

        using detail::lift::sized_range  <lift_type<F, target::any>, F>::operator();
        using detail::lift::tuple_vector <lift_type<F, target::any>, F>::operator();
        using detail::lift::variant      <lift_type<F, target::any>, F>::operator();
        using detail::lift::result       <lift_type<F, target::any>, F>::operator();
        using detail::lift::component    <lift_type<F, target::any>, F>::operator();
        using detail::lift::category     <lift_type<F, target::any>, F>::operator();
        using detail::lift::direct       <lift_type<F, target::any>, F>::operator();

        template <typename... Ts>
        constexpr auto function () const {
            return [this] (Ts &&... args) {
                return operator()(std::forward<Ts>(args)...);
            };
        }
    };

    /**
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

    // Just an experiment:
    template <typename F, template <typename...> typename... Ts>
    struct lift_: lift_type<F, Ts...> {
        using base = lift_type<F, Ts...>;

        template <typename... Fs>
        constexpr lift_ (Fs &&... fs):
            base{fs...} {}
    };

    // TODO: Rename to lift as soon as I get rid of the old lift implementation.
    template <template <typename...> typename... Ts, typename... Fs>
    constexpr lift_type<util::overloaded<Fs...>, Ts...> lift2 (Fs &&... fs) {
        return {util::overload2(std::forward<Fs>(fs)...)};
    }

}
