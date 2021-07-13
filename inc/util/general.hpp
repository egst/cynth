#pragma once

#include <cstddef>
#include <string>
#include <optional>
#include <variant>
#include <vector>
#include <type_traits>
#include <concepts>
#include <utility>
#include <iterator>
#include <tuple>
#include <functional>

namespace cynth::util {

    /**
     *  This is only a debug tool.
     *  Place `util::inspect<Type>{}` or `util::inspect<decltype(value)>{}`
     *  somewhere to see the corresponding type in an error message.
     */
    template <typename Type> requires false struct inspect {};

    template <typename T>
    concept scalar = std::is_scalar_v<T>;

    /** Overload set from lambda functions. */
    template <typename... Fs> struct overload: Fs... { using Fs::operator()...; };
    template <typename... Fs> overload(Fs...) -> overload<Fs...>;

    namespace detail {

        template <typename T, template <typename...> typename U>
        struct is: std::false_type {};

        // Note: std::same_as is actually necessary here to support type aliases, e.g. is<util::tiny_vector<T>, tuple_vector>.
        template <template <typename...> typename T, template <typename...> typename U, typename... Ts>
        requires std::same_as<T<Ts...>, U<Ts...>>
        struct is<T<Ts...>, U>: std::true_type {};

    }

    /**
     *  Is a specific template with any template arguments.
     *  E.g. to check if T is some form of std::vector:
     *  is<T, std::vector> will be true for std::vector<int>, etc.
     */
    template <typename T, template <typename...> typename U>
    concept is = detail::is<std::remove_cvref_t<T>, U>::value;

    /** Negation of util::is */
    template <typename T, template <typename...> typename U>
    concept is_not = !is<T, U>;

    /** Is possibly a temporary value - is an rvalue reference or a direct value. */
    template <typename T>
    concept temporary = std::is_rvalue_reference_v<T> || !std::is_reference_v<T>;

    /** std::make_move_iterator or keep the same iterator - similar to std::forward<T>. */
    template <typename T, typename I>
    constexpr auto make_forwarding_iterator (I && i) {
        if constexpr (temporary<T>)
            return std::make_move_iterator(i);
        else
            return i;
    }

    /*template <typename To, compatible_variant<To> From>
    To variant_cast (From && source) {
        return std::visit([] <typename T> (T && val) -> To { return {val}; }, source);
    }*/

    /** Add/remove any kind of reference to mimic another type. */
    template <typename T, typename U>
    using match_reference = std::conditional_t <
        std::is_reference_v<T>,
        std::conditional_t <
            std::is_rvalue_reference_v<T>,
            std::add_rvalue_reference_t<std::remove_reference_t<U>>,
            std::add_lvalue_reference_t<std::remove_reference_t<U>>
        >,
        std::remove_reference_t<U>
    >;

    /** Add/remove const to mimic another type. */
    template <typename T, typename U>
    using match_constness = std::conditional_t <
        std::is_const_v<std::remove_reference_t<T>>,
        // Remove reference, match constness, then add the reference back:
        util::match_reference<U, std::add_const_t<std::remove_reference_t<U>>>,
        std::remove_const_t<U>
    >;

    /** Add/remove const and any kind of reference to mimic another type. TODO: volatile */
    template <typename T, typename U>
    using match_cvref = util::match_reference<T, util::match_constness<T, U>>;

    /**
     *  Alias for match_cvref.
     *  Inspired by the "deducting this" proposal along with the forward_like function below.
     */
    template <typename T, typename U>
    using like = util::match_cvref<T, U>;

    /** std::forward based on a different type. */
    template <typename T, typename U>
    constexpr decltype(auto) forward_like (U && x) {
        return std::forward<util::like<T, U>>(x);
    }

    template <typename T, typename U>
    concept same_as_no_cvref = std::same_as<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;

    namespace detail {

        template <typename, typename>
        inline constexpr bool element = false;

        template <template <typename...> typename C, typename T, typename... Ts>
        inline constexpr bool element<T, C<Ts...>> = (std::same_as<T, Ts> || ...);

        template <typename, typename>
        inline constexpr bool subset = false;

        template <template <typename...> typename C, typename... Ts, typename... Us>
        inline constexpr bool subset<C<Ts...>, C<Us...>> = (element<Ts, C<Us...>> && ...);

    }

