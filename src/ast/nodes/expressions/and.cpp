#include "ast/nodes/expressions/and.hpp"

#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::And::display () const {
        return "(" + ast::display(left_argument) + " && " + ast::display(right_argument) + ")";
    }

}
