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

// Note: No macros escape this file.
#define DIRECT_TYPE_NAME(name) \
    constexpr static interface::TypeNameConstant directTypeName = name
#define TYPE_NAME \
    interface::TypeNameResult typeName () const
#define SAME(type) \
    interface::SameTypeResult sameType (type const &) const
#define CONST(type) \
    interface::ConstTypeResult constType () const
#define COMMON(type) \
    interface::CommonTypeResult commonType (type const &) const
#define TYPE_INTERFACE \
    interface::DisplayResult display () const; \
    interface::DefinitionTranslationResult translateDefinition ( \
        context::C &, \
        std::optional<TypedResolvedValue> const & definition \
    ) const; \
    interface::AllocationTranslationResult translateAllocation ( \
        context::C &, \
        std::optional<TypedResolvedValue> const & definition \
    ) const; \
    interface::ConversionTranslationResult translateConversion ( \
        context::C &, \
        TypedResolvedValue const & from \
    ) const;
#define INCOMPLETE_TYPE_INTERFACE \
    interface::TypeCompletionResult completeType (context::C &) const

/*
#define DECAY \
    interface::TypeDecayResult decayType () const
*/

namespace cynth::sem {

    namespace type {

        struct Bool {
            TYPE_INTERFACE;

            DIRECT_TYPE_NAME(str::boolean);

            COMMON(type::Bool);
            COMMON(type::Int);
            COMMON(type::Float);
            COMMON(type::In);
            COMMON(type::Const);

            SAME(type::Bool);

            // TODO?
            //constexpr static CompleteType make ();
        };

        struct Int {
            TYPE_INTERFACE;

            DIRECT_TYPE_NAME(str::integral);

            // implicit common(Bool)
            COMMON(type::Int);
            COMMON(type::Float);
            COMMON(type::In);
            COMMON(type::Const);

            SAME(type::Int);
        };

        struct Float {
            TYPE_INTERFACE;

            DIRECT_TYPE_NAME(str::floating);

            // implicit common(Bool)
            // implicit common(Int)
            COMMON(type::Float);
            COMMON(type::In);
            COMMON(type::Const);

            SAME(type::Float);
        };

        /** Strings will not be used in the first versions. */
        struct String {
            TYPE_INTERFACE;

            DIRECT_TYPE_NAME(str::string);

            COMMON(type::String);

            SAME(type::String);
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
            struct Const {
                esl::component<Type<Complete>> type;
            };

            template <bool Complete>
            using Size = std::conditional_t <
                Complete,
                Integral,
                esl::component<IncompleteValue> // TODO: This makes types dependant on values.
            >;

            template <bool Complete>
            struct Array {
                esl::component_vector<Type<Complete>> type;
                Size<Complete> size;
            };

            template <bool Complete>
            struct Buffer {
                constexpr static char const * sampleType = "float"; // TODO?
                Size<Complete> size;
            };

            template <bool Complete>
            struct Function {
                esl::component_vector<Type<Complete>> out;
                esl::component_vector<Type<Complete>> in;
            };

        }

        struct In: detail::types::In<true> {
            using detail::types::In<true>::type;

            TYPE_INTERFACE;

            // implicit common(Bool)
            // implicit common(Int)
            // implicit common(Float)

            SAME(type::In);

            //DECAY;
        };

        struct Out: detail::types::Out<true> {
            TYPE_INTERFACE;

            SAME(type::Out);

            //DECAY;
        };

        struct Const: detail::types::Const<true> {
            TYPE_INTERFACE;

            TYPE_NAME;

            // implicit common(Bool)
            // implicit common(Int)
            // implicit common(Float)
            COMMON(type::Const);
            COMMON(type::Array);

            SAME(type::Const);

            CONST();

            //DECAY;
        };

        struct Array: detail::types::Array<true> {
            TYPE_INTERFACE;

            // implicit coomon(Const)
            COMMON(type::Array);

            SAME(type::Array);

            static esl::result<type::Array> make (esl::component_vector<CompleteType> &&, Integral);
        };

        struct Buffer: detail::types::Buffer<true> {
            TYPE_INTERFACE;

            COMMON(type::Buffer);

            SAME(type::Buffer);

            CONST();

            static esl::result<type::Buffer> make (Integral);
        };

        struct Function: detail::types::Function<true> {
            TYPE_INTERFACE;

            COMMON(type::Function);

            SAME(type::Function);

            CONST();
        };

        struct IncompleteIn: detail::types::In<false> {
            INCOMPLETE_TYPE_INTERFACE;
        };

        struct IncompleteOut: detail::types::Out<false> {
            INCOMPLETE_TYPE_INTERFACE;
        };

        struct IncompleteConst: detail::types::Const<false> {
            INCOMPLETE_TYPE_INTERFACE;
        };

        struct IncompleteArray: detail::types::Array<false> {
            INCOMPLETE_TYPE_INTERFACE;
        };

        struct IncompleteBuffer: detail::types::Buffer<false> {
            INCOMPLETE_TYPE_INTERFACE;
        };

        struct IncompleteFunction: detail::types::Function<false> {
            INCOMPLETE_TYPE_INTERFACE;
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
            type::Const,
            type::In,
            type::Out,
            type::Array,
            type::Buffer,
            type::Function
        >;

        using Incomplete = esl::extend<
            Complete,
            type::IncompleteConst,
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

#undef DIRECT_TYPE_NAME
#undef TYPE_NAME
#undef SAME
#undef COMMON
#undef TYPE_INTERFACE
#undef INCOMPLETE_TYPE_INTERFACE

//#undef DECAY
