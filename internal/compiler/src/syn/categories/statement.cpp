#include "syn/categories/statement.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::syn::category::Statement;

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
