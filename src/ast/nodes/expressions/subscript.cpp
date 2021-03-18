#include "ast/nodes/expressions/subscript.hpp"

#include "ast/categories/array_elem.hpp"
#include "ast/interface.hpp"
#include "util/string.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Subscript::display () const {
        return ast::display(container) + " [" + util::join(", ", ast::display(location)) + "]";
    }

}
