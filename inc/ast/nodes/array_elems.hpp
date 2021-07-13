#pragma once

#include "ast/interface_types.hpp"
#include "ast/categories_forward.hpp"
#include "component.hpp"
#include "context.hpp"

#include <string>

namespace cynth::ast::node {

    /** a to b */
    struct RangeTo {
        component<category::Expression> from;
        component<category::Expression> to;

        display_result         display         ()          const;
        array_elem_eval_result eval_array_elem (context &) const;
    };

    /** a to b by c */
    struct RangeToBy {
        component<category::Expression> from;
        component<category::Expression> to;
        component<category::Expression> by;

        display_result         display         ()          const;
        array_elem_eval_result eval_array_elem (context &) const;
    };

    /** ...a */
    struct Spread {
        component<category::Expression> container;

        display_result         display         ()          const;
        array_elem_eval_result eval_array_elem (context &) const;
    };

}
