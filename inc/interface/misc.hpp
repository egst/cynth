#pragma once

#include <utility>

#include "esl/result.hpp"
#include "esl/tiny_vector.hpp"

#include "context/main.hpp"
#include "sem/compound.hpp"
#include "sem/declarations.hpp"
#include "sem/numeric_types.hpp"

namespace cynth::interface {

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
        context::Main & ctx,
        std::string const & index,
        sem::ResolvedValue const & array
    );

    /***
    Int i = 1;
    a[i]; # run-time index
    ***/
    SingleExpressionProcessingResult processSubscript (
        context::Main &,
        sem::TypedExpression const & index,
        sem::ResolvedValue   const & array
    );

}
