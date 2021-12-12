#pragma once

#include <string>
#include <variant>
#include <vector>

#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/type_manip.hpp"
#include "esl/view.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"
#include "sem/numeric_types.hpp"
#include "sem/types.hpp"
#include "syn/categories/expression.hpp"

// Circular dependencies:
#include "sem/forward.hpp"

// Note: No macros escape this file.
#define GET(type) \
    interface::GetResult<type> get () const
#define CONVERT(type) \
    interface::ConversionResult convert (context::C &, type const &) const
#define VALUE_INTERFACE \
    interface::DisplayResult display () const; \
    interface::ValueTypeResult valueType () const

namespace cynth::sem {

    namespace value {

        struct Bool {
            bool value;

            VALUE_INTERFACE;

            GET(bool);

            CONVERT(type::Bool);
            CONVERT(type::Int);
            CONVERT(type::Float);
            CONVERT(type::Const);

            constexpr static CompleteValue make (bool); //return sem::value::Bool{.value = value};
        };

        struct Int {
            Integral value;

            VALUE_INTERFACE;

            GET(Integral);

            CONVERT(type::Bool);
            CONVERT(type::Int);
            CONVERT(type::Float);
            CONVERT(type::Const);

            constexpr static CompleteValue make (Integral); //return sem::value::Int{.value = value};
        };

        struct Float {
            Floating value;

            VALUE_INTERFACE;

            GET(Floating);

            CONVERT(type::Bool);
            CONVERT(type::Int);
            CONVERT(type::Float);
            CONVERT(type::Const);

            constexpr static CompleteValue make (Floating); //return sem::value::Float{.value = value};
        };

        struct String {
            std::string value;

            VALUE_INTERFACE;

            GET(std::string);

            constexpr static CompleteValue make (std::string); //return sem::value::Sting{.value = value};
        };

        /** Constant values will not be used in the first versions. */
        struct Const {
            esl::component<CompleteValue> value;

            VALUE_INTERFACE;

            CONVERT(type::Bool);
            CONVERT(type::Int);
            CONVERT(type::Float);
            CONVERT(type::Const);
            CONVERT(type::Array);
        };

        struct InValue {
            esl::component<CompleteValue> value;
        };

        struct In {
            InValue * value;
            esl::component<CompleteValue> type;

            VALUE_INTERFACE;

            CONVERT(type::Bool);
            CONVERT(type::Int);
            CONVERT(type::Float);
            CONVERT(type::In);
            CONVERT(type::Const);
            CONVERT(type::Buffer);
        };

        struct OutValue {
            esl::component<CompleteValue> value;
        };

        struct Out {
            OutValue * value;
            esl::component<CompleteValue> type;

            VALUE_INTERFACE;

            CONVERT(type::Out);
        };

        template <template <typename...> typename Base>
        struct vector_param {
            template <typename T>
            struct test_vector: Base<T> {};
        };

        template <typename T, template <typename...> typename Base>
        using basic_test_vector = typename vector_param<Base>::template test_vector<T>;

        template <typename T> using test_vector      = basic_test_vector<T, std::vector>;
        template <typename T> using tiny_test_vector = basic_test_vector<T, esl::tiny_vector>;

        struct ArrayValue {
            using Vector = esl::component_vector<esl::tiny_vector<CompleteValue>>;

            Vector value;
        };

        struct Array {
            using Vector = ArrayValue::Vector;

            ArrayValue * value;
            esl::component_vector<CompleteType> type;
            Integral size;

            VALUE_INTERFACE;

            GET(std::vector<esl::tiny_vector<CompleteValue>>);

            CONVERT(type::Array);
            CONVERT(type::Const);

            static esl::result<CompleteValue> make (
                value::ArrayValue *,
                esl::component_vector<CompleteType> &&, // TODO: allow lvalues here
                Integral
            );

            esl::view<Vector::iterator> trimmed_value () const;
        };

        struct FunctionValue;

        struct BufferValue {
            using Sample = Floating;
            using Vector = std::vector<Floating>;

            Vector value;
            FunctionValue * generator;
        };

        struct Buffer {
            using Sample = BufferValue::Sample;
            using Vector = std::vector<Sample>;

            BufferValue * value;
            Integral size;

            VALUE_INTERFACE;

            CONVERT(type::Buffer);

            constexpr static esl::result<CompleteValue> make (value::BufferValue *, Integral);
        };

        struct FunctionValue {
            using Body = syn::category::Expression;

            esl::component_vector<CompleteType> out_type;
            esl::component_vector<CompleteDeclaration> parameters;
            esl::component<Body> body;
            esl::component<context::Cynth> capture;
        };

        struct Function {
            FunctionValue * value;

            VALUE_INTERFACE;

            GET(Function);

            CONVERT(type::Function);
            CONVERT(type::Buffer);
        };

        struct Unknown {
            esl::optional_component<IncompleteDeclaration> decl;
        };

    }

    namespace detail::values {

        using Simple = std::variant<
            value::Bool,
            value::Int,
            value::Float,
            value::String
        >;

        using Complete = esl::extend<
            Simple,
            value::In,
            value::Out,
            value::Const,
            value::Array,
            value::Buffer,
            value::Function
        >;

        using Incomplete = esl::extend<
            Complete,
            value::Unknown
        >;

    }

    struct CompleteValue: esl::category<CompleteValue, detail::values::Complete> {
        using Base = esl::category<CompleteValue, detail::values::Complete>;
        using Base::Base;
    };

    struct IncompleteValue: esl::category<IncompleteValue, detail::values::Incomplete> {
        using Base = esl::category<IncompleteValue, detail::values::Incomplete>;
        using Base::Base;
    };

}

#undef GET
#undef CONVERT
#undef VALUE_INTERFACE
