#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct If {
        component<category::Expression> condition;
        component<category::Statement>  positive_branch;
        component<category::Statement>  negative_branch;

        std::string display () const;
    };

}
