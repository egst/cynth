#include "sem/values.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::sem::CompleteValue;
    using cynth::sem::IncompleteValue;

    template <>
    void component_deleter<CompleteValue>::operator () (CompleteValue * ptr) const {
        delete ptr;
    }

    template <>
    CompleteValue * component_allocator<CompleteValue>::operator () (CompleteValue const & other) const {
        return new CompleteValue{other};
    }

    template <>
    CompleteValue * component_allocator<CompleteValue>::operator () (CompleteValue && other) const {
        return new CompleteValue{std::move(other)};
    }

    template <>
    void component_deleter<IncompleteValue>::operator () (IncompleteValue * ptr) const {
        delete ptr;
    }

    template <>
    IncompleteValue * component_allocator<IncompleteValue>::operator () (IncompleteValue const & other) const {
        return new IncompleteValue{other};
    }

    template <>
    IncompleteValue * component_allocator<IncompleteValue>::operator () (IncompleteValue && other) const {
        return new IncompleteValue{std::move(other)};
    }

}

// TODO
#if 0
namespace cynth {

    //// Implementation helpers ////

    namespace {

        sem::conversion_result make_const (auto const & result) {
            if (!result)
                return result.error();
            return {sem::value::Const {
                .value = *result
            }};
        }

    }

    //// Categories ////

    //// Bool ////

    display_result sem::value::Bool::display () const {
        return "Bool(" + std::string{value ? "true" : "false"} + ")";
    }

    sem::get_result<bool> sem::value::Bool::get () const {
        return value;
    }

    sem::conversion_result sem::value::Bool::convert (context &, sem::type::Bool const &) const {
        return {*this};
    }

    sem::conversion_result sem::value::Bool::convert (context &, sem::type::Int const &) const {
        return sem::value::make_int(util::btoi(value));
    }

    sem::conversion_result sem::value::Bool::convert (context &, sem::type::Float const &) const {
        return sem::value::make_float(util::btof(value));
    }

    sem::conversion_result sem::value::Bool::convert (context & ctx, sem::type::Const const & to) const {
        return make_const(sem::convert_to(ctx)(*this)(to.type));
    }

    sem::value_type_result sem::value::Bool::value_type () const {
        return sem::type::Bool{};
    }

    //// Int ////

    display_result sem::value::Int::display () const {
        return "Int(" + std::to_string(value) + ")";
    }

    sem::get_result<integral> sem::value::Int::get () const {
        return value;
    }

    sem::conversion_result sem::value::Int::convert (context &, sem::type::Bool const &) const {
        return sem::value::make_bool(util::itob(value));
    }

    sem::conversion_result sem::value::Int::convert (context &, sem::type::Int const &) const {
        return {*this};
    }

    sem::conversion_result sem::value::Int::convert (context &, sem::type::Float const &) const {
        return sem::value::make_float(util::itof(value));
    }

    sem::conversion_result sem::value::Int::convert (context & ctx, sem::type::Const const & to) const {
        return make_const(sem::convert_to(ctx)(*this)(to.type));
    }

    sem::value_type_result sem::value::Int::value_type () const {
        return sem::type::Int{};
    }

    //// Float ////

    display_result sem::value::Float::display () const {
        return "Float(" + std::to_string(value) + ")";
    }

    sem::get_result<floating> sem::value::Float::get () const {
        return value;
    }

    sem::conversion_result sem::value::Float::convert (context &, sem::type::Bool const &) const {
        return sem::value::make_bool(util::ftob(value));
    }

    sem::conversion_result sem::value::Float::convert (context &, sem::type::Int const &) const {
        return sem::value::make_int(util::ftoi(value));
    }

    sem::conversion_result sem::value::Float::convert (context &, sem::type::Float const &) const {
        return {*this};
    }

    sem::conversion_result sem::value::Float::convert (context & ctx, sem::type::Const const & to) const {
        return make_const(sem::convert_to(ctx)(*this)(to.type));
    }

    sem::value_type_result sem::value::Float::value_type () const {
        return sem::type::Float{};
    }

