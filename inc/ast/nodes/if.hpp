#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct If {
        component          <ast::category::Expression> condition;
        component          <ast::category::Statement>  positive_branch;
        optional_component <ast::category::Statement>  negative_branch;

        std::string display () const;
    };

}
