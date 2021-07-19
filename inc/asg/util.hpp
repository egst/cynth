#pragma once

#include "config.hpp"
#include "context.hpp"
#include "asg/declarations.hpp"
#include "asg/values.hpp"
#include "asg/targets.hpp"
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
