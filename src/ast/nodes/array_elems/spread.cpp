#include "ast/nodes/array_elems/spread.hpp"

#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Spread::display () const {
        return "..." + ast::display(container);
    }

}
