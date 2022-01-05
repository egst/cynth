#include "syn/nodes/incomplete/expressions/function.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "sem/values.hpp"
#include "sem/compound.hpp"
#include "syn/nodes/common/fun_nodes.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::NameExtractionResult;
    using interface::TypeNameExtractionResult;
    using sem::CompleteValue;
    using sem::ResolvedValue;

    DisplayResult node::Function::display () const {
        return
            (interface::display || target::category{} <<= *output) + " fn " +
            esl::parenthesized(interface::display || target::category{} <<= *input) + " " +
            (interface::display || target::category{} <<= *body);
    }

    ExpressionProcessingResult node::Function::processExpression (context::Main & ctx) const {
        return [&] (auto fun) -> ExpressionProcessingResult {
            return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{fun}});

        } || target::result{} <<= fun_nodes::process(ctx, *output, *input, *body);
    }

    NameExtractionResult node::Function::extractNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        auto o = interface::extractNames(nestedScope) || target::category{} <<= *output;
        auto i = interface::extractNames(nestedScope) || target::category{} <<= *input;
        auto b = interface::extractNames(nestedScope) || target::category{} <<= *body;
        return esl::insert_cat || target::result{} <<= args(o, i, b);
    }

    TypeNameExtractionResult node::Function::extractTypeNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(nestedScope) || target::category{} <<= *input,
            interface::extractTypeNames(nestedScope) || target::category{} <<= *output,
            interface::extractTypeNames(nestedScope) || target::category{} <<= *body
        );
    }

}
