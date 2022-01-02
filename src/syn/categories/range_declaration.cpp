#include "syn/categories/range_declaration.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::syn::category::RangeDeclaration;

    template <>
    void component_deleter<RangeDeclaration>::operator () (RangeDeclaration * ptr) const {
        delete ptr;
    }

    template <>
    RangeDeclaration * component_allocator<RangeDeclaration>::operator () (RangeDeclaration const & other) const {
        return new RangeDeclaration{other};
    }

    template <>
    RangeDeclaration * component_allocator<RangeDeclaration>::operator () (RangeDeclaration && other) const {
        return new RangeDeclaration{std::move(other)};
    }

}
