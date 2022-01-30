#pragma once

#include <concepts>
#include <optional>
#include <type_traits>
#include <utility>

#include "esl/concepts.hpp"
#include "esl/functional.hpp"
#include "esl/iterator.hpp"
#include "esl/ranges.hpp"
#include "esl/result.hpp"
#include "esl/type_manip.hpp"

namespace esl {

    /**
     *  Initialize a container from a single element.
     *  It's usually not at all straightforward with all the constructor overloads in STL containers.
     *  TODO: Generalize to any number of elements and reserve.
     */
    template <template <typename...> typename Container>
    constexpr auto init = [] <typename T> (T && first) {
        Container<std::remove_cvref_t<T>> result;
        /*if constexpr (detail::misc::reservable_range<Container<T>>) {
            result.reserve(sizeof...(rest) + 1);
        }*/
        result.push_back(std::forward<T>(first));
        //(result.push_back(std::forward<T>(rest)), ...);
        return result;
    };

    /** Concat using the standart push method with variadic value parameters. */
    constexpr auto push_cat =
        [] <esl::back_pushable_range R, std::same_as<esl::range_value_type<R>>... Ts> (R && r, Ts &&... vals) -> R {
            R c = std::forward<R>(r);
            (c.push(vals), ...);
            return c;
        };

    namespace detail::containers {

        /** Concat using the standart insert method. */
        //template <typename T, template <typename...> typename V>
        template <esl::insertable_range First, esl::insertable_range Second, esl::insertable_range... Rest> requires (
            (esl::same_but_cvref<First,  Rest> && ...) &&
            (esl::same_but_cvref<Second, Rest> && ...)
        ) First insert_cat (First && first, Second && second, Rest &&... rest) {
            first.insert(
                first.end(),
                esl::make_forwarding_iterator<Second>(second.begin()),
                esl::make_forwarding_iterator<Second>(second.end())
            );

            if constexpr (sizeof...(rest) >= 1)
                insert_cat(std::forward<First>(first), std::forward<Rest>(rest)...);

            return std::forward<First>(first);
        }

        /** Concat using the simplified insert_back method in tiny_vector. (Until I implement the standard insert.) */
        //template <typename T, template <typename...> typename V>
        template <
            esl::back_insertable_range First,
            esl::back_insertable_range Second,
            esl::back_insertable_range... Rest
        > requires (
            (esl::same_but_cvref<First,  Rest> && ...) &&
            (esl::same_but_cvref<Second, Rest> && ...)
        ) First insert_back_cat (First && first, Second && second, Rest &&... rest) {
            first.insert_back(
                esl::make_forwarding_iterator<Second>(second.begin()),
                esl::make_forwarding_iterator<Second>(second.end())
            );

            if constexpr (sizeof...(rest) >= 1)
                insert_back_cat(std::forward<First>(first), std::forward<Rest>(rest)...);

            return std::forward<First>(first);
        }

        // Note: Exposed as lambda functions to allow passing them to other functions without template parameters.
    }

    /** Concat using the standart insert method or the simplified insert_back method. */
    constexpr auto insert_cat = esl::overload(
        [] <esl::insertable_range... Rs> (Rs &&... ranges) {
            return detail::containers::insert_cat(std::forward<Rs>(ranges)...);
        },
        [] <esl::back_insertable_range... Rs> (Rs &&... ranges) {
            return detail::containers::insert_back_cat(std::forward<Rs>(ranges)...);
        }
    );

    /** Concat/flatten a range of ranges using the standard insert methor or the simplified insert_back method. */
    constexpr auto insert_nested_cat = esl::overload(
        [] <esl::range R> (R && range) requires (esl::insertable_range<esl::range_value_type<R>>) {
            esl::range_value_type<R> result;
            for (auto && nested: std::forward<R>(range))
                result.insert(
                    result.end(),
                    esl::make_forwarding_iterator<R>(nested.begin()),
                    esl::make_forwarding_iterator<R>(nested.end())
                );
            return result;
        },
        [] <esl::range R> (R && range) requires (esl::back_insertable_range<esl::range_value_type<R>>) {
            esl::range_value_type<R> result;
            for (auto && nested: std::forward<R>(range))
                result.insert_back(
                    esl::make_forwarding_iterator<R>(nested.begin()),
                    esl::make_forwarding_iterator<R>(nested.end())
                );
            return result;
        }
    );

    /** vector::push_back in a free function for convenience is some specific cases. */
    //template <esl::push_bach_range T>
    template <typename T>
    T & push_back (esl::range_value_type<T> const & value, T & target) {
        target.push_back(value);
        return target;
    }

    //template <esl::push_bach_range T> requires (esl::temporary<T>)
    template <typename T> requires (esl::temporary<T>)
    T push_back (esl::range_value_type<T> const & value, T && target) {
        std::move(target).push_back(value);
        return std::move(target);
    }

    //template <esl::push_bach_range T>
    template <typename T>
    T & push_back (esl::range_value_type<T> && value, T & target) {
        target.push_back(std::move(value));
        return target;
    }

    //template <esl::push_bach_range T> requires (esl::temporary<T>)
    template <typename T> requires (esl::temporary<T>)
    T push_back (esl::range_value_type<T> && value, T && target) {
        std::move(target).push_back(std::move(value));
        return std::move(target);
    }

