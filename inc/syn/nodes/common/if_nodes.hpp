#pragma once

#include <string>

#include "esl/tiny_vector.hpp"
#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/nodes.hpp"
#include "syn/categories/expression.hpp"

namespace cynth::syn::if_nodes {

    struct StatementResult {
        interface::StatementProcessingResult returnResult;
        // Returned compile-time values:
        esl::tiny_vector<std::string> posReturnStmts;
        esl::tiny_vector<std::string> negReturnStmts;
    };

    StatementResult processStatement (
        context::Main & outerScope,
        context::Main & posBranchScope,
        context::Main & negBranchScope,
        esl::component<category::Expression> positiveBranch,
        esl::component<category::Expression> negativeBranch
    );

}
