#pragma once

#include "ast/interface_types.hpp"
//#include "ast/nodes/expressions.hpp"
#include "ast/categories_forward.hpp"
#include "component.hpp"
#include "context.hpp"

#include <string>

namespace cynth::ast::node {

    /** T e in a */
    struct RangeDecl {
        component<category::Declaration> declaration;
        component<category::Expression>  range;

        display_result   display   ()          const;
        /*decl_eval_result eval_decl (context &) const;
        execution_result execute   (context &) const;*/
    };

    /** (T e in a, ...) */
    struct TupleRangeDecl {
        component_vector<category::RangeDecl> declarations;

        display_result   display   ()          const;
        /*decl_eval_result eval_decl (context &) const;
        execution_result execute   (context &) const;*/
    };

}
