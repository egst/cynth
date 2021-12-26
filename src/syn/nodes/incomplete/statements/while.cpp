#include "syn/nodes/incomplete/statements/while.hpp"
#include "syn/nodes/statements.hpp" // To complete circular dependencies.

#include "esl/category.hpp"
#include "esl/string.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "interface/compound.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::StatementProcessingResult;
    using interface::DisplayResult;

    DisplayResult node::While::display () const {
        return
            "while " + esl::parenthesized(interface::display || target::category{} <<= *condition) +
            " "      + (interface::display || target::category{} <<= *body);
    }

    StatementProcessingResult node::While::processStatement (context::Main & outerScope) const {
        // TODO: Implement comp-time execution.
        // TODO: Some impleentation from if_nodes and some from for_nodes could be extracted and re-used here combined.
        // While is essentialy just an if-like conditional with a for-like loop body (without the range declarations).
        // Meh, the implementation is actually so simple, that I won't bother with this right now.

        return [&] (auto cond) -> StatementProcessingResult {

            // Note: No implicit conversions of the while condition will be implemented in the first version.
            if (!cond.type.template holds_alternative<sem::type::Bool>())
                return esl::result_error{"While condition must be an integer value."};

            auto loopScope = outerScope.makeScopeChild();
            auto bodyResult = interface::processStatement(loopScope) || target::category{} <<= *body;
            if (!bodyResult) return bodyResult.error();

            auto head = c::whileBegin(cond.expression);
            auto end  = c::end();

            /***
            while (<cond>) {
            ***/
            outerScope.insertStatement(head);

            /***
                <body>
            ***/
            outerScope.mergeNestedChild(loopScope);

            /***
            }
            ***/
            outerScope.insertStatement(end);

            return bodyResult;

        } || target::result{} <<=
            interface::translateResolvedValue(outerScope) || target::result{} <<=
            esl::single || target::result{} <<=
            interface::processExpression(outerScope) || target::category{} <<= *condition;
    }

}
