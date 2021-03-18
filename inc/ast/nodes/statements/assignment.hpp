#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Assignment {
        // Target is syntactically any expression (otherwise it would be too complicated to parse),
        // but semantically it may be only be a name or a tuple of names.
        component<category::Expression> target;
        component<category::Expression> value;

        std::string display () const;
    };

}
