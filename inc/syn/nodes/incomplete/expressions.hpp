#pragma once

#include <string>
#include <type_traits>

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"
#include "sem/numeric_types.hpp"

// Expressions in separate headers:
#include "syn/nodes/incomplete/expressions/application.hpp"
#include "syn/nodes/incomplete/expressions/array.hpp"
#include "syn/nodes/incomplete/expressions/block.hpp"
#include "syn/nodes/incomplete/expressions/conversion.hpp"
#include "syn/nodes/incomplete/expressions/expr_for.hpp"
#include "syn/nodes/incomplete/expressions/expr_if.hpp"
#include "syn/nodes/incomplete/expressions/function.hpp"
#include "syn/nodes/incomplete/expressions/subscript.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    //// Atomic expressions ////

    /**
     *  true
     *  false
     */
    struct Bool {
        bool value;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** 12.34e-56 */
    struct Float {
        sem::Floating value;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** 12e-34 */
    struct Int {
        sem::Integral value;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a */
    struct Name {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        esl::component<std::string> name;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
        interface::TargetResolutionResult     resolveTarget     (context::Main &) const;
    };

    /** "abc" */
    struct String {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        esl::component<std::string> value;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** (a, ...) */
    struct Tuple {
        esl::component_vector<category::Expression> values;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
        interface::TargetResolutionResult     resolveTarget     (context::Main &) const;
    };

    //// Operations ////

    /** a + b */
    struct Add {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a && b */
    struct And {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a / b */
    struct Div {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a == b */
    struct Eq {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a >= b */
    struct Ge {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a > b */
    struct Gt {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a <= b */
    struct Le {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a < b */
    struct Lt {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a - b */
    struct Minus {
        esl::component<category::Expression> argument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a % b */
    struct Mod {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a * b */
    struct Mul {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a != b */
    struct Ne {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** !a */
    struct Not {
        esl::component<category::Expression> argument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a || b */
    struct Or {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a + b */
    struct Plus {
        esl::component<category::Expression> argument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a ** b */
    struct Pow {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

    /** a - b */
    struct Sub {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        interface::DisplayResult              display           ()                const;
        interface::ExpressionProcessingResult processExpression (context::Main &) const;
    };

}
