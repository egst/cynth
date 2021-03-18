#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Mul {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        std::string display () const;
    };

}
