#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct BufferType {
        component<category::Expression> size;

        std::string display () const;
    };

}
