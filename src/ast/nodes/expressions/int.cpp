#include "ast/nodes/expressions/int.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Int::display () const {
        return std::to_string(value);
    }

}
