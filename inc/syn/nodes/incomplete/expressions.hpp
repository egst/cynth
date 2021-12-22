#pragma once

#include <string>
#include <type_traits>

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"
#include "sem/numeric_types.hpp"

// Expressions in separate headers:
#include "syn/nodes/incomplete/expressions/block.hpp"
#include "syn/nodes/incomplete/expressions/expr_for.hpp"
#include "syn/nodes/incomplete/expressions/expr_if.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

// Note: No macros escape this file.
#define DISPLAY \
    interface::DisplayResult display () const
#define EXPRESSION_INTERFACE \
    interface::ExpressionProcessingResult processExpression (context::Main &) const
#define PROGRAM_INTERFACE \
    interface::ExpressionProcessingResult processProgram (context::Main &) const
#define STATEMENT_INTERFACE \
    interface::StatementProcessingResult processStatement (context::Main &) const
#define TARGET_INTERFACE \
    interface::TargetResolutionResult resolveTarget (context::Main &) const

namespace cynth::syn::node {

    /** a + b */
    struct Add {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a && b */
    struct And {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** f(in) */
    struct Application {
        esl::component<category::Expression> function;
        esl::component<category::Expression> arguments;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** [a, ...] */
    struct Array {
        esl::component_vector<category::ArrayElement> elements;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /**
     *  true
     *  false
     */
    struct Bool {
        bool value;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** T(a) */
    struct Conversion {
        esl::component<category::Type>       type;
        esl::component<category::Expression> argument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a / b */
    struct Div {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a == b */
    struct Eq {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** 12.34e-56 */
    struct Float {
        sem::Floating value;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** Out fn (In a) */
    struct Function {
        esl::component<category::Type>        output;
        esl::component<category::Declaration> input;
        esl::component<category::Expression>  body;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a >= b */
    struct Ge {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a > b */
    struct Gt {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** 12e-34 */
    struct Int {
        sem::Integral value;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a <= b */
    struct Le {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a < b */
    struct Lt {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a - b */
    struct Minus {
        esl::component<category::Expression> argument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a % b */
    struct Mod {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a * b */
    struct Mul {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a */
    struct Name {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        esl::component<std::string> name;

        EXPRESSION_INTERFACE;
        DISPLAY;
        TARGET_INTERFACE;
    };

    /** a != b */
    struct Ne {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** !a */
    struct Not {
        esl::component<category::Expression> argument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a || b */
    struct Or {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a + b */
    struct Plus {
        esl::component<category::Expression> argument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a ** b */
    struct Pow {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** "abc" */
    struct String {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        esl::component<std::string> value;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a - b */
    struct Sub {
        esl::component<category::Expression> leftArgument;
        esl::component<category::Expression> rightArgument;

        EXPRESSION_INTERFACE;
        DISPLAY;
    };

    /** a[b] */
    struct Subscript {
        esl::component<category::Expression>          container;
        esl::component_vector<category::ArrayElement> location;

        EXPRESSION_INTERFACE;
        DISPLAY;
        TARGET_INTERFACE;
    };

    /** (a, ...) */
    struct Tuple {
        // TODO: Non-unary vector?
        esl::component_vector<category::Expression> values;

        EXPRESSION_INTERFACE;
        DISPLAY;
        TARGET_INTERFACE;
    };

}

#undef DISPLAY
#undef EXPRESSION_INTERFACE
#undef STATEMENT_INTERFACE
#undef TARGET_INTERFACE
