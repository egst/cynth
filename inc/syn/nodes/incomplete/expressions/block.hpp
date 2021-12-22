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

    /***
    { stmt; ... }
    ***/
    struct Block {
        esl::component_vector<category::Statement> statements;

        interface::DisplayResult              display           ()                const;
        interface::StatementProcessingResult  processStatement  (context::Main &) const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
        interface::ExpressionProcessingResult processProgram    (context::Main &) const;

    private:
        // Generic implementation for both `processProgram` and `processExpression`.
        template <bool Program = true> interface::ExpressionProcessingResult process (context::Main &) const;
    };

}
