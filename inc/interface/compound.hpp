#pragma once

#include "esl/category.hpp"
#include "esl/functional.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"

#include "sem/compound.hpp"

#include "interface/forward.hpp"
#include "interface/values.hpp"

namespace cynth::interface {

    // Concepts:

    namespace has {

        template <typename T>
        concept processAssignment = type<T> && requires (
            T type, context::C & ctx,
            sem::ResolvedValue  value,
            sem::ResolvedTarget target
        ) {
            { type.processAssignment(ctx, value, target) } -> std::same_as<AssignmentProcessingResult>;
        };

    }

    // Functions:

    inline auto targetType (sem::ResolvedTarget const & target) {
        return esl::lift<esl::target::category>(
            [] (sem::CompleteValue * target) -> ValueTypeResult {
                return esl::lift<esl::target::category>(interface::valueType)(*target);
            },
            [] (sem::TypedTargetExpression const & target) -> ValueTypeResult {
                return target.type;
            }
        )(target);
    }

    constexpr auto processAssignment (context::C & ctx) {
        return [&ctx] (sem::ResolvedValue const & value, sem::ResolvedTarget const & target) {
            auto type = targetType(target);

            return esl::lift<esl::target::category>(
                [&ctx, &value, &target] <has::processAssignment T> (T const & type) -> AssignmentProcessingResult {
                    return type.processAssignment(ctx, value, target);
                },
                [] (auto const &) -> AssignmentProcessingResult {
                    return esl::result_error{"An assignment of this type cannot be translated."};
                }
            )(type);
        };
    }

}
