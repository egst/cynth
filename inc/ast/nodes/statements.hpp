#pragma once

#include "ast/interface_types.hpp"
#include "ast/categories_forward.hpp"
#include "ast/nodes/expressions.hpp"
#include "ast/nodes/types.hpp"
#include "component.hpp"
#include "context.hpp"

#include <string>

namespace cynth::ast::node {

    /** a = b */
    struct Assignment {
        // Target is syntactically any expression (otherwise it would be too complicated to parse),
        // but semantically it may be only be a name or a tuple of names.
        component<category::Expression> target;
        component<category::Expression> value;

        display_result   display ()          const;
        execution_result execute (context &) const;
    };

    /** T a = b */
    struct Definition {
        component<category::Declaration> target;
        component<category::Expression>  value;

        display_result   display ()          const;
        execution_result execute (context &) const;
    };

    /** Out f (In a) b */
    struct FunctionDef {
        component<category::Type>        output;
        component<category::Declaration> input;
        component<node::Name>            name;
        component<category::Expression>  body;

        display_result   display ()          const;
        execution_result execute (context &) const;
    };

    /** if (cond) a else b */
    struct If {
        component<category::Expression> condition;
        component<category::Statement>  positive_branch;
        component<category::Statement>  negative_branch;

        display_result   display ()          const;
        execution_result execute (context &) const;
    };

    /** return a
        return ()
        return */
    struct Return {
        component<category::Expression> value;

        display_result   display ()          const;
        execution_result execute (context &) const;
    };

    /** type T = U */
    struct TypeDef {
        component<node::TypeName> target;
        component<category::Type> type;

        display_result   display ()          const;
        execution_result execute (context &) const;
    };

    /** when (cond) a */
    struct When {
        component <category::Expression> condition;
        component <category::Statement>  branch;

        display_result   display ()          const;
        execution_result execute (context &) const;
    };

}