    /** Item containable in the variant.
        e.g. variant_member<item, variant>
        or   variant_member<variant> item */
    template <typename T, typename Variant>
    concept variant_member = detail::element<std::remove_cvref_t<T>, Variant>;

    /** First variant containable in the other.
        e.g. compatible_variant<source, target>
        or   compatible_variant<target> source */
    template <typename T, typename U>
    concept compatible_variant = detail::subset<T, U> || detail::subset<typename T::variant, U>;

    /** Category containable in the variant.
        e.g. compatible_category<target_variant, source_category>
        or   compatible_category<target_variant> source_category */
    /*template <typename Category, typename Variant>
    concept compatible_category = category::interface<Category> && compatible_variant<decltype(Category::node), Variant>;*/

    template <typename To, compatible_variant<To> From>
    constexpr To variant_cast (From && source) {
        return std::visit([] <typename T> (T && val) -> To { return {util::forward_like<From>(val)}; }, std::forward<From>(source));
    }

    namespace detail {

        template <typename T>
        concept reservable = requires (T a, std::size_t s) {
            a.reserve(s);
        };

    }

    /**
     *  Initialize a container from a single element.
     *  It's usually not easy to do with all the constructor overloads in STL containers.
     */
    template <template <typename> typename Container, typename T>
    constexpr auto init (T && first) {
        Container<std::remove_cvref_t<T>> result;
        // TODO
        /*if constexpr (detail::reservable<Container<T>>) {
            result.reserve(sizeof...(rest) + 1);
        }*/
        result.push_back(std::forward<T>(first));
        //(result.push_back(std::forward<T>(rest)), ...);
        return result;
    }

#if 0 // Just some experiments to implement a "better" visit function.
    template <auto... values, typename F>
    constexpr void for_values (F && f) {
        (f.template operator()<values>(), ...);
    }
    template <auto from, auto to, typename F>
    constexpr void for_range (F && f) {
        using T = std::common_type_t<decltype(from), decltype(to)>;

        [& f] <auto... values> (std::integer_sequence<T, values...>) {
            for_values<(from + values)...>(f);
        } (std::make_integer_sequence<T, from - to>{});
    }
    template <std::size_t start = 0>
    auto visit (auto && f, auto && v) {
        using F = decltype(f);
        using V = decltype(v);
        constexpr std::size_t chunk = 32;
        constexpr std::size_t size  = std::variant_size_v<std::remove_cvref_t<V>>;
        std::size_t           index = v.index();
        /*
        N ->
            case start + N: {
                if constexpr(start + N < vs) {
                    return std::forward<F>(f)(std::get<start + N>(std::forward<V>(v)));
                } else {
                    UNREACHABLE_RETURN(std::forward<F>(f)(std::get<0>(std::forward<V>(v))));
                }                                                                                       \
            }

        */
        for_range<0, chunk>([index, & f, & v] <int i> {
            if (index == start + i)
                return std::forward<F>(f)(std::get<start + i>);
        });
    }
#endif

    namespace detail {

        template <typename, typename...> struct concat;

        template <template <typename...> typename T, typename... First, typename... Second, typename... Rest>
        struct concat<T<First...>, T<Second...>, Rest...> {
            using type = typename concat<T<First..., Second...>, Rest...>::type;
        };

        template <template <typename...> typename T, typename... First, typename... Rest>
        struct concat<T<First...>, T<Rest...>> {
            using type = T<First..., Rest...>;
        };

        template <typename, typename...> struct extend;

        template <template <typename...> typename T, typename... First, typename... Rest>
        struct extend<T<First...>, Rest...> {
            using type = T<First..., Rest...>;
        };

        template <typename, typename...> struct replace;

        template <template <typename...> typename Tpl, typename... From, typename... To>
        struct replace<Tpl<From...>, To...> {
            using type = Tpl<To...>;
        };

        template <typename, typename>
        struct same_template: std::false_type {};

        //template <template <typename...> typename A, template <typename...> typename B, typename... Ts, typename... Us>
        template <template <typename...> typename T, typename... Ts, typename... Us>
        struct same_template<T<Ts...>, T<Us...>>: std::true_type {};

    }

