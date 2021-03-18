#include "ast/nodes/statements/if.hpp"

#include "ast/categories/expression.hpp"
#include "ast/categories/statement.hpp"
#include "ast/interface.hpp"
#include "util/string.hpp"

#include <string>

namespace cynth {

    std::string ast::node::If::display () const {
        return
            "if "    + util::parenthesized(ast::display(condition)) +
            " "      + ast::display(positive_branch) +
            " else " + ast::display(negative_branch);
    }

}
