#include "syn/nodes/incomplete/expressions/application.hpp"
#include "syn/nodes/expressions.hpp" // To complete circular dependencies.

#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"

#include "context/main.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/nodes.hpp"
#include "sem/compound.hpp"
#include "sem/values.hpp"

// TMP
#include "esl/debug.hpp"
#include "esl/macros.hpp"

namespace cynth::syn {

    namespace target = esl::target;
    using namespace esl::sugar;
    using interface::DisplayResult;
    using interface::ExpressionProcessingResult;
    using sem::CompleteValue;
    using sem::TypedExpression;
    using sem::ResolvedValue;

    DisplayResult syn::node::Application::display () const {
        return
            (interface::display || target::category{} <<= *function) +
            esl::parenthesized(interface::display || target::category{} <<= *arguments);
    }

    namespace {

        std::string expression (TypedExpression const & expr) {
            return expr.expression;
        }

    }

    ExpressionProcessingResult syn::node::Application::processExpression (context::Main & ctx) const {
        return [&] (auto f, auto args) -> ExpressionProcessingResult {
            auto valResult = std::move(f).template get<CompleteValue>();
            if (!valResult) return valResult.error();
            auto funResult = valResult->template get<sem::value::Function>();
            if (!funResult) return funResult.error();
            auto & fun = *funResult;

            esl::tiny_vector<CompleteValue> compargs;

            [&] (CompleteValue const & value) {
                compargs.push_back(value);
            } | [] (TypedExpression const &) {
                // skip
            } || target::nested<target::tiny_vector, target::category>{} <<= args;

            if (compargs.size() == args.size()) {
                // Comp-time arguments only:

                // TODO
            }

            // At least tome arguments run-time:
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