    //// String ////

    display_result sem::value::String::display () const {
        return "String(" + value + ")";
    }

    sem::get_result<string> sem::value::String::get () const {
        return result_error{"Strings are not supported yet."};
    }

    sem::value_type_result sem::value::String::value_type () const {
        return sem::type::String{};
    }

    //// In ////

    display_result sem::value::In::display () const {
        return "in(" + cynth::display(value->value) + ")";
    }

    sem::conversion_result sem::value::In::convert (context & ctx, sem::type::Bool const & to) const {
        return sem::convert(ctx)(to)(value->value);
    }

    sem::conversion_result sem::value::In::convert (context & ctx, sem::type::Int const & to) const {
        return sem::convert(ctx)(to)(value->value);
    }

    sem::conversion_result sem::value::In::convert (context & ctx, sem::type::Float const & to) const {
        return sem::convert(ctx)(to)(value->value);
    }

    sem::conversion_result sem::value::In::convert (context &, sem::type::In const & to) const {
        if (!sem::same(*type, *to.type))
            return result_error{"Incompatible input value types."};
        return {*this};
    }

    sem::conversion_result sem::value::In::convert (context & ctx, sem::type::Const const & to) const {
        return make_const(sem::convert(ctx)(value->value, to.type));
    }

    sem::conversion_result sem::value::In::convert (context & ctx, sem::type::Buffer const & to) const {
        return sem::convert(ctx)(to)(value->value);
    }

    sem::value_type_result sem::value::In::value_type () const {
        return sem::type::In {
            .type = type
        };
    }

    //// Out ////

    display_result sem::value::Out::display () const {
        return "out(" + cynth::display(value->value) + ")";
    }

    sem::conversion_result sem::value::Out::convert (context &, sem::type::Out const & to) const {
        if (!sem::same(*type, *to.type))
            return result_error{"Incompatible output value types."};
        return {*this};
    }

    sem::value_type_result sem::value::Out::value_type () const {
        return sem::type::Out {
            .type = type
        };
    }

    //// Const ////

    display_result sem::value::Const::display () const {
        return "const(" + cynth::display(value) + ")";
    }

    sem::conversion_result sem::value::Const::convert (context & ctx, sem::type::Bool const & to) const {
        return sem::convert(ctx)(to)(value);
    }

    sem::conversion_result sem::value::Const::convert (context & ctx, sem::type::Int const & to) const {
        return sem::convert(ctx)(to)(value);
    }

    sem::conversion_result sem::value::Const::convert (context & ctx, sem::type::Float const & to) const {
        return sem::convert(ctx)(to)(value);
    }

    sem::conversion_result sem::value::Const::convert (context & ctx, sem::type::Const const & to) const {
        return make_const(sem::convert(ctx)(value, to.type));
    }

    sem::conversion_result sem::value::Const::convert (context & ctx, sem::type::Array const & to) const {
        return sem::convert(ctx)(to)(value);
    }

    sem::value_type_result sem::value::Const::value_type () const {
        return sem::type::Const {
            .type = sem::value_type(value)
        };
    }

    //// Array ////

    // TODO: const & type overload
    result<sem::value::complete> sem::value::make_array (
        sem::value::ArrayValue * value,
        component_vector<type::complete> && type,
        integral size
    ) {
        if (size <= 0)
            return result_error{"Array must have a positive size."};
        auto elem_type_check = util::unite_results(sem::array_elem_type_check(type));
        if (!elem_type_check)
            return elem_type_check.error();
        return sem::value::complete{sem::value::Array {
            .value = value,
            .type  = std::move(type),
            .size  = size
        }};
    }

    view<sem::value::ArrayValue::vector::iterator> sem::value::Array::trimmed_value () const {
        return view{value->value.begin(), static_cast<std::size_t>(size)};
    }

    sem::get_result<std::vector<tuple_vector<sem::value::complete>>> sem::value::Array::get () const {
        std::vector<tuple_vector<sem::value::complete>> result;
        result.reserve(size);
        for (auto & elem : trimmed_value()) {
            result.push_back(elem);
        }
        return result;
    }

