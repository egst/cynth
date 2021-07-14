#include "ast/nodes/statements.hpp"

#include "result.hpp"
#include "ast/nodes/expressions.hpp"
#include "ast/categories/declaration.hpp"
#include "ast/categories/range_decl.hpp"
#include "ast/categories/expression.hpp"
#include "ast/categories/statement.hpp"
#include "ast/categories/type.hpp"
#include "ast/interface.hpp"
#include "asg/interface.hpp"
#include "asg/util.hpp"
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

    std::string ast::node::Assignment::display () const {
        return ast::display(target) + " = " + ast::display(value);
    }

    // TODO: Assigning to array subscripts.
    ast::execution_result ast::node::Assignment::execute (context & ctx) const {
        auto names_result = lift::category_component{asg::eval_name}(target);
        if (!names_result)
            return ast::make_execution_result(names_result.error());
        auto names = *std::move(names_result);

        // TODO: What about .size() == 0? And elsewhere as well...
        if (names.size() > 1)
            return ast::make_execution_result(result_error{"Assigning to tuples of names is not supported yet."});

        auto name = std::move(names)[0];

        auto values_result = util::unite_results(ast::evaluate(ctx)(value));
        if (!values_result)
            return ast::make_execution_result(values_result.error());
        auto values = *std::move(values_result);

        auto value_result = ctx.find_value(name);
        if (!value_result)
            return ast::make_execution_result(result_error{"Name not found."});

        for (auto & type : value_result->type) {
            auto const_check = lift::category{util::overload {
                // TODO: arrays of const values (once assignment by elements is implemented).
                [] (asg::type::Const const &) -> cynth::result<void> {
                    return result_error{"Cannot assign to a const type."};
                },
                [] <typename Type> (Type &&) -> cynth::result<void> requires (!util::same_as_no_cvref<Type, asg::type::Const>) {
                    return {};
                }
            }} (type);
            if (!const_check)
                return ast::make_execution_result(const_check.error());
        }

        auto converted_results = asg::convert(values, value_result->type);
        if (!converted_results)
            return ast::make_execution_result(converted_results.error());
        auto converted_result = util::unite_results(*converted_results);
        if (!converted_result)
            return ast::make_execution_result(converted_result.error());

        value_result->value = *std::move(converted_result);

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

    std::string ast::node::Definition::display () const {
        return ast::display(target) + " = " + ast::display(value);
    }

    ast::execution_result ast::node::Definition::execute (context & ctx) const {
        auto decls_result = util::unite_results(asg::complete(ast::eval_decl(ctx)(target)));
        if (!decls_result)
            return ast::make_execution_result(decls_result.error());
        auto decls = *std::move(decls_result);

        auto values_result = util::unite_results(ast::evaluate(ctx)(value));
        if (!values_result)
            return ast::make_execution_result(values_result.error());
        auto values = *std::move(values_result);

        auto define_result = asg::define(ctx, decls, values);
        if (!define_result)
            return ast::make_execution_result(define_result.error());

        return {};
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

    std::string ast::node::For::display () const {
        return
            "for " + util::parenthesized(util::parenthesized(util::join(", ", ast::display(declarations)))) +
            " "    + ast::display(body);
    }

    ast::execution_result ast::node::For::execute (context & ctx) const {
        return ast::make_execution_result(result_error{"For statement execution not implemented yet."});
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

    std::string ast::node::FunctionDef::display () const {
        return ast::display(output) + " " + ast::display(name) + " " + util::parenthesized(ast::display(input)) + " " + ast::display(body);
    }

    ast::execution_result ast::node::FunctionDef::execute (context & ctx) const {
        auto output_result = util::unite_results(asg::complete(ast::eval_type(ctx)(output)));
        if (!output_result)
            return ast::make_execution_result(output_result.error());
        auto output = *std::move(output_result);

        auto input_result = util::unite_results(asg::complete(ast::eval_decl(ctx)(input)));
        if (!input_result)
            return ast::make_execution_result(input_result.error());
        auto input = *std::move(input_result);

        auto value = util::init<tuple_vector>(asg::value::complete{asg::value::Function {
            .out_type   = make_component_vector(output),
            .parameters = make_component_vector(input),
            .body       = body,
            .capture    = ctx // TODO
        }});

        auto define_result = ctx.define_value(*name->name, value);
        if (!define_result)
            return ast::make_execution_result(define_result.error());

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

    std::string ast::node::If::display () const {
        return
            "if "    + util::parenthesized(ast::display(condition)) +
            " "      + ast::display(positive_branch) +
            " else " + ast::display(negative_branch);
    }

    ast::execution_result ast::node::If::execute (context & ctx) const {
        auto result = asg::get<bool>(asg::convert(asg::type::Bool{})(util::single(ast::evaluate(ctx)(condition))));
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

    std::string ast::node::Return::display () const {
        return "return " + ast::display(value);
    }

    ast::execution_result ast::node::Return::execute (context & ctx) const {
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

    std::string ast::node::TypeDef::display () const {
        return "type " + ast::display(target) + " = " + ast::display(type);
    }

    ast::execution_result ast::node::TypeDef::execute (context & ctx) const {
        std::string name = *target->name;

        auto type_result = util::unite_results(asg::complete(ast::eval_type(ctx)(type)));
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

    std::string ast::node::While::display () const {
        return
            "while " + util::parenthesized(ast::display(condition)) +
            " "      + ast::display(body);
    }

    ast::execution_result ast::node::While::execute (context & ctx) const {
        return ast::make_execution_result(result_error{"While statement execution not implemented yet."});
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

    std::string ast::node::When::display () const {
        return
            "when " + util::parenthesized(ast::display(condition)) +
            " "     + ast::display(branch);
    }

    ast::execution_result ast::node::When::execute (context & ctx) const {
        auto result = asg::get<bool>(asg::convert(asg::type::Bool{})(util::single(ast::evaluate(ctx)(condition))));
        if (!result)
            return ast::make_execution_result(result.error());
        if (*result)
            return ast::execute(ctx)(branch);
        return {};
    }

}
