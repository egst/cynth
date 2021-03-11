#pragma once

#include <string>
#include <variant>
#include <concepts>

namespace cynth::ast::node {

    template <typename Node>
    concept interface = requires (Node node) {
        { node.display() } -> std::same_as<std::string>;
        //{ node.evaluate() } -> std::same_as<...>;
        //{ node.execute()  } -> std::same_as<...>;
    };

}
