#include "context.hpp"

namespace cynth {

    template <>
    void component_deleter<context>::operator () (context * ptr) const {
        delete ptr;
    };

    template <>
    context * component_allocator<context>::operator () (context const & other) const {
        return new context{other};
    };

    template <>
    context * component_allocator<context>::operator () (context && other) const {
        return new context{std::move(other)};
    };

    context make_child_context (context & parent) {
        context ctx;
        ctx.parent = &parent;
        return ctx;
    }

}
