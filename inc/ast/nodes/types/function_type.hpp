#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct FunctionType {
        component<category::Type> output;
        component<category::Type> input;

        std::string display () const;
    };

}
