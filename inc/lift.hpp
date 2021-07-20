#pragma once
// TODO: return decltype(auto)

#include "config.hpp"
#include "component.hpp"
#include "category_base.hpp"
#include "result.hpp"
#include "lazy.hpp"
#include "util/general.hpp"
#include "util/tiny_vector.hpp"
#include "asg/values.hpp"
#include "asg/types.hpp"
#include "asg/declarations.hpp"

#include <optional>
#include <vector>
#include <type_traits>
#include <concepts>
#include <utility>
#include <algorithm>

namespace cynth::lift {

    namespace detail {

        template <template <typename...> typename V, typename F, typename T>
        constexpr auto on_vector (F const & functor, T && target) {
            using value_type  = decltype(*util::make_forwarding_iterator<T>(target.begin()));
            using result_type = decltype(functor.invoke(std::declval<value_type>()));
            using vector      = V<result_type>;
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

        template <template <typename...> typename V, typename F, typename T, typename U>
        constexpr auto on_vector (F const & functor, T && first, U && second) {
            using first_type  = decltype(*util::make_forwarding_iterator<T>(first.begin()));
            using second_type = decltype(*util::make_forwarding_iterator<U>(second.begin()));
            using result_type = decltype(functor.invoke(std::declval<first_type>(), std::declval<second_type>()));
            using vector      = V<result_type>;
            if (first.size() != second.size())
                return cynth::result<vector>{result_error{
                    "Binary tuple operation values count mismatch. -- " +
                    std::to_string(first.size()) +
                    " and " +
                    std::to_string(second.size()) +
                    "."
                }};
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

        // The lift base is only used for the common function member and to apply the mixins below.

        template <
            typename Derived,
            typename F,
            template <typename, typename> typename... Targets
        >
        struct lift: Targets<Derived, F>... {
            F fun;

            constexpr lift (F && f): fun{std::move(f)} {}
            constexpr lift (F const & f): fun{f} {}

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
            Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        // All needed functionality is separated into the following CRTP mixins.

        template <typename Derived, typename F>
        struct sized_range {
            template <typename T>
            //using vector_type = std::vector<T>;
            using vector_type = cynth::tuple_vector<T>;
            // Note: This is only used for different range types.

            /*template <util::sized_range T>
            constexpr auto operator () (T && target) const {
                return on_vector<vector_type>(derived(), std::forward<T>(target));
            }*/

            template <util::sized_range T, util::sized_range U> requires (!util::same_template<T, U>)
            constexpr auto operator () (T && first, U && second) const {
                return on_vector<vector_type>(derived(), std::forward<T>(first), std::forward<U>(second));
            }

        private:
            Derived const & derived () const {
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
            Derived const & derived () const {
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

            Derived const & derived () const {
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
                    [this] <typename... Us> (Us &&... value) { return derived().call(std::forward<Us>(value)...); },
                    std::forward<Ts>(target)...
                );
            }

        private:
            Derived const & derived () const {
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
            Derived const & derived () const {
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
            Derived const & derived () const {
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
            Derived const & derived () const {
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
            Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename T, typename F>
        using any_base = detail::lift <
            T,
            F,
            detail::sized_range,
            detail::tuple_vector,
            detail::variant,
            detail::result,
            detail::component,
            detail::category,
            detail::direct
        >;

    }

    template <typename F>
    struct sized_range: detail::lift<sized_range<F>, F, detail::sized_range> {
        using base = detail::lift<sized_range<F>, F, detail::sized_range>;
        constexpr sized_range (F const & f): base{f} {}
        constexpr sized_range (F && f): base{std::move(f)} {}
    };

    template <typename F>
    struct view: detail::lift<view<F>, F, detail::view> {
        using base = detail::lift<view<F>, F, detail::view>;
        constexpr view (F const & f): base{f} {}
        constexpr view (F && f): base{std::move(f)} {}
    };

    template <typename F>
    struct tuple_vector: detail::lift<tuple_vector<F>, F, detail::tuple_vector> {
        using base = detail::lift<tuple_vector<F>, F, detail::tuple_vector>;
        constexpr tuple_vector (F && f): base{std::move(f)} {}
        constexpr tuple_vector (F const & f): base{f} {}
    };

    template <typename F>
    struct variant: detail::lift<variant<F>, F, detail::variant> {
        using base = detail::lift<variant<F>, F, detail::variant>;
        constexpr variant (F const & f): base{f} {}
        constexpr variant (F && f): base{std::move(f)} {}
    };

    template <typename F>
    struct result: detail::lift<result<F>, F, detail::result> {
        using base = detail::lift<result<F>, F, detail::result>;
        constexpr result (F const & f): base{f} {}
        constexpr result (F && f): base{std::move(f)} {}
    };

    template <typename F>
    struct category: detail::lift<category<F>, F, detail::category> {
        using base = detail::lift<category<F>, F, detail::category>;
        constexpr category (F const & f): base{f} {}
        constexpr category (F && f): base{std::move(f)} {}
    };

    template <typename F>
    struct component: detail::lift<component<F>, F, detail::component> {
        using base = detail::lift<component<F>, F, detail::component>;
        constexpr component (F const & f): base{f} {}
        constexpr component (F && f): base{std::move(f)} {}
    };

    template <typename F>
    struct direct: detail::lift<direct<F>, F, detail::direct> {
        using base = detail::lift<direct<F>, F, detail::direct>;
        constexpr direct (F const & f): base{f} {}
        constexpr direct (F && f): base{std::move(f)} {}
    };

    template <typename F>
    struct category_component: detail::lift<category_component<F>, component<category<F>>, detail::direct> {
        using base = detail::lift<category_component<F>, component<category<F>>, detail::direct>;

        constexpr category_component (F const & f):
            base{lift::component{lift::category{f}}} {}
        constexpr category_component (F && f):
            base{lift::component{lift::category{std::move(f)}}} {}
    };

#if 0
    template <typename F>
    struct component_vector: detail::lift<component_vector<F>, component<component<F>>, detail::direct> {
        using base = detail::lift<component_vector<F>, component<component<F>>, detail::direct>;

        constexpr component_vector (F && f):
            base{lift::component{lift::component{std::move(f)}}} {}
        constexpr component_vector (F const & f):
            base{lift::component{lift::component{f}}} {}
    };
#endif

    template <typename F>
    struct category_vector: detail::lift<category_vector<F>, tuple_vector<category<F>>, detail::direct> {
        using base = detail::lift<category_vector<F>, tuple_vector<category<F>>, detail::direct>;

        constexpr category_vector (F const & f):
            base{lift::tuple_vector{lift::category{f}}} {}
        constexpr category_vector (F && f):
            base{lift::tuple_vector{lift::category{std::move(f)}}} {}
    };

    template <typename F>
    struct category_result: detail::lift<category_component<F>, result<category<F>>, detail::direct> {
        using base = detail::lift<category_component<F>, result<category<F>>, detail::direct>;

        constexpr category_result (F const & f):
            base{lift::result{lift::category{f}}} {}
        constexpr category_result (F && f):
            base{lift::result{lift::category{std::move(f)}}} {}
    };

    template <typename F>
    struct evaluation: detail::lift<evaluation<F>, tuple_vector<result<category<F>>>, detail::direct> {
        using base = detail::lift<evaluation<F>, tuple_vector<result<category<F>>>, detail::direct>;

        constexpr evaluation (F const & f):
            base{lift::tuple_vector{lift::result{lift::category{f}}}} {}
        constexpr evaluation (F && f):
            base{lift::tuple_vector{lift::result{lift::category{std::move(f)}}}} {}
    };

    template <typename F>
    struct single_evaluation: detail::lift<single_evaluation<F>, result<category<F>>, detail::direct> {
        using base = detail::lift<single_evaluation<F>, result<category<F>>, detail::direct>;

        constexpr single_evaluation (F const & f):
            base{lift::result{lift::category{f}}} {}
        constexpr single_evaluation (F && f):
            base{lift::result{lift::category{std::move(f)}}} {}
    };

    /** Lift a callable to operate on containers and other composite values. */
    template <typename F>
    struct any_once: detail::any_base<any_once<F>, F> {
        using base = detail::any_base<any_once<F>, F>;
        constexpr any_once (F const & f): base{f} {}
        constexpr any_once (F && f): base{std::move(f)} {}
    };

    /** Lift a callable to operate on containers and other composite values recursively until a direct call is possible. */
    template <typename F>
    struct any: detail::any_base<any<F>, F> {
        using base = detail::any_base<any<F>, F>;

        constexpr any (F const & f): base{f} {}
        constexpr any (F && f): base{std::move(f)} {}

        using detail::sized_range  <any<F>, F>::operator();
        using detail::tuple_vector <any<F>, F>::operator();
        using detail::variant      <any<F>, F>::operator();
        using detail::result       <any<F>, F>::operator();
        using detail::component    <any<F>, F>::operator();
        using detail::category     <any<F>, F>::operator();
        using detail::direct       <any<F>, F>::operator();

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
     *  where w is any abstraction that is supported by lift::any.
     */
    template <typename F>
    struct any_asymetric {
        F fun;

        constexpr any_asymetric (F const & fun): fun{fun} {}
        constexpr any_asymetric (F && fun): fun{std::move(fun)} {}

        template <typename T, typename U>
        constexpr decltype(auto) operator () (T && a, U && b) const {
            return lift::any{fun}(std::forward<T>(a), std::forward<U>(b));
        }

        template <typename U>
        constexpr auto operator () (U && b) const {
            return lift::any {
                [this, &b] <typename T> (T && a) /*-> decltype(auto)*/ requires std::invocable<F, T, U> {
                    return fun(std::forward<T>(a), std::forward<U>(b));
                }
            };
        }
    };

}
