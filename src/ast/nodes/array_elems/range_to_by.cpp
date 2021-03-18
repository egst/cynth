#include "ast/nodes/array_elems/range_to_by.hpp"

#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::RangeToBy::display () const {
        return ast::display(from) + " to " + ast::display(to) + " by " + ast::display(by);
    }

}
