#pragma once

#include <concepts>
#include <optional>
#include <string>
#include <utility>

#include "esl/boolean.hpp"
#include "esl/concepts.hpp"
#include "esl/containers.hpp"
#include "esl/functional.hpp"
#include "esl/ranges.hpp"
#include "esl/result.hpp"
#include "esl/type_manip.hpp"

#include "context/main.hpp"
#include "interface/forward.hpp"

// Completing forward declarations:
#include "sem/compound.hpp"
#include "sem/types.hpp"

namespace cynth::interface {

    // Concepts:

    template <typename T>
    concept type = esl::variant_member<T, sem::CompleteType::variant>;

    template <typename T>
    concept incompleteType = esl::variant_member<T, sem::IncompleteType::variant>;

    template <typename T>
    concept simpleType =
        esl::same_but_cvref<T, sem::type::Bool> ||
        esl::same_but_cvref<T, sem::type::Int>  ||
        esl::same_but_cvref<T, sem::type::Float>;

    template <typename T>
    concept numericType =
        esl::same_but_cvref<T, sem::type::Int>  ||
        esl::same_but_cvref<T, sem::type::Float>;

    namespace has {

        template <typename T>
        concept typeValue = type<T> && requires () {
            typename T::Value;
        };

        template <typename T>
        concept directTypeName = simpleType<T> && requires (T value) {
            // Note: This potentially also accepts a non-static member.
            //{ T::typeName } -> std::same_as<TypeNameConstant>;
            { value.typeName } -> std::same_as<TypeNameConstant>;
        };

        template <typename T>
        concept typeName = type<T> && requires (T type) {
            { type.typeName() } -> std::same_as<TypeNameResult>;
        };

        template <typename T, typename U>
        concept sameType = type<T> && requires (T type, U const & other) {
            { type.sameType(other) } -> std::same_as<SameTypeResult>;
        };

        template <typename T, typename U>
        concept identicalType = type<T> && requires (T type, U const & other) {
            { type.identicalType(other) } -> std::same_as<SameTypeResult>;
        };

        template <typename T>
        concept constant = type<T> && requires (T type) {
            //{ T::constant } -> std::same_as<bool>;
            { type.constant } -> std::same_as<bool>;
        };

        template <typename T>
        concept loseConstness = type<T> && requires (T type) {
            { type.loseConstness() } -> std::same_as<bool>;
        };

        // There will be no implicit conversions in the first version.
        /*
        template <typename T, typename U>
        concept commonType = type<T> && requires (T type, U const & other) {
            { type.commonType(other) } -> std::same_as<CommonTypeResult>;
        };
        */

        /*
        template <typename T>
        concept constType = type<T> && requires (T type) {
            { type.constType() } -> std::same_as<ConstTypeResult>;
        };
        */

        /*
        template <typename T>
        concept translateType = type<T> && requires (T type, context::Main & ctx) {
            { type.translateType(ctx) } -> std::same_as<TypeTranslationResult>;
        };
        */

        template <typename T>
        concept translateType = type<T> && requires (T type) {
            { type.translateType() } -> std::same_as<TypeTranslationResult>;
        };

        template <typename T>
        concept translateTypeSpecifier = type<T> && requires (T type) {
            { type.translateTypeSpecifier() } -> std::same_as<TypeSpecifierTranslationResult>;
        };

        /*
        template <typename T>
        concept completeType = incompleteType<T> && requires (T type, context::Main & ctx) {
            { type.completeType(ctx) } -> std::same_as<TypeCompletionResult>;
        };
        */

        template <typename T>
        concept processDefinition = type<T> && requires (
            T type, context::Main & ctx, sem::ResolvedValue const * definition
        ) {
            { type.processDefinition(ctx, definition) } -> std::same_as<DefinitionProcessingResult>;
        };

        /*
        template <typename T>
        concept translateConversion = type<T> && requires (
            T type, context::Main & ctx, sem::ResolvedValue from
        ) {
            { type.translateConversion(ctx, from) } -> std::same_as<ConversionTranslationResult>;
        };
        */

