#pragma once

#include "ast/nodes/expressions/name.hpp"
#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct FunctionDef {
        component<category::Type>        output;
        component<category::Declaration> input;
        component<node::Name>            name;
        component<category::Expression>  body;

        std::string display () const;
    };

}
