#include "ast/categories/type.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::ast::category::Type;

    template <>
    void component_deleter<Type>::operator () (Type * ptr) const {
        delete ptr;
    }

    template <>
    Type * component_allocator<Type>::operator () (Type const & other) const {
        return new Type{other};
    }

    template <>
    Type * component_allocator<Type>::operator () (Type && other) const {
        return new Type{std::move(other)};
    }

}
