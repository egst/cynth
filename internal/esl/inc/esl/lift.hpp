#pragma once

#include <algorithm>
#include <concepts>
#include <iterator>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "esl/boolean.hpp"
#include "esl/functional.hpp"
#include "esl/iterator.hpp"
#include "esl/ranges.hpp"
#include "esl/result.hpp"
#include "esl/type_manip.hpp"
#include "esl/zip.hpp"

namespace esl {

    template <typename> struct lift_specialization_map;

    template <template <typename, typename> typename S>
    struct lift_implementation {
        template <typename Derived, typename F>
        using tpl = S<Derived, F>;
    };

    template <typename Tag, typename Derived, typename F>
    using specialization = typename lift_specialization_map<Tag>::template tpl<Derived, F>;

    namespace detail::lift {

        // TODO: Deprecate detail::lift::lift.
        template <
            typename Derived,
            typename F,
            typename... Tags
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
            for (auto && val: std::forward<T>(target))
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
            return esl::result<final_type>{esl::result_error{"Binary tuple operation values count mismatch."}};
        if constexpr (std::same_as<result_type, void>) {
            for (auto && [a, b]: esl::zip(std::forward<T>(first), std::forward<U>(second)))
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

    template <template <typename...> typename V, typename F, typename T>
    constexpr auto lift_on_range_cat (F const & functor, T && target) {
        using value_type  = decltype(*esl::make_forwarding_iterator<T>(target.begin()));
        using result_type = decltype(functor.invoke(std::declval<value_type>()));
        using nested_type = esl::range_value_type<result_type>;
        if constexpr (std::same_as<result_type, void>) {
            for (auto && val: std::forward<T>(target))
                functor.invoke(std::forward<value_type>(val));
            return esl::result<void>{};
        } else {
            using vector = V<nested_type>;
            vector result;
            if constexpr (esl::reservable_range<vector>)
                result.reserve(target.size()); // It could need more though, but this is the known minimum.
            for (auto && val: std::forward<T>(target))
                for (auto && nested: functor.invoke(std::forward<value_type>(val)))
                    result.push_back(esl::forward_like<result_type>(nested));
            return result;
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
        struct nested_range_cat_impl {
            template <typename T>
            using vector_type = std::vector<T>;

            template <esl::sized_range T>
            constexpr auto operator () (T && target) const {
                return esl::lift_on_range_cat<vector_type>(derived(), std::forward<T>(target));
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

        template <bool RETURN, typename Result, typename... Ts>
        static constexpr auto handle_errors =
            [] <typename... Us> (Us &&... args)
            requires (
                // All types must be the same as specified (in the specified order) or esl::result_error:
                sizeof...(Us) == sizeof...(Ts) &&
                ((esl::same_but_cvref<esl::result_error, Us> || esl::same_but_cvref<Ts, Us>) && ...) &&
                // At least one of them must be esl::result_error:
                esl::some_same_as<esl::result_error, Us...>
            ) {
                if constexpr (RETURN)
                    return Result{esl::first_of<esl::result_error>(std::forward<Us>(args)...)};
            };

        template <bool RETURN, typename Result, typename... Ts>
        static constexpr auto handle_optional_errors =
            [] <typename... Us> (Us &&... args)
            requires (
                sizeof...(Us) == sizeof...(Ts) &&
                // Same as handle_errors, but std::monostate is also allowed:
                ((
                    esl::same_but_cvref<std::monostate, Us> ||
                    esl::same_but_cvref<esl::result_error, Us> ||
                    esl::same_but_cvref<Ts, Us>
                ) && ...) &&
                esl::some_same_as<esl::result_error, Us...>
            ) {
                if constexpr (RETURN)
                    return Result{esl::first_of<esl::result_error>(std::forward<Us>(args)...)};
            };

        template <typename T>
        using value_type = typename std::remove_cvref_t<T>::value_type;

        template <typename Derived, typename F>
        struct result_impl {
            /** Operate on any number of results. */
            template <esl::same_template<esl::result>... Ts>
            constexpr decltype(auto) operator () (Ts &&... targets) const {
                using result_type = std::remove_cvref_t<decltype(derived().invoke(
                    std::declval<value_type<Ts>>()...
                ))>;

                if constexpr (std::same_as<result_type, void>) {
                    std::visit(
                        esl::overload(
                            [this] <typename... Args> (Args &&... args) requires (
                                (esl::same_but_cvref<value_type<Ts>, Args> && ...)
                            ) {
                                derived().invoke(std::forward<Args>(args)...);
                            },
                            handle_errors<false, esl::result<void>, value_type<Ts>...>
                        ),
                        esl::forward_like<Ts>(targets.content)...
                    );

                } else if constexpr (esl::same_template<result_type, esl::result>) {
                    using nested_type = typename result_type::value_type;
                    return std::visit(
                        esl::overload(
                            [this] <typename... Args> (Args &&... args) requires (
                                esl::same_but_cvref<value_type<Ts>, Args> && ...
                            ) {
                                return derived().invoke(std::forward<Args>(args)...);
                            },
                            handle_errors<true, esl::result<nested_type>, value_type<Ts>...>
                        ),
                        esl::forward_like<Ts>(targets.content)...
                    );

                } else if constexpr (esl::same_template<result_type, esl::optional_result>) {
                    using nested_type = typename result_type::value_type;
                    return std::visit(
                        esl::overload(
                            [this] <typename... Args> (Args &&... args) requires (
                                (
                                    esl::same_but_cvref<Args, value_type<Ts>> ||
                                    esl::same_but_cvref<Args, std::monostate>
                                ) && ...
                            ) {
                                return derived().invoke(std::forward<Args>(args)...);
                            },
                            handle_errors<true, esl::optional_result<nested_type>, value_type<Ts>...>
                        ),
                        esl::forward_like<Ts>(targets.content)...
                    );

                } else
                    return std::visit(
                        esl::overload(
                            [this] <typename... Args> (Args &&... args) requires (
                                esl::same_but_cvref<value_type<Ts>, Args> && ...
                            ) {
                                return esl::result<result_type>{derived().invoke(std::forward<Args>(args)...)};
                            },
                            handle_errors<true, esl::result<result_type>, value_type<Ts>...>
                        ),
                        esl::forward_like<Ts>(targets.content)...
                    );
            }

        private:

            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename Derived, typename F>
        struct opt_result_impl {
            /** Operate on any number of results. */
            template <esl::same_template<esl::optional_result>... Ts>
            constexpr decltype(auto) operator () (Ts &&... targets) const {
                using result_type = std::remove_cvref_t<decltype(derived().invoke(
                    std::declval<value_type<Ts>>()...
                ))>;

                if constexpr (std::same_as<result_type, void>) {
                    static_assert("Optional result of void not implemented.");

                } else if constexpr (esl::same_template<result_type, esl::result>) {
                    using nested_type = typename result_type::value_type;
                    return std::visit(
                        esl::overload(
                            [this] <typename... Args> (Args &&... args) requires (
                                (
                                    esl::same_but_cvref<Args, value_type<Ts>> ||
                                    esl::same_but_cvref<Args, std::monostate>
                                ) && ...
                            ) {
                                return derived().invoke(std::forward<Args>(args)...);
                            },
                            handle_optional_errors<true, esl::result<nested_type>, value_type<Ts>...>
                        ),
                        esl::forward_like<Ts>(targets.content)...
                    );

                } else if constexpr (esl::same_template<result_type, esl::optional_result>) {
                    using nested_type = typename result_type::value_type;
                    return std::visit(
                        esl::overload(
                            [this] <typename... Args> (Args &&... args) requires (
                                (
                                    esl::same_but_cvref<Args, value_type<Ts>> ||
                                    esl::same_but_cvref<Args, std::monostate>
                                ) && ...
                            ) {
                                return derived().invoke(std::forward<Args>(args)...);
                            },
                            handle_optional_errors<true, esl::optional_result<nested_type>, value_type<Ts>...>
                        ),
                        esl::forward_like<Ts>(targets.content)...
                    );

                } else
                    return std::visit(
                        esl::overload(
                            [this] <typename... Args> (Args &&... args) requires (
                                (
                                    esl::same_but_cvref<Args, value_type<Ts>> ||
                                    esl::same_but_cvref<Args, std::monostate>
                                ) && ...
                            ) {
                                return esl::result<result_type>{derived().invoke(std::forward<Args>(args)...)};
                            },
                            handle_optional_errors<true, esl::result<result_type>, value_type<Ts>...>
                        ),
                        esl::forward_like<Ts>(targets.content)...
                    );
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

        template <typename Derived, typename F>
        struct optional_impl {
            // TODO: What's going on here with the two implementations?

            /** Operate on any number of optionals. */
            template <esl::same_template<std::optional>... Ts>
            constexpr decltype(auto) operator () (Ts &&... target) const {
                return derived().invoke(*std::forward<Ts>(target)...);
            }

            /** Operate on a single optional. Returns an optional. */
            template <esl::same_template<std::optional> T>
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

        template <typename Derived, typename F>
        struct pointer_impl {
            /**
             *  Operate on a single pointer with an esl::optional_result result.
             *  This is just a very specific use case that I currently need, others will be implemented as needed.
             */
            template <typename T>
            constexpr auto operator () (T * target) const {
                using result_type = std::remove_cvref_t<decltype(derived().invoke(*target))>;
                if constexpr (esl::same_template<result_type, esl::optional_result>) {
                    if (target)
                        return derived().invoke(*target);
                    else
                        return result_type{};
                } else {
                    static_assert("No lifts over pointers without optional_result implemented yet.");
                    // ...
                }
            }

        private:
            constexpr Derived const & derived () const {
                return *static_cast<Derived const *>(this);
            }
        };

    }

    template <template <typename...> typename> struct lift_tpl_target_map;

    template <typename T>
    struct lift_target {
        using target = T;
    };

    struct lift_target_tag {};

    namespace target {

        struct direct           { constexpr static lift_target_tag tag = {}; };
        struct sized_range      { constexpr static lift_target_tag tag = {}; };
        struct nested_range_cat { constexpr static lift_target_tag tag = {}; };

        struct pointer          { constexpr static lift_target_tag tag = {}; };
        struct optional         { constexpr static lift_target_tag tag = {}; };
        struct variant          { constexpr static lift_target_tag tag = {}; };
        struct vector           { constexpr static lift_target_tag tag = {}; };

        struct result           { constexpr static lift_target_tag tag = {}; };
        struct optional_result  { constexpr static lift_target_tag tag = {}; };

        template <typename...> struct nested {};
        template <typename...> struct nary {};

        /** ex.: target::tpl<std::vector> -> target::vector */
        template <template <typename...> typename Tpl>
        using tpl = typename lift_tpl_target_map<Tpl>::target;

    }

    template <> struct lift_tpl_target_map<std::optional>:        lift_target<target::optional>        {};
    template <> struct lift_tpl_target_map<std::variant>:         lift_target<target::variant>         {};
    template <> struct lift_tpl_target_map<std::vector>:          lift_target<target::vector>          {};
    template <> struct lift_tpl_target_map<esl::result>:          lift_target<target::result>          {};
    template <> struct lift_tpl_target_map<esl::optional_result>: lift_target<target::optional_result> {};

    // Only std containers (vector, variant and such), generic containers (sized_range) and esl::result
    // are implemented here. Other esl containers have their implementation in their respective headers.
    // Custom implementations may be added for any contiainer.
    // Note: esl::result is implemented here, because it's a dependency of the sized_range implementation.
    template <> struct lift_specialization_map<target::direct>:           lift_implementation<detail::lift::direct_impl>       {};
    template <> struct lift_specialization_map<target::sized_range>:      lift_implementation<detail::lift::sized_range_impl>  {};
    template <> struct lift_specialization_map<target::nested_range_cat>: lift_implementation<detail::lift::sized_range_impl>  {};
    template <> struct lift_specialization_map<target::vector>:           lift_implementation<detail::lift::sized_range_impl>  {};
    template <> struct lift_specialization_map<target::pointer>:          lift_implementation<detail::lift::pointer_impl>      {};
    template <> struct lift_specialization_map<target::optional>:         lift_implementation<detail::lift::optional_impl>     {};
    template <> struct lift_specialization_map<target::variant>:          lift_implementation<detail::lift::variant_impl>      {};
    template <> struct lift_specialization_map<target::result>:           lift_implementation<detail::lift::result_impl>       {};
    template <> struct lift_specialization_map<target::optional_result>:  lift_implementation<detail::lift::opt_result_impl>   {};

    template <typename, typename... Rest> struct lift_type;

    // Nested target:
    template <typename F, typename First, typename... Rest>
    struct lift_type<F, First, Rest...>: detail::lift::base<lift_type<F, First, Rest...>, lift_type<F, Rest...>, First> {
        using base = detail::lift::base<lift_type<F, First, Rest...>, lift_type<F, Rest...>, First>;

        constexpr lift_type (F const & f): base{lift_type<F, Rest...>{f}}            {}
        constexpr lift_type (F &&      f): base{lift_type<F, Rest...>{std::move(f)}} {}
    };

    // Single target:
    template <typename F, typename T>
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

    /*
     *  Lift usage:
     *
     *  n-ary vs nested lift:
     *  f = lift_nary<result, vector, variant>(g)         => f(result<T>, vector<U>, variant<V, W>)   # fixed number of args
     *  f = lift_nested<result, vector, variant>(g)       => f(result<vector<variant<T, U>>>, ...)    # any number of args (if the individual implementations support it)
     *
     *  to combine both:
     *  f = lift_nary<nested<result, vector>, variant>(g) => f(result<vector<T>>, variant<U, V>, ...)
     *
     *  the default `lift` is `lift_nested`
     *
     *  lift_*<...>(f, g, h) performs overload(f, g, h)
     */

    template <typename... Ts, typename... Fs>
    constexpr lift_type<esl::overloaded<Fs...>, Ts...> lift_nested (Fs &&... fs) {
        return {esl::overload(std::forward<Fs>(fs)...)};
    }

    template <typename... Ts, typename... Fs>
    constexpr auto lift (Fs &&... fs) {
        return lift_nested<Ts...>(std::forward<Fs>(fs)...);
    }

    namespace detail::lift {

        template <typename T>
        struct nested {
            template <typename... Fs>
            constexpr static auto lift (Fs &&... fs) {
                return lift_nested<T>(std::forward<Fs>(fs)...);
            }
        };

        template <typename... Ts>
        struct nested<target::nested<Ts...>> {
            template <typename... Fs>
            constexpr static auto lift (Fs &&... fs) {
                return lift_nested<Ts...>(std::forward<Fs>(fs)...);
            }
        };

    }

    /** Only the binary version works right now. */
    template <typename T, typename U, typename... Fs>
    constexpr auto lift_nary (Fs &&... fs) {
        return [...fs = esl::functor(std::forward<Fs>(fs))] <typename V, typename W> (V && a, W && b) {
            return detail::lift::nested<U>::lift(
                esl::curry(detail::lift::nested<T>::lift(fs...))(std::forward<V>(a))
            )(std::forward<W>(b));
        };
    }

}
