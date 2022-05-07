#include "syn/nodes/incomplete/statements/type_def.hpp"
#include "syn/nodes/statements.hpp" // To complete circular dependencies.

#include "esl/category.hpp"
#include "esl/string.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "sem/compound.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DisplayResult;
    using interface::NameExtractionResult;
    using interface::StatementProcessingResult;
    using interface::TypeNameExtractionResult;
    using sem::NoReturn;

    DisplayResult node::TypeDef::display () const {
        return
            "type " + interface::display(target) +
            " = "   + (interface::display || target::category{} <<= *type);
    }

    StatementProcessingResult node::TypeDef::processStatement (context::Main & ctx) const {
        std::string name = *target.name;

        auto typeResult = interface::resolveType(ctx) || target::category{} <<= *type;
        if (!typeResult) return typeResult.error();
        auto type = *std::move(typeResult);

        ctx.lookup.insertType(name, type);

        return NoReturn{};
    }

    NameExtractionResult node::TypeDef::extractNames (context::Lookup & ctx) const {
        return interface::extractNames(ctx) || target::category{} <<= *type;
    }

    TypeNameExtractionResult node::TypeDef::extractTypeNames (context::Lookup & ctx) const {
        auto names = interface::extractTypeNames(ctx) || target::category{} <<= *type;
        ctx.insertType(*target.name, {});
        return names;
    }

}
