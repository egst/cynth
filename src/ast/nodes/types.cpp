#include "ast/nodes/types.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::ast::node::ArrayType
    using cynth::ast::node::Auto
    using cynth::ast::node::BufferType
    using cynth::ast::node::ConstType
    using cynth::ast::node::InType
    using cynth::ast::node::OutType
    using cynth::ast::node::TupleType
    using cynth::ast::node::TypeDecl
    using cynth::ast::node::TypeName

    template <>
    void component_deleter<ArrayType>::operator () (ArrayType * ptr) const {
        delete ptr;
    }

    template <>
    ArrayType * component_allocator<ArrayType>::operator () (ArrayType const & other) const {
        return new ArrayType{other};
    }

    template <>
    ArrayType * component_allocator<ArrayType>::operator () (ArrayType && other) const {
        return new ArrayType{std::move(other)};
    }

    template <>
    void component_deleter<Auto>::operator () (Auto * ptr) const {
        delete ptr;
    }

    template <>
    Auto * component_allocator<Auto>::operator () (Auto const & other) const {
        return new Auto{other};
    }

    template <>
    Auto * component_allocator<Auto>::operator () (Auto && other) const {
        return new Auto{std::move(other)};
    }

    template <>
    void component_deleter<BufferType>::operator () (BufferType * ptr) const {
        delete ptr;
    }

    template <>
    BufferType * component_allocator<BufferType>::operator () (BufferType const & other) const {
        return new BufferType{other};
    }

    template <>
    BufferType * component_allocator<BufferType>::operator () (BufferType && other) const {
        return new BufferType{std::move(other)};
    }

    template <>
    void component_deleter<ConstType>::operator () (ConstType * ptr) const {
        delete ptr;
    }

    template <>
    ConstType * component_allocator<ConstType>::operator () (ConstType const & other) const {
        return new ConstType{other};
    }

    template <>
    ConstType * component_allocator<ConstType>::operator () (ConstType && other) const {
        return new ConstType{std::move(other)};
    }

    template <>
    void component_deleter<FunctionType>::operator () (FunctionType * ptr) const {
        delete ptr;
    }

    template <>
    FunctionType * component_allocator<FunctionType>::operator () (FunctionType const & other) const {
        return new FunctionType{other};
    }

    template <>
    FunctionType * component_allocator<FunctionType>::operator () (FunctionType && other) const {
        return new FunctionType{std::move(other)};
    }

    template <>
    void component_deleter<InType>::operator () (InType * ptr) const {
        delete ptr;
    }

    template <>
    InType * component_allocator<InType>::operator () (InType const & other) const {
        return new InType{other};
    }

    template <>
    InType * component_allocator<InType>::operator () (InType && other) const {
        return new InType{std::move(other)};
    }

    template <>
    void component_deleter<OutType>::operator () (OutType * ptr) const {
        delete ptr;
    }

    template <>
    OutType * component_allocator<OutType>::operator () (OutType const & other) const {
        return new OutType{other};
    }

    template <>
    OutType * component_allocator<OutType>::operator () (OutType && other) const {
        return new OutType{std::move(other)};
    }

    template <>
    void component_deleter<TupleType>::operator () (TupleType * ptr) const {
        delete ptr;
    }

    template <>
    TupleType * component_allocator<TupleType>::operator () (TupleType const & other) const {
        return new TupleType{other};
    }

    template <>
    TupleType * component_allocator<TupleType>::operator () (TupleType && other) const {
        return new TupleType{std::move(other)};
    }

    template <>
    void component_deleter<TypeDecl>::operator () (TypeDecl * ptr) const {
        delete ptr;
    }

    template <>
    TypeDecl * component_allocator<TypeDecl>::operator () (TypeDecl const & other) const {
        return new TypeDecl{other};
    }

    template <>
    TypeDecl * component_allocator<TypeDecl>::operator () (TypeDecl && other) const {
        return new TypeDecl{std::move(other)};
    }

    template <>
    void component_deleter<TypeName>::operator () (TypeName * ptr) const {
        delete ptr;
    }

    template <>
    TypeName * component_allocator<TypeName>::operator () (TypeName const & other) const {
        return new TypeName{other};
    }

    template <>
    TypeName * component_allocator<TypeName>::operator () (TypeName && other) const {
        return new TypeName{std::move(other)};
    }

}

