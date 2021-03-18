#include "ast/nodes/expressions/conversion.hpp"

#include "ast/categories/type.hpp"
#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"
#include "util/string.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Conversion::display () const {
        return ast::display(type) + util::parenthesized(ast::display(argument));
    }

}
