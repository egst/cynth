#pragma once

#include "component.hpp"
#include "ast/interface_types.hpp"
#include "ast/categories_forward.hpp"
#include "sem/context.hpp"

#include <string>

// Note: Macros are always undefined at the end of the file.
#define TYPE_DECL \
    display_result   display   ()               const; \
    type_eval_result eval_type (sem::context &) const

namespace cynth::ast::node {

    /** T [a]
        T [T a]
        T [$]
        T [] */
    struct ArrayType {
        component          <category::Type>    type;
        optional_component <category::Pattern> size;

        TYPE_DECL;
    };

    /** $ */
    struct Auto {
        TYPE_DECL;
    };

    /** buffer [a] */
    // TODO: Maybe allow pattern size here too?
    // Incomplete sem buffer type is declared, so right now it's possible semantically, but not syntactically.
    struct BufferType {
        component<category::Expression> size;

        TYPE_DECL;
    };

    /** T const */
    struct ConstType {
        component<category::Type> type;

        TYPE_DECL;
    };

    /** Out (In) */
    struct FunctionType {
        component<category::Type> output;
        component<category::Type> input;

        TYPE_DECL;
    };

    /** T in */
    struct InType {
        component<category::Type> type;

        TYPE_DECL;
    };

    /** T out */
    struct OutType {
        component<category::Type> type;

        TYPE_DECL;
    };

    /** (T, ...) */
    struct TupleType {
        // TODO: Non-unary vector?
        component_vector<category::Type> types;

        TYPE_DECL;
    };

    /** T */
    struct TypeName {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        component<std::string> name;

        TYPE_DECL;
    };

    /** type T */
    struct TypeDecl {
        component<node::TypeName> name;

        TYPE_DECL;
    };

}

#undef TYPE_DECL
