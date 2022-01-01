#include "syn/nodes/incomplete/statements/definition.hpp"
#include "syn/nodes/statements.hpp" // To complete circular dependencies.

#include "esl/category.hpp"
#include "esl/string.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "interface/compound.hpp"
#include "sem/compound.hpp"
#include "syn/nodes/common/decl_nodes.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DisplayResult;
    using interface::NameExtractionResult;
    using interface::StatementProcessingResult;
    using interface::TypeNameExtractionResult;
    using sem::NoReturn;

    DisplayResult node::Definition::display () const {
        return
            (interface::display || target::category{} <<= *target) + " = " +
            (interface::display || target::category{} <<= *value);
    }

    StatementProcessingResult node::Definition::processStatement (context::Main & ctx) const {
        return [&] (auto decls, auto values) -> StatementProcessingResult {
            auto result = decl_nodes::define(ctx, decls, values);
            if (!result) return result.error();
            return NoReturn{};

        } || target::result{} <<= args(
            interface::resolveDeclaration(ctx) || target::category{} <<= *target,
            interface::processExpression(ctx)  || target::category{} <<= *value
        );
    }

    NameExtractionResult node::Definition::extractNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractNames(ctx) || target::category{} <<= *value,
            interface::extractNames(ctx) || target::category{} <<= *target
        );
    }

    TypeNameExtractionResult node::Definition::extractTypeNames (context::Lookup & ctx) const {
        return esl::insert_cat || target::result{} <<= args(
            interface::extractTypeNames(ctx) || target::category{} <<= *value,
            interface::extractTypeNames(ctx) || target::category{} <<= *target
        );
    }

}
