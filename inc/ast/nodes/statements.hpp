#pragma once

#include "esl/component.hpp"

#include "sem/context.hpp"
#include "sem/translation_context.hpp"
#include "ast/forward_categories.hpp"
#include "ast/interface_types.hpp"
#include "ast/nodes/expressions.hpp"
#include "ast/nodes/types.hpp"

#include <string>

// Note: No macros escape this file.
#define STATEMENT_INTERFACE \
    DisplayResult display () const; \
    ExecutionResult execute (sem::Context &) const; \
    TranslationResult translate (sem::TranslationContext &) const

namespace cynth::ast::node {

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

    /** for (T e in a) x */
    struct For {
        esl::component<category::RangeDeclaration> declarations;
        esl::component<category::Statement>        body;

        STATEMENT_INTERFACE;
    };

    /** Out f (In a) b */
    struct FunDef {
        esl::component<category::Type>        output;
        esl::component<category::Declaration> input;
        esl::component<node::Name>            name;
        esl::component<category::Expression>  body;

        STATEMENT_INTERFACE;
    };

    /** if (cond) a else b */
    struct If {
        esl::component<category::Expression> condition;
        esl::component<category::Statement>  positive_branch;
        esl::component<category::Statement>  negative_branch;

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
        esl::component<node::TypeName> target;
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
