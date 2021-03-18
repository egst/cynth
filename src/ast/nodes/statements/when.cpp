#include "ast/nodes/statements/when.hpp"

#include "ast/categories/expression.hpp"
#include "ast/categories/statement.hpp"
#include "ast/interface.hpp"
#include "util/string.hpp"

#include <string>

namespace cynth {

    std::string ast::node::When::display () const {
        return
            "when " + util::parenthesized(ast::display(condition)) +
            " "     + ast::display(branch);
    }

}
