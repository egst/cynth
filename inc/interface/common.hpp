#pragma once

#include <concepts>

#include "esl/ranges.hpp"
#include "esl/string.hpp"

#include "interface/forward.hpp"

namespace cynth::interface {

    // Concepts:

    template <typename Node>
    concept displayable = requires (Node node) {
        { node.display() } -> std::same_as<DisplayResult>;
    };

    // Functions:

    constexpr auto display =
        [] (interface::displayable auto const & a) -> DisplayResult {
            return a.display();
        };

    namespace detail::common {

        template <typename Node>
        concept displayableTuple = requires (Node node) {
            { display(node) } -> esl::range_of<DisplayResult>;
        };

    }

    constexpr auto displayTuple = [] (detail::common::displayableTuple auto const & a) -> DisplayResult {
        auto result = display(a);
        return result.size() == 1
            ? result.front()
            : esl::parenthesized(esl::join(", ", display(a)));
    };

}