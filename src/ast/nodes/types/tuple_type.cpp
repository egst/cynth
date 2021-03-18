#include "ast/nodes/types/tuple_type.hpp"

#include "ast/categories/type.hpp"
#include "ast/interface.hpp"
#include "util/string.hpp"

#include <string>

namespace cynth {

    std::string ast::node::TupleType::display () const {
        return "(" + util::join(", ", ast::display(types)) + ")";
    }

}
