#include "ast/nodes/expressions/block.hpp"

#include "ast/categories/statement.hpp"
#include "ast/interface.hpp"
#include "util/string.hpp"

#include <string>

namespace cynth {

    std::string ast::node::Block::display () const {
        return statements.empty()
            ? "{}"
            : "{\n" + util::join(";\n", ast::display(statements)) + "\n}";
    }

}
