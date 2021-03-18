#include "ast/nodes/declarations/declaration.hpp"

#include "ast/nodes/expressions/name.hpp"
#include "ast/categories/type.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Declaration::display () const {
        return ast::display(type) + " " + ast::display(name);
    }

}
