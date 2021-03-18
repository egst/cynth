#pragma once

#include "ast/nodes/types/type_name.hpp"
#include "ast/categories_forward.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct TypeDef {
        component<node::TypeName> target;
        component<category::Type> type;

        std::string display () const;
    };

}
