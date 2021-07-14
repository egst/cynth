#pragma once

namespace cynth::asg {

    template <bool> struct declaration;

    using complete_decl   = declaration<true>;
    using incomplete_decl = declaration<false>;

    struct type_decl;

    template <bool> struct range_decl;

    using complete_range_decl   = range_decl<true>;
    using incomplete_range_decl = range_decl<false>;

    namespace value {

        template <bool> struct any;

        using complete   = any<true>;
        using incomplete = any<false>;

    }

    namespace type {

        template <bool> struct any;

        using complete   = any<true>;
        using incomplete = any<false>;

        struct Bool;
        struct Int;
        struct Float;
        struct String;

        template <bool> struct in_type;
        template <bool> struct out_type;
        template <bool> struct const_type;
        template <bool> struct array_type;
        template <bool> struct buffer_type;
        template <bool> struct function_type;

        using In               = in_type       <true>;
        using Out              = out_type      <true>;
        using Const            = const_type    <true>;
        using Array            = array_type    <true>;
        using Buffer           = buffer_type   <true>;
        using Function         = function_type <true>;
        using FunctionTemplate = function_type <false>;

    }

}
