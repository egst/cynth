#include "ast/nodes/expressions.hpp"

#include "component.hpp"
#include "config.hpp"
#include "lift.hpp"
#include "ast/categories/array_elem.hpp"
#include "ast/categories/declaration.hpp"
#include "ast/categories/expression.hpp"
#include "ast/categories/statement.hpp"
#include "ast/categories/type.hpp"
#include "ast/categories/range_decl.hpp"
#include "ast/interface.hpp"
#include "ast/interface_types.hpp"
#include "sem/context.hpp"
#include "sem/values.hpp"
#include "sem/types.hpp"
#include "sem/targets.hpp"
#include "sem/util.hpp"
#include "util/general.hpp"
#include "util/container.hpp"
#include "util/string.hpp"
#include "util/operations.hpp"

#include <string>

using namespace std::string_literals;

namespace cynth {

    //// Implementation helpers ////

    // Arithmetic operations //

    template <bool Check>
    constexpr auto bin_arith_floats = [] <typename F> (sem::context & ctx, F && f) {
        return [&ctx, &f] <util::temporary T, util::temporary U> (T && a, U && b) requires (!Check || util::some<sem::value::Float, T, U>) {
            return lift::result{sem::value::make_float} (
                lift::result{std::forward<F>(f)} (
                    sem::get<floating>(sem::convert(ctx)(sem::type::Float{})(std::move(a))),
                    sem::get<floating>(sem::convert(ctx)(sem::type::Float{})(std::move(b)))
                )
            );
        };
    };

    template <bool Check>
    constexpr auto bin_arith_ints = [] <typename F> (sem::context & ctx, F && f) {
        return [&ctx, &f] <util::temporary T, util::temporary U> (T && a, U && b) requires (!Check || util::none<sem::value::Float, T, U>) {
            return lift::result{sem::value::make_int} (
                lift::result{std::forward<F>(f)} (
                    sem::get<integral>(sem::convert(ctx)(sem::type::Int{})(std::move(a))),
                    sem::get<integral>(sem::convert(ctx)(sem::type::Int{})(std::move(b)))
                )
            );
        };
    };

    constexpr auto bin_arith = [] <typename I, typename F> (sem::context & ctx, I && i, F && f) {
        return [&ctx, &i, &f] (util::temporary auto && first, util::temporary auto && second) -> result<tuple_vector<result<sem::value::complete>>> {
            if (first.size() == 0)
                return ast::make_evaluation_result(result_error{"Cannot use the void value on the lhs of a binary operation."});
            if (second.size() == 0)
                return ast::make_evaluation_result(result_error{"Cannot use the void value on the lhs of a binary operation."});
            if (first.size() > second.size())
                return ast::make_evaluation_result(result_error{"More values on the lhs of a binary operation."});
            if (first.size() < second.size())
                return ast::make_evaluation_result(result_error{"More values on the rhs of a binary operation."});
            return lift::evaluation{util::overload {
                bin_arith_floats<true>(ctx, f),
                [&ctx, &i, &f] <util::temporary T, util::temporary U> (T && a, U && b) -> result<sem::value::complete> requires util::none<sem::value::Float, T, U> {
                    auto results = sem::decays(sem::type::Float{})(sem::value_type((a))) || sem::decays(sem::type::Float{})(sem::value_type((b)))
                        ? bin_arith_floats <false>(ctx, std::forward<F>(f))(std::move(a), std::move(b))
                        : bin_arith_ints   <false>(ctx, std::forward<I>(i))(std::move(a), std::move(b));
                    if (!results)
                        return results.error();
                    return *results;
                },
            }} (std::move(first), std::move(second));
        };
    };

    template <bool Check>
    constexpr auto un_arith_float = [] <typename F> (sem::context & ctx, F && f) {
        return [&ctx, &f] <util::temporary T> (T && a) requires (!Check || util::same_as_no_cvref<sem::value::Float, T>) {
            return lift::result{sem::value::make_float} (
                lift::result{std::forward<F>(f)} (
                    sem::get<floating>(sem::convert(ctx)(sem::type::Float{})(std::move(a)))
                )
            );
        };
    };

