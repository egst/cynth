#pragma once

#include <variant>
#include <vector>

#include <iostream>

namespace cynth::util {

    // std::vector and std::variant might have some performance issues because of some strict standard rules.
    // There are alternatives that are not strictly standard-compliant, but might improve performance.
    // All AST components will use these aliases, but implementation-specific code
    // that doesn't affect any interface may chose to use the standard or other versions depending on the situation.
    // Exapmle: According to the standard, the std::visit function must chose the appropriate overload in O(1) time,
    // which only allows a function pointer based implementation. An altertative that generates if..else statements
    // is not strictly O(1) but provides more options for inlining and other compiler optimizations.

    template <typename... Ts>
    using variant = std::variant<Ts...>;

    template <typename T>
    using vector = std::vector<T>;

    using floating = float;
    using integral = int;

    constexpr bool debug = false;

    struct dostream {
        template <typename T>
        constexpr dostream const & operator << (T const & val) const {
            if constexpr (util::debug)
                std::cout << val;
            return *this;
        }
    };

    /** Output to stdout (std::cout) only when util::debug is set to true.
        Otherwise there should be no overhead. */
    constexpr util::dostream dout;

}
