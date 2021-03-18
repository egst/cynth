#pragma once

#include "ast/category_base.hpp"
#include "ast/nodes/declarations.hpp"
#include "util/config.hpp"

namespace cynth::ast::category {

    namespace detail {

        using declaration = util::variant <
            node::Declaration,
            node::TupleDecl
        >;

    }

    struct Declaration: detail::category_base<Declaration, detail::declaration> {
        using base = detail::category_base<Declaration, detail::declaration>;
        using base::base;
        using base::operator=;
    };

}
