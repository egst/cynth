#pragma once

#include "util/tiny_vector.hpp"

#include <variant>
#include <vector>

#include <iostream>

namespace cynth {

    // The standard variant will probably stay in use here, but I'll keep it configurable just in case.
    // However, the standard visit function might be replaced by a non-standard one (TODO).
    // std::visit has O(1) time complexity, but involves indirection (basically a lookup table).
    // The visit function might also be imlemented with automatically generated if..else statements
    // which would increase the time complexity to O(n) for n types in a variant,
    // but would involve no indirection and could be highly optimized by the compiler.
    template <typename... Ts>
    using variant = std::variant<Ts...>;

    // All values and types are represented as a tuple in the Cynth language.
    // For simpler implementation, they are represented by variable-length container even in the case of a single value.
    // For this reason, I will use some optimized variation of std::vector.
    // I will experiment with different variations until I find the optimal one.
    // For now, I'm using an optimization which holds an std::optional for the first value (no dynamic allocation)
    // and an std::vector for the rest of the values (so the dynamic allocation kicks in only for 2 and more items).
    // I'll call this a "tiny vector". Another option would be to hold a statically-sized std::array (no dynamic allocation)
    // for a first few values (e.g. 4 or something like that) and an std::vector for the rest.
    // I'll call this a "small vector" and its static size will be configurable at compile time.
    template <typename T>
    using tuple_vector = util::tiny_vector<T>;

    // Strings will be rarely used in the language - only for labeling and commenting on some components in the resulting GUI,
    // so some optimization for such simple static non-modifiable strings could be used here.
    using string = std::string;

    using floating = float;
    using integral = int;

    constexpr bool debug = false;

}
