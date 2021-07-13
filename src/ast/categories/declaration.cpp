#include "ast/categories/declaration.hpp"

#include "component.hpp"

namespace cynth {

    template <>
    void component_deleter<ast::category::Declaration>::operator () (ast::category::Declaration * ptr) const {
        delete ptr;
    }

    template <>
    ast::category::Declaration * component_allocator<ast::category::Declaration>::operator () (ast::category::Declaration const & other) const {
        return new ast::category::Declaration{other};
    }

    template <>
    ast::category::Declaration * component_allocator<ast::category::Declaration>::operator () (ast::category::Declaration && other) const {
        return new ast::category::Declaration{std::move(other)};
    }

}
