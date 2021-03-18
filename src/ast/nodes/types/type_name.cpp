#include "ast/nodes/types/type_name.hpp"

#include <string>

namespace cynth {

    std::string ast::node::TypeName::display () const {
        return name;
    }

}
