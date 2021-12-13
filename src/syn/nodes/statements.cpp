#include "syn/nodes/statements.hpp"

#include <string>
#include <utility>

#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/lift.hpp"
#include "esl/string.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/view.hpp"
#include "esl/zip.hpp"
//#include "esl/containers.hpp" // unite_results, single, init (from old code)

#include "context/c.hpp"
#include "interface/common.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/compound.hpp"
#include "sem/translation.hpp"

// TMP
#include "esl/debug.hpp"
#include "esl/macros.hpp"

namespace esl {

    using cynth::syn::node::Assignment;
    using cynth::syn::node::Definition;
    using cynth::syn::node::For;
    using cynth::syn::node::FunDef;
    using cynth::syn::node::If;
    using cynth::syn::node::Return;
    using cynth::syn::node::If;
    using cynth::syn::node::Return;
    using cynth::syn::node::TypeDef;
    using cynth::syn::node::When;
    using cynth::syn::node::While;

    template <>
    void component_deleter<Assignment>::operator () (Assignment * ptr) const {
        delete ptr;
    }

    template <>
    Assignment * component_allocator<Assignment>::operator () (Assignment const & other) const {
        return new Assignment{other};
    }

    template <>
    Assignment * component_allocator<Assignment>::operator () (Assignment && other) const {
        return new Assignment{std::move(other)};
    }

    template <>
    void component_deleter<Definition>::operator () (Definition * ptr) const {
        delete ptr;
    }

    template <>
    Definition * component_allocator<Definition>::operator () (Definition const & other) const {
        return new Definition{other};
    }

    template <>
    Definition * component_allocator<Definition>::operator () (Definition && other) const {
        return new Definition{std::move(other)};
    }

    template <>
    void component_deleter<For>::operator () (For * ptr) const {
        delete ptr;
    }

    template <>
    For * component_allocator<For>::operator () (For const & other) const {
        return new For{other};
    }

    template <>
    For * component_allocator<For>::operator () (For && other) const {
        return new For{std::move(other)};
    }

    template <>
    void component_deleter<FunDef>::operator () (FunDef * ptr) const {
        delete ptr;
    }

    template <>
    FunDef * component_allocator<FunDef>::operator () (FunDef const & other) const {
        return new FunDef{other};
    }

    template <>
    FunDef * component_allocator<FunDef>::operator () (FunDef && other) const {
        return new FunDef{std::move(other)};
    }

    template <>
    void component_deleter<If>::operator () (If * ptr) const {
        delete ptr;
    }

    template <>
    If * component_allocator<If>::operator () (If const & other) const {
        return new If{other};
    }

    template <>
    If * component_allocator<If>::operator () (If && other) const {
        return new If{std::move(other)};
    }

    template <>
    void component_deleter<Return>::operator () (Return * ptr) const {
        delete ptr;
    }

    template <>
    Return * component_allocator<Return>::operator () (Return const & other) const {
        return new Return{other};
    }

    template <>
    Return * component_allocator<Return>::operator () (Return && other) const {
        return new Return{std::move(other)};
    }

    template <>
    void component_deleter<TypeDef>::operator () (TypeDef * ptr) const {
        delete ptr;
    }

    template <>
    TypeDef * component_allocator<TypeDef>::operator () (TypeDef const & other) const {
        return new TypeDef{other};
    }

    template <>
    TypeDef * component_allocator<TypeDef>::operator () (TypeDef && other) const {
        return new TypeDef{std::move(other)};
    }

    template <>
    void component_deleter<While>::operator () (While * ptr) const {
        delete ptr;
    }

    template <>
    While * component_allocator<While>::operator () (While const & other) const {
        return new While{other};
    }

    template <>
    While * component_allocator<While>::operator () (While && other) const {
        return new While{std::move(other)};
    }

    template <>
    void component_deleter<When>::operator () (When * ptr) const {
        delete ptr;
    }

    template <>
    When * component_allocator<When>::operator () (When const & other) const {
        return new When{other};
    }

    template <>
    When * component_allocator<When>::operator () (When && other) const {
        return new When{std::move(other)};
    }

}

namespace cynth {

    namespace target = esl::target;
    using esl::lift;

    //// Assignment ////

    interface::DisplayResult syn::node::Assignment::display () const {
        return
            lift<target::component, target::category>(interface::display)(target) + " = " +
            lift<target::component, target::category>(interface::display)(value);
    }

    interface::StatementResolutionResult syn::node::Assignment::resolveStatement (context::C & ctx) const {
        auto targetsResult = lift<target::component, target::category>(interface::resolveTarget(ctx))(target);
        if (!targetsResult) return targetsResult.error();
        auto targets = *std::move(targetsResult);

        auto target = std::move(targets.front());

        auto valuesResult = lift<target::component, target::category>(interface::resolveExpression(ctx))(value);
        if (!valuesResult) return valuesResult.error();
        auto values = *std::move(valuesResult);

