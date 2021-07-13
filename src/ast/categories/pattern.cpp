#include "ast/categories/pattern.hpp"

#include "ast/categories/array_elem.hpp"
#include "ast/categories/statement.hpp"
#include "component.hpp"

namespace cynth {

    template <>
    void component_deleter<ast::category::Pattern>::operator () (ast::category::Pattern * ptr) const {
        delete ptr;
    }

    template <>
    ast::category::Pattern * component_allocator<ast::category::Pattern>::operator () (ast::category::Pattern const & other) const {
        return new ast::category::Pattern{other};
    }

    template <>
    ast::category::Pattern * component_allocator<ast::category::Pattern>::operator () (ast::category::Pattern && other) const {
        return new ast::category::Pattern{std::move(other)};
    }

}
