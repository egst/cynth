#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct Subscript {
        component        <category::Expression> container;
        component_vector <category::ArrayElem>  location;

        std::string display () const;
    };

}
