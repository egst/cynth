#include "ast/nodes/declarations.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::ast::node::Declaration;
    using cynth::ast::node::TupleDecl;

    template <>
    void component_deleter<Declaration>::operator () (Declaration * ptr) const {
        delete ptr;
    }

    template <>
    Declaration * component_allocator<Declaration>::operator () (Declaration const & other) const {
        return new Declaration{other};
    }

    template <>
    Declaration * component_allocator<Declaration>::operator () (Declaration && other) const {
        return new Declaration{std::move(other)};
    }

    template <>
    void component_deleter<TupleDecl>::operator () (TupleDecl * ptr) const {
        delete ptr;
    }

    template <>
    TupleDecl * component_allocator<TupleDecl>::operator () (TupleDecl const & other) const {
        return new TupleDecl{other};
    }

    template <>
    TupleDecl * component_allocator<TupleDecl>::operator () (TupleDecl && other) const {
        return new TupleDecl{std::move(other)};
    }

}

// TODO
#if 0
namespace cynth {

    namespace {

        ast::execution_result decl_execute (auto const & node, sem::context & ctx) {
            auto decls_result = util::unite_results(sem::complete(ctx)(ast::eval_decl(ctx)(node)));
            if (!decls_result)
                return ast::make_execution_result(decls_result.error());
            auto decls = *std::move(decls_result);

            auto decl_result = ctx.declare(decls);
            if (!decl_result)
                return ast::make_execution_result(decl_result.error());

            return {};
        }

    }

    //// Declaration ////

    display_result ast::node::Declaration::display () const {
        return cynth::display(type) + " " + cynth::display(name);
    }

    ast::decl_eval_result ast::node::Declaration::eval_decl (sem::context & ctx) const {
        auto type_result = util::unite_results(ast::eval_type(ctx)(type)); // tuple_vector<result<type::incomplete>>
        if (!type_result)
            return ast::make_decl_eval_result(type_result.error());
        auto type = *std::move(type_result); // tuple_vector<type::incomplete>
        auto decl = sem::incomplete_decl {
            .type = std::move(type),
            .name = *name->name
        };
        return ast::make_decl_eval_result(decl);
    }

    ast::execution_result ast::node::Declaration::execute (sem::context & ctx) const {
        return decl_execute(*this, ctx);
    }

    //// TupleDecl ////

    display_result ast::node::TupleDecl::display () const {
        return "(" + util::join(", ", cynth::display(declarations)) + ")";
    }

    ast::decl_eval_result ast::node::TupleDecl::eval_decl (sem::context & ctx) const {
        ast::decl_eval_result result;
        for (auto & value_tuple : ast::eval_decl(ctx)(declarations)) for (auto & value : value_tuple) {
            result.push_back(std::move(value));
        }
        return result;
    }

    ast::execution_result ast::node::TupleDecl::execute (sem::context & ctx) const {
        return decl_execute(*this, ctx);
    }

}
#endif
