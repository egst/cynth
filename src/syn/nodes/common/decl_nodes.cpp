#include "syn/nodes/common/decl_nodes.hpp"

#include "esl/category.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/zip.hpp"

#include "interface/types.hpp"
#include "sem/compound.hpp"

// TMP
#include "debug.hpp"
#include "interface/common.hpp"

namespace cynth::syn::decl_nodes {

    using namespace esl::sugar;
    namespace target = esl::target;
    using sem::Variable;
    using sem::TypedName;

    esl::result<void> define (
        context::Main & ctx,
        esl::tiny_vector<sem::CompleteDeclaration> const & decls,
        esl::tiny_vector<sem::ResolvedValue>       const & values,
        bool params
    ) {
        if (params && decls.empty() && values.empty())
            return {};
        if (params && decls.empty() && !values.empty())
            return esl::result_error{"Arguments provided for a function without parameters."};
        if (params && !decls.empty() && values.empty())
            return esl::result_error{"No arguments provided for a function with parameters."};
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
            if (static_cast<std::ptrdiff_t>(count) > values.end() - valueIterator)
                return esl::result_error{"More values than targets in a definition."};

            for (auto const & [type, value]: esl::zip(decl.type, esl::view(valueIterator, valueIterator + count))) {
                auto definitionResult = interface::processDefinition(ctx)(value) || target::category{} <<= type;
                if (!definitionResult) return definitionResult.error();

                vars.push_back(*definitionResult);
            }

            auto result = ctx.lookup.insertValue(decl.name, std::move(vars));
            if (!result) return result.error();
            valueIterator += count;
        }

        if (valueIterator != values.end())
            return esl::result_error{"More targets than values in a definition."};

        return {};
    }

    esl::result<void> declare (
        context::Main & ctx,
        esl::tiny_vector<sem::CompleteDeclaration> const & decls,
        bool parameters
    ) {
        for (auto const & decl: decls) {
            auto result = [&] (auto vars) -> esl::result<void> {
                auto lookupResult = ctx.lookup.insertValue(std::move(decl).name, std::move(std::move(vars)));
                if (!lookupResult)
                    return lookupResult.error();
                return {};

            } || target::result{} <<= esl::unite_results <<= [&, parameters] (auto const & type) -> esl::result<Variable> {
                if (parameters) {
                    return [&] (auto translType) -> esl::result<Variable> {
                        auto name = c::variableName(c::id(ctx.nextId()));
                        auto decl = c::declaration(std::move(translType), name);
                        ctx.function.insertParameter(decl);
                        return Variable{TypedName{type, name}};

                    } || target::result{} <<= interface::translateType(type);
                }
                return interface::processDeclaration(ctx)(type);

            } || target::nested<target::component_vector_tiny_result, target::category>{} <<=
                decl.type;
            if (!result) return result.error();
        }

        return {};
    }

}
