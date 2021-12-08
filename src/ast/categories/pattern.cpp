#include "ast/categories/pattern.hpp"

#include "esl/component.hpp"

// Note: These are dependencies of nodes/expression.hpp, but are only forward declared there:
#include "ast/categories/array_element.hpp"
#include "ast/categories/statement.hpp"

namespace esl {

    using cynth::ast::category::Pattern;

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
