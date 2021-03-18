#include "ast/nodes/statements/definition.hpp"

#include "ast/categories/declaration.hpp"
#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Definition::display () const {
        return ast::display(target) + " = " + ast::display(value);
    }

}
