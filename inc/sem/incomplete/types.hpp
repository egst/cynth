#pragma once

#include <type_traits>
#include <variant>
#include <optional>

#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/result.hpp"
#include "esl/type_manip.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"
#include "sem/numeric_types.hpp"
#include "sem/translation.hpp"

// Circular dependencies:
#include "sem/forward.hpp"

namespace cynth::sem {

    namespace type {

        struct Bool {
            bool constant;

            interface::DisplayResult                  display                () const;
            interface::TypeTranslationResult          translateType          () const;
            interface::TypeSpecifierTranslationResult translateTypeSpecifier () const;
            interface::DefinitionProcessingResult     processDefinition (
                context::Main &,
                std::optional<ResolvedValue> const &
            ) const;

            using Value = value::Bool;

            constexpr static interface::TypeNameConstant typeName = str::boolean;

            interface::SameTypeResult sameType (type::Bool const &) const;
        };

        struct Int {
            bool constant;

            interface::DisplayResult                  display                () const;
            interface::TypeTranslationResult          translateType          () const;
            interface::TypeSpecifierTranslationResult translateTypeSpecifier () const;
            interface::DefinitionProcessingResult     processDefinition (
                context::Main &,
                std::optional<ResolvedValue> const &
            ) const;

            using Value = value::Int;

            constexpr static interface::TypeNameConstant typeName = str::integral;

            interface::SameTypeResult sameType (type::Int const &) const;
        };

        struct Float {
            bool constant;

            interface::DisplayResult                  display                () const;
            interface::TypeTranslationResult          translateType          () const;
            interface::TypeSpecifierTranslationResult translateTypeSpecifier () const;
            interface::DefinitionProcessingResult     processDefinition (
                context::Main &,
                std::optional<ResolvedValue> const &
            ) const;

            using Value = value::Float;

            constexpr static interface::TypeNameConstant typeName = str::floating;

            interface::SameTypeResult sameType (type::Float const &) const;
        };

        /** Strings will not be used in the first versions. */
        struct String {
            interface::DisplayResult                  display                () const;
            interface::TypeTranslationResult          translateType          () const;
            interface::TypeSpecifierTranslationResult translateTypeSpecifier () const;
            interface::DefinitionProcessingResult     processDefinition (
                context::Main &,
                std::optional<ResolvedValue> const &
            ) const;

            using Value = value::String;

            constexpr static interface::TypeNameConstant typeName = str::string;

            interface::SameTypeResult sameType (type::String const &) const;
        };

        namespace detail::types {

            template <bool Complete>
            struct In {
                esl::component<Type<Complete>> type;
            };

            template <bool Complete>
            struct Out {
                esl::component<Type<Complete>> type;
            };

            template <bool Complete>
            using Size = std::conditional_t <
                Complete,
                Integral,
                esl::component<IncompleteValue> // TODO: This makes types dependant on values.
            >;

            // TODO: Figure out a way to work with arrays of tuples.
            template <bool Complete>
            struct Array {
                esl::component<Type<Complete>> type;
                Size<Complete>                 size;
                bool                           constval;
                bool                           constref;
            };

            template <bool Complete>
            struct Buffer {
                Size<Complete> size;
            };

            template <bool Complete>
            struct Function {
                // TODO
            };

        }

        struct In: detail::types::In<true> {
            using detail::types::In<true>::type;

            interface::DisplayResult                  display                () const;
            interface::TypeTranslationResult          translateType          () const;
            interface::TypeSpecifierTranslationResult translateTypeSpecifier () const;
            interface::DefinitionProcessingResult     processDefinition (
                context::Main &,
                std::optional<ResolvedValue> const &
            ) const;

            using Value = value::In;

            // implicit common(Bool)
            // implicit common(Int)
            // implicit common(Float)

            interface::SameTypeResult sameType (type::In const &) const;
        };

        struct Out: detail::types::Out<true> {
            interface::DisplayResult                  display                () const;
            interface::TypeTranslationResult          translateType          () const;
            interface::TypeSpecifierTranslationResult translateTypeSpecifier () const;
            interface::DefinitionProcessingResult     processDefinition (
                context::Main &,
                std::optional<ResolvedValue> const &
            ) const;

            using Value = value::Out;

            interface::SameTypeResult sameType (type::Out const &) const;
        };

        struct Array: detail::types::Array<true> {
            interface::DisplayResult                  display                () const;
            interface::TypeTranslationResult          translateType          () const;
            interface::TypeSpecifierTranslationResult translateTypeSpecifier () const;
            interface::DefinitionProcessingResult     processDefinition (
                context::Main &,
                std::optional<ResolvedValue> const &
            ) const;

            using Value = value::Array;

            interface::SameTypeResult sameType (type::Array const &) const;
        };

        struct Buffer: detail::types::Buffer<true> {
            interface::DisplayResult                  display                () const;
            interface::TypeTranslationResult          translateType          () const;
            interface::TypeSpecifierTranslationResult translateTypeSpecifier () const;
            interface::DefinitionProcessingResult     processDefinition (
                context::Main &,
                std::optional<ResolvedValue> const &
            ) const;

            using Value = value::Buffer;

            interface::SameTypeResult sameType (type::Buffer const &) const;

            static esl::result<type::Buffer> make (Integral);
        };

        struct Function: detail::types::Function<true> {
            esl::component_vector<CompleteType> in;
            esl::component_vector<CompleteType> out;

            interface::DisplayResult                  display                () const;
            interface::TypeTranslationResult          translateType          () const;
            interface::TypeSpecifierTranslationResult translateTypeSpecifier () const;
            interface::DefinitionProcessingResult     processDefinition (
                context::Main &,
                std::optional<ResolvedValue> const &
            ) const;

            using Value = value::Function;

            interface::SameTypeResult sameType (type::Function const &) const;
        };

        struct IncompleteIn: detail::types::In<false> {
            interface::TypeCompletionResult completeType (context::Main &) const;
        };

        struct IncompleteOut: detail::types::Out<false> {
            interface::TypeCompletionResult completeType (context::Main &) const;
        };

        struct IncompleteArray: detail::types::Array<false> {
            interface::TypeCompletionResult completeType (context::Main &) const;
        };

        struct IncompleteBuffer: detail::types::Buffer<false> {
            interface::TypeCompletionResult completeType (context::Main &) const;
        };

        struct IncompleteFunction: detail::types::Function<false> {
            interface::TypeCompletionResult completeType (context::Main &) const;
        };

        struct Unknown {
            esl::optional_component<TypeDeclaration> declaration;
        };

    }

    namespace detail::types {

        using Simple = std::variant <
            type::Bool,
            type::Int,
            type::Float,
            type::String
        >;

        using Complete = esl::extend<
            Simple,
            type::In,
            type::Out,
            type::Array,
            type::Buffer,
            type::Function
        >;

        using Incomplete = esl::extend<
            Complete,
            type::IncompleteIn,
            type::IncompleteOut,
            type::IncompleteArray,
            type::IncompleteBuffer,
            type::IncompleteFunction,
            type::Unknown
        >;

    }

    struct CompleteType: esl::category<CompleteType, detail::types::Complete> {
        using Base = esl::category<CompleteType, detail::types::Complete>;
        using Base::Base;
    };

    struct IncompleteType: esl::category<IncompleteType, detail::types::Incomplete> {
        using Base = esl::category<IncompleteType, detail::types::Incomplete>;
        using Base::Base;
    };

}
