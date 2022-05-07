#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"
#include "syn/nodes/incomplete/expressions.hpp"

namespace cynth::syn::node {

    /** Out f (In a) b */
    struct FunDef {
        esl::component<category::Type>        output;
        esl::component<category::Declaration> input;
        node::Name                            name;
        esl::component<category::Expression>  body;

        interface::DisplayResult             display          ()                  const;
        interface::StatementProcessingResult processStatement (context::Main   &) const;
        interface::NameExtractionResult      extractNames     (context::Lookup &) const;
        interface::TypeNameExtractionResult  extractTypeNames (context::Lookup &) const;
    };

}
