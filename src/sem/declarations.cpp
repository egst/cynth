#include "sem/declarations.hpp"

#include "sem/types.hpp"
#include "component.hpp"


namespace cynth {

    template <>
    void component_deleter<sem::complete_decl>::operator () (sem::complete_decl * ptr) const {
        delete ptr;
    }

    template <>
    sem::complete_decl * component_allocator<sem::complete_decl>::operator () (sem::complete_decl const & other) const {
        return new sem::complete_decl{other};
    }

    template <>
    sem::complete_decl * component_allocator<sem::complete_decl>::operator () (sem::complete_decl && other) const {
        return new sem::complete_decl{std::move(other)};
    }

    template <>
    void component_deleter<sem::incomplete_decl>::operator () (sem::incomplete_decl * ptr) const {
        delete ptr;
    }

    template <>
    sem::incomplete_decl * component_allocator<sem::incomplete_decl>::operator () (sem::incomplete_decl const & other) const {
        return new sem::incomplete_decl{other};
    }

    template <>
    sem::incomplete_decl * component_allocator<sem::incomplete_decl>::operator () (sem::incomplete_decl && other) const {
        return new sem::incomplete_decl{std::move(other)};
    }

    template <>
    void component_deleter<sem::type_decl>::operator () (sem::type_decl * ptr) const {
        delete ptr;
    }

    template <>
    sem::type_decl * component_allocator<sem::type_decl>::operator () (sem::type_decl const & other) const {
        return new sem::type_decl{other};
    }

    template <>
    sem::type_decl * component_allocator<sem::type_decl>::operator () (sem::type_decl && other) const {
        return new sem::type_decl{std::move(other)};
    }

}
