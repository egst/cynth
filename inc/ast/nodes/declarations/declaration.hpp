#pragma once

#include "ast/nodes/expressions/name.hpp"
#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Declaration {
        component<node::Name>     name;
        component<category::Type> type;

        std::string display () const;
    };

}
