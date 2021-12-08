#pragma once

#include <string>

#include "esl/category.hpp"

#include "sem/numeric_types.hpp"
#include "sem/context.hpp"
#include "sem/translation_context.hpp"
#include "ast/interface_types.hpp"
#include "ast/forward_categories.hpp"


// Note: No macros escape this file.
#define DISPLAY_INTERFACE() \
    DisplayResult display () const

#define TRANSLATE_INTERFACE() \
    TranslationResult translate (sem::TranslationContext &) const

#define EVALUATE_INTERFACE() \
    EvaluationResult evaluate (sem::Context &) const

#define EXECUTE_INTERFACE() \
    ExecutionResult execute (sem::Context &) const

#define EVALUATE_TARGET_INTERFACE() \
    TargetEvaluationResult evaluateTarget (sem::Context &) const

#define EXPRESSION_INTERFACE \
    DISPLAY_INTERFACE(); \
    TRANSLATE_INTERFACE(); \
    EVALUATE_INTERFACE()

namespace cynth::ast::node {

    /** a + b */
    struct Add {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
    };

    /** a && b */
    struct And {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
    };

    /** f(in) */
    struct Application {
        esl::component<category::Expression> function;
        esl::component<category::Expression> arguments;

        EXPRESSION_INTERFACE;
    };

    /** [a, ...] */
    struct Array {
        esl::component_vector<category::ArrayElement> elements;

        EXPRESSION_INTERFACE;
    };

    /** { stmt; ... } */
    struct Block {
        esl::component_vector<category::Statement> statements;

        DISPLAY_INTERFACE();
        TRANSLATE_INTERFACE();
        EVALUATE_INTERFACE();
        EXECUTE_INTERFACE();

        template <bool = true> EvaluationResult evaluate (sem::Context &) const;
    };

    /**
     *  true
     *  false
     */
    struct Bool {
        bool value;

        EXPRESSION_INTERFACE;
    };

    /** T(a) */
    struct Conversion {
        esl::component<category::Type>       type;
        esl::component<category::Expression> argument;

        EXPRESSION_INTERFACE;
    };

    /** a / b */
    struct Div {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
    };

    /** a == b */
    struct Eq {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
    };

    /** for (T e in a) x */
    struct ExprFor {
        esl::component<category::RangeDeclaration> declarations;
        esl::component<category::Expression>       body;

        EXPRESSION_INTERFACE;
        EXECUTE_INTERFACE();
    };

    /** if (cond) a else b */
    struct ExprIf {
        esl::component<category::Expression> condition;
        esl::component<category::Expression> positive_branch;
        esl::component<category::Expression> negative_branch;

        EXPRESSION_INTERFACE;
        EXECUTE_INTERFACE();
    };

    /** 12.34e-56 */
    struct Float {
        sem::Floating value;

        EXPRESSION_INTERFACE;
    };

    /** Out fn (In a) */
    struct Function {
        esl::component<category::Type>        output;
        esl::component<category::Declaration> input;
        esl::component<category::Expression>  body;

        EXPRESSION_INTERFACE;
    };

    /** a >= b */
    struct Ge {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
    };

    /** a > b */
    struct Gt {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
    };

    /** 12e-34 */
    struct Int {
        sem::Integral value;

        EXPRESSION_INTERFACE;
    };

    /** a <= b */
    struct Le {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
    };

    /** a < b */
    struct Lt {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
    };

    /** a - b */
    struct Minus {
        esl::component<category::Expression> argument;

        EXPRESSION_INTERFACE;
    };

    /** a % b */
    struct Mod {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
    };

    /** a * b */
    struct Mul {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
    };

    /** a */
    struct Name {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        esl::component<std::string> name;

        EXPRESSION_INTERFACE;
        EVALUATE_TARGET_INTERFACE();
    };

    /** a != b */
    struct Ne {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
    };

    /** !a */
    struct Not {
        esl::component<category::Expression> argument;

        EXPRESSION_INTERFACE;
    };

    /** a || b */
    struct Or {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
    };

    /** a + b */
    struct Plus {
        esl::component<category::Expression> argument;

        EXPRESSION_INTERFACE;
    };

    /** a ** b */
    struct Pow {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
    };

    /** "abc" */
    struct String {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        esl::component<std::string> value;

        EXPRESSION_INTERFACE;
    };

    /** a - b */
    struct Sub {
        esl::component<category::Expression> left_argument;
        esl::component<category::Expression> right_argument;

        EXPRESSION_INTERFACE;
    };

    /** a[b] */
    struct Subscript {
        esl::component<category::Expression>          container;
        esl::component_vector<category::ArrayElement> location;

        EXPRESSION_INTERFACE;
        EVALUATE_TARGET_INTERFACE();
    };

    /** (a, ...) */
    struct Tuple {
        // TODO: Non-unary vector?
        esl::component_vector<category::Expression> values;

        EXPRESSION_INTERFACE;
        EVALUATE_TARGET_INTERFACE();
    };

}

#undef DISPLAY_INTERFACE
#undef TRANSLATE_INTERFACE
#undef EVALUATE_INTERFACE
#undef EXECUTE_INTERFACE
#undef EVALUATE_TARGET_INTERFACE
#undef EXPRESSION_INTERFACE