        // TODO: What about .size() == 0? And elsewhere as well...
        // I guess techincally it shouldn't be a problem semantically and it should also be impossible syntactically,
        // so maybe it's not a problem, but I should check it once I get back to testing again.

        if (values.size() > targets.size())
            return esl::result_error{"More values than targets in an assignment."};
        if (targets.size() > values.size())
            return esl::result_error{"More targets than values in an assignment."};

        for (auto const & [target, value]: esl::zip(targets, values)) {
            auto conversionResult = lift<target::category>(interface::translateConversion(ctx, value))(target.type);
            if (!conversionResult) return conversionResult.error();
            auto converted = *std::move(conversionResult);

            return lift<target::variant>(
                [] (sem::CompleteValue * target, sem::CompleteValue const & value) -> esl::result<void> {
                    if (!target) return esl::result_error{"Missing target."};
                    *target = value;
                    return {};
                },
                [&ctx] (sem::CompleteValue * target, std::string const & value) -> esl::result<void> {
                    if (!target) return esl::result_error{"Missing target."};
                    auto translatoinResult = lift<target::category>(interface::translateTarget(ctx))(*target);
                    if (!translatoinResult) return translatoinResult.error();
                    return {};
                },
                [&ctx] (std::string const & target, sem::CompleteValue const & value) -> esl::result<void> {
                    auto translatoinResult = lift<target::category>(interface::translateValue(ctx))(value);
                    if (!translatoinResult) return translatoinResult.error();
                    return ctx.insertStatement(c::assignment(*translatoinResult, target));
                },
                [&ctx] (std::string const & target, std::string const & value) -> esl::result<void> {
                    return ctx.insertStatement(c::assignment(value, target));
                }
            )(target.target, converted.value);
        }

        return {};
    }

    //// Definition ////

    interface::DisplayResult syn::node::Definition::display () const {
        return
            lift<target::component, target::category>(interface::display)(target) + " = " +
            lift<target::component, target::category>(interface::display)(value);
    }

    interface::StatementResolutionResult syn::node::Definition::resolveStatement (context::C & ctx) const {
        auto declsResult  = lift<target::component, target::category>(interface::resolveDeclaration(ctx))(target);
        auto valuesResult = lift<target::component, target::category>(interface::resolveExpression(ctx))(value);
        if (!declsResult)  return declsResult.error();
        if (!valuesResult) return valuesResult.error();
        auto decls  = *declsResult;
        auto values = *valuesResult;

        auto valueIterator = values.begin();
        for (auto const & decl: decls) {
            esl::tiny_vector<sem::Variable> vars;
            auto count = decl.type.size();
            if (count > values.end() - valueIterator)
                return esl::result_error{"More values than targets in a definition."};

            for (auto const & [type, value]: zip(decl.type, esl::view(valueIterator, valueIterator + count))) {
                auto defResult = lift<target::category>(interface::translateDefinition(ctx, value))(type);
                if (!defResult) return defResult.error();
                auto def = *defResult;

                vars.push_back(sem::Variable{
                    .type     = value.type,
                    .value    = def.value,
                    .variable = std::nullopt
                });
            }

            auto varResult = ctx.compCtx->insertValue(decl.name, vars);
            if (!varResult) return varResult.error();
            valueIterator += count;
        }

        if (valueIterator != values.end())
            return esl::result_error{"More targets than values in a definition."};

        return {};
    }

    //// For ////

    interface::DisplayResult syn::node::For::display () const {
        return
            "for " + esl::parenthesized(lift<target::component, target::category>(interface::display)(declarations)) +
            " "    + lift<target::component, target::category>(interface::display)(body);
    }

    interface::StatementResolutionResult syn::node::For::resolveStatement (context::C & ctx) const {
        return {};
#if 0 // TODO
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
            auto returned = interface::resolveStatement(iter_scope)(body);

            if (returned)
                return *returned;
            if (returned.has_error())
                return syn::make_execution_result(returned.error());
        }

