#pragma once

#include "config.hpp"
#include "category_base.hpp"
#include "component.hpp"
#include "common_interface_types.hpp"
#include "sem/forward.hpp"
#include "sem/interface_types.hpp"
#include "util/general.hpp"

#include <type_traits>

// Note: Macros are always undefined at the end of the file.
#define TYPE_DECL \
    display_result     display     () const; \
    type_transl_result transl_type () const

namespace cynth::sem::type {

    struct Bool {
        common_type_result common (type::Bool  const &) const;
        common_type_result common (type::Int   const &) const;
        common_type_result common (type::Float const &) const;
        common_type_result common (type::In    const &) const;
        common_type_result common (type::Const const &) const;

        bool same (type::Bool const &) const;

        TYPE_DECL;
    };

    struct Int {
        // implicit common (Bool)
        common_type_result common (type::Int   const &) const;
        common_type_result common (type::Float const &) const;
        common_type_result common (type::In    const &) const;
        common_type_result common (type::Const const &) const;

        bool same (type::Int const &) const;

        TYPE_DECL;
    };

    struct Float {
        // implicit common (Bool)
        // implicit common (Int)
        common_type_result common (type::Float const &) const;
        common_type_result common (type::In    const &) const;
        common_type_result common (type::Const const &) const;

        bool same (type::Float const &) const;

        TYPE_DECL;
    };

    /** Strings will not be used in the first versions. */
    struct String {
        common_type_result common (type::String const &) const;

        bool same (type::String const &) const;

        TYPE_DECL;
    };

    namespace detail {

        using simple = variant <
            type::Bool,
            type::Int,
            type::Float,
            type::String
        >;

    }

    // TODO: This isn't even used anywhere.
    struct simple: category_base<simple, detail::simple> {
        using base = category_base<simple, detail::simple>;
        using base::base;
    };

    template <bool Complete>
    struct in_type {
        component<type::any<Complete>> type;

        decay_result decay () const requires Complete;

        // implicit common (Bool)
        // implicit common (Int)
        // implicit common (Float)

        bool same (type::In const &) const requires Complete;

        complete_result complete (context &) const requires (!Complete);

        TYPE_DECL;
    };

    template struct in_type<true>;
    template struct in_type<false>;

    template <bool Complete>
    struct out_type {
        component<type::any<Complete>> type;

        decay_result decay () const requires Complete;

        bool same (type::Out const &) const requires Complete;

        complete_result complete (context &) const requires (!Complete);

        TYPE_DECL;
    };

    template struct out_type<true>;
    template struct out_type<false>;

    template <bool Complete>
    struct const_type {
        component<type::any<Complete>> type;

        decay_result decay () const requires Complete;

        // implicit common (Bool)
        // implicit common (Int)
        // implicit common (Float)
        common_type_result common (type::Const const &) const requires Complete;

        bool same (type::Const const &) const requires Complete;

        complete_result complete (context &) const requires (!Complete);

        TYPE_DECL;
    };

    template struct const_type<true>;
    template struct const_type<false>;

    namespace detail {

        template <bool Complete>
        using size_type = std::conditional_t <
            Complete,
            integral,
            component<value::incomplete>
        >;

    }

    template <bool Complete>
    struct array_type {
        component_vector<type::any<Complete>> type;
        detail::size_type<Complete>           size;

        common_type_result common (type::Array const &) const requires Complete;

        bool same (type::Array const &) const requires Complete;

        complete_result complete (context &) const requires (!Complete);

        TYPE_DECL;
    };

    template struct array_type<true>;
    template struct array_type<false>;

    result<type::Array> make_array (component_vector<type::complete> &&, integral);

    template <bool Complete>
    struct buffer_type {
        constexpr static char const * sample_type = "float";

        detail::size_type<Complete> size;

        common_type_result common (type::Buffer const &) const requires Complete;

        bool same (type::Buffer const &) const requires Complete;

        complete_result complete (context &) const requires (!Complete);

        TYPE_DECL;
    };

    template struct buffer_type<true>;
    template struct buffer_type<false>;

    result<type::Buffer> make_buffer (integral);

    template <bool Complete>
    struct function_type {
        // Might return or accept a tuple.
        component_vector<type::any<Complete>> out;
        component_vector<type::any<Complete>> in;

        common_type_result common (type::Function const &) const requires Complete;

        bool same (type::Function const &) const requires Complete;

        complete_result complete (context &) const requires (!Complete);

        TYPE_DECL;
    };

    template struct function_type<true>;
    template struct function_type<false>;

    struct unknown {
        optional_component<type_decl> declaration;
    };

    namespace detail {

        using any_base = util::extend <
            type::simple::variant,
            type::const_type    <true>,
            type::in_type       <true>,
            type::out_type      <true>,
            type::array_type    <true>,
            type::buffer_type   <true>,
            type::function_type <true>
        >;

        template <bool Complete>
        using any = std::conditional_t <
            Complete,
            any_base,
            util::extend <
                any_base,
                type::const_type    <false>,
                type::in_type       <false>,
                type::out_type      <false>,
                type::array_type    <false>,
                type::buffer_type   <false>,
                type::function_type <false>,
                type::unknown
            >
        >;

    }

    // Note: Incomplete types are actually "possibly incomplete".
    // I.e. complete types are a subset of incomplete types.
    template <bool Complete>
    struct any: category_base<any<Complete>, detail::any<Complete>> {
        using base = category_base<any<Complete>, detail::any<Complete>>;
        using base::base;
    };

    template struct any<true>;
    template struct any<false>;

}

#undef TYPE_DECL