#pragma once

#include <string>

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Statements in separate headers:
#include "syn/nodes/incomplete/statements/for.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"
#include "syn/nodes/incomplete/expressions.hpp"
#include "syn/nodes/incomplete/types.hpp"

// Note: No macros escape this file.
#define STATEMENT_INTERFACE \
    interface::DisplayResult display () const; \
    interface::StatementProcessingResult processStatement (context::Main &) const

namespace cynth::syn::node {

    /** a = b */
    struct Assignment {
        // Target is syntactically any expression (otherwise it would be too complicated to parse),
        // but semantically it may be only be a name or a tuple of names.
        // TODO: This is no longer true. Should I type this tighter?
        esl::component<category::Expression> target;
        esl::component<category::Expression> value;

        STATEMENT_INTERFACE;
    };

    /** T a = b */
    struct Definition {
        esl::component<category::Declaration> target;
        esl::component<category::Expression>  value;

        STATEMENT_INTERFACE;
    };

    /** Out f (In a) b */
    struct FunDef {
        esl::component<category::Type>        output;
        esl::component<category::Declaration> input;
        node::Name                            name;
        esl::component<category::Expression>  body;

        STATEMENT_INTERFACE;
    };

    /** if (cond) a else b */
    struct If {
        esl::component<category::Expression> condition;
        esl::component<category::Statement>  positiveBranch;
        esl::component<category::Statement>  negativeBranch;

        STATEMENT_INTERFACE;
    };

    /** return a
        return ()
        return */
    struct Return {
        esl::component<category::Expression> value;

        STATEMENT_INTERFACE;
    };

    /** type T = U */
    struct TypeDef {
        node::TypeName                 target;
        esl::component<category::Type> type;

        STATEMENT_INTERFACE;
    };

    /** when (cond) a */
    struct When {
        esl::component <category::Expression> condition;
        esl::component <category::Statement>  branch;

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
