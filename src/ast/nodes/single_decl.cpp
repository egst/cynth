#include "ast/nodes/single_decl.hpp"
#include "ast/categories.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::SingleDecl::display () const {
        return ast::display(type) + " " + ast::display(name);
    }

}
