#include "ast/nodes/expressions/expr_if.hpp"

#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"
#include "util/string.hpp"

#include <string>

namespace cynth {

    std::string ast::node::ExprIf::display () const {
        return
            "if "    + util::parenthesized(ast::display(condition)) +
            " "      + ast::display(positive_branch) +
            " else " + ast::display(negative_branch);
    }

}
