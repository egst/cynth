#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    /** T a = b */
    struct Definition {
        esl::component<category::Declaration> target;
        esl::component<category::Expression>  value;

        interface::DisplayResult             display          ()                const;
        interface::StatementProcessingResult processStatement (context::Main &) const;
    };

}
