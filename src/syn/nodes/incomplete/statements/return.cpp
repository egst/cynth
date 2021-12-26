#include "syn/nodes/incomplete/statements/return.hpp"
#include "syn/nodes/statements.hpp" // To complete circular dependencies.

#include "esl/category.hpp"
#include "esl/string.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "syn/nodes/common/if_nodes.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::StatementProcessingResult;
    using interface::DisplayResult;

    interface::DisplayResult node::Return::display () const {
        return "return " + (interface::display || target::category{} <<= *value);
    }

    interface::StatementProcessingResult node::Return::processStatement (context::Main & ctx) const {
        return {}; // TODO

#if 0 // Old code
        auto value_result = esl::unite_results(evaluate(ctx)(value));
        if (!value_result)
            return make_execution_result(value_result.error());
        auto value = *std::move(value_result);

        return value;
#endif
    }

}
