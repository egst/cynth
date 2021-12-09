#pragma once

#include <variant>
#include <vector>
#include <string>

#include "esl/type_manip.hpp"
#include "esl/result.hpp"
#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/view.hpp"

#include "ast/forward_categories.hpp"
#include "sem/forward.hpp"
#include "sem/interface_types.hpp"
#include "sem/numeric_types.hpp"
#include "sem/types.hpp"
#include "common_interface_types.hpp"

// Note: No macros escape this file.
#define VALUE \
    DisplayResult display () const; \
    ValueTypeResult valueType () const

#define GET(type) \
    GetResult<type> get () const

#define CONVERSION(type) \
    ConversionResult convert (Context &, type const &) const

namespace cynth::sem {

    namespace value {

        struct Bool {
            bool value;

            VALUE;

            GET(bool);

            CONVERSION(type::Bool);
            CONVERSION(type::Int);
            CONVERSION(type::Float);
            CONVERSION(type::Const);

            constexpr static CompleteValue make (bool); //return sem::value::Bool{.value = value};
        };

        struct Int {
            Integral value;

            VALUE;

            GET(Integral);

            CONVERSION(type::Bool);
            CONVERSION(type::Int);
            CONVERSION(type::Float);
            CONVERSION(type::Const);

            constexpr static CompleteValue make (Integral); //return sem::value::Int{.value = value};
        };

        struct Float {
            Floating value;

            VALUE;

            GET(Floating);

            CONVERSION(type::Bool);
            CONVERSION(type::Int);
            CONVERSION(type::Float);
            CONVERSION(type::Const);

            constexpr static CompleteValue make (Floating); //return sem::value::Float{.value = value};
        };

        struct String {
            std::string value;

            VALUE;

            GET(std::string);

            constexpr static CompleteValue make (std::string); //return sem::value::Sting{.value = value};
        };

        /** Constant values will not be used in the first versions. */
        struct Const {
            esl::component<CompleteValue> value;

            VALUE;

            CONVERSION(type::Bool);
            CONVERSION(type::Int);
            CONVERSION(type::Float);
            CONVERSION(type::Const);
            CONVERSION(type::Array);
        };

        struct InValue {
            esl::component<CompleteValue> value;
        };

        struct In {
            InValue * value;
            esl::component<CompleteValue> type;

            VALUE;

            CONVERSION(type::Bool);
            CONVERSION(type::Int);
            CONVERSION(type::Float);
            CONVERSION(type::In);
            CONVERSION(type::Const);
            CONVERSION(type::Buffer);
        };

        struct OutValue {
            esl::component<CompleteValue> value;
        };

        struct Out {
            OutValue * value;
            esl::component<CompleteValue> type;

            VALUE;

            CONVERSION(type::Out);
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

            VALUE;

            GET(std::vector<esl::tiny_vector<CompleteValue>>);

            CONVERSION(type::Array);
            CONVERSION(type::Const);

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

            VALUE;

            CONVERSION(type::Buffer);

            constexpr static esl::result<CompleteValue> make (value::BufferValue *, Integral);
        };

        struct FunctionValue {
            using Body = ast::category::Expression;

            esl::component_vector<CompleteType> out_type;
            esl::component_vector<CompleteDeclaration> parameters;
            esl::component<Body> body;
            esl::component<Context> capture;
        };

        struct Function {
            FunctionValue * value;

            VALUE;

            GET(Function);

            CONVERSION(type::Function);
            CONVERSION(type::Buffer);
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

#undef VALUE
#undef GET
#undef CONVERSION
