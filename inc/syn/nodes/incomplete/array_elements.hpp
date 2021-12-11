#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

// Note: No macros escape this file.
#define ARRAY_INTEFRACE \
    interface::DisplayResult display () const; \
    interface::ArrayElementEvaluationResult evaluateArrayElement (context::Cynth &) const

namespace cynth::syn::node {

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
