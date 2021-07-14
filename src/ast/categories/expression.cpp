#include "ast/categories/expression.hpp"

#include "ast/categories/array_elem.hpp"
#include "ast/categories/statement.hpp"
#include "ast/categories/range_decl.hpp"
#include "component.hpp"

namespace cynth {

    template <>
    void component_deleter<ast::category::Expression>::operator () (ast::category::Expression * ptr) const {
        delete ptr;
    }

    template <>
    ast::category::Expression * component_allocator<ast::category::Expression>::operator () (ast::category::Expression const & other) const {
        return new ast::category::Expression{other};
    }

    template <>
    ast::category::Expression * component_allocator<ast::category::Expression>::operator () (ast::category::Expression && other) const {
        return new ast::category::Expression{std::move(other)};
    }

}
