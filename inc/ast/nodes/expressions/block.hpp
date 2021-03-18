#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Block {
        component_vector<category::Statement> statements;

        std::string display () const;
    };

}
