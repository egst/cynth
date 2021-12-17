#pragma once

#include <concepts>
#include <optional>
#include <utility>

#include "esl/concepts.hpp"
#include "esl/functional.hpp"
#include "esl/ranges.hpp"

#include "context/c.hpp"
#include "interface/forward.hpp"
#include "interface/types.hpp"
#include "sem/compound.hpp"
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
        concept directValueType = value<T> && requires (T value) {
            // Note: Both static and non-static `valueType` members satisfy this concept.
            // It seems there is no straightforward way to check for one of them specifically,
            // but in the end it doesn't really matter, because both are accessible
            // with the "usual" member access `.`.
            //{ T::valueType } -> type;
            { value.valueType } -> type;
        };

        template <typename T>
        concept valueType = value<T> && requires (T value) {
            //{ value.valueType() } -> std::same_as<ValueTypeResult>;
            value.valueType();
        };

        template <typename T, typename U>
        concept convertValue = value<T> && requires (T value, context::C & ctx, U const & other) {
            { value.convertValue(ctx, other) } -> std::same_as<ConversionResult>;
        };

        template <typename T>
        concept translateValue = value<T> && requires (T value, context::C & ctx) {
            { value.translateValue(ctx) } -> std::same_as<ValueTranslationResult>;
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

    constexpr auto valueType = esl::overload(
        [] <has::directValueType T> (T const & value) -> ValueTypeResult requires (!has::valueType<T>) {
            //return sem::CompleteType{T::valueType};
            return sem::CompleteType{value.valueType};
        },
        [] <has::valueType T> (T const & value) -> ValueTypeResult requires (!has::directValueType<T>) {
            return value.valueType();
        }
    );

    // TODO: Do I need this?
    // Or perhaps `convertValue`'s functionality could be included in `translateConversion` (in interface/types)?
    inline auto convertValue (context::C & ctx) {
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

    inline auto translateValue (context::C & ctx) {
        return esl::overload(
            [&ctx] <value T> (T const & value) -> ValueTranslationResult
            requires (has::translateValue<T>) {
                return value.translateValue(ctx);
            },
            [] (value auto const &) -> ValueTranslationResult {
                return {esl::result_error{"This value cannot be translated."}};
            }
        );
    };

}
