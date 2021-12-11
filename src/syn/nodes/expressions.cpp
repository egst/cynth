#include "syn/nodes/expressions.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::syn::node::Add;
    using cynth::syn::node::And;
    using cynth::syn::node::Application;
    using cynth::syn::node::Array;
    using cynth::syn::node::Block;
    using cynth::syn::node::Bool;
    using cynth::syn::node::Conversion;
    using cynth::syn::node::Div;
    using cynth::syn::node::Eq;
    using cynth::syn::node::ExprFor;
    using cynth::syn::node::ExprIf;
    using cynth::syn::node::Float;
    using cynth::syn::node::Function;
    using cynth::syn::node::Ge;
    using cynth::syn::node::Gt;
    using cynth::syn::node::Int;
    using cynth::syn::node::Le;
    using cynth::syn::node::Lt;
    using cynth::syn::node::Minus;
    using cynth::syn::node::Mod;
    using cynth::syn::node::Mul;
    using cynth::syn::node::Name;
    using cynth::syn::node::Ne;
    using cynth::syn::node::Not;
    using cynth::syn::node::Or;
    using cynth::syn::node::Plus;
    using cynth::syn::node::Pow;
    using cynth::syn::node::String;
    using cynth::syn::node::Sub;
    using cynth::syn::node::Subscript;
    using cynth::syn::node::Tuple;

    template <>
    void component_deleter<Add>::operator () (Add * ptr) const {
        delete ptr;
    }

    template <>
    Add * component_allocator<Add>::operator () (Add const & other) const {
        return new Add{other};
    }

    template <>
    Add * component_allocator<Add>::operator () (Add && other) const {
        return new Add{std::move(other)};
    }

    template <>
    void component_deleter<And>::operator () (And * ptr) const {
        delete ptr;
    }

    template <>
    And * component_allocator<And>::operator () (And const & other) const {
        return new And{other};
    }

    template <>
    And * component_allocator<And>::operator () (And && other) const {
        return new And{std::move(other)};
    }

    template <>
    void component_deleter<Application>::operator () (Application * ptr) const {
        delete ptr;
    }

    template <>
    Application * component_allocator<Application>::operator () (Application const & other) const {
        return new Application{other};
    }

    template <>
    Application * component_allocator<Application>::operator () (Application && other) const {
        return new Application{std::move(other)};
    }

    template <>
    void component_deleter<Array>::operator () (Array * ptr) const {
        delete ptr;
    }

    template <>
    Array * component_allocator<Array>::operator () (Array const & other) const {
        return new Array{other};
    }

    template <>
    Array * component_allocator<Array>::operator () (Array && other) const {
        return new Array{std::move(other)};
    }

    template <>
    void component_deleter<Block>::operator () (Block * ptr) const {
        delete ptr;
    }

    template <>
    Block * component_allocator<Block>::operator () (Block const & other) const {
        return new Block{other};
    }

    template <>
    Block * component_allocator<Block>::operator () (Block && other) const {
        return new Block{std::move(other)};
    }

    template <>
    void component_deleter<Bool>::operator () (Bool * ptr) const {
        delete ptr;
    }

    template <>
    Bool * component_allocator<Bool>::operator () (Bool const & other) const {
        return new Bool{other};
    }

    template <>
    Bool * component_allocator<Bool>::operator () (Bool && other) const {
        return new Bool{std::move(other)};
    }

    template <>
    void component_deleter<Conversion>::operator () (Conversion * ptr) const {
        delete ptr;
    }

    template <>
    Conversion * component_allocator<Conversion>::operator () (Conversion const & other) const {
        return new Conversion{other};
    }

    template <>
    Conversion * component_allocator<Conversion>::operator () (Conversion && other) const {
        return new Conversion{std::move(other)};
    }

    template <>
    void component_deleter<Div>::operator () (Div * ptr) const {
        delete ptr;
    }

    template <>
    Div * component_allocator<Div>::operator () (Div const & other) const {
        return new Div{other};
    }

    template <>
    Div * component_allocator<Div>::operator () (Div && other) const {
        return new Div{std::move(other)};
    }

    template <>
    void component_deleter<Eq>::operator () (Eq * ptr) const {
        delete ptr;
    }

    template <>
    Eq * component_allocator<Eq>::operator () (Eq const & other) const {
        return new Eq{other};
    }

    template <>
    Eq * component_allocator<Eq>::operator () (Eq && other) const {
        return new Eq{std::move(other)};
    }

    template <>
    void component_deleter<ExprFor>::operator () (ExprFor * ptr) const {
        delete ptr;
    }

    template <>
    ExprFor * component_allocator<ExprFor>::operator () (ExprFor const & other) const {
        return new ExprFor{other};
    }

    template <>
    ExprFor * component_allocator<ExprFor>::operator () (ExprFor && other) const {
        return new ExprFor{std::move(other)};
    }

    template <>
    void component_deleter<ExprIf>::operator () (ExprIf * ptr) const {
        delete ptr;
    }

    template <>
    ExprIf * component_allocator<ExprIf>::operator () (ExprIf const & other) const {
        return new ExprIf{other};
    }

    template <>
    ExprIf * component_allocator<ExprIf>::operator () (ExprIf && other) const {
        return new ExprIf{std::move(other)};
    }

    template <>
    void component_deleter<Float>::operator () (Float * ptr) const {
        delete ptr;
    }

    template <>
    Float * component_allocator<Float>::operator () (Float const & other) const {
        return new Float{other};
    }

    template <>
    Float * component_allocator<Float>::operator () (Float && other) const {
        return new Float{std::move(other)};
    }

    template <>
    void component_deleter<Function>::operator () (Function * ptr) const {
        delete ptr;
    }

    template <>
    Function * component_allocator<Function>::operator () (Function const & other) const {
        return new Function{other};
    }

    template <>
    Function * component_allocator<Function>::operator () (Function && other) const {
        return new Function{std::move(other)};
    }

    template <>
    void component_deleter<Ge>::operator () (Ge * ptr) const {
        delete ptr;
    }

    template <>
    Ge * component_allocator<Ge>::operator () (Ge const & other) const {
        return new Ge{other};
    }

    template <>
    Ge * component_allocator<Ge>::operator () (Ge && other) const {
        return new Ge{std::move(other)};
    }

    template <>
    void component_deleter<Gt>::operator () (Gt * ptr) const {
        delete ptr;
    }

    template <>
    Gt * component_allocator<Gt>::operator () (Gt const & other) const {
        return new Gt{other};
    }

    template <>
    Gt * component_allocator<Gt>::operator () (Gt && other) const {
        return new Gt{std::move(other)};
    }

    template <>
    void component_deleter<Int>::operator () (Int * ptr) const {
        delete ptr;
    }

    template <>
    Int * component_allocator<Int>::operator () (Int const & other) const {
        return new Int{other};
    }

    template <>
    Int * component_allocator<Int>::operator () (Int && other) const {
        return new Int{std::move(other)};
    }

    template <>
    void component_deleter<Le>::operator () (Le * ptr) const {
        delete ptr;
    }

    template <>
    Le * component_allocator<Le>::operator () (Le const & other) const {
        return new Le{other};
    }

    template <>
    Le * component_allocator<Le>::operator () (Le && other) const {
        return new Le{std::move(other)};
    }

    template <>
    void component_deleter<Lt>::operator () (Lt * ptr) const {
        delete ptr;
    }

    template <>
    Lt * component_allocator<Lt>::operator () (Lt const & other) const {
        return new Lt{other};
    }

    template <>
    Lt * component_allocator<Lt>::operator () (Lt && other) const {
        return new Lt{std::move(other)};
    }

    template <>
    void component_deleter<Minus>::operator () (Minus * ptr) const {
        delete ptr;
    }

    template <>
    Minus * component_allocator<Minus>::operator () (Minus const & other) const {
        return new Minus{other};
    }

    template <>
    Minus * component_allocator<Minus>::operator () (Minus && other) const {
        return new Minus{std::move(other)};
    }

    template <>
    void component_deleter<Mod>::operator () (Mod * ptr) const {
        delete ptr;
    }

    template <>
    Mod * component_allocator<Mod>::operator () (Mod const & other) const {
        return new Mod{other};
    }

    template <>
    Mod * component_allocator<Mod>::operator () (Mod && other) const {
        return new Mod{std::move(other)};
    }

    template <>
    void component_deleter<Mul>::operator () (Mul * ptr) const {
        delete ptr;
    }

    template <>
    Mul * component_allocator<Mul>::operator () (Mul const & other) const {
        return new Mul{other};
    }

    template <>
    Mul * component_allocator<Mul>::operator () (Mul && other) const {
        return new Mul{std::move(other)};
    }

    template <>
    void component_deleter<Name>::operator () (Name * ptr) const {
        delete ptr;
    }

    template <>
    Name * component_allocator<Name>::operator () (Name const & other) const {
        return new Name{other};
    }

    template <>
    Name * component_allocator<Name>::operator () (Name && other) const {
        return new Name{std::move(other)};
    }

    template <>
    void component_deleter<Ne>::operator () (Ne * ptr) const {
        delete ptr;
    }

    template <>
    Ne * component_allocator<Ne>::operator () (Ne const & other) const {
        return new Ne{other};
    }

    template <>
    Ne * component_allocator<Ne>::operator () (Ne && other) const {
        return new Ne{std::move(other)};
    }

    template <>
    void component_deleter<Not>::operator () (Not * ptr) const {
        delete ptr;
    }

    template <>
    Not * component_allocator<Not>::operator () (Not const & other) const {
        return new Not{other};
    }

    template <>
    Not * component_allocator<Not>::operator () (Not && other) const {
        return new Not{std::move(other)};
    }

    template <>
    void component_deleter<Or>::operator () (Or * ptr) const {
        delete ptr;
    }

    template <>
    Or * component_allocator<Or>::operator () (Or const & other) const {
        return new Or{other};
    }

    template <>
    Or * component_allocator<Or>::operator () (Or && other) const {
        return new Or{std::move(other)};
    }

    template <>
    void component_deleter<Plus>::operator () (Plus * ptr) const {
        delete ptr;
    }

    template <>
    Plus * component_allocator<Plus>::operator () (Plus const & other) const {
        return new Plus{other};
    }

    template <>
    Plus * component_allocator<Plus>::operator () (Plus && other) const {
        return new Plus{std::move(other)};
    }

    template <>
    void component_deleter<Pow>::operator () (Pow * ptr) const {
        delete ptr;
    }

    template <>
    Pow * component_allocator<Pow>::operator () (Pow const & other) const {
        return new Pow{other};
    }

    template <>
    Pow * component_allocator<Pow>::operator () (Pow && other) const {
        return new Pow{std::move(other)};
    }

    template <>
    void component_deleter<String>::operator () (String * ptr) const {
        delete ptr;
    }

    template <>
    String * component_allocator<String>::operator () (String const & other) const {
        return new String{other};
    }

    template <>
    String * component_allocator<String>::operator () (String && other) const {
        return new String{std::move(other)};
    }

    template <>
    void component_deleter<Sub>::operator () (Sub * ptr) const {
        delete ptr;
    }

    template <>
    Sub * component_allocator<Sub>::operator () (Sub const & other) const {
        return new Sub{other};
    }

    template <>
    Sub * component_allocator<Sub>::operator () (Sub && other) const {
        return new Sub{std::move(other)};
    }

    template <>
    void component_deleter<Subscript>::operator () (Subscript * ptr) const {
        delete ptr;
    }

    template <>
    Subscript* component_allocator<Subscript>::operator () (Subscript const & other) const {
        return new Subscript{other};
    }

    template <>
    Subscript* component_allocator<Subscript>::operator () (Subscript && other) const {
        return new Subscript{std::move(other)};
    }

    template <>
    void component_deleter<Tuple>::operator () (Tuple * ptr) const {
        delete ptr;
    }

    template <>
    Tuple * component_allocator<Tuple>::operator () (Tuple const & other) const {
        return new Tuple{other};
    }

    template <>
    Tuple * component_allocator<Tuple>::operator () (Tuple && other) const {
        return new Tuple{std::move(other)};
    }

}

