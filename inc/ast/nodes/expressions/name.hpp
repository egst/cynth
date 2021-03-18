#pragma once

#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Name {
        component<std::string> name;

        std::string display () const;
    };

}
