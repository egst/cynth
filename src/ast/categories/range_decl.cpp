#include "ast/categories/range_decl.hpp"

#include "component.hpp"

namespace cynth {

    template <>
    void component_deleter<ast::category::RangeDecl>::operator () (ast::category::RangeDecl * ptr) const {
        delete ptr;
    }

    template <>
    ast::category::RangeDecl * component_allocator<ast::category::RangeDecl>::operator () (ast::category::RangeDecl const & other) const {
        return new ast::category::RangeDecl{other};
    }

    template <>
    ast::category::RangeDecl * component_allocator<ast::category::RangeDecl>::operator () (ast::category::RangeDecl && other) const {
        return new ast::category::RangeDecl{std::move(other)};
    }

}
