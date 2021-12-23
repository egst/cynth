#include "syn/nodes/incomplete/expressions/expr_for.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include <optional>
#include <utility>

#include "esl/category.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/numeric_types.hpp"
#include "sem/translation.hpp"
#include "syn/nodes/common/for_nodes.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::StatementProcessingResult;
    using sem::ArrayAllocation;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::Integral;
    using sem::NoReturn;
    using sem::ResolvedValue;
    using sem::ReturnedValues;
    using sem::TypedExpression;
    using sem::Variable;

    interface::DisplayResult syn::node::ExprFor::display () const {
        return
            "for " + esl::parenthesized(interface::display || target::category{} <<= *declarations) +
            " "    + (interface::display || target::category{} <<= *body);
    }


    interface::ExpressionProcessingResult syn::node::ExprFor::processExpression (context::Main & outerScope) const {
        return [&] (auto decl) -> ExpressionProcessingResult {
            auto & [size, iterDecls] = decl;

            for_nodes::State state = {.ctx = outerScope};

            for (auto & [decl, array]: iterDecls) {
                auto result = [&, &decl = decl, &array = array] (auto type) {
                    return processArray(state, decl.name, type, array);
                } || target::result{} <<= esl::single(decl.type);
                if (!result) return result.error();
            }

            if (state.comptime()) {
                // All range arrays comp-time:

                // Accumulated result:
                std::optional<CompleteType> type;
                ArrayAllocation result;
                bool runtime = false;

                //resultValues.reserve(size);

                for (sem::Integral i = 0; i < size; ++i) {
                    // Init inner scope:
                    auto loopScope = outerScope.makeScopeChild();

                    // Define iteration elements:
                    for (auto & [name, alloc]: state.allocations) {
                        auto var = Variable{alloc->value[i]};
                        loopScope.lookup.insertValue(name, esl::init<esl::tiny_vector>(std::move(var)));
                    }

                    // Evaluate the loop body:
                    auto bodyResult = interface::processExpression(loopScope) || target::category{} <<= *body;
                    if (!bodyResult) return bodyResult.error();
                    if (!loopScope.empty()) { runtime = true; break; }
                    auto valueResult = [] (auto resolved) {
                        return std::move(resolved).template get<CompleteValue>();
                    } || target::result{} <<= esl::single(*std::move(bodyResult));
                    if (!valueResult) { runtime = true; break; }
                    auto value   = *std::move(valueResult);
                    auto resType = interface::valueType || target::category{} <<= value;

                    using Target = target::nested<target::tiny_vector, target::category>;
                    if (!type)
                        type = resType;
                    else if (!(interface::sameTypes || target::category{} <<= args(*type, resType)))
                        return esl::result_error{"Incompatible return types in a comp-time for expression."};

                    result.value.push_back(std::move(value));
                }

                if (!runtime) {
                    if (result.value.empty() || !type)
                        return esl::result_error{"Returning an empty array from a comp-time for expression."};

                    auto & stored = outerScope.function.storeValue(result);

                    return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{sem::value::Array{
                        .allocation = &stored,
                        .valueType  = sem::type::Array::make(*type, size)
                    }}});
                } // else, continue with the run-time algorithm...
            }

            // At least some range arrays run-time:

            auto loopScope = outerScope.makeScopeChild();
            state.processAllocations();
            for (auto const & [name, var]: std::move(state.variables))
                loopScope.lookup.insertValue(name, esl::init<esl::tiny_vector>(std::move(var)));

            return [&, size = size] (auto expr) -> ExpressionProcessingResult {
                return [&, size = size] (auto type) -> ExpressionProcessingResult {
                    auto head = c::forBegin(
                        c::iterationStructure(state.declarations, state.initializations),
                        c::lt(c::iterationPosition(), c::intLiteral(size)),
                        c::join(",", state.advancements)
                    );
                    for (auto & assgn: state.assignments)
                        assgn += c::brackets(c::iterationPosition());
                    auto assgn   = c::indentedTerminatedJoin(";", state.assignments);
                    auto end     = c::end();
                    auto valName = c::valueName(c::id(outerScope.nextId()));
                    auto alloc   = c::declaration(c::arrayType(size, type), valName);
                    auto result  = c::indented(
                        c::assignment(c::arraySubscript(valName, c::iterationPosition()), expr.expression)
                    );

                    /***
                    cth_arr$16$cth_int val_f;
                    ***/
                    outerScope.function.insertAllocation(alloc);

                    /***
                    for (
                        struct {
                            cth_int pos;
                            <decl1>;
                            <decl2>;
                            ...
                        } iter = {0, <init1>, <init2>, ...};
                        iter.pos < <size>;
                        ++iter.pos,
                        <advancement1>,
                        <advancement2>,
                        ...
                    ) {
                        <assignment1>[iter];
                        <assignment2>[iter];
                    ***/
                    outerScope.insertStatement(head);
                    outerScope.insertStatement(assgn);

                    /***
                        <body>
                    ***/
                    outerScope.mergeNestedChild(loopScope);

                    /***
                        val_f[iter] = <result>;
                    ***/
                    outerScope.insertStatement(result);

                    /***
                    }
                    ***/
                    outerScope.insertStatement(end);

                    /***
                    val_f
                    ***/
                    return esl::init<esl::tiny_vector>(ResolvedValue{TypedExpression{
                        .type       = expr.type,
                        .expression = valName
                    }});

                } || target::result{} <<=
                    interface::translateType || target::category{} <<= expr.type;

            } || target::result{} <<=
                interface::translateResolvedValue(loopScope) || target::result{} <<=
                esl::single || target::result{} <<=
                interface::processExpression(loopScope) || target::category{} <<= *body;

        } || target::result{} <<= for_nodes::resolveRangeDeclarations(outerScope, *declarations);

    }

    interface::StatementProcessingResult syn::node::ExprFor::processStatement (context::Main & ctx) const {
        return for_nodes::processStatement(ctx, *declarations, *body);
    }

}

// Some old code:
// Could be useful for fully comp-time evaluation of for expressions:
#if 0
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
#endif
// Could be useful for fully comp-time evaluation of for statements:
#if 0
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
#endif
