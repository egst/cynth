#include "ast/nodes/declarations/tuple_decl.hpp"

#include "ast/categories/declaration.hpp"
#include "ast/interface.hpp"
#include "util/string.hpp"

#include <string>

namespace cynth {

    std::string ast::node::TupleDecl::display () const {
        return "(" + util::join(", ", ast::display(declarations)) + ")";
    }

}
