#include "ast/nodes/expressions/bool.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Bool::display () const {
        return value ? "true" : "false";
    }

}
