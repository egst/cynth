#pragma once

#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Int {
        component<int> value;

        std::string display () const;
    };

}
