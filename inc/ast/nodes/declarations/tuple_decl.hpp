#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct TupleDecl {
        component_vector<category::Declaration> declarations;

        std::string display () const;
    };

}
