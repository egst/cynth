#include "context.hpp"

#include "config.hpp"
#include "context_types.hpp"

namespace cynth {

    template <>
    void component_deleter<context>::operator () (context * ptr) const {
        delete ptr;
    }

    template <>
    context * component_allocator<context>::operator () (context const & other) const {
        return new context{other};
    }

    template <>
    context * component_allocator<context>::operator () (context && other) const {
        return new context{std::move(other)};
    }

    context::context (): parent{nullptr} {}

    result<void> context::define_value (std::string name, typed_value const & v) {
        if (find_value_inside(name))
            return result_error{"Cannot redefine a value in the same scope."};
        values.insert({name, v});
        return {};
    }

    result<void> context::define_value (std::string name, value_vector const & v) {
        if (find_value_inside(name))
            return result_error{"Cannot redefine a value in the same scope."};
        values.insert({name, {v, asg::value_type(v)}});
        return {};
    }

    result<void> context::define_type (std::string name, type_vector const & t) {
        if (find_type_inside(name))
            return result_error{"Cannot redefine a type in the same scope."};
        types.insert({name, t});
        return {};
    }

    typed_value * context::find_value_inside (std::string const & name) {
        auto iter = values.find(name);
        return iter != values.end()
            ? &iter->second
            : nullptr;
    }

    type_vector * context::find_type_inside (std::string const & name) {
        auto iter = types.find(name);
        return iter != types.end()
            ? &iter->second
            : nullptr;
    }

    typed_value * context::find_value (std::string const & name) {
        auto inside = find_value_inside(name);
        if (!parent || inside)
            return inside;
        return parent->find_value(name);
    }

    type_vector * context::find_type (std::string const & name) {
        auto inside = find_type_inside(name);
        if (!parent || inside)
            return inside;
        return parent->find_type(name);
    }

    context make_child_context (context & parent) {
        context ctx;
        ctx.parent = &parent;
        return ctx;
    }

    template <typename Value>
    refval_container<Value> & context::stored_values () {
        auto & stored = std::get<std::optional<refval_container<Value>>>(referential);
        if (stored)
            return *stored;
        if (!parent) {
            stored = refval_container<Value>{};
            return *stored;
        }
        return parent->stored_values<Value>();
    }

    template refval_container<asg::value::InValue>     & context::stored_values ();
    template refval_container<asg::value::OutValue>    & context::stored_values ();
    template refval_container<asg::value::ArrayValue>  & context::stored_values ();
    template refval_container<asg::value::BufferValue> & context::stored_values ();

    template <typename Value>
    reference_result<Value> context::store_value (Value const & v) {
        auto & stored = stored_values<Value>();
        stored.push_front(v);
        return stored.front();
    }

    template reference_result<asg::value::InValue>     context::store_value (asg::value::InValue     const &);
    template reference_result<asg::value::OutValue>    context::store_value (asg::value::OutValue    const &);
    template reference_result<asg::value::ArrayValue>  context::store_value (asg::value::ArrayValue  const &);
    template reference_result<asg::value::BufferValue> context::store_value (asg::value::BufferValue const &);

}
