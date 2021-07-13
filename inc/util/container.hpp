#pragma once

#include "result.hpp"
#include "util/general.hpp"

namespace cynth::util {

    namespace detail {

        template <typename T>
        struct result_value_type {
            using type = T;
        };

        template <util::is<result> T>
        struct result_value_type<T> {
            using type = typename T::value_type;
        };

    }

    /**
     *  First value of a range. Used for tuples in the AST.
     *  Specialized for a range of results - colapsing potential nested results.
     */
    constexpr auto single = [] <sized_range Container> (Container && values) {
        using value_type  = util::range_value_type<Container>;
        using result_type = typename detail::result_value_type<value_type>::type;
        return values.size() == 1
            ? result<result_type>{*util::make_forwarding_iterator<Container>(values.begin())}
            : result<result_type>{result_error{"Single item expected."}};
    };

    /**
     *  Transform a range of results into a result of a range.
     *  The first error encountered in the original range will form the resulting error.
     *  TODO: Combine all the errors. There is no mechanism for this yet.
     *  range<result<T>> -> range<vector<T>>
     */
    template <util::range Container>
    requires
        util::is<util::range_value_type<Container>, result> &&
        util::push_back_range<Container> // TODO: Generalize for any range.
    constexpr auto unite_results (Container && items) {
        using value_type  = util::range_value_type<Container>;
        using result_type = typename value_type::value_type;

        if constexpr (std::same_as<result_type, void>) {
            for (auto & item : items)
                if (!item.has_value())
                    return result<void>{item.error()};
            return result<void>{};

        } else {
            using container_type = util::replace<Container, result_type>;
            container_type values;
            if constexpr (util::sized_range<Container> && util::reservable_range<container_type>)
                values.reserve(items.size());
            for (auto & item : items)
                if (item.has_value())
                    values.push_back(util::forward_like<Container>(*item));
                else
                    return result<container_type>{item.error()};
            return result{util::forward_like<Container>(values)};
        }
    }

    /**
     *  range<optional<T>> -> optional<vector<T>> (See unite_results.)
     */
    template <util::range Container>
    requires
        util::is<util::range_value_type<Container>, std::optional> &&
        util::push_back_range<Container> // TODO: Generalize for any range.
    constexpr auto unite_optionals (Container && items) {
        using value_type     = util::range_value_type<Container>;
        using result_type    = typename value_type::value_type;
        using container_type = util::replace<Container, result_type>;
        container_type values;
        if constexpr (util::sized_range<Container> && util::reservable_range<container_type>)
            values.reserve(items.size());
        for (auto & item : items)
            if (item.has_value())
                values.push_back(util::forward_like<Container>(*item));
            else
                return std::optional<container_type>{};
        return std::optional{util::forward_like<Container>(values)};
    }

}
