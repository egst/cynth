#include "ast/nodes/expressions/plus.hpp"

#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Plus::display () const {
        return "+" + ast::display(argument);
    }

}
