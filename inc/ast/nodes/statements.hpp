#pragma once

#include "component.hpp"
#include "ast/interface_types.hpp"
#include "ast/categories_forward.hpp"
#include "ast/nodes/expressions.hpp"
#include "ast/nodes/types.hpp"
#include "sem/context.hpp"
#include "sem/translation_context.hpp"

#include <string>

// Note: Macros are always undefined at the end of the file.
#define STMT_DECL \
    display_result     display   ()                           const; \
    execution_result   execute   (sem::context &)             const; \
    translation_result translate (sem::translation_context &) const

namespace cynth::ast::node {

    /** a = b */
    struct Assignment {
        // Target is syntactically any expression (otherwise it would be too complicated to parse),
        // but semantically it may be only be a name or a tuple of names.
        component<category::Expression> target;
        component<category::Expression> value;

        STMT_DECL;
    };

    /** T a = b */
    struct Definition {
        component<category::Declaration> target;
        component<category::Expression>  value;

        STMT_DECL;
    };

    /** for (T e in a) x */
    struct For {
        component<category::RangeDecl> declarations;
        component<category::Statement> body;

        STMT_DECL;
    };

    /** Out f (In a) b */
    struct FunctionDef {
        component<category::Type>        output;
        component<category::Declaration> input;
        component<node::Name>            name;
        component<category::Expression>  body;

        STMT_DECL;
    };

    /** if (cond) a else b */
    struct If {
        component<category::Expression> condition;
        component<category::Statement>  positive_branch;
        component<category::Statement>  negative_branch;

        STMT_DECL;
    };

    /** return a
        return ()
        return */
    struct Return {
        component<category::Expression> value;

        STMT_DECL;
    };

    /** type T = U */
    struct TypeDef {
        component<node::TypeName> target;
        component<category::Type> type;

        STMT_DECL;
    };

    /** when (cond) a */
    struct When {
        component <category::Expression> condition;
        component <category::Statement>  branch;

        STMT_DECL;
    };

    /** while (cond) a */
    struct While {
        component<category::Expression> condition;
        component<category::Statement>  body;

        STMT_DECL;
    };

}

#undef STMT_DECL
