#include "syn/nodes/range_declarations.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::syn::node::RangeDecl;
    using cynth::syn::node::TupleRangeDecl;

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

        syn::execution_result decl_execute (auto const & node, sem::context & ctx) {
            auto decls_result = util::unite_results(sem::complete(syn::eval_decl(ctx)(node)));
            if (!decls_result)
                return syn::make_execution_result(decls_result.error());
            auto decls = *std::move(decls_result);

            auto decl_result = ctx.declare(decls);
            if (!decl_result)
                return syn::make_execution_result(decl_result.error());

            return {};
        }

    }

    //// RangeDecl ////

    display_result syn::node::RangeDecl::display () const {
        return cynth::display(declaration) + " in " + cynth::display(range);
    }

    syn::range_decl_eval_result syn::node::RangeDecl::eval_range_decl (sem::context & ctx) const {
        auto decl_result = util::unite_results(syn::eval_decl(ctx)(declaration));
        if (!decl_result)
            return syn::make_range_decl_eval_result(decl_result.error());
        auto range_result = util::single(syn::evaluate(ctx)(range));
        if (!range_result)
            return syn::make_range_decl_eval_result(decl_result.error());
        return syn::make_range_decl_eval_result(sem::incomplete_range_decl {
            .declaration = *decl_result,
            .range       = *range_result
        });
    }

    //// TupleRangeDecl ////

    display_result syn::node::TupleRangeDecl::display () const {
        return "(" + util::join(", ", cynth::display(declarations)) + ")";
    }

    syn::range_decl_eval_result syn::node::TupleRangeDecl::eval_range_decl (sem::context & ctx) const {
        syn::range_decl_eval_result result;
        for (auto & value_tuple : syn::eval_range_decl(ctx)(declarations)) for (auto & value : value_tuple) {
            result.push_back(std::move(value));
        }
        return result;
    }

}
#endif
