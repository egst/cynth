#include "ast/nodes/declarations.hpp"

#include "ast/nodes/expressions.hpp"
#include "ast/categories/type.hpp"
#include "ast/categories/declaration.hpp"
#include "ast/interface.hpp"
#include "asg/interface.hpp"
#include "asg/util.hpp"
#include "util/string.hpp"
#include "util/container.hpp"

#include <string>

namespace cynth {

    ast::execution_result decl_execute (auto const & node, context & ctx) {
        auto decls_result = util::unite_results(asg::complete(ast::eval_decl(ctx)(node)));
        if (!decls_result)
            return ast::make_execution_result(decls_result.error());
        auto decls = *std::move(decls_result);

        auto decl_result = asg::declare(ctx, decls);
        if (!decl_result)
            return ast::make_execution_result(decl_result.error());

        return {};
    }

    //// Declaration ////

    template <>
    void component_deleter<ast::node::Declaration>::operator () (ast::node::Declaration * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::Declaration * component_allocator<ast::node::Declaration>::operator () (ast::node::Declaration const & other) const {
        return new ast::node::Declaration{other};
    }

    template <>
    ast::node::Declaration * component_allocator<ast::node::Declaration>::operator () (ast::node::Declaration && other) const {
        return new ast::node::Declaration{std::move(other)};
    }

    std::string ast::node::Declaration::display () const {
        return ast::display(type) + " " + ast::display(name);
    }

    ast::decl_eval_result ast::node::Declaration::eval_decl (context & ctx) const {
        auto type_result = util::unite_results(ast::eval_type(ctx)(type)); // tuple_vector<result<type::incomplete>>
        if (!type_result)
            return ast::make_decl_eval_result(type_result.error());
        auto type = *std::move(type_result); // tuple_vector<type::incomplete>
        auto decl = asg::incomplete_decl {
            .type = std::move(type),
            .name = *name->name
        };
        return ast::make_decl_eval_result(decl);
    }

    ast::execution_result ast::node::Declaration::execute (context & ctx) const {
        return decl_execute(*this, ctx);
    }

    //// TupleDecl ////

    template <>
    void component_deleter<ast::node::TupleDecl>::operator () (ast::node::TupleDecl * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::TupleDecl * component_allocator<ast::node::TupleDecl>::operator () (ast::node::TupleDecl const & other) const {
        return new ast::node::TupleDecl{other};
    }

    template <>
    ast::node::TupleDecl * component_allocator<ast::node::TupleDecl>::operator () (ast::node::TupleDecl && other) const {
        return new ast::node::TupleDecl{std::move(other)};
    }

    std::string ast::node::TupleDecl::display () const {
        return "(" + util::join(", ", ast::display(declarations)) + ")";
    }

    ast::decl_eval_result ast::node::TupleDecl::eval_decl (context & ctx) const {
        decl_eval_result result;
        for (auto & value_tuple : ast::eval_decl(ctx)(declarations)) for (auto & value : value_tuple) {
            result.push_back(std::move(value));
        }
        return result;
    }

    ast::execution_result ast::node::TupleDecl::execute (context & ctx) const {
        return decl_execute(*this, ctx);
    }

}
