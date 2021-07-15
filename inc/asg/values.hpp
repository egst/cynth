#pragma once

#include "config.hpp"
#include "context_forward.hpp"
#include "category_base.hpp"
#include "component.hpp"
#include "result.hpp"
#include "asg/forward.hpp"
#include "asg/interface_types.hpp"
#include "ast/categories_forward.hpp"
#include "util/general.hpp"

#include <string>
#include <vector>
#include <type_traits>

namespace cynth::asg::value {

    struct Bool {
        bool value;

        std::string display () const;

        get_result<bool> get () const;

        conversion_result convert (type::Bool  const &) const;
        conversion_result convert (type::Int   const &) const;
        conversion_result convert (type::Float const &) const;
        conversion_result convert (type::Const const &) const; // TODO

        value_type_result value_type () const;
    };

    struct Int {
        integral value;

        std::string display () const;

        get_result<integral> get () const;

        conversion_result convert (type::Bool  const &) const;
        conversion_result convert (type::Int   const &) const;
        conversion_result convert (type::Float const &) const;
        conversion_result convert (type::Const const &) const; // TODO

        value_type_result value_type ()             const;
    };

    struct Float {
        floating value;

        std::string display () const;

        get_result<floating> get () const;

        conversion_result convert (type::Bool  const &) const;
        conversion_result convert (type::Int   const &) const;
        conversion_result convert (type::Float const &) const;
        conversion_result convert (type::Const const &) const; // TODO

        value_type_result value_type ()             const;
    };

    struct String {
        string value;

        std::string display () const;

        get_result<string> get () const;

        value_type_result value_type () const;
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

    struct In {
        component<value::complete> value;

        std::string display () const;

        conversion_result convert (type::Bool  const &) const;
        conversion_result convert (type::Int   const &) const;
        conversion_result convert (type::Float const &) const;
        conversion_result convert (type::In    const &) const;
        conversion_result convert (type::Const const &) const;

        value_type_result value_type () const;
    };

    struct Out {
        component<value::complete> value;

        std::string display () const;

        conversion_result convert (type::Out const &) const;

        value_type_result value_type () const;
    };

    /** Constant values will not be used in the first versions. */
    struct Const {
        component<value::complete> value;

        std::string display () const;

        conversion_result convert (type::Bool     const &) const;
        conversion_result convert (type::Int      const &) const;
        conversion_result convert (type::Float    const &) const;
        conversion_result convert (type::Const    const &) const;
        conversion_result convert (type::Function const &) const;

        value_type_result value_type () const;
    };

    struct Array {
        using vector = component_vector<component_vector<value::complete>>;

        get_result<std::vector<tuple_vector<value::any<true>>>> get () const;

        std::string display () const;

        vector                           value;
        component_vector<type::complete> type;

        integral size () const;

        conversion_result convert (type::Array const &) const;
        conversion_result convert (type::Const const &) const;

        value_type_result value_type () const;
    };

    struct Buffer {
        using sample_type = floating;
        using vector      = std::vector<floating>;

        integral size () const;

        std::string display () const;

        vector value;

        conversion_result convert (asg::type::Buffer const &) const;

        value_type_result value_type () const;
    };

    struct Function {
        component_vector <type::complete>            out_type;
        component_vector <complete_decl>             parameters;
        component        <ast::category::Expression> body;
        component        <context>                   capture;

        std::string display () const;

        get_result<Function> get () const;

        conversion_result convert (asg::type::Function const &) const;
        conversion_result convert (asg::type::Buffer   const &) const;

        value_type_result value_type () const;
    };

    /** Function templates will not be used in the first versions. */
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

}
