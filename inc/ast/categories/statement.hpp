#pragma once

#include "ast/category_base.hpp"
#include "ast/nodes/statements.hpp"
#include "ast/categories/declaration.hpp"
#include "ast/categories/expression.hpp"
#include "util/general.hpp"

#include <concepts>

namespace cynth::ast::category {

    namespace detail {

        using statement = util::extend <
            util::concat <
                decltype(category::Declaration::node),
                decltype(category::Expression::node)
            >,
            ast::node::Assignment,
            ast::node::Definition,
            ast::node::FunctionDef,
            ast::node::If,
            ast::node::Return,
            ast::node::When,
            ast::node::TypeDef
        >;

    }

    struct Statement: detail::category_base<Statement, detail::statement> {
        using base = detail::category_base<Statement, detail::statement>;
        using base::base;
        using base::operator=;
    };

}
