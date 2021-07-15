#pragma once

#include "config.hpp"
#include "context.hpp"
#include "asg/declarations.hpp"
#include "asg/values.hpp"
#include "ast/nodes/expressions.hpp"
#include "ast/categories/range_decl.hpp"
#include "ast/interface.hpp"

namespace cynth::asg {

    result<void> define (
        context &,
        tuple_vector<asg::complete_decl> const &, tuple_vector<asg::value::complete> const &
    );

    result<void> declare (
        context &,
        tuple_vector<asg::complete_decl> const &
    );

    namespace detail {

        template <typename T>
        result<tuple_vector<std::string>> eval_name_node (T const &) {
            return result_error{"A name or a tuple of names expected."};
        }

        //template <>
        result<tuple_vector<std::string>> eval_name_node (ast::node::Name  const & node);
        //template <>
        result<tuple_vector<std::string>> eval_name_node (ast::node::Tuple const & node);

    }

    // TODO: ast::interface::any only guarantees presence of the .display() method, which is useless here.
    constexpr auto eval_name = [] <ast::interface::any Node> (Node && node) {
        return detail::eval_name_node/*<Node>*/(std::forward<Node>(node));
    };

    using range_vector = tuple_vector<std::pair <
        tuple_vector<asg::complete_decl>,
        asg::value::Array
    >>;

    result<std::pair<integral, range_vector>> for_decls (context &, ast::category::RangeDecl);

    using array_vector = asg::value::Array::vector;
    using array_type   = tuple_vector<asg::type::complete>;

    result<std::pair<array_vector, array_type>> array_elems (
        context &,
        component_vector<ast::category::ArrayElem> const &
    );

}
