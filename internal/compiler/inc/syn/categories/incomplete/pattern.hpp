#pragma once

#include "esl/category.hpp"
#include "esl/type_manip.hpp"

// Circular dependencies:
#include "syn/categories/incomplete/declaration.hpp"
#include "syn/categories/incomplete/expression.hpp"

namespace cynth::syn::category {

    namespace detail::pattern {

        using Variant = esl::concat<
            category::Declaration::variant,
            category::Expression::variant
        >;

    }

    struct Pattern: esl::category<Pattern, detail::pattern::Variant> {
        using base = esl::category<Pattern, detail::pattern::Variant>;
        using base::base;
    };

}
