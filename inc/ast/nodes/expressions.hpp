#pragma once

#include "ast/interface_types.hpp"
#include "ast/categories_forward.hpp"
#include "component.hpp"
#include "asg/values.hpp"
#include "asg/declarations.hpp"
#include "context.hpp"

#include <string>

namespace cynth::ast::node {

    /** a + b */
    struct Add {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a && b */
    struct And {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** f(in) */
    struct Application {
        component<category::Expression> function;
        component<category::Expression> arguments;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** [a, ...] */
    struct Array {
        component_vector<category::ArrayElem> elements;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** { stmt; ... } */
    struct Block {
        component_vector<category::Statement> statements;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
        execution_result  execute  (context &) const;
    };

    /**
     *  true
     *  false
     */
    struct Bool {
        bool value;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** T(a) */
    struct Conversion {
        component<category::Type>       type;
        component<category::Expression> argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a / b */
    struct Div {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a == b */
    struct Eq {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** for (T e in a) x */
    struct ExprFor {
        component<category::RangeDecl>  declarations;
        component<category::Expression> body;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
        execution_result  execute  (context &) const;
    };

    /** if (cond) a else b */
    struct ExprIf {
        component<category::Expression> condition;
        component<category::Expression> positive_branch;
        component<category::Expression> negative_branch;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
        execution_result  execute  (context &) const;
    };

    /** 12.34e-56 */
    struct Float {
        floating value;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** Out fn (In a) */
    struct Function {
        component<category::Type>        output;
        component<category::Declaration> input;
        component<category::Expression>  body;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a >= b */
    struct Ge {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a > b */
    struct Gt {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** 12e-34 */
    struct Int {
        integral value;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a <= b */
    struct Le {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a < b */
    struct Lt {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a - b */
    struct Minus {
        component<category::Expression> argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a % b */
    struct Mod {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a * b */
    struct Mul {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a */
    struct Name {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        component<std::string> name;

        display_result     display     ()          const;
        evaluation_result  evaluate    (context &) const;
        target_eval_result eval_target (context &) const;
    };

    /** a != b */
    struct Ne {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** !a */
    struct Not {
        component<category::Expression> argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a || b */
    struct Or {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a + b */
    struct Plus {
        component<category::Expression> argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a ** b */
    struct Pow {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** "abc" */
    struct String {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        component<std::string> value;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a - b */
    struct Sub {
        component<category::Expression> left_argument;
        component<category::Expression> right_argument;

        display_result    display  ()          const;
        evaluation_result evaluate (context &) const;
    };

    /** a[b] */
    struct Subscript {
        component        <category::Expression> container;
        component_vector <category::ArrayElem>  location;

        display_result     display     ()          const;
        evaluation_result  evaluate    (context &) const;
        target_eval_result eval_target (context &) const;
    };

    /** (a, ...) */
    struct Tuple {
        // TODO: Non-unary vector?
        component_vector<category::Expression> values;

        display_result     display     ()          const;
        evaluation_result  evaluate    (context &) const;
        target_eval_result eval_target (context &) const;
    };

}
