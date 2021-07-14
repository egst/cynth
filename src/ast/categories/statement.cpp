#include "ast/categories/statement.hpp"

#include "ast/categories/array_elem.hpp"
#include "ast/categories/range_decl.hpp"
#include "component.hpp"

namespace cynth {

    template <>
    void component_deleter<ast::category::Statement>::operator () (ast::category::Statement * ptr) const {
        delete ptr;
    }

    template <>
    ast::category::Statement * component_allocator<ast::category::Statement>::operator () (ast::category::Statement const & other) const {
        return new ast::category::Statement{other};
    }

    template <>
    ast::category::Statement * component_allocator<ast::category::Statement>::operator () (ast::category::Statement && other) const {
        return new ast::category::Statement{std::move(other)};
    }

}
