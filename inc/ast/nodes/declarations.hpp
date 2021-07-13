#pragma once

#include "ast/interface_types.hpp"
#include "ast/nodes/expressions.hpp"
#include "ast/categories_forward.hpp"
#include "component.hpp"
#include "context.hpp"

#include <string>

namespace cynth::ast::node {

    /** T a */
    struct Declaration {
        component<node::Name>     name;
        component<category::Type> type;

        display_result   display   ()          const;
        decl_eval_result eval_decl (context &) const;
        execution_result execute   (context &) const;
    };

    /** (T a, ...) */
    struct TupleDecl {
        component_vector<category::Declaration> declarations;

        display_result   display   ()          const;
        decl_eval_result eval_decl (context &) const;
        execution_result execute   (context &) const;
    };

}
