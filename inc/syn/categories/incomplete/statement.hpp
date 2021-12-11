#pragma once

#include "esl/category.hpp"
#include "esl/type_manip.hpp"

// Circular dependencies:
#include "syn/categories/incomplete/declaration.hpp"
#include "syn/categories/incomplete/expression.hpp"
#include "syn/nodes/incomplete/statements.hpp"

namespace cynth::syn::category {

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
