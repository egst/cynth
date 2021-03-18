#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct ExprIf {
        component<category::Expression> condition;
        component<category::Expression> positive_branch;
        component<category::Expression> negative_branch;

        std::string display () const;
    };

}
