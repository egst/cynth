#pragma once

#include "ast/category_base.hpp"
#include "ast/nodes/array_elems.hpp"
#include "ast/categories/expression.hpp"
#include "util/general.hpp"

namespace cynth::ast::category {

    namespace detail {

        using array_elem = util::extend <
            decltype(category::Expression::node),
            node::RangeTo,
            node::RangeToBy,
            node::Spread
        >;

    }

    struct ArrayElem: detail::category_base<ArrayElem, detail::array_elem> {
        using base = detail::category_base<ArrayElem, detail::array_elem>;
        using base::base;
        using base::operator=;
    };

}
