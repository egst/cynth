#include "ast/nodes/statements/type_def.hpp"

#include "ast/nodes/types/type_name.hpp"
#include "ast/categories/type.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::TypeDef::display () const {
        return "type " + ast::display(target) + " = " + ast::display(type);
    }

}