    /**
     *  An equivalent of std::for_each that supports zip-like iteration over two containers.
     */
    template <typename T, typename U, typename F>
    constexpr F for_each (T first1, T last1, U first2, F f) {
        for (; first1 != last1; ++first1, ++first2)
            f(*first1, *first2);
        return f;
    }

    template <typename T, typename F>
    constexpr F for_each (T first, T last, F f) {
        for (; first != last; ++first)
            f(*first);
        return f;
    }

    namespace detail::container {

        template <typename T>
        struct result_value_type {
            using type = T;
        };

        template <esl::same_template<esl::result> T>
        struct result_value_type<T> {
            using type = typename T::value_type;
        };

    }

    /**
     *  First value of a range. Used for tuples in the AST.
     *  Specialized for a range of results - colapsing potential nested results.
     */
    constexpr auto single = [] <esl::sized_range Container> (Container && values) {
        using value_type  = esl::range_value_type<Container>;
        using result_type = typename detail::container::result_value_type<value_type>::type;
        return values.size() == 1
            ? esl::result<result_type>{*esl::make_forwarding_iterator<Container>(values.begin())}
            : esl::result<result_type>{esl::result_error{"Single item expected."}};
    };

    /**
     *  Transform a range of results into a result of a range.
     *  The first error encountered in the original range will form the resulting error.
     *  TODO: Combine all the errors. There is no mechanism for this yet.
     *  range<result<T>> -> result<range<T>>
     */
    constexpr auto unite_results = [] <esl::range Container> (Container && items)
        requires (
            esl::same_template<esl::range_value_type<Container>, esl::result> &&
            esl::back_pushable_range<Container> // TODO: Generalize for any range.
        ) {
            using value_type  = esl::range_value_type<Container>;
            using result_type = typename value_type::value_type;

            if constexpr (std::same_as<result_type, void>) {
                for (auto & item: items)
                    if (!item.has_value())
                        return esl::result<void>{item.error()};
                return esl::result<void>{};

            } else {
                using container_type = esl::replace<Container, result_type>;
                container_type values;
                if constexpr (esl::sized_range<Container> && esl::reservable_range<container_type>)
                    values.reserve(items.size());
                for (auto & item: items)
                    if (item.has_value())
                        values.push_back(esl::forward_like<Container>(*item));
                    else
                        return esl::result<container_type>{item.error()};
                return esl::result{esl::forward_like<Container>(values)};
            }
        };

    /**
     *  range<optional_result<T>> -> result<range<optional<T>>>
     */
    template <esl::range Container>
    requires
        esl::same_template<esl::range_value_type<Container>, optional_result> &&
        esl::back_pushable_range<Container> // TODO: Generalize for any range.
    constexpr auto unite_optional_results (Container && items) {
        using value_type     = esl::range_value_type<Container>;
        using result_type    = typename value_type::value_type;
        using container_type = esl::replace<Container, std::optional<result_type>>;

        container_type values;
        if constexpr (esl::sized_range<Container> && esl::reservable_range<container_type>)
            values.reserve(items.size());
        for (auto & item: items)
            if (item.has_value())
                values.push_back(esl::forward_like<Container>(*item));
            else if (item.empty())
                //values.emplace_back(std::nullopt);
                values.push_back(std::optional<result_type>{});
            else // if item.has_error()
                return optional_result<container_type>{item.error()};
        return optional_result{esl::forward_like<Container>(values)};
    }

    /**
     *  (range<optional_result<T>>, empty_error) -> result<range<T>>
     */
    template <esl::range Container>
    requires
        esl::same_template<esl::range_value_type<Container>, optional_result> &&
        esl::back_pushable_range<Container> // TODO: Generalize for any range.
    constexpr auto unite_optional_results (Container && items, result_error const & empty_error) {
        using value_type     = esl::range_value_type<Container>;
        using result_type    = typename value_type::value_type;
        using container_type = esl::replace<Container, result_type>;

        container_type values;
        if constexpr (esl::sized_range<Container> && esl::reservable_range<container_type>)
            values.reserve(items.size());
        for (auto & item: items)
            if (item.has_value())
                values.push_back(esl::forward_like<Container>(*item));
            else if (item.empty())
                return optional_result<container_type>{empty_error};
            else // if item.has_error()
                return optional_result<container_type>{item.error()};
        return optional_result{esl::forward_like<Container>(values)};
    }

    /**
     *  range<optional<T>> -> optional<vector<T>>
     */
    template <esl::range Container>
    requires
        esl::same_template<esl::range_value_type<Container>, std::optional> &&
        esl::back_pushable_range<Container> // TODO: Generalize for any range.
    constexpr auto unite_optionals (Container && items) {
        using value_type     = esl::range_value_type<Container>;
        using result_type    = typename value_type::value_type;
        using container_type = esl::replace<Container, result_type>;
        container_type values;
        if constexpr (esl::sized_range<Container> && esl::reservable_range<container_type>)
            values.reserve(items.size());
        for (auto & item: items)
            if (item.has_value())
                values.push_back(esl::forward_like<Container>(*item));
            else
                return std::optional<container_type>{};
        return std::optional{esl::forward_like<Container>(values)};
    }

}
