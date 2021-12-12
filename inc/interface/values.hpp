#pragma once

#include <concepts>
#include <optional>
#include <utility>

#include "esl/concepts.hpp"
#include "esl/functional.hpp"
#include "esl/ranges.hpp"

#include "context/cynth.hpp"
#include "interface/forward.hpp"
#include "interface/types.hpp"
#include "sem/declarations.hpp"
#include "sem/values.hpp"

// Completing declarations:
#include "sem/types.hpp"
#include "sem/values.hpp"

namespace cynth::interface {

    // Concepts:

    template <typename T>
    concept value = esl::variant_member<T, sem::CompleteValue::variant>;

    namespace has {

        template <typename T, typename Out>
        concept get = value<T> && requires (T value) {
            { value.get() } -> std::same_as<GetResult<Out>>;
        };

        template <typename T>
        concept valueType = value<T> && requires (T value) {
            { value.valueType() } -> std::same_as<ValueTypeResult>;
        };

        template <typename T, typename U>
        concept convertValue = value<T> && requires (T value, context::Cynth & ctx, U const & other) {
            { value.convertValue(ctx, other) } -> std::same_as<ConversionResult>;
        };

        template <typename T, typename U>
        concept translateValue = value<T> && requires (T value, context::Cynth & ctx, U const & other) {
            { value.translateValue(ctx, other) } -> std::same_as<ValueTranslationResult>;
        };

    }

    // Functions:

    template <typename Out>
    constexpr auto get = esl::overload(
        [] <has::get<Out> T> (T const & value) -> GetResult<Out> {
            return value.get();
        },
        // TODO: Why is this ambiguout without `requires (!...)` while other similar functions are ok?
        [] <value T> (T const &) -> GetResult<Out> requires (!has::get<T, Out>) {
            return esl::result_error{"Value does not contain the requested type."};
        }
    );

    constexpr auto valueType =
        [] (has::valueType auto const & value) -> ValueTypeResult {
            return value.valueType();
        };

    constexpr auto convertValue = [] (context::Cynth & ctx) {
        return esl::overload(
            [&ctx] <value T, type To> (T const & value, To const & to) -> ConversionResult
            requires (has::convertValue<T, To>) {
                return value.convertValue(ctx, to);
            },
            [] (value auto const &, type auto const &) -> ConversionResult {
                return {esl::result_error{"No conversion available."}};
            }
        );
    };

    constexpr auto translateValue = [] (context::Cynth & ctx) {
        return esl::overload(
            [&ctx] <value T, type To> (T const & value, To const & to) -> ValueTranslationResult
            requires (has::translateValue<T, To>) {
                return value.translateValue(ctx, to);
            },
            [] (value auto const &, type auto const &) -> ValueTranslationResult {
                return {esl::result_error{"This value cannot be translated."}};
            }
        );
    };

}
