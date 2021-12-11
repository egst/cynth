#pragma once

#include <concepts>
#include <optional>
#include <utility>

#include "esl/concepts.hpp"
#include "esl/functional.hpp"
#include "esl/ranges.hpp"

#include "context/cynth.hpp"
#include "interface/types.hpp"
#include "sem/declarations.hpp"
#include "sem/values.hpp"
#include "interface/forward.hpp"

// Completing declarations:
#include "sem/compound.hpp"
#include "sem/types.hpp"

namespace cynth::interface {

    // Concepts:

    template <typename Node>
    concept value = esl::variant_member<Node, sem::CompleteValue::variant>;

    template <typename Node>
    concept typed = requires (Node node) {
        { node.type() } -> std::same_as<ValueTypeResult>;
    };

    template <typename Node, typename Out>
    concept valueOf = requires (Node node) {
        { node.get() } -> std::same_as<GetResult<Out>>;
    };

    template <typename Node, typename To>
    concept convertible = requires (Node node, context::Cynth & ctx, To const & to) {
        { node.convert(ctx, to) } -> std::same_as<ConversionResult>;
    };

    // Functions:

    constexpr auto valueType =
        [] (interface::typed auto const & node) -> ValueTypeResult {
            return node.valueType();
        };

    template <typename Out>
    constexpr auto get = esl::overload(
        [] <interface::valueOf<Out> T> (T const & node) -> GetResult<Out> {
            return node.get();
        },
        // TODO: Why is this ambiguout without `requires (!...)` while other similar functions are ok?
        [] <interface::value T> (T const &) -> GetResult<Out> requires (!interface::valueOf<T, Out>) {
            return esl::result_error{"Value does not contain the requested type."};
        }
    );

    constexpr auto convert = [] (context::Cynth & ctx) {
        return esl::overload(
            [&ctx] <interface::value Node, interface::type To> (Node const & node, To const & to) -> ConversionResult
            requires (interface::convertible<Node, To>) {
                return node.convert(ctx, to);
            },
            [] (interface::value auto const &, interface::type auto const &) -> ConversionResult {
                return {esl::result_error{"No conversion available."}};
            }
        );
    };

}
