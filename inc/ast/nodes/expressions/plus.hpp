#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Plus {
        component<category::Expression> argument;

        std::string display () const;
    };

}
