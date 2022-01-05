#pragma once

#include <cstddef>

#include "context/forward.hpp"

namespace cynth::context {

    struct Branching {
        friend Main;

        inline std::size_t nextBranch () {
            return branch++;
        }

    protected:
        std::size_t branch = 0;
    };

}