// TODO
#if 0
namespace cynth {

    //// Implementation helpers ////

    namespace {

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
                    return syn::make_evaluation_result(result_error{"Cannot use the void value on the lhs of a binary operation."});
                if (second.size() == 0)
                    return syn::make_evaluation_result(result_error{"Cannot use the void value on the lhs of a binary operation."});
                if (first.size() > second.size())
                    return syn::make_evaluation_result(result_error{"More values on the lhs of a binary operation."});
                if (first.size() < second.size())
                    return syn::make_evaluation_result(result_error{"More values on the rhs of a binary operation."});
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
                    return syn::make_evaluation_result(result_error{"Cannot use the void value in a unary operation."});
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
                    return syn::make_evaluation_result(result_error{"Cannot use the void value on the lhs of a binary operation."});
                if (second.size() == 0)
                    return syn::make_evaluation_result(result_error{"Cannot use the void value on the lhs of a binary operation."});
                if (first.size() > second.size())
                    return syn::make_evaluation_result(result_error{"More values on the lhs of a binary operation."});
                if (first.size() < second.size())
                    return syn::make_evaluation_result(result_error{"More values on the rhs of a binary operation."});
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

    }

    //// Add ////

    display_result syn::node::Add::display () const {
        return "(" + cynth::display(left_argument) + " + " + cynth::display(right_argument) + ")";
    }

