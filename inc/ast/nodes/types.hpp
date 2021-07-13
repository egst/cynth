#pragma once

#include "ast/interface_types.hpp"
#include "ast/categories_forward.hpp"
#include "component.hpp"
#include "context.hpp"

#include <string>

namespace cynth::ast::node {

    /** T [a]
        T [T a]
        T [$]
        T [] */
    struct ArrayType {
        component          <category::Type>    type;
        optional_component <category::Pattern> size;

        display_result   display   ()          const;
        type_eval_result eval_type (context &) const;
    };

    /** $ */
    struct Auto {
        display_result   display   ()          const;
        type_eval_result eval_type (context &) const;
    };

    /** buffer [a] */
    // TODO: Maybe allow pattern size here too?
    // Incomplete asg buffer type is declared, so right now it's possible semantically, but not syntactically.
    struct BufferType {
        component<category::Expression> size;

        display_result   display   ()          const;
        type_eval_result eval_type (context &) const;
    };

    /** T const */
    struct ConstType {
        component<category::Type> type;

        display_result   display   ()          const;
        type_eval_result eval_type (context &) const;
    };

    /** Out (In) */
    struct FunctionType {
        component<category::Type> output;
        component<category::Type> input;

        display_result   display   ()          const;
        type_eval_result eval_type (context &) const;
    };

    /** T in */
    struct InType {
        component<category::Type> type;

        display_result   display   ()          const;
        type_eval_result eval_type (context &) const;
    };

    /** T out */
    struct OutType {
        component<category::Type> type;

        display_result   display   ()          const;
        type_eval_result eval_type (context &) const;
    };

    /** (T, ...) */
    struct TupleType {
        // TODO: Non-unary vector?
        component_vector<category::Type> types;

        display_result   display   ()          const;
        type_eval_result eval_type (context &) const;
    };

    /** T */
    struct TypeName {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        component<std::string> name;

        display_result   display   ()          const;
        type_eval_result eval_type (context &) const;
    };

    /** type T */
    struct TypeDecl {
        component<ast::node::TypeName> name;

        display_result   display   ()          const;
        type_eval_result eval_type (context &) const;
    };

}
