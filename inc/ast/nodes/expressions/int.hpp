#pragma once

#include "ast/node_component.hpp"
#include "util/config.hpp"

#include <string>

namespace cynth::ast::node {

    struct Int {
        component<util::integral> value;

        std::string display () const;
    };

}
