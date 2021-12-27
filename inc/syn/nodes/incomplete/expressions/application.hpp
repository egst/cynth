#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    /** f(in) */
    struct Application {
        esl::component<category::Expression> function;
        esl::component<category::Expression> arguments;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

}
