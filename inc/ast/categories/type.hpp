#pragma once

#include "config.hpp"
#include "category_base.hpp"
#include "asg/declarations.hpp"
#include "ast/nodes/types.hpp"

namespace cynth::ast::category {

    namespace detail {

        using type = variant <
            ast::node::ArrayType,
            ast::node::Auto,
            ast::node::BufferType,
            ast::node::ConstType,
            ast::node::FunctionType,
            ast::node::InType,
            ast::node::OutType,
            ast::node::TupleType,
            ast::node::TypeDecl,
            ast::node::TypeName
        >;

    }

    struct Type: category_base<Type, detail::type> {
        using base = category_base<Type, detail::type>;
        using base::base;
    };

}
