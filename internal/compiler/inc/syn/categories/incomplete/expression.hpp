#pragma once

#include <variant>

#include "esl/category.hpp"

// Circular dependencies:
#include "syn/nodes/incomplete/expressions.hpp"

namespace cynth::syn::category {

    namespace detail::expression {

        using Variant = std::variant<
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

    struct Expression: esl::category<Expression, detail::expression::Variant> {
        using base = esl::category<Expression, detail::expression::Variant>;
        using base::base;
    };

}
