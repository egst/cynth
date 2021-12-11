#pragma once

#include <concepts>
#include <optional>
#include <string>

#include "esl/functional.hpp"
#include "esl/result.hpp"

#include "context/c.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"

// Completing forward declarations:
#include "sem/compound.hpp"

namespace cynth::interface {

    template <typename Node>
    concept translatableExpression = requires (Node node, context::C & ctx) {
        { node.translateExpression(ctx) } -> std::same_as<ExpressionTranslationResult>;
    };

    template <typename Node>
    concept translatableDefinition = requires (
        Node node,
        context::C & ctx,
        std::string const & definition,
        bool compval
    ) {
        { node.translateDefinition(ctx, definition, compval) } -> std::same_as<DefinitionTranslationResult>;
    };

    template <typename Node, typename To>
    concept translatableConversion = requires (Node node, context::C & ctx, To const & to) {
        { node.translateConversion(ctx, to) } -> std::same_as<ExpressionTranslationResult>;
    };

    /** Use nullopt definition argument for a declaration. */
    constexpr auto translateDefinition (
        context::C & ctx,
        std::optional<std::string> const & definition,
        bool compval
    ) {
        return esl::overload(
            [&ctx, &definition, compval] (interface::translatableDefinition auto const & node)
            -> DefinitionTranslationResult {
                return node.translateDefinition(ctx, definition, compval);
            },
            [] (interface::type auto const & node) -> DefinitionTranslationResult {
                return esl::result_error{"A definition of this type cannot be directly translated."};
            }
        );
    }

    constexpr auto translateExpression (context::C & ctx) {
        return esl::overload(
            [&ctx] (interface::translatableExpression auto const & node) -> ExpressionTranslationResult {
                return node.translateExpression(ctx);
            },
            [] (interface::value auto const & node) -> ExpressionTranslationResult {
                return esl::result_error{"This value cannot be directly translated to an expression."};
            }
        );
    }

}
