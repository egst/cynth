#pragma once

#include "esl/ranges.hpp"

namespace esl {

    template <esl::range T>
    constexpr bool all (T const & a) {
        for (auto const & e: a) if (!e)
            return false;
        return true;
    }

}
