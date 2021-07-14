#pragma once

#include "category_base.hpp"
#include "ast/nodes/statements.hpp"
#include "ast/categories/declaration.hpp"
#include "ast/categories/expression.hpp"
#include "util/general.hpp"

#include <concepts>

namespace cynth::ast::category {

    namespace detail {

        using statement = util::extend <
            util::concat <
                category::Declaration::variant,
                category::Expression::variant
            >,
            ast::node::Assignment,
            ast::node::Definition,
            ast::node::For,
            ast::node::FunctionDef,
            ast::node::If,
            ast::node::Return,
            ast::node::TypeDef,
            ast::node::When,
            ast::node::While
        >;

    }

    struct Statement: category_base<Statement, detail::statement> {
        using base = category_base<Statement, detail::statement>;
        using base::base;
    };

}
