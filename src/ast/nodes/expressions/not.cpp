#include "ast/nodes/expressions/not.hpp"

#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Not::display () const {
        return "!" + ast::display(argument);
    }

}
