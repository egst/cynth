#include "ast/nodes/range_declarations.hpp"

#include "esl/component.hpp"

// Note: These are dependencies of nodes/range_declarations.hpp, but are only forward declared there:
#include "ast/categories/range_declaration.hpp"

namespace esl {

    using cynth::ast::node::RangeDecl;
    using cynth::ast::node::TupleRangeDecl;

    template <>
    void component_deleter<RangeDecl>::operator () (RangeDecl * ptr) const {
        delete ptr;
    }

    template <>
    RangeDecl * component_allocator<RangeDecl>::operator () (RangeDecl const & other) const {
        return new RangeDecl{other};
    }

    template <>
    RangeDecl * component_allocator<RangeDecl>::operator () (RangeDecl && other) const {
        return new RangeDecl{std::move(other)};
    }

    template <>
    void component_deleter<TupleRangeDecl>::operator () (TupleRangeDecl * ptr) const {
        delete ptr;
    }

    template <>
    TupleRangeDecl * component_allocator<TupleRangeDecl>::operator () (
        TupleRangeDecl const & other
    ) const {
        return new TupleRangeDecl{other};
    }

    template <>
    TupleRangeDecl * component_allocator<TupleRangeDecl>::operator () (
        TupleRangeDecl && other
    ) const {
        return new TupleRangeDecl{std::move(other)};
    }

}

// TODO
#if 0
namespace cynth {

    namespace {

        ast::execution_result decl_execute (auto const & node, sem::context & ctx) {
            auto decls_result = util::unite_results(sem::complete(ast::eval_decl(ctx)(node)));
            if (!decls_result)
                return ast::make_execution_result(decls_result.error());
            auto decls = *std::move(decls_result);

            auto decl_result = ctx.declare(decls);
            if (!decl_result)
                return ast::make_execution_result(decl_result.error());

            return {};
        }

    }

    //// RangeDecl ////

    display_result ast::node::RangeDecl::display () const {
        return cynth::display(declaration) + " in " + cynth::display(range);
    }

    ast::range_decl_eval_result ast::node::RangeDecl::eval_range_decl (sem::context & ctx) const {
        auto decl_result = util::unite_results(ast::eval_decl(ctx)(declaration));
        if (!decl_result)
            return ast::make_range_decl_eval_result(decl_result.error());
        auto range_result = util::single(ast::evaluate(ctx)(range));
        if (!range_result)
            return ast::make_range_decl_eval_result(decl_result.error());
        return ast::make_range_decl_eval_result(sem::incomplete_range_decl {
            .declaration = *decl_result,
            .range       = *range_result
        });
    }

    //// TupleRangeDecl ////

    display_result ast::node::TupleRangeDecl::display () const {
        return "(" + util::join(", ", cynth::display(declarations)) + ")";
    }

    ast::range_decl_eval_result ast::node::TupleRangeDecl::eval_range_decl (sem::context & ctx) const {
        ast::range_decl_eval_result result;
        for (auto & value_tuple : ast::eval_range_decl(ctx)(declarations)) for (auto & value : value_tuple) {
            result.push_back(std::move(value));
        }
        return result;
    }

}
#endif
