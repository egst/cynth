#include "ast/categories/type.hpp"

#include "component.hpp"

namespace cynth {

    template <>
    void component_deleter<ast::category::Type>::operator () (ast::category::Type * ptr) const {
        delete ptr;
    };

    template <>
    ast::category::Type * component_allocator<ast::category::Type>::operator () (ast::category::Type const & other) const {
        return new ast::category::Type{other};
    };

    template <>
    ast::category::Type * component_allocator<ast::category::Type>::operator () (ast::category::Type && other) const {
        return new ast::category::Type{std::move(other)};
    };

}
