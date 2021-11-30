#pragma once

#include "esl/type_manip.hpp"
#include "esl/category.hpp"

#include "ast/nodes/array_elements.hpp"
#include "ast/categories/expression.hpp"

namespace cynth::ast::category {

    namespace detail::array_element {

        using Variant = esl::extend<
            category::Expression::variant,
            node::RangeTo,
            node::RangeToBy,
            node::Spread
        >;

    }

    struct ArrayElement: esl::category<ArrayElement, detail::array_element::Variant> {
        using base = esl::category<ArrayElement, detail::array_element::Variant>;
        using base::base;
    };

}
