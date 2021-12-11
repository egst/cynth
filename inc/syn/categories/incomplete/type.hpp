#pragma once

#include <variant>

#include "esl/category.hpp"

// Circular dependencies:
#include "syn/nodes/incomplete/types.hpp"

namespace cynth::syn::category {

    namespace detail::type {

        using Variant = std::variant<
            node::ArrayType,
            node::Auto,
            node::BufferType,
            node::ConstType,
            node::FunctionType,
            node::InType,
            node::OutType,
            node::TupleType, // TODO: Or TypeTuple?
            node::TypeDecl,
            node::TypeName
        >;

    }

    struct Type: esl::category<Type, detail::type::Variant> {
        using base = esl::category<Type, detail::type::Variant>;
        using base::base;
    };

}
