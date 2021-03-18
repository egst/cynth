#include "ast/nodes/types/array_type.hpp"

#include "ast/categories/type.hpp"
#include "ast/categories/pattern.hpp"
#include "ast/interface.hpp"
#include "util/general.hpp"

#include <string>

namespace cynth {

    std::string ast::node::ArrayType::display () const {
        //return ast::display(type) + " [" + util::coalesce(ast::display(size) ?: "") + "]";
        //return ast::display(type) + " [" + util::coalesce(ast::display(size), "") + "]";
        return ast::display(type) + " [" + ast::display(size).value_or("$") + "]";
    }

}
