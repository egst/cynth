#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    /** T e in a */
    struct RangeDecl {
        esl::component<category::Declaration> declaration;
        esl::component<category::Expression>  range;

        interface::DisplayResult                    display                 ()                  const;
        interface::RangeDeclarationResolutionResult resolveRangeDeclaration (context::Main   &) const;
        interface::NameExtractionResult             extractNames            (context::Lookup &) const;
        interface::TypeNameExtractionResult         extractTypeNames        (context::Lookup &) const;
    };

    /** (T e in a, ...) */
    struct TupleRangeDecl {
        esl::component_vector<category::RangeDeclaration> declarations;

        interface::DisplayResult                    display                 ()                  const;
        interface::RangeDeclarationResolutionResult resolveRangeDeclaration (context::Main   &) const;
        interface::NameExtractionResult             extractNames            (context::Lookup &) const;
        interface::TypeNameExtractionResult         extractTypeNames        (context::Lookup &) const;
    };

}
