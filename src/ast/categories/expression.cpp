#include "ast/categories/expression.hpp"

#include "esl/component.hpp"

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
