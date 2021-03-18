#include "ast/nodes/types/const_type.hpp"

#include "ast/categories/type.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::ConstType::display () const {
        return ast::display(type) + " const";
    }

}
