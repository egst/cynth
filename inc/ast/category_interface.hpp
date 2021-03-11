#pragma once

#include "ast/node_interface.hpp"

namespace cynth::ast::category {

    namespace detail {

        constexpr auto node_visitor = [] <node::interface Node> (Node const &) -> void {};

        template <typename Var>
        concept node_variant = requires (Var var) {
            std::visit(node_visitor, var);
        };

    }

    template <typename Cat>
    concept interface = requires (Cat cat) {
        { cat.node } -> detail::node_variant;
    };

}