    /** Concatenate template parameters of any type template (of the form template <typename...>). */
    template <typename... Ts>
    using concat = typename detail::concat<Ts...>::type;

    /** Add more template parameters to any type template (of the form template <typename...>). */
    template <typename T, typename... More>
    using extend = typename detail::extend<T, More...>::type;

    // TODO: Decide on remove_cvref and match_cvref on the following two:

    /** Replace all template parameters of any type template (of the form template <typename...>). */
    template <typename T, typename... By>
    using replace = typename detail::replace<std::remove_cvref_t<T>, By...>::type;

    template <typename T, typename U>
    concept same_template = detail::same_template<std::remove_cvref_t<T>, std::remove_cvref_t<U>>::value;

    /** A standard range. */
    template <typename T>
    concept range = requires (T range) { *range.begin(); *range.end(); ++range.begin(); };
    /** A standard range with the .size() method. */
    template <typename T>
    concept sized_range = range<T> && requires (T range) { range.size(); };

    template <typename T>
    concept reservable_range = sized_range<T> && requires (T range, std::size_t size) { range.reserve(size); };

    /** Get value type of any range. */
    template <range T>
    using range_value_type = std::remove_reference_t<decltype(*std::declval<T>().begin())>;

    /** A range containing a specific type. */
    template <typename T, typename U>
    concept range_of = range<T> && std::convertible_to<range_value_type<T>, U>;
    /** A sized range containing a specific type. */
    template <typename T, typename U>
    concept sized_range_of = sized_range<T> && std::convertible_to<range_value_type<T>, U>;

    /** A range containing a type constrained by the given type trait. */
    template <typename T, template <typename> typename Constraint>
    concept constrained_range = range<T> && Constraint<range_value_type<T>>::value;
    /** A sized range containing a type constrained by the given type trait. */
    template <typename T, template <typename> typename Constraint>
    concept constrained_sized_range = sized_range<T> && Constraint<range_value_type<T>>::value;

    /** A standard range with the .push_back() method. */
    template <typename T>
    concept push_back_range = range<T> && requires (T target, range_value_type<T> && val) {
        target.push_back(std::move(val));
    };

#if 0 // The previous attempt at function composition.
    namespace detail {
        /** The first one may be of any arity, the rest must be only unary functions. */
        /*template <typename First>
        constexpr auto compose (First first) {
            return std::move(first);
        }
        template <typename First, typename... Rest>
        constexpr auto compose (First first, Rest... rest) {
            return [first, rest...] <typename... Ts> (Ts &&... args) {
                return compose(rest...)(first(std::forward(args)...));
            };
        }*/
        // Move semantics for non-copyable types:
        template <typename First>
        constexpr auto compose (First && first) {
            return [
                //first = util::copy_or_move(std::forward<First>(first))
                first = std::forward<First>(first)
            ] <typename... Ts> (Ts &&... args) -> decltype(auto) {
                return first(std::forward<Ts>(args)...);
            };
        }
        template <typename First, typename... Rest>
        constexpr auto compose (First && first, Rest &&... rest) {
            //return [first = util::copy_or_move(std::forward<First>(first)), ...rest = util::copy_or_move(std::forward<Rest>(rest))] <typename... Ts> (Ts &&... args) -> decltype(auto) {
            //auto rec = compose(util::copy_or_move(std::forward<Rest>(rest))...);
            return [
                //first = util::copy_or_move(std::forward<First>(first)),
                //rec   = util::copy_or_move(compose(util::copy_or_move(std::forward<Rest>(rest))...))
                first = std::forward<First>(first),
                rec   = compose(std::forward<Rest>(rest)...)
            ] <typename... Ts> (Ts &&... args) -> decltype(auto) {
                return rec(first(std::forward<Ts>(args)...));
            };
        }
        template <typename... Fs>
        using composed = decltype(compose(std::declval<Fs>()...));
    }
#endif

    template <util::range T>
    constexpr bool all (T const & a) {
        for (auto const & e : a) if (!e)
            return false;
        return true;
    }

    /**
     *  Equivalent of std::get for tuples with forwarding (std::froward) of the result regardless of the tuple reference type.
     *  e.g. the first type of tuple<T &&> & remains T && even though the whole tuple is an lvalue.
     */
    template <std::size_t I, util::is<std::tuple> T>
    constexpr decltype(auto) get_forward (T && t) {
        return std::forward<std::tuple_element_t<I, std::remove_reference_t<T>>>(std::get<I>(std::forward<T>(t)));
    }

