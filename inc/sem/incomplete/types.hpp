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
#define VALUE(Type) \
    using Value = Type;
#define STATIC_TYPE_NAME(name) \
    constexpr static interface::TypeNameConstant typeName = name
#define TYPE_NAME \
    interface::TypeNameResult typeName () const
#define SAME(Type) \
    interface::SameTypeResult sameType (Type const &) const
#define COMMON(Type) \
    interface::CommonTypeResult commonType (Type const &) const
#define TYPE_INTERFACE \
    interface::DisplayResult display () const; \
    interface::TypeTranslationResult translateType() const; \
    interface::TypeSpecifierTranslationResult translateTypeSpecifier() const; \
    interface::DefinitionProcessingResult processDefinition ( \
        context::Main &, \
        std::optional<ResolvedValue> const & definition \
    ) const; \
    interface::ConversionTranslationResult translateConversion ( \
        context::Main &, \
        TypedExpression const & from \
    ) const;
    /*
    interface::AllocationTranslationResult translateAllocation ( \
        context::Main &, \
        std::optional<TypedExpression> const & definition \
    ) const; \
    */
#define INCOMPLETE_TYPE_INTERFACE \
    interface::TypeCompletionResult completeType (context::Main &) const

/*
#define DECAY \
    interface::TypeDecayResult decayType () const
*/

namespace cynth::sem {

    namespace type {

        struct Bool {
            bool constant;

            TYPE_INTERFACE;

            VALUE(value::Bool);

            STATIC_TYPE_NAME(str::boolean);

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
            bool constant;

            TYPE_INTERFACE;

            VALUE(value::Int);

            STATIC_TYPE_NAME(str::integral);

            // implicit common(Bool)
            COMMON(type::Int);
            COMMON(type::Float);
            COMMON(type::In);
            COMMON(type::Const);

            SAME(type::Int);
        };

        struct Float {
            bool constant;

            TYPE_INTERFACE;

            VALUE(value::Float);

            STATIC_TYPE_NAME(str::floating);

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

            VALUE(value::String);

            STATIC_TYPE_NAME(str::string);

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

            TYPE_INTERFACE;

            VALUE(value::In);

            // implicit common(Bool)
            // implicit common(Int)
            // implicit common(Float)

            SAME(type::In);

            //DECAY;
        };

        struct Out: detail::types::Out<true> {
            TYPE_INTERFACE;

            VALUE(value::Out);

            SAME(type::Out);

            //DECAY;
        };

        struct Array: detail::types::Array<true> {
            /*
            using base = detail::types::Array<true>;
            using base::type;
            using base::size;
            using base::constval;
            using base::constref;
            */

            TYPE_INTERFACE;

            VALUE(value::Array);

            COMMON(type::Array);

            SAME(type::Array);
        };

        struct Buffer: detail::types::Buffer<true> {
            TYPE_INTERFACE;

            VALUE(value::Buffer);

            COMMON(type::Buffer);

            SAME(type::Buffer);

            static esl::result<type::Buffer> make (Integral);
        };

        struct Function: detail::types::Function<true> {
            esl::component_vector<CompleteType> in;
            esl::component_vector<CompleteType> out;

            TYPE_INTERFACE;

            VALUE(value::Function);

            COMMON(type::Function);

            SAME(type::Function);
        };

        struct IncompleteIn: detail::types::In<false> {
            INCOMPLETE_TYPE_INTERFACE;
        };

        struct IncompleteOut: detail::types::Out<false> {
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

#undef VALUE
#undef STATIC_TYPE_NAME
#undef TYPE_NAME
#undef SAME
#undef COMMON
#undef TYPE_INTERFACE
#undef INCOMPLETE_TYPE_INTERFACE

//#undef DECAY
