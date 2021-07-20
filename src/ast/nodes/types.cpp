#include "ast/nodes/types.hpp"

#include "ast/categories/expression.hpp"
#include "ast/categories/pattern.hpp"
#include "ast/categories/type.hpp"
#include "ast/interface.hpp"
#include "asg/interface.hpp"
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

    std::string ast::node::ArrayType::display () const {
        //return ast::display(type) + " [" + util::coalesce(ast::display(size) ?: "") + "]";
        //return ast::display(type) + " [" + util::coalesce(ast::display(size), "") + "]";
        return ast::display(type) + " [" + ast::display(size).value_or("$") + "]";
    }

    // vector<result<type::incomplete>>
    ast::type_eval_result ast::node::ArrayType::eval_type (context & ctx) const {
        auto type_result = util::unite_results(ast::eval_type(ctx)(type));
        if (!type_result)
            return ast::make_type_eval_result(type_result.error());
        auto type = *std::move(type_result);

        auto size_result = lift::category_component{util::overload {
            [&ctx] <ast::interface::expression Expr> (Expr && e) -> result<asg::value::incomplete> {
                auto result = asg::convert(asg::type::Int{})(util::single(ast::evaluate(ctx)(e)));
                if (!result)
                    return result.error();
                return asg::value::incomplete{*std::move(result)};
            },
            [] <ast::interface::declaration Decl> (Decl &&) -> result<asg::value::incomplete> {
                return result_error{"Capturing array size deduction is not supported yet."};
            },
        }} (size);
        asg::value::incomplete size = (size_result && *size_result)
            ? **size_result
            : asg::value::unknown{};

        return ast::make_type_eval_result(asg::type::array_type<false> {
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

    std::string ast::node::Auto::display () const {
        return "$";
    }

    ast::type_eval_result ast::node::Auto::eval_type (context &) const {
        return ast::make_type_eval_result(asg::type::unknown{});
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

    std::string ast::node::BufferType::display () const {
        return "buffer [" + ast::display(size) + "]";
    }

    ast::type_eval_result ast::node::BufferType::eval_type (context & ctx) const {
        auto size_result = asg::convert(asg::type::Int{})(util::single(ast::evaluate(ctx)(size)));
        if (!size_result)
            return ast::make_type_eval_result(size_result.error());
        auto size = asg::value::incomplete{*std::move(size_result)};
        // TODO: Decide whether a pattern should be allowed here.

        return ast::make_type_eval_result(asg::type::buffer_type<false> {
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

    std::string ast::node::ConstType::display () const {
        return ast::display(type) + " const";
    }

    ast::type_eval_result ast::node::ConstType::eval_type (context & ctx) const {
        auto types_result = ast::eval_type(ctx)(type);

        return lift::evaluation{util::overload {
            [] (asg::type::const_type<false> && type) -> result<asg::type::incomplete> {
                return {type};
            },
            [] (asg::type::in_type<false> &&) -> result<asg::type::incomplete> {
                return result_error{"In type cannot be const."};
            },
            [] (asg::type::out_type<false> &&) -> result<asg::type::incomplete> {
                return result_error{"Out type cannot be const."};
            },
            [] (asg::type::buffer_type<false> &&) -> result<asg::type::incomplete> {
                return result_error{"Buffer type cannot be const."};
            },
            [] (asg::type::function_type<false> && type) -> result<asg::type::incomplete> {
                return {type}; // Function type is implicitly const.
            },
            [] <util::temporary Type> (Type && type) -> result<asg::type::incomplete> {
                return {asg::type::const_type<false> {
                    .type = make_component(asg::type::incomplete{std::move(type)})
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

    std::string ast::node::FunctionType::display () const {
        return ast::display(output) + " " + util::parenthesized(ast::display(input));
    }

    ast::type_eval_result ast::node::FunctionType::eval_type (context & ctx) const {
        auto out_result = util::unite_results(ast::eval_type(ctx)(output));
        if (!out_result)
            return ast::make_type_eval_result(out_result.error());
        auto out = *std::move(out_result);

        auto in_result = util::unite_results(ast::eval_type(ctx)(input));
        if (!in_result)
            return ast::make_type_eval_result(in_result.error());
        auto in = *std::move(in_result);

        return ast::make_type_eval_result(asg::type::function_type<false> {
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

    std::string ast::node::InType::display () const {
        return ast::display(type) + " in";
    }

    ast::type_eval_result ast::node::InType::eval_type (context & ctx) const {
        auto types_result = ast::eval_type(ctx)(type);

        return lift::evaluation{util::overload {
            [] (asg::type::in_type<false> && type) -> result<asg::type::incomplete> {
                return {type};
            },
            [] (asg::type::out_type<false> &&) -> result<asg::type::incomplete> {
                return result_error{"Cannot combine in and out type modifiers."};
            },
            [] (asg::type::const_type<false> &&) -> result<asg::type::incomplete> {
                return result_error{"In type cannot be const."};
            },
            [] (asg::type::array_type<false> &&) -> result<asg::type::incomplete> {
                return result_error{"Array cannot be an in type."};
            },
            [] (asg::type::buffer_type<false> &&) -> result<asg::type::incomplete> {
                return result_error{"Buffer in types are not supported yet."};
            },
            [] (asg::type::function_type<false> &&) -> result<asg::type::incomplete> {
                return result_error{"Function cannot be an in type."};
            },
            [] <util::temporary Type> (Type && type) -> result<asg::type::incomplete> {
                return {asg::type::in_type<false> {
                    .type = make_component(asg::type::incomplete{std::move(type)})
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

    std::string ast::node::OutType::display () const {
        return ast::display(type) + " out";
    }

    ast::type_eval_result ast::node::OutType::eval_type (context & ctx) const {
        auto types_result = ast::eval_type(ctx)(type);

        return lift::evaluation{util::overload {
            [] (asg::type::out_type<false> && type) -> result<asg::type::incomplete> {
                return {type};
            },
            [] (asg::type::in_type<false> &&) -> result<asg::type::incomplete> {
                return result_error{"Cannot combine in and out type modifiers."};
            },
            [] (asg::type::const_type<false> &&) -> result<asg::type::incomplete> {
                return result_error{"Out type cannot be const."};
            },
            [] (asg::type::array_type<false> &&) -> result<asg::type::incomplete> {
                return result_error{"Array out types are not supported yet."};
            },
            [] (asg::type::buffer_type<false> &&) -> result<asg::type::incomplete> {
                // TODO
                return result_error{"Buffer out types are not supported yet."};
            },
            [] (asg::type::function_type<false> &&) -> result<asg::type::incomplete> {
                return result_error{"Function cannot be an out type."};
            },
            [] <util::temporary Type> (Type && type) -> result<asg::type::incomplete> {
                return {asg::type::out_type<false> {
                    .type = make_component(asg::type::incomplete{std::move(type)})
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

    std::string ast::node::TupleType::display () const {
        return "(" + util::join(", ", ast::display(types)) + ")";
    }

    ast::type_eval_result ast::node::TupleType::eval_type (context & ctx) const {
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

    std::string ast::node::TypeDecl::display () const {
        return "type " + ast::display(name);
    }

    ast::type_eval_result ast::node::TypeDecl::eval_type (context &) const {
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

    std::string ast::node::TypeName::display () const {
        return *name;
    }

    ast::type_eval_result ast::node::TypeName::eval_type (context & ctx) const {
        auto value = ctx.find_type(*name);
        return value
            ? asg::incomplete(lift::tuple_vector{make_result}(*value))
            : ast::make_type_eval_result(result_error{"Type name not found."});
    }

}
