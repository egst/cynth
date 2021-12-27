#include "syn/nodes/incomplete/statements/fun_def.hpp"
#include "syn/nodes/statements.hpp" // To complete circular dependencies.

#include <utility>

#include "esl/category.hpp"
#include "esl/string.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"
#include "esl/zip.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "sem/compound.hpp"

// TMP
#include "esl/debug.hpp"
#include "esl/macros.hpp"

namespace cynth::syn {

    using namespace esl::sugar;
    namespace target = esl::target;
    using interface::DisplayResult;
    using interface::StatementProcessingResult;
    using sem::CaptureVector;
    using sem::Closure;
    using sem::CompleteDeclaration;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::FunctionDefinition;
    using sem::Integral;
    using sem::NoReturn;
    using sem::ResolvedCapture;
    using sem::TypedName;
    using sem::Variable;

    DisplayResult node::FunDef::display () const {
        return
            (interface::display || target::category{} <<= *output) + " " +
            interface::display(name) + " " +
            esl::parenthesized(interface::display || target::category{} <<= *input) + " " +
            (interface::display || target::category{} <<= *body);
    }

    // TODO: This should probably be moved to syn/nodes/common/fun_nodes
    // so that it can be used in the anonymous function definition expression as well.
    namespace {

        FunctionDefinition::Parameter resolveParam (CompleteDeclaration const & decl) {
            return {.name = decl.name, .arity = static_cast<Integral>(decl.type.size())};
        }

        esl::tiny_vector<CompleteType> declType (CompleteDeclaration const & decl) {
            return decl.type;
        }

        std::string runtimeCapture (
            context::Main            & ctx,
            std::vector<std::string> & declarations,
            std::vector<std::string> & assignments,
            std::string const        & closureName,
            std::string const        & type,
            std::string const        & variable
        ) {
            auto captureName = c::variableName(c::id(ctx.nextId()));
            auto decl        = c::declaration(type, captureName);
            auto assgn       = c::statement(closureName + c::designatedInitialization(captureName, variable));
            declarations.push_back(decl);
            assignments.push_back(assgn);
            return captureName;
        }

        struct CaptureResult {
            Closure closure;
            std::optional<std::string> closureType;
            std::optional<std::string> closureVariable;
        };

        esl::result<CaptureResult> capture (
            context::Main & ctx,
            std::vector<std::string> const & names,
            std::vector<std::string> const & typeNames
        ) {
            CaptureResult            result;
            std::vector<std::string> declarations; // <type> <name>
            std::vector<std::string> assignments;  // <closure>.<name> = <var>;

            auto closureName = c::closureVariableName(c::id(ctx.nextId()));

            for (auto const & name: names) {
                auto const & type = ctx.lookup.findType(name);
                result.closure.types.emplace(std::make_pair(name, type));
            }

            for (auto const & name: names) {
                CaptureVector<ResolvedCapture> capturedTuple;

                auto const & tupleVar = ctx.lookup.findValue(name);

                for (auto const & var: tupleVar) {
                    auto captureResult = [&] (CompleteValue const & varVal) {
                        return [&] (sem::value::Function fun) -> esl::result<void> {
                            // Capturing a function (a partially run-time value):
                            if (!fun.closureVariable) {
                                // Fully comp-time closure:
                                capturedTuple.emplace_back(varVal);
                                return {};
                            }
                            if (!fun.definition.closureType) // Implementation error.
                                return esl::result_error{"No closure type in a captured function with a closure variable."};
                            // Run-time closure:
                            auto capturedMember = runtimeCapture(
                                ctx, declarations, assignments, closureName,
                                *fun.definition.closureType, *fun.closureVariable
                            );
                            auto copy = sem::value::Function{
                                .definition      = fun.definition,
                                .closureVariable = capturedMember
                            };
                            capturedTuple.emplace_back(CompleteValue{copy});

                        } | [&] (auto value) -> esl::result<void> {
                            // Capturing a comp-time value:
                            capturedTuple.emplace_back(varVal);
                            return {};

                        } || target::category{} <<= varVal;

                    } | [&] (TypedName const & varName) {
                        // Capturing a run-time variable:
                        return [&] (auto const & type) -> esl::result<void> {
                            auto capturedMember = runtimeCapture(
                                ctx, declarations, assignments,
                                closureName, type, varName.name
                            );
                            capturedTuple.emplace_back(TypedName{
                                .type = varName.type,
                                .name = capturedMember
                            });
                        } || target::result{} <<=
                            interface::translateType || target::category{} <<= varName.type;

                    } || target::category{} <<= var;
                    if (!captureResult) return captureResult.error();
                }

                result.closure.values.emplace(std::make_pair(name, capturedTuple));
            }

            if (!declarations.empty() || !assignments.empty()) {
                // Closure type definition:
                result.closureType = c::closureVariableType(c::id(ctx.nextId()));
                auto closureStruct = c::structureDefinition(*result.closureType, declarations);
                /***
                struct <closure> {
                    <declaration1>;
                    ...
                };
                ***/
                ctx.global.insertType(closureStruct);

                // Closure variable initialization:
                for (auto const & assgn: assignments)
                    ctx.insertStatement(assgn);
            }

            return result;
        }

    }

    StatementProcessingResult node::FunDef::processStatement (context::Main & ctx) const {
        return [&] (
            auto outTypes, auto inDecls,
            auto names, auto typeNames
        ) {

            return [&] (auto captured) -> StatementProcessingResult {
                auto const & [closure, closureType, closureVariable] = captured;

                auto inParams = resolveParam || target::tiny_vector{} <<= inDecls;
                auto inTypes  = declType     || target::nested_tiny_vector_cat{} <<= inDecls;

                auto functionName = c::functionName(c::id(ctx.nextId()));
                auto & def = ctx.global.storeValue(FunctionDefinition{
                    .implementation = FunctionDefinition::Implementation{
                        .parameters = inParams,
                        .body       = body,
                        .closure    = closure
                    },
                    .type = sem::type::Function{
                        .in  = esl::make_component_vector(inTypes),
                        .out = esl::make_component_vector(outTypes)
                    },
                    .closureType = closureType, // If capturing some run-time values.
                    .name        = functionName
                });
                auto fun = sem::value::Function{
                    .definition      = def,
                    .closureVariable = closureVariable
                };
                ctx.lookup.insertValue(*name.name, esl::init<esl::tiny_vector>(
                    Variable{CompleteValue{fun}}
                ));

                return NoReturn{};

            } || target::result{} <<= capture(ctx, names, typeNames);

        } || target::result{} <<= args(
            interface::resolveType(ctx)        || target::category{} <<= *output,
            interface::resolveDeclaration(ctx) || target::category{} <<= *input,
            interface::extractNames            || target::category{} <<= *body,
            interface::extractTypeNames        || target::category{} <<= *body
        );

#if 0
        auto translated = value.translateValue();

        auto varResult = ctx.comptime().insertValue(*name.name, {/* TODO */});
        if (!varResult) return varResult.error();

        /*
        auto stored = ctx.comptime().storeValue(sem::value::FunctionValue {
            .out_type   = make_component_vector(output),
            .parameters = make_component_vector(input),
            .body       = body,
            .capture    = ctx // TODO
        });
        if (!stored)
            return make_execution_result(stored.error());

        auto value = esl::init<tuple_vector>(sem::value::complete{sem::value::Function {
            .value = stored.get()
        }});
        */

        // TODO
        /*
        auto define_result = ctx.define_value(*name->name, value);
        if (!define_result)
            return make_execution_result(define_result.error());
        */
#endif
    }

}
