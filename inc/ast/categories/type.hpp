#pragma once

#include "ast/category_base.hpp"
#include "ast/nodes/types.hpp"
#include "util/config.hpp"

namespace cynth::ast::category {

    namespace detail {

        using type = util::variant <
            ast::node::Auto,
            ast::node::TypeName,
            ast::node::FunctionType,
            ast::node::ArrayType,
            ast::node::BufferType,
            ast::node::TypeDecl,
            ast::node::ConstType,
            ast::node::TupleType
        >;

    }

    struct Type: detail::category_base<Type, detail::type> {
        using base = detail::category_base<Type, detail::type>;
        using base::base;
        using base::operator=;
    };

}
