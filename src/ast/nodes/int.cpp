#include "ast/nodes/int.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Int::display () const {
        return std::to_string(value.get());
    }

}
