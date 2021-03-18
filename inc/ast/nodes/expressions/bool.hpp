#pragma once

#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Bool {
        component<bool> value;

        std::string display () const;
    };

}
