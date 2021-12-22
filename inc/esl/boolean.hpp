#pragma once

#include "esl/ranges.hpp"

namespace esl {

    // TODO: Come up with better names.

    template <esl::range T>
    constexpr bool all (T const & a) {
        for (auto const & e: a) if (!e)
            return false;
        return true;
    }

    template <esl::range T>
    constexpr bool none (T const & a) {
        for (auto const & e: a) if (e)
            return false;
        return true;
    }

    template <bool... Bs>
    constexpr bool every = (Bs && ...);

    template <bool... Bs>
    constexpr bool some = (Bs || ...);

}
