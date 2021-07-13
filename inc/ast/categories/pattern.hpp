#pragma once

#include "asg/declarations.hpp"
#include "category_base.hpp"
#include "ast/categories/declaration.hpp"
#include "ast/categories/expression.hpp"
#include "util/general.hpp"

namespace cynth::ast::category {

    namespace detail {

        using pattern = util::concat <
            category::Declaration::variant,
            category::Expression::variant
        >;

    }

    struct Pattern: category_base<Pattern, detail::pattern> {
        using base = category_base<Pattern, detail::pattern>;
        using base::base;
    };

}
