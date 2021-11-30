#pragma once

#include "esl/component.hpp"

#include "sem/context.hpp"
#include "ast/interface_types.hpp"
#include "ast/forward_categories.hpp"

// Note: No macros escape this file.
#define ARRAY_INTEFRACE \
    DisplayResult display () const; \
    ArrayElementEvaluationResult evaluateArrayElement (sem::Context &) const

namespace cynth::ast::node {

    /** a to b */
    struct RangeTo {
        esl::component<category::Expression> from;
        esl::component<category::Expression> to;

        ARRAY_INTEFRACE;
    };

    /** a to b by c */
    struct RangeToBy {
        esl::component<category::Expression> from;
        esl::component<category::Expression> to;
        esl::component<category::Expression> by;

        ARRAY_INTEFRACE;
    };

    /** ...a */
    struct Spread {
        esl::component<category::Expression> container;

        ARRAY_INTEFRACE;
    };

}

#undef ARRAY_INTEFRACE
