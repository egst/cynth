#pragma once

#include <algorithm>
#include <bit>
#include <concepts>
#include <cstddef>
#include <utility>
#include <array>
//#include <cstdint>
//#include <type_traits>

#include "asio.hpp"

#include "driver/interface.hpp"
#include "driver/asio/errors.hpp"

namespace cynth::driver::asio {

    namespace detail::write {

        template <typename t>
        std::array<std::byte, sizeof(t)> byteView (t & x) {
            return *reinterpret_cast<std::array<std::byte, sizeof(t)> *>(&x);
        }

        template <typename t>
        std::array<std::byte const, sizeof(t)> byteView (t const & x) {
            return *reinterpret_cast<std::array<std::byte const, sizeof(t)> const *>(&x);
        }

        template <std::size_t, bool> struct SampleWrapper;
        template <> struct SampleWrapper<1, false> { using type = std::int8_t;  };
        template <> struct SampleWrapper<2, false> { using type = std::int16_t; };
        template <> struct SampleWrapper<4, false> { using type = std::int32_t; };
        template <> struct SampleWrapper<8, false> { using type = std::int64_t; };
        template <> struct SampleWrapper<3, false> {
            class type {
            public:
                template <std::integral t> requires (sizeof(t) >= 3)
                type (t const sample) {
                    auto const view = byteView(sample);
                    if constexpr (std::endian::native == std::endian::little)
                        std::copy(view.end() - 2, view.end(), data_.begin());
                    else
                        std::copy(view.rend() - 2, view.rend(), data_.rbegin());
                }
                template <typename t>
                type (t const sample): type{static_cast<std::int32_t>(std::move(sample))} {}
                friend type operator << (type const & spacer, std::size_t const shift) { return {spacer.get() << shift}; }
                std::int32_t get () const {
                    std::int32_t result = std::to_integer<int>(data_[0]) > 0 ? 0 : -1;
                    auto view = byteView(result);
                    if constexpr (std::endian::native == std::endian::little)
                        std::copy(data_.begin(), data_.end(), view.begin() + 1);
                    else
                        std::copy(data_.rbegin(), data_.rend(), view.rbegin() + 1);
                    return result;
                }
                operator std::int32_t () const { return get(); }
            private:
                std::array<std::byte, 3> data_;
            };
        };
        template <> struct SampleWrapper<4, true> { using type = float;  };
        template <> struct SampleWrapper<8, true> { using type = double; };
    }

    // Either a native integral/floating type or an aggregate of bytes.
    template <std::size_t size, bool floating>
    using SampleSpacer = typename detail::write::SampleWrapper<size, floating>::type;

    namespace detail::write {

        template <typename t, std::convertible_to<t> u>
        t limit (t val, u const min, u const max) noexcept {
            if (val > max)
                val = max;
            if (val < min)
                val = min;
            return val;
        }

        // Converts to an appropriate sample type of the given {size} that may be {floating}.
        // TODO: Check overflow in the corner cases.
        template <std::size_t size, bool floating, std::integral in> requires (!floating && size >= sizeof(in)) // integral -> larger integral
        SampleSpacer<size, floating> rangeCast (in const sample) {
            return static_cast<SampleSpacer<size, floating>>(sample) << (8 * (size - sizeof(in)));
        }
        template <std::size_t size, bool floating, std::integral in> requires (!floating && size <  sizeof(in)) // integral -> smaller integral
        SampleSpacer<size, floating> rangeCast (in const sample) {
            return static_cast<SampleSpacer<size, floating>>(sample >> (8 * (sizeof(in) - size)));
        }
        template <std::size_t size, bool floating, std::floating_point in> requires (!floating) // floating -> integral
        SampleSpacer<size, floating> rangeCast (in const sample) {
            return static_cast<SampleSpacer<size, floating>>(limit(sample, -1, 1) * (1ull << (8 * size - 1)));
        }
        template <std::size_t size, bool floating, std::integral in> requires (floating)        // integral -> floating
        SampleSpacer<size, floating> rangeCast (in const sample) {
            return static_cast<SampleSpacer<size, floating>>(std::int64_t{sample} / (1ull << (8 * sizeof(in) - 1)));
        }
        template <std::size_t size, bool floating, std::floating_point in> requires (floating)  // floating -> floating
        SampleSpacer<size, floating> rangeCast (in const sample) {
            return static_cast<SampleSpacer<size, floating>>(limit(sample, -1, 1));
        }

        template <typename T>
        T switch_endianness (T sample) {
            auto view = byteView(sample);
            std::reverse(view.begin(), view.end());
            return sample;
        }

        /** Switch endianness only if it doesn't match the curent system's endianness. */
        template <std::endian endianness, typename T>
        T match_endianness (T const sample) {
            if (endianness == std::endian::native)
                return std::move(sample);
            else
                return switch_endianness(std::move(sample));
        }

        template <std::size_t size, bool floating, std::endian endianness>
        void write (void * const buffer, std::size_t const pos, Sample const sample) {
            reinterpret_cast<SampleSpacer<size, floating> *>(buffer)[pos] =
                match_endianness<endianness>(rangeCast<size, floating>(sample));
        }

    }

    inline Status write (ASIOSampleType const type, void * const buffer, std::size_t const pos, Sample const sample) {
        switch (type) {
            // < size, floating, little endian >
            case ASIOSTInt16MSB:   detail::write::write< 2, false, std::endian::big    >(buffer, pos, sample); break;
            case ASIOSTInt16LSB:   detail::write::write< 2, false, std::endian::little >(buffer, pos, sample); break;
            case ASIOSTInt24MSB:   detail::write::write< 3, false, std::endian::big    >(buffer, pos, sample); break;
            case ASIOSTInt24LSB:   detail::write::write< 3, false, std::endian::little >(buffer, pos, sample); break;
            case ASIOSTInt32MSB:   detail::write::write< 4, false, std::endian::big    >(buffer, pos, sample); break;
            case ASIOSTInt32LSB:   detail::write::write< 4, false, std::endian::little >(buffer, pos, sample); break;
            case ASIOSTFloat32MSB: detail::write::write< 4, true,  std::endian::big    >(buffer, pos, sample); break;
            case ASIOSTFloat32LSB: detail::write::write< 4, true,  std::endian::little >(buffer, pos, sample); break;
            case ASIOSTFloat64MSB: detail::write::write< 8, true,  std::endian::big    >(buffer, pos, sample); break;
            case ASIOSTFloat64LSB: detail::write::write< 8, true,  std::endian::little >(buffer, pos, sample); break;
            default:               return Status::unsupportedSystem;
        }
        return Status::ok;
    }

}
