#include "ast/nodes/auto.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Auto::display () const {
        return "$";
    }

}
