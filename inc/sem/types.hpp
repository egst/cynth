#pragma once

#include "esl/type_manip.hpp"
#include "esl/result.hpp"
#include "esl/component.hpp"
#include "esl/category.hpp"

#include "common_interface_types.hpp"
#include "sem/numeric_types.hpp"
#include "sem/interface_types.hpp"

#include <type_traits>
#include <variant>

// Note: No macros escape this file.
#define TYPE \
    DisplayResult display () const; \
    TypeTranslationResult translateType () const

#define COMMON(type) \
    CommonTypeResult common (type const &) const

#define SAME(type) \
    SameTypeResult same (type const &) const

#define DECAY() \
    TypeDecayResult decay () const

#define INCOMPLETE_TYPE \
    TypeCompletionResult complete (Context &) const

namespace cynth::sem {

    namespace type {

        struct Bool {
            TYPE;

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
            TYPE;

            // implicit common(Bool)
            COMMON(type::Int);
            COMMON(type::Float);
            COMMON(type::In);
            COMMON(type::Const);

            SAME(type::Int);
        };

        struct Float {
            TYPE;

            // implicit common(Bool)
            // implicit common(Int)
            COMMON(type::Float);
            COMMON(type::In);
            COMMON(type::Const);

            SAME(type::Float);
        };

        /** Strings will not be used in the first versions. */
        struct String {
            TYPE;

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
                esl::component<IncompleteValue>
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
            TYPE;

            // implicit common(Bool)
            // implicit common(Int)
            // implicit common(Float)

            SAME(type::In);

            DECAY();
        };

        struct Out: detail::types::Out<true> {
            TYPE;

            SAME(type::Out);

            DECAY();
        };

        struct Const: detail::types::Const<true> {
            TYPE;

            // implicit common(Bool)
            // implicit common(Int)
            // implicit common(Float)
            COMMON(type::Const);

            SAME(type::Const);

            DECAY();
        };

        struct Array: detail::types::Array<true> {
            TYPE;

            COMMON(type::Array);

            SAME(type::Array);

            constexpr static esl::result<type::Array> make (esl::tiny_component_vector<CompleteType> &&, Integral);
        };

        struct Buffer: detail::types::Buffer<true> {
            TYPE;

            COMMON(type::Buffer);

            SAME(type::Buffer);

            constexpr static esl::result<type::Buffer> make (Integral);
        };

        struct Function: detail::types::Function<true> {
            TYPE;

            COMMON(type::Function);

            SAME(type::Function);
        };

        struct IncompleteIn: detail::types::In<false> {
            INCOMPLETE_TYPE;
        };

        struct IncompleteOut: detail::types::Out<false> {
            INCOMPLETE_TYPE;
        };

        struct IncompleteConst: detail::types::Const<false> {
            INCOMPLETE_TYPE;
        };

        struct IncompleteArray: detail::types::Array<false> {
            INCOMPLETE_TYPE;
        };

        struct IncompleteBuffer: detail::types::Buffer<false> {
            INCOMPLETE_TYPE;
        };

        struct IncompleteFunction: detail::types::Function<false> {
            INCOMPLETE_TYPE;
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

#undef TYPE
#undef COMMON
#undef SAME
#undef DECAY
#undef INCOMPLETE_TYPE
