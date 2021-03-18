#pragma once

#include "ast/node_interface.hpp"
#include "ast/node_component.hpp"
#include "ast/category_interface.hpp"
#include "util/lift.hpp"

#include <string>
#include <array>
#include <vector>
#include <variant>

namespace cynth::ast {

    // The generic AST functions operate on:
    // * nodes:                 nodes define the core functionality themselves in their corresponding methods.
    // * categories:            applying the function as a visitor.
    // * components:            applying the function to the get() method result.
    // * optional components:   returning an std::optional.
    // * vectors of components: mapping the function (std::transform) and returning a new std::vector.

    // This header only includes the necessary headers for the generic interface.
    // To actually use these functions on nodes and categories or components thereof, the appropriate headers must be also included manually.
    // E.g. to be able to call ast::display on an expression category, both 'ast/interface.hpp' and 'ast/categories/expression.hpp' must be included.
    // For simpler use, the 'ast.hpp' header provides all nodes and categories.

    constexpr auto display = util::lift{[] <ast::node::interface Node> (Node const & node) -> std::string { return node.display(); }};
    //constexpr auto evaluate;
    //constexpr auto execute;

}
