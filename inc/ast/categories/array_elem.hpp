#pragma once

#include "category_base.hpp"
#include "ast/nodes/array_elems.hpp"
#include "ast/categories/expression.hpp"
#include "util/general.hpp"

namespace cynth::ast::category {

    namespace detail {

        using array_elem = util::extend <
            category::Expression::variant,
            node::RangeTo,
            node::RangeToBy,
            node::Spread
        >;

    }

    struct ArrayElem: category_base<ArrayElem, detail::array_elem> {
        using base = category_base<ArrayElem, detail::array_elem>;
        using base::base;
    };

}
