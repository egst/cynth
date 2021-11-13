#pragma once

#include "lift.hpp"
#include "common_interface_types.hpp"
#include "util/general.hpp"
#include "util/string.hpp"

#include <concepts>
#include <string>

namespace cynth::interface {

    template <typename Node>
    concept displayable = requires (Node node) {
        { node.display() } -> std::same_as<display_result>;
    };

}

namespace cynth {

    constexpr auto display = lift::any {
        [] <interface::displayable Node> (Node const & a) -> display_result {
            return a.display();
        }
    };

    namespace detail {

        template <typename Node>
        concept displayable_tuple = requires (Node node) {
            { display(node) } -> util::range_of<display_result>;
        };

    }

    constexpr auto display_tuple = [] <detail::displayable_tuple Tuple> (Tuple const & a) -> display_result {
        auto result = display(a);
        return result.size() == 1
            ? result.front()
            : util::parenthesized(util::join(", ", display(a)));
    };

}
