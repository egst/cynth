#include "syn/categories/pattern.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::syn::category::Pattern;

    template <>
    void component_deleter<Pattern>::operator () (Pattern * ptr) const {
        delete ptr;
    }

    template <>
    Pattern * component_allocator<Pattern>::operator () (Pattern const & other) const {
        return new Pattern{other};
    }

    template <>
    Pattern * component_allocator<Pattern>::operator () (Pattern && other) const {
        return new Pattern{std::move(other)};
    }

}