// TODO
#if 0
namespace cynth {

    //// ArrayType ////

    display_result ast::node::ArrayType::display () const {
        //return cynth::display(type) + " [" + util::coalesce(cynth::display(size) ?: "") + "]";
        //return cynth::display(type) + " [" + util::coalesce(cynth::display(size), "") + "]";
        return cynth::display(type) + " [" + cynth::display(size).value_or("$") + "]";
    }

    ast::type_eval_result ast::node::ArrayType::eval_type (sem::context & ctx) const {
        auto type_result = util::unite_results(ast::eval_type(ctx)(type));
        if (!type_result)
            return ast::make_type_eval_result(type_result.error());
        auto type = *std::move(type_result);

        auto size_result = lift::category_component{util::overload {
            [&ctx] <ast::interface::expression Expr> (Expr && e) -> result<sem::value::incomplete> {
                auto result = sem::convert(ctx)(sem::type::Int{})(util::single(ast::evaluate(ctx)(e)));
                if (!result)
                    return result.error();
                return sem::value::incomplete{*std::move(result)};
            },
            [] <ast::interface::declaration Decl> (Decl &&) -> result<sem::value::incomplete> {
                return result_error{"Capturing array size deduction is not supported yet."};
            },
        }} (size);
        sem::value::incomplete size = (size_result && *size_result)
            ? **size_result
            : sem::value::unknown{};

        return ast::make_type_eval_result(sem::type::array_type<false> {
            .type = make_component_vector (std::move(type)),
            .size = make_component        (std::move(size))
        });
    }

    //// Auto ////

    display_result ast::node::Auto::display () const {
        return "$";
    }

    ast::type_eval_result ast::node::Auto::eval_type (sem::context &) const {
        return ast::make_type_eval_result(sem::type::unknown{});
    }

    //// BufferType ////

    display_result ast::node::BufferType::display () const {
        return "buffer [" + cynth::display(size) + "]";
    }

    ast::type_eval_result ast::node::BufferType::eval_type (sem::context & ctx) const {
        auto size_result = sem::convert(ctx)(sem::type::Int{})(util::single(ast::evaluate(ctx)(size)));
        if (!size_result)
            return ast::make_type_eval_result(size_result.error());
        auto size = sem::value::incomplete{*std::move(size_result)};
        // TODO: Decide whether a pattern should be allowed here.

        return ast::make_type_eval_result(sem::type::buffer_type<false> {
            .size = make_component(std::move(size))
        });
    }

    //// ConstType ////

    display_result ast::node::ConstType::display () const {
        return cynth::display(type) + " const";
    }

    ast::type_eval_result ast::node::ConstType::eval_type (sem::context & ctx) const {
        auto types_result = ast::eval_type(ctx)(type);

        return lift::evaluation{util::overload {
            [] <bool Complete> (sem::type::const_type<Complete> && type) -> result<sem::type::incomplete> {
                return {type};
            },
            [] <bool Complete> (sem::type::in_type<Complete> && type) -> result<sem::type::incomplete> {
                // Note: Input types are implicitly const.
                return {std::move(type)};
            },
            [] <bool Complete> (sem::type::out_type<Complete> && type) -> result<sem::type::incomplete> {
                // Note: Output types are implicitly const.
                return {std::move(type)};
            },
            [] <bool Complete> (sem::type::buffer_type<Complete> && type) -> result<sem::type::incomplete> {
                // Note: Buffers are implicitly const.
                return {std::move(type)};
            },
            [] <bool Complete> (sem::type::function_type<Complete> && type) -> result<sem::type::incomplete> {
                // Note: Function types are implicitly const.
                return {std::move(type)};
            },
            [] <util::temporary Type> (Type && type) -> result<sem::type::incomplete> {
                return {sem::type::const_type<false> {
                    .type = make_component(sem::type::incomplete{std::move(type)})
                }};
            }
        }} (std::move(types_result));
    }

    //// FunctionType ////

    display_result ast::node::FunctionType::display () const {
        return cynth::display(output) + " " + util::parenthesized(cynth::display(input));
    }

