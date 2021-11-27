#pragma once

#include <cstddef>

namespace esl {

    namespace detail {

        template <typename T>
        constexpr T powers_of_10 [3 * 3] = {
            1, 10, 100,
            1'000, 10'000, 100'000,
            1'000'000, 10'000'000, 100'000'000/*,
            1'000'000'000, 10'000'000'000, 100'000'000'000,
            1'000'000'000'000, 10'000'000'000'000, 100'000'000'000'000,
            1'000'000'000'000'000, 10'000'000'000'000'000, 100'000'000'000'000'000*/
        };

    }

    /** Integer exponentiation of 10. */
    template <typename T>
    constexpr T pow10 (std::size_t const p) noexcept { return detail::powers_of_10<T>[p]; }

}