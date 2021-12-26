#include "syn/nodes/incomplete/statements/for.hpp"
#include "syn/nodes/statements.hpp" // To complete circular dependencies.

#include "esl/category.hpp"
#include "esl/string.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "syn/nodes/common/for_nodes.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;

    using interface::StatementProcessingResult;
    using interface::DisplayResult;

    DisplayResult node::For::display () const {
        return
            "for " + esl::parenthesized(interface::display || target::category{} <<= *declarations) +
            " "    + (interface::display || target::category{} <<= *body);
    }

    StatementProcessingResult node::For::processStatement (context::Main & ctx) const {
        return for_nodes::processStatement(ctx, *declarations, *body);
    }

}
