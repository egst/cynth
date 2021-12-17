#include "syn/nodes/statements.hpp"

#include <string>
#include <utility>

#include "esl/category.hpp"
#include "esl/component.hpp"
#include "esl/containers.hpp"
#include "esl/lift.hpp"
#include "esl/string.hpp"
#include "esl/sugar.hpp"
#include "esl/tiny_vector.hpp"
#include "esl/view.hpp"
#include "esl/zip.hpp"

// TODO: Clean this up, when I'm done.
#include "context/c.hpp"
#include "interface/common.hpp"
#include "interface/compound.hpp"
#include "interface/misc.hpp"
#include "interface/nodes.hpp"
#include "interface/types.hpp"
#include "interface/values.hpp"
#include "sem/compound.hpp"
#include "sem/translation.hpp"
#include "sem/numeric_types.hpp"

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

namespace cynth::syn {

    using namespace esl::sugar;

    namespace target = esl::target;

    using sem::Returned;
    using sem::NoReturn;
    using sem::Variable;

    //// Assignment ////

    interface::DisplayResult node::Assignment::display () const {
        return
            (*target >>= target::category{} && interface::display) + " = " +
            (*value >>= target::category{} && interface::display);
    }

    interface::StatementProcessingResult node::Assignment::processStatement (context::C & ctx) const {
        auto targetsResult = *target >>= target::category{} && interface::resolveTarget(ctx);
        auto valuesResult  = *value  >>= target::category{} && interface::processExpression(ctx);
        if (!valuesResult)  return valuesResult.error();
        if (!targetsResult) return targetsResult.error();
        auto targets = *std::move(targetsResult);
        auto values  = *std::move(valuesResult);

        // TODO: What about .size() == 0? And elsewhere as well...
        // I guess techincally it shouldn't be a problem semantically and it should also be impossible syntactically,
        // so maybe it's not a problem, but I should check it once I get back to testing again.

        if (values.size() > targets.size())
            return esl::result_error{"More values than targets in an assignment."};
        if (targets.size() > values.size())
            return esl::result_error{"More targets than values in an assignment."};

        //lift<target::tiny_vector>(interface::processAssignment(ctx))(value, target);
        // TODO: lift<tiny_vector> doesn't work here for some reason.

        for (auto const & [target, value]: esl::zip(targets, values)) {
            auto result = interface::processAssignment(ctx)(value, target);
            if (!result) return result.error();
        }

        return {sem::NoReturn{}};
    }

    //// Definition ////

    interface::DisplayResult node::Definition::display () const {
        return
            (*target >>= target::category{} && interface::display) + " = " +
            (*value >>= target::category{} && interface::display);
    }

    interface::StatementProcessingResult node::Definition::processStatement (context::C & ctx) const {
        auto declsResult  = *target >>= target::category{} && interface::resolveDeclaration(ctx);
        auto valuesResult = *value  >>= target::category{} && interface::processExpression(ctx);
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
                auto definitionResult = type >>= target::category{} && interface::processDefinition(ctx)(value);
                if (!definitionResult) return definitionResult.error();

                vars.push_back(*definitionResult);
            }

