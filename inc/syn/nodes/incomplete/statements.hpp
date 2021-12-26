#pragma once

#include <string>

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Statements in separate headers:
#include "syn/nodes/incomplete/statements/assignment.hpp"
#include "syn/nodes/incomplete/statements/definition.hpp"
#include "syn/nodes/incomplete/statements/for.hpp"
#include "syn/nodes/incomplete/statements/if.hpp"
#include "syn/nodes/incomplete/statements/return.hpp"
#include "syn/nodes/incomplete/statements/when.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"
#include "syn/nodes/incomplete/expressions.hpp"
#include "syn/nodes/incomplete/types.hpp"

// Note: No macros escape this file.
#define STATEMENT_INTERFACE \
    interface::DisplayResult display () const; \
    interface::StatementProcessingResult processStatement (context::Main &) const

namespace cynth::syn::node {

    /** Out f (In a) b */
    struct FunDef {
        esl::component<category::Type>        output;
        esl::component<category::Declaration> input;
        node::Name                            name;
        esl::component<category::Expression>  body;

        STATEMENT_INTERFACE;
    };

    /** type T = U */
    struct TypeDef {
        node::TypeName                 target;
        esl::component<category::Type> type;

        STATEMENT_INTERFACE;
    };

    /** while (cond) a */
    struct While {
        esl::component<category::Expression> condition;
        esl::component<category::Statement>  body;

        STATEMENT_INTERFACE;
    };

}

#undef STATEMENT_INTERFACE