    ast::type_eval_result ast::node::FunctionType::eval_type (sem::context & ctx) const {
        auto out_result = util::unite_results(ast::eval_type(ctx)(output));
        if (!out_result)
            return ast::make_type_eval_result(out_result.error());
        auto out = *std::move(out_result);

        auto in_result = util::unite_results(ast::eval_type(ctx)(input));
        if (!in_result)
            return ast::make_type_eval_result(in_result.error());
        auto in = *std::move(in_result);

        return ast::make_type_eval_result(sem::type::function_type<false> {
            .out = make_component_vector(std::move(out)),
            .in  = make_component_vector(std::move(in))
        });
    }

    //// InType ////

    display_result ast::node::InType::display () const {
        return cynth::display(type) + " in";
    }

    ast::type_eval_result ast::node::InType::eval_type (sem::context & ctx) const {
        auto types_result = ast::eval_type(ctx)(type);

        return lift::evaluation{util::overload {
            [] <bool Complete> (sem::type::in_type<Complete> && type) -> result<sem::type::incomplete> {
                return {type};
            },
            [] <bool Complete> (sem::type::out_type<Complete> &&) -> result<sem::type::incomplete> {
                return result_error{"Input type cannot contain a nested output type."};
            },
            [] <bool Complete> (sem::type::const_type<Complete> && type) -> result<sem::type::incomplete> {
                // Note: Input type implicitly contains a const type already.
                return {sem::type::in_type<false> {
                    .type = sem::type::incomplete{*std::move(type.type)}
                }};
            },
            [] <bool Complete> (sem::type::array_type<Complete> &&) -> result<sem::type::incomplete> {
                return result_error{"Array input types are not suppported yet."};
            },
            [] <bool Complete> (sem::type::function_type<Complete> &&) -> result<sem::type::incomplete> {
                return result_error{"Function cannot be an input type."};
            },
            [] <util::temporary Type> (Type && type) -> result<sem::type::incomplete> {
                return {sem::type::in_type<false> {
                    .type = make_component(sem::type::incomplete{std::move(type)})
                }};
            }
        }} (std::move(types_result));
    }

    //// OutType ////

    display_result ast::node::OutType::display () const {
        return cynth::display(type) + " out";
    }

    ast::type_eval_result ast::node::OutType::eval_type (sem::context & ctx) const {
        auto types_result = ast::eval_type(ctx)(type);

        return lift::evaluation{util::overload {
            [] <bool Complete> (sem::type::out_type<Complete> && type) -> result<sem::type::incomplete> {
                return {type};
            },
            [] <bool Complete> (sem::type::in_type<Complete> &&) -> result<sem::type::incomplete> {
                return result_error{"Output type cannot contain a nested input type."};
            },
            [] <bool Complete> (sem::type::const_type<Complete> &&) -> result<sem::type::incomplete> {
                return result_error{"Output type cannot contain a const value."};
            },
            [] <bool Complete> (sem::type::array_type<Complete> &&) -> result<sem::type::incomplete> {
                return result_error{"Array output types are not supported yet."};
            },
            [] <bool Complete> (sem::type::function_type<Complete> &&) -> result<sem::type::incomplete> {
                return result_error{"Function cannot be an output type."};
            },
            [] <util::temporary Type> (Type && type) -> result<sem::type::incomplete> {
                return {sem::type::out_type<false> {
                    .type = make_component(sem::type::incomplete{std::move(type)})
                }};
            }
        }} (std::move(types_result));
    }

    //// TupleType ////

    display_result ast::node::TupleType::display () const {
        return "(" + util::join(", ", cynth::display(types)) + ")";
    }

    ast::type_eval_result ast::node::TupleType::eval_type (sem::context & ctx) const {
        type_eval_result result;
        for (auto & value_tuple : ast::eval_type(ctx)(types)) for (auto & value : value_tuple) {
            result.push_back(std::move(value));
        }
        return result;
    }

    //// TypeDecl ////

    display_result ast::node::TypeDecl::display () const {
        return "type " + cynth::display(name);
    }

    ast::type_eval_result ast::node::TypeDecl::eval_type (sem::context &) const {
        return ast::make_type_eval_result(result_error{"Capturing type deduction is not supported yet."});
    }

    //// TypeName ////

    display_result ast::node::TypeName::display () const {
        return *name;
    }

    ast::type_eval_result ast::node::TypeName::eval_type (sem::context & ctx) const {
        auto value = ctx.find_type(*name);
        return value
            ? sem::incomplete(lift::tuple_vector{make_result}(*value))
            : ast::make_type_eval_result(result_error{"Type name not found."});
    }

}
#endif