    namespace detail {

        template <typename F, typename T, std::size_t... I>
        constexpr decltype(auto) apply_forward (F && f, T && t, std::index_sequence<I...>) {
            return std::invoke(std::forward<F>(f), util::get_forward<I>(std::forward<T>(t))...);
        }

    }

    /**
     *  Equivalent of std::apply that forwards references inside of the tuple,
     *  See util::get_forward.
     */
    template <typename F, typename T>
    constexpr decltype(auto) apply_forward (F && f, T && t) {
        return detail::apply_forward (
            std::forward<F>(f),
            std::forward<T>(t),
            std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<T>>>{}
        );
    }

    namespace detail {

        template <std::size_t S, typename... Ts>
        constexpr auto make_indices () {
            constexpr std::size_t sizes [] = {std::tuple_size_v<std::remove_reference_t<Ts>>...};
            using arr_t = std::array<std::size_t, S>;
            std::pair<arr_t, arr_t> ret{};
            for (std::size_t c = 0, i = 0; i < sizeof...(Ts); ++i) for (std::size_t j = 0; j < sizes[i]; ++j, ++c) {
                ret.first[c] = i;
                ret.second[c] = j;
            }
            return ret;
        }

        template <bool Forward, typename F, typename... Tuples, std::size_t... OuterIs, std::size_t... InnerIs>
        constexpr decltype(auto) multi_apply_imp_2 (std::index_sequence<OuterIs...>, std::index_sequence<InnerIs...>, F && f, std::tuple<Tuples...> && t) {
            if constexpr (Forward)
                return std::invoke(std::forward<F>(f), util::get_forward<InnerIs>(util::get_forward<OuterIs>(std::move(t)))...);
            else
                return std::invoke(std::forward<F>(f), std::get<InnerIs>(std::get<OuterIs>(std::move(t)))...);
        }

        template <bool Forward, typename F, typename... Tuples, std::size_t... Is>
        constexpr decltype(auto) multi_apply_imp_1 (std::index_sequence<Is...>, F && f, std::tuple<Tuples...> && t) {
            constexpr auto indices = make_indices<sizeof...(Is), Tuples...>();
            return multi_apply_imp_2<Forward>(std::index_sequence<indices.first[Is]...>{}, std::index_sequence<indices.second[Is]...>{}, std::forward<F>(f), std::move(t));
        }

        template <bool Forward, typename F, typename... Tuples>
        constexpr decltype(auto) multi_apply_imp0 (F && f, Tuples &&... ts) {
            constexpr std::size_t flat_s = (0U + ... + std::tuple_size_v<std::remove_reference_t<Tuples>>);
            if constexpr(flat_s != 0)
                return multi_apply_imp_1<Forward>(std::make_index_sequence<flat_s>{}, std::forward<F>(f), std::forward_as_tuple(std::forward<Tuples>(ts)...));
            else
                return std::forward<F>(f)();
        }

    }

    /**
     *  Taken from https://newbedev.com/applying-multiple-tuples-to-the-same-function-i-e-apply-f-tuples-without-recursion-or-tuple-cat
     *  along with the implementation details above.
     *  Equivalent of std::apply extended to accept multiple tuples.
     *  This takes care of possible copy/move problems that would arise when using the standard std::apply with std::tuple_cat instead.
     */
    template <typename F, typename... Tuples>
    constexpr decltype(auto) multi_apply_forward (F && f, Tuples &&... ts) {
        return detail::multi_apply_imp0<true>(std::forward<F>(f), std::forward<Tuples>(ts)...);
    }

    /** Equivalent of util::multi_apply with forwarding of the tuple items (util::get_forward). */
    template <typename F, typename... Tuples>
    constexpr decltype(auto) multi_apply (F && f, Tuples &&... ts) {
        return detail::multi_apply_imp0<false>(std::forward<F>(f), std::forward<Tuples>(ts)...);
    }

    namespace detail {

        template <typename First, typename... Rest>
        constexpr decltype(auto) head_forward (First && first, Rest &&...) {
            return std::forward<First>(first);
        }

