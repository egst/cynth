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

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::StatementProcessingResult;
    using interface::DisplayResult;

    DisplayResult node::Definition::display () const {
        return
            (interface::display || target::category{} <<= *target) + " = " +
            (interface::display || target::category{} <<= *value);
    }

    StatementProcessingResult node::Definition::processStatement (context::Main & ctx) const {
        return [&] (auto decls, auto values) -> StatementProcessingResult {
            if (decls.empty())
                return esl::result_error{"No declarations in a definition."};
            if (values.empty())
                return esl::result_error{"No values in a definition."};
            auto valueIterator = values.begin();
            for (auto const & decl: decls) {
                if (decl.type.empty())
                    return esl::result_error{"No types in a declaration."};
                esl::tiny_vector<sem::Variable> vars;
                auto count = decl.type.size();
                if (count > values.end() - valueIterator)
                    return esl::result_error{"More values than targets in a definition."};

                for (auto const & [type, value]: zip(decl.type, esl::view(valueIterator, valueIterator + count))) {
                    auto definitionResult = interface::processDefinition(ctx)(value) || target::category{} <<= type;
                    if (!definitionResult) return definitionResult.error();

                    vars.push_back(*definitionResult);
                }

                auto varResult = ctx.lookup.insertValue(decl.name, std::move(vars));
                if (!varResult) return varResult.error();
                valueIterator += count;
            }

            if (valueIterator != values.end())
                return esl::result_error{"More targets than values in a definition."};

            return {sem::NoReturn{}};

        } || target::result{} <<= args(
            interface::resolveDeclaration(ctx) || target::category{} <<= *target,
            interface::processExpression(ctx)  || target::category{} <<= *value
        );
    }

}
