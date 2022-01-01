#pragma once

#include <string>
#include <type_traits>

#include "esl/category.hpp"
#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    /** Out fn (In a) */
    struct Function {
        esl::component<category::Type>        output;
        esl::component<category::Declaration> input;
        esl::component<category::Expression>  body;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

}
