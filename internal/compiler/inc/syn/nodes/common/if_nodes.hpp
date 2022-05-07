#pragma once

#include "context/main.hpp"
#include "interface/nodes.hpp"
#include "syn/categories/expression.hpp"

namespace cynth::syn::if_nodes {

    template <typename Branch>
    interface::StatementProcessingResult processStatement (
        context::Main              &,
        category::Expression const & condition,
        Branch               const & positiveBranch,
        Branch               const * negativeBranch = nullptr
    );

}
