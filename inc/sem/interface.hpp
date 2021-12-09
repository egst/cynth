#pragma once

#include <concepts>
#include <optional>
#include <utility>

#include "esl/concepts.hpp"
#include "esl/containers.hpp"
#include "esl/functional.hpp"
#include "esl/ranges.hpp"
#include "esl/type_manip.hpp"

#include "sem/context.hpp"
#include "sem/declarations.hpp"
#include "sem/interface_types.hpp"
#include "sem/translation.hpp"
#include "sem/values.hpp"

//#include "esl/debug.hpp"
//#include "esl/macros.hpp"

namespace cynth::sem::interface {

    template <typename Node>
    concept value = esl::variant_member<Node, CompleteValue::variant>;

    template <typename Node, typename To>
    concept convertible = requires (Node node, Context & ctx, To const & to) {
        { node.convert(ctx, to) } -> std::same_as<ConversionResult>;
    };

    template <typename Node>
    concept typed = requires (Node node) {
        { node.type() } -> std::same_as<ValueTypeResult>;
    };

    template <typename Node, typename Out>
    concept valueOf = requires (Node node) {
        { node.get() } -> std::same_as<GetResult<Out>>;
    };

    template <typename Node>
    concept type = esl::variant_member<Node, CompleteType::variant>;

    template <typename Node>
    concept decaying = requires (Node node) {
        { node.decayType() } -> std::same_as<TypeDecayResult>;
    };

    template <typename Node, typename As>
    concept same = requires (Node node, As const & as) {
        { node.sameType(as) } -> std::same_as<SameTypeResult>;
    };

    template <typename Node, typename With>
    concept common = requires (Node node, With const & type) {
        { node.commonType(type) } -> std::same_as<CommonTypeResult>;
    };

    template <typename Node>
    concept incompleteType = esl::variant_member<Node, IncompleteType::variant>;

    template <typename Node>
    concept completableType = requires (Node node, Context & ctx) {
        { node.completeType(ctx) } -> std::same_as<TypeCompletionResult>;
    };

    template <typename Node>
    concept target = requires (Node node, bool c) {
        { node.resolveTarget(c) } -> std::same_as<TargetResolutionResult>;
    };

    template <typename Node>
    concept translatableExpression = requires (Node node, TranslationContext & ctx) {
        { node.translate(ctx) } -> std::same_as<ExpressionTranslationResult>;
    };

    template <typename Node>
    concept translatableDefinition = requires (
        Node node,
        TranslationContext & ctx,
        std::string const & definition,
        bool compval
    ) {
        { node.translateDefinition(ctx, definition, compval) } -> std::same_as<StatementTranslationResult>;
    };

    template <typename Node>
    concept directlyNamedType = requires {
        { Node::typeName } -> std::same_as<TypeNameConstant>;
    };

    template <typename Node>
    concept namedType = requires (Node node) {
        { node.getTypeName() } -> std::same_as<TypeNameResult>;
    };

    template <typename T>
    concept simpleType =
        std::same_as<T, type::Bool> ||
        std::same_as<T, type::Int>  ||
        std::same_as<T, type::Float>;

}

namespace cynth::sem {

    /** Use nullopt definition argument for a declaration. */
    constexpr auto translateDefinition (
        TranslationContext & ctx,
        std::optional<TranslatedExpression> const & definition,
        bool compval
    ) {
        return esl::overload(
            [&ctx, &definition, compval] (interface::translatableExpression auto const & node)
            -> StatementTranslationResult {
                return node.translateDefinition(ctx, definition, compval);
            },
            [] (interface::type auto const & node) -> StatementTranslationResult {
                return esl::result_error{"A definition of this type cannot be directly translated."};
            }
        );
    }

    constexpr auto translateExpression (TranslationContext &) {
        return esl::overload(
            [] (interface::translatableDefinition auto const & node) -> StatementTranslationResult {
                return node.translateExpression();
            },
            [] (interface::type auto const & node) -> StatementTranslationResult {
                return esl::result_error{"This expression cannot be directly translated."};
            }
        );
    }

