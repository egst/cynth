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

    template <typename Node>
    concept evaluatableExpression = requires (Node node, context::Cynth & ctx) {
        { node.evaluateExpression(ctx) } -> std::same_as<ExpressionEvaluationResult>;
    };

    template <typename Node>
    concept executableStatement = requires (Node node, context::Cynth & ctx) {
        { node.executeStatement(ctx) } -> std::same_as<StatementExecutionResult>;
    };

    template <typename Node>
    concept resolvableType = requires (Node node, context::Cynth & ctx) {
        { node.resolveType(ctx) } -> std::same_as<TypeResolutionResult>;
    };

    template <typename Node>
    concept evaluatableArrayElement = requires (Node node, context::Cynth & ctx) {
        { node.evaluateArrayElement(ctx) } -> std::same_as<ExpressionEvaluationResult>; // TODO: Decide on the result type.
    };

    template <typename Node>
    concept resolvableDeclaration = requires (Node node, context::Cynth & ctx) {
        { node.resolveDeclaration(ctx) } -> std::same_as<DeclarationResolutionResult>;
    };

    template <typename Node>
    concept resolvableRangeDeclaration = requires (Node node, context::Cynth & ctx) {
        { node.resolveRangeDeclaration(ctx) } -> std::same_as<RangeDeclarationResolutionResult>;
    };

    template <typename Node>
    concept resolvableTarget = requires (Node node, context::Cynth & ctx) {
        { node.resolveTarget(ctx) } -> std::same_as<TargetResolutionResult>;
    };

    // Functions:

    constexpr auto executeStatement (context::Cynth & ctx) {
        return esl::overload(
            [&ctx] (interface::executableStatement auto const & node) {
                return node.executeStatement(ctx);
            },
            [&ctx] (interface::evaluatableExpression auto const & node) -> StatementExecutionResult {
                auto result = esl::unite_results(node.evaluateExpression(ctx));
                if (!result)
                    return result.error();
                return {};
            }
        );
    }

    constexpr auto evaluateExpression (context::Cynth & ctx) {
        return [&ctx] <interface::evaluatableExpression Node> (Node const & node) {
            return node.evaluateExpression(ctx);
        };
    }

    constexpr auto names =
        [] <typename Node> (Node const & node)
        requires (
            interface::evaluatableExpression <Node> ||
            interface::executableStatement   <Node> ||
            interface::resolvableType        <Node>
        ) {
            return node.names();
        };

    constexpr auto type_names =
        [] <typename Node> (Node const & node)
        requires (
            interface::evaluatableExpression <Node> ||
            interface::executableStatement   <Node> ||
            interface::resolvableType        <Node>
        ) {
            return node.typeNames();
        };

    constexpr auto resolveType (context::Cynth & ctx) {
        return [&ctx] (interface::resolvableType auto const & node) {
            return node.resolveType(ctx);
        };
    }

    constexpr auto evaluateArrayElement (context::Cynth & ctx) {
        return [&ctx] (interface::evaluatableArrayElement auto const & node) {
            return node.evaluateArrayElement(ctx);
        };
    }

    constexpr auto resolveDeclaration (context::Cynth & ctx) {
        return [&ctx] (interface::resolvableDeclaration auto const & node) {
            return node.resolveDeclaration(ctx);
        };
    }

    constexpr auto resolveRangeDeclaration (context::Cynth & ctx) {
        return [&ctx] (interface::resolvableRangeDeclaration auto const & node) {
            return node.resolveRangeDeclaration(ctx);
        };
    }

    constexpr auto resolveTarget (context::Cynth & ctx) {
        return esl::overload(
            [&ctx] (interface::resolvableTarget auto const & node) -> TargetResolutionResult {
                return node.resolveTarget(ctx);
            },
            [] (auto const &) -> TargetResolutionResult {
                return esl::result_error{"Assignment target may only be a name, a subscript or any tuple thereof."};
            }
        );
    }

}
