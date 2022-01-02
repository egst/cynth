#pragma once

#include <array>
#include <cstddef>
#include <utility>

namespace esl {

    namespace detail {

        template <typename, typename> struct pow10_seq;
        template <typename T, int... REPEAT>
        struct pow10_seq<T, std::index_sequence<REPEAT...>> {
            constexpr static T value = (1 * ... * (REPEAT, static_cast<T>(10)));
        };

        template <typename T, std::size_t EXP>
        constexpr T pow10_const () {
            return pow10_seq<T, std::make_index_sequence<EXP>>::value;
        }

        template <typename, typename> struct pow10_init_seq;
        template <typename T, auto... EXPS>
        struct pow10_init_seq<T, std::index_sequence<EXPS...>> {
            constexpr static std::array<T, sizeof...(EXPS)> value = {pow10_const<T, EXPS>()...};
        };

        template <typename T, std::size_t EXP>
        constexpr auto pow10_init () {
            return pow10_init_seq<T, std::make_index_sequence<EXP>>::value;
        }

        /** Array of powers of ten up to 10^9 */
        template <typename T>
        constexpr auto pow10_list = pow10_init<T, 8>();
        // TODO: Choose the max power depending on T. It's 9 only for 32bit unsigned integers,
        // but for smaller types it won't compile (overflow is checked in compile-time expressions)
        // and for larger types it won't be enough.
        // TODO: Check if REPEAT value 8 actually means 10^9... I got kinda lost here.

    }

    /** Integer exponentiation of 10. */
    template <typename T = std::size_t>
    constexpr T pow10 (unsigned exp) {
        return detail::pow10_list<T>[exp];
    }

}
