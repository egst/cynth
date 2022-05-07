#pragma once

#include "esl/category.hpp"
#include "esl/type_manip.hpp"

// Circular dependencies:
#include "syn/categories/incomplete/expression.hpp"
#include "syn/nodes/incomplete/array_elements.hpp"

namespace cynth::syn::category {

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
