#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

// Note: No macros escape this file.
#define RANGE_DECLARATION_INTERFACE \
    interface::DisplayResult display () const; \
    interface::RangeDeclarationResolutionResult resolveRangeDeclaration (context::C &) const

namespace cynth::syn::node {

    /** T e in a */
    struct RangeDecl {
        esl::component<category::Declaration> declaration;
        esl::component<category::Expression>  range;

        RANGE_DECLARATION_INTERFACE;
    };

    /** (T e in a, ...) */
    struct TupleRangeDecl {
        esl::component_vector<category::RangeDeclaration> declarations;

        RANGE_DECLARATION_INTERFACE;
    };

}

#undef RANGE_DECLARATION_INTERFACE
