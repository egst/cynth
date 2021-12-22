#pragma once

#include <cstddef>

#include "context/forward.hpp"

namespace cynth::context {

    struct Branching {
        friend Main;

        std::size_t nextBranch ();

    protected:
        std::size_t branch;
    };

}
