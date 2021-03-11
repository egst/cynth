#include "ast/nodes/if.hpp"
#include "ast/categories.hpp"
#include "ast/interface.hpp"
#include "util.hpp"

#include <string>

namespace cynth {

    std::string ast::node::If::display () const {
        std::string result = "if " + util::parenthesized(ast::display(condition)) + " " + ast::display(positive_branch);
        if (negative_branch.has_value())
            result += " else " + ast::display(negative_branch.get());
        return result;
    }

}
