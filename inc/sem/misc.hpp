#pragma once

#include <utility>

#include "esl/type_manip.hpp"
#include "esl/ranges.hpp"
#include "esl/functional.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/component.hpp"

#include "sem/numeric_types.hpp"
#include "sem/forward.hpp"
#include "sem/context.hpp"

namespace cynth::sem {

    using RangeVector = esl::tiny_vector<std::pair<
        esl::tiny_vector<CompleteDeclaration>,
        value::Array
    >>;

    esl::result<std::pair<Integral, RangeVector>> for_decls (
        Context &,
        ast::category::RangeDeclaration
    );

    using ArrayVector = value::Array::Vector;
    using ArrayType   = esl::tiny_vector<CompleteType>;

    esl::result<std::pair<ArrayVector, ArrayType>> arrayElems (
        Context &,
        esl::component_vector<ast::category::ArrayElement> const & // TODO: or maybe tiny_component_vector?
    );

    namespace detail::misc {

        constexpr auto ArrayElemShallowTypeCheck = esl::overload(
            [] (type::In const &) -> esl::result<void> {
                return esl::result_error{"Arrays of input values are not supported yet."};
            },
            [] (type::Out const &) -> esl::result<void> {
                return esl::result_error{"Arrays of output values are not supported yet."};
            },
            [] (type::Array const &) -> esl::result<void> {
                return esl::result_error{"Nested (multidimensional) arrays are not supported yet."};
            },
            [] (type::Buffer const &) -> esl::result<void> {
                return esl::result_error{"Arrays of buffers are not supported yet."};
            },
            [] (type::Function const &) -> esl::result<void> {
                return esl::result_error{"Arrays of functions are not supported yet."};
            },
            [] (type::String const &) -> esl::result<void> {
                return esl::result_error{"Arrays of strings are not supported yet."};
            },
            [] (type::Bool const &) -> esl::result<void> {
                return {};
            },
            [] (type::Int const &) -> esl::result<void> {
                return {};
            },
            [] (type::Float const &) -> esl::result<void> {
                return {};
            }
        );

    };

    constexpr auto arrayElemTypeCheck = esl::overload(
        detail::misc::ArrayElemShallowTypeCheck,
        [] (type::Const const & type) -> esl::result<void> {
            return esl::lift<esl::target::component, esl::target::category>(
                detail::misc::ArrayElemShallowTypeCheck,
                [] (type::Const const &) -> esl::result<void> {
                    return esl::result_error{"Nested const array value type. (TODO: This case shouldn't happen.)"};
                }
            )(type.type);
        }
    );

    constexpr auto copy (Context & ctx) {
        return esl::overload(
            [&ctx] (value::Array const & a) -> esl::result<value::complete> {
                auto stored = ctx.store_value(*a.value);
                if (!stored)
                    return stored.error();
                auto typeCopy = a.type;
                return value::make_array(stored.get(), std::move(typeCopy), a.size);
            },
            [] <interface::value T> (T && v) -> esl::result<value::complete>
            requires (!esl::same_but_cvref<T, value::Array>) {
                return value::complete{std::forward<T>(v)};
            }
        );
    };

    namespace detail::misc {

        std::vector<std::string> declNames (CompleteDeclaration const & decl);

    }

    constexpr auto declarationNames = esl::overload(
        [] (CompleteDeclaration const & declaration) -> std::vector<std::string> {
            return detail::misc::decl_names(declaration);
        },
        [] (esl::range_of<CompleteDeclaration> auto const & declarations) -> std::vector<std::string> {
            std::vector<std::string> esl::result;
            for (auto & decl : declarations) for (auto names : detail::misc::decl_names(decl))
                esl::result.push_back(std::move(names));
            return esl::result;
        }
    );

    Context functionCapture (
        esl::component_vector<CompleteDeclaration> const & parameters,
        esl::component<ast::category::Expression>  const & body
    );

}
