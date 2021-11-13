#pragma once

#include "config.hpp"
#include "sem/context.hpp"
#include "sem/translation_context.hpp"
#include "sem/declarations.hpp"
#include "sem/values.hpp"
#include "sem/targets.hpp"
#include "ast/nodes/expressions.hpp"
#include "ast/categories/range_decl.hpp"
#include "ast/interface.hpp"

namespace cynth::sem {

    using range_vector = tuple_vector<std::pair <
        tuple_vector<complete_decl>,
        value::Array
    >>;

    result<std::pair<integral, range_vector>> for_decls (
        context &,
        ast::category::RangeDecl
    );

    using array_vector = value::Array::vector;
    using array_type   = tuple_vector<type::complete>;

    result<std::pair<array_vector, array_type>> array_elems (
        context &,
        component_vector<ast::category::ArrayElem> const &
    );

    namespace detail {

        constexpr auto array_elem_shallow_type_check = util::overload {
            [] (type::In const &) -> result<void> {
                return result_error{"Arrays of input values are not supported yet."};
            },
            [] (type::Out const &) -> result<void> {
                return result_error{"Arrays of output values are not supported yet."};
            },
            [] (type::Array const &) -> result<void> {
                return result_error{"Nested (multidimensional) arrays are not supported yet."};
            },
            [] (type::Buffer const &) -> result<void> {
                return result_error{"Arrays of buffers are not supported yet."};
            },
            [] (type::Function const &) -> result<void> {
                return result_error{"Arrays of functions are not supported yet."};
            },
            [] (type::String const &) -> result<void> {
                return result_error{"Arrays of strings are not supported yet."};
            },
            [] (type::Bool const &) -> result<void> {
                return {};
            },
            [] (type::Int const &) -> result<void> {
                return {};
            },
            [] (type::Float const &) -> result<void> {
                return {};
            }
        };

    };

    constexpr auto array_elem_type_check = lift::any{util::overload {
        detail::array_elem_shallow_type_check,
        [] (type::Const const & type) -> result<void> {
            return lift::category_component{util::overload {
                detail::array_elem_shallow_type_check,
                [] (type::Const const &) -> result<void> {
                    return result_error{"Nested const array value type. (TODO: This case shouldn't happen.)"};
                }
            }} (type.type);
        }
    }};

    constexpr auto copy = [] (context & ctx) {
        return lift::any{util::overload {
            [&ctx] (value::Array const & a) -> result<value::complete> {
                auto stored = ctx.store_value(*a.value);
                if (!stored)
                    return stored.error();
                auto type_copy = a.type;
                return value::make_array(stored.get(), std::move(type_copy), a.size);
            },
            [] <interface::value T> (T && v) -> result<value::complete>
            requires (!util::same_as_no_cvref<T, value::Array>) {
                return value::complete{std::forward<T>(v)};
            }
        }};
    };

    namespace detail {

        std::vector<std::string> decl_names (complete_decl const & decl);

    }

    constexpr auto declaration_names = util::overload {
        [] (complete_decl const & declaration) -> std::vector<std::string> {
            return detail::decl_names(declaration);
        },
        [] (util::range_of<complete_decl> auto const & declarations) -> std::vector<std::string> {
            std::vector<std::string> result;
            for (auto & decl : declarations) for (auto names : detail::decl_names(decl))
                result.push_back(std::move(names));
            return result;
        }
    };

    context function_capture (
        component_vector <complete_decl>             const & parameters,
        component        <ast::category::Expression> const & body
    );

}
