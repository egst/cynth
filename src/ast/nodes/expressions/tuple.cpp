#include "ast/nodes/expressions/tuple.hpp"

#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"
#include "util/string.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Tuple::display () const {
        return "(" + util::join(", ", ast::display(values)) + ")";
    }

}
