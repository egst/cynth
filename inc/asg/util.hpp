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

    namespace detail {

        constexpr auto array_elem_shallow_type_check = util::overload {
            [] (asg::type::In const &) -> result<void> {
                return result_error{"Arrays of input values are not supported yet."};
            },
            [] (asg::type::Out const &) -> result<void> {
                return result_error{"Arrays of output values are not supported yet."};
            },
            [] (asg::type::Array const &) -> result<void> {
                return result_error{"Nested (multidimensional) arrays are not supported yet."};
            },
            [] (asg::type::Buffer const &) -> result<void> {
                return result_error{"Arrays of buffers are not supported yet."};
            },
            [] (asg::type::Function const &) -> result<void> {
                return result_error{"Arrays of functions are not supported yet."};
            },
            [] (asg::type::String const &) -> result<void> {
                return result_error{"Arrays of strings are not supported yet."};
            },
            [] (asg::type::Bool const &) -> result<void> {
                return {};
            },
            [] (asg::type::Int const &) -> result<void> {
                return {};
            },
            [] (asg::type::Float const &) -> result<void> {
                return {};
            }
        };

    };

    constexpr auto array_elem_type_check = lift::any{util::overload {
        detail::array_elem_shallow_type_check,
        [] (asg::type::Const const & type) -> result<void> {
            return lift::category_component{util::overload {
                detail::array_elem_shallow_type_check,
                [] (asg::type::Const const &) -> result<void> {
                    return result_error{"Nested const array value type. (TODO: This case shouldn't happen.)"};
                }
            }} (type.type);
        }
    }};

    constexpr auto copy = [] (context & ctx) {
        return lift::any{util::overload {
            [&ctx] (asg::value::Array const & a) -> result<asg::value::complete> {
                auto stored = ctx.store_value(*a.value);
                if (!stored)
                    return stored.error();
                auto type_copy = a.type;
                return value::make_array(stored.get(), std::move(type_copy), a.size);
            },
            [] <asg::interface::value T> (T && v) -> result<asg::value::complete>
            requires (!util::same_as_no_cvref<T, asg::value::Array>) {
                return asg::value::complete{std::forward<T>(v)};
            }
        }};
    };

}
