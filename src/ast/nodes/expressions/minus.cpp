#include "ast/nodes/expressions/minus.hpp"

#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Minus::display () const {
        return "-" + ast::display(argument);
    }

}
