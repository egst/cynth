#include "ast/nodes/statements/function_def.hpp"

#include "ast/nodes/expressions/name.hpp"
#include "ast/categories/type.hpp"
#include "ast/categories/declaration.hpp"
#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"
#include "util/string.hpp"

#include <string>

namespace cynth {

    std::string ast::node::FunctionDef::display () const {
        return ast::display(output) + " " + ast::display(name) + " " + util::parenthesized(ast::display(input)) + " " + ast::display(body);
    }

}
