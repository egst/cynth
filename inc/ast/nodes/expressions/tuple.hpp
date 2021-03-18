#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Tuple {
        // TODO: Non-unary vector?
        component_vector<category::Expression> values;

        std::string display () const;
    };

}
