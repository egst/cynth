#pragma once

#include <utility>

#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"

#include "context/c.hpp"
#include "sem/compound.hpp"
#include "sem/declarations.hpp"
#include "sem/numeric_types.hpp"

namespace cynth::interface {

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
        sem::CompleteDeclaration, // Iteration variable declaration
        sem::ResolvedValue        // value::Array or a C variable name
    >>;

    // TODO: Implement.
    esl::result<std::pair<sem::Integral, RangeVector>> resolveRangeDeclarations (
        context::C &,
        syn::category::RangeDeclaration
    );

    using SingleExpressionProcessingResult = esl::result<sem::ResolvedValue>;

    namespace detail::misc {

        SingleExpressionProcessingResult processStaticSubscript (sem::Integral, sem::ResolvedValue const &);

        SingleExpressionProcessingResult processSubscript (sem::ResolvedValue const &, sem::ResolvedValue const &);

    }

    /***
    a[1]; # compile-time index
    ***/
    constexpr auto processStaticSubscript (sem::Integral index) {
        return [index] (sem::ResolvedValue const & array) {
            return detail::misc::processStaticSubscript(index, array);
        };
    }

    /** Same as processSubscript but with no type checks - index is assumed to be Int. */
    SingleExpressionProcessingResult processVerifiedSubscript (
        context::C & ctx,
        std::string const & index,
        sem::ResolvedValue const & array
    );

    /***
    Int i = 1;
    a[i]; # run-time index
    ***/
    SingleExpressionProcessingResult processSubscript (
        context::C &,
        sem::TypedExpression const & index,
        sem::ResolvedValue   const & array
    );

}
