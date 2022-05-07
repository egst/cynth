#pragma once

#include "esl/category.hpp"

// Circular dependencies:
#include "syn/nodes/incomplete/declarations.hpp"

namespace cynth::syn::category {

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
