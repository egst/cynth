#include "ast/categories/statement.hpp"

#include "esl/component.hpp"

// Note: These are dependencies of nodes/expression.hpp, but are only forward declared there:
#include "ast/categories/array_element.hpp"

namespace esl {

    using cynth::ast::category::Statement;

    template <>
    void component_deleter<Statement>::operator () (Statement * ptr) const {
        delete ptr;
    }

    template <>
    Statement * component_allocator<Statement>::operator () (Statement const & other) const {
        return new Statement{other};
    }

    template <>
    Statement * component_allocator<Statement>::operator () (Statement && other) const {
        return new Statement{std::move(other)};
    }

}
