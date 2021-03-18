#include "ast/nodes/expressions/le.hpp"

#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Le::display () const {
        return "(" + ast::display(left_argument) + " <= " + ast::display(right_argument) + ")";
    }

}