            auto varResult = ctx.compCtx->insertValue(decl.name, vars);
            if (!varResult) return varResult.error();
            valueIterator += count;
        }

        if (valueIterator != values.end())
            return esl::result_error{"More targets than values in a definition."};

        return {sem::NoReturn{}};
    }

    //// For ////

    interface::DisplayResult node::For::display () const {
        return
            "for " + esl::parenthesized(*declarations >>= target::category{} && interface::display) +
            " "    + (*body >>= target::category{} && interface::display);
    }

    // TODO: Maybe check if some optimizations could be done for some simple iteration cases.
    interface::StatementProcessingResult node::For::processStatement (context::C & ctx) const {
        auto declsResult = interface::resolveRangeDeclarations(ctx, *declarations);
        if (!declsResult) return declsResult.error();
        auto [size, iterDecls] = *std::move(declsResult);

        /***
        for (cth_int itervar_i = 0; itervar_i < <size>; ++itervar_i) {
            <decl> = <array>[i]; ...
            <body>
        }
        ***/

#if 0 // TODO
        for (sem::Integral index = 0; index < size; ++index) {
            // Init inner scope:
            auto scope = ctx.makeScopeChild();

            // Define iteration elements:
            for (auto & [decl, array]: iterDecls) {
                auto elementResult = interface::processStaticSubscript(index)(array);
                if (!elementResult) return elementResult.error();
                auto element = *std::move(elementResult);

                auto definitionResult = esl::single(decl.type) >>= target::result{} && target::category{} &&
                    interface::processDefinition(ctx)(element); // Note: Arrays of tuples are not supported yet.
                if (!definitionResult) return definitionResult.error();
                auto variable = *std::move(definitionResult);

                auto varResult = scope.compCtx->insertValue(decl.name, {variable});
            }

            // Execute the loop body:
            auto returned = *body >>= target::category{} && interface::processStatement(scope);
            if (returned.has_error()) return returned.error();

            auto returnKind = returned.kind();

            // TODO: I just realized... This will unroll the loop.
            // I probably don't want to implement any loop unrolling. I'll let the C compiler take care of that.
            // But maybe it still could be useful to go through the whole loop at compile time to extract some compconst values.
            // Eh... I need a break, this makes no sense, how do I even know the range of the loop at compile-time?

            if (returnKind == sem::Returned::returned)
                return returned;

            if (returned)
                return *returned;
        }
#endif

        return {sem::NoReturn{}};
    }

    //// FunDef ////

    interface::DisplayResult node::FunDef::display () const {
        return
            (*output >>= target::category{} && interface::display) + " " +
            (name >>= interface::display) + " " +
            esl::parenthesized(*input >>= target::category{} && interface::display) + " " +
            (*body >>= target::category{} && interface::display);
    }

    interface::StatementProcessingResult node::FunDef::processStatement (context::C & ctx) const {

        auto outResult = *output >>= target::category{} && interface::resolveType(ctx);
        auto inResult  = *input  >>= target::category{} && interface::resolveDeclaration(ctx);
        if (!outResult) return outResult.error();
        if (!inResult)  return inResult.error();
        auto outTypes = *std::move(outResult);
        auto inDecls  = *std::move(inResult);

#if 0 // TODO
        auto namesResult = lift<target::component, target::category>(interface::extractNames)(body);
        if (!namesResult) return namesResult.error();
        auto typeNamesResult = lift<target::component, target::category>(interface::extractTypeNames)(body);
        if (!typeNamesResult) return typeNamesResult.error();
        auto capture = ctx.compCtx->capture(*namesResult, *typeNamesResult);

        sem::value::Function value{
            .context      = std::move(capture), // TODO
            .outType      = esl::make_component_vector(outTypes),
            .parameters   = esl::make_component_vector(inDecls),
            .body         = body,
            .functionName = {},
            .captureName  = {},
        };

        auto translated = value.translateValue();

        auto varResult = ctx.compCtx->insertValue(*name.name, {/* TODO */});
        if (!varResult) return varResult.error();
#endif

        /*
        auto stored = ctx.compCtx->storeValue(sem::value::FunctionValue {
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

        return {sem::NoReturn{}};
    }

    //// If ////

    interface::DisplayResult node::If::display () const {
        return
            "if "    + esl::parenthesized(*condition >>= target::category{} && interface::display) +
            " "      + (*positiveBranch >>= target::category{} && interface::display) +
            " else " + (*negativeBranch >>= target::category{} && interface::display);
    }

    interface::StatementProcessingResult node::If::processStatement (context::C & ctx) const {
        return {sem::NoReturn{}};
#if 0 // TODO
        auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(esl::single(evaluate(ctx)(condition))));
        if (!result)
            return make_execution_result(result.error());
        if (*result)
            return interface::processStatement(ctx)(positive_branch);
        else
            return interface::processStatement(ctx)(negative_branch);
#endif
    }

    //// Return ////

    interface::DisplayResult node::Return::display () const {
        return "return " + (*value >>= target::category{} && interface::display);
    }

    interface::StatementProcessingResult node::Return::processStatement (context::C & ctx) const {
        return {sem::NoReturn{}};
#if 0 // TODO
        auto value_result = esl::unite_results(evaluate(ctx)(value));
        if (!value_result)
            return make_execution_result(value_result.error());
        auto value = *std::move(value_result);

        return value;
#endif
    }

    //// TypeDef ////

    interface::DisplayResult node::TypeDef::display () const {
        return
            "type " + (target >>= interface::display) +
            " = "   + (*type >>= target::category{} && interface::display);
    }

    interface::StatementProcessingResult node::TypeDef::processStatement (context::C & ctx) const {
        return {sem::NoReturn{}};
#if 0 // TODO
        std::string name = *target->name;

        auto type_result = esl::unite_results(sem::complete(ctx)(eval_type(ctx)(type)));
        if (!type_result)
            return make_execution_result(type_result.error());
        auto type = *std::move(type_result);

        auto define_result = ctx.define_type(name, type);
        if (!define_result)
            return make_execution_result(define_result.error());

        return {};
#endif
    }

    //// While ////

    interface::DisplayResult node::While::display () const {
        return
            "while " + esl::parenthesized(*condition >>= target::category{} && interface::display) +
            " "      + (*body >>= target::category{} && interface::display);
    }

    interface::StatementProcessingResult node::While::processStatement (context::C & ctx) const {
        return {sem::NoReturn{}};
#if 0 // TODO
        while (true) {
            auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(esl::single(evaluate(ctx)(condition))));
            if (!result)
                return make_execution_result(result.error());
            if (*result) {
                auto branch_scope = make_child_context(ctx);
                auto returned = interface::processStatement(branch_scope)(body);
                if (returned)
                    return *returned;
                if (returned.has_error())
                    return make_execution_result(returned.error());
            } else
                return {};
        }
#endif
    }

    //// When ////

    interface::DisplayResult node::When::display () const {
        return
            "when " + esl::parenthesized(*condition >>= target::category{} && interface::display) +
            " "     + (*branch >>= target::category{} && interface::display);
    }

    interface::StatementProcessingResult node::When::processStatement (context::C & ctx) const {
        return {sem::NoReturn{}};
#if 0 // TODO
        auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(esl::single(evaluate(ctx)(condition))));
        if (!result)
            return make_execution_result(result.error());
        if (*result) {
            auto branch_scope = make_child_context(ctx);
            return interface::processStatement(branch_scope)(branch);
        }
        return {};
#endif
    }

}

//// Pieces of old code ////

// This might be useful when implementing assignments.
#if 0
            auto assignmentResult = lift<target::variant>(
                [&ctx] (sem::TypedTargetExpression const & target, sem::TypedExpression const & expr) -> esl::result<void> {
                    /***
                    Int a = 1;
                    Int b = 2;
                    a = b; # assigning a run-time value to a runtime variable
                    # Note that even values known at compile-time (such as the literals `1` and `2` above)
                    # are intentionally "lost" (translated to a run-time C expression) when assigned to any non-const variable.
                    # So, while `2` was initially a comp-time value, `b` is a run-time expression.
                    ***/

                    auto conversionResult = lift<target::category>(
                        interface::translateConversion(ctx, expr)
                    )(target.type);
                    if (!conversionResult) return conversionResult.error();
                    auto converted = *std::move(conversionResult);

                    return ctx.insertStatement(c::assignment(expr.expression, target.expression));
                },
                [&ctx] (sem::TypedTargetExpression const & target, sem::CompleteValue const & value) -> esl::result<void> {
                    /***
                    # runtime x
                    Int a;
                    a = 1; # assigning a compile-time value to a runtime variable
                    ***/

                    auto exprResult = lift<target::category>(interface::translateValue(ctx))(value);
                    if (!exprResult) return exprResult.error();
                    auto expr = *std::move(exprResult);

                    auto conversionResult = lift<target::category>(
                        interface::translateConversion(ctx, expr)
                    )(target.type);
                    if (!conversionResult) return conversionResult.error();
                    auto converted = *std::move(conversionResult);

                    return esl::result_error{"A compile-time value cannot be assigned to a run-time target."};
                },
                [&ctx] (sem::CompleteValue * target, sem::CompleteValue const & value) -> esl::result<void> {
                    // TODO: Assignment to compconst variables should be impossible.
                    // So does this even make sense? Do comp-time targets make any sense?

                    if (!target) return esl::result_error{"Missing target."};

                    auto targetType = lift<target::category>(interface::valueType)(*target);
                    auto conversionResult = lift<target::category>(interface::convertValue(ctx))(value, targetType);
                    if (!conversionResult) return conversionResult.error();
                    auto converted = *std::move(conversionResult);

                    *target = value;

                    return {};
                },
                // Note: This is an implementation error, not user error.
                [&ctx] (sem::CompleteValue *, sem::TypedExpression const &) -> esl::result<void> {
                    return esl::result_error{"A run-time value cannot be assigned to a compile-time target."};
                }
            )(target.target, value.value);
            if (!assignmentResult) return assignmentResult.error();
#endif

// This might be useful when implementing definitions/declarations.
#if 0
                auto definitionResult = lift<target::variant>(
                    [] (sem::CompleteValue const & value) {
                        /***
                        Int a = 1;       # initializing from a compile-time value
                        Int const b = 1; # in compconst cases, no run-time declaration is needed
                        ***/

                    },
                    [&ctx, &type = type] (sem::TypedExpression const & expr) {
                        /***
                        Int b = 1;
                        Int a = b; # initializing from a run-time value
                        ***/

                        auto result = lift<target::category>(interface::translateDefinition(ctx, expr))(type);
                        // -> TypedName
                    },
                )(value.value);
                if (!definitionResult ) return definitionResult.error();
                auto definition = *definitionResult;

                /*
                auto defResult = lift<target::category>(interface::translateDefinition(ctx, value))(type);
                if (!defResult) return defResult.error();
                auto def = *defResult;
                */
#endif
