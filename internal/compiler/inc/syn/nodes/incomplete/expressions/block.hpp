#pragma once

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

        interface::DisplayResult              display           ()                  const;
        interface::StatementProcessingResult  processStatement  (context::Main   &) const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::ExpressionProcessingResult processProgram    (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

}
