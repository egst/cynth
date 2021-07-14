#pragma once

#include "config.hpp"
#include "category_base.hpp"
#include "ast/nodes/expressions.hpp"

namespace cynth::ast::category {

    namespace detail {

        using expression = variant <
            node::Add,
            node::And,
            node::Application,
            node::Array,
            node::Block,
            node::Bool,
            node::Conversion,
            node::Div,
            node::Eq,
            node::ExprFor,
            node::ExprIf,
            node::Float,
            node::Function,
            node::Ge,
            node::Gt,
            node::Int,
            node::Le,
            node::Lt,
            node::Minus,
            node::Mod,
            node::Mul,
            node::Name,
            node::Ne,
            node::Not,
            node::Or,
            node::Plus,
            node::Pow,
            node::String,
            node::Sub,
            node::Subscript,
            node::Tuple
        >;

    }

    // TODO: Once everything is settled with the copyable category here, do the same elsewhere.
    struct Expression: category_base<Expression, detail::expression, true> {
        using base = category_base<Expression, detail::expression, true>;
        using base::base;
    };

}
