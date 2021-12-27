#include "syn/nodes/incomplete/expressions/subscript.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include "esl/lift.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/nodes.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;

    DisplayResult node::Subscript::display () const {
    }

    ExpressionProcessingResult node::Subscript::processExpression (context::Main & ctx) const {
    }

}
