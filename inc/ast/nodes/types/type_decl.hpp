#pragma once

#include "ast/nodes/types/type_name.hpp"
#include "ast/node_component.hpp"

#include <string>

namespace cynth::ast::node {

    struct TypeDecl {
        component<ast::node::TypeName> name;

        std::string display () const;
    };

}
