#include "asg/declarations.hpp"

#include "asg/types.hpp"
#include "component.hpp"


namespace cynth {

    template <>
    void component_deleter<asg::complete_decl>::operator () (asg::complete_decl * ptr) const {
        delete ptr;
    };

    template <>
    asg::complete_decl * component_allocator<asg::complete_decl>::operator () (asg::complete_decl const & other) const {
        return new asg::complete_decl{other};
    };

    template <>
    asg::complete_decl * component_allocator<asg::complete_decl>::operator () (asg::complete_decl && other) const {
        return new asg::complete_decl{std::move(other)};
    };

    template <>
    void component_deleter<asg::incomplete_decl>::operator () (asg::incomplete_decl * ptr) const {
        delete ptr;
    };

    template <>
    asg::incomplete_decl * component_allocator<asg::incomplete_decl>::operator () (asg::incomplete_decl const & other) const {
        return new asg::incomplete_decl{other};
    };

    template <>
    asg::incomplete_decl * component_allocator<asg::incomplete_decl>::operator () (asg::incomplete_decl && other) const {
        return new asg::incomplete_decl{std::move(other)};
    };

    template <>
    void component_deleter<asg::type_decl>::operator () (asg::type_decl * ptr) const {
        delete ptr;
    };

    template <>
    asg::type_decl * component_allocator<asg::type_decl>::operator () (asg::type_decl const & other) const {
        return new asg::type_decl{other};
    };

    template <>
    asg::type_decl * component_allocator<asg::type_decl>::operator () (asg::type_decl && other) const {
        return new asg::type_decl{std::move(other)};
    };

}
