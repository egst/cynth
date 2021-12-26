#include "syn/nodes/incomplete/statements/for.hpp"
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

    DisplayResult node::If::display () const {
        return
            "if "   + esl::parenthesized(interface::display || target::category{} <<= *condition) +
            " "     + (interface::display || target::category{} <<= *positiveBranch) +
            "else " + (interface::display || target::category{} <<= *positiveBranch);
    }

    StatementProcessingResult node::If::processStatement (context::Main & ctx) const {
        return if_nodes::processStatement(ctx, *condition, *positiveBranch, *negativeBranch);
    }

}
