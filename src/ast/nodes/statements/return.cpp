#include "ast/nodes/statements/return.hpp"

#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Return::display () const {
        return "return " + ast::display(value);
    }

}
