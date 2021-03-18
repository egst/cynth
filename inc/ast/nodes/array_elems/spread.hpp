#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Spread {
        component<category::Expression> container;

        std::string display () const;
    };

}
