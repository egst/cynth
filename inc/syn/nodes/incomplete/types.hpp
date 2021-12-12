#pragma once

#include <string>

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

// Note: No macros escape this file.
#define TYPE_INTERFACE \
    interface::DisplayResult display () const; \
    interface::TypeResolutionResult resolveType (context::C &) const

namespace cynth::syn::node {

    /** T [a]
        T [T a]
        T [$]
        T [] */
    struct ArrayType {
        esl::component<category::Type> type;
        esl::optional_component<category::Pattern> size;

        TYPE_INTERFACE;
    };

    /** $ */
    struct Auto {
        TYPE_INTERFACE;
    };

    /** buffer [a] */
    // TODO: Maybe allow pattern size here too?
    // Incomplete sem buffer type is declared, so right now it's possible semantically, but not syntactically.
    struct BufferType {
        esl::component<category::Expression> size;

        TYPE_INTERFACE;
    };

    /** T const */
    struct ConstType {
        esl::component<category::Type> type;

        TYPE_INTERFACE;
    };

    /** Out (In) */
    struct FunctionType {
        esl::component<category::Type> output;
        esl::component<category::Type> input;

        TYPE_INTERFACE;
    };

    /** T in */
    struct InType {
        esl::component<category::Type> type;

        TYPE_INTERFACE;
    };

    /** T out */
    struct OutType {
        esl::component<category::Type> type;

        TYPE_INTERFACE;
    };

    /** (T, ...) */
    struct TupleType {
        // TODO: Non-unary vector?
        esl::component_vector<category::Type> types;

        TYPE_INTERFACE;
    };

    /** T */
    struct TypeName {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        esl::component<std::string> name;

        TYPE_INTERFACE;
    };

    /** type T */
    struct TypeDecl {
        node::TypeName name;

        TYPE_INTERFACE;
    };

}

#undef TYPE_INTERFACE
