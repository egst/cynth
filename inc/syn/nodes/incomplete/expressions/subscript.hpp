#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    /** a[b] */
    struct Subscript {
        esl::component<category::Expression>          container;
        esl::component_vector<category::ArrayElement> location;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
        interface::TargetResolutionResult     resolveTarget     (context::Main &) const;
    };

}
