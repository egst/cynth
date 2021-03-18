#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Application {
        component<category::Expression> function;
        component<category::Expression> arguments;

        std::string display () const;
    };

}
