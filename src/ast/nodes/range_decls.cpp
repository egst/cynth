#include "ast/nodes/range_decls.hpp"

#include "ast/nodes/expressions.hpp"
#include "ast/categories/type.hpp"
#include "ast/categories/declaration.hpp"
#include "ast/categories/expression.hpp"
#include "ast/categories/range_decl.hpp"
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

    //// RangeDecl ////

    template <>
    void component_deleter<ast::node::RangeDecl>::operator () (ast::node::RangeDecl * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::RangeDecl * component_allocator<ast::node::RangeDecl>::operator () (ast::node::RangeDecl const & other) const {
        return new ast::node::RangeDecl{other};
    }

    template <>
    ast::node::RangeDecl * component_allocator<ast::node::RangeDecl>::operator () (ast::node::RangeDecl && other) const {
        return new ast::node::RangeDecl{std::move(other)};
    }

    std::string ast::node::RangeDecl::display () const {
        return ast::display(declaration) + " in " + ast::display(range);
    }

    //// TupleRangeDecl ////

    template <>
    void component_deleter<ast::node::TupleRangeDecl>::operator () (ast::node::TupleRangeDecl * ptr) const {
        delete ptr;
    }

    template <>
    ast::node::TupleRangeDecl * component_allocator<ast::node::TupleRangeDecl>::operator () (ast::node::TupleRangeDecl const & other) const {
        return new ast::node::TupleRangeDecl{other};
    }

    template <>
    ast::node::TupleRangeDecl * component_allocator<ast::node::TupleRangeDecl>::operator () (ast::node::TupleRangeDecl && other) const {
        return new ast::node::TupleRangeDecl{std::move(other)};
    }

    std::string ast::node::TupleRangeDecl::display () const {
        return "(" + util::join(", ", ast::display(declarations)) + ")";
    }

}
