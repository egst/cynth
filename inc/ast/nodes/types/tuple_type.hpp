#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct TupleType {
        // TODO: Non-unary vector?
        component_vector<category::Type> types;

        std::string display () const;
    };

}
