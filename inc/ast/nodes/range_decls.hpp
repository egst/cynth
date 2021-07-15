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

        display_result         display         ()          const;
        range_decl_eval_result eval_range_decl (context &) const;
    };

    /** (T e in a, ...) */
    struct TupleRangeDecl {
        component_vector<category::RangeDecl> declarations;

        display_result         display         ()          const;
        range_decl_eval_result eval_range_decl (context &) const;
    };

}
