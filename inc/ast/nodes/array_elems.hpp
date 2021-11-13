#pragma once

#include "component.hpp"
#include "ast/interface_types.hpp"
#include "ast/categories_forward.hpp"
#include "sem/context.hpp"

#include <string>

// Note: Macros are always undefined at the end of the file.
#define ARRAY_DECL \
    display_result         display         ()               const; \
    array_elem_eval_result eval_array_elem (sem::context &) const

namespace cynth::ast::node {

    /** a to b */
    struct RangeTo {
        component<category::Expression> from;
        component<category::Expression> to;

        ARRAY_DECL;
    };

    /** a to b by c */
    struct RangeToBy {
        component<category::Expression> from;
        component<category::Expression> to;
        component<category::Expression> by;

        ARRAY_DECL;
    };

    /** ...a */
    struct Spread {
        component<category::Expression> container;

        ARRAY_DECL;
    };

}

#undef ARRAY_DECL
