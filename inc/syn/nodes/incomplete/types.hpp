#pragma once

#include <string>

#include "esl/component.hpp"

#include "context/forward.hpp"
#include "interface/forward.hpp"

// Circular dependencies:
#include "syn/categories/forward.hpp"

namespace cynth::syn::node {

    /***
    T [a]
    T [T a]
    T [$]
    T []
    ***/
    struct ArrayType {
        esl::component<category::Type> type;
        esl::optional_component<category::Pattern> size;

        interface::DisplayResult        display     ()                const;
        interface::TypeResolutionResult resolveType (context::Main &) const;
    };

    /***
    $
    ***/
    struct Auto {
        interface::DisplayResult        display     ()                const;
        interface::TypeResolutionResult resolveType (context::Main &) const;
    };

    /***
    buffer [a]
    ***/
    // TODO: Maybe allow pattern size here too?
    // Incomplete sem buffer type is declared, so right now it's possible semantically, but not syntactically.
    struct BufferType {
        esl::component<category::Expression> size;

        interface::DisplayResult        display     ()                const;
        interface::TypeResolutionResult resolveType (context::Main &) const;
    };

    /***
    T const
    ***/
    struct ConstType {
        esl::component<category::Type> type;

        interface::DisplayResult        display     ()                const;
        interface::TypeResolutionResult resolveType (context::Main &) const;
    };

    /***
    Out (In)
    ***/
    struct FunctionType {
        esl::component<category::Type> output;
        esl::component<category::Type> input;

        interface::DisplayResult        display     ()                const;
        interface::TypeResolutionResult resolveType (context::Main &) const;
    };

    /***
    T in
    ***/
    struct InType {
        esl::component<category::Type> type;

        interface::DisplayResult        display     ()                const;
        interface::TypeResolutionResult resolveType (context::Main &) const;
    };

    /***
    T out
    ***/
    struct OutType {
        esl::component<category::Type> type;

        interface::DisplayResult        display     ()                const;
        interface::TypeResolutionResult resolveType (context::Main &) const;
    };

    /***
    (T, ...)
    ***/
    struct TupleType {
        // TODO: Non-unary vector?
        esl::component_vector<category::Type> types;

        interface::DisplayResult        display     ()                const;
        interface::TypeResolutionResult resolveType (context::Main &) const;
    };

    /***
    T
    ***/
    struct TypeName {
        // TODO: For some reason, not wrapping strings in a component causes segmentation fault.
        esl::component<std::string> name;

        interface::DisplayResult        display     ()                const;
        interface::TypeResolutionResult resolveType (context::Main &) const;
    };

    /***
    type T
    ***/
    struct TypeDecl {
        node::TypeName name;

        interface::DisplayResult        display     ()                const;
        interface::TypeResolutionResult resolveType (context::Main &) const;
    };

}
