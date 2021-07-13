#pragma once

#include "config.hpp"

#include <iostream>

namespace cynth::util {

    struct dostream {
        template <typename T>
        constexpr dostream const & operator << (T const & val) const {
            if constexpr (debug)
                std::cout << val;
            return *this;
        }
    };

    /**
     *  Output to stdout (std::cout) only when util::debug is set to true.
     *  Otherwise there should be no overhead.
     *
     *  util::dout << "this is a test\n";
     */
    constexpr dostream dout;

}
