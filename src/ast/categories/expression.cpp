#include "ast/categories/expression.hpp"

#include "esl/component.hpp"

// Note: These are dependencies of nodes/expression.hpp, but are only forward declared there:
#include "ast/categories/array_element.hpp"
#include "ast/categories/statement.hpp"

namespace esl {

    using cynth::ast::category::Expression;

    template <>
    void component_deleter<Expression>::operator () (Expression * ptr) const {
        delete ptr;
    }

    template <>
    Expression * component_allocator<Expression>::operator () (Expression const & other) const {
        return new Expression{other};
    }

    template <>
    Expression * component_allocator<Expression>::operator () (Expression && other) const {
        return new Expression{std::move(other)};
    }

}
