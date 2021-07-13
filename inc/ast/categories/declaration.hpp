#pragma once

#include "config.hpp"
#include "category_base.hpp"
#include "ast/nodes/declarations.hpp"

namespace cynth::ast::category {

    namespace detail {

        using declaration = variant <
            node::Declaration,
            node::TupleDecl
        >;

    }

    struct Declaration: category_base<Declaration, detail::declaration> {
        using base = category_base<Declaration, detail::declaration>;
        using base::base;
    };

}