        template <typename First, typename... Rest>
        constexpr auto tail_forward (First &&, Rest &&... rest) {
            return std::forward_as_tuple(std::forward<Rest>(rest)...);
        }

        template <typename First, typename... Rest>
        constexpr auto const & head_tie_const (First const & first, Rest &...) {
            return first;
        }

        template <typename First, typename... Rest>
        constexpr auto & head_tie (First & first, Rest &...) {
            return first;
        }

        template <typename First, typename... Rest>
        constexpr auto tail_tie (First &, Rest &... rest) {
            return std::tie(rest...);
        }

    }

    /** Tuple head with forwarding (std::forward). */
    template <typename... Ts>
    constexpr decltype(auto) head_forward (std::tuple<Ts...> const & t) {
        return util::apply_forward(detail::head_forward<Ts...>, t);
        //return util::get_forward<0>(t);
    }

    /** Tuple tail with forwarding (std::forward). */
    template <typename... Ts>
    constexpr auto tail_forward (std::tuple<Ts...> const & t) {
        return util::apply_forward(detail::tail_forward<Ts...>, t);
    }

    /** Tuple head by reference. (similar to std::tie) */
    template <typename... Ts>
    constexpr auto const & head_tie (std::tuple<Ts...> const & t) {
        return std::apply(detail::head_tie_const<std::add_const_t<Ts>...>, t);
        //return std::get<0>(t);
    }
    template <typename... Ts>
    constexpr auto & head_tie (std::tuple<Ts...> & t) {
        return std::apply(detail::head_tie<Ts...>, t);
        //return std::get<0>(t);
    }

    /** Tuple tail by reference. (similar to std::tie) */
    template <typename... Ts>
    constexpr auto tail_tie (std::tuple<Ts...> const & t) {
        return std::apply(detail::tail_tie<std::add_const_t<Ts>...>, t);
    }
    template <typename... Ts>
    constexpr auto tail_tie (std::tuple<Ts...> & t) {
        return std::apply(detail::tail_tie<Ts...>, t);
    }

    /** std::tie from an existing tuple. */
    template <typename... Ts>
    constexpr auto tie (std::tuple<Ts...> & t) {
        return util::apply_forward(std::tie<Ts...>, t);
    }
    template <typename... Ts>
    constexpr auto tie (std::tuple<Ts...> const & t) {
        return util::apply_forward(std::tie<std::add_const_t<Ts>...>, t);
    }

    namespace detail {

        template <typename Arg>
        constexpr decltype(auto) comp (Arg && arg) {
            return std::forward<Arg>(arg);
        }

        template <typename Arg, typename First, typename... Rest>
        constexpr decltype(auto) comp (Arg && arg, First && first, Rest &&... rest) {
            return comp(first(std::forward<Arg>(arg)), std::forward<Rest>(rest)...);
        }

        template <typename Arg, typename... Fs>
        constexpr decltype(auto) comp_tuple (Arg && arg, std::tuple<Fs...> const & fs) {
            return util::multi_apply(comp<Arg &&, Fs...>, std::forward_as_tuple(std::forward<Arg>(arg)), fs);
        }

        template <typename F>
        constexpr auto wrap (F && f) {
            return [f = std::forward<F>(f)] <typename... Args> (Args... args) {
                return f(std::forward<Args>(args)...);
            };
        }

    }

    /** Compose multiple functions. */
    template <typename... Fs>
    struct compose {
        std::tuple<Fs...> fs;

        constexpr compose (compose const &) = default;
        constexpr compose (compose &&)      = default;

        // At least two functions:
        template <typename First, typename Second, typename... Rest>
        constexpr compose (First && first, Second && second, Rest &&... rest):
            //fs{std::forward_as_tuple (
            fs{std::make_tuple (
                (std::forward<First>(first)),
                (std::forward<Second>(second)),
                (std::forward<Rest>(rest))...
            )} {}

        // One function - cannot be confused with a copy/move constructor:
        template <typename F> requires (util::is_not<std::remove_cvref_t<F>, compose>)
        constexpr compose (F && f):
            //fs{std::forward_as_tuple (
            fs{std::make_tuple (
                (std::forward<F>(f))
            )} {}

