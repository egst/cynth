#pragma once

#include "ast/nodes.hpp"
#include "util.hpp"

namespace cynth::ast::category {

    struct Type {
        util::variant <
            ast::node::Auto
            //ast::node::TypeName,
            //ast::node::FunctionType,
            //ast::node::ArrayType,
            //ast::node::AutoArrayType,
            //ast::node::DeclArrayType,
            //ast::node::BufferType,
            //ast::node::TypeDecl,
            //ast::node::ConstType,
            //ast::node::TupleType
        > node;
    };

    struct Expression {
        util::variant <
            ast::node::Name,
            //ast::node::Boolean,
            ast::node::Int
            //ast::node::Decimal,
            //ast::node::String,
            //ast::node::Not,
            //ast::node::Or,
            //ast::node::And,
            //ast::node::Eq,
            //ast::node::Ne,
            //ast::node::Ge,
            //ast::node::Le,
            //ast::node::Gt,
            //ast::node::Lt,
            //ast::node::Add,
            //ast::node::Sub,
            //ast::node::Mul,
            //ast::node::Div,
            //ast::node::Mod,
            //ast::node::Pow,
            //ast::node::Plus,
            //ast::node::Minus,
            //ast::node::Application,
            //ast::node::Subscript,
            //ast::node::Conversion,
            //ast::node::Block,
            //ast::node::ExprIf,
            //ast::node::Function,
            //ast::node::Array,
            //ast::node::Tuple
        > node;
    };

    struct Declaration {
        util::variant <
            ast::node::SingleDecl
            //ast::node::TupleDecl
        > node;
    };

    // TODO
    /*struct ArrayElem {
        util::extend <
            decltype(ast::category::Expression::variant),
            //ast::node::RangeTo,
            //ast::node::RangeToBy,
            //ast::node::Spread
        > node;
    };*/

    struct Statement {
        util::extend <
            util::concat <
                decltype(ast::category::Expression::node),
                decltype(ast::category::Declaration::node)
            >,
            ast::node::If
            //ast::node::When,
            //ast::node::Definition,
            //ast::node::TypeDef,
            //ast::node::FunctionDef,
            //ast::node::Assignment,
            //ast::node::Return
        > node;
    };

}
