#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    /** when (cond) a */
    struct When {
        esl::component <category::Expression> condition;
        esl::component <category::Statement>  branch;

        interface::DisplayResult             display          ()                  const;
        interface::StatementProcessingResult processStatement (context::Main   &) const;
        interface::NameExtractionResult      extractNames     (context::Lookup &) const;
        interface::TypeNameExtractionResult  extractTypeNames (context::Lookup &) const;
    };

}
