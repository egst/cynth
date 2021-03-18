#include "ast/nodes/expressions/name.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Name::display () const {
        return name;
    }

}
