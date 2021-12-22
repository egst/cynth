#pragma once

#include <string>
#include <type_traits>

#include "esl/category.hpp"
#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    /** if (cond) a else b */
    struct ExprIf {
        esl::component<category::Expression> condition;
        esl::component<category::Expression> positiveBranch;
        esl::component<category::Expression> negativeBranch;

        interface::DisplayResult              display           ()                const;
        interface::StatementProcessingResult  processStatement  (context::Main &) const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

}
