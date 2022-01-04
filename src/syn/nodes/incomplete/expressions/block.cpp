#include "syn/nodes/incomplete/expressions/block.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include <string>
#include <utility>

#include "esl/category.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/zip.hpp"

#include "context/main.hpp"
#include "context/branching.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/translation.hpp"
#include "syn/categories/statement.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using interface::NameExtractionResult;
    using interface::StatementProcessingResult;
    using interface::TypeNameExtractionResult;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::FunctionDefinition;
    using sem::NoReturn;
    using sem::ResolvedValue;
    using sem::ReturnedValues;
    using sem::Returned;
    using sem::TypedExpression;

    DisplayResult node::Block::display () const {
        using Target = target::nested<target::component_vector, target::category>;
        return statements.empty()
            ? "{}"
            : "{\n" + esl::join(";\n", interface::display || Target{} <<= statements) + "\n}";
    }

    ExpressionProcessingResult node::Block::processExpression (context::Main & ctx) const {
        return process<false>(ctx);
    }

    ExpressionProcessingResult node::Block::processProgram (context::Main & ctx) const {
        return process<true>(ctx);
    }

    namespace {

        // TODO: These helper functions are huge.
        // Can I split them up and place them in some corresponding semantic structures?

        constexpr bool stop = true;  // break
        constexpr bool next = false; // continue

        struct BlockResult {
            esl::tiny_vector<Returned> returned; // Empty => Returning void.
            bool always  = false;
            bool runtime = false;
        };

        esl::result<BlockResult> processBlock (
            context::Main & ctx,
            esl::component_vector<category::Statement> const & statements
        ) {
            auto before = ctx.count();
            BlockResult blockResult = {};

            for (auto const & statement: statements) {
                using Result = esl::result<bool>;

                auto result = [] (NoReturn const &) -> Result {
                    return next;

                } | [&] (sem::Return const & ret) -> Result {

                    if (blockResult.returned.empty())
                        blockResult.returned.reserve(ret.returned.size());
                        // TODO: Resize.
                    else if (blockResult.returned.size() > ret.returned.size())
                        return esl::result_error{"Returning more values than last time."};
                    else if (blockResult.returned.size() < ret.returned.size())
                        return esl::result_error{"Returning less values than last time."};

                    for (auto const & [i, returned]: esl::enumerate(ret.returned)) {
                        auto returnedType = interface::returnedType(returned);
                        bool init = i >= blockResult.returned.size();
                        if (init)
                            blockResult.returned.push_back(Returned{returnedType});

                        auto & entry = blockResult.returned[i];

                        if (!init) {
                            auto lastType = interface::returnedType(entry);
                            // Note: Conversion to comon types upon return will not be supported in the first version.
                            if (!(interface::sameTypes || target::category{} <<= args(lastType, returnedType)))
                                return esl::result_error{"Returning incompatible types."};
                        }

                        [&] (ReturnedValues const & values, ReturnedValues entry) {
                            entry.insert_back(values.begin(), values.end());

                        } | [&] (ReturnedValues const &, auto const &) {
                            // Ignore those.

                        } | [&] (CompleteType const &, auto const &) {
                            blockResult.runtime = true;
                            entry = returnedType;

                        } || target::category{} <<= args(returned, entry);
                    }

                    if (ret.always)
                        blockResult.always = true;

                    return ret.always ? stop : next;

                } || target::optional_result{} <<=
                interface::processStatement(ctx) || target::category{} <<= statement;

                if (!result) return result.error();
                if (*result == stop) break;
            }

            if (ctx.count() != before)
                // If any local statements added, enforce the run-time state.
                blockResult.runtime = true;

            return blockResult;
        };

        struct BlockExpressionResult {
            esl::tiny_vector<ResolvedValue> resolved;
            esl::tiny_vector<std::string>   declarations;
        };

        esl::result<BlockExpressionResult> processBlockExpression (
            context::Global & global,
            std::string const * tupleVar,
            esl::tiny_vector<Returned> const & returned
        ) {
            BlockExpressionResult blockResult;

            for (auto const & [i, entry]: esl::enumerate(returned)) {
                auto name         = c::tupleElementName(i);
                auto tupleElement = tupleVar ? c::tupleElement(*tupleVar, i) : "<result>";
                // TODO: Take care of nullptr tupleVar properly...

                auto result = [&] (ReturnedValues const & values) {
                    return [&] (sem::type::Function const & type) -> esl::result<void> {
                        // Partially run-time function values:
                        if (values.size() == 0) // Implemetation error.
                            return esl::result_error{"Returning no values in a function-typed block return."};
                        return [&] (auto functions) -> esl::result<void> {
                            if (functions.size() == 1) {
                                auto const & fun = functions.front();
                                if (!fun.runtimeClosure()) {
                                    // A single function with no run-time capture:
                                    blockResult.resolved.push_back(CompleteValue{fun});
                                    return {};
                                }

                                // A single function with run-time capture:
                                auto decl = c::declaration(*fun.definition.closureType, name);
                                auto copy = sem::value::Function{fun.definition, tupleElement};
                                blockResult.declarations.push_back(decl);
                                blockResult.resolved.push_back(CompleteValue{copy});
                                return {};
                            }

                            // Multiple functions combined in a run-time switch function:

                            auto & def = global.storeValue<FunctionDefinition>(FunctionDefinition{
                                .implementation = FunctionDefinition::Switch{esl::make_component_vector(functions)},
                                .type           = type,
                                .closureType    = c::closureType(c::id(global.nextId())),
                                .name           = c::functionName(c::id(global.nextId()))
                            });
                            auto newFun = sem::value::Function{def, tupleElement};
                            auto decl = c::declaration(*def.closureType, name);
                            blockResult.declarations.push_back(decl);
                            blockResult.resolved.push_back(CompleteValue{newFun});
                            return {};

                        } || target::result{} <<= esl::unite_results <<=
                            [] (auto value) { return std::move(value).template get<sem::value::Function>(); } ||
                            target::tiny_vector{} <<= std::move(values);

                    } | [&] (auto const &) -> esl::result<void> {
                        // Compile-time value:
                        // This only happens when there is only one possible return value independent from any runtime conditions.
                        if (values.size() > 1) // Implementation error.
                            return esl::result_error{"Returning multiple values in a compile-time block return."};
                        if (values.size() == 0)
                            return {}; // Returning void.
                        auto const & value = values.front();
                        blockResult.resolved.push_back(value);

                        // TODO: What about arrays? (value copy...)
                        // Well, they should be returned as pointers, so I don't think anything special needs to be done.
                        // (They are only copied when returned from a function.)
                        return {};

                    } || target::category{} <<= interface::returnedValuesType <<= values;

                } | [&] (CompleteType const & type) {
                    return [&] (auto transl) -> esl::result<void> {
                        // A run-time value:
                        auto decl = c::declaration(transl, name);
                        blockResult.declarations.push_back(decl);
                        blockResult.resolved.push_back(TypedExpression{
                            .type       = type,
                            .expression = tupleElement
                        });
                        return {};

                    } || target::result{} <<= interface::translateType || target::category{} <<= type;

                } || target::category{} <<= entry;

                if (!result) return result.error();
            }

            return blockResult;
        }

    }

    template <bool Program>
    ExpressionProcessingResult node::Block::process (context::Main & outerScope) const {
        context::Branching branching;
        auto blockScope = outerScope.makeBranchingChild(branching);

        if constexpr (Program) {
            return [&] (auto blockResult) -> ExpressionProcessingResult {
                return [&] (auto blockResult) -> ExpressionProcessingResult {
                    auto init  = c::returnInitFromDeclarations(blockResult.declarations);
                    auto begin = c::blockBegin();
                    auto end   = c::end();
                    auto ret   = c::mainReturn();

                    /***
                    __label__ ret;
                    struct result {
                        <type1> e0;
                        <type2> e1;
                        // ...
                    } result;
                    {
                        <body>
                    }
                    ret:
                    ***/
                    outerScope.insertStatement(init);
                    outerScope.insertStatement(begin);
                    outerScope.mergeChild(blockScope);
                    outerScope.insertStatement(end);
                    outerScope.insertStatement(ret);

                    return blockResult.resolved;
                } || target::result{} <<= processBlockExpression(outerScope.global, nullptr, blockResult.returned);

            } || target::result{} <<= processBlock(blockScope, statements);

            /*** TODO: Initialization output.
            cth_init_output = <result>;
            ***/

            /*** TODO: Main loop.
            int status = 0;
            int stop   = 0;
            int time   = 0;

            while (!stop) {
                // Write:
                <buff>.data[(<buff>.offset + 1) % <size>] = <generator>(time);
                ...

                // Step forward:
                <buff>.pos = (<buff>.pos + 1) % <size>;
                ...

                ++iter;

                sleep(...);
            }

            return status;
            ***/

            return {};

        } else {
            auto tupleVar = c::tupleVariableName(c::id(outerScope.nextId()));

            return [&] (auto blockResult) -> ExpressionProcessingResult {
                if (!blockResult.always)
                    return esl::result_error{"Block expression does not always return."};
                    // Note: This actually includes the case when it never returns.

                // Fully compile-time block expression:
                if (!blockResult.runtime) {
                    esl::tiny_vector<ResolvedValue> result;
                    for (auto const & entry: blockResult.returned) {
                        auto returnedResult = entry.template get<ReturnedValues>();
                        if (!returnedResult) // Implementation error.
                            return esl::result_error{"Unknown value of a compile-time return."};
                        auto const & returned = *returnedResult;
                        if (returned.size() == 0)
                            return {}; // Returning void.
                        if (returned.size() > 1) // Implementation error.
                            return esl::result_error{"More than one compile-time return."};
                        result.push_back(returned.front());
                    }
                    return result;
                }

                // At least partially run-time block expression:

                return [&] (auto blockResult) -> ExpressionProcessingResult {
                    auto head = c::blockExpressionBegin(tupleVar);
                    auto init = c::indented(c::returnInitFromDeclarations(blockResult.declarations));
                    auto ret  = c::indented(c::blockExpressionReturn());
                    auto end  = c::statement(c::blockExpressionEnd());

                    /***
                    __auto_type <tupvar> = ({
                        __label__ ret;
                        struct result {
                            <type1> e0;
                            <type2> e1;
                            // ...
                        } result;
                        <body>
                        ret: result;
                    });
                    ***/
                    outerScope.insertStatement(head);
                    outerScope.insertStatement(init);
                    outerScope.mergeChild(blockScope);
                    outerScope.insertStatement(ret);
                    outerScope.insertStatement(end);

                    return blockResult.resolved;
                } || target::result{} <<= processBlockExpression(outerScope.global, &tupleVar, blockResult.returned);

            } || target::result{} <<= processBlock(blockScope, statements);
        }

    }

    StatementProcessingResult node::Block::processStatement (context::Main & outerScope) const {
        auto blockScope = outerScope.makeScopeChild();

        return [&] (auto blockResult) -> StatementProcessingResult {

            if (blockResult.runtime) {
                // At least partially run-time block statement:

                auto head = c::blockBegin();
                auto end  = c::end();

                /***
                {
                    <body>
                }
                ***/
                outerScope.insertStatement(head);
                outerScope.mergeChild(blockScope);
                outerScope.insertStatement(end);
            }

            return sem::Return{
                .returned = blockResult.returned,
                .always   = blockResult.always
            };

        } || target::result{} <<= processBlock(blockScope, statements);
    }

    NameExtractionResult node::Block::extractNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::extractNames(nestedScope) || target::nested<target::component_vector, target::category>{} <<=
            statements;
    }

    TypeNameExtractionResult node::Block::extractTypeNames (context::Lookup & outerScope) const {
        auto nestedScope = outerScope.makeChild();
        return esl::insert_nested_cat || target::result{} <<=
            esl::unite_results <<=
            interface::extractTypeNames(nestedScope) || target::nested<target::component_vector, target::category>{} <<=
            statements;
    }

}
