#pragma once

#include <bit>
#include <concepts>
#include <cstdint>

namespace cynth::driver::asio {

    template <std::convertible_to<double> T>
    double nativeDouble (T from) {
        return from;
    }

    template <typename T>
    double nativeDouble (T from) {
        return *reinterpret_cast<double*>(&from);
    }

    template <std::convertible_to<std::int64_t> T>
    std::int64_t nativeInt64 (T from) {
        return from;
    }

    template <typename T>
    std::int64_t nativeInt64 (T from) {
        if constexpr (std::endian::native == std::endian::little)
            std::swap(from.hi, from.lo);
        return *reinterpret_cast<std::int64_t*>(&from);
    }

}
