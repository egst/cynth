#include "syn/nodes/incomplete/statements/when.hpp"
#include "syn/nodes/statements.hpp" // To complete circular dependencies.

#include "esl/category.hpp"
#include "esl/string.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "syn/nodes/common/if_nodes.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DisplayResult;
    using interface::NameExtractionResult;
    using interface::StatementProcessingResult;
    using interface::TypeNameExtractionResult;

    DisplayResult node::When::display () const {
        return
            "when " + esl::parenthesized(interface::display || target::category{} <<= *condition) +
            " "     + (interface::display || target::category{} <<= *branch);
    }

    StatementProcessingResult node::When::processStatement (context::Main & ctx) const {
        return if_nodes::processStatement(ctx, *condition, *branch);
    }

    NameExtractionResult node::When::extractNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(nestedScope) || target::category{} <<= *condition,
            interface::extractNames(nestedScope) || target::category{} <<= *branch
        );
    }

    TypeNameExtractionResult node::When::extractTypeNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(nestedScope) || target::category{} <<= *condition,
            interface::extractTypeNames(nestedScope) || target::category{} <<= *branch
        );
    }

}
