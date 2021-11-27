#pragma once

namespace Cynth::Sem {

    template <bool> struct Declaration;

    using CompleteDecl   = Declaration<true>;
    using IncompleteDecl = Declaration<false>;

    struct TypeDecl;

    template <bool> struct RangeDecl;

    using CompleteRangedecl   = RangeDecl<true>;
    using IncompleteRangeDecl = RangeDecl<false>;

    struct DirectTarget;
    struct SubscriptTarget;
    struct AnyTarget;

    namespace Value {

        template <bool> struct any;

        using complete   = any<true>;
        using incomplete = any<false>;

        //struct referential;

    }

    using CompleteValue = value::complete;

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

    using complete_type = type::complete;

}
