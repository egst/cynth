#include "ast/categories/array_element.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::ast::category::ArrayElement;

    template <>
    void component_deleter<ArrayElement>::operator () (ArrayElement * ptr) const {
        delete ptr;
    }

    template <>
    ArrayElement * component_allocator<ArrayElement>::operator () (ArrayElement const & other) const {
        return new ArrayElement{other};
    }

    template <>
    ArrayElement * component_allocator<ArrayElement>::operator () (ArrayElement && other) const {
        return new ArrayElement{std::move(other)};
    }

}
