#pragma once

#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct ConstType {
        component<category::Type> type;

        std::string display () const;
    };

}
