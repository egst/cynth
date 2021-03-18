#include "ast/nodes/expressions/function.hpp"

#include "ast/categories/type.hpp"
#include "ast/categories/declaration.hpp"
#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"
#include "util/string.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Function::display () const {
        return ast::display(output) + " fn " + util::parenthesized(ast::display(input)) + " " + ast::display(body);
    }

}
