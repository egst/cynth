#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Definition {
        component<category::Declaration> target;
        component<category::Expression>  value;

        std::string display () const;
    };

}
