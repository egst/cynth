#include "ast/nodes/expressions/application.hpp"

#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"
#include "util/string.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Application::display () const {
        return ast::display(function) + util::parenthesized(ast::display(arguments));
    }

}
