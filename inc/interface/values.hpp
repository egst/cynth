#pragma once

#include <concepts>
#include <optional>
#include <utility>

#include "esl/concepts.hpp"
#include "esl/functional.hpp"
#include "esl/ranges.hpp"

#include "context/main.hpp"
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

    template <typename T>
    concept simpleValue =
        esl::same_but_cvref<T, sem::value::Bool> ||
        esl::same_but_cvref<T, sem::value::Int>  ||
        esl::same_but_cvref<T, sem::value::Float>;

    template <typename T>
    concept numericValue =
        esl::same_but_cvref<T, sem::value::Int>  ||
        esl::same_but_cvref<T, sem::value::Float>;

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

        // TODO: There are now actually no values that don't have a directly stated value type.
        // So maybe this shold be removed.
        template <typename T>
        concept valueType = value<T> && requires (T value) {
            //{ value.valueType() } -> std::same_as<ValueTypeResult>;
            value.valueType();
        };

        /*
        template <typename T, typename To>
        concept convertSimpleValue = value<T> && requires (T value, To const & other) {
            { value.convertValue(other) } -> std::same_as<ConversionResult<To>>;
        };
        */

        /*
        template <typename T, typename To>
        concept convertValue = value<T> && requires (T value, context::Main & ctx, To const & other) {
            { value.convertValue(ctx, other) } -> std::same_as<ConversionResult<To>>;
        };
        */

        template <typename T>
        concept translateValue = value<T> && requires (T value, context::Main & ctx) {
            { value.translateValue(ctx) } -> std::same_as<ValueTranslationResult>;
        };

    }

    // Functions:

    template <typename Out>
    constexpr auto get = esl::overload(
        [] <has::get<Out> T> (T const & value) -> esl::result<GetResult<Out>> {
            return value.get();
        },
        // TODO: Why is this ambiguout without `requires (!...)` while other similar functions are ok?
        [] <value T> (T const &) -> esl::result<GetResult<Out>> requires (!has::get<T, Out>) {
            return esl::result_error{"Value does not contain the requested type."};
        }
    );

    constexpr auto valueType = esl::overload(
        [] <has::directValueType T> (T const & value) -> ValueTypeResult /*requires (!has::valueType<T>)*/ {
            //return sem::CompleteType{T::valueType};
            return sem::CompleteType{value.valueType};
        }
        /*
        [] <has::valueType T> (T const & value) -> ValueTypeResult requires (!has::directValueType<T>) {
            return value.valueType();
        }
        */
    );

    /*
    constexpr auto convertValueTo (context::Main & ctx) {
        return [&ctx] <type To> (To const & to) {
            return esl::overload(
                [&to] <value T> (T const & value) -> ConversionResult<To>
                requires (has::convertSimpleValue<T, To>) {
                    return value.convertSimpleValue(to);
                },
                [&ctx, &to] <value T> (T const & value) -> ConversionResult<To>
                requires (has::convertValue<T, To> && !has::convertSimpleValue<T, To>) {
                    return value.convertValue(ctx, to);
                },
                [] (value auto const &) -> ConversionResult<To> {
                    return {esl::result_error{"No conversion available."}};
                }
            );
        };
    };

    constexpr auto convertValue (context::Main & ctx) {
        return esl::overload(
            [] <value T, type To> (T const & value, To const & to) -> DynamicConversionResult
            requires (has::convertSimpleValue<T, To>) {
                auto result = value.convertValue(to);
                if (!result) return result.error();
                return {sem::CompleteValue{*result}};
            },
            [&ctx] <value T, type To> (T const & value, To const & to) -> DynamicConversionResult
            requires (has::convertValue<T, To> && !has::convertSimpleValue<T, To>) {
                auto result = value.convertValue(ctx, to);
                if (!result) return result.error();
                return {sem::CompleteValue{*result}};
            },
            [] (value auto const &, type auto const &) -> DynamicConversionResult {
                return {esl::result_error{"No conversion available."}};
            }
        );
    };

    constexpr auto convertSimpleValueTo =
        [] <type To> (To const & to) {
            return esl::overload(
                [&to] <value T> (T const & value) -> ConversionResult<To>
                requires (has::convertSimpleValue<T, To>) {
                    return value.convertValue(to);
                },
                [] (value auto const &) -> ConversionResult<To> {
                    return {esl::result_error{"No conversion available."}};
                }
            );
        };
    // TODO: convertSimpleValue?
    */

    inline auto translateValue (context::Main & ctx) {
        return esl::overload(
            [&ctx] <value T> (T const & value) -> ValueTranslationResult
            requires (has::translateValue<T>) {
                return value.translateValue(ctx);
            },
            [] (value auto const &) -> ValueTranslationResult {
                return {esl::result_error{"This value cannot be translated."}};
            }
        );
    }

}
