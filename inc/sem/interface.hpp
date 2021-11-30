#pragma once

#include "esl/macros.hpp"

#include <concepts>
#include <optional>
#include <utility>

#include "esl/type_manip.hpp"
#include "esl/concepts.hpp"
#include "esl/functional.hpp"
#include "esl/containers.hpp"
#include "esl/ranges.hpp"

#include "sem/interface_types.hpp"
#include "sem/context.hpp"
#include "sem/values.hpp"
#include "sem/declarations.hpp"

namespace cynth::sem::interface {

    template <typename Node>
    concept value = esl::variant_member<Node, CompleteValue::variant>;

    template <typename Node, typename To>
    concept convertible = requires (Node node, Context & ctx, To const & to) {
        { node.convert(ctx, to) } -> std::same_as<ConversionResult>;
    };

    template <typename Node>
    concept typed = requires (Node node) {
        { node.valueType() } -> std::same_as<ValueTypeResult>;
    };

    template <typename Node, typename Out>
    concept valueOf = requires (Node node) {
        { node.get() } -> std::same_as<GetResult<Out>>;
    };

    template <typename Node>
    concept type = esl::variant_member<Node, CompleteType::variant>;

    template <typename Node>
    concept decaying = requires (Node node) {
        { node.decay() } -> std::same_as<TypeDecayResult>;
    };

    template <typename Node, typename As>
    concept same = requires (Node node, As const & as) {
        { node.same(as) } -> std::same_as<SameTypeResult>;
    };

    template <typename Node, typename With>
    concept common = requires (Node node, With const & type) {
        { node.common(type) } -> std::same_as<CommonTypeResult>;
    };

    template <typename Node>
    concept incompleteType = esl::variant_member<Node, IncompleteType::variant>;

    template <typename Node>
    concept completableType = requires (Node node, Context & ctx) {
        { node.complete(ctx) } -> std::same_as<TypeCompletionResult>;
    };

    template <typename Node>
    concept target = requires (Node node, bool c) {
        { node.resolveTarget(c) } -> std::same_as<TargetResolutionResult>;
    };

    /*
    template <typename Node>
    concept translatable = requires (Node node, TranslationContext & ctx) {
        { node.translate(ctx) } -> std::same_as<TranslationResult>;
    };
    */

    template <typename Node>
    concept translatableType = requires (Node node) {
        { node.translateType() } -> std::same_as<TypeTranslationResult>;
    };

}

namespace cynth::sem {

    // In the following docblock comments, the construct any<T>
    // means any abstraction, that is supported by lift::any.
    // f (any<T>, any<T>) means that to completely unwrap any one of them,
    // a series of the same lift::* operations must be applied.
    // E.g. f(std::variant<int, float>, std::variant<int, bool>) is ok,
    // but f(std::vector<int>, std::variant<int>) is not.
    // TODO: Remove the lift wrappers. Put them explicitly where needed at the call site.

    /*
    constexpr auto translate = lift::any {
        [] <interface::value Node> (Node const & node) {
            return node.translate();
        }
    };
    */

    constexpr auto translateType = esl::overload(
        [] (interface::translatableType auto const & node) -> TypeTranslationResult {
            return node.translateType();
        },
        [] (auto const & node) -> TypeTranslationResult {
            return esl::result_error{"This type cannot be directly translated."};
        }
    );

    constexpr auto valueType =
        [] (interface::typed auto const & node) -> ValueTypeResult {
            return node.valueType();
        };

    template <typename Out>
    constexpr auto get = esl::overload(
        [] (interface::valueOf<Out> auto const & node) -> GetResult<Out> {
            return node.template get<Out>();
        },
        [] (auto const &) -> GetResult<Out> {
            return esl::result_error{"Value does not contain the requested type."};
        }
    );

    constexpr auto same = esl::overload(
        [] <interface::type Node, interface::type As> (Node const & node, As const & as) -> SameTypeResult
        requires (interface::same<Node, As>) {
            return node.same(as);
        },
        [] (interface::type auto const &, interface::type auto const &) -> SameTypeResult {
            return false;
        }
    );

    // TODO: Maybe it would be better to return the same type for non-decaying types?
    // (As if they decay into themselves.)
    constexpr auto decay = esl::overload(
        [] <interface::type Node> (Node const & node) -> TypeDecayResult
        requires (interface::decaying<Node>) {
            return {node.decay()};
        },
        [] (interface::type auto const &) -> TypeDecayResult {
            return {};
        }
    );

    constexpr auto decaysTo = esl::overload(
        [] <interface::type Node, interface::type To> (Node const & node, To const & to) -> bool
        requires (interface::decaying<Node>) {
            auto result = esl::lift<std::optional>(esl::curry(same)(to))(node.decay());
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
    constexpr auto common = esl::overload(
        [] <interface::type Node> (Node const & node, Node const & with) -> CommonTypeResult
        requires (interface::common<Node, Node>) {
            return node.common(with);
        },
        [] <interface::type Node, interface::type With> (Node const & node, With const & with) -> CommonTypeResult
        requires (
            !std::same_as<Node, With> &&
            interface::common<Node, With> &&
            !interface::common<With, Node>
        ) {
            return node.common(with);
        },
        [] <interface::type Node, interface::type With> (Node const & node, With const & with) -> CommonTypeResult
        requires (
            !std::same_as<Node, With> &&
            !interface::common<Node, With> &&
            interface::common<With, Node>
        ) {
            return with.common(node);
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
            return {esl::result_error{"Two-way node.common(with) implementation found."}};
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
                    return node.complete(ctx);
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
                    auto complete = esl::unite_results(esl::lift<esl::component, esl::target::category>(
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
                    auto complete = esl::unite_results(lift<esl::component>(
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

    constexpr auto complete = [] (Context & ctx) {
        return esl::overload(
            detail::makeTypeComplete(ctx),
            detail::makeDeclComplete(ctx),
            detail::makeRangeDeclComplete(ctx)
        );
    };

    constexpr auto uncomplete = esl::overload(
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
