#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    /** while (cond) a */
    struct While {
        esl::component<category::Expression> condition;
        esl::component<category::Statement>  body;

        interface::DisplayResult             display          ()                const;
        interface::StatementProcessingResult processStatement (context::Main &) const;
    };

}