    template <bool Check>
    constexpr auto un_arith_int = [] <typename F> (sem::context & ctx, F && f) {
        return [&ctx, &f] <util::temporary T> (T && a) requires (!Check || !util::same_as_no_cvref<sem::value::Float, T>) {
            return lift::result{sem::value::make_int} (
                lift::result{std::forward<F>(f)} (
                    sem::get<integral>(sem::convert(ctx)(sem::type::Int{})(std::move(a)))
                )
            );
        };
    };

    constexpr auto un_arith = [] <typename I, typename F> (sem::context & ctx, I && i, F && f) {
        return [&ctx, &i, &f] (util::temporary auto && arg) -> tuple_vector<result<sem::value::complete>> {
            if (arg.size() == 0)
                return ast::make_evaluation_result(result_error{"Cannot use the void value in a unary operation."});
            return lift::evaluation{util::overload {
                un_arith_float<true>(ctx, f),
                [&ctx, &i, &f] <util::temporary T> (T && a) {
                    return sem::decays(sem::type::Float{})(sem::value_type(a))
                        ? un_arith_float <false>(ctx, std::forward<F>(f))(std::move(a))
                        : un_arith_int   <false>(ctx, std::forward<I>(i))(std::move(a));
                },
            }} (std::move(arg));
        };
    };

    // Comparison operations //

    constexpr auto compare_same_types = [] <typename F> (F && f) {
        return lift::any_asymetric{util::overload {
            // TODO: Decaying types (T const, T in, T out -> T)
            [&f] <util::temporary T> (T && a, T && b) requires util::same_as_no_cvref<T, sem::value::Bool> {
                return lift::result{sem::value::make_bool} (
                    lift::result{std::forward<F>(f)} (
                        sem::get<bool>(std::move(a)),
                        sem::get<bool>(std::move(b))
                    )
                );
            },
            [&f] <util::temporary T> (T && a, T && b) requires util::same_as_no_cvref<T, sem::value::Int> {
                return lift::result{sem::value::make_bool} (
                    lift::result{std::forward<F>(f)} (
                        sem::get<integral>(std::move(a)),
                        sem::get<integral>(std::move(b))
                    )
                );
            },
            [&f] <util::temporary T> (T && a, T && b) requires util::same_as_no_cvref<T, sem::value::Float> {
                return lift::result{sem::value::make_bool} (
                    lift::result{std::forward<F>(f)} (
                        sem::get<floating>(std::move(a)),
                        sem::get<floating>(std::move(b))
                    )
                );
            },
            [] <util::temporary T> (T &&, T &&) requires util::same_as_no_cvref<T, sem::value::Function> {
                return result<sem::value::complete>{result_error{"Cannot compare functions."}};
            },
            [] <util::temporary T> (T &&, T &&) requires util::same_as_no_cvref<T, sem::value::Array> {
                // TODO
                return result<sem::value::complete>{result_error{"Array comparison not supported yet."}};
            },
            [] <util::temporary T> (T &&, T &&) requires util::same_as_no_cvref<T, sem::value::Buffer> {
                // TODO
                return result<sem::value::complete>{result_error{"Cannot compare buffers"}};
            },
            [] <util::temporary T> (T &&, T &&) requires util::same_as_no_cvref<T, sem::value::String> {
                // TODO
                return result<sem::value::complete>{result_error{"Strings are not supported yet."}};
            },
            [] <util::temporary T> (T &&, T &&) requires util::same_as_no_cvref<T, sem::value::In> {
                // This shouldn't happen unless this overload set is used incorectly.
                return result<sem::value::complete>{result_error{}};
            },
            [] <util::temporary T> (T &&, T &&) requires util::same_as_no_cvref<T, sem::value::Out> {
                // This shouldn't happen unless this overload set is used incorectly.
                return result<sem::value::complete>{result_error{}};
            },
            [] <util::temporary T> (T &&, T &&) requires util::same_as_no_cvref<T, sem::value::Const> {
                // This shouldn't happen unless this overload set is used incorectly.
                return result<sem::value::complete>{result_error{}};
            },
            [] <util::temporary T, util::temporary U> (T &&, U &&) requires sem::interface::value<T> && sem::interface::value<U> && (!util::same_as_no_cvref<T, U>) {
                return result<sem::value::complete>{result_error{"Cannot compare incompatible types."}};
            }
        }};
    };

