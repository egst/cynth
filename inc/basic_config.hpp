#pragma once

#include <cstddef>
#include <optional>
#include <variant>
#include <array>
#include <vector>
#include <string>
#include <utility>

namespace Cynth {

    using Size = std::size_t;

    using Diff = std::ptrdiff_t;

    using String = std::string;

    template <typename T, Size size>
    using Array = std::array<T, size>;

    template <typename T>
    using Vector = std::vector<T>;

    template <typename T>
    using Optional = std::optional<T>;

    template <typename T, typename U>
    using Pair = std::pair<T, U>;

    template <typename... Ts>
    using Tuple = std::tuple<Ts...>;

    template <typename... Ts>
    using Variant = std::variant<Ts...>;

    using Floating = float;

    using Integral = int;

    // TODO: More levels of debug.
    constexpr bool debug = false;

    // cth_t_Int, ue3_foo, ...
    constexpr char const * global_prefix = "cth";
    constexpr char const * type_prefix = "t";
    constexpr char const * user_prefix = "u";
    constexpr char const * elem_prefix = "e";

}
