#include "syn/nodes/incomplete/statements/for.hpp"
#include "syn/nodes/statements.hpp" // To complete circular dependencies.

#include "esl/category.hpp"
#include "esl/string.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "syn/nodes/common/for_nodes.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::StatementProcessingResult;
    using interface::DisplayResult;
    using interface::NameExtractionResult;
    using interface::TypeNameExtractionResult;

    DisplayResult node::For::display () const {
        return
            "for " + esl::parenthesized(interface::display || target::category{} <<= *declarations) +
            " "    + (interface::display || target::category{} <<= *body);
    }

    StatementProcessingResult node::For::processStatement (context::Main & ctx) const {
        return for_nodes::processStatement(ctx, *declarations, *body);
    }

    NameExtractionResult node::For::extractNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        auto d = interface::extractNames(nestedScope) || target::category{} <<= *declarations;
        auto b = interface::extractNames(nestedScope) || target::category{} <<= *body;
        return esl::insert_cat || target::result{} <<= args(d, b);
    }

    TypeNameExtractionResult node::For::extractTypeNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        auto d = interface::extractTypeNames(nestedScope) || target::category{} <<= *declarations;
        auto b = interface::extractTypeNames(nestedScope) || target::category{} <<= *body;
        return esl::insert_cat || target::result{} <<= args(d, b);
    }
}
