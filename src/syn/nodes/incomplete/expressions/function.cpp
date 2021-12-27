#include "syn/nodes/incomplete/expressions/function.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "sem/values.hpp"
#include "sem/compound.hpp"
#include "syn/nodes/common/fun_nodes.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using sem::CompleteValue;
    using sem::ResolvedValue;

    DisplayResult syn::node::Function::display () const {
        return
            (interface::display || target::category{} <<= *output) + " fn " +
            esl::parenthesized(interface::display || target::category{} <<= *input) + " " +
            (interface::display || target::category{} <<= *body);
    }

    ExpressionProcessingResult syn::node::Function::processExpression (context::Main & ctx) const {
        return [&] (auto fun) -> ExpressionProcessingResult {
            return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{fun}});

        } || target::result{} <<= fun_nodes::process(ctx, *output, *input, *body);
    }