        return {};
#endif
    }

    //// FunDef ////

    interface::DisplayResult syn::node::FunDef::display () const {
        return
            lift<target::component, target::category>(interface::display)(output) + " " +
            interface::display(name) + " " +
            esl::parenthesized(lift<target::component, target::category>(interface::display)(input)) + " " +
            lift<target::component, target::category>(interface::display)(body);
    }

    interface::StatementResolutionResult syn::node::FunDef::resolveStatement (context::C & ctx) const {

        auto outResult = lift<target::component, target::category>(interface::resolveType(ctx))(output);
        if (!outResult) return outResult.error();
        auto outTypes = *std::move(outResult);

        auto inResult = lift<target::component, target::category>(interface::resolveDeclaration(ctx))(input);
        if (!inResult) return inResult.error();
        auto inDecls = *std::move(inResult);

        auto namesResult = lift<target::component, target::category>(interface::extractNames)(body);
        if (!namesResult) return namesResult.error();
        auto typeNamesResult = lift<target::component, target::category>(interface::extractTypeNames)(body);
        if (!typeNamesResult) return typeNamesResult.error();
        auto capture = ctx.compCtx->capture(*namesResult, *typeNamesResult);

        sem::value::Function value{
            .capture      = std::move(capture), // TODO
            .outType      = esl::make_component_vector(outTypes),
            .parameters   = esl::make_component_vector(inDecls),
            .body         = body,
            .functionName = {},
            .captureName  = {},
        };

        auto translated = value.translateValue();

        auto varResult = ctx.compCtx->insertValue(*name.name, {/* TODO */});
        if (!varResult) return varResult.error();

        /*
        auto stored = ctx.compCtx->storeValue(sem::value::FunctionValue {
            .out_type   = make_component_vector(output),
            .parameters = make_component_vector(input),
            .body       = body,
            .capture    = ctx // TODO
        });
        if (!stored)
            return syn::make_execution_result(stored.error());

        auto value = esl::init<tuple_vector>(sem::value::complete{sem::value::Function {
            .value = stored.get()
        }});
        */

        // TODO
        /*
        auto define_result = ctx.define_value(*name->name, value);
        if (!define_result)
            return syn::make_execution_result(define_result.error());
        */

        return {};
    }

    //// If ////

    interface::DisplayResult syn::node::If::display () const {
        return
            "if "    + esl::parenthesized(lift<target::component, target::category>(interface::display)(condition)) +
            " "      + lift<target::component, target::category>(interface::display)(positive_branch) +
            " else " + lift<target::component, target::category>(interface::display)(negative_branch);
    }

    interface::StatementResolutionResult syn::node::If::resolveStatement (context::C & ctx) const {
        return {};
#if 0 // TODO
        auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(esl::single(syn::evaluate(ctx)(condition))));
        if (!result)
            return syn::make_execution_result(result.error());
        if (*result)
            return interface::resolveStatement(ctx)(positive_branch);
        else
            return interface::resolveStatement(ctx)(negative_branch);
#endif
    }

    //// Return ////

    interface::DisplayResult syn::node::Return::display () const {
        return "return " + lift<target::component, target::category>(interface::display)(value);
    }

    interface::StatementResolutionResult syn::node::Return::resolveStatement (context::C & ctx) const {
        return {};
#if 0 // TODO
        auto value_result = esl::unite_results(syn::evaluate(ctx)(value));
        if (!value_result)
            return syn::make_execution_result(value_result.error());
        auto value = *std::move(value_result);

        return value;
#endif
    }

    //// TypeDef ////

    interface::DisplayResult syn::node::TypeDef::display () const {
        return
            "type " + interface::display(target) +
            " = "   + lift<target::component, target::category>(interface::display)(type);
    }

    interface::StatementResolutionResult syn::node::TypeDef::resolveStatement (context::C & ctx) const {
        return {};
#if 0 // TODO
        std::string name = *target->name;

        auto type_result = esl::unite_results(sem::complete(ctx)(syn::eval_type(ctx)(type)));
        if (!type_result)
            return syn::make_execution_result(type_result.error());
        auto type = *std::move(type_result);

        auto define_result = ctx.define_type(name, type);
        if (!define_result)
            return syn::make_execution_result(define_result.error());

        return {};
#endif
    }

    //// While ////

    interface::DisplayResult syn::node::While::display () const {
        return
            "while " + esl::parenthesized(lift<target::component, target::category>(interface::display)(condition)) +
            " "      + lift<target::component, target::category>(interface::display)(body);
    }

    interface::StatementResolutionResult syn::node::While::resolveStatement (context::C & ctx) const {
        return {};
#if 0 // TODO
        while (true) {
            auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(esl::single(syn::evaluate(ctx)(condition))));
            if (!result)
                return syn::make_execution_result(result.error());
            if (*result) {
                auto branch_scope = make_child_context(ctx);
                auto returned = interface::resolveStatement(branch_scope)(body);
                if (returned)
                    return *returned;
                if (returned.has_error())
                    return syn::make_execution_result(returned.error());
            } else
                return {};
        }
#endif
    }

    //// When ////

    interface::DisplayResult syn::node::When::display () const {
        return
            "when " + esl::parenthesized(lift<target::component, target::category>(interface::display)(condition)) +
            " "     + lift<target::component, target::category>(interface::display)(branch);
    }

    interface::StatementResolutionResult syn::node::When::resolveStatement (context::C & ctx) const {
        return {};
#if 0 // TODO
        auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(esl::single(syn::evaluate(ctx)(condition))));
        if (!result)
            return syn::make_execution_result(result.error());
        if (*result) {
            auto branch_scope = make_child_context(ctx);
            return interface::resolveStatement(branch_scope)(branch);
        }
        return {};
#endif
    }

}
