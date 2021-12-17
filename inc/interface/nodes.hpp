#pragma once

#include <concepts>

#include "esl/containers.hpp"
#include "esl/functional.hpp"
#include "esl/result.hpp"
#include "esl/concepts.hpp" // variant_member

#include "context/c.hpp"
#include "interface/forward.hpp"

// This might introduce some problematic circular dependencies, but I'll give it a try:
#include "syn/categories/all.hpp"

// Completing forward declarations:
#include "sem/compound.hpp"
#include "sem/declarations.hpp"
#include "sem/types.hpp"

namespace cynth::interface {

    // Concepts:

    /** Any AST node. */
    template <typename T>
    concept node =
        esl::variant_member<T, syn::category::ArrayElement::variant>     ||
        esl::variant_member<T, syn::category::Declaration::variant>      ||
        esl::variant_member<T, syn::category::Expression::variant>       ||
        esl::variant_member<T, syn::category::Pattern::variant>          ||
        esl::variant_member<T, syn::category::RangeDeclaration::variant> ||
        esl::variant_member<T, syn::category::Statement::variant>        ||
        esl::variant_member<T, syn::category::Type::variant>;
    // syn::category::* could introduce unnecessary dependencies,
    // so maybe I'll need to keep this requirement purely informative, i.e.:
    // concept node = true;
    // or maybe at least enforce some category in general, i.e.:
    // concept node = esl::categorial<T>;

    namespace has {

        template <typename T>
        concept processExpression = node<T> && requires (T node, context::C & ctx) {
            { node.processExpression(ctx) } -> std::same_as<ExpressionProcessingResult>;
        };

        template <typename T>
        concept processArrayElement = node<T> && requires (T node, context::C & ctx) {
            { node.processArrayElement(ctx) } -> std::same_as<ArrayElementProcessingResult>;
        };

        template <typename T>
        concept processStatement = node<T> && requires (T node, context::C & ctx) {
            { node.processStatement(ctx) } -> std::same_as<StatementProcessingResult>;
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

        template <typename T>
        concept extractNames = node<T> && requires (T node) {
            { node.extractNames() } -> std::same_as<NameExtractionResult>;
        };

        template <typename T>
        concept extractTypeNames = node<T> && requires (T node) {
            { node.extractTypeNames() } -> std::same_as<TypeNameExtractionResult>;
        };

    }

    // Functions:

    constexpr auto processExpression (context::C & ctx) {
        return [&ctx] (has::processExpression auto const & node) -> ExpressionProcessingResult {
            return node.processExpression(ctx);
        };
    }

    constexpr auto processArrayElement (context::C & ctx) {
        return [&ctx] (has::processArrayElement auto const & node) -> ArrayElementProcessingResult {
            return node.processArrayElement(ctx);
        };
    }

    constexpr auto processStatement (context::C & ctx) {
        return esl::overload(
            [&ctx] (has::processStatement auto const & node) -> StatementProcessingResult
            {
                return node.processStatement(ctx);
            },
            [&ctx] <has::processExpression T> (T const & node) -> StatementProcessingResult
            requires (!has::processStatement<T>) { // TODO: Or is it the other way around? (Should i put !has::processExpression above?)
                auto result = node.processExpression(ctx);
                if (!result)
                    return result.error();
                return {sem::NoReturn{}};
            }
        );
    }

    constexpr auto resolveType (context::C & ctx) {
        return [&ctx] (has::resolveType auto const & node) -> TypeResolutionResult {
            return node.resolveType(ctx);
        };
    }

    constexpr auto resolveDeclaration (context::C & ctx) {
        return [&ctx] (has::resolveDeclaration auto const & node) -> DeclarationResolutionResult {
            return node.resolveDeclaration(ctx);
        };
    }

    constexpr auto resolveRangeDeclaration (context::C & ctx) {
        return [&ctx] (has::resolveRangeDeclaration auto const & node) -> RangeDeclarationResolutionResult {
            return node.resolveRangeDeclaration(ctx);
        };
    }

    constexpr auto resolveTarget (context::C & ctx) {
        return esl::overload(
            [&ctx] (has::resolveTarget auto const & node) -> TargetResolutionResult {
                return node.resolveTarget(ctx);
            },
            [] (node auto const &) -> TargetResolutionResult {
                return esl::result_error{"Assignment target may only be a name, a subscript or any tuple thereof."};
            }
        );
    }

    constexpr auto extractNames = esl::overload(
        [] (has::extractNames auto const & node) -> NameExtractionResult {
            return node.extractNames();
        },
        [] (node auto const &) -> NameExtractionResult {
            return {}; // No names captured.
        }
    );

    constexpr auto extractTypeNames = esl::overload(
        [] (has::extractTypeNames auto const & node) -> TypeNameExtractionResult {
            return node.extractTypeNames();
        },
        [] (node auto const &) -> TypeNameExtractionResult {
            return {}; // No names captured.
        }
    );

}