        /*
        template <typename T>
        concept translateAllocation = type<T> && requires (
            T type, context::Main & ctx, std::optional<sem::ResolvedValue> initialization
        ) {
            { type.translateAllocation(ctx, initialization) } -> std::same_as<AllocationTranslationResult>;
        };
        */

        /*
        template <typename T>
        concept decayType = type<T> && requires (T type) {
            { type.decayType() } -> std::same_as<TypeDecayResult>;
        };
        */

    }

    // Functions:

    constexpr auto constant = esl::overload(
        [] (interface::has::constant auto const & type) -> bool {
            return type.constant;
        },
        [] <type T> (T const &) -> bool requires (!interface::has::constant<T>) {
            return false;
        }
    );

    constexpr auto loseConstness = esl::overload(
        [] (interface::has::loseConstness auto const & type) {
            return type.loseConstness();
        },
        [] <type T> (T const &) -> bool requires (!interface::has::loseConstness<T>) {
            // No-op.
        }
    );

    constexpr auto isSimple = esl::overload(
        [] (simpleType auto const &) -> bool {
            return true;
        },
        [] <type T> (T const &) -> bool requires (!simpleType<T>) {
            return false;
        }
    );

    template <interface::has::typeValue T>
    using TypeValue = typename T::TypeValue;

    constexpr auto directTypeName =
        [] <has::directTypeName T> (T const & type) -> std::string {
            //return T::typeName;
            return type.typeName;
        };

    constexpr auto typeName = esl::overload(
        [] <has::directTypeName T> (T const & type) -> TypeNameResult {
            //return std::string{T::typeName};
            return std::string{type.typeName};
        },
        [] <has::typeName T> (T const & type) -> TypeNameResult requires (!has::directTypeName<T>) {
            return type.getTypeName();
        },
        [] <type T> (T const & type) -> TypeNameResult requires (!has::typeName<T> && !has::directTypeName<T>) {
            return esl::result_error{"This type does not have a name."};
        }
    );

    constexpr auto sameTypes = esl::overload(
        [] <type T, type U> (T const & type, U const & as) -> SameTypeResult
        requires (has::sameType<T, U>) {
            return type.sameType(as);
        },
        [] (type auto const &, type auto const &) -> SameTypeResult {
            return false;
        }
    );

    constexpr auto sameType = [] <type T> (T const & t) {
        return esl::overload(
            [&t] <type U> (U const & as) -> SameTypeResult
            requires (has::sameType<T, U>) {
                return t.sameType(as);
            },
            [] (type auto const &) -> SameTypeResult {
                return false;
            }
        );
    };

    constexpr auto identicalTypes = esl::overload(
        [] <type T, type U> (T const & type, U const & as) -> SameTypeResult
        requires (has::identicalType<T, U>) {
            return type.identicalType(as);
        },
        [] (type auto const &, type auto const &) -> SameTypeResult {
            return false;
        }
    );

    constexpr auto identicalType = [] <type T> (T const & t) {
        return esl::overload(
            [&t] <type U> (U const & as) -> SameTypeResult
            requires (has::identicalType<T, U>) {
                return t.identicalType(as);
            },
            [] (type auto const &) -> SameTypeResult {
                return false;
            }
        );
    };

    template <typename... Targets>
    constexpr auto sameTypeTupleLift = [] (auto const & type, auto const & as) -> SameTypeResult {
        // Lift over two sized ranges will return an error for ranges of different sizes.
        // TODO: Maybe it should return an empty optional or something,
        // as this function shows that different sized inputs don't necessarilly mean an error.
        auto result = esl::lift<esl::target::tiny_vector, Targets...>(sameType)(type, as);
        return result && esl::all(*result); // same size && same contents
    };

    constexpr auto sameTypeTuple = sameTypeTupleLift<>;

    /*
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
    */

