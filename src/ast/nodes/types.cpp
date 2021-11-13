#include "ast/nodes/types.hpp"

#include "common_interface.hpp"
#include "ast/categories/expression.hpp"
#include "ast/categories/pattern.hpp"
#include "ast/categories/type.hpp"
#include "ast/interface.hpp"
#include "sem/interface.hpp"
#include "util/general.hpp"
#include "util/container.hpp"
#include "util/string.hpp"

#include <string>

namespace cynth {

    //// ArrayType ////

    template <>
    void component_deleter<ast::node::ArrayType>::operator () (ast::node::ArrayType * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::ArrayType * component_allocator<ast::node::ArrayType>::operator () (ast::node::ArrayType const & other) const {
        return new ast::node::ArrayType{other};
    }

    template <>
    ast::node::ArrayType * component_allocator<ast::node::ArrayType>::operator () (ast::node::ArrayType && other) const {
        return new ast::node::ArrayType{std::move(other)};
    }

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

    template <>
    void component_deleter<ast::node::Auto>::operator () (ast::node::Auto * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Auto * component_allocator<ast::node::Auto>::operator () (ast::node::Auto const & other) const {
        return new ast::node::Auto{other};
    }

    template <>
    ast::node::Auto * component_allocator<ast::node::Auto>::operator () (ast::node::Auto && other) const {
        return new ast::node::Auto{std::move(other)};
    }

    display_result ast::node::Auto::display () const {
        return "$";
    }

    ast::type_eval_result ast::node::Auto::eval_type (sem::context &) const {
        return ast::make_type_eval_result(sem::type::unknown{});
    }

    //// BufferType ////

    template <>
    void component_deleter<ast::node::BufferType>::operator () (ast::node::BufferType * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::BufferType * component_allocator<ast::node::BufferType>::operator () (ast::node::BufferType const & other) const {
        return new ast::node::BufferType{other};
    }

    template <>
    ast::node::BufferType * component_allocator<ast::node::BufferType>::operator () (ast::node::BufferType && other) const {
        return new ast::node::BufferType{std::move(other)};
    }

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

    template <>
    void component_deleter<ast::node::ConstType>::operator () (ast::node::ConstType * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::ConstType * component_allocator<ast::node::ConstType>::operator () (ast::node::ConstType const & other) const {
        return new ast::node::ConstType{other};
    }

    template <>
    ast::node::ConstType * component_allocator<ast::node::ConstType>::operator () (ast::node::ConstType && other) const {
        return new ast::node::ConstType{std::move(other)};
    }

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

    template <>
    void component_deleter<ast::node::FunctionType>::operator () (ast::node::FunctionType * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::FunctionType * component_allocator<ast::node::FunctionType>::operator () (ast::node::FunctionType const & other) const {
        return new ast::node::FunctionType{other};
    }

    template <>
    ast::node::FunctionType * component_allocator<ast::node::FunctionType>::operator () (ast::node::FunctionType && other) const {
        return new ast::node::FunctionType{std::move(other)};
    }

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

    template <>
    void component_deleter<ast::node::InType>::operator () (ast::node::InType * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::InType * component_allocator<ast::node::InType>::operator () (ast::node::InType const & other) const {
        return new ast::node::InType{other};
    }

    template <>
    ast::node::InType * component_allocator<ast::node::InType>::operator () (ast::node::InType && other) const {
        return new ast::node::InType{std::move(other)};
    }

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

    template <>
    void component_deleter<ast::node::OutType>::operator () (ast::node::OutType * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::OutType * component_allocator<ast::node::OutType>::operator () (ast::node::OutType const & other) const {
        return new ast::node::OutType{other};
    }

    template <>
    ast::node::OutType * component_allocator<ast::node::OutType>::operator () (ast::node::OutType && other) const {
        return new ast::node::OutType{std::move(other)};
    }

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

    template <>
    void component_deleter<ast::node::TupleType>::operator () (ast::node::TupleType * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::TupleType * component_allocator<ast::node::TupleType>::operator () (ast::node::TupleType const & other) const {
        return new ast::node::TupleType{other};
    }

    template <>
    ast::node::TupleType * component_allocator<ast::node::TupleType>::operator () (ast::node::TupleType && other) const {
        return new ast::node::TupleType{std::move(other)};
    }

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

    template <>
    void component_deleter<ast::node::TypeDecl>::operator () (ast::node::TypeDecl * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::TypeDecl * component_allocator<ast::node::TypeDecl>::operator () (ast::node::TypeDecl const & other) const {
        return new ast::node::TypeDecl{other};
    }

    template <>
    ast::node::TypeDecl * component_allocator<ast::node::TypeDecl>::operator () (ast::node::TypeDecl && other) const {
        return new ast::node::TypeDecl{std::move(other)};
    }

    display_result ast::node::TypeDecl::display () const {
        return "type " + cynth::display(name);
    }

    ast::type_eval_result ast::node::TypeDecl::eval_type (sem::context &) const {
        return ast::make_type_eval_result(result_error{"Capturing type deduction is not supported yet."});
    }

    //// TypeName ////

    template <>
    void component_deleter<ast::node::TypeName>::operator () (ast::node::TypeName * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::TypeName * component_allocator<ast::node::TypeName>::operator () (ast::node::TypeName const & other) const {
        return new ast::node::TypeName{other};
    }

    template <>
    ast::node::TypeName * component_allocator<ast::node::TypeName>::operator () (ast::node::TypeName && other) const {
        return new ast::node::TypeName{std::move(other)};
    }

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