    display_result sem::value::Array::display () const {
        return
            "array<" +
            display_tuple(type) +
            ">" +
            util::parenthesized(util::join(", ", lift::view{display_tuple}(trimmed_value())));
    }

    sem::conversion_result sem::value::Array::convert (context &, sem::type::Array const & to) const {
        if (size < to.size)
            return result_error{"Cannot convert an array to one with larger size."};
        auto compatible_result = lift::category_component{util::overload {
            [] <typename T, typename U> (T const & a, U const & b) -> bool {
            //requires (std::same_as<T, U> || !std::same_as<T, sem::type::Const> && std::same_as<U, sem::type::Const>)
                return sem::same(a, b);
            },
            [] <typename T> (sem::type::Const const &, T const &) -> bool
            requires (!std::same_as<T, sem::type::Const>) {
                return false;
            },
            [] <typename T> (T const & a, sem::type::Const const & b) -> bool
            requires (!std::same_as<T, sem::type::Const>) {
                return (sem::same(a, b) || sem::same(sem::type::Const{{a}}, b));
            }
        }} (type, to.type);
        if (!compatible_result)
            return compatible_result.error();
        if (!util::all(*compatible_result))
            return result_error{"Incompatible array value types."};
        auto type_copy = to.type;
        auto result = sem::value::make_array (
            value,
            std::move(type_copy),
            std::min(size, to.size)
        );
        if (!result)
            return result.error();
        return {*result};
    }

    sem::conversion_result sem::value::Array::convert (context & ctx, sem::type::Const const & to) const {
        return make_const(sem::convert_to(ctx)(*this)(to.type));
    }

    sem::value_type_result sem::value::Array::value_type () const {
        // TODO: Check the element type here? (i.e. use the value::make_array constructor?)
        return sem::type::Array {
            .type = type,
            .size = size
        };
    }

    //// Buffer ////

    // TODO: const & type overload
    result<sem::value::complete> sem::value::make_buffer (
        sem::value::BufferValue * value,
        integral size
    ) {
        if (size <= 0)
            return result_error{"Buffer must have a positive size."};
        return sem::value::complete{sem::value::Buffer {
            .value = value,
            .size  = size
        }};
    }

    display_result sem::value::Buffer::display () const {
        return "buffer(...)";
    }

    sem::conversion_result sem::value::Buffer::convert (context &, sem::type::Buffer const & to) const {
        if (size < to.size)
            return result_error{"Cannot convert a buffer to one with larger size."};
        auto result = sem::value::make_buffer (
            value,
            std::min(size, to.size)
        );
        if (!result)
            return result.error();
        return {*result};
    }

    sem::value_type_result sem::value::Buffer::value_type () const {
        return sem::type::Buffer {
            .size = static_cast<integral>(size) // TODO: Some safety checks or enforce an invariant?
        };
    }

    //// Function ////

    sem::get_result<sem::value::Function> sem::value::Function::get () const {
        return *this;
    }

    display_result sem::value::Function::display () const {
        return "function(...)";
    }

    sem::conversion_result sem::value::Function::convert (context &, sem::type::Function const & to) const {
        if (sem::same(to)(value_type()))
            return {*this};
        return result_error{"Invalid function conversion."};
    }

    sem::conversion_result sem::value::Function::convert (context & ctx, sem::type::Buffer const & to) const {
        auto stored = ctx.store_value(sem::value::BufferValue {
            .value     = sem::value::Buffer::vector(to.size, 0),
            .generator = value
        });
        if (!stored)
            return stored.error();
        auto result = sem::value::make_buffer (
            stored.get(),
            to.size
        );
        if (!result)
            return result.error();
        return {*result};
    }

    sem::value_type_result sem::value::Function::value_type () const {
        return sem::type::Function {
            .out = value->out_type,
            .in  = sem::decl_type(value->parameters)
        };
    }

}
#endif
