#include "ast/categories/array_elem.hpp"

#include "ast/categories/statement.hpp"
#include "component.hpp"

namespace cynth {

    template <>
    void component_deleter<ast::category::ArrayElem>::operator () (ast::category::ArrayElem * ptr) const {
        delete ptr;
    }

    template <>
    ast::category::ArrayElem * component_allocator<ast::category::ArrayElem>::operator () (ast::category::ArrayElem const & other) const {
        return new ast::category::ArrayElem{other};
    }

    template <>
    ast::category::ArrayElem * component_allocator<ast::category::ArrayElem>::operator () (ast::category::ArrayElem && other) const {
        return new ast::category::ArrayElem{std::move(other)};
    }

}
