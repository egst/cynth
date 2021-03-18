#pragma once

#include "ast/category_base.hpp"
#include "ast/categories/declaration.hpp"
#include "ast/categories/expression.hpp"
#include "util/general.hpp"

namespace cynth::ast::category {

    namespace detail {

        using pattern = util::concat <
            decltype(category::Declaration::node),
            decltype(category::Expression::node)
        >;

    }

    struct Pattern: detail::category_base<Pattern, detail::pattern> {
        using base = detail::category_base<Pattern, detail::pattern>;
        using base::base;
        using base::operator=;
    };

}
