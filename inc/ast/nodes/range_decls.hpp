#pragma once

#include "component.hpp"
#include "ast/interface_types.hpp"
#include "ast/categories_forward.hpp"
#include "sem/context.hpp"

#include <string>

// Note: Macros are always undefined at the end of the file.
#define RANGE_DECL \
    display_result         display         ()               const; \
    range_decl_eval_result eval_range_decl (sem::context &) const

namespace cynth::ast::node {

    /** T e in a */
    struct RangeDecl {
        component<category::Declaration> declaration;
        component<category::Expression>  range;

        RANGE_DECL;
    };

    /** (T e in a, ...) */
    struct TupleRangeDecl {
        component_vector<category::RangeDecl> declarations;

        RANGE_DECL;
    };

}

#undef RANGE_DECL
