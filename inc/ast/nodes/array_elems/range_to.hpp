#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct RangeTo {
        component<category::Expression> from;
        component<category::Expression> to;

        std::string display () const;
    };

}
