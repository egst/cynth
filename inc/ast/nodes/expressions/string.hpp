#pragma once

#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct String {
        component<std::string> value;

        std::string display () const;
    };

}
