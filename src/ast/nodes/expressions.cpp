#include "ast/nodes/expressions.hpp"

#include "config.hpp"
#include "lift.hpp"
#include "context.hpp"
#include "ast/categories/array_elem.hpp"
#include "ast/categories/declaration.hpp"
#include "ast/categories/expression.hpp"
#include "ast/categories/statement.hpp"
#include "ast/categories/type.hpp"
#include "ast/categories/range_decl.hpp"
#include "ast/interface.hpp"
#include "ast/interface_types.hpp"
#include "asg/values.hpp"
#include "asg/types.hpp"
#include "asg/targets.hpp"
#include "asg/util.hpp"
#include "util/general.hpp"
#include "util/container.hpp"
#include "util/string.hpp"
#include "util/operations.hpp"

#include <string>

namespace cynth {

    //// Implementation helpers ////

    // Arithmetic operations //

    template <bool Check>
    constexpr auto bin_arith_floats = [] <typename F> (F && f) {
        return [&f] <util::temporary T, util::temporary U> (T && a, U && b) requires (!Check || util::some<asg::value::Float, T, U>) {
            return lift::result{asg::value::make_float} (
                lift::result{std::forward<F>(f)} (
                    asg::get<floating>(asg::convert(asg::type::Float{})(std::move(a))),
                    asg::get<floating>(asg::convert(asg::type::Float{})(std::move(b)))
                )
            );
        };
    };

    template <bool Check>
    constexpr auto bin_arith_ints = [] <typename F> (F && f) {
        return [&f] <util::temporary T, util::temporary U> (T && a, U && b) requires (!Check || util::none<asg::value::Float, T, U>) {
            return lift::result{asg::value::make_int} (
                lift::result{std::forward<F>(f)} (
                    asg::get<integral>(asg::convert(asg::type::Int{})(std::move(a))),
                    asg::get<integral>(asg::convert(asg::type::Int{})(std::move(b)))
                )
            );
        };
    };

    constexpr auto bin_arith = [] <typename I, typename F> (I && i, F && f) {
        return lift::evaluation{util::overload {
            bin_arith_floats<true>(f),
            [&i, &f] <util::temporary T, util::temporary U> (T && a, U && b) -> result<asg::value::complete> requires util::none<asg::value::Float, T, U> {
                auto results = asg::decays(asg::type::Float{})(asg::value_type((a))) || asg::decays(asg::type::Float{})(asg::value_type((b)))
                    ? bin_arith_floats <false>(std::forward<F>(f))(std::move(a), std::move(b))
                    : bin_arith_ints   <false>(std::forward<I>(i))(std::move(a), std::move(b));
                if (!results)
                    return results.error();
                return *results;
            },
        }};
    };

    template <bool Check>
    constexpr auto un_arith_float = [] <typename F> (F && f) {
        return [&f] <util::temporary T> (T && a) requires (!Check || util::same_as_no_cvref<asg::value::Float, T>) {
            return lift::result{asg::value::make_float} (
                lift::result{std::forward<F>(f)} (
                    asg::get<floating>(asg::convert(asg::type::Float{})(std::move(a)))
                )
            );
        };
    };

    template <bool Check>
    constexpr auto un_arith_int = [] <typename F> (F && f) {
        return [&f] <util::temporary T> (T && a) requires (!Check || !util::same_as_no_cvref<asg::value::Float, T>) {
            return lift::result{asg::value::make_int} (
                lift::result{std::forward<F>(f)} (
                    asg::get<integral>(asg::convert(asg::type::Int{})(std::move(a)))
                )
            );
        };
    };

    constexpr auto un_arith = [] <typename I, typename F> (I && i, F && f) {
        return lift::evaluation{util::overload {
            un_arith_float<true>(f),
            [&i, &f] <util::temporary T> (T && a) {
                return asg::decays(asg::type::Float{})(asg::value_type(a))
                    ? un_arith_float <false>(std::forward<F>(f))(std::move(a))
                    : un_arith_int   <false>(std::forward<I>(i))(std::move(a));
            },
        }};
    };

    // Comparison operations //

