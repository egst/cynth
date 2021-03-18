#include "ast/nodes/statements/assignment.hpp"

#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Assignment::display () const {
        return ast::display(target) + " = " + ast::display(value);
    }

}
