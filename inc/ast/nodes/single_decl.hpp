#pragma once

#include "ast/nodes/name.hpp"
#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct SingleDecl {
        component<ast::node::Name>     name;
        component<ast::category::Type> type;

        std::string display () const;
    };

}
