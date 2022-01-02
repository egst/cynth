#include "sem/compound.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::sem::TypedExpression;
    using cynth::sem::TypedName;
    using cynth::sem::TypedTargetExpression;
    using cynth::sem::Return;
    using cynth::sem::Returned;
    using cynth::sem::Variable;
    using cynth::sem::ResolvedValue;
    using cynth::sem::ResolvedTarget;
    using cynth::sem::ResolvedCapture;
    using cynth::sem::Closure;

    template <>
    void component_deleter<TypedExpression>::operator () (TypedExpression * ptr) const {
        delete ptr;
    }

    template <>
    TypedExpression * component_allocator<TypedExpression>::operator () (TypedExpression const & other) const {
        return new TypedExpression{other};
    }

    template <>
    TypedExpression * component_allocator<TypedExpression>::operator () (TypedExpression && other) const {
        return new TypedExpression{std::move(other)};
    }

    template <>
    void component_deleter<TypedName>::operator () (TypedName * ptr) const {
        delete ptr;
    }

    template <>
    TypedName * component_allocator<TypedName>::operator () (TypedName const & other) const {
        return new TypedName{other};
    }

    template <>
    TypedName * component_allocator<TypedName>::operator () (TypedName && other) const {
        return new TypedName{std::move(other)};
    }

    template <>
    void component_deleter<TypedTargetExpression>::operator () (TypedTargetExpression * ptr) const {
        delete ptr;
    }

    template <>
    TypedTargetExpression * component_allocator<TypedTargetExpression>::operator () (
        TypedTargetExpression const & other
    ) const {
        return new TypedTargetExpression{other};
    }

    template <>
    TypedTargetExpression * component_allocator<TypedTargetExpression>::operator () (
        TypedTargetExpression && other
    ) const {
        return new TypedTargetExpression{std::move(other)};
    }

    template <>
    void component_deleter<Return>::operator () (Return * ptr) const {
        delete ptr;
    }

    template <>
    Return * component_allocator<Return>::operator () (Return const & other) const {
        return new Return{other};
    }

    template <>
    Return * component_allocator<Return>::operator () (Return && other) const {
        return new Return{std::move(other)};
    }

    template <>
    void component_deleter<Returned>::operator () (Returned * ptr) const {
        delete ptr;
    }

    template <>
    Returned * component_allocator<Returned>::operator () (Returned const & other) const {
        return new Returned{other};
    }

    template <>
    Returned * component_allocator<Returned>::operator () (Returned && other) const {
        return new Returned{std::move(other)};
    }

    template <>
    void component_deleter<Variable>::operator () (Variable * ptr) const {
        delete ptr;
    }

    template <>
    Variable * component_allocator<Variable>::operator () (Variable const & other) const {
        return new Variable{other};
    }

    template <>
    Variable * component_allocator<Variable>::operator () (Variable && other) const {
        return new Variable{std::move(other)};
    }

    template <>
    void component_deleter<ResolvedValue>::operator () (ResolvedValue * ptr) const {
        delete ptr;
    }

    template <>
    ResolvedValue * component_allocator<ResolvedValue>::operator () (ResolvedValue const & other) const {
        return new ResolvedValue{other};
    }

    template <>
    ResolvedValue * component_allocator<ResolvedValue>::operator () (ResolvedValue && other) const {
        return new ResolvedValue{std::move(other)};
    }

    template <>
    void component_deleter<ResolvedTarget>::operator () (ResolvedTarget * ptr) const {
        delete ptr;
    }

    template <>
    ResolvedTarget * component_allocator<ResolvedTarget>::operator () (ResolvedTarget const & other) const {
        return new ResolvedTarget{other};
    }

    template <>
    ResolvedTarget * component_allocator<ResolvedTarget>::operator () (ResolvedTarget && other) const {
        return new ResolvedTarget{std::move(other)};
    }

    template <>
    void component_deleter<ResolvedCapture>::operator () (ResolvedCapture * ptr) const {
        delete ptr;
    }

    template <>
    ResolvedCapture * component_allocator<ResolvedCapture>::operator () (ResolvedCapture const & other) const {
        return new ResolvedCapture{other};
    }

    template <>
    ResolvedCapture * component_allocator<ResolvedCapture>::operator () (ResolvedCapture && other) const {
        return new ResolvedCapture{std::move(other)};
    }

    template <>
    void component_deleter<Closure>::operator () (Closure * ptr) const {
        delete ptr;
    }

    template <>
    Closure * component_allocator<Closure>::operator () (Closure const & other) const {
        return new Closure{other};
    }

    template <>
    Closure * component_allocator<Closure>::operator () (Closure && other) const {
        return new Closure{std::move(other)};
    }

}
