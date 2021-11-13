#include "ast/nodes/statements.hpp"

#include "sem/forward.hpp"
#include "result.hpp"
#include "common_interface.hpp"
#include "ast/nodes/expressions.hpp"
#include "ast/categories/declaration.hpp"
#include "ast/categories/range_decl.hpp"
#include "ast/categories/expression.hpp"
#include "ast/categories/statement.hpp"
#include "ast/categories/type.hpp"
#include "ast/interface.hpp"
#include "sem/interface.hpp"
#include "sem/util.hpp"
#include "util/general.hpp"
#include "util/string.hpp"
#include "util/container.hpp"

#include <string>

namespace cynth {

    //// Assignment ////

    template <>
    void component_deleter<ast::node::Assignment>::operator () (ast::node::Assignment * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Assignment * component_allocator<ast::node::Assignment>::operator () (ast::node::Assignment const & other) const {
        return new ast::node::Assignment{other};
    }

    template <>
    ast::node::Assignment * component_allocator<ast::node::Assignment>::operator () (ast::node::Assignment && other) const {
        return new ast::node::Assignment{std::move(other)};
    }

    display_result ast::node::Assignment::display () const {
        return cynth::display(target) + " = " + cynth::display(value);
    }

    ast::execution_result ast::node::Assignment::execute (sem::context & ctx) const {
        auto targets_result = ast::eval_target(ctx)(target);
        if (!targets_result)
            return ast::make_execution_result(targets_result.error());
        auto targets = *std::move(targets_result);

        // TODO: What about .size() == 0? And elsewhere as well...
        if (targets.size() > 1)
            return ast::make_execution_result(result_error{"Assigning to tuples is not supported yet."});

        auto target = std::move(targets.front());

        auto values_result = util::unite_results(ast::evaluate(ctx)(value));
        if (!values_result)
            return ast::make_execution_result(values_result.error());
        auto values = *std::move(values_result);

        auto target_ref_result = sem::resolve_target(target);
        if (!target_ref_result)
            return ast::make_execution_result(target_ref_result.error());
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

    template <>
    void component_deleter<ast::node::Definition>::operator () (ast::node::Definition * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Definition * component_allocator<ast::node::Definition>::operator () (ast::node::Definition const & other) const {
        return new ast::node::Definition{other};
    }

    template <>
    ast::node::Definition * component_allocator<ast::node::Definition>::operator () (ast::node::Definition && other) const {
        return new ast::node::Definition{std::move(other)};
    }

    display_result ast::node::Definition::display () const {
        return cynth::display(target) + " = " + cynth::display(value);
    }

    ast::execution_result ast::node::Definition::execute (sem::context & ctx) const {
        auto decls_result = util::unite_results(sem::complete(ctx)(ast::eval_decl(ctx)(target)));
        if (!decls_result)
            return ast::make_execution_result(decls_result.error());
        auto decls = *std::move(decls_result);

        auto values_result = util::unite_results(ast::evaluate(ctx)(value));
        if (!values_result)
            return ast::make_execution_result(values_result.error());
        auto values = *std::move(values_result);

        auto define_result = ctx.define_value(decls, values);
        if (!define_result)
            return ast::make_execution_result(define_result.error());

        return {};
    }

    ast::translation_result ast::node::Definition::translate (sem::translation_context & ctx) const {
        return {};

        auto decls_result = util::unite_results(sem::complete(ctx.compconst_context)(eval_decl(ctx.compconst_context)(target)));
        if (!decls_result)
            return ast::make_translation_result(decls_result.error());
        auto decls = *std::move(decls_result);

        auto values_result = util::unite_results(ast::translate(ctx)(value));
        if (!values_result)
            return ast::make_translation_result(values_result.error());
        auto values = *std::move(values_result);

        ctx.define(decls, values);

        // TODO...
    }

    //// For ////

    template <>
    void component_deleter<ast::node::For>::operator () (ast::node::For * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::For * component_allocator<ast::node::For>::operator () (ast::node::For const & other) const {
        return new ast::node::For{other};
    }

    template <>
    ast::node::For * component_allocator<ast::node::For>::operator () (ast::node::For && other) const {
        return new ast::node::For{std::move(other)};
    }

    display_result ast::node::For::display () const {
        return
            "for " + util::parenthesized(cynth::display(declarations)) +
            " "    + cynth::display(body);
    }

    ast::execution_result ast::node::For::execute (sem::context & ctx) const {
        auto decls_result = sem::for_decls(ctx, *declarations);
        if (!decls_result)
            return ast::make_execution_result(decls_result.error());
        auto [size, iter_decls] = *std::move(decls_result);

        for (integral i = 0; i < size; ++i) {
            // Init inner scope:
            auto iter_scope = make_child_context(ctx);

            // Define iteration elements:
            for (auto & [decl, value] : iter_decls)
                iter_scope.define_value(decl, value.value->value[i]);

            // Execute the loop body:
            auto returned = ast::execute(iter_scope)(body);

            if (returned)
                return *returned;
            if (returned.has_error())
                return ast::make_execution_result(returned.error());
        }

        return {};
    }

    //// FunctionDef ////

    template <>
    void component_deleter<ast::node::FunctionDef>::operator () (ast::node::FunctionDef * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::FunctionDef * component_allocator<ast::node::FunctionDef>::operator () (ast::node::FunctionDef const & other) const {
        return new ast::node::FunctionDef{other};
    }

    template <>
    ast::node::FunctionDef * component_allocator<ast::node::FunctionDef>::operator () (ast::node::FunctionDef && other) const {
        return new ast::node::FunctionDef{std::move(other)};
    }

    display_result ast::node::FunctionDef::display () const {
        return cynth::display(output) + " " + cynth::display(name) + " " + util::parenthesized(cynth::display(input)) + " " + cynth::display(body);
    }

    ast::execution_result ast::node::FunctionDef::execute (sem::context & ctx) const {
        auto output_result = util::unite_results(sem::complete(ctx)(ast::eval_type(ctx)(output)));
        if (!output_result)
            return ast::make_execution_result(output_result.error());
        auto output = *std::move(output_result);

        auto input_result = util::unite_results(sem::complete(ctx)(ast::eval_decl(ctx)(input)));
        if (!input_result)
            return ast::make_execution_result(input_result.error());
        auto input = *std::move(input_result);

        auto stored = ctx.store_value(sem::value::FunctionValue {
            .out_type   = make_component_vector(output),
            .parameters = make_component_vector(input),
            .body       = body,
            .capture    = ctx // TODO
        });
        if (!stored)
            return ast::make_execution_result(stored.error());

        auto value = util::init<tuple_vector>(sem::value::complete{sem::value::Function {
            .value = stored.get()
        }});

        // TODO
#if 0
        auto define_result = ctx.define_value(*name->name, value);
        if (!define_result)
            return ast::make_execution_result(define_result.error());
#endif

        return {};
    }

    //// If ////

    template <>
    void component_deleter<ast::node::If>::operator () (ast::node::If * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::If * component_allocator<ast::node::If>::operator () (ast::node::If const & other) const {
        return new ast::node::If{other};
    }

    template <>
    ast::node::If * component_allocator<ast::node::If>::operator () (ast::node::If && other) const {
        return new ast::node::If{std::move(other)};
    }

    display_result ast::node::If::display () const {
        return
            "if "    + util::parenthesized(cynth::display(condition)) +
            " "      + cynth::display(positive_branch) +
            " else " + cynth::display(negative_branch);
    }

    ast::execution_result ast::node::If::execute (sem::context & ctx) const {
        auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(ast::evaluate(ctx)(condition))));
        if (!result)
            return ast::make_execution_result(result.error());
        if (*result)
            return ast::execute(ctx)(positive_branch);
        else
            return ast::execute(ctx)(negative_branch);
    }

    //// Return ////

    template <>
    void component_deleter<ast::node::Return>::operator () (ast::node::Return * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Return * component_allocator<ast::node::Return>::operator () (ast::node::Return const & other) const {
        return new ast::node::Return{other};
    }

    template <>
    ast::node::Return * component_allocator<ast::node::Return>::operator () (ast::node::Return && other) const {
        return new ast::node::Return{std::move(other)};
    }

    display_result ast::node::Return::display () const {
        return "return " + cynth::display(value);
    }

    ast::execution_result ast::node::Return::execute (sem::context & ctx) const {
        auto value_result = util::unite_results(ast::evaluate(ctx)(value));
        if (!value_result)
            return ast::make_execution_result(value_result.error());
        auto value = *std::move(value_result);

        return value;
    }

    //// TypeDef ////

    template <>
    void component_deleter<ast::node::TypeDef>::operator () (ast::node::TypeDef * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::TypeDef * component_allocator<ast::node::TypeDef>::operator () (ast::node::TypeDef const & other) const {
        return new ast::node::TypeDef{other};
    }

    template <>
    ast::node::TypeDef * component_allocator<ast::node::TypeDef>::operator () (ast::node::TypeDef && other) const {
        return new ast::node::TypeDef{std::move(other)};
    }

    display_result ast::node::TypeDef::display () const {
        return "type " + cynth::display(target) + " = " + cynth::display(type);
    }

    ast::execution_result ast::node::TypeDef::execute (sem::context & ctx) const {
        std::string name = *target->name;

        auto type_result = util::unite_results(sem::complete(ctx)(ast::eval_type(ctx)(type)));
        if (!type_result)
            return ast::make_execution_result(type_result.error());
        auto type = *std::move(type_result);

        auto define_result = ctx.define_type(name, type);
        if (!define_result)
            return ast::make_execution_result(define_result.error());

        return {};
    }

    //// While ////

    template <>
    void component_deleter<ast::node::While>::operator () (ast::node::While * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::While * component_allocator<ast::node::While>::operator () (ast::node::While const & other) const {
        return new ast::node::While{other};
    }

    template <>
    ast::node::While * component_allocator<ast::node::While>::operator () (ast::node::While && other) const {
        return new ast::node::While{std::move(other)};
    }

    display_result ast::node::While::display () const {
        return
            "while " + util::parenthesized(cynth::display(condition)) +
            " "      + cynth::display(body);
    }

    ast::execution_result ast::node::While::execute (sem::context & ctx) const {
        while (true) {
            auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(ast::evaluate(ctx)(condition))));
            if (!result)
                return ast::make_execution_result(result.error());
            if (*result) {
                auto branch_scope = make_child_context(ctx);
                auto returned = ast::execute(branch_scope)(body);
                if (returned)
                    return *returned;
                if (returned.has_error())
                    return ast::make_execution_result(returned.error());
            } else
                return {};
        }
    }

    //// When ////

    template <>
    void component_deleter<ast::node::When>::operator () (ast::node::When * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::When * component_allocator<ast::node::When>::operator () (ast::node::When const & other) const {
        return new ast::node::When{other};
    }

    template <>
    ast::node::When * component_allocator<ast::node::When>::operator () (ast::node::When && other) const {
        return new ast::node::When{std::move(other)};
    }

    display_result ast::node::When::display () const {
        return
            "when " + util::parenthesized(cynth::display(condition)) +
            " "     + cynth::display(branch);
    }

    ast::execution_result ast::node::When::execute (sem::context & ctx) const {
        auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(ast::evaluate(ctx)(condition))));
        if (!result)
            return ast::make_execution_result(result.error());
        if (*result) {
            auto branch_scope = make_child_context(ctx);
            return ast::execute(branch_scope)(branch);
        }
        return {};
    }

}
