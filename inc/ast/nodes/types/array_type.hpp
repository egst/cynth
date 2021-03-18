#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct ArrayType {
        component          <category::Type>    type;
        optional_component <category::Pattern> size;

        std::string display () const;
    };

}