    constexpr auto compare_same_types = [] <typename F> (F && f) {
        return lift::any_asymetric{util::overload {
            // TODO: Decaying types (T const, T in, T out -> T)
            [&f] <util::temporary T> (T && a, T && b) requires util::same_as_no_cvref<T, asg::value::Bool> {
                return lift::result{asg::value::make_bool} (
                    lift::result{std::forward<F>(f)} (
                        asg::get<bool>(std::move(a)),
                        asg::get<bool>(std::move(b))
                    )
                );
            },
            [&f] <util::temporary T> (T && a, T && b) requires util::same_as_no_cvref<T, asg::value::Int> {
                return lift::result{asg::value::make_bool} (
                    lift::result{std::forward<F>(f)} (
                        asg::get<integral>(std::move(a)),
                        asg::get<integral>(std::move(b))
                    )
                );
            },
            [&f] <util::temporary T> (T && a, T && b) requires util::same_as_no_cvref<T, asg::value::Float> {
                return lift::result{asg::value::make_bool} (
                    lift::result{std::forward<F>(f)} (
                        asg::get<floating>(std::move(a)),
                        asg::get<floating>(std::move(b))
                    )
                );
            },
            [] <util::temporary T> (T &&, T &&) requires util::same_as_no_cvref<T, asg::value::Function> {
                return result<asg::value::complete>{result_error{"Cannot compare functions."}};
            },
            [] <util::temporary T> (T &&, T &&) requires util::same_as_no_cvref<T, asg::value::Array> {
                // TODO
                return result<asg::value::complete>{result_error{"Array comparison not supported yet."}};
            },
            [] <util::temporary T> (T &&, T &&) requires util::same_as_no_cvref<T, asg::value::Buffer> {
                // TODO
                return result<asg::value::complete>{result_error{"Cannot compare buffers"}};
            },
            [] <util::temporary T> (T &&, T &&) requires util::same_as_no_cvref<T, asg::value::String> {
                // TODO
                return result<asg::value::complete>{result_error{"Strings are not supported yet."}};
            },
            [] <util::temporary T> (T &&, T &&) requires util::same_as_no_cvref<T, asg::value::In> {
                // This shouldn't happen unless this overload set is used incorectly.
                return result<asg::value::complete>{result_error{}};
            },
            [] <util::temporary T> (T &&, T &&) requires util::same_as_no_cvref<T, asg::value::Out> {
                // This shouldn't happen unless this overload set is used incorectly.
                return result<asg::value::complete>{result_error{}};
            },
            [] <util::temporary T> (T &&, T &&) requires util::same_as_no_cvref<T, asg::value::Const> {
                // This shouldn't happen unless this overload set is used incorectly.
                return result<asg::value::complete>{result_error{}};
            },
            [] <util::temporary T, util::temporary U> (T &&, U &&) requires asg::interface::value<T> && asg::interface::value<U> && (!util::same_as_no_cvref<T, U>) {
                return result<asg::value::complete>{result_error{"Cannot compare incompatible types."}};
            }
        }};
    };

    constexpr auto compare = [] <typename F> (F && f) {
        //constexpr auto same_types = compare_same_types(std::forward<F>(f));
        //decltype(auto) same_types = std::forward<F>(f);
        return lift::evaluation{util::overload {
            [&f] <util::temporary T> (T && a, T && b) {
                return compare_same_types(std::forward<F>(f))(std::move(a), std::move(b));
            },
            [&f] <util::temporary T, util::temporary U> (T && a, U && b) requires (!util::same_as_no_cvref<T, U>) {
                auto a_type    = asg::value_type(a);
                auto b_type    = asg::value_type(b);
                auto a_decayed = util::coalesce(asg::decay(a_type), std::move(a_type)); // TODO: The lazy trick (with ?:) doesn't work here.
                auto b_decayed = util::coalesce(asg::decay(b_type), std::move(b_type));
                return compare_same_types (
                    std::forward<F>(f))(asg::convert_to(std::move(a))(std::move(a_decayed)),
                    asg::convert_to(std::move(b))(std::move(b_decayed))
                );
            }
        }};
    };

    constexpr auto add = bin_arith(util::add, util::add);
    constexpr auto sub = bin_arith(util::sub, util::sub);
    constexpr auto mul = bin_arith(util::mul, util::mul);
    constexpr auto div = bin_arith(util::div, util::div);
    constexpr auto pow = bin_arith(util::pow, util::pow);
    constexpr auto mod = bin_arith(util::mod, util::fmod);

    constexpr auto plus  = un_arith(util::plus,  util::plus);
    constexpr auto minus = un_arith(util::minus, util::minus);

    constexpr auto eq = compare(util::eq);
    constexpr auto ne = compare(util::ne);
    constexpr auto gt = compare(util::gt);
    constexpr auto lt = compare(util::lt);
    constexpr auto ge = compare(util::ge);
    constexpr auto le = compare(util::le);

    // Arrays //


    //// Add ////

