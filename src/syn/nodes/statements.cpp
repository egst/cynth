#include "syn/nodes/statements.hpp"

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

// TODO
#if 0
namespace cynth {

    //// Assignment ////

    display_result syn::node::Assignment::display () const {
        return cynth::display(target) + " = " + cynth::display(value);
    }

    syn::execution_result syn::node::Assignment::execute (sem::context & ctx) const {
        auto targets_result = syn::eval_target(ctx)(target);
        if (!targets_result)
            return syn::make_execution_result(targets_result.error());
        auto targets = *std::move(targets_result);

        // TODO: What about .size() == 0? And elsewhere as well...
        if (targets.size() > 1)
            return syn::make_execution_result(result_error{"Assigning to tuples is not supported yet."});

        auto target = std::move(targets.front());

        auto values_result = util::unite_results(syn::evaluate(ctx)(value));
        if (!values_result)
            return syn::make_execution_result(values_result.error());
        auto values = *std::move(values_result);

        auto target_ref_result = sem::resolve_target(target);
        if (!target_ref_result)
            return syn::make_execution_result(target_ref_result.error());
        auto target_ref = *std::move(target_ref_result);

        if (values.size() > target_ref.type.size())
            return result_error{"More values than targets in an assignment."};
        if (values.size() < target_ref.type.size())
            return result_error{"More targets than values in an assignment."};
        auto converted_results = sem::convert(ctx)(values, target_ref.type);
        if (!converted_results)
            return converted_results.error();
        auto converted_result = util::unite_results(*converted_results);
        if (!converted_result)
            return converted_result.error();
        auto assign_result = target_ref.assign(*std::move(converted_result));
        if (!assign_result)
            return assign_result.error();

        return {};
    }

    //// Definition ////

    display_result syn::node::Definition::display () const {
        return cynth::display(target) + " = " + cynth::display(value);
    }

    syn::execution_result syn::node::Definition::execute (sem::context & ctx) const {
        auto decls_result = util::unite_results(sem::complete(ctx)(syn::eval_decl(ctx)(target)));
        if (!decls_result)
            return syn::make_execution_result(decls_result.error());
        auto decls = *std::move(decls_result);

        auto values_result = util::unite_results(syn::evaluate(ctx)(value));
        if (!values_result)
            return syn::make_execution_result(values_result.error());
        auto values = *std::move(values_result);

        auto define_result = ctx.define_value(decls, values);
        if (!define_result)
            return syn::make_execution_result(define_result.error());

        return {};
    }

    syn::translation_result syn::node::Definition::translate (sem::translation_context & ctx) const {
        return {};

        auto decls_result = util::unite_results(sem::complete(ctx.compconst_context)(eval_decl(ctx.compconst_context)(target)));
        if (!decls_result)
            return syn::make_translation_result(decls_result.error());
        auto decls = *std::move(decls_result);

        auto values_result = util::unite_results(syn::translate(ctx)(value));
        if (!values_result)
            return syn::make_translation_result(values_result.error());
        auto values = *std::move(values_result);

        ctx.define(decls, values);

        // TODO...
    }

    //// For ////

    display_result syn::node::For::display () const {
        return
            "for " + util::parenthesized(cynth::display(declarations)) +
            " "    + cynth::display(body);
    }

    syn::execution_result syn::node::For::execute (sem::context & ctx) const {
        auto decls_result = sem::for_decls(ctx, *declarations);
        if (!decls_result)
            return syn::make_execution_result(decls_result.error());
        auto [size, iter_decls] = *std::move(decls_result);

        for (integral i = 0; i < size; ++i) {
            // Init inner scope:
            auto iter_scope = make_child_context(ctx);

            // Define iteration elements:
            for (auto & [decl, value] : iter_decls)
                iter_scope.define_value(decl, value.value->value[i]);

            // Execute the loop body:
            auto returned = syn::execute(iter_scope)(body);

            if (returned)
                return *returned;
            if (returned.has_error())
                return syn::make_execution_result(returned.error());
        }

        return {};
    }

    //// FunctionDef ////

