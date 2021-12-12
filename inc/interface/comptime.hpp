#pragma once

#include <concepts>

#include "esl/containers.hpp"
#include "esl/functional.hpp"
#include "esl/result.hpp"

#include "context/cynth.hpp"
#include "interface/forward.hpp"

// Completing forward declarations:
#include "sem/declarations.hpp"
#include "sem/targets.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"

namespace cynth::interface {

    // Concepts:

    /** Any AST node. */
    template <typename T>
    concept node = true; // Unconstrained for now. (Could be implemented with esl::variant_member for every category.)
    // Probably won't be used, but I'll keep it for documentation purposes.

    namespace has {

        template <typename T>
        concept resolveExpression = requires (T node, context::Cynth & ctx) {
            { node.resolveExpression(ctx) } -> std::same_as<ExpressionResolutionResult>;
        };

        template <typename T>
        concept resolveStatement = requires (T node, context::Cynth & ctx, bool translate) {
            { node.resolveStatement(ctx, translate) } -> std::same_as<StatementResolutionResult>;
        };

        template <typename T>
        concept resolveType = requires (T node, context::Cynth & ctx) {
            { node.resolveType(ctx) } -> std::same_as<TypeResolutionResult>;
        };

        template <typename T>
        concept resolveArrayElement = requires (T node, context::Cynth & ctx) {
            { node.resolveArrayElement(ctx) } -> std::same_as<ExpressionResolutionResult>;
        };

        template <typename T>
        concept resolveDeclaration = requires (T node, context::Cynth & ctx) {
            { node.resolveDeclaration(ctx) } -> std::same_as<DeclarationResolutionResult>;
        };

        template <typename T>
        concept resolveRangeDeclaration = requires (T node, context::Cynth & ctx) {
            { node.resolveRangeDeclaration(ctx) } -> std::same_as<RangeDeclarationResolutionResult>;
        };

        template <typename T>
        concept resolveTarget = requires (T node, context::Cynth & ctx) {
            { node.resolveTarget(ctx) } -> std::same_as<TargetResolutionResult>;
        };

    }

    // Functions:

    constexpr auto resolveStatement (context::Cynth & ctx) {
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

    constexpr auto resolveExpression (context::Cynth & ctx, bool translate) {
        return [&ctx, translate] <has::resolveExpression T> (T const & node) {
            return node.resolveExpression(ctx, translate);
        };
    }

    constexpr auto resolveType (context::Cynth & ctx) {
        return [&ctx] (has::resolveType auto const & node) {
            return node.resolveType(ctx);
        };
    }

    constexpr auto resolveArrayElement (context::Cynth & ctx) {
        return [&ctx] (has::resolveArrayElement auto const & node) {
            return node.resolveArrayElement(ctx);
        };
    }

    constexpr auto resolveDeclaration (context::Cynth & ctx) {
        return [&ctx] (has::resolveDeclaration auto const & node) {
            return node.resolveDeclaration(ctx);
        };
    }

    constexpr auto resolveRangeDeclaration (context::Cynth & ctx) {
        return [&ctx] (has::resolveRangeDeclaration auto const & node) {
            return node.resolveRangeDeclaration(ctx);
        };
    }

    constexpr auto resolveTarget (context::Cynth & ctx) {
        return esl::overload(
            [&ctx] (has::resolveTarget auto const & node) -> TargetResolutionResult {
                return node.resolveTarget(ctx);
            },
            [] (auto const &) -> TargetResolutionResult {
                return esl::result_error{"Assignment target may only be a name, a subscript or any tuple thereof."};
            }
        );
    }

    // TODO?
    /*
    constexpr auto names =
        [] <typename T> (T const & node)
        requires (
            has::resolveExpression <T> ||
            has::resolveStatement  <T> ||
            has::resolveType       <T>
        ) {
            return node.names();
        };

    constexpr auto type_names =
        [] <typename T> (T const & node)
        requires (
            has::resolveExpression <T> ||
            has::resolveStatement  <T> ||
            has::resolveType       <T>
        ) {
            return node.typeNames();
        };
    */

}
