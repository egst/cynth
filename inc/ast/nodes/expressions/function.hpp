#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Function {
        component<category::Type>        output;
        component<category::Declaration> input;
        component<category::Expression>  body;

        std::string display () const;
    };

}
