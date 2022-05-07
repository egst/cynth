#include "sem/declarations.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::sem::CompleteDeclaration;
    using cynth::sem::IncompleteDeclaration;
    using cynth::sem::TypeDeclaration;

    template <>
    void component_deleter<CompleteDeclaration>::operator () (CompleteDeclaration * ptr) const {
        delete ptr;
    }

    template <>
    CompleteDeclaration * component_allocator<CompleteDeclaration>::operator () (
        CompleteDeclaration const & other
    ) const {
        return new CompleteDeclaration{other};
    }

    template <>
    CompleteDeclaration * component_allocator<CompleteDeclaration>::operator () (CompleteDeclaration && other) const {
        return new CompleteDeclaration{std::move(other)};
    }

    template <>
    void component_deleter<IncompleteDeclaration>::operator () (IncompleteDeclaration * ptr) const {
        delete ptr;
    }

    template <>
    IncompleteDeclaration * component_allocator<IncompleteDeclaration>::operator () (
        IncompleteDeclaration const & other
    ) const {
        return new IncompleteDeclaration{other};
    }

    template <>
    IncompleteDeclaration * component_allocator<IncompleteDeclaration>::operator () (
        IncompleteDeclaration && other
    ) const {
        return new IncompleteDeclaration{std::move(other)};
    }

    template <>
    void component_deleter<TypeDeclaration>::operator () (TypeDeclaration * ptr) const {
        delete ptr;
    }

    template <>
    TypeDeclaration * component_allocator<TypeDeclaration>::operator () (TypeDeclaration const & other) const {
        return new TypeDeclaration{other};
    }

    template <>
    TypeDeclaration * component_allocator<TypeDeclaration>::operator () (TypeDeclaration && other) const {
        return new TypeDeclaration{std::move(other)};
    }

}
