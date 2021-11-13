#pragma once

#include "config.hpp"
#include "category_base.hpp"
#include "sem/declarations.hpp"
#include "ast/nodes/types.hpp"

namespace cynth::ast::category {

    namespace detail {

        using type = variant <
            node::ArrayType,
            node::Auto,
            node::BufferType,
            node::ConstType,
            node::FunctionType,
            node::InType,
            node::OutType,
            node::TupleType,
            node::TypeDecl,
            node::TypeName
        >;

    }

    struct Type: category_base<Type, detail::type> {
        using base = category_base<Type, detail::type>;
        using base::base;
    };

}
