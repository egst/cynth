#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct RangeToBy {
        component<category::Expression> from;
        component<category::Expression> to;
        component<category::Expression> by;

        std::string display () const;
    };

}
