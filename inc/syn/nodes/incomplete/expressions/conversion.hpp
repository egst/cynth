#pragma once

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    /** T(a) */
    struct Conversion {
        esl::component<category::Type>       type;
        esl::component<category::Expression> argument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

}
