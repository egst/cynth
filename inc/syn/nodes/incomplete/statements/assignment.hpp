#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    /** a = b */
    struct Assignment {
        // Target is syntactically any expression (otherwise it would be too complicated to parse),
        // but semantically it may be only be a name or a tuple of names.
        // TODO: This is no longer true. Should I type this tighter?
        esl::component<category::Expression> target;
        esl::component<category::Expression> value;

        interface::DisplayResult             display          ()                  const;
        interface::StatementProcessingResult processStatement (context::Main   &) const;
        interface::NameExtractionResult      extractNames     (context::Lookup &) const;
        interface::TypeNameExtractionResult  extractTypeNames (context::Lookup &) const;
    };

}
