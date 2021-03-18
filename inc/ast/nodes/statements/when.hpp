#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct When {
        component <category::Expression> condition;
        component <category::Statement>  branch;

        std::string display () const;
    };

}
