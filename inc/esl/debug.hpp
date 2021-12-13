#pragma once

#include "esl/config.hpp"

#include <iostream>

namespace esl {

    /**
     *  Place `esl::inspector<Type>{}` or `esl::inspector<decltype(value)>{}`
     *  somewhere to see the corresponding type in an error message.
     *  For less verbose syntax, use the ESL_INSPECT and ESL_INSPECT_TYPE macros from `esl/macros.hpp`.
     */
    template <typename Type> requires (false) struct inspector {};

    struct dostream {
        template <typename T>
        constexpr dostream const & operator << (T const & val) const {
            if constexpr (debug)
                std::cout << val;
            return *this;
        }
    };

    /**
     *  Output to stdout (std::cout) only when esl::debug (in esl/config.hpp) is set to true.
     *  Otherwise there should be no overhead.
     *
     *  util::dout << "this is a test\n";
     */
    constexpr dostream dout;

}
