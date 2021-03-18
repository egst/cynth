#include "ast/nodes/expressions/float.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Float::display () const {
        return std::to_string(value);
    }

}
