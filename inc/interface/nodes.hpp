#pragma once

#include <concepts>

#include "esl/containers.hpp"
#include "esl/functional.hpp"
#include "esl/result.hpp"

#include "context/c.hpp"
#include "interface/forward.hpp"

// Completing forward declarations:
#include "sem/declarations.hpp"
#include "sem/targets.hpp"
#include "sem/types.hpp"

namespace cynth::interface {

    // Concepts:

    /** Any AST node. */
    template <typename T>
    concept node = true;
    // variant_member<T, syn::category::ArrayElement::variant> || ... || variant_member<T, syn::category::Type::variant>
    // syn::category::* would introduce unnecessary dependencies,
    // so I'll keep this requirement purely informative for now.

    namespace has {

        template <typename T>
        concept resolveExpression = node<T> && requires (T node, context::C & ctx, bool translate) {
            { node.resolveExpression(ctx, translate) } -> std::same_as<ExpressionResolutionResult>;
        };

        template <typename T>
        concept resolveArrayElement = node<T> && requires (T node, context::C & ctx) {
            { node.resolveArrayElement(ctx) } -> std::same_as<ExpressionResolutionResult>;
        };

        template <typename T>
        concept resolveStatement = node<T> && requires (T node, context::C & ctx/*, bool translate*/) {
            { node.resolveStatement(ctx/*, translate*/) } -> std::same_as<StatementResolutionResult>;
        };

        template <typename T>
        concept resolveType = node<T> && requires (T node, context::C & ctx) {
            { node.resolveType(ctx) } -> std::same_as<TypeResolutionResult>;
        };

        template <typename T>
        concept resolveDeclaration = node<T> && requires (T node, context::C & ctx) {
            { node.resolveDeclaration(ctx) } -> std::same_as<DeclarationResolutionResult>;
        };

        template <typename T>
        concept resolveRangeDeclaration = node<T> && requires (T node, context::C & ctx) {
            { node.resolveRangeDeclaration(ctx) } -> std::same_as<RangeDeclarationResolutionResult>;
        };

        template <typename T>
        concept resolveTarget = node<T> && requires (T node, context::C & ctx) {
            { node.resolveTarget(ctx) } -> std::same_as<TargetResolutionResult>;
        };

    }

    // Functions:

    constexpr auto resolveExpression (context::C & ctx, bool translate = false) {
        return [&ctx, translate] (has::resolveExpression auto const & node) {
            return node.resolveExpression(ctx, translate);
        };
    }

    constexpr auto resolveArrayElement (context::C & ctx) {
        return [&ctx] (has::resolveArrayElement auto const & node) {
            return node.resolveArrayElement(ctx);
        };
    }

    constexpr auto resolveStatement (context::C & ctx) {
        return esl::overload(
            [&ctx] (has::resolveStatement auto const & node) {
                return node.resolveStatement(ctx);
            },
            [&ctx] (has::resolveExpression auto const & node) -> StatementResolutionResult {
                auto result = esl::unite_results(node.resolveExpression(ctx));
                if (!result)
                    return result.error();
                return {};
            }
        );
    }

    constexpr auto resolveType (context::C & ctx) {
        return [&ctx] (has::resolveType auto const & node) {
            return node.resolveType(ctx);
        };
    }

    constexpr auto resolveDeclaration (context::C & ctx) {
        return [&ctx] (has::resolveDeclaration auto const & node) {
            return node.resolveDeclaration(ctx);
        };
    }

    constexpr auto resolveRangeDeclaration (context::C & ctx) {
        return [&ctx] (has::resolveRangeDeclaration auto const & node) {
            return node.resolveRangeDeclaration(ctx);
        };
    }

    constexpr auto resolveTarget (context::C & ctx) {
        return esl::overload(
            [&ctx] (has::resolveTarget auto const & node) -> TargetResolutionResult {
                return node.resolveTarget(ctx);
            },
            [] (auto const &) -> TargetResolutionResult {
                return esl::result_error{"Assignment target may only be a name, a subscript or any tuple thereof."};
            }
        );
    }

}