    template <>
    void component_deleter<ast::node::Add>::operator () (ast::node::Add * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Add * component_allocator<ast::node::Add>::operator () (ast::node::Add const & other) const {
        return new ast::node::Add{other};
    }

    template <>
    ast::node::Add * component_allocator<ast::node::Add>::operator () (ast::node::Add && other) const {
        return new ast::node::Add{std::move(other)};
    }

    ast::display_result ast::node::Add::display () const {
        return "(" + ast::display(left_argument) + " + " + ast::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Add::evaluate (context & ctx) const {
        auto results = add(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
        if (!results)
            return ast::make_evaluation_result(results.error());
        return *results;
    }

    //// And ////

    template <>
    void component_deleter<ast::node::And>::operator () (ast::node::And * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::And * component_allocator<ast::node::And>::operator () (ast::node::And const & other) const {
        return new ast::node::And{other};
    }

    template <>
    ast::node::And * component_allocator<ast::node::And>::operator () (ast::node::And && other) const {
        return new ast::node::And{std::move(other)};
    }

    std::string ast::node::And::display () const {
        return "(" + ast::display(left_argument) + " && " + ast::display(right_argument) + ")";
    }

    // TODO: This implementation doesn't work on tuples.
    ast::evaluation_result ast::node::And::evaluate (context & ctx) const {
        auto llhs = lazy{[this, &ctx] {
            return asg::get<bool>(asg::convert(asg::type::Bool{})(util::single(ast::evaluate(ctx)(left_argument))));
        }};
        auto lrhs = lazy{[this, &ctx] {
            return asg::get<bool>(asg::convert(asg::type::Bool{})(util::single(ast::evaluate(ctx)(right_argument))));
        }};
        return ast::make_evaluation_result(lift::result{asg::value::make_bool}(util::land(llhs, lrhs)));
    }

    //// Application ////

    template <>
    void component_deleter<ast::node::Application>::operator () (ast::node::Application * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Application * component_allocator<ast::node::Application>::operator () (ast::node::Application const & other) const {
        return new ast::node::Application{other};
    }

    template <>
    ast::node::Application * component_allocator<ast::node::Application>::operator () (ast::node::Application && other) const {
        return new ast::node::Application{std::move(other)};
    }

    std::string ast::node::Application::display () const {
        return ast::display(function) + util::parenthesized(ast::display(arguments));
    }

    // TODO: Segmentation fault.
    ast::evaluation_result ast::node::Application::evaluate (context & ctx) const {
        // Definition:
        auto definition_result = asg::get<asg::value::Function>(util::single(ast::evaluate(ctx)(function)));
        // TODO: Check if evaluated to a function?
        if (!definition_result)
            return ast::make_evaluation_result(definition_result.error());
        auto definition = *std::move(definition_result);

        // Arguments:
        auto args_result = util::unite_results(ast::evaluate(ctx)(arguments));
        if (!args_result)
            return ast::make_evaluation_result(args_result.error());
        auto args = *std::move(args_result);

        // Init nested scope:
        //auto function_scope = ctx;
        auto function_scope = make_child_context(*definition.capture);

        // Parameters:
        /*auto params_result = util::unite_results(asg::complete(ast::eval_decl(function_scope)(definition.input)));
        if (!params_result)
            return ast::make_evaluation_result(params_result.error());
        auto params = *std::move(params_result);*/
        auto params = std::move(definition.parameters);

        auto paramdef_result = asg::define(function_scope, params, args);
        if (!paramdef_result)
            return ast::make_evaluation_result(paramdef_result.error());

        auto body_result = util::unite_results(ast::evaluate(function_scope)(definition.body));
        if (!body_result)
            return ast::make_evaluation_result(body_result.error());
        auto body = *std::move(body_result);
        //auto type = asg::complete(ast::eval_type(function_scope)(definition.output));
        auto type = std::move(definition.out_type);

        auto results = asg::convert(std::move(body), std::move(type));
        if (!results)
            return ast::make_evaluation_result(results.error());
        return *results;
    }

    //// Array ////

    template <>
    void component_deleter<ast::node::Array>::operator () (ast::node::Array * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Array * component_allocator<ast::node::Array>::operator () (ast::node::Array const & other) const {
        return new ast::node::Array{other};
    }

    template <>
    ast::node::Array * component_allocator<ast::node::Array>::operator () (ast::node::Array && other) const {
        return new ast::node::Array{std::move(other)};
    }

    std::string ast::node::Array::display () const {
        return "[" + util::join(", ", ast::display(elements)) + "]";
    }

    ast::evaluation_result ast::node::Array::evaluate (context & ctx) const {
        auto result = asg::array_elems(ctx, elements);
        if (!result)
            return ast::make_evaluation_result(result.error());
        auto [values, type] = *std::move(result);

        // Note: There were some unresolved issues in the standard with lambda-capturing structured bindings,
        // which should now (as of C++20?) be resolved, but clang (10) still hasn't implemented the changes. (Maybe clang 11?)
        // So until it's fixed in clang, the workaround is to do a capture with an initializer: [&type = type]

        auto converted_result = util::unite_results(lift::component{
            [&type = type] <typename T> (T && value) -> cynth::result<tuple_vector<asg::value::complete>> {
                auto result = asg::convert(std::forward<T>(value), type);
                if (!result)
                    return result.error();
                return util::unite_results(*result);
            }
        } (values));
        if (!converted_result)
            return ast::make_evaluation_result(converted_result.error());
        auto converted = *std::move(converted_result);
        auto stored = ctx.store_value(asg::value::ArrayValue {
            .value = converted
        });
        if (!stored)
            return ast::make_evaluation_result(stored.error());

        auto array_result = asg::value::make_array (
            stored.get(),
            make_component_vector(std::move(type)),
            static_cast<integral>(stored->value.size())
        );
        if (!array_result)
            return ast::make_evaluation_result(array_result.error());
        return ast::make_evaluation_result(*array_result);
    }

    //// Block ////

    template <>
    void component_deleter<ast::node::Block>::operator () (ast::node::Block * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Block * component_allocator<ast::node::Block>::operator () (ast::node::Block const & other) const {
        return new ast::node::Block{other};
    }

    template <>
    ast::node::Block * component_allocator<ast::node::Block>::operator () (ast::node::Block && other) const {
        return new ast::node::Block{std::move(other)};
    }

    std::string ast::node::Block::display () const {
        return statements.empty()
            ? "{}"
            : "{\n" + util::join(";\n", ast::display(statements)) + "\n}";
    }

    // TODO: Is there really a need for separate evaluate and execute implementation?
    // It seems like it should naturally be the same thing (except for the mandatory return in evaluation).

    ast::evaluation_result ast::node::Block::evaluate (context & ctx) const {
        auto block_scope = make_child_context(ctx);

        for (auto & statement : statements) {
            auto returned = ast::execute(block_scope)(statement);
            if (returned)
                return lift::tuple_vector{make_result}(*returned);
            if (returned.has_error())
                return ast::make_evaluation_result(returned.error());
        }

        //return ast::make_evaluation_result(result_error{"Evaluated block does not return."});
        return {}; // Return the void value.
    }

    ast::execution_result ast::node::Block::execute (context & ctx) const {
        auto block_scope = make_child_context(ctx);

        for (auto & statement : statements) {
            auto returned = ast::execute(block_scope)(statement);
            if (returned)
                return *returned;
            if (returned.has_error())
                return ast::make_execution_result(returned.error());
        }

        return {};
    }

    //// Bool ////

    template <>
    void component_deleter<ast::node::Bool>::operator () (ast::node::Bool * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Bool * component_allocator<ast::node::Bool>::operator () (ast::node::Bool const & other) const {
        return new ast::node::Bool{other};
    }

    template <>
    ast::node::Bool * component_allocator<ast::node::Bool>::operator () (ast::node::Bool && other) const {
        return new ast::node::Bool{std::move(other)};
    }

    std::string ast::node::Bool::display () const {
        return value ? "true" : "false";
    }

    ast::evaluation_result ast::node::Bool::evaluate (context &) const {
        return ast::make_evaluation_result(asg::value::make_bool(value));
    }

    //// Conversion ////

    template <>
    void component_deleter<ast::node::Conversion>::operator () (ast::node::Conversion * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Conversion * component_allocator<ast::node::Conversion>::operator () (ast::node::Conversion const & other) const {
        return new ast::node::Conversion{other};
    }

    template <>
    ast::node::Conversion * component_allocator<ast::node::Conversion>::operator () (ast::node::Conversion && other) const {
        return new ast::node::Conversion{std::move(other)};
    }

    std::string ast::node::Conversion::display () const {
        return ast::display(type) + util::parenthesized(ast::display(argument));
    }

    // TODO: Check with all the types as soon as I fix them.
    ast::evaluation_result ast::node::Conversion::evaluate (context & ctx) const {
        auto result = asg::convert(ast::evaluate(ctx)(argument), asg::complete(ast::eval_type(ctx)(type)));
        if (!result)
            return ast::make_evaluation_result(result.error());
        return *result;
    }

    //// Div ///

    template <>
    void component_deleter<ast::node::Div>::operator () (ast::node::Div * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Div * component_allocator<ast::node::Div>::operator () (ast::node::Div const & other) const {
        return new ast::node::Div{other};
    }

    template <>
    ast::node::Div * component_allocator<ast::node::Div>::operator () (ast::node::Div && other) const {
        return new ast::node::Div{std::move(other)};
    }

    std::string ast::node::Div::display () const {
        return "(" + ast::display(left_argument) + " / " + ast::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Div::evaluate (context & ctx) const {
        auto results = div(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
        if (!results)
            return ast::make_evaluation_result(results.error());
        return *results;
    }

    //// Eq ///

    template <>
    void component_deleter<ast::node::Eq>::operator () (ast::node::Eq * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Eq * component_allocator<ast::node::Eq>::operator () (ast::node::Eq const & other) const {
        return new ast::node::Eq{other};
    }

    template <>
    ast::node::Eq * component_allocator<ast::node::Eq>::operator () (ast::node::Eq && other) const {
        return new ast::node::Eq{std::move(other)};
    }

    std::string ast::node::Eq::display () const {
        return "(" + ast::display(left_argument) + " == " + ast::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Eq::evaluate (context & ctx) const {
        auto results = eq(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
        if (!results)
            return ast::make_evaluation_result(results.error());
        return *results;
    }

    //// ExprFor ////

    template <>
    void component_deleter<ast::node::ExprFor>::operator () (ast::node::ExprFor * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::ExprFor * component_allocator<ast::node::ExprFor>::operator () (ast::node::ExprFor const & other) const {
        return new ast::node::ExprFor{other};
    }

    template <>
    ast::node::ExprFor * component_allocator<ast::node::ExprFor>::operator () (ast::node::ExprFor && other) const {
        return new ast::node::ExprFor{std::move(other)};
    }

    std::string ast::node::ExprFor::display () const {
        return
            "for " + util::parenthesized(ast::display(declarations)) +
            " "    + ast::display(body);
    }

    ast::evaluation_result ast::node::ExprFor::evaluate (context & ctx) const {
        auto decls_result = asg::for_decls(ctx, *declarations);
        if (!decls_result)
            return ast::make_evaluation_result(decls_result.error());
        auto [size, iter_decls] = *std::move(decls_result);

        asg::array_vector              result_values;
        std::optional<asg::array_type> result_type;

        result_values.reserve(size);

        for (integral i = 0; i < size; ++i) {
            // Init inner scope:
            auto iter_scope = make_child_context(ctx);

            // Define iteration elements:
            for (auto & [decl, value] : iter_decls)
                asg::define(iter_scope, decl, value.value->value[i]);

            // Evaluate the loop body:
            auto value_result = util::unite_results(ast::evaluate(iter_scope)(body));
            if (!value_result)
                return ast::make_evaluation_result(value_result.error());

            auto & value = *value_result;
            auto   type  = asg::value_type(value);

            if (result_type) {
                auto common_results = asg::common(type, *result_type);
                if (!common_results)
                    return ast::make_evaluation_result(common_results.error());
                result_type = result_to_optional(util::unite_results(*common_results));
            } else {
                result_type = std::optional{std::move(type)};
            }

            result_values.push_back(std::move(value));
        }

        if (!result_type)
            return ast::make_evaluation_result(result_error{"No common type for an array in a for expression."});

        auto stored = ctx.store_value(asg::value::ArrayValue {
            .value = result_values
        });
        if (!stored)
            return ast::make_evaluation_result(stored.error());

        auto result = asg::value::make_array (
            stored.get(),
            *std::move(result_type),
            static_cast<integral>(stored->value.size())
        );
        if (!result)
            return ast::make_evaluation_result(result.error());
        return ast::make_evaluation_result(*result);
    }

    ast::execution_result ast::node::ExprFor::execute (context & ctx) const {
        auto decls_result = asg::for_decls(ctx, *declarations);
        if (!decls_result)
            return ast::make_execution_result(decls_result.error());
        auto [size, iter_decls] = *std::move(decls_result);

        for (integral i = 0; i < size; ++i) {
            // Init inner scope:
            auto iter_scope = make_child_context(ctx);

            // Define iteration elements:
            for (auto & [decl, value] : iter_decls)
                asg::define(iter_scope, decl, value.value->value[i]);

            // Execute the loop body:
            auto returned = ast::execute(iter_scope)(body);

            if (returned)
                return *returned;
            if (returned.has_error())
                return ast::make_execution_result(returned.error());
        }

        return {};
    }

    //// ExprIf ////

    template <>
    void component_deleter<ast::node::ExprIf>::operator () (ast::node::ExprIf * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::ExprIf * component_allocator<ast::node::ExprIf>::operator () (ast::node::ExprIf const & other) const {
        return new ast::node::ExprIf{other};
    }

    template <>
    ast::node::ExprIf * component_allocator<ast::node::ExprIf>::operator () (ast::node::ExprIf && other) const {
        return new ast::node::ExprIf{std::move(other)};
    }

    std::string ast::node::ExprIf::display () const {
        return
            "if "    + util::parenthesized(ast::display(condition)) +
            " "      + ast::display(positive_branch) +
            " else " + ast::display(negative_branch);
    }

    ast::evaluation_result ast::node::ExprIf::evaluate (context & ctx) const {
        auto result = asg::get<bool>(asg::convert(asg::type::Bool{})(util::single(ast::evaluate(ctx)(condition))));
        if (!result)
            return ast::make_evaluation_result(result.error());
        if (*result)
            return ast::evaluate(ctx)(positive_branch);
        else
            return ast::evaluate(ctx)(negative_branch);
    }

    ast::execution_result ast::node::ExprIf::execute (context & ctx) const {
        auto result = asg::get<bool>(asg::convert(asg::type::Bool{})(util::single(ast::evaluate(ctx)(condition))));
        if (!result)
            return ast::make_execution_result(result.error());
        if (*result) {
            auto branch_scope = make_child_context(ctx);
            return ast::execute(branch_scope)(positive_branch);
        } else {
            auto branch_scope = make_child_context(ctx);
            return ast::execute(branch_scope)(negative_branch);
        }
    }

    //// Float ////

    template <>
    void component_deleter<ast::node::Float>::operator () (ast::node::Float * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Float * component_allocator<ast::node::Float>::operator () (ast::node::Float const & other) const {
        return new ast::node::Float{other};
    }

    template <>
    ast::node::Float * component_allocator<ast::node::Float>::operator () (ast::node::Float && other) const {
        return new ast::node::Float{std::move(other)};
    }

    std::string ast::node::Float::display () const {
        return std::to_string(value);
    }

    ast::evaluation_result ast::node::Float::evaluate (context &) const {
        return ast::make_evaluation_result(asg::value::make_float(value));
    }

    //// Function ////

    template <>
    void component_deleter<ast::node::Function>::operator () (ast::node::Function * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Function * component_allocator<ast::node::Function>::operator () (ast::node::Function const & other) const {
        return new ast::node::Function{other};
    }

    template <>
    ast::node::Function * component_allocator<ast::node::Function>::operator () (ast::node::Function && other) const {
        return new ast::node::Function{std::move(other)};
    }

    std::string ast::node::Function::display () const {
        return ast::display(output) + " fn " + util::parenthesized(ast::display(input)) + " " + ast::display(body);
    }

    // TODO: Test as soon as I fix function application.
    ast::evaluation_result ast::node::Function::evaluate (context & ctx) const {
        auto out_type = util::unite_results(asg::complete(ast::eval_type(ctx)(output)));
        if (!out_type)
            return ast::make_evaluation_result(out_type.error());
        auto parameters = util::unite_results(asg::complete(ast::eval_decl(ctx)(input)));
        if (!parameters)
            return ast::make_evaluation_result(parameters.error());
        return ast::make_evaluation_result(asg::value::complete{asg::value::Function {
            .out_type   = component_vector<asg::type::complete> {*std::move(out_type)},
            .parameters = component_vector<asg::complete_decl>  {*std::move(parameters)},
            .body       = body,
            .capture    = ctx // TODO: copy-on-write references
        }});
    }

    //// Ge ////

    template <>
    void component_deleter<ast::node::Ge>::operator () (ast::node::Ge * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Ge * component_allocator<ast::node::Ge>::operator () (ast::node::Ge const & other) const {
        return new ast::node::Ge{other};
    }

    template <>
    ast::node::Ge * component_allocator<ast::node::Ge>::operator () (ast::node::Ge && other) const {
        return new ast::node::Ge{std::move(other)};
    }

    std::string ast::node::Ge::display () const {
        return "(" + ast::display(left_argument) + " >= " + ast::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Ge::evaluate (context & ctx) const {
        auto results = ge(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
        if (!results)
            return ast::make_evaluation_result(results.error());
        return *results;
    }

    //// Gt ////

    template <>
    void component_deleter<ast::node::Gt>::operator () (ast::node::Gt * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Gt * component_allocator<ast::node::Gt>::operator () (ast::node::Gt const & other) const {
        return new ast::node::Gt{other};
    }

    template <>
    ast::node::Gt * component_allocator<ast::node::Gt>::operator () (ast::node::Gt && other) const {
        return new ast::node::Gt{std::move(other)};
    }

    std::string ast::node::Gt::display () const {
        return "(" + ast::display(left_argument) + " > " + ast::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Gt::evaluate (context & ctx) const {
        auto results = gt(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
        if (!results)
            return ast::make_evaluation_result(results.error());
        return *results;
    }

    //// Int ////

    template <>
    void component_deleter<ast::node::Int>::operator () (ast::node::Int * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Int * component_allocator<ast::node::Int>::operator () (ast::node::Int const & other) const {
        return new ast::node::Int{other};
    }

    template <>
    ast::node::Int * component_allocator<ast::node::Int>::operator () (ast::node::Int && other) const {
        return new ast::node::Int{std::move(other)};
    }

    std::string ast::node::Int::display () const {
        return std::to_string(value);
    }

    ast::evaluation_result ast::node::Int::evaluate (context &) const {
        return ast::make_evaluation_result(asg::value::make_int(value));
    }

    //// Le ////

    template <>
    void component_deleter<ast::node::Le>::operator () (ast::node::Le * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Le * component_allocator<ast::node::Le>::operator () (ast::node::Le const & other) const {
        return new ast::node::Le{other};
    }

    template <>
    ast::node::Le * component_allocator<ast::node::Le>::operator () (ast::node::Le && other) const {
        return new ast::node::Le{std::move(other)};
    }

    std::string ast::node::Le::display () const {
        return "(" + ast::display(left_argument) + " <= " + ast::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Le::evaluate (context & ctx) const {
        auto results = le(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
        if (!results)
            return ast::make_evaluation_result(results.error());
        return *results;
    }

    //// Lt ////

    template <>
    void component_deleter<ast::node::Lt>::operator () (ast::node::Lt * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Lt * component_allocator<ast::node::Lt>::operator () (ast::node::Lt const & other) const {
        return new ast::node::Lt{other};
    }

    template <>
    ast::node::Lt * component_allocator<ast::node::Lt>::operator () (ast::node::Lt && other) const {
        return new ast::node::Lt{std::move(other)};
    }

    std::string ast::node::Lt::display () const {
        return "(" + ast::display(left_argument) + " < " + ast::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Lt::evaluate (context & ctx) const {
        auto results = lt(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
        if (!results)
            return ast::make_evaluation_result(results.error());
        return *results;
    }

    //// Minus ////

    template <>
    void component_deleter<ast::node::Minus>::operator () (ast::node::Minus * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Minus * component_allocator<ast::node::Minus>::operator () (ast::node::Minus const & other) const {
        return new ast::node::Minus{other};
    }

    template <>
    ast::node::Minus * component_allocator<ast::node::Minus>::operator () (ast::node::Minus && other) const {
        return new ast::node::Minus{std::move(other)};
    }

    std::string ast::node::Minus::display () const {
        return "-" + ast::display(argument);
    }

    ast::evaluation_result ast::node::Minus::evaluate (context & ctx) const {
        return minus(ast::evaluate(ctx)(argument));
    }

    //// Mod ////

    template <>
    void component_deleter<ast::node::Mod>::operator () (ast::node::Mod * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Mod * component_allocator<ast::node::Mod>::operator () (ast::node::Mod const & other) const {
        return new ast::node::Mod{other};
    }

    template <>
    ast::node::Mod * component_allocator<ast::node::Mod>::operator () (ast::node::Mod && other) const {
        return new ast::node::Mod{std::move(other)};
    }

    std::string ast::node::Mod::display () const {
        return "(" + ast::display(left_argument) + " % " + ast::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Mod::evaluate (context & ctx) const {
        auto results = mod(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
        if (!results)
            return ast::make_evaluation_result(results.error());
        return *results;
    }

    //// Mul ////

    template <>
    void component_deleter<ast::node::Mul>::operator () (ast::node::Mul * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Mul * component_allocator<ast::node::Mul>::operator () (ast::node::Mul const & other) const {
        return new ast::node::Mul{other};
    }

    template <>
    ast::node::Mul * component_allocator<ast::node::Mul>::operator () (ast::node::Mul && other) const {
        return new ast::node::Mul{std::move(other)};
    }

    std::string ast::node::Mul::display () const {
        return "(" + ast::display(left_argument) + " * " + ast::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Mul::evaluate (context & ctx) const {
        auto results = mul(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
        if (!results)
            return ast::make_evaluation_result(results.error());
        return *results;
    }

    //// Name ////

    template <>
    void component_deleter<ast::node::Name>::operator () (ast::node::Name * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Name * component_allocator<ast::node::Name>::operator () (ast::node::Name const & other) const {
        return new ast::node::Name{other};
    }

    template <>
    ast::node::Name * component_allocator<ast::node::Name>::operator () (ast::node::Name && other) const {
        return new ast::node::Name{std::move(other)};
    }

    std::string ast::node::Name::display () const {
        return *name;
    }

    ast::evaluation_result ast::node::Name::evaluate (context & ctx) const {
        auto value = ctx.find_value(*name);
        return value
            ? lift::tuple_vector{make_result}(value->value)
            : ast::make_evaluation_result(result_error{"Name not found."});
    }

    ast::target_eval_result ast::node::Name::eval_target (context & ctx) const {
        auto result = ctx.find_value(*name);
        if (!result)
            return ast::make_target_eval_result(result_error{"Target name not found."});
        return ast::make_target_eval_result(asg::any_target{asg::direct_target {
            .value = *result
        }});
    }

    //// Ne ////

    template <>
    void component_deleter<ast::node::Ne>::operator () (ast::node::Ne * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Ne * component_allocator<ast::node::Ne>::operator () (ast::node::Ne const & other) const {
        return new ast::node::Ne{other};
    }

    template <>
    ast::node::Ne * component_allocator<ast::node::Ne>::operator () (ast::node::Ne && other) const {
        return new ast::node::Ne{std::move(other)};
    }

    std::string ast::node::Ne::display () const {
        return "(" + ast::display(left_argument) + " != " + ast::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Ne::evaluate (context & ctx) const {
        auto results = ne(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
        if (!results)
            return ast::make_evaluation_result(results.error());
        return *results;
    }

    //// Not ////

    template <>
    void component_deleter<ast::node::Not>::operator () (ast::node::Not * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Not * component_allocator<ast::node::Not>::operator () (ast::node::Not const & other) const {
        return new ast::node::Not{other};
    }

    template <>
    ast::node::Not * component_allocator<ast::node::Not>::operator () (ast::node::Not && other) const {
        return new ast::node::Not{std::move(other)};
    }

    std::string ast::node::Not::display () const {
        return "!" + ast::display(argument);
    }

    ast::evaluation_result ast::node::Not::evaluate (context & ctx) const {
        return lift::evaluation {
            [] <util::temporary T> (T && a) {
                return lift::result{asg::value::make_bool} (
                    lift::result{util::lnot} (
                        asg::get<bool>(asg::convert(asg::type::Bool{})(std::move(a)))
                    )
                );
            },
        }(ast::evaluate(ctx)(argument));
    }

    //// Or ////

    template <>
    void component_deleter<ast::node::Or>::operator () (ast::node::Or * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Or * component_allocator<ast::node::Or>::operator () (ast::node::Or const & other) const {
        return new ast::node::Or{other};
    }

    template <>
    ast::node::Or * component_allocator<ast::node::Or>::operator () (ast::node::Or && other) const {
        return new ast::node::Or{std::move(other)};
    }

    std::string ast::node::Or::display () const {
        return "(" + ast::display(left_argument) + " || " + ast::display(right_argument) + ")";
    }

    // TODO: This implementation doesn't work on tuples.
    ast::evaluation_result ast::node::Or::evaluate (context & ctx) const {
        auto llhs = lazy{[this, &ctx] {
            return asg::get<bool>(asg::convert(asg::type::Bool{})(util::single(ast::evaluate(ctx)(left_argument))));
        }};
        auto lrhs = lazy{[this, &ctx] {
            return asg::get<bool>(asg::convert(asg::type::Bool{})(util::single(ast::evaluate(ctx)(right_argument))));
        }};
        return util::init<tuple_vector>(lift::result{asg::value::make_bool}(util::lor(llhs, lrhs)));
    }

    //// Plus ////

    template <>
    void component_deleter<ast::node::Plus>::operator () (ast::node::Plus * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Plus * component_allocator<ast::node::Plus>::operator () (ast::node::Plus const & other) const {
        return new ast::node::Plus{other};
    }

    template <>
    ast::node::Plus * component_allocator<ast::node::Plus>::operator () (ast::node::Plus && other) const {
        return new ast::node::Plus{std::move(other)};
    }

    std::string ast::node::Plus::display () const {
        return "+" + ast::display(argument);
    }

    ast::evaluation_result ast::node::Plus::evaluate (context & ctx) const {
        return plus(ast::evaluate(ctx)(argument));
    }

    //// Pow ////

    template <>
    void component_deleter<ast::node::Pow>::operator () (ast::node::Pow * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Pow * component_allocator<ast::node::Pow>::operator () (ast::node::Pow const & other) const {
        return new ast::node::Pow{other};
    }

    template <>
    ast::node::Pow * component_allocator<ast::node::Pow>::operator () (ast::node::Pow && other) const {
        return new ast::node::Pow{std::move(other)};
    }

    std::string ast::node::Pow::display () const {
        return "(" + ast::display(left_argument) + " ** " + ast::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Pow::evaluate (context & ctx) const {
        auto results = pow(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
        if (!results)
            return ast::make_evaluation_result(results.error());
        return *results;
    }

    //// String ////

    template <>
    void component_deleter<ast::node::String>::operator () (ast::node::String * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::String * component_allocator<ast::node::String>::operator () (ast::node::String const & other) const {
        return new ast::node::String{other};
    }

    template <>
    ast::node::String * component_allocator<ast::node::String>::operator () (ast::node::String && other) const {
        return new ast::node::String{std::move(other)};
    }

    std::string ast::node::String::display () const {
        //return "\"" + value + "\"";
        return "\"" + *value + "\"";
    }

    ast::evaluation_result ast::node::String::evaluate (context &) const {
        return ast::make_evaluation_result(result_error{"Strings are not supported yet."});
    }

    //// Sub ////

    template <>
    void component_deleter<ast::node::Sub>::operator () (ast::node::Sub * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Sub * component_allocator<ast::node::Sub>::operator () (ast::node::Sub const & other) const {
        return new ast::node::Sub{other};
    }

    template <>
    ast::node::Sub * component_allocator<ast::node::Sub>::operator () (ast::node::Sub && other) const {
        return new ast::node::Sub{std::move(other)};
    }

    std::string ast::node::Sub::display () const {
        return "(" + ast::display(left_argument) + " - " + ast::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Sub::evaluate (context & ctx) const {
        auto results = sub(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
        if (!results)
            return ast::make_evaluation_result(results.error());
        return *results;
    }

    //// Subscript ////

    template <>
    void component_deleter<ast::node::Subscript>::operator () (ast::node::Subscript * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Subscript * component_allocator<ast::node::Subscript>::operator () (ast::node::Subscript const & other) const {
        return new ast::node::Subscript{other};
    }

    template <>
    ast::node::Subscript * component_allocator<ast::node::Subscript>::operator () (ast::node::Subscript && other) const {
        return new ast::node::Subscript{std::move(other)};
    }

    std::string ast::node::Subscript::display () const {
        return ast::display(container) + " [" + util::join(", ", ast::display(location)) + "]";
    }

    // TODO: error: Single item expected.
    // TODO: This implementation only allows the simple c-like subscript a[i] with a single index on a single (non-tuple) value.
    // TODO: What about subscript on the lhs of an assignment (a[i] = x)?
    ast::evaluation_result ast::node::Subscript::evaluate (context & ctx) const {
        //ast::evaluate(container);
        //return asg::get<bool>(lift::single_evaluation{asg::convert(asg::type::Bool{})}(util::single(location)));
        auto location_result = asg::array_elems(ctx, location);
        if (!location_result)
            return ast::make_evaluation_result(location_result.error());
        auto [locations, location_type] = *location_result;

        // TODO: Check the location_type?
        // Simplification: only the first location is taken.
        // (the util::single(locastions) part is the simplification.
        // lift::result{util::single} corresponds to an intended behaviour, not a simplification.)
        //auto r = asg::convert(asg::type::Int{})(util::single(locations));

        auto index_result = asg::get<integral> (
            asg::convert(asg::type::Int{})(lift::result{util::single}(util::single(locations)))
        );
        if (!index_result)
            return ast::make_evaluation_result(index_result.error());
        integral index = *index_result;

        // Simplification: only the first container is taken:
        using result_type = result<tuple_vector<asg::value::complete>>;
        auto result = lift::single_evaluation{util::overload {
            [index] (asg::value::Array const & a) -> result_type {
                integral size = a.size;
                if (index >= size)
                    return {result_error{"Subscript index out of bounds."}};
                if (index < 0)
                    return {result_error{"Negative subscripts not supported yet."}};
                auto results = asg::convert(a.value->value[index], a.type);
                if (!results)
                    return results.error();
                return util::unite_results(*results);
            },
            [] (auto const &) -> result_type {
                return {result_error{"Cannot subscript a non-array value."}};
            }
        }} (util::single(ast::evaluate(ctx)(container)));
        if (!result)
            return ast::make_evaluation_result(result.error());

        return lift::tuple_vector{make_result}(*result);
    }

    ast::target_eval_result ast::node::Subscript::eval_target (context & ctx) const {
        // Only the first container is taken. (This is the intended behaviour, not a simplification.)
        auto container_result = lift::result{util::single}(ast::eval_target(ctx)(container));
        if (!container_result)
            return ast::make_target_eval_result(container_result.error());

        auto location_result = asg::array_elems(ctx, location);
        if (!location_result)
            return ast::make_target_eval_result(location_result.error());
        auto [locations, location_type] = *std::move(location_result);

        if (locations.size() == 0)
            return ast::make_target_eval_result(asg::any_target{asg::subscript_target {
                .container = *container_result,
                .location  = {}
            }});

        // Simplification: Only the first location is taken.
        auto index_result = util::unite_results (
            asg::convert(asg::type::Int{})(lift::component{util::single}(locations))
        );
        if (!index_result)
            return ast::make_target_eval_result(index_result.error());

        return ast::make_target_eval_result(asg::any_target{asg::subscript_target {
            .container = *container_result,
            .location  = *index_result
        }});
    }

    //// Tuple ////

    template <>
    void component_deleter<ast::node::Tuple>::operator () (ast::node::Tuple * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Tuple * component_allocator<ast::node::Tuple>::operator () (ast::node::Tuple const & other) const {
        return new ast::node::Tuple{other};
    }

    template <>
    ast::node::Tuple * component_allocator<ast::node::Tuple>::operator () (ast::node::Tuple && other) const {
        return new ast::node::Tuple{std::move(other)};
    }

    std::string ast::node::Tuple::display () const {
        return "(" + util::join(", ", ast::display(values)) + ")";
    }

    ast::evaluation_result ast::node::Tuple::evaluate (context & ctx) const {
        ast::evaluation_result result;
        for (auto & value_tuple : ast::evaluate(ctx)(values)) for (auto & value : value_tuple) {
            result.push_back(std::move(value));
        }
        return result;
    }

    ast::target_eval_result ast::node::Tuple::eval_target (context & ctx) const {
        tuple_vector<asg::any_target> result;
        auto values_result = util::unite_results(ast::eval_target(ctx)(values));
        if (!values_result)
            return ast::make_target_eval_result(values_result.error());
        for (auto & value_tuple : *values_result) for (auto & value : value_tuple) {
            result.push_back(std::move(value));
        }
        return result;
    }

}
