#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"
#include "syn/nodes/incomplete/expressions.hpp"

namespace cynth::syn::node {

    /** T a */
    struct Declaration {
        node::Name                     name;
        esl::component<category::Type> type;

        interface::DisplayResult               display            ()                const;
        interface::DeclarationResolutionResult resolveDeclaration (context::Main &) const;
        interface::StatementProcessingResult   processStatement   (context::Main &) const;
    };

    /** (T a, ...) */
    struct TupleDecl {
        esl::component_vector<category::Declaration> declarations;

        interface::DisplayResult               display            ()                const;
        interface::DeclarationResolutionResult resolveDeclaration (context::Main &) const;
        interface::StatementProcessingResult   processStatement   (context::Main &) const;
    };

}
