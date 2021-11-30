#pragma once

#include "esl/component.hpp"

#include "sem/context.hpp"
#include "sem/translation_context.hpp"
#include "ast/forward_categories.hpp"
#include "ast/interface_types.hpp"
#include "ast/nodes/expressions.hpp"

// Note: No macros escape this file.
#define DECLARATION_INTERFACE \
    DisplayResult display () const; \
    DeclarationEvaluationResult evaluateDeclaration (sem::Context &) const; \
    ExecutionResult execute (sem::Context &) const; \
    TranslationResult translate (sem::TranslationContext &) const

namespace cynth::ast::node {

    /** T a */
    struct Declaration {
        esl::component<node::Name>     name;
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
