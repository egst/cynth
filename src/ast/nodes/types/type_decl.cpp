#include "ast/nodes/types/type_decl.hpp"

#include "ast/nodes/types/type_name.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::TypeDecl::display () const {
        return "type " + ast::display(name);
    }

}
