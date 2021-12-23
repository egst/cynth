#pragma once

#include "esl/debug.hpp"
#include "esl/macros.hpp"
#include <vector>

#include <optional>

#include "esl/concepts.hpp"
#include "esl/result.hpp"
#include "esl/ranges.hpp"
#include "esl/functional.hpp"
#include "esl/containers.hpp"

namespace cynth {

    namespace detail::util {

        // Not a wrapper:
        template <typename>
        struct ResultMatcher {};

        // A single valued result wrapper:
        template <
            template <typename...> typename W,
            template <typename...> typename R,
            typename T
        > requires (
            // Allowed result wrappers:
            (
                esl::same_template<W<R<T>>, esl::result>           ||
                esl::same_template<W<R<T>>, esl::reference_result> ||
                esl::same_template<W<R<T>>, esl::optional_result>  ||
                esl::same_template<W<R<T>>, std::optional>
            ) &&
            // Must contain a range:
            esl::range<R<T>>
        )
        struct ResultMatcher<W<R<T>>> {
            template <typename U>
            using Wrapper = W<U>;

            template <typename U>
            using Range = R<U>;

            using Value = T;
        };

        // A multiple valued result wrapper:
        template <
            template <typename...> typename W,
            typename T
        > requires (
            // Allowed result wrappers:
            esl::same_template<W<T>, esl::result>           ||
            esl::same_template<W<T>, esl::reference_result> ||
            esl::same_template<W<T>, esl::optional_result>  ||
            esl::same_template<W<T>, std::optional>
        )
        struct ResultMatcher<W<T>> {
            template <typename U>
            using Wrapper = W<U>;

            using Value = T;
        };

    }

    /**
     *  Note: This was especially useful with standard interface functions returning types like vector<result<T>>.
     *  Now I mostly return result<vector<T>> from such functions which simplifies it and makes this function less useful.
     *
     *  Generalizes flexible result wrapper construction.
     *  Accepts (esl::result|std::optional)<esl::range<T>|T> as the Result type, then
     *  takes either a complete result wrapper, a range (if Result type is a wrapper containing a range),
     *  or the contained value directly to construct the requested Result type.
     *  I.e. this constructs a result of a single or multiple values from the full result, a list of values,
     *  a single value, or the first value to form a list of them.
     */
    template <typename Result>
    constexpr auto makeResult = esl::overload(
        // Any kind of result wrapper, that wrapper given:
        // (Forwarding the wrapper.)
        [] <esl::same_template<detail::util::ResultMatcher<Result>::template Wrapper> T> (T value) -> Result {
            return std::forward<T>(value);
        },
        // Wrapper contains a range, that range given:
        // (Constructing the wrapper.)
        [] <typename T> (T value) -> Result
        requires (esl::same_template<T, detail::util::ResultMatcher<Result>::template Range>) {
            return {std::forward<T>(value)};
        },
        // Wrapper contains a range, something other than the range given - assuming it's the value:
        // (Initializing the range and constructing the wrapper.)
        [] <typename T> (T value) -> Result
        requires (!esl::same_template<T, detail::util::ResultMatcher<Result>::template Range>) {
            return {esl::init<detail::util::ResultMatcher<Result>::template Range>(std::forward<T>(value))};
        },
        // Doesn't contain a range, something other than the wrapper given - assuming it's the value:
        // (Constructing the wrapper.)
        [] <typename T> (T value) -> Result {
            return {std::forward<T>(value)};
        }
    );

}
