#pragma once

#include "ast/node_component.hpp"
#include "ast/node_interface.hpp"
#include "ast/category_interface.hpp"
#include "util/general.hpp"
#include "util/config.hpp"

#include <optional>
#include <type_traits>
#include <concepts>
#include <utility>

namespace cynth::util {

    /** Lift a callable to operate on containers and other composite values. */
    template <typename F>
    struct lift {
        F const function;

        constexpr lift (F function): function{function} {}

        /** Operate on any sized range. Returns a new vector. */
        template <util::sized_range T>
        auto operator () (T const & target) const {
            util::vector<decltype(function(*target.begin()))> result;
            //result.reserve(target.size());
            std::transform(target.begin(), target.end(), std::back_inserter(result), function);
            return result;
        }

        /** Operate on any variant. */
        template <typename... Ts>
        auto operator () (util::variant<Ts...> const & target) const {
            return std::visit(function, target);
        }

        /** Operate on a node. */
        template <ast::node::interface T>
        auto operator () (T const & target) const {
            return function(target);
        }

        /** Operate on a category. */
        template <ast::category::interface T>
        auto operator () (T const & target) const {
            return operator()(target.node);
        }

        /** Operate on a component. */
        template <typename T>
        auto operator () (ast::node::component<T> const & target) const {
            return operator()(target.get());
        }

        /** Operate on an optional component. Returns an optional. */
        template <typename T>
        auto operator () (ast::node::optional_component<T> const & target) const {
            using Result = decltype(operator()(target.get()));
            if (target.has_value())
                return std::optional<Result>{operator()(target.get())};
            else
                return std::optional<Result>{};
        }

        /** Operate on a component vector. Returns a new vector. */
        template <typename T>
        auto operator () (ast::node::component_vector<T> const & target) const {
            util::vector<decltype(operator()(*target.begin()))> result;
            result.reserve(target.size());
            std::transform(target.begin(), target.end(), std::back_inserter(result), *this);
            return result;
        }
    };

}
