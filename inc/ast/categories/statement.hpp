#pragma once

#include "esl/type_manip.hpp"
#include "esl/category.hpp"

#include "ast/categories/declaration.hpp"
#include "ast/categories/expression.hpp"
#include "ast/nodes/statements.hpp"

namespace cynth::ast::category {

    namespace detail::statement {

        using Variant = esl::extend<
            esl::concat <
                category::Declaration::variant,
                category::Expression::variant
            >,
            node::Assignment,
            node::Definition,
            node::For,
            node::FunDef,
            node::If,
            node::Return,
            node::TypeDef,
            node::When,
            node::While
        >;

    }

    struct Statement: esl::category<Statement, detail::statement::Variant> {
        using base = esl::category<Statement, detail::statement::Variant>;
        using base::base;
    };

}
