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

#include "config.hpp"
#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/translation.hpp"
#include "syn/nodes/common/for_nodes.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::NameExtractionResult;
    using interface::StatementProcessingResult;
    using interface::TypeNameExtractionResult;
    using sem::ArrayAllocation;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::NoReturn;
    using sem::ResolvedValue;
    using sem::ReturnedValues;
    using sem::TypedExpression;
    using sem::Variable;

    DisplayResult node::ExprFor::display () const {
        return
            "for " + esl::parenthesized(interface::display || target::category{} <<= *declarations) +
            " "    + (interface::display || target::category{} <<= *body);
    }


    ExpressionProcessingResult node::ExprFor::processExpression (context::Main & outerScope) const {
        auto helperScope = outerScope.makeScopeChild();
        return [&] (auto decl) -> ExpressionProcessingResult {
            auto & [size, iterDecls] = decl;

            // TODO: Add a State constructor that takes care of this.
            for_nodes::State state = {
                .ctx             = helperScope,
                .initializations = {c::integralLiteral(0)},
                .advancements    = {c::increment(c::iterationPosition())},
            };

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

                for (Integral i = 0; i < size; ++i) {
                    // Init inner scope:
                    auto loopScope = helperScope.makeScopeChild();

                    // Define iteration elements:
                    for (auto & [name, alloc]: state.allocations) {
                        auto var = Variable{alloc->value[i]};
                        auto result = loopScope.lookup.insertValue(name, esl::init<esl::tiny_vector>(std::move(var)));
                        if (!result) return result.error();
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

                    if (!type)
                        type = resType;
                    else if (!(interface::sameTypes || target::category{} <<= args(*type, resType)))
                        return esl::result_error{"Incompatible return types in a comp-time for expression."};

                    result.value.push_back(std::move(value));
                }

                if (!runtime) {
                    if (result.value.empty() || !type) // Implementation error?
                        return esl::result_error{"Returning an empty array from a comp-time for expression."};

                    auto & stored = outerScope.function.storeValue(result);

                    return esl::init<esl::tiny_vector>(ResolvedValue{CompleteValue{sem::value::Array{
                        .allocation = &stored,
                        .valueType  = sem::type::Array{*type, size}
                    }}});
                } // else, continue with the run-time algorithm...
            }

            // At least some range arrays run-time:
            auto loopScope = helperScope.makeScopeChild();
            state.processAllocations();
            for (auto const & [name, var]: std::move(state.variables)) {
                auto result = loopScope.lookup.insertValue(name, esl::init<esl::tiny_vector>(std::move(var)));
                if (!result) return result.error();
            }

            return [&, size = size] (auto expr) -> ExpressionProcessingResult {
                return [&, size = size] (auto type) -> ExpressionProcessingResult {
                    auto head = c::forBegin(
                        c::iterationStructure(state.declarations, state.initializations),
                        c::lt(c::iterationPosition(), c::integralLiteral(size)),
                        c::join(",", state.advancements)
                    );
                    for (auto & assgn: state.assignments)
                        assgn += c::brackets(c::iterationPosition());
                    auto assgn   = c::indented(c::terminatedJoin(";", state.assignments));
                    auto end     = c::end();
                    auto valName = c::valueName(c::id(outerScope.nextId()));
                    auto alloc   = c::statement(c::definition(c::arrayType(size, type), valName, c::zeroInitialization()));
                    auto result  = c::indented(
                        c::statement(c::assignment(expr.expression, c::arraySubscript(valName, c::iterationPosition())))
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
                    helperScope.mergeChild(loopScope);
                    outerScope.mergeChild(helperScope);

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
                        .type       = sem::type::Array{expr.type, size},
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

    StatementProcessingResult node::ExprFor::processStatement (context::Main & ctx) const {
        return for_nodes::processStatement(ctx, *declarations, *body);
    }

    NameExtractionResult node::ExprFor::extractNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        auto d = interface::extractNames(nestedScope) || target::category{} <<= *declarations;
        auto b = interface::extractNames(nestedScope) || target::category{} <<= *body;
        return esl::insert_cat || target::result{} <<= args(d, b);
    }

    TypeNameExtractionResult node::ExprFor::extractTypeNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        auto d = interface::extractTypeNames(nestedScope) || target::category{} <<= *declarations;
        auto b = interface::extractTypeNames(nestedScope) || target::category{} <<= *body;
        return esl::insert_cat || target::result{} <<= args(d, b);
    }

}
