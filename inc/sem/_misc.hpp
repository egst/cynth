#pragma once

#include <utility>

#include "esl/component.hpp"
#include "esl/functional.hpp"
#include "esl/lift.hpp"
#include "esl/ranges.hpp"
#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/type_manip.hpp"

#include "context/cynth.hpp"
#include "interface/forward.hpp"
#include "interface/values.hpp"
#include "sem/numeric_types.hpp"
#include "sem/values.hpp"

// TODO: Maybe move this somewhere to `interface/`. (It's not only related to the semantic structures.)
namespace cynth::sem {

    /***
    for (
        Int i in [1, 2],                    # 0
        (Int i, Int j) in [(1, 2), (3, 4)], # 1
        (Int i, Int j) in ([1, 2], [3, 4]), # 2
        ((Int, Int) i, Int j)   in ([(1, 2), (3, 4)], [5, 6]), #3
        ((Int i, Int j), Int k) in ([(1, 2), (3, 4)], [5, 6]), #4
        (Int i, Int j, Int k)   in ([(1, 2), (3, 4)], [5, 6])  #5
    )
    # 0: This simplest case is implemented currently.
    # "Zip" iteration can be represented with a list of such range declarations.
    # 1: Arrays of tuples will not be implemented in the first version, so this case is not considered.
    # 2: This won't be implemented in the first version, but it could replace the need for multiple range
    # declarations (e.g. `for (decl, decl, ...)`) as it also represents the zip functionality.
    # (So in future versions, there will be a backwards-incompatible change of removing this.)
    # 3: This shows how zip iteration over arrays of tuples can be represented.
    # 4: Even the tuples inside of arrays can be "unpacked".
    # 5: Tuples are always flat, so this is actually semantically equivalent to #4
    ***/
    // This only considers a list of #0 range declarations from the example above.
    using RangeVector = esl::tiny_vector<std::pair<
        CompleteDeclaration, // Iteration variable declaration
        ResolvedValue        // value::Array or a C variable name
    >>;

    esl::result<std::pair<Integral, RangeVector>> resolveRangeDeclarations (
        context::C &,
        syn::category::RangeDeclaration
    );

    interface::ExpressionProcessingResult processStaticSubscript (ResolvedValue const & array, Integral subscript);

#if 0 // TODO
    using ArrayVector = value::Array::Vector;
    using ArrayType   = esl::tiny_vector<CompleteType>;

    esl::result<std::pair<ArrayVector, ArrayType>> arrayElems (
        context::Cynth &,
        esl::component_vector<syn::category::ArrayElement> const & // TODO: or maybe tiny_component_vector?
    );

    namespace detail::misc {

        constexpr auto ArrayElemShallowTypeCheck = esl::overload(
            [] (type::In const &) -> esl::result<void> {
                return esl::result_error{"Arrays cannot contain input values."};
            },
            [] (type::Out const &) -> esl::result<void> {
                return esl::result_error{"Arrays cannot contain output values."};
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

    constexpr auto copy (context::Cynth & ctx) {
        return esl::overload(
            [&ctx] (value::Array const & a) -> esl::result<CompleteValue> {
                auto stored = ctx.storeValue(*a.value);
                if (!stored)
                    return stored.error();
                auto typeCopy = a.type;
                return value::Array::make(stored.get(), std::move(typeCopy), a.size);
            },
            [] <interface::value T> (T && v) -> esl::result<CompleteValue>
            requires (!esl::same_but_cvref<T, value::Array>) {
                return CompleteValue{std::forward<T>(v)};
            }
        );
    };

    namespace detail::misc {

        std::vector<std::string> declNames (CompleteDeclaration const & decl);

    }

    constexpr auto declarationNames = esl::overload(
        [] (CompleteDeclaration const & declaration) -> std::vector<std::string> {
            return detail::misc::declNames(declaration);
        },
        [] (esl::range_of<CompleteDeclaration> auto const & declarations) -> std::vector<std::string> {
            std::vector<std::string> result;
            for (auto & decl: declarations) for (auto names: detail::misc::declNames(decl))
                result.push_back(std::move(names));
            return result;
        }
    );

    context::Cynth functionCapture (
        esl::component_vector<CompleteDeclaration> const & parameters,
        esl::component<syn::category::Expression>  const & body
    );
#endif

}