    constexpr auto compare = [] <typename F> (sem::context & ctx, F && f) {
        return [&ctx, &f] (util::temporary auto && first, util::temporary auto && second) -> result<tuple_vector<result<sem::value::complete>>> {
            if (first.size() == 0)
                return ast::make_evaluation_result(result_error{"Cannot use the void value on the lhs of a binary operation."});
            if (second.size() == 0)
                return ast::make_evaluation_result(result_error{"Cannot use the void value on the lhs of a binary operation."});
            if (first.size() > second.size())
                return ast::make_evaluation_result(result_error{"More values on the lhs of a binary operation."});
            if (first.size() < second.size())
                return ast::make_evaluation_result(result_error{"More values on the rhs of a binary operation."});
            return lift::evaluation{util::overload {
                [&f] <util::temporary T> (T && a, T && b) {
                    return compare_same_types(std::forward<F>(f))(std::move(a), std::move(b));
                },
                [&ctx, &f] <util::temporary T, util::temporary U> (T && a, U && b) requires (!util::same_as_no_cvref<T, U>) {
                    auto a_type    = sem::value_type(a);
                    auto b_type    = sem::value_type(b);
                    auto a_decayed = util::coalesce(sem::decay(a_type), std::move(a_type)); // TODO: The lazy trick (with ?:) doesn't work here.
                    auto b_decayed = util::coalesce(sem::decay(b_type), std::move(b_type));
                    return compare_same_types (
                        std::forward<F>(f))(sem::convert_to(ctx)(std::move(a))(std::move(a_decayed)),
                        sem::convert_to(ctx)(std::move(b))(std::move(b_decayed))
                    );
                }
            }} (std::move(first), std::move(second));
        };
    };

    constexpr auto add = [] (sem::context & ctx) { return bin_arith(ctx, util::add, util::add);  };
    constexpr auto sub = [] (sem::context & ctx) { return bin_arith(ctx, util::sub, util::sub);  };
    constexpr auto mul = [] (sem::context & ctx) { return bin_arith(ctx, util::mul, util::mul);  };
    constexpr auto div = [] (sem::context & ctx) { return bin_arith(ctx, util::div, util::div);  };
    constexpr auto pow = [] (sem::context & ctx) { return bin_arith(ctx, util::pow, util::pow);  };
    constexpr auto mod = [] (sem::context & ctx) { return bin_arith(ctx, util::mod, util::fmod); };

    constexpr auto plus  = [] (sem::context & ctx) { return un_arith(ctx, util::plus,  util::plus);  };
    constexpr auto minus = [] (sem::context & ctx) { return un_arith(ctx, util::minus, util::minus); };

    constexpr auto eq = [] (sem::context & ctx) { return compare(ctx, util::eq); };
    constexpr auto ne = [] (sem::context & ctx) { return compare(ctx, util::ne); };
    constexpr auto gt = [] (sem::context & ctx) { return compare(ctx, util::gt); };
    constexpr auto lt = [] (sem::context & ctx) { return compare(ctx, util::lt); };
    constexpr auto ge = [] (sem::context & ctx) { return compare(ctx, util::ge); };
    constexpr auto le = [] (sem::context & ctx) { return compare(ctx, util::le); };

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

    display_result ast::node::Add::display () const {
        return "(" + cynth::display(left_argument) + " + " + cynth::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Add::evaluate (sem::context & ctx) const {
        auto results = add(ctx)(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
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

    display_result ast::node::And::display () const {
        return "(" + cynth::display(left_argument) + " && " + cynth::display(right_argument) + ")";
    }

    // TODO: This implementation doesn't work on tuples.
    ast::evaluation_result ast::node::And::evaluate (sem::context & ctx) const {
        auto llhs = lazy{[this, &ctx] {
            return sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(ast::evaluate(ctx)(left_argument))));
        }};
        auto lrhs = lazy{[this, &ctx] {
            return sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(ast::evaluate(ctx)(right_argument))));
        }};
        return ast::make_evaluation_result(lift::result{sem::value::make_bool}(util::land(llhs, lrhs)));
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

    display_result ast::node::Application::display () const {
        return cynth::display(function) + util::parenthesized(cynth::display(arguments));
    }

