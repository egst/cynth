#include "syn/nodes/incomplete/statements/assignment.hpp"
#include "syn/nodes/statements.hpp" // To complete circular dependencies.

#include "esl/category.hpp"
#include "esl/string.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "interface/compound.hpp"
#include "sem/compound.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::StatementProcessingResult;
    using interface::DisplayResult;

    DisplayResult node::Assignment::display () const {
        return
            (interface::display || target::category{} <<= *target) + " = " +
            (interface::display || target::category{} <<= *value);
    }

    StatementProcessingResult node::Assignment::processStatement (context::Main & ctx) const {
        return [&] (auto targets, auto values) -> StatementProcessingResult {
            if (targets.empty())
                return esl::result_error{"No targets in an assignment."};
            if (values.empty())
                return esl::result_error{"No values in an assignment."};
            if (values.size() > targets.size())
                return esl::result_error{"More values than targets in an assignment."};
            if (targets.size() > values.size())
                return esl::result_error{"More targets than values in an assignment."};

            for (auto const & [target, value]: esl::zip(targets, values)) {
                auto result = interface::processAssignment(ctx)(value, target);
                if (!result) return result.error();
            }

            return {sem::NoReturn{}};

        } || target::result{} <<= args(
            interface::resolveTarget(ctx)     || target::category{} <<= *target,
            interface::processExpression(ctx) || target::category{} <<= *value
        );
    }

}
