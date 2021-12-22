#include "syn/nodes/incomplete/expressions/expr_for.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

// TODO: Cleanup when done.

#include <string>

#include "esl/category.hpp"
#include "esl/type_manip.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/zip.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/numeric_types.hpp"
#include "sem/translation.hpp"
#include "syn/categories/expression.hpp"

// TODO:
// Surely there must be a way to generalize the algohithms used here.
// I guess I won't be able to get rid of all the branches,
// not without too much runtime polymorphism and repeated
// "packing" and "unpacking" of abstractions and indirections.
// But I'll try to generalize the main ideas in some generic helper functions
// and just delegate to those in the different braeches.

namespace cynth::syn {

    // TODO: Cleanup when done.

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::StatementProcessingResult;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::FunctionDefinition;
    using sem::Integral;
    using sem::NoReturn;
    using sem::ResolvedValue;
    using sem::Returned;
    using sem::ReturnedValues;
    using sem::TypedExpression;

    interface::DisplayResult syn::node::ExprFor::display () const {
        return
            "for " + esl::parenthesized(interface::display || target::category{} <<= *declarations) +
            " "    + (interface::display || target::category{} <<= *body);
    }

    interface::ExpressionProcessingResult syn::node::ExprFor::processExpression (context::Main & ctx) const {
        return {}; // TODO

        /*
        auto decls_result = sem::for_decls(ctx, *declarations);
        if (!decls_result)
            return syn::make_evaluation_result(decls_result.error());
        auto [size, iter_decls] = *std::move(decls_result);

        sem::array_vector              result_values;
        std::optional<sem::array_type> result_type;

        result_values.reserve(size);

        for (integral i = 0; i < size; ++i) {
            // Init inner scope:
            auto iter_scope = make_child_context(ctx);

            // Define iteration elements:
            for (auto & [decl, value]: iter_decls)
                iter_scope.define_value(decl, value.value->value[i]);

            // Evaluate the loop body:
            auto value_result = esl::unite_results(syn::evaluate(iter_scope)(body));
            if (!value_result)
                return syn::make_evaluation_result(value_result.error());

            auto & value = *value_result;
            auto   type  = sem::value_type(value);

            if (result_type) {
                auto common_results = sem::common(type, *result_type);
                if (!common_results)
                    return syn::make_evaluation_result(common_results.error());
                result_type = result_to_optional(esl::unite_results(*common_results));
            } else {
                result_type = std::optional{std::move(type)};
            }

            result_values.push_back(std::move(value));
        }

        if (!result_type)
            return syn::make_evaluation_result(result_error{"No common type for an array in a for expression."});

        auto stored = ctx.store_value(sem::value::ArrayValue {
            .value = result_values
        });
        if (!stored)
            return syn::make_evaluation_result(stored.error());

        auto result = sem::value::make_array (
            stored.get(),
            *std::move(result_type),
            static_cast<integral>(stored->value.size())
        );
        if (!result)
            return syn::make_evaluation_result(result.error());
        return syn::make_evaluation_result(*result);
        */
    }

    interface::StatementProcessingResult syn::node::ExprFor::processStatement (context::Main & ctx) const {
        return {}; // TODO

        /*
        auto decls_result = sem::for_decls(ctx, *declarations);
        if (!decls_result)
            return syn::make_execution_result(decls_result.error());
        auto [size, iter_decls] = *std::move(decls_result);

        for (integral i = 0; i < size; ++i) {
            // Init inner scope:
            auto iter_scope = make_child_context(ctx);

            // Define iteration elements:
            for (auto & [decl, value]: iter_decls)
                iter_scope.define_value(decl, value.value->value[i]);

            // Execute the loop body:
            auto returned = syn::execute(iter_scope)(body);

            if (returned)
                return *returned;
            if (returned.has_error())
                return syn::make_execution_result(returned.error());
        }

        */
    }

}
