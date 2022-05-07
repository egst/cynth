#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    /***
    for (T e in a) x
    ***/
    struct For {
        esl::component<category::RangeDeclaration> declarations;
        esl::component<category::Statement>        body;

        interface::DisplayResult             display          ()                  const;
        interface::StatementProcessingResult processStatement (context::Main   &) const;
        interface::NameExtractionResult      extractNames     (context::Lookup &) const;
        interface::TypeNameExtractionResult  extractTypeNames (context::Lookup &) const;
    };

}
