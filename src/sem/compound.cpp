#include "sem/compound.hpp"

#include <string>
#include <variant>

#include "esl/lift.hpp"

#include "context/c.hpp"
#include "sem/translation.hpp"
#include "sem/values.hpp"
#include "interface/values.hpp"

namespace cynth::sem {

    using esl::lift;
    namespace target = esl::target;

    esl::result<void> TypedResolvedTarget::assign (context::C & ctx, ResolvedValue const & value) {

        return lift<target::variant>(
            [] (CompleteValue * target, CompleteValue const & value) -> esl::result<void> {
                if (!target) return esl::result_error{"Missing target."};
                *target = value;
                return {};
            },
            [&ctx] (CompleteValue * target, std::string const & value) -> esl::result<void> {
                if (!target) return esl::result_error{"Missing target."};
                auto translatoinResult = lift<target::category>(interface::translateTarget(ctx))(*target);
                if (!translatoinResult) return translatoinResult.error();
                return {};
            },
            [&ctx] (std::string const & target, CompleteValue const & value) -> esl::result<void> {
                auto translatoinResult = lift<target::category>(interface::translateValue(ctx))(value);
                if (!translatoinResult) return translatoinResult.error();
                return ctx.insertStatement(c::assignment(*translatoinResult, target));
            },
            [&ctx] (std::string const & target, std::string const & value) -> esl::result<void> {
                return ctx.insertStatement(c::assignment(value, target));
            }
        )(target, value.value);
    }

}