    constexpr auto directTypeName = esl::overload(
        [] <interface::directlyNamedType T> (T const & node) -> TypeNameResult {
            return std::string{T::typeName};
        },
        [] <interface::type T> (T const & node) -> TypeNameResult requires (!interface::directlyNamedType<T>) {
            return esl::result_error{"This type it not directly named."};
        }
    );

    // TODO: Might not be needed.
    constexpr auto typeName = esl::overload(
        [] <interface::directlyNamedType T> (T const & node) -> TypeNameResult {
            return std::string{T::typeName};
        },
        [] <interface::namedType T> (T const & node) -> TypeNameResult requires (!interface::directlyNamedType<T>) {
            return node.getTypeName();
        },
        [] <interface::type T> (T const & node) -> TypeNameResult requires (!interface::namedType<T> && !interface::directlyNamedType<T>) {
            return esl::result_error{"This type does not have a name."};
        }
    );

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

    constexpr auto sameType = esl::overload(
        [] <interface::type Node, interface::type As> (Node const & node, As const & as) -> SameTypeResult
        requires (interface::same<Node, As>) {
            return node.sameType(as);
        },
        [] (interface::type auto const &, interface::type auto const &) -> SameTypeResult {
            return false;
        }
    );

    // TODO: Maybe it would be better to return the same type for non-decaying types?
    // (As if they decay into themselves.)
    constexpr auto decayType = esl::overload(
        [] <interface::type Node> (Node const & node) -> TypeDecayResult
        requires (interface::decaying<Node>) {
            return {node.decayType()};
        },
        [] (interface::type auto const &) -> TypeDecayResult {
            return {};
        }
    );

    constexpr auto decaysTo = esl::overload(
        [] <interface::type Node, interface::type To> (Node const & node, To const & to) -> bool
        requires (interface::decaying<Node>) {
            auto result = esl::lift<esl::target::optional>(esl::curry(sameType)(to))(node.decayType());
            return result && *result; // i.e. decays && decays to the same type
        },
        [] (interface::type auto const &, interface::type auto const &) -> bool {
            return false;
        }
    );

    /**
     *  This operation is symetric.
     *  It is enough to only provide one implementation for both directions.
     */
    constexpr auto commonType = esl::overload(
        [] <interface::type Node> (Node const & node, Node const & with) -> CommonTypeResult
        requires (interface::common<Node, Node>) {
            return node.commonType(with);
        },
        [] <interface::type Node, interface::type With> (Node const & node, With const & with) -> CommonTypeResult
        requires (
            !std::same_as<Node, With> &&
            interface::common<Node, With> &&
            !interface::common<With, Node>
        ) {
            return node.commonType(with);
        },
        [] <interface::type Node, interface::type With> (Node const & node, With const & with) -> CommonTypeResult
        requires (
            !std::same_as<Node, With> &&
            !interface::common<Node, With> &&
            interface::common<With, Node>
        ) {
            return with.commonType(node);
        },
        [] <interface::type Node, interface::type With> (Node const &, With const &) -> CommonTypeResult
        requires (
            !interface::common<Node, With> &&
            !interface::common<With, Node>
        ) {
            return {esl::result_error{"No comomn type."}};
        },
        // TODO: This problem should be caught at compile-time.
        [] <interface::type Node, interface::type With> (Node const &, With const &) -> CommonTypeResult
        requires (
            interface::common<Node, With> &&
            interface::common<With, Node>
        ) {
            return {esl::result_error{"Two-way node.commonType(with) implementation found."}};
        }
    );