    ast::evaluation_result ast::node::Application::evaluate (sem::context & ctx) const {
        // Definition:
        auto definition_result = sem::get<sem::value::Function>(util::single(ast::evaluate(ctx)(function)));
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
        auto function_scope = make_child_context(*definition.value->capture);
        // Every function has its internal storage for array values:
        // Note: No other referential values need local function storage for now.
        // In, out and buffer types are only stored globally right now.
        function_scope.init_storage<sem::value::ArrayValue>();

        // Parameters:
        /*auto params_result = util::unite_results(sem::complete(ast::eval_decl(function_scope)(definition.input)));
        if (!params_result)
            return ast::make_evaluation_result(params_result.error());
        auto params = *std::move(params_result);*/
        auto params = std::move(definition.value->parameters);

        auto paramdef_result = function_scope.define_value(params, args);
        if (!paramdef_result)
            return ast::make_evaluation_result(paramdef_result.error());

        auto body_result = util::unite_results(ast::evaluate(function_scope)(definition.value->body));
        if (!body_result)
            return ast::make_evaluation_result(body_result.error());
        auto body = *std::move(body_result);
        //auto type = sem::complete(ast::eval_type(function_scope)(definition.output));
        auto type = std::move(definition.value->out_type);

        auto results = sem::copy(ctx)(sem::convert(ctx)(std::move(body), std::move(type)));
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

    display_result ast::node::Array::display () const {
        return "[" + util::join(", ", cynth::display(elements)) + "]";
    }

    ast::evaluation_result ast::node::Array::evaluate (sem::context & ctx) const {
        auto result = sem::array_elems(ctx, elements);
        if (!result)
            return ast::make_evaluation_result(result.error());
        auto [values, type] = *std::move(result);

        // Note: There were some unresolved issues in the standard with lambda-capturing structured bindings,
        // which should now (as of C++20?) be resolved, but clang (10) still hasn't implemented the changes. (Maybe clang 11?)
        // So until it's fixed in clang, the workaround is to do a capture with an initializer: [&type = type]

        auto converted_result = util::unite_results(lift::component{
            [&ctx, &type = type] <typename T> (T && value) -> cynth::result<tuple_vector<sem::value::complete>> {
                auto result = sem::convert(ctx)(std::forward<T>(value), type);
                if (!result)
                    return result.error();
                return util::unite_results(*result);
            }
        } (values));
        if (!converted_result)
            return ast::make_evaluation_result(converted_result.error());
        auto converted = *std::move(converted_result);
        auto stored = ctx.store_value(sem::value::ArrayValue {
            .value = converted
        });
        if (!stored)
            return ast::make_evaluation_result(stored.error());

        auto array_result = sem::value::make_array (
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

    display_result ast::node::Block::display () const {
        return statements.empty()
            ? "{}"
            : "{\n" + util::join(";\n", cynth::display(statements)) + "\n}";
    }

    template <bool Scope>
    ast::evaluation_result ast::node::Block::evaluate (sem::context & ctx) const {
        constexpr auto eval = [] (
            sem::context & ctx,
            component_vector<category::Statement> const & statements
        ) -> ast::evaluation_result {
            for (auto & statement : statements) {
                auto returned = ast::execute(ctx)(statement);
                if (returned)
                    return lift::tuple_vector{make_result}(*returned);
                if (returned.has_error())
                    return ast::make_evaluation_result(returned.error());
            }

            //return ast::make_evaluation_result(result_error{"Evaluated block does not return."});
            return {}; // Return the void value.
        };

        if constexpr (Scope) {
            auto block_scope = make_child_context(ctx);
            return eval(block_scope, statements);

        } else
            return eval(ctx, statements);
    }

    template ast::evaluation_result ast::node::Block::evaluate <true>  (sem::context &) const;
    template ast::evaluation_result ast::node::Block::evaluate <false> (sem::context &) const;

    ast::execution_result ast::node::Block::execute (sem::context & ctx) const {
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

    display_result ast::node::Bool::display () const {
        return value ? "true" : "false";
    }

    ast::evaluation_result ast::node::Bool::evaluate (sem::context &) const {
        return ast::make_evaluation_result(sem::value::make_bool(value));
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

    display_result ast::node::Conversion::display () const {
        return cynth::display(type) + util::parenthesized(cynth::display(argument));
    }

    ast::evaluation_result ast::node::Conversion::evaluate (sem::context & ctx) const {
        auto from = ast::evaluate(ctx)(argument);
        auto to   = sem::complete(ctx)(ast::eval_type(ctx)(type));
        if (to.size() == 0)
            return ast::make_evaluation_result(result_error{"Cannot use the void type in an explicit conversion."});
        if (from.size() == 0)
            return ast::make_evaluation_result(result_error{"Cannot use the void value in an explicit conversion."});
        if (to.size() > from.size())
            return ast::make_evaluation_result(result_error{"Too little values in a conversion."});
        if (to.size() < from.size())
            return ast::make_evaluation_result(result_error{"Too many values in a conversion."});
        auto result = sem::convert(ctx)(from, to);
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

    display_result ast::node::Div::display () const {
        return "(" + cynth::display(left_argument) + " / " + cynth::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Div::evaluate (sem::context & ctx) const {
        auto results = div(ctx)(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
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

    display_result ast::node::Eq::display () const {
        return "(" + cynth::display(left_argument) + " == " + cynth::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Eq::evaluate (sem::context & ctx) const {
        auto results = eq(ctx)(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
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

    display_result ast::node::ExprFor::display () const {
        return
            "for " + util::parenthesized(cynth::display(declarations)) +
            " "    + cynth::display(body);
    }

    ast::evaluation_result ast::node::ExprFor::evaluate (sem::context & ctx) const {
        auto decls_result = sem::for_decls(ctx, *declarations);
        if (!decls_result)
            return ast::make_evaluation_result(decls_result.error());
        auto [size, iter_decls] = *std::move(decls_result);

        sem::array_vector              result_values;
        std::optional<sem::array_type> result_type;

        result_values.reserve(size);

        for (integral i = 0; i < size; ++i) {
            // Init inner scope:
            auto iter_scope = make_child_context(ctx);

            // Define iteration elements:
            for (auto & [decl, value] : iter_decls)
                iter_scope.define_value(decl, value.value->value[i]);

            // Evaluate the loop body:
            auto value_result = util::unite_results(ast::evaluate(iter_scope)(body));
            if (!value_result)
                return ast::make_evaluation_result(value_result.error());

            auto & value = *value_result;
            auto   type  = sem::value_type(value);

            if (result_type) {
                auto common_results = sem::common(type, *result_type);
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

        auto stored = ctx.store_value(sem::value::ArrayValue {
            .value = result_values
        });
        if (!stored)
            return ast::make_evaluation_result(stored.error());

        auto result = sem::value::make_array (
            stored.get(),
            *std::move(result_type),
            static_cast<integral>(stored->value.size())
        );
        if (!result)
            return ast::make_evaluation_result(result.error());
        return ast::make_evaluation_result(*result);
    }

    ast::execution_result ast::node::ExprFor::execute (sem::context & ctx) const {
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

    display_result ast::node::ExprIf::display () const {
        return
            "if "    + util::parenthesized(cynth::display(condition)) +
            " "      + cynth::display(positive_branch) +
            " else " + cynth::display(negative_branch);
    }

    ast::evaluation_result ast::node::ExprIf::evaluate (sem::context & ctx) const {
        auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(ast::evaluate(ctx)(condition))));
        if (!result)
            return ast::make_evaluation_result(result.error());
        if (*result)
            return ast::evaluate(ctx)(positive_branch);
        else
            return ast::evaluate(ctx)(negative_branch);
    }

    ast::execution_result ast::node::ExprIf::execute (sem::context & ctx) const {
        auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(ast::evaluate(ctx)(condition))));
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

    display_result ast::node::Float::display () const {
        return std::to_string(value);
    }

    ast::evaluation_result ast::node::Float::evaluate (sem::context &) const {
        return ast::make_evaluation_result(sem::value::make_float(value));
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

    display_result ast::node::Function::display () const {
        return cynth::display(output) + " fn " + util::parenthesized(cynth::display(input)) + " " + cynth::display(body);
    }

    ast::evaluation_result ast::node::Function::evaluate (sem::context & ctx) const {
        auto out_type = util::unite_results(sem::complete(ctx)(ast::eval_type(ctx)(output)));
        if (!out_type)
            return ast::make_evaluation_result(out_type.error());
        auto parameters = util::unite_results(sem::complete(ctx)(ast::eval_decl(ctx)(input)));
        if (!parameters)
            return ast::make_evaluation_result(parameters.error());

        auto stored = ctx.store_value(sem::value::FunctionValue {
            .out_type   = component_vector<sem::type::complete> {*std::move(out_type)},
            .parameters = component_vector<sem::complete_decl>  {*std::move(parameters)},
            .body       = body,
            .capture    = ctx // TODO
        });
        if (!stored)
            return ast::make_evaluation_result(stored.error());

        return ast::make_evaluation_result(sem::value::complete{sem::value::Function {
            .value = stored.get()
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

    display_result ast::node::Ge::display () const {
        return "(" + cynth::display(left_argument) + " >= " + cynth::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Ge::evaluate (sem::context & ctx) const {
        auto results = ge(ctx)(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
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

    display_result ast::node::Gt::display () const {
        return "(" + cynth::display(left_argument) + " > " + cynth::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Gt::evaluate (sem::context & ctx) const {
        auto results = gt(ctx)(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
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

    display_result ast::node::Int::display () const {
        return std::to_string(value);
    }

    ast::evaluation_result ast::node::Int::evaluate (sem::context &) const {
        return ast::make_evaluation_result(sem::value::make_int(value));
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

    display_result ast::node::Le::display () const {
        return "(" + cynth::display(left_argument) + " <= " + cynth::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Le::evaluate (sem::context & ctx) const {
        auto results = le(ctx)(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
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

    display_result ast::node::Lt::display () const {
        return "(" + cynth::display(left_argument) + " < " + cynth::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Lt::evaluate (sem::context & ctx) const {
        auto results = lt(ctx)(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
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

    display_result ast::node::Minus::display () const {
        return "-" + cynth::display(argument);
    }

    ast::evaluation_result ast::node::Minus::evaluate (sem::context & ctx) const {
        return minus(ctx)(ast::evaluate(ctx)(argument));
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

    display_result ast::node::Mod::display () const {
        return "(" + cynth::display(left_argument) + " % " + cynth::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Mod::evaluate (sem::context & ctx) const {
        auto results = mod(ctx)(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
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

    display_result ast::node::Mul::display () const {
        return "(" + cynth::display(left_argument) + " * " + cynth::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Mul::evaluate (sem::context & ctx) const {
        auto results = mul(ctx)(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
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

    display_result ast::node::Name::display () const {
        return *name;
    }

    ast::evaluation_result ast::node::Name::evaluate (sem::context & ctx) const {
        return ast::make_evaluation_result(result_error{"TODO"});
        /*
        auto value = ctx.find_value(*name);
        return value
            ? lift::tuple_vector{make_result}(value->value)
            : ast::make_evaluation_result(result_error{"Name not found."});
        */
    }

    ast::target_eval_result ast::node::Name::eval_target (sem::context & ctx) const {
        auto result = ctx.find_value(*name);
        if (!result)
            return ast::make_target_eval_result(result_error{"Target name not found."});
        return ast::make_target_eval_result(sem::any_target{sem::direct_target {
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

    display_result ast::node::Ne::display () const {
        return "(" + cynth::display(left_argument) + " != " + cynth::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Ne::evaluate (sem::context & ctx) const {
        auto results = ne(ctx)(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
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

    display_result ast::node::Not::display () const {
        return "!" + cynth::display(argument);
    }

    ast::evaluation_result ast::node::Not::evaluate (sem::context & ctx) const {
        return lift::evaluation {
            [&ctx] <util::temporary T> (T && a) {
                return lift::result{sem::value::make_bool} (
                    lift::result{util::lnot} (
                        sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(std::move(a)))
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

    display_result ast::node::Or::display () const {
        return "(" + cynth::display(left_argument) + " || " + cynth::display(right_argument) + ")";
    }

    // TODO: This implementation doesn't work on tuples.
    ast::evaluation_result ast::node::Or::evaluate (sem::context & ctx) const {
        auto llhs = lazy{[this, &ctx] {
            return sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(ast::evaluate(ctx)(left_argument))));
        }};
        auto lrhs = lazy{[this, &ctx] {
            return sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(ast::evaluate(ctx)(right_argument))));
        }};
        return util::init<tuple_vector>(lift::result{sem::value::make_bool}(util::lor(llhs, lrhs)));
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

    display_result ast::node::Plus::display () const {
        return "+" + cynth::display(argument);
    }

    ast::evaluation_result ast::node::Plus::evaluate (sem::context & ctx) const {
        return plus(ctx)(ast::evaluate(ctx)(argument));
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

    display_result ast::node::Pow::display () const {
        return "(" + cynth::display(left_argument) + " ** " + cynth::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Pow::evaluate (sem::context & ctx) const {
        auto results = pow(ctx)(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
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

    display_result ast::node::String::display () const {
        //return "\"" + value + "\"";
        return "\"" + *value + "\"";
    }

    ast::evaluation_result ast::node::String::evaluate (sem::context &) const {
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

    display_result ast::node::Sub::display () const {
        return "(" + cynth::display(left_argument) + " - " + cynth::display(right_argument) + ")";
    }

    ast::evaluation_result ast::node::Sub::evaluate (sem::context & ctx) const {
        auto results = sub(ctx)(ast::evaluate(ctx)(left_argument), ast::evaluate(ctx)(right_argument));
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

    display_result ast::node::Subscript::display () const {
        return cynth::display(container) + " [" + util::join(", ", cynth::display(location)) + "]";
    }

    // TODO: This implementation only allows the simple c-like subscript a[i] with a single index on a single (non-tuple) value.
    ast::evaluation_result ast::node::Subscript::evaluate (sem::context & ctx) const {
        //ast::evaluate(container);
        //return sem::get<bool>(lift::single_evaluation{sem::convert(sem::type::Bool{})}(util::single(location)));
        auto location_result = sem::array_elems(ctx, location);
        if (!location_result)
            return ast::make_evaluation_result(location_result.error());
        auto [locations, location_type] = *location_result;

        // TODO: Check the location_type?
        // Simplification: only the first location is taken.
        // (the util::single(locastions) part is the simplification.
        // lift::result{util::single} corresponds to an intended behaviour, not a simplification.)
        //auto r = sem::convert(sem::type::Int{})(util::single(locations));

        auto index_result = sem::get<integral> (
            sem::convert(ctx)(sem::type::Int{})(lift::result{util::single}(util::single(locations)))
        );
        if (!index_result)
            return ast::make_evaluation_result(index_result.error());
        integral index = *index_result;

        // Simplification: only the first container is taken:
        using result_type = result<tuple_vector<sem::value::complete>>;
        auto result = lift::single_evaluation{util::overload {
            [&ctx, index] (sem::value::Array const & a) -> result_type {
                integral size = a.size;
                if (index >= size)
                    return {result_error{"Subscript index out of bounds."}};
                if (index < 0)
                    return {result_error{"Negative subscripts not supported yet."}};
                auto results = sem::convert(ctx)(a.value->value[index], a.type);
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

    ast::target_eval_result ast::node::Subscript::eval_target (sem::context & ctx) const {
        // Only the first container is taken. (This is the intended behaviour, not a simplification.)
        auto container_result = lift::result{util::single}(ast::eval_target(ctx)(container));
        if (!container_result)
            return ast::make_target_eval_result(container_result.error());

        auto location_result = sem::array_elems(ctx, location);
        if (!location_result)
            return ast::make_target_eval_result(location_result.error());
        auto [locations, location_type] = *std::move(location_result);

        if (locations.size() == 0)
            return ast::make_target_eval_result(sem::any_target{sem::subscript_target {
                .container = *container_result,
                .location  = {}
            }});

        // Simplification: Only the first location is taken.
        auto index_result = util::unite_results (
            sem::convert(ctx)(sem::type::Int{})(lift::component{util::single}(locations))
        );
        if (!index_result)
            return ast::make_target_eval_result(index_result.error());

        return ast::make_target_eval_result(sem::any_target{sem::subscript_target {
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

    display_result ast::node::Tuple::display () const {
        return "(" + util::join(", ", cynth::display(values)) + ")";
    }

    ast::evaluation_result ast::node::Tuple::evaluate (sem::context & ctx) const {
        ast::evaluation_result result;
        for (auto & value_tuple : ast::evaluate(ctx)(values)) for (auto & value : value_tuple) {
            result.push_back(std::move(value));
        }
        return result;
    }

    ast::target_eval_result ast::node::Tuple::eval_target (sem::context & ctx) const {
        tuple_vector<sem::any_target> result;
        auto values_result = util::unite_results(ast::eval_target(ctx)(values));
        if (!values_result)
            return ast::make_target_eval_result(values_result.error());
        for (auto & value_tuple : *values_result) for (auto & value : value_tuple) {
            result.push_back(std::move(value));
        }
        return result;
    }

}
