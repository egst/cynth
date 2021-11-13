#pragma once

#include "ast/interface_types.hpp"
#include "ast/categories_forward.hpp"
#include "component.hpp"
#include "sem/values.hpp"
#include "sem/declarations.hpp"
#include "sem/context.hpp"
#include "sem/translation_context.hpp"

#include <string>

// Note: Macros are always undefined at the end of the file.
#define EXPR_DECL \
    display_result     display     ()                           const; \
    evaluation_result  evaluate    (sem::context &)             const; \
    translation_result translate   (sem::translation_context &) const
#define NOEVAL_DECL \
    display_result     display     ()                           const; \
    translation_result translate   (sem::translation_context &) const
#define EXEC_DECL \
    execution_result   execute     (sem::context &)             const
#define TARGET_DECL \
    target_eval_result eval_target (sem::context &)             const

namespace cynth::ast::node {

    /** a + b */
    struct Add {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        EXPR_DECL;
    };

    /** a && b */
    struct And {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        EXPR_DECL;
    };

    /** f(in) */
    struct Application {
        component<category::Expression> function;
        component<category::Expression> arguments;

        EXPR_DECL;
    };

    /** [a, ...] */
    struct Array {
        component_vector<category::ArrayElem> elements;

        EXPR_DECL;
    };

    /** { stmt; ... } */
    struct Block {
        component_vector<category::Statement> statements;

        template <bool = true> evaluation_result evaluate (sem::context &) const;

        NOEVAL_DECL;
        EXEC_DECL;
    };

    /**
     *  true
     *  false
     */
    struct Bool {
        bool value;

        EXPR_DECL;
    };

    /** T(a) */
    struct Conversion {
        component<category::Type>       type;
        component<category::Expression> argument;

        EXPR_DECL;
    };

    /** a / b */
    struct Div {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        EXPR_DECL;
    };

    /** a == b */
    struct Eq {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        EXPR_DECL;
    };

    /** for (T e in a) x */
    struct ExprFor {
        component<category::RangeDecl>  declarations;
        component<category::Expression> body;

        EXPR_DECL;
        EXEC_DECL;
    };

    /** if (cond) a else b */
    struct ExprIf {
        component<category::Expression> condition;
        component<category::Expression> positive_branch;
        component<category::Expression> negative_branch;

        EXPR_DECL;
        EXEC_DECL;
    };

    /** 12.34e-56 */
    struct Float {
        floating value;

        EXPR_DECL;
    };

    /** Out fn (In a) */
    struct Function {
        component<category::Type>        output;
        component<category::Declaration> input;
        component<category::Expression>  body;

        EXPR_DECL;
    };

    /** a >= b */
    struct Ge {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        EXPR_DECL;
    };

    /** a > b */
    struct Gt {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        EXPR_DECL;
    };

    /** 12e-34 */
    struct Int {
        integral value;

        EXPR_DECL;
    };

    /** a <= b */
    struct Le {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        EXPR_DECL;
    };

    /** a < b */
    struct Lt {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        EXPR_DECL;
    };

    /** a - b */
    struct Minus {
        component<category::Expression> argument;

        EXPR_DECL;
    };

    /** a % b */
    struct Mod {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        EXPR_DECL;
    };

    /** a * b */
    struct Mul {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        EXPR_DECL;
    };

    /** a */
    struct Name {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        component<std::string> name;

        EXPR_DECL;
        TARGET_DECL;
    };

    /** a != b */
    struct Ne {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        EXPR_DECL;
    };

    /** !a */
    struct Not {
        component<category::Expression> argument;

        EXPR_DECL;
    };

    /** a || b */
    struct Or {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        EXPR_DECL;
    };

    /** a + b */
    struct Plus {
        component<category::Expression> argument;

        EXPR_DECL;
    };

    /** a ** b */
    struct Pow {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        EXPR_DECL;
    };

    /** "abc" */
    struct String {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        component<std::string> value;

        EXPR_DECL;
    };

    /** a - b */
    struct Sub {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        EXPR_DECL;
    };

    /** a[b] */
    struct Subscript {
        component        <category::Expression> container;
        component_vector <category::ArrayElem>  location;

        EXPR_DECL;
        TARGET_DECL;
    };

    /** (a, ...) */
    struct Tuple {
        // TODO: Non-unary vector?
        component_vector<category::Expression> values;

        EXPR_DECL;
        TARGET_DECL;
    };

}

#undef EXPR_DECL
#undef EXEC_DECL
#undef TARGET_DECL
