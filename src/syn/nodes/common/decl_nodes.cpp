#include "syn/nodes/common/decl_nodes.hpp"

#include "esl/category.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/zip.hpp"

#include "interface/types.hpp"
#include "sem/compound.hpp"

namespace cynth::syn::decl_nodes {

    using namespace esl::sugar;
    namespace target = esl::target;
    using sem::Variable;

    esl::result<void> define (
        context::Main & ctx,
        esl::tiny_vector<sem::CompleteDeclaration> const & decls,
        esl::tiny_vector<sem::ResolvedValue>       const & values
    ) {
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

            for (auto const & [type, value]: esl::zip(decl.type, esl::view(valueIterator, valueIterator + count))) {
                auto definitionResult = interface::processDefinition(ctx)(value) || target::category{} <<= type;
                if (!definitionResult) return definitionResult.error();

                vars.push_back(*definitionResult);
            }

            ctx.lookup.insertValue(decl.name, std::move(vars));
            valueIterator += count;
        }

        if (valueIterator != values.end())
            return esl::result_error{"More targets than values in a definition."};

        return {};
    }

}
