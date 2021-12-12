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

    template <typename T>
    concept type = esl::variant_member<T, sem::CompleteType::variant>;

    template <typename T>
    concept incompleteType = esl::variant_member<T, sem::IncompleteType::variant>;

    template <typename T>
    concept simpleType =
        std::same_as<T, sem::type::Bool> ||
        std::same_as<T, sem::type::Int>  ||
        std::same_as<T, sem::type::Float>;

    namespace has {

        template <typename T>
        concept directTypeName = requires {
            { T::directTypeName } -> std::same_as<TypeNameConstant>;
        };

        template <typename T>
        concept typeName = requires (T type) {
            { type.typeName() } -> std::same_as<TypeNameResult>;
        };

        template <typename T>
        concept translateType = requires (T type) {
            { type.translateType() } -> std::same_as<TypeTranslationResult>;
        };

        /*
        template <typename T>
        concept decayType = requires (T type) {
            { type.decayType() } -> std::same_as<TypeDecayResult>;
        };
        */

        template <typename T, typename U>
        concept sameType = requires (T type, U const & other) {
            { type.sameType(other) } -> std::same_as<SameTypeResult>;
        };

        template <typename T, typename U>
        concept commonType = requires (T type, U const & other) {
            { type.commonType(other) } -> std::same_as<CommonTypeResult>;
        };

        template <typename T>
        concept completeType = requires (T type, context::Cynth & ctx) {
            { type.completeType(ctx) } -> std::same_as<TypeCompletionResult>;
        };

    }

    // Functions:

    constexpr auto directTypeName = esl::overload(
        [] <has::directTypeName T> (T const & type) -> TypeNameResult {
            return std::string{T::typeName};
        },
        [] <type T> (T const & type) -> TypeNameResult requires (!has::directTypeName<T>) {
            return esl::result_error{"This type it not directly named."};
        }
    );

    constexpr auto typeName = esl::overload(
        [] <has::directTypeName T> (T const & type) -> TypeNameResult {
            return std::string{T::typeName};
        },
        [] <has::typeName T> (T const & type) -> TypeNameResult requires (!has::directTypeName<T>) {
            return type.getTypeName();
        },
        [] <type T> (T const & type) -> TypeNameResult requires (!has::typeName<T> && !has::directTypeName<T>) {
            return esl::result_error{"This type does not have a name."};
        }
    );

    // TODO
    constexpr auto translateType = esl::overload(
        [] <has::translateType T> (T const & type) -> TypeNameResult {
            return std::string{T::typeName};
        },
        [] <has::typeName T> (T const & type) -> TypeNameResult requires (!has::directTypeName<T>) {
            return type.getTypeName();
        },
        [] <type T> (T const & type) -> TypeNameResult requires (!has::typeName<T> && !has::directTypeName<T>) {
            return esl::result_error{"This type does not have a name."};
        }
    );

    constexpr auto sameType = esl::overload(
        [] <type T, type U> (T const & type, U const & as) -> SameTypeResult
        requires (has::sameType<T, U>) {
            return type.sameType(as);
        },
        [] (type auto const &, type auto const &) -> SameTypeResult {
            return false;
        }
    );

    /*
    // TODO: Maybe it would be better to return the same type for non-decaying types?
    // TODO: Rethink this whole decaying mechanism. Maybe it's useless.
    // (As if they decay into themselves.)
    constexpr auto decayType = esl::overload(
        [] <type T> (T const & type) -> TypeDecayResult
        requires (has::decayType<T>) {
            return {type.decayType()};
        },
        [] (type auto const &) -> TypeDecayResult {
            return {};
        }
    );

    constexpr auto decaysTo = esl::overload(
        [] <type T, type To> (T const & type, To const & to) -> bool
        requires (has::decayType<T>) {
            auto result = esl::lift<esl::target::optional>(esl::curry(sameType)(to))(type.decayType());
            return result && *result; // i.e. decays && decays to the same type
        },
        [] (type auto const &, type auto const &) -> bool {
            return false;
        }
    );
    */

    /**
     *  This operation is symetric.
     *  It is enough to only provide one implementation for both directions.
     */
    constexpr auto commonType = esl::overload(
        [] <type T> (T const & type, T const & with) -> CommonTypeResult
        requires (has::commonType<T, T>) {
            return type.commonType(with);
        },
        [] <type T, type With> (T const & type, With const & with) -> CommonTypeResult
        requires (
            !std::same_as<T, With> &&
            has::commonType<T, With> &&
            !has::commonType<With, T>
        ) {
            return type.commonType(with);
        },
        [] <type T, type With> (T const & type, With const & with) -> CommonTypeResult
        requires (
            !std::same_as<T, With> &&
            !has::commonType<T, With> &&
            has::commonType<With, T>
        ) {
            return with.commonType(type);
        },
        [] <type T, type With> (T const &, With const &) -> CommonTypeResult
        requires (
            !has::commonType<T, With> &&
            !has::commonType<With, T>
        ) {
            return {esl::result_error{"No comomn type."}};
        },
        // TODO: This problem should be caught at compile-time.
        [] <type T, type With> (T const &, With const &) -> CommonTypeResult
        requires (
            has::commonType<T, With> &&
            has::commonType<With, T>
        ) {
            return {esl::result_error{"Two-way type.commonType(with) implementation found."}};
        }
    );

    constexpr auto completeType (context::Cynth & ctx) {
        return esl::overload(
            [] <type T> (T && type) -> TypeCompletionResult {
                return sem::CompleteType{std::forward<T>(type)};
            },
            [&ctx] <incompleteType T> (T const & type) -> TypeCompletionResult
            requires has::completeType<T> {
                return type.completeType(ctx);
            },
            [] (sem::type::Unknown const &) -> TypeCompletionResult {
                return {esl::result_error{"An unknown type ($ or type T) is not complete."}};
            }
            /*[] <incompleteType T> (T const &) -> TypeCompletionResult
            requires (!has::completeType<T>) {
                return {esl::result_error{"Complete type expected."}};
            }*/
        );
    };

    constexpr auto uncompleteType = esl::overload(
        [] <type Type> (Type && type) -> esl::result<sem::IncompleteType> {
            return sem::IncompleteType{sem::CompleteType{std::forward<Type>(type)}};
        }
        /*[] <incompleteType Type> (Type && type) -> esl::result<sem::IncompleteType> {
            return sem::IncompleteType{std::forward<Type>(type)};
        }*/
    );
    /*
        [] <value Type> (Type && type) -> esl::result<IncompleteValue> {
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