        template <typename... Ts>
        constexpr auto operator () (Ts &&... args) const {
            return detail::comp_tuple(util::head_tie(fs)(std::forward<Ts>(args)...), util::tail_tie(fs));
        }
    };
    template <typename First, typename Second, typename... Rest>
    compose(First &&, Second &&, Rest &&...) -> compose<std::remove_cvref_t<First>, std::remove_cvref_t<Second>, std::remove_cvref_t<Rest>...>;
    template <util::is_not<compose> F>
    compose(F &&) -> compose<std::remove_cvref_t<F>>;

    /**
     *  Cast constness away.
     *  Useful with std::as_const to avoid code duplication in const/non-const method overloads.
     */
    template <typename T>
    constexpr T & as_nonconst (T const & value) {
        return const_cast<T &>(value);
    }
    template <typename T>
    constexpr T * as_nonconst (T const * value) noexcept {
        return const_cast<T *>(value);
    }
    /*template <typename T>
    constexpr T & as_nonconst (T & value) noexcept {
        return value;
    }*/
    template <typename T>
    constexpr T * as_nonconst (T * value) noexcept {
        return value;
    }
    template <typename T>
    void as_nonconst (T const &&) = delete;

    /** Can be called with specific arguments. */
    // TODO: Probably useless, std::invocable is practically the same.
    // Yep, it's the same and even more generic because of function pointers.
    // Maybe I should also use std::invoke(f, args...) instead of f(args...) in generic code.
    template <typename F, typename... Args>
    concept callable = requires (F f, Args... args) {
        f(std::forward<Args>(args)...);
    };

    namespace detail {

        template <typename...> struct some;

        template <typename T, typename U, typename... Us>
        struct some<T, U, Us...> {
            static constexpr bool value = std::same_as<T, U> || some<T, Us...>::value;
        };

        template <typename T, typename U>
        struct some<T, U> {
            static constexpr bool value = std::same_as<T, U>;
        };

        template <typename T>
        struct some<T> {
            static constexpr bool value = false;
        };

    }

    /** At least one type is the same. */
    template <typename T, typename... Ts>
    concept some = detail::some<T, Ts...>::value;

    /** None of the types are the same. */
    template <typename T, typename... Ts>
    concept none = !some<T, Ts...>;

    template <typename T, typename V> requires util::is<std::remove_const_t<V>, std::variant>
    constexpr util::match_constness<V, T> * get_nullable (V & v) {
        return std::holds_alternative<T>(v)
            ? std::addressof(std::get<T>(v))
            : nullptr;
    }

    /**
     *  Dereference the optional if it has_value() or keep the raw fallback otherwise.
     *  For short-circuit behavior use the unary overload of this function.
     */
    template <typename T, std::convertible_to<T> U>
    constexpr T coalesce (std::optional<T> const & opt, U && fallback) {
        return opt.has_value()
            ? *opt
            : std::forward<U>(fallback);
    }
    template <typename T, std::convertible_to<T> U>
    constexpr T coalesce (std::optional<T> && opt, U && fallback) {
        return opt.has_value()
            ? *std::move(opt)
            : std::forward<U>(fallback);
    }

    /**
     *  Intended use: `util::coalesce(opt ?: fallback)`
     *  The `opt ?: fallback` expression returns `opt` only when it has_value() and `fallback` otherwise.
     *  This function then dereferences the optional or leaves the raw value.
     */
    template <typename T>
    constexpr T coalesce (std::optional<T> opt) {
        return *opt;
    }
    template <typename T>
    constexpr T coalesce (T fallback) {
        return fallback;
    }

    /** vector::push_back in a free function for convenience is some specific cases. */
    //template <push_back_range T>
    template <typename T>
    T & push_back (range_value_type<T> const & value, T & target) {
        target.push_back(value);
        return target;
    }
    //template <push_back_range T> requires temporary<T>
    template <typename T> requires temporary<T>
    T push_back (range_value_type<T> const & value, T && target) {
        std::move(target).push_back(value);
        return std::move(target);
    }
    //template <push_back_range T>
    template <typename T>
    T & push_back (range_value_type<T> && value, T & target) {
        target.push_back(std::move(value));
        return target;
    }
    //template <push_back_range T> requires temporary<T>
    template <typename T> requires temporary<T>
    T push_back (range_value_type<T> && value, T && target) {
        std::move(target).push_back(std::move(value));
        return std::move(target);
    }

}
