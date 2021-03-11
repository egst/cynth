#pragma once

#include "ast/node_interface.hpp"
#include "ast/node_component.hpp"
#include "ast/category_interface.hpp"
#include "util.hpp"

#include <string>
#include <variant>

namespace cynth::ast {

    namespace detail {

        template <typename F>
        consteval auto generalize (F f) {
            return util::overload {
                [f] <ast::node::interface     Node> (Node                       const & node) -> std::string { return f(node);                        },
                [f] <ast::category::interface Cat>  (Cat                        const & cat)  -> std::string { return std::visit(f, cat.node);        },
                [f] <ast::node::interface     Node> (ast::node::component<Node> const & comp) -> std::string { return f(comp.get());                  },
                [f] <ast::category::interface Cat>  (ast::node::component<Cat>  const & comp) -> std::string { return std::visit(f, comp.get().node); }
                // There's no overload for optional_component. Use .has_value() and .get() manually.
            };
        }

        constexpr auto display  = [] <ast::node::interface Node> (Node const & node) -> std::string { return node.display();  };
        //constexpr auto evaluate = [] <ast::node::interface Node> (Node const & node) -> std::string { return node.evaluate(); };
        //constexpr auto execute  = [] <ast::node::interface Node> (Node const & node) -> std::string { return node.execute();  };

    }

    constexpr auto display  = detail::generalize(detail::display);
    //constexpr auto evaluate = detail::generalize(detail::evaluate);
    //constexpr auto execute  = detail::generalize(detail::execute );

}
