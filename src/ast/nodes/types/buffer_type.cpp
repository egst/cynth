#include "ast/nodes/types/buffer_type.hpp"

#include "ast/categories/expression.hpp"
#include "ast/interface.hpp"

#include <string>

namespace cynth {

    std::string ast::node::BufferType::display () const {
        return "buffer [" + ast::display(size) + "]";
    }

}
