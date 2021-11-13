#pragma once

#include "component.hpp"
#include "ast/interface_types.hpp"
#include "ast/nodes/expressions.hpp"
#include "ast/categories_forward.hpp"
#include "sem/context.hpp"

#include <string>

// Note: Macros are always undefined at the end of the file.
#define DECL_DECL \
    display_result     display   ()                           const; \
    decl_eval_result   eval_decl (sem::context &)             const; \
    execution_result   execute   (sem::context &)             const; \
    translation_result translate (sem::translation_context &) const

namespace cynth::ast::node {

    /** T a */
    struct Declaration {
        component<node::Name>     name;
        component<category::Type> type;

        DECL_DECL;
    };

    /** (T a, ...) */
    struct TupleDecl {
        component_vector<category::Declaration> declarations;

        DECL_DECL;
    };

}

#undef DECL_DECL
