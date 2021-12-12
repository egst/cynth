#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"
#include "syn/nodes/incomplete/expressions.hpp"

// Note: No macros escape this file.
#define DECLARATION_INTERFACE \
    interface::DisplayResult display () const; \
    interface::DeclarationResolutionResult resolveDeclaration (context::C &) const; \
    interface::StatementResolutionResult resolveStatement (context::C &) const;

namespace cynth::syn::node {

    /** T a */
    struct Declaration {
        node::Name                     name;
        esl::component<category::Type> type;

        DECLARATION_INTERFACE;
    };

    /** (T a, ...) */
    struct TupleDecl {
        esl::component_vector<category::Declaration> declarations;

        DECLARATION_INTERFACE;
    };

}

#undef DECLARATION_INTERFACE
