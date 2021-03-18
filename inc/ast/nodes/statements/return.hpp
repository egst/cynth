#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Return {
        component<category::Expression> value;

        std::string display () const;
    };

}
