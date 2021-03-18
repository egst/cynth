#pragma once

#include "ast/node_component.hpp"
#include "util/config.hpp"

#include <string>

namespace cynth::ast::node {

    struct Float {
        component<util::floating> value;

        std::string display () const;
    };

}
