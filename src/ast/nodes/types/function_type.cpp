#include "ast/nodes/types/function_type.hpp"

#include "ast/categories.hpp"
#include "ast/interface.hpp"
#include "util.hpp"

#include <string>

namespace cynth {

    std::string ast::node::FunctionType::display () const {
        return ast::display(output) + " " + util::parenthesized(ast::display(input));
    }

}
