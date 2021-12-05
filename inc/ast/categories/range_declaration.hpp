#pragma once

#include <variant>

#include "esl/category.hpp"

#include "ast/nodes/range_declarations.hpp"

namespace cynth::ast::category {

    namespace detail::range_declaration {

        using Variant = std::variant<
            node::RangeDecl,
            node::TupleRangeDecl
        >;

    }

    struct RangeDeclaration: esl::category<RangeDeclaration, detail::range_declaration::Variant> {
        using base = esl::category<RangeDeclaration, detail::range_declaration::Variant>;
        using base::base;
    };

}
