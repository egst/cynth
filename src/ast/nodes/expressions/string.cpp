#include "ast/nodes/expressions/string.hpp"

#include <string>

namespace cynth {

    std::string ast::node::String::display () const {
        return "\"" + *value + "\"";
    }

}
