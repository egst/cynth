#include "interface/misc.hpp"

#include "esl/lift.hpp"
#include "esl/result.hpp"

#include "sem/values.hpp"
#include "sem/types.hpp"
#include "sem/compound.hpp"
#include "sem/numeric_types.hpp"

namespace cynth::interface {

    namespace target = esl::target;
    namespace type   = sem::type;
    namespace value  = sem::value;

    using esl::lift;
    using sem::ArrayAllocation;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::Integral;
    using sem::ResolvedValue;
    using sem::TypedExpression;

    namespace {

        /***
        Int const [3] const a = [1, 2, 3];
        a[1]; # compile-time array
        ***/
        constexpr auto comptimeSubscript =
            [] (Integral index, CompleteType const & type, ArrayAllocation const & alloc)
            -> SingleExpressionProcessingResult {
                // TODO: type probably not needed.
                return ResolvedValue{
                    alloc.value[index]
                };
            };

        /***
        Int [3] a = [1, 2, 3];
        a[1]; # run-time array
        ***/
        constexpr auto runtimeSubscript =
            [] (Integral index, CompleteType const & type, std::string const & expr) {
                return ResolvedValue{TypedExpression{
                    .type       = type,
                    .expression = c::arraySubscript(expr, std::to_string(index))
                }};
            };

        /***
        1[2];
        ***/
        constexpr auto nonArraySubscript =
            [] (auto const &) -> SingleExpressionProcessingResult {
                return esl::result_error{"Subscript can only be performed on an array."};
            };

    }

    // TODO: No array value type conversions are assumed here.
    // TODO: Constness?
    SingleExpressionProcessingResult detail::misc::processStaticSubscript (
        Integral index,
        ResolvedValue const & array
    ) {
        return lift<target::category>(
            [index] (CompleteValue const & value) -> SingleExpressionProcessingResult {
                return lift<target::category>(
                    [index] (value::Array const & value) -> SingleExpressionProcessingResult {

                        auto type = value.valueType;
                        if (index >= type.size)
                            return esl::result_error{"Subscript index out of bounds."};

                        return lift<target::variant>(
                            [index, &type] (ArrayAllocation * alloc) -> SingleExpressionProcessingResult {
                                return comptimeSubscript(index, *type.type, *alloc);
                            },
                            [index, &type] (std::string const & alloc) -> SingleExpressionProcessingResult {
                                return runtimeSubscript(index, *type.type, alloc); // Subscript directly from the allocation variable.
                            }
                        )(value.allocation);

                    },
                    nonArraySubscript
                )(value);
            },
            [index] (TypedExpression const & value) {
                return lift<target::category>(
                    [index, &value] (type::Array const & type) -> SingleExpressionProcessingResult {

                        if (index >= type.size)
                            return esl::result_error{"Subscript index out of bounds."};
                        return runtimeSubscript(index, *type.type, value.expression);

                    },
                    nonArraySubscript
                )(value.type);
            }
        )(array);
    }

}
