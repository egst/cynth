#pragma once

#include <string>

#include "esl/category.hpp"
#include "esl/component.hpp"

#include "sem/numeric_types.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

// Note: No macros escape this file.
#define DISPLAY_INTERFACE \
    interface::DisplayResult display () const

#define EXPRESSION_INTERFACE \
    interface::ExpressionResolutionResult resolveExpression (context::Cynth &) const

#define STATEMENT_INTERFACE \
    interface::StatementResolutionResult resolveStatement (context::Cynth &) const

#define TARGET_INTERFACE \
    interface::TargetResolutionResult resolveTarget (context::Cynth &) const

namespace cynth::syn::node {

    /** a + b */
    struct Add {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a && b */
    struct And {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** f(in) */
    struct Application {
        esl::component<category::Expression> function;
        esl::component<category::Expression> arguments;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** [a, ...] */
    struct Array {
        esl::component_vector<category::ArrayElement> elements;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** { stmt; ... } */
    struct Block {
        esl::component_vector<category::Statement> statements;

        DISPLAY_INTERFACE;
        EXPRESSION_INTERFACE;
        STATEMENT_INTERFACE;

        template <bool = true> interface::ExpressionResolutionResult resolveExpression (context::Cynth &) const;
    };

    /**
     *  true
     *  false
     */
    struct Bool {
        bool value;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** T(a) */
    struct Conversion {
        esl::component<category::Type>       type;
        esl::component<category::Expression> argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a / b */
    struct Div {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a == b */
    struct Eq {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** for (T e in a) x */
    struct ExprFor {
        esl::component<category::RangeDeclaration> declarations;
        esl::component<category::Expression>       body;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
        STATEMENT_INTERFACE;
    };

    /** if (cond) a else b */
    struct ExprIf {
        esl::component<category::Expression> condition;
        esl::component<category::Expression> positive_branch;
        esl::component<category::Expression> negative_branch;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
        STATEMENT_INTERFACE;
    };

    /** 12.34e-56 */
    struct Float {
        sem::Floating value;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** Out fn (In a) */
    struct Function {
        esl::component<category::Type>        output;
        esl::component<category::Declaration> input;
        esl::component<category::Expression>  body;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a >= b */
    struct Ge {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a > b */
    struct Gt {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** 12e-34 */
    struct Int {
        sem::Integral value;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a <= b */
    struct Le {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a < b */
    struct Lt {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a - b */
    struct Minus {
        esl::component<category::Expression> argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a % b */
    struct Mod {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a * b */
    struct Mul {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a */
    struct Name {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        esl::component<std::string> name;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
        TARGET_INTERFACE;
    };

    /** a != b */
    struct Ne {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** !a */
    struct Not {
        esl::component<category::Expression> argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a || b */
    struct Or {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a + b */
    struct Plus {
        esl::component<category::Expression> argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a ** b */
    struct Pow {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** "abc" */
    struct String {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        esl::component<std::string> value;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a - b */
    struct Sub {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
    };

    /** a[b] */
    struct Subscript {
        esl::component<category::Expression>          container;
        esl::component_vector<category::ArrayElement> location;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
        TARGET_INTERFACE;
    };

    /** (a, ...) */
    struct Tuple {
        // TODO: Non-unary vector?
        esl::component_vector<category::Expression> values;

        EXPRESSION_INTERFACE;
        DISPLAY_INTERFACE;
        TARGET_INTERFACE;
    };

}

#undef DISPLAY_INTERFACE
#undef EXPRESSION_INTERFACE
#undef STATEMENT_INTERFACE
#undef TARGET_INTERFACE
