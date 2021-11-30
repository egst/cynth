#pragma once

#include "esl/type_manip.hpp"
#include "esl/category.hpp"

#include "ast/categories/declaration.hpp"
#include "ast/categories/expression.hpp"

namespace cynth::ast::category {

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
