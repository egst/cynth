#pragma once

#include "config.hpp"
#include "category_base.hpp"
#include "ast/nodes/range_decls.hpp"

namespace cynth::ast::category {

    namespace detail {

        using range_decl = variant <
            node::RangeDecl,
            node::TupleRangeDecl
        >;

    }

    struct RangeDecl: category_base<RangeDecl, detail::range_decl> {
        using base = category_base<RangeDecl, detail::range_decl>;
        using base::base;
    };

}
