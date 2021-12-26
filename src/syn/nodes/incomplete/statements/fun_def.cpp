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
    using sem::CapturedContext;
    using sem::CompleteDeclaration;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::FunctionDefinition;
    using sem::Integral;
    using sem::NoReturn;
    using sem::ResolvedCapture;
    using sem::Closure;
    using sem::TypedName;

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

        struct CaptureResult {
            Closure closure;
            std::string closuteType;
        };

        esl::result<ResolvedCapturedContext> capture (
            context::Main & ctx,
            std::vector<std::string> const & names,
            std::vector<std::string> const & typeNames
        ) {
            ResolvedCapturedContext result;

            for (auto const & name: names) {
                auto const & type = ctx.lookup.findType(name);
                result.types.emplace(std::make_pair(name, type));
            }

            auto ctxTypeName = c::contextVariableType(c::id(ctx.nextId())); // cth_ctx_<id>
            std::vector<std::string> declarations;                          // <type> <name>;
            std::vector<std::string> assignments;                           // <ctxVarName>.<name> = <varName>

            for (auto const & name: names) {
                CaptureVector<ResolvedCapture> tuple;

                auto const & tupleVar = ctx.lookup.findValue(name);

                for (auto const & var: tupleVar) {
                    auto captureResult = [&] (CompleteValue const & varVal) -> esl::result<void> {
                        tuple.emplace_back(varVal);
                        return {};

                    } | [&] (TypedName const & varName) {

                        return [&] (auto const & type) -> esl::result<void> {

                            auto ctxVarName = c::contextVariableName(c::id(ctx.nextId()));
                            auto captureName = varName.name; // Could be anything else though, this choice as arbitrary.
                            auto decl  = c::declaration(type, captureName);
                            auto assgn = ctxVarName + c::contextVariableInitialization(captureName, varName.name);
                            declarations.push_back(decl);
                            assignments.push_back(assgn);
                            tuple.emplace_back(name);

                        } || target::result{} <<=
                        interface::translateType || target::category{} <<= varName.type;

                        /***
                        cth_ctx_<ctxTypeName>
                        ---
                        <type> <name>;
                        ---
                        <ctxVarName>.<name> = <varName>
                        ***/

                    } || target::category{} <<= var;
                    if (!captureResult) return captureResult.error();
                }

                result.values.emplace(std::make_pair(name, tuple));
            }

            return result;
        }

    }

    StatementProcessingResult node::FunDef::processStatement (context::Main & ctx) const {
        return [&] (
            auto outTypes, auto inDecls,
            auto names, auto typeNames
        ) -> StatementProcessingResult {

            auto capture = ctx.lookup.capture(names, typeNames);

            auto resolvedCapture = resolveCapturedContext(ctx, capture);

            auto & def = ctx.global.storeValue(FunctionDefinition{
                .implementation = FunctionDefinition::Implementation{
                    .parameters = resolveParam || target::tiny_vector{} <<= inDecls,
                    .body       = body,
                    .context    = {}
                },
                .type           = {},
                .contextType    = {}, // If capturing some run-time values.
                .name           = {}
            });

            sem::value::Function value = {
                .definition = def
                /*
                .context      = std::move(capture), // TODO
                .outType      = esl::make_component_vector(outTypes),
                .parameters   = esl::make_component_vector(inDecls),
                .body         = body,
                .functionName = {},
                .captureName  = {},
                */
            };

            // TODO...
            return {sem::NoReturn{}};

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