    /*
    constexpr auto constType = esl::overload(
        [] <type T> (T const & type) -> ConstTypeResult
        requires (has::constType<T>) {
            return type.constType();
        },
        [] (type auto const &) -> ConstTypeResult {
            return false;
        }
    );
    */

    /*
    constexpr auto translateType (context::Main & ctx) {
        return esl::overload(
            [&ctx] <has::translateType T> (T const & type) -> TypeTranslationResult {
                return type.translateType(ctx);
            },
            [] (type auto const &) -> TypeTranslationResult {
                return esl::result_error{"This type cannot be translated."};
            }
        );
    }
    */

    constexpr auto translateType = esl::overload(
        [] <has::translateType T> (T const & type) -> esl::result<TypeTranslationResult> {
            return type.translateType();
        },
        [] (type auto const &) -> esl::result<TypeTranslationResult> {
            return esl::result_error{"This type cannot be translated."};
        }
    );

    constexpr auto translateTypeSpecifier = esl::overload(
        [] <has::translateType T> (T const & type) -> esl::result<TypeSpecifierTranslationResult> {
            return type.translateTypeSpecifier();
        },
        [] (type auto const &) -> esl::result<TypeSpecifierTranslationResult> {
            return esl::result_error{"This type cannot be translated into a type specifier."};
        }
    );

    constexpr auto processDefinition (context::Main & ctx) {
        return [&ctx] (sem::ResolvedValue const & definition) {
            return esl::overload(
                [&ctx, &definition] <has::processDefinition T> (T const & type) -> DefinitionProcessingResult {
                    return type.processDefinition(ctx, &definition);
                },
                [] (type auto const &) -> DefinitionProcessingResult {
                    return esl::result_error{"A definition of this type cannot be translated."};
                }
            );
        };
    }

    constexpr auto processDeclaration (context::Main & ctx) {
        return esl::overload(
            [&ctx] <has::processDefinition T> (T const & type) -> DeclarationProcessingResult {
                return type.processDefinition(ctx, nullptr);
            },
            [] (type auto const &) -> DeclarationProcessingResult {
                return esl::result_error{"A declaration of this type cannot be translated."};
            }
        );
    }

    /*
    constexpr auto translateAllocation (context::Main & ctx, std::optional<sem::TypedExpression> const & initialization) {
        return esl::overload(
            [&ctx, &initialization] <has::translateAllocation T> (T const & type) -> AllocationTranslationResult {
                return type.translateAllocation(ctx, initialization);
            },
            [] (auto const &) -> AllocationTranslationResult {
                return esl::result_error{"An allocation of this type cannot be translated."};
            }
        );
    }
    */

    /*
    constexpr auto translateConversion (context::Main & ctx, sem::TypedExpression const & from) {
        return esl::overload(
            [&ctx, &from] <has::translateConversion T> (T const & type) -> ConversionTranslationResult {
                return type.translateConversion(ctx, from);
            },
            [] (type auto const &) -> ConversionTranslationResult {
                return esl::result_error{"A conversion to this type cannot be translated."};
            }
        );
    }
    */

#if 0
    constexpr auto completeType (context::Main & ctx) {
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
#endif

#if 0
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
#endif

# if 0
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
#endif

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
            for (auto & decl: decls) for (auto & type: decl.type) {
                result.push_back(esl::forward_like<Decls>(type));
            }
            return result;
        },
        [] <esl::range_of<sem::IncompleteRangeDeclaration> Decls> (Decls && decls) -> esl::tiny_vector<sem::IncompleteType> {
            esl::tiny_vector<sem::IncompleteType> result;
            for (auto & decl: decls) for (auto & type: decl.type) {
                result.push_back(esl::forward_like<Decls>(type));
            }
            return result;
        }
        */
    );

    namespace detail {

        constexpr auto makeDeclComplete = [] (context::Main & ctx) {
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

        constexpr auto makeRangeDeclComplete = [] (context::Main & ctx) {
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