    display_result syn::node::FunctionDef::display () const {
        return cynth::display(output) + " " + cynth::display(name) + " " + util::parenthesized(cynth::display(input)) + " " + cynth::display(body);
    }

    syn::execution_result syn::node::FunctionDef::execute (sem::context & ctx) const {
        auto output_result = util::unite_results(sem::complete(ctx)(syn::eval_type(ctx)(output)));
        if (!output_result)
            return syn::make_execution_result(output_result.error());
        auto output = *std::move(output_result);

        auto input_result = util::unite_results(sem::complete(ctx)(syn::eval_decl(ctx)(input)));
        if (!input_result)
            return syn::make_execution_result(input_result.error());
        auto input = *std::move(input_result);

        auto stored = ctx.store_value(sem::value::FunctionValue {
            .out_type   = make_component_vector(output),
            .parameters = make_component_vector(input),
            .body       = body,
            .capture    = ctx // TODO
        });
        if (!stored)
            return syn::make_execution_result(stored.error());

        auto value = util::init<tuple_vector>(sem::value::complete{sem::value::Function {
            .value = stored.get()
        }});

        // TODO
#if 0
        auto define_result = ctx.define_value(*name->name, value);
        if (!define_result)
            return syn::make_execution_result(define_result.error());
#endif

        return {};
    }

    //// If ////

    display_result syn::node::If::display () const {
        return
            "if "    + util::parenthesized(cynth::display(condition)) +
            " "      + cynth::display(positive_branch) +
            " else " + cynth::display(negative_branch);
    }

    syn::execution_result syn::node::If::execute (sem::context & ctx) const {
        auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(syn::evaluate(ctx)(condition))));
        if (!result)
            return syn::make_execution_result(result.error());
        if (*result)
            return syn::execute(ctx)(positive_branch);
        else
            return syn::execute(ctx)(negative_branch);
    }

    //// Return ////

    display_result syn::node::Return::display () const {
        return "return " + cynth::display(value);
    }

    syn::execution_result syn::node::Return::execute (sem::context & ctx) const {
        auto value_result = util::unite_results(syn::evaluate(ctx)(value));
        if (!value_result)
            return syn::make_execution_result(value_result.error());
        auto value = *std::move(value_result);

        return value;
    }

    //// TypeDef ////

    display_result syn::node::TypeDef::display () const {
        return "type " + cynth::display(target) + " = " + cynth::display(type);
    }

    syn::execution_result syn::node::TypeDef::execute (sem::context & ctx) const {
        std::string name = *target->name;

        auto type_result = util::unite_results(sem::complete(ctx)(syn::eval_type(ctx)(type)));
        if (!type_result)
            return syn::make_execution_result(type_result.error());
        auto type = *std::move(type_result);

        auto define_result = ctx.define_type(name, type);
        if (!define_result)
            return syn::make_execution_result(define_result.error());

        return {};
    }

    //// While ////

    display_result syn::node::While::display () const {
        return
            "while " + util::parenthesized(cynth::display(condition)) +
            " "      + cynth::display(body);
    }

    syn::execution_result syn::node::While::execute (sem::context & ctx) const {
        while (true) {
            auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(syn::evaluate(ctx)(condition))));
            if (!result)
                return syn::make_execution_result(result.error());
            if (*result) {
                auto branch_scope = make_child_context(ctx);
                auto returned = syn::execute(branch_scope)(body);
                if (returned)
                    return *returned;
                if (returned.has_error())
                    return syn::make_execution_result(returned.error());
            } else
                return {};
        }
    }

    //// When ////

    display_result syn::node::When::display () const {
        return
            "when " + util::parenthesized(cynth::display(condition)) +
            " "     + cynth::display(branch);
    }

    syn::execution_result syn::node::When::execute (sem::context & ctx) const {
        auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(syn::evaluate(ctx)(condition))));
        if (!result)
            return syn::make_execution_result(result.error());
        if (*result) {
            auto branch_scope = make_child_context(ctx);
            return syn::execute(branch_scope)(branch);
        }
        return {};
    }

}
#endif
