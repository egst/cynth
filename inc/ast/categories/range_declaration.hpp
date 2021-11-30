#pragma once

#include <variant>

#include "esl/category.hpp"

#include "ast/nodes/range_declarations.hpp"

namespace cynth::ast::category {

    namespace detail::range_declaration {

        using Variant = std::variant<
            node::RangeDeclaration,
            node::TupleRangeDeclaration
        >;

    }

    struct RangeDecl: esl::category<RangeDecl, detail::range_declaration::Variant> {
        using base = esl::category<RangeDecl, detail::range_declaration::Variant>;
        using base::base;
    };

}
