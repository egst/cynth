#pragma once

#include "ast/category_base.hpp"
#include "ast/nodes/expressions.hpp"
#include "util/config.hpp"

namespace cynth::ast::category {

    namespace detail {

        using expression = util::variant <
            node::Add,
            node::And,
            node::Application,
            node::Array,
            node::Block,
            node::Bool,
            node::Conversion,
            node::Div,
            node::Eq,
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

    struct Expression: detail::category_base<Expression, detail::expression> {
        using base = detail::category_base<Expression, detail::expression>;
        using base::base;
        using base::operator=;
    };

}
