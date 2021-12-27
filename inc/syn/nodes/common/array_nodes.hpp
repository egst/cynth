#pragma once

#include <optional>
#include <string>

#include "esl/result.hpp"
#include "esl/component.hpp"
#include "esl/tiny_vector.hpp"

#include "context/main.hpp"
#include "sem/compound.hpp"
#include "sem/numeric_types.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"
#include "syn/categories/array_element.hpp"

namespace cynth::syn::array_nodes {

    struct ElementsResult {
        sem::Integral                        arraySize;
        esl::tiny_vector<sem::CompleteValue> compValues;
        esl::tiny_vector<sem::ResolvedValue> values;
        std::optional<sem::type::Array>      arrayType; // Empty value => no elements.

        // Note: Empty list of array elements doesn't form a legal array, but it is legal in a subscript:
        // a = b[] -- copy the whole array
        // a[] = b -- assign new values to the whole array
        // o[] = x -- assign a value to an out type

        inline bool comptime () const {
            return compValues.size() == arraySize;
        }
    };

    esl::result<ElementsResult> processElements (
        context::Main &,
        esl::component_vector<category::ArrayElement> const &
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

    /** Same as processSubscriptExpression but with no type checks - index is assumed to be Int. */
    SingleExpressionProcessingResult processVerifiedSubscriptExpression (
        context::Main & ctx,
        std::string const & index,
        sem::ResolvedValue const & array
    );

    /***
    Int i = 1;
    a[i]; # run-time index
    ***/
    SingleExpressionProcessingResult processSubscriptExpression (
        context::Main &,
        sem::TypedExpression const & index,
        sem::ResolvedValue   const & array
    );

    SingleExpressionProcessingResult processSubscript (
        context::Main &,
        sem::ResolvedValue const & index,
        sem::ResolvedValue const & array
    );

    std::string arrayAllocation (
        context::Main &,
        std::string const & type,
        sem::Integral       size
    );

    void individualArrayInitialization (
        context::Main &,
        std::string                   const & allocation,
        esl::tiny_vector<std::string> const & elements
    );

    void bulkArrayInitialization (
        context::Main &,
        std::string const & allocation,
        std::string const & source
    );

}
