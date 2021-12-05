#pragma once

#include "esl/component.hpp"

#include "sem/context.hpp"
#include "ast/interface_types.hpp"
#include "ast/forward_categories.hpp"

// Note: No macros escape this file.
#define RANGE_DECLARATION_INTERFACE \
    DisplayResult display () const; \
    RangeDeclarationEvaluationResult evaluateRangeDeclaration (sem::Context &) const

namespace cynth::ast::node {

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