    syn::evaluation_result syn::node::Add::evaluate (sem::context & ctx) const {
        auto results = add(ctx)(syn::evaluate(ctx)(left_argument), syn::evaluate(ctx)(right_argument));
        if (!results)
            return syn::make_evaluation_result(results.error());
        return *results;
    }

    //// And ////

    display_result syn::node::And::display () const {
        return "(" + cynth::display(left_argument) + " && " + cynth::display(right_argument) + ")";
    }

    // TODO: This implementation doesn't work on tuples.
    syn::evaluation_result syn::node::And::evaluate (sem::context & ctx) const {
        auto llhs = lazy{[this, &ctx] {
            return sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(syn::evaluate(ctx)(left_argument))));
        }};
        auto lrhs = lazy{[this, &ctx] {
            return sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(syn::evaluate(ctx)(right_argument))));
        }};
        return syn::make_evaluation_result(lift::result{sem::value::make_bool}(util::land(llhs, lrhs)));
    }

    //// Application ////

    display_result syn::node::Application::display () const {
        return cynth::display(function) + util::parenthesized(cynth::display(arguments));
    }

    syn::evaluation_result syn::node::Application::evaluate (sem::context & ctx) const {
        // Definition:
        auto definition_result = sem::get<sem::value::Function>(util::single(syn::evaluate(ctx)(function)));
        // TODO: Check if evaluated to a function?
        if (!definition_result)
            return syn::make_evaluation_result(definition_result.error());
        auto definition = *std::move(definition_result);

        // Arguments:
        auto args_result = util::unite_results(syn::evaluate(ctx)(arguments));
        if (!args_result)
            return syn::make_evaluation_result(args_result.error());
        auto args = *std::move(args_result);

        // Init nested scope:
        //auto function_scope = ctx;
        auto function_scope = make_child_context(*definition.value->capture);
        // Every function has its internal storage for array values:
        // Note: No other referential values need local function storage for now.
        // In, out and buffer types are only stored globally right now.
        function_scope.init_storage<sem::value::ArrayValue>();

        // Parameters:
        /*auto params_result = util::unite_results(sem::complete(syn::eval_decl(function_scope)(definition.input)));
        if (!params_result)
            return syn::make_evaluation_result(params_result.error());
        auto params = *std::move(params_result);*/
        auto params = std::move(definition.value->parameters);

        auto paramdef_result = function_scope.define_value(params, args);
        if (!paramdef_result)
            return syn::make_evaluation_result(paramdef_result.error());

        auto body_result = util::unite_results(syn::evaluate(function_scope)(definition.value->body));
        if (!body_result)
            return syn::make_evaluation_result(body_result.error());
        auto body = *std::move(body_result);
        //auto type = sem::complete(syn::eval_type(function_scope)(definition.output));
        auto type = std::move(definition.value->out_type);

        auto results = sem::copy(ctx)(sem::convert(ctx)(std::move(body), std::move(type)));
        if (!results)
            return syn::make_evaluation_result(results.error());
        return *results;
    }

    //// Array ////

    display_result syn::node::Array::display () const {
        return "[" + util::join(", ", cynth::display(elements)) + "]";
    }

    syn::evaluation_result syn::node::Array::evaluate (sem::context & ctx) const {
        auto result = sem::array_elems(ctx, elements);
        if (!result)
            return syn::make_evaluation_result(result.error());
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
            return syn::make_evaluation_result(converted_result.error());
        auto converted = *std::move(converted_result);
        auto stored = ctx.store_value(sem::value::ArrayValue {
            .value = converted
        });
        if (!stored)
            return syn::make_evaluation_result(stored.error());

        auto array_result = sem::value::make_array (
            stored.get(),
            make_component_vector(std::move(type)),
            static_cast<integral>(stored->value.size())
        );
        if (!array_result)
            return syn::make_evaluation_result(array_result.error());
        return syn::make_evaluation_result(*array_result);
    }

    //// Block ////

    display_result syn::node::Block::display () const {
        return statements.empty()
            ? "{}"
            : "{\n" + util::join(";\n", cynth::display(statements)) + "\n}";
    }

    template <bool Scope>
    syn::evaluation_result syn::node::Block::evaluate (sem::context & ctx) const {
        constexpr auto eval = [] (
            sem::context & ctx,
            component_vector<category::Statement> const & statements
        ) -> syn::evaluation_result {
            for (auto & statement : statements) {
                auto returned = syn::execute(ctx)(statement);
                if (returned)
                    return lift::tuple_vector{make_result}(*returned);
                if (returned.has_error())
                    return syn::make_evaluation_result(returned.error());
            }

            //return syn::make_evaluation_result(result_error{"Evaluated block does not return."});
            return {}; // Return the void value.
        };

        if constexpr (Scope) {
            auto block_scope = make_child_context(ctx);
            return eval(block_scope, statements);

        } else
            return eval(ctx, statements);
    }

    template syn::evaluation_result syn::node::Block::evaluate <true>  (sem::context &) const;
    template syn::evaluation_result syn::node::Block::evaluate <false> (sem::context &) const;

    syn::execution_result syn::node::Block::execute (sem::context & ctx) const {
        auto block_scope = make_child_context(ctx);

        for (auto & statement : statements) {
            auto returned = syn::execute(block_scope)(statement);
            if (returned)
                return *returned;
            if (returned.has_error())
                return syn::make_execution_result(returned.error());
        }

        return {};
    }

    //// Bool ////

    display_result syn::node::Bool::display () const {
        return value ? "true" : "false";
    }

    syn::evaluation_result syn::node::Bool::evaluate (sem::context &) const {
        return syn::make_evaluation_result(sem::value::make_bool(value));
    }

    //// Conversion ////

    display_result syn::node::Conversion::display () const {
        return cynth::display(type) + util::parenthesized(cynth::display(argument));
    }

    syn::evaluation_result syn::node::Conversion::evaluate (sem::context & ctx) const {
        auto from = syn::evaluate(ctx)(argument);
        auto to   = sem::complete(ctx)(syn::eval_type(ctx)(type));
        if (to.size() == 0)
            return syn::make_evaluation_result(result_error{"Cannot use the void type in an explicit conversion."});
        if (from.size() == 0)
            return syn::make_evaluation_result(result_error{"Cannot use the void value in an explicit conversion."});
        if (to.size() > from.size())
            return syn::make_evaluation_result(result_error{"Too little values in a conversion."});
        if (to.size() < from.size())
            return syn::make_evaluation_result(result_error{"Too many values in a conversion."});
        auto result = sem::convert(ctx)(from, to);
        if (!result)
            return syn::make_evaluation_result(result.error());
        return *result;
    }

    //// Div ///

    display_result syn::node::Div::display () const {
        return "(" + cynth::display(left_argument) + " / " + cynth::display(right_argument) + ")";
    }

    syn::evaluation_result syn::node::Div::evaluate (sem::context & ctx) const {
        auto results = div(ctx)(syn::evaluate(ctx)(left_argument), syn::evaluate(ctx)(right_argument));
        if (!results)
            return syn::make_evaluation_result(results.error());
        return *results;
    }

    //// Eq ///

    display_result syn::node::Eq::display () const {
        return "(" + cynth::display(left_argument) + " == " + cynth::display(right_argument) + ")";
    }

    syn::evaluation_result syn::node::Eq::evaluate (sem::context & ctx) const {
        auto results = eq(ctx)(syn::evaluate(ctx)(left_argument), syn::evaluate(ctx)(right_argument));
        if (!results)
            return syn::make_evaluation_result(results.error());
        return *results;
    }

    //// ExprFor ////

    display_result syn::node::ExprFor::display () const {
        return
            "for " + util::parenthesized(cynth::display(declarations)) +
            " "    + cynth::display(body);
    }

    syn::evaluation_result syn::node::ExprFor::evaluate (sem::context & ctx) const {
        auto decls_result = sem::for_decls(ctx, *declarations);
        if (!decls_result)
            return syn::make_evaluation_result(decls_result.error());
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
            auto value_result = util::unite_results(syn::evaluate(iter_scope)(body));
            if (!value_result)
                return syn::make_evaluation_result(value_result.error());

            auto & value = *value_result;
            auto   type  = sem::value_type(value);

            if (result_type) {
                auto common_results = sem::common(type, *result_type);
                if (!common_results)
                    return syn::make_evaluation_result(common_results.error());
                result_type = result_to_optional(util::unite_results(*common_results));
            } else {
                result_type = std::optional{std::move(type)};
            }

            result_values.push_back(std::move(value));
        }

        if (!result_type)
            return syn::make_evaluation_result(result_error{"No common type for an array in a for expression."});

        auto stored = ctx.store_value(sem::value::ArrayValue {
            .value = result_values
        });
        if (!stored)
            return syn::make_evaluation_result(stored.error());

        auto result = sem::value::make_array (
            stored.get(),
            *std::move(result_type),
            static_cast<integral>(stored->value.size())
        );
        if (!result)
            return syn::make_evaluation_result(result.error());
        return syn::make_evaluation_result(*result);
    }

    syn::execution_result syn::node::ExprFor::execute (sem::context & ctx) const {
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

    //// ExprIf ////

    display_result syn::node::ExprIf::display () const {
        return
            "if "    + util::parenthesized(cynth::display(condition)) +
            " "      + cynth::display(positive_branch) +
            " else " + cynth::display(negative_branch);
    }

    syn::evaluation_result syn::node::ExprIf::evaluate (sem::context & ctx) const {
        auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(syn::evaluate(ctx)(condition))));
        if (!result)
            return syn::make_evaluation_result(result.error());
        if (*result)
            return syn::evaluate(ctx)(positive_branch);
        else
            return syn::evaluate(ctx)(negative_branch);
    }

    syn::execution_result syn::node::ExprIf::execute (sem::context & ctx) const {
        auto result = sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(syn::evaluate(ctx)(condition))));
        if (!result)
            return syn::make_execution_result(result.error());
        if (*result) {
            auto branch_scope = make_child_context(ctx);
            return syn::execute(branch_scope)(positive_branch);
        } else {
            auto branch_scope = make_child_context(ctx);
            return syn::execute(branch_scope)(negative_branch);
        }
    }

    //// Float ////

    display_result syn::node::Float::display () const {
        return std::to_string(value);
    }

    syn::evaluation_result syn::node::Float::evaluate (sem::context &) const {
        return syn::make_evaluation_result(sem::value::make_float(value));
    }

    //// Function ////

    display_result syn::node::Function::display () const {
        return cynth::display(output) + " fn " + util::parenthesized(cynth::display(input)) + " " + cynth::display(body);
    }

    syn::evaluation_result syn::node::Function::evaluate (sem::context & ctx) const {
        auto out_type = util::unite_results(sem::complete(ctx)(syn::eval_type(ctx)(output)));
        if (!out_type)
            return syn::make_evaluation_result(out_type.error());
        auto parameters = util::unite_results(sem::complete(ctx)(syn::eval_decl(ctx)(input)));
        if (!parameters)
            return syn::make_evaluation_result(parameters.error());

        auto stored = ctx.store_value(sem::value::FunctionValue {
            .out_type   = component_vector<sem::type::complete> {*std::move(out_type)},
            .parameters = component_vector<sem::complete_decl>  {*std::move(parameters)},
            .body       = body,
            .capture    = ctx // TODO
        });
        if (!stored)
            return syn::make_evaluation_result(stored.error());

        return syn::make_evaluation_result(sem::value::complete{sem::value::Function {
            .value = stored.get()
        }});
    }

    //// Ge ////

    display_result syn::node::Ge::display () const {
        return "(" + cynth::display(left_argument) + " >= " + cynth::display(right_argument) + ")";
    }

    syn::evaluation_result syn::node::Ge::evaluate (sem::context & ctx) const {
        auto results = ge(ctx)(syn::evaluate(ctx)(left_argument), syn::evaluate(ctx)(right_argument));
        if (!results)
            return syn::make_evaluation_result(results.error());
        return *results;
    }

    //// Gt ////

    display_result syn::node::Gt::display () const {
        return "(" + cynth::display(left_argument) + " > " + cynth::display(right_argument) + ")";
    }

    syn::evaluation_result syn::node::Gt::evaluate (sem::context & ctx) const {
        auto results = gt(ctx)(syn::evaluate(ctx)(left_argument), syn::evaluate(ctx)(right_argument));
        if (!results)
            return syn::make_evaluation_result(results.error());
        return *results;
    }

    //// Int ////

    display_result syn::node::Int::display () const {
        return std::to_string(value);
    }

    syn::evaluation_result syn::node::Int::evaluate (sem::context &) const {
        return syn::make_evaluation_result(sem::value::make_int(value));
    }

    //// Le ////

    display_result syn::node::Le::display () const {
        return "(" + cynth::display(left_argument) + " <= " + cynth::display(right_argument) + ")";
    }

    syn::evaluation_result syn::node::Le::evaluate (sem::context & ctx) const {
        auto results = le(ctx)(syn::evaluate(ctx)(left_argument), syn::evaluate(ctx)(right_argument));
        if (!results)
            return syn::make_evaluation_result(results.error());
        return *results;
    }

    //// Lt ////

    display_result syn::node::Lt::display () const {
        return "(" + cynth::display(left_argument) + " < " + cynth::display(right_argument) + ")";
    }

    syn::evaluation_result syn::node::Lt::evaluate (sem::context & ctx) const {
        auto results = lt(ctx)(syn::evaluate(ctx)(left_argument), syn::evaluate(ctx)(right_argument));
        if (!results)
            return syn::make_evaluation_result(results.error());
        return *results;
    }

    //// Minus ////

    display_result syn::node::Minus::display () const {
        return "-" + cynth::display(argument);
    }

    syn::evaluation_result syn::node::Minus::evaluate (sem::context & ctx) const {
        return minus(ctx)(syn::evaluate(ctx)(argument));
    }

    //// Mod ////

    display_result syn::node::Mod::display () const {
        return "(" + cynth::display(left_argument) + " % " + cynth::display(right_argument) + ")";
    }

    syn::evaluation_result syn::node::Mod::evaluate (sem::context & ctx) const {
        auto results = mod(ctx)(syn::evaluate(ctx)(left_argument), syn::evaluate(ctx)(right_argument));
        if (!results)
            return syn::make_evaluation_result(results.error());
        return *results;
    }

    //// Mul ////

    display_result syn::node::Mul::display () const {
        return "(" + cynth::display(left_argument) + " * " + cynth::display(right_argument) + ")";
    }

    syn::evaluation_result syn::node::Mul::evaluate (sem::context & ctx) const {
        auto results = mul(ctx)(syn::evaluate(ctx)(left_argument), syn::evaluate(ctx)(right_argument));
        if (!results)
            return syn::make_evaluation_result(results.error());
        return *results;
    }

    //// Name ////

    display_result syn::node::Name::display () const {
        return *name;
    }

    syn::evaluation_result syn::node::Name::evaluate (sem::context & ctx) const {
        return syn::make_evaluation_result(result_error{"TODO"});
        /*
        auto value = ctx.find_value(*name);
        return value
            ? lift::tuple_vector{make_result}(value->value)
            : syn::make_evaluation_result(result_error{"Name not found."});
        */
    }

    syn::target_eval_result syn::node::Name::eval_target (sem::context & ctx) const {
        auto result = ctx.find_value(*name);
        if (!result)
            return syn::make_target_eval_result(result_error{"Target name not found."});
        return syn::make_target_eval_result(sem::any_target{sem::direct_target {
            .value = *result
        }});
    }

    //// Ne ////

    display_result syn::node::Ne::display () const {
        return "(" + cynth::display(left_argument) + " != " + cynth::display(right_argument) + ")";
    }

    syn::evaluation_result syn::node::Ne::evaluate (sem::context & ctx) const {
        auto results = ne(ctx)(syn::evaluate(ctx)(left_argument), syn::evaluate(ctx)(right_argument));
        if (!results)
            return syn::make_evaluation_result(results.error());
        return *results;
    }

    //// Not ////

    display_result syn::node::Not::display () const {
        return "!" + cynth::display(argument);
    }

    syn::evaluation_result syn::node::Not::evaluate (sem::context & ctx) const {
        return lift::evaluation {
            [&ctx] <util::temporary T> (T && a) {
                return lift::result{sem::value::make_bool} (
                    lift::result{util::lnot} (
                        sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(std::move(a)))
                    )
                );
            },
        }(syn::evaluate(ctx)(argument));
    }

    //// Or ////

    display_result syn::node::Or::display () const {
        return "(" + cynth::display(left_argument) + " || " + cynth::display(right_argument) + ")";
    }

    // TODO: This implementation doesn't work on tuples.
    syn::evaluation_result syn::node::Or::evaluate (sem::context & ctx) const {
        auto llhs = lazy{[this, &ctx] {
            return sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(syn::evaluate(ctx)(left_argument))));
        }};
        auto lrhs = lazy{[this, &ctx] {
            return sem::get<bool>(sem::convert(ctx)(sem::type::Bool{})(util::single(syn::evaluate(ctx)(right_argument))));
        }};
        return util::init<tuple_vector>(lift::result{sem::value::make_bool}(util::lor(llhs, lrhs)));
    }

    //// Plus ////

    display_result syn::node::Plus::display () const {
        return "+" + cynth::display(argument);
    }

    syn::evaluation_result syn::node::Plus::evaluate (sem::context & ctx) const {
        return plus(ctx)(syn::evaluate(ctx)(argument));
    }

    //// Pow ////

    display_result syn::node::Pow::display () const {
        return "(" + cynth::display(left_argument) + " ** " + cynth::display(right_argument) + ")";
    }

    syn::evaluation_result syn::node::Pow::evaluate (sem::context & ctx) const {
        auto results = pow(ctx)(syn::evaluate(ctx)(left_argument), syn::evaluate(ctx)(right_argument));
        if (!results)
            return syn::make_evaluation_result(results.error());
        return *results;
    }

    //// String ////

    display_result syn::node::String::display () const {
        //return "\"" + value + "\"";
        return "\"" + *value + "\"";
    }

    syn::evaluation_result syn::node::String::evaluate (sem::context &) const {
        return syn::make_evaluation_result(result_error{"Strings are not supported yet."});
    }

    //// Sub ////

    display_result syn::node::Sub::display () const {
        return "(" + cynth::display(left_argument) + " - " + cynth::display(right_argument) + ")";
    }

    syn::evaluation_result syn::node::Sub::evaluate (sem::context & ctx) const {
        auto results = sub(ctx)(syn::evaluate(ctx)(left_argument), syn::evaluate(ctx)(right_argument));
        if (!results)
            return syn::make_evaluation_result(results.error());
        return *results;
    }

    //// Subscript ////

    display_result syn::node::Subscript::display () const {
        return cynth::display(container) + " [" + util::join(", ", cynth::display(location)) + "]";
    }

    // TODO: This implementation only allows the simple c-like subscript a[i] with a single index on a single (non-tuple) value.
    syn::evaluation_result syn::node::Subscript::evaluate (sem::context & ctx) const {
        //syn::evaluate(container);
        //return sem::get<bool>(lift::single_evaluation{sem::convert(sem::type::Bool{})}(util::single(location)));
        auto location_result = sem::array_elems(ctx, location);
        if (!location_result)
            return syn::make_evaluation_result(location_result.error());
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
            return syn::make_evaluation_result(index_result.error());
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
        }} (util::single(syn::evaluate(ctx)(container)));
        if (!result)
            return syn::make_evaluation_result(result.error());

        return lift::tuple_vector{make_result}(*result);
    }

    syn::target_eval_result syn::node::Subscript::eval_target (sem::context & ctx) const {
        // Only the first container is taken. (This is the intended behaviour, not a simplification.)
        auto container_result = lift::result{util::single}(syn::eval_target(ctx)(container));
        if (!container_result)
            return syn::make_target_eval_result(container_result.error());

        auto location_result = sem::array_elems(ctx, location);
        if (!location_result)
            return syn::make_target_eval_result(location_result.error());
        auto [locations, location_type] = *std::move(location_result);

        if (locations.size() == 0)
            return syn::make_target_eval_result(sem::any_target{sem::subscript_target {
                .container = *container_result,
                .location  = {}
            }});

        // Simplification: Only the first location is taken.
        auto index_result = util::unite_results (
            sem::convert(ctx)(sem::type::Int{})(lift::component{util::single}(locations))
        );
        if (!index_result)
            return syn::make_target_eval_result(index_result.error());

        return syn::make_target_eval_result(sem::any_target{sem::subscript_target {
            .container = *container_result,
            .location  = *index_result
        }});
    }

    //// Tuple ////

    display_result syn::node::Tuple::display () const {
        return "(" + util::join(", ", cynth::display(values)) + ")";
    }

    syn::evaluation_result syn::node::Tuple::evaluate (sem::context & ctx) const {
        syn::evaluation_result result;
        for (auto & value_tuple : syn::evaluate(ctx)(values)) for (auto & value : value_tuple) {
            result.push_back(std::move(value));
        }
        return result;
    }

    syn::target_eval_result syn::node::Tuple::eval_target (sem::context & ctx) const {
        tuple_vector<sem::any_target> result;
        auto values_result = util::unite_results(syn::eval_target(ctx)(values));
        if (!values_result)
            return syn::make_target_eval_result(values_result.error());
        for (auto & value_tuple : *values_result) for (auto & value : value_tuple) {
            result.push_back(std::move(value));
        }
        return result;
    }

}
#endif
