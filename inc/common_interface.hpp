#pragma once

#include <concepts>

#include "esl/ranges.hpp"
#include "esl/string.hpp"

#include "common_interface_types.hpp"

namespace cynth::interface {

    template <typename Node>
    concept displayable = requires (Node node) {
        { node.display() } -> std::same_as<DisplayResult>;
    };

}

namespace cynth {

    constexpr auto display =
        [] (interface::displayable auto const & a) -> DisplayResult {
            return a.display();
        };

    namespace detail {

        template <typename Node>
        concept displayableTuple = requires (Node node) {
            { display(node) } -> esl::range_of<DisplayResult>;
        };

    }

    constexpr auto displayTuple = [] (detail::displayableTuple auto const & a) -> DisplayResult {
        auto result = display(a);
        return result.size() == 1
            ? result.front()
            : esl::parenthesized(esl::join(", ", display(a)));
    };

}
