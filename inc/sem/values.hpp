#pragma once

#include "config.hpp"
#include "category_base.hpp"
#include "view.hpp"
#include "component.hpp"
#include "result.hpp"
#include "common_interface_types.hpp"
#include "sem/context_forward.hpp"
#include "sem/forward.hpp"
#include "sem/interface_types.hpp"
#include "ast/categories_forward.hpp"
#include "util/general.hpp"

#include <string>
#include <vector>
#include <type_traits>

// Note: Macros are always undefined at the end of the file.
#define VALUE_DECL \
    display_result    display    () const; \
    value_type_result value_type () const

namespace cynth::sem::value {

    struct Bool {
        bool value;

        get_result<bool> get () const;

        conversion_result convert (context &, type::Bool  const &) const;
        conversion_result convert (context &, type::Int   const &) const;
        conversion_result convert (context &, type::Float const &) const;
        conversion_result convert (context &, type::Const const &) const; // TODO

        VALUE_DECL;
    };

    struct Int {
        integral value;

        get_result<integral> get () const;

        conversion_result convert (context &, type::Bool  const &) const;
        conversion_result convert (context &, type::Int   const &) const;
        conversion_result convert (context &, type::Float const &) const;
        conversion_result convert (context &, type::Const const &) const; // TODO

        VALUE_DECL;
    };

    struct Float {
        floating value;

        get_result<floating> get () const;

        conversion_result convert (context &, type::Bool  const &) const;
        conversion_result convert (context &, type::Int   const &) const;
        conversion_result convert (context &, type::Float const &) const;
        conversion_result convert (context &, type::Const const &) const; // TODO

        VALUE_DECL;
    };

    struct String {
        string value;

        get_result<string> get () const;

        VALUE_DECL;
    };

    namespace detail {

        using simple = variant <
            value::Bool,
            value::Int,
            value::Float,
            value::String
        >;

    }

    struct simple: category_base<simple, detail::simple> {
        using base = category_base<simple, detail::simple>;
        using base::base;
    };

    /** Constant values will not be used in the first versions. */
    struct Const {
        component<value::complete> value;

        conversion_result convert (context &, type::Bool  const &) const;
        conversion_result convert (context &, type::Int   const &) const;
        conversion_result convert (context &, type::Float const &) const;
        conversion_result convert (context &, type::Const const &) const;
        conversion_result convert (context &, type::Array const &) const;

        VALUE_DECL;
    };

    struct InValue {
        component<value::complete> value;
    };

    struct In {
        InValue *                 value;
        component<type::complete> type;

        // TODO: In types should have a specified type
        // for the same purposes as out types and arrays:
        // Int in a;
        // Float in b = a; # a referential read view over a with a different type
        // Float c = a;    # reading implicitly converted values
        // Float out d;
        // Int out e = d;  # a referential write view over d with a different type
        // e[] = 2;        # writing implicitly converted values
        // Float [3] f;
        // Int [2] g = f;  # a referential view over f with a different type and size

        conversion_result convert (context &, type::Bool   const &) const;
        conversion_result convert (context &, type::Int    const &) const;
        conversion_result convert (context &, type::Float  const &) const;
        conversion_result convert (context &, type::In     const &) const;
        conversion_result convert (context &, type::Const  const &) const;
        conversion_result convert (context &, type::Buffer const &) const;

        VALUE_DECL;
    };

    struct OutValue {
        component<value::complete> value;
    };

    struct Out {
        OutValue *                value;
        component<type::complete> type;

        conversion_result convert (context &, type::Out const &) const;

        VALUE_DECL;
    };

    struct ArrayValue {
        using vector = component_vector<tuple_vector<value::complete>>;

        vector value;
    };

    struct Array {
        using vector = ArrayValue::vector;

        ArrayValue *                     value;
        component_vector<type::complete> type;
        integral                         size;

        view<ArrayValue::vector::iterator> trimmed_value () const;

        get_result<std::vector<tuple_vector<value::complete>>> get () const;

        conversion_result convert (context &, type::Array const &) const;
        conversion_result convert (context &, type::Const const &) const;

        VALUE_DECL;
    };

    struct FunctionValue;

    struct BufferValue {
        using sample_type = floating;
        using vector      = std::vector<floating>;

        vector          value;
        FunctionValue * generator;
    };

    struct Buffer {
        using sample_type = floating;
        using vector      = std::vector<sample_type>;

        BufferValue * value;
        integral      size;

        conversion_result convert (context &, type::Buffer const &) const;

        VALUE_DECL;
    };

    struct FunctionValue {
        component_vector <type::complete>            out_type;
        component_vector <complete_decl>             parameters;
        component        <ast::category::Expression> body;
        component        <context>                   capture;
    };

    struct Function {
        FunctionValue * value;

        get_result<Function> get () const;

        conversion_result convert (context &, type::Function const &) const;
        conversion_result convert (context &, type::Buffer   const &) const;

        VALUE_DECL;
    };

    /** Function templates will not be implemented in the first versions. */
    struct FunctionTemplate {
        // TODO
    };

    // Just some examples of unknown types and values:
    // Int       [Int       size] array
    // Int       [type Size size] array
    // type Elem [type Size size] array
    // $         [$         size] array
    // $         [$]              array
    // $         []               array
    struct unknown {
        optional_component<incomplete_decl> decl;
    };

    namespace detail {

        using any_base = util::extend <
            value::simple::variant,
            value::In,
            value::Out,
            value::Const,
            value::Array,
            value::Buffer,
            value::Function
        >;

        template <bool Complete>
        using any = std::conditional_t <
            Complete,
            any_base,
            util::extend <
                any_base,
                value::unknown
            >
        >;

    }

    template <bool Complete>
    struct any: category_base<any<Complete>, detail::any<Complete>, true> {
        using base = category_base<any<Complete>, detail::any<Complete>, true>;
        using base::base;
    };

    template struct any<true>;
    template struct any<false>;

    constexpr auto make_bool = [] (bool value) -> value::complete {
        return value::Bool{.value = value};
    };

    constexpr auto make_int = [] (integral value) -> value::complete {
        return value::Int{.value = value};
    };

    constexpr auto make_float = [] (floating value) -> value::complete {
        return value::Float{.value = value};
    };

    constexpr auto make_string = [] (string value) -> value::complete {
        return value::String{.value = value};
    };

    result<value::complete> make_array (value::ArrayValue *, component_vector<type::complete> &&, integral);

    result<value::complete> make_buffer (value::BufferValue *, integral);

}

#undef VALUE_DECL
