#pragma once

#include <concepts>

#include "esl/ranges.hpp"
#include "esl/string.hpp"

#include "interface/forward.hpp"

namespace cynth::interface {

    // Concepts:

    template <typename T>
    concept any = true; // This will probably stay unconstrained, but I'll keep it for documentation purposes.

    namespace has {

        template <typename T>
        concept display = requires (T target) {
            { target.display() } -> std::same_as<DisplayResult>;
        };

    }

    // Functions:

    constexpr auto display =
        [] (has::display auto const & a) -> DisplayResult {
            return a.display();
        };

    namespace detail::common {

        template <typename T>
        concept displayableTuple = requires (T target) {
            { display(target) } -> esl::range_of<DisplayResult>;
        };

    }

    constexpr auto displayTuple = [] (detail::common::displayableTuple auto const & a) -> DisplayResult {
        auto result = display(a);
        return result.size() == 1
            ? result.front()
            : esl::parenthesized(esl::join(", ", display(a)));
    };

}
