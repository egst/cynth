#pragma once

#include <concepts>
#include <optional>
#include <string>
#include <utility>

#include "esl/concepts.hpp"
#include "esl/containers.hpp"
#include "esl/functional.hpp"
#include "esl/ranges.hpp"
#include "esl/result.hpp"
#include "esl/type_manip.hpp"

#include "context/cynth.hpp"
#include "interface/forward.hpp"

// Completing forward declarations:
#include "sem/types.hpp"

namespace cynth::interface {

    // Concepts:

    template <typename Node>
    concept type = esl::variant_member<Node, sem::CompleteType::variant>;

    template <typename Node>
    concept directlyNamedType = requires {
        { Node::typeName } -> std::same_as<TypeNameConstant>;
    };

    template <typename Node>
    concept namedType = requires (Node node) {
        { node.getTypeName() } -> std::same_as<TypeNameResult>;
    };

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
    concept incompleteType = esl::variant_member<Node, sem::IncompleteType::variant>;

    template <typename Node>
    concept completableType = requires (Node node, context::Cynth & ctx) {
        { node.completeType(ctx) } -> std::same_as<TypeCompletionResult>;
    };

    template <typename T>
    concept simpleType =
        std::same_as<T, sem::type::Bool> ||
        std::same_as<T, sem::type::Int>  ||
        std::same_as<T, sem::type::Float>;

    // Functions:

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


    constexpr auto completeType (context::Cynth & ctx) {
        return esl::overload(
            [] <interface::type Node> (Node && node) -> TypeCompletionResult {
                return sem::CompleteType{std::forward<Node>(node)};
            },
            [&ctx] <interface::incompleteType Node> (Node const & node) -> TypeCompletionResult
            requires interface::completableType<Node> {
                return node.completeType(ctx);
            },
            [] (sem::type::Unknown const &) -> TypeCompletionResult {
                return {esl::result_error{"An unknown type ($ or type T) is not complete."}};
            }
            /*[] <interface::incompleteType Node> (Node const &) -> TypeCompletionResult
            requires (!interface::completableType<Node>) {
                return {esl::result_error{"Complete type expected."}};
            }*/
        );
    };

    constexpr auto uncompleteType = esl::overload(
        [] <interface::type Type> (Type && type) -> esl::result<sem::IncompleteType> {
            return sem::IncompleteType{sem::CompleteType{std::forward<Type>(type)}};
        }
        /*[] <interface::incompleteType Type> (Type && type) -> esl::result<sem::IncompleteType> {
            return sem::IncompleteType{std::forward<Type>(type)};
        }*/
    );
    /*
        [] <interface::value Type> (Type && type) -> esl::result<IncompleteValue> {
            return IncompleteValue{std::forward<Type>(type)};
        }
        // ... declaration?
    */

#if 0 // TODO: Move to interface/declarations?

    constexpr auto declarationType = esl::overload(
        [] <esl::same_but_cvref<sem::CompleteDeclaration> Decl> (Decl && decl) -> esl::tiny_vector<sem::CompleteType> {
            return esl::forward_like<Decl>(decl.type);
        },
        [] <esl::same_but_cvref<sem::IncompleteRangeDeclaration> Decl> (Decl && decl) -> esl::tiny_vector<sem::IncompleteType> {
            return esl::forward_like<Decl>(decl.type);
        }
        // Note: use lift<target::nested_tiny_vector_cat>(declarationType) instead
        /*
        [] <esl::range_of<sem::CompleteDeclaration> Decls> (Decls && decls) -> esl::tiny_vector<sem::CompleteType> {
            esl::tiny_vector<sem::CompleteType> result;
            for (auto & decl : decls) for (auto & type : decl.type) {
                result.push_back(esl::forward_like<Decls>(type));
            }
            return result;
        },
        [] <esl::range_of<sem::IncompleteRangeDeclaration> Decls> (Decls && decls) -> esl::tiny_vector<sem::IncompleteType> {
            esl::tiny_vector<sem::IncompleteType> result;
            for (auto & decl : decls) for (auto & type : decl.type) {
                result.push_back(esl::forward_like<Decls>(type));
            }
            return result;
        }
        */
    );

    namespace detail {

        constexpr auto makeDeclComplete = [] (context::Cynth & ctx) {
            return esl::overload(
                [&ctx] <esl::same_but_cvref<sem::IncompleteDeclaration> Decl> (Decl && decl)
                -> esl::result<sem::CompleteDeclaration> {
                    auto complete = esl::unite_results(esl::lift<esl::target::component, esl::target::category>(
                        detail::makeTypeComplete(ctx)
                    )(esl::forward_like<Decl>(decl.type)));
                    if (!complete)
                        return complete.error();
                    return sem::CompleteDeclaration{
                        .type = *std::move(complete),
                        .name = decl.name
                    };
                },
                [] <esl::same_but_cvref<sem::CompleteDeclaration> Decl> (Decl && decl)
                -> esl::result<sem::CompleteDeclaration> {
                    return std::forward<Decl>(decl);
                }
            );
        };

        constexpr auto makeRangeDeclComplete = [] (context::Cynth & ctx) {
            return esl::overload(
                [&ctx] <esl::same_but_cvref<sem::IncompleteRangeDeclaration> Decl> (Decl && decl)
                -> esl::result<sem::CompleteRangeDeclaration> {
                    auto complete = esl::unite_results(lift<esl::target::component>(
                        detail::makeDeclComplete(ctx)
                    )(esl::forward_like<Decl>(decl.declaration)));
                    if (!complete)
                        return complete.error();
                    return sem::CompleteRangeDeclaration{
                        .declaration = *std::move(complete),
                        .range       = decl.range
                    };
                },
                [] <esl::same_but_cvref<sem::CompleteRangeDeclaration> Decl> (Decl && decl)
                -> esl::result<sem::CompleteRangeDeclaration> {
                    return std::forward<Decl>(decl);
                }
            );
        };

    }

#endif

}
