#pragma once

#include "esl/category.hpp"

#include "ast/nodes/declarations.hpp"

namespace cynth::ast::category {

    namespace detail::declaration {

        using Variant = std::variant<
            node::Declaration,
            node::TupleDecl
        >;

    }

    struct Declaration: esl::category<Declaration, detail::declaration::Variant> {
        using base = esl::category<Declaration, detail::declaration::Variant>;
        using base::base;
    };

}
