#include "component.hpp"

#include "config.hpp"

#include <string>

namespace cynth {

    // Yeah, I know it makes no sense to heap-allocate the std::string value container,
    // but weird stuff is happening otherwise for some reason, which needs to be fixed,
    // but right now this is the quick workaround. (TODO)

    template <>
    void component_deleter<std::string>::operator () (std::string * ptr) const {
        delete ptr;
    }

    template <>
    std::string * component_allocator<std::string>::operator () (std::string const & other) const {
        return new std::string{other};
    }

    template <>
    std::string * component_allocator<std::string>::operator () (std::string && other) const {
        return new std::string{std::move(other)};
    }

}
