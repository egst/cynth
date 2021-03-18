#include "ast/nodes/expressions/array.hpp"

#include "ast/categories/array_elem.hpp"
#include "ast/interface.hpp"
#include "util/string.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Array::display () const {
        return "[" + util::join(", ", ast::display(elements)) + "]";
    }

}
