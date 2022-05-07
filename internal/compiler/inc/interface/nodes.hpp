#pragma once

#include <concepts>

#include "esl/concepts.hpp"
#include "esl/containers.hpp"
#include "esl/functional.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"

#include "context/lookup.hpp"
#include "context/main.hpp"
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
        concept processExpression = node<T> && requires (T node, context::Main & ctx) {
            { node.processExpression(ctx) } -> std::same_as<ExpressionProcessingResult>;
        };

        template <typename T>
        concept processArrayElement = node<T> && requires (T node, context::Main & ctx) {
            { node.processArrayElement(ctx) } -> std::same_as<ArrayElementProcessingResult>;
        };

        template <typename T>
        concept processStatement = node<T> && requires (T node, context::Main & ctx) {
            { node.processStatement(ctx) } -> std::same_as<StatementProcessingResult>;
        };

        template <typename T>
        concept resolveType = node<T> && requires (T node, context::Main & ctx) {
            { node.resolveType(ctx) } -> std::same_as<TypeResolutionResult>;
        };

        template <typename T>
        concept resolveDeclaration = node<T> && requires (T node, context::Main & ctx) {
            { node.resolveDeclaration(ctx) } -> std::same_as<DeclarationResolutionResult>;
        };

        template <typename T>
        concept resolveRangeDeclaration = node<T> && requires (T node, context::Main & ctx) {
            { node.resolveRangeDeclaration(ctx) } -> std::same_as<RangeDeclarationResolutionResult>;
        };

        template <typename T>
        concept resolveTarget = node<T> && requires (T node, context::Main & ctx) {
            { node.resolveTarget(ctx) } -> std::same_as<TargetResolutionResult>;
        };

        template <typename T>
        concept extractNames = node<T> && requires (T node, context::Lookup & ctx) {
            { node.extractNames(ctx) } -> std::same_as<NameExtractionResult>;
        };

        template <typename T>
        concept extractTypeNames = node<T> && requires (T node, context::Lookup & ctx) {
            { node.extractTypeNames(ctx) } -> std::same_as<TypeNameExtractionResult>;
        };

    }

    // Functions:

    constexpr auto processExpression (context::Main & ctx) {
        return [&ctx] (has::processExpression auto const & node) -> ExpressionProcessingResult {
            return node.processExpression(ctx);
        };
    }

    constexpr auto processArrayElement (context::Main & ctx) {
        return esl::overload(
            [&ctx] (has::processArrayElement auto const & node) -> ArrayElementProcessingResult {
                return node.processArrayElement(ctx);
            },
            [&ctx] <has::processExpression T> (T const & node) -> ArrayElementProcessingResult
            requires (!has::processArrayElement<T>) {
                return node.processExpression(ctx);
                /*
                if (!result) return result.error();
                return esl::init<interface::ArrayElementVector>(*result);
                */
            }
        );
    }

    template <typename Target>
    constexpr auto processArrayElementsLift (context::Main & ctx) {
        return [&ctx] (auto const & elems) -> ArrayElementProcessingResult {
            interface::ArrayElementVector<sem::ResolvedValue> processed;
            processed.reserve(elems.size()); // Lower-bound size estimate.
            for (auto const & elem: elems) {
                auto result = esl::lift<Target>(processArrayElement(ctx))(elem);
                if (!result) return result.error();
                processed.insert_back(std::make_move_iterator(result->begin()), std::make_move_iterator(result->end()));
            }
            return processed;
        };
    }

    constexpr auto processArrayElementCategories = processArrayElementsLift<esl::target::category>;

    constexpr auto processStatement (context::Main & ctx) {
        return esl::overload(
            [&ctx] (has::processStatement auto const & node) -> StatementProcessingResult {
                return node.processStatement(ctx);
            },
            [&ctx] <has::processExpression T> (T const & node) -> StatementProcessingResult
            requires (!has::processStatement<T>) { // TODO: Or is it the other way around? (Should i put !has::processExpression above?)
                auto result = node.processExpression(ctx);
                if (!result)
                    return result.error();
                return sem::NoReturn{};
            }
        );
    }

    constexpr auto resolveType (context::Main & ctx) {
        return [&ctx] (has::resolveType auto const & node) -> TypeResolutionResult {
            return node.resolveType(ctx);
        };
    }

    constexpr auto resolveDeclaration (context::Main & ctx) {
        return [&ctx] (has::resolveDeclaration auto const & node) -> DeclarationResolutionResult {
            return node.resolveDeclaration(ctx);
        };
    }

    constexpr auto resolveRangeDeclaration (context::Main & ctx) {
        return [&ctx] (has::resolveRangeDeclaration auto const & node) -> RangeDeclarationResolutionResult {
            return node.resolveRangeDeclaration(ctx);
        };
    }

    constexpr auto resolveTarget (context::Main & ctx) {
        return esl::overload(
            [&ctx] (has::resolveTarget auto const & node) -> TargetResolutionResult {
                return node.resolveTarget(ctx);
            },
            [] (node auto const &) -> TargetResolutionResult {
                return esl::result_error{"Assignment target may only be a name, a subscript or any tuple thereof."};
            }
        );
    }

    constexpr auto extractNames (context::Lookup & ctx) {
        return esl::overload(
            [&] (has::extractNames auto const & node) -> NameExtractionResult {
                return node.extractNames(ctx);
            },
            [] (node auto const &) -> NameExtractionResult {
                return {}; // No names captured.
            }
        );
    }

    constexpr auto extractTypeNames (context::Lookup & ctx) {
        return esl::overload(
            [&] (has::extractTypeNames auto const & node) -> TypeNameExtractionResult {
                return node.extractTypeNames(ctx);
            },
            [] (node auto const &) -> TypeNameExtractionResult {
                return {}; // No names captured.
            }
        );
    }

}
