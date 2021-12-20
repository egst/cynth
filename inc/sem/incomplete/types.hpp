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
    interface::DefinitionProcessingResult processDefinition ( \
        context::C &, \
        std::optional<ResolvedValue> const & definition \
    ) const; \
    interface::ConversionTranslationResult translateConversion ( \
        context::C &, \
        TypedExpression const & from \
    ) const;
    /*
    interface::AllocationTranslationResult translateAllocation ( \
        context::C &, \
        std::optional<TypedExpression> const & definition \
    ) const; \
    */
#define INCOMPLETE_TYPE_INTERFACE \
    interface::TypeCompletionResult completeType (context::C &) const

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
            TYPE_INTERFACE;

            VALUE(value::Array);

            COMMON(type::Array);

            SAME(type::Array);

            static esl::result<type::Array> make (esl::component_vector<CompleteType> &&, Integral);
        };

        struct Buffer: detail::types::Buffer<true> {
            TYPE_INTERFACE;

            VALUE(value::Buffer);

            COMMON(type::Buffer);

            SAME(type::Buffer);

            static esl::result<type::Buffer> make (Integral);
        };

        struct Function: detail::types::Function<true> {
            // TODO: Which of these really need to be in a component?

            esl::component_vector<CompleteType> out;
            esl::component_vector<CompleteType> in;

            esl::optional_component<sem::ResolvedCapturedContext> context;
            std::optional<std::string> contextType;     // Runtime context type
            std::optional<std::string> contextVariable; // Runtime context variable
            std::optional<std::string> functionName;    // Runtime function name

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
