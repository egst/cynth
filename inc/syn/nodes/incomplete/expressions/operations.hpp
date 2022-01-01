#pragma once

#include <string>

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    /** a + b */
    struct Add {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** a && b */
    struct And {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** a / b */
    struct Div {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** a == b */
    struct Eq {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** a >= b */
    struct Ge {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** a > b */
    struct Gt {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** a <= b */
    struct Le {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** a < b */
    struct Lt {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** a - b */
    struct Minus {
        esl::component<category::Expression> argument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** a % b */
    struct Mod {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** a * b */
    struct Mul {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** a != b */
    struct Ne {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** !a */
    struct Not {
        esl::component<category::Expression> argument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** a || b */
    struct Or {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** a + b */
    struct Plus {
        esl::component<category::Expression> argument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** a ** b */
    struct Pow {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

    /** a - b */
    struct Sub {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                  const;
        interface::ExpressionProcessingResult processExpression (context::Main   &) const;
        interface::NameExtractionResult       extractNames      (context::Lookup &) const;
        interface::TypeNameExtractionResult   extractTypeNames  (context::Lookup &) const;
    };

}