    constexpr auto convert = [] (Context & ctx) {
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

    namespace detail {

        constexpr auto makeTypeComplete = [] (Context & ctx) {
            return esl::overload(
                [] <interface::type Node> (Node && node) -> TypeCompletionResult {
                    return CompleteType{std::forward<Node>(node)};
                },
                [&ctx] <interface::incompleteType Node> (Node const & node) -> TypeCompletionResult
                requires interface::completableType<Node> {
                    return node.completeType(ctx);
                },
                [] (type::Unknown const &) -> TypeCompletionResult {
                    return {esl::result_error{"An unknown type ($ or type T) is not complete."}};
                }
                /*[] <interface::incompleteType Node> (Node const &) -> TypeCompletionResult
                requires (!interface::completableType<Node>) {
                    return {esl::result_error{"Complete type expected."}};
                }*/
            );
        };


        constexpr auto makeDeclComplete = [] (Context & ctx) {
            return esl::overload(
                [&ctx] <esl::same_but_cvref<IncompleteDeclaration> Decl> (Decl && decl)
                -> esl::result<CompleteDeclaration> {
                    auto complete = esl::unite_results(esl::lift<esl::target::component, esl::target::category>(
                        detail::makeTypeComplete(ctx)
                    )(esl::forward_like<Decl>(decl.type)));
                    if (!complete)
                        return complete.error();
                    return CompleteDeclaration{
                        .type = *std::move(complete),
                        .name = decl.name
                    };
                },
                [] <esl::same_but_cvref<CompleteDeclaration> Decl> (Decl && decl)
                -> esl::result<CompleteDeclaration> {
                    return std::forward<Decl>(decl);
                }
            );
        };

        constexpr auto makeRangeDeclComplete = [] (Context & ctx) {
            return esl::overload(
                [&ctx] <esl::same_but_cvref<IncompleteRangeDeclaration> Decl> (Decl && decl)
                -> esl::result<CompleteRangeDeclaration> {
                    auto complete = esl::unite_results(lift<esl::target::component>(
                        detail::makeDeclComplete(ctx)
                    )(esl::forward_like<Decl>(decl.declaration)));
                    if (!complete)
                        return complete.error();
                    return CompleteRangeDeclaration{
                        .declaration = *std::move(complete),
                        .range       = decl.range
                    };
                },
                [] <esl::same_but_cvref<CompleteRangeDeclaration> Decl> (Decl && decl)
                -> esl::result<CompleteRangeDeclaration> {
                    return std::forward<Decl>(decl);
                }
            );
        };

    }

    constexpr auto completeType = [] (Context & ctx) {
        return esl::overload(
            detail::makeTypeComplete(ctx),
            detail::makeDeclComplete(ctx),
            detail::makeRangeDeclComplete(ctx)
        );
    };

    constexpr auto uncompleteType = esl::overload(
        [] <interface::type Type> (Type && type) -> esl::result<IncompleteType> {
            return IncompleteType{CompleteType{std::forward<Type>(type)}};
        },
        /*[] <interface::incompleteType Type> (Type && type) -> esl::result<IncompleteType> {
            return IncompleteType{std::forward<Type>(type)};
        },*/
        [] <interface::value Type> (Type && type) -> esl::result<IncompleteValue> {
            return IncompleteValue{std::forward<Type>(type)};
        }
        // ... declaration?
    );

    constexpr auto declarationType = esl::overload(
        [] <esl::same_but_cvref<CompleteDeclaration> Decl> (Decl && decl) -> esl::tiny_vector<CompleteType> {
            return esl::forward_like<Decl>(decl.type);
        },
        [] <esl::same_but_cvref<IncompleteRangeDeclaration> Decl> (Decl && decl) -> esl::tiny_vector<IncompleteType> {
            return esl::forward_like<Decl>(decl.type);
        }
        // Note: use lift<target::nested_tiny_vector_cat>(declarationType) instead
        /*
        [] <esl::range_of<CompleteDeclaration> Decls> (Decls && decls) -> esl::tiny_vector<CompleteType> {
            esl::tiny_vector<CompleteType> result;
            for (auto & decl : decls) for (auto & type : decl.type) {
                result.push_back(esl::forward_like<Decls>(type));
            }
            return result;
        },
        [] <esl::range_of<IncompleteRangeDeclaration> Decls> (Decls && decls) -> esl::tiny_vector<IncompleteType> {
            esl::tiny_vector<IncompleteType> result;
            for (auto & decl : decls) for (auto & type : decl.type) {
                result.push_back(esl::forward_like<Decls>(type));
            }
            return result;
        }
        */
    );

    constexpr auto resolveTarget =
        [] <interface::target Node> (Node const & node) {
            return node.resolveTarget(false);
        };

    constexpr auto resolveConstTarget =
        [] <interface::target Node> (Node const & node) {
            return node.resolveTarget(true);
        };

}
