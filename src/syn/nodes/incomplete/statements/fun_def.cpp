#include "syn/nodes/incomplete/statements/fun_def.hpp"
#include "syn/nodes/statements.hpp" // To complete circular dependencies.

#include "esl/category.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/zip.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "sem/compound.hpp"
#include "sem/values.hpp"
#include "syn/nodes/common/fun_nodes.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DisplayResult;
    using interface::NameExtractionResult;
    using interface::StatementProcessingResult;
    using interface::TypeNameExtractionResult;
    using sem::CompleteValue;
    using sem::NoReturn;
    using sem::Variable;

    DisplayResult node::FunDef::display () const {
        return
            (interface::display || target::category{} <<= *output) + " " +
            interface::display(name) + " " +
            esl::parenthesized(interface::display || target::category{} <<= *input) + " " +
            (interface::display || target::category{} <<= *body);
    }

    StatementProcessingResult node::FunDef::processStatement (context::Main & ctx) const {
        return [&] (auto fun) -> StatementProcessingResult {
            ctx.lookup.insertValue(*name.name, esl::init<esl::tiny_vector>(
                Variable{CompleteValue{fun}}
            ));

            return NoReturn{};

        } || target::result{} <<= fun_nodes::process(ctx, *output, *input, *body);
    }

    NameExtractionResult node::FunDef::extractNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        auto names = esl::insert_cat || target::result{} <<= args(
            interface::extractNames(nestedScope) || target::category{} <<= *output,
            interface::extractNames(nestedScope) || target::category{} <<= *input,
            interface::extractNames(nestedScope) || target::category{} <<= *body
        );
        outerScope.insertValue(*name.name, {});
        return names;
    }

    TypeNameExtractionResult node::FunDef::extractTypeNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(nestedScope) || target::category{} <<= *output,
            interface::extractTypeNames(nestedScope) || target::category{} <<= *input,
            interface::extractTypeNames(nestedScope) || target::category{} <<= *body
        );
    }

}
