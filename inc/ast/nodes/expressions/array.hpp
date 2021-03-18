#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Array {
        component_vector<category::ArrayElem> elements;

        std::string display () const;
    };

}
