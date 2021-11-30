#pragma once

#include <variant>

#include "esl/category.hpp"

#include "ast/nodes/types.hpp"

namespace cynth::ast::category {

    namespace detail::type {

        using Variant = std::variant<
            node::ArrayType,
            node::Auto,
            node::BufferType,
            node::ConstType,
            node::FunctionType,
            node::InType,
            node::OutType,
            node::TupleType,
            node::TypeDecl,
            node::TypeName
        >;

    }

    struct Type: esl::category<Type, detail::type::Variant> {
        using base = esl::category<Type, detail::type::Variant>;
        using base::base;
    };

}
