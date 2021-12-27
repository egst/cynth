#include "syn/nodes/incomplete/expressions/application.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include <variant>
#include <utility>

#include "esl/component.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/result.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/view.hpp"

#include "context/main.hpp"
#include "context/function.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "sem/compound.hpp"
#include "sem/declarations.hpp"
#include "sem/values.hpp"
#include "syn/nodes/common/decl_nodes.hpp"

// TMP
#include "esl/debug.hpp"
#include "esl/macros.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using sem::CompleteDeclaration;
    using sem::CompleteType;
    using sem::CompleteValue;
    using sem::FunctionDefinition;
    using sem::ResolvedCapture;
    using sem::ResolvedValue;
    using sem::TypedExpression;
    using sem::Variable;

    DisplayResult syn::node::Application::display () const {
        return
            (interface::display || target::category{} <<= *function) +
            esl::parenthesized(interface::display || target::category{} <<= *arguments);
    }

    namespace {

        std::string expression (TypedExpression const & expr) {
            return expr.expression;
        }

        esl::result<esl::tiny_vector<CompleteDeclaration>> paramDecls (
            esl::tiny_vector<FunctionDefinition::Parameter> const & parameters,
            esl::tiny_vector<CompleteType>                  const & types
        ) {
            auto typeIter = types.begin();
            esl::tiny_vector<CompleteDeclaration> decls;
            for (auto const & param: parameters) {
                auto count = param.arity;
                if (count > types.end() - typeIter) // Implementation error.
                    return esl::result_error{"More parameters than input types in a function definition."};
                esl::tiny_vector<CompleteType> typeTuple;
                for (auto const & type: esl::view(typeIter, typeIter + count))
                    typeTuple.push_back(type);
                decls.push_back(CompleteDeclaration{
                    esl::make_component_vector(typeTuple),
                    param.name
                });
            }
            return decls;
        }

        ResolvedValue wrapResolved (CompleteValue const & value) {
            return ResolvedValue{value};
        }

        esl::result<Variable> captureVariable (ResolvedCapture const & capture) {
            auto value = capture.get<CompleteValue>();
            if (!value) return value.error();
            return Variable{*value};
        }

        esl::result<Variable> valueVariable (CompleteValue const & value) {
            return Variable{value};
        }

        /** Empty result => can't evaluate at compile-time. */
        using ComptimeResult = esl::optional_result<esl::tiny_vector<ResolvedValue>>;

        ComptimeResult comptimeApplication (
            context::Main                            & ctx,
            sem::type::Function                const & type,
            FunctionDefinition::Implementation const & implementation,
            esl::tiny_vector<CompleteValue>    const & arguments
        ) {
            context::Function funCtx;
            auto funScope = ctx.makeFunctionChild(funCtx);

            for (auto const & [name, capture]: implementation.closure->values) {
                auto varsResult = esl::unite_results <<= captureVariable || target::tiny_vector{} <<= capture;
                if (!varsResult) return varsResult.error();
                funScope.lookup.insertValue(name, *std::move(varsResult));
            }
            for (auto const & [name, type]: implementation.closure->types) {
                funScope.lookup.insertType(name, {type});
            }

            return [&] (auto paramDecls) -> ComptimeResult {
                auto defResult =
                    decl_nodes::define(funScope, paramDecls, wrapResolved || target::tiny_vector{} <<= arguments);
                if (!defResult) return defResult.error();
                if (!funScope.empty()) return {}; // Run-time params.

                return [&] (auto tuple) -> ComptimeResult {
                    if (!funScope.empty()) return {}; // Run-time body.
                    esl::tiny_vector<ResolvedValue> result;
                    for (auto const & resolved: tuple) {
                        if (!resolved.template holds_alternative<CompleteValue>())
                            return {}; // Run-time return value.
                        result.push_back(resolved);
                    }
                    return result; // Successfully evaluated at compile-time.

                } || target::result{} <<= interface::processExpression(funScope) || target::category{} <<= *implementation.body;

            } || target::result{} <<= paramDecls(implementation.parameters, type.in);
        }

    }

    ExpressionProcessingResult syn::node::Application::processExpression (context::Main & ctx) const {
        return [&] (auto f, auto args) -> ExpressionProcessingResult {
            auto valResult = std::move(f).template get<CompleteValue>();
            if (!valResult) return valResult.error();
            auto funResult = valResult->template get<sem::value::Function>();
            if (!funResult) return funResult.error();
            auto & fun = *funResult;

            if (!fun.closureVariable) {
                // No run-time capture:
                auto implResult = std::get_if<FunctionDefinition::Implementation>(&fun.definition.implementation);
                if (implResult) {
                    // Not a run-time "switch" function:
                    esl::tiny_vector<CompleteValue> compargs;
                    [&] (CompleteValue const & value) {
                        compargs.push_back(value);
                    } | [] (TypedExpression const &) {
                        // skip
                    } || target::nested<target::tiny_vector, target::category>{} <<= args;
                    if (compargs.size() == args.size()) {
                        // Comp-time arguments only:
                        auto evalResult = comptimeApplication(ctx, fun.valueType, *implResult, compargs);
                        if (evalResult.has_error()) return evalResult.error();
                        if (evalResult.has_value()) return evalResult.value();
                        // Otherwise, continue to the run-time translation...
                    }
                }
            }

            // Run-time capture or some arguments run-time:
            return [&] (auto args) -> ExpressionProcessingResult {
                auto name = ctx.global.define(fun.definition);
                auto call = fun.closureVariable
                    ? c::call(name, *fun.closureVariable, args)
                    : c::call(name, args);
                auto resultName = c::tupleVariableName(c::id(ctx.nextId()));
                auto resultDef  = c::definition(c::autoType(), resultName, call);

                /***
                __auto_type <result> = <fun>(<closure>, <arg1>, <arg2>, ...);
                ***/
                ctx.insertStatement(resultDef);

                std::size_t i = 0;
                return [&] (auto const & type) {
                    auto expr = c::tupleElement(resultName, i);
                    ++i;
                    return ResolvedValue{TypedExpression{.type = type, .expression = expr}};

                } || target::component_vector_tiny_result{} <<= fun.valueType.out;

            } || target::result{} <<=
                expression || target::nested<target::result, target::tiny_vector>{} <<=
                esl::unite_results <<= interface::translateResolvedValue(ctx) || target::tiny_vector{} <<= args;

            return {};

        } || target::result{} <<= args(
            esl::single || target::result{} <<=
                interface::processExpression(ctx) || target::category{} <<= *function,
            interface::processExpression(ctx) || target::category{} <<= *arguments
        );
    }

}
