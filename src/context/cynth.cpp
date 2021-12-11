#include "context/cynth.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::context::Cynth;

    template <>
    void component_deleter<Cynth>::operator () (Cynth * ptr) const {
        delete ptr;
    }

    template <>
    Cynth * component_allocator<Cynth>::operator () (
        Cynth const & other
    ) const {
        return new Cynth{other};
    }

    template <>
    Cynth * component_allocator<Cynth>::operator () (Cynth && other) const {
        return new Cynth{std::move(other)};
    }

}

// TODO
#if 0
namespace cynth::context {

    Cynth::Cynth (): parent{nullptr} {}

    esl::result<void> Cynth::define_value (std::string name, sem::TypedValue const & v) {
        /*
        if (find_value_inside(name))
            return esl::result_error{"Cannot redefine a value in the same scope."};
        values.insert({name, v});
        */
        return {};
    }

    esl::result<void> Cynth::define_value (
        tuple_vector<sem::CompleteDeclaration>   const & decls,
        tuple_vector<sem::CompleteValue> const & values
    ) {
        /*
        auto value_begin = values.begin();

        for (auto & decl : decls) {
            if (static_cast<std::size_t>(values.end() - value_begin) < decl.type.size())
                return esl::result_error{"Less values than types in a definition."};

            tuple_vector<sem::CompleteValue> value;
            // TODO: Why none of these options work?
            //value.assign(value_begin, value_begin + decl.type.size());
            //value.reserve(decl.type.size());
            //std::copy(value_begin, value_begin + decl.type.size(), std::back_inserter(value));
            for (auto it = value_begin; it != value_begin + decl.type.size(); ++it) {
                value.push_back(*it);
            }

            value_begin += decl.type.size();

            // Convert to the correct type:
            auto conversion_results = interface::convert(*this)(value, decl.type);
            if (!conversion_results)
                return conversion_results.error();
            auto conversion_result = esl::unite_results(*conversion_results);
            if (!conversion_result)
                return conversion_result.error();
            auto converted = *std::move(conversion_result);

            auto define_result = define_value(decl.name, converted);
            if (!define_result)
                return define_result.error();
        }

        if (value_begin != values.end())
            return esl::result_error{"More values than types in a definition."};
        */

        return {};
    }

    namespace detail {

        template <typename T>
        esl::result<sem::CompleteValue> default_value (Cynth &, T const &);

        template <> esl::result<sem::CompleteValue> default_value<sem::type::Bool>   (Cynth & ctx, sem::type::Bool   const &);
        template <> esl::result<sem::CompleteValue> default_value<sem::type::Int>    (Cynth & ctx, sem::type::Int    const &);
        template <> esl::result<sem::CompleteValue> default_value<sem::type::Float>  (Cynth & ctx, sem::type::Float  const &);
        template <> esl::result<sem::CompleteValue> default_value<sem::type::Const>  (Cynth & ctx, sem::type::Const  const &);
        template <> esl::result<sem::CompleteValue> default_value<sem::type::In>     (Cynth & ctx, sem::type::In     const &);
        template <> esl::result<sem::CompleteValue> default_value<sem::type::Out>    (Cynth & ctx, sem::type::Out    const &);
        template <> esl::result<sem::CompleteValue> default_value<sem::type::Array>  (Cynth & ctx, sem::type::Array  const &);
        template <> esl::result<sem::CompleteValue> default_value<sem::type::Buffer> (Cynth & ctx, sem::type::Buffer const &);

        template <> esl::result<sem::CompleteValue> default_value<sem::type::String>   (Cynth & ctx, sem::type::String   const &);
        template <> esl::result<sem::CompleteValue> default_value<sem::type::Function> (Cynth & ctx, sem::type::Function const &);

    }

    constexpr auto default_value = [] (Cynth & ctx) {
        return [&ctx] (auto const & type) {
            return detail::default_value(ctx, type);
        };
    };

    template <>
    esl::result<sem::CompleteValue> detail::default_value<sem::type::Bool> (Cynth &, sem::type::Bool const &) {
        return sem::value::Bool::make(false);
    }

    template <>
    esl::result<sem::CompleteValue> detail::default_value<sem::type::Int> (Cynth &, sem::type::Int const &) {
        return sem::value::Int::make(0);
    }

    template <>
    esl::result<sem::CompleteValue> detail::default_value<sem::type::Float> (Cynth &, sem::type::Float const &) {
        return sem::value::Float::make(0);
    }

    template <>
    esl::result<sem::CompleteValue> detail::default_value<sem::type::Const> (Cynth & ctx, sem::type::Const const & constant) {
        //return esl::result_error{"No default value for a const type."};
        auto value = lift::category_component{cynth::default_value(ctx)}(constant.type);
        if (!value)
            return value.error();
        return sem::CompleteValue{sem::value::Const{*value}};
    }

    template <>
    esl::result<sem::CompleteValue> detail::default_value<sem::type::In> (Cynth & ctx, sem::type::In const & input) {
        auto value = lift::category_component{cynth::default_value(ctx)}(input.type);
        if (!value)
            return value.error();
        auto stored = ctx.store_value(sem::value::InValue {
            .value = *value
        });
        return sem::CompleteValue{sem::value::In {
            .value = stored.get(),
            .type  = input.type
        }};
    }

    template <>
    esl::result<sem::CompleteValue> detail::default_value<sem::type::Out> (Cynth & ctx, sem::type::Out const & output) {
        auto value = lift::category_component{cynth::default_value(ctx)}(output.type);
        if (!value)
            return value.error();
        auto stored = ctx.store_value(sem::value::OutValue {
            .value = *value
        });
        return sem::CompleteValue{sem::value::Out {
            .value = stored.get(),
            .type  = output.type
        }};
    }

    template <>
    esl::result<sem::CompleteValue> detail::default_value<sem::type::Array> (Cynth & ctx, sem::type::Array const & array) {
        auto value = esl::unite_results(lift::category_component{cynth::default_value(ctx)}(array.type));
        if (!value)
            return value.error();
        tuple_vector<tuple_vector<sem::CompleteValue>> values(array.size, *value);
        auto stored = ctx.store_value(sem::value::ArrayValue {
            .value = values
        });
        auto type_copy = array.type;
        return sem::value::Array::make(stored.get(), std::move(type_copy), array.size);
    }

    template <>
    esl::result<sem::CompleteValue> detail::default_value<sem::type::Buffer> (Cynth & ctx, sem::type::Buffer const & buffer) {
        sem::value::Buffer::vector values(buffer.size, 0);
        auto stored = ctx.store_value(sem::value::BufferValue {
            .value = values
        });
        return sem::value::Buffer::make(stored.get(), buffer.size);
    }

    template <>
    esl::result<sem::CompleteValue> detail::default_value<sem::type::String> (Cynth &, sem::type::String const &) {
        return esl::result_error{"Default string values are not supported yet."};
    }

    template <>
    esl::result<sem::CompleteValue> detail::default_value<sem::type::Function> (Cynth &, sem::type::Function const &) {
        return esl::result_error{"No default value for a function."};
    }

    esl::result<void> Cynth::declare (tuple_vector<sem::CompleteDeclaration> const & decls) {
        /*
        for (auto & decl : decls) {
            auto const_check = esl::unite_results(lift::category_component{esl::overload {
                [] (sem::type::Const const &) -> esl::result<void> {
                    return esl::result_error{"Cannot declare a const value with no definition."};
                },
                // Note: Buffers and functions are implicitly const.
                // Input values are also implicitly const, but input values specifically can never be defined, only declared.
                [] (sem::type::Buffer const &) -> esl::result<void> {
                    return esl::result_error{"Cannot declare a buffer with no generator definition."};
                },
                [] (sem::type::Function const &) -> esl::result<void> {
                    return esl::result_error{"Cannot declare a function with no definition."};
                },
                [] <typename Type> (Type &&) -> esl::result<void>
                requires
                    (!esl::same_but_cvref<Type, sem::type::Const>) &&
                    (!esl::same_but_cvref<Type, sem::type::Buffer>) &&
                    (!esl::same_but_cvref<Type, sem::type::Function>)
                {
                    return {};
                }
            }} (decl.type));
            if (!const_check)
                return const_check.error();

            auto init_result = esl::unite_results(lift::category_component{default_value(*this)}(decl.type));
            if (!init_result)
                return init_result.error();

            auto define_result = define_value(decl.name, sem::TypedValue{.type = decl.type, .value = *std::move(init_result)});
            if (!define_result)
                return define_result.error();
        }
        */

        return {};
    }

    esl::result<void> Cynth::define_type (std::string name, esl::tiny_vector<sem::CompleteType> const & t) {
        if (find_type_inside(name))
            return esl::result_error{"Cannot redefine a type in the same scope."};
        types.insert({name, t});
        return {};
    }

    /*
    sem::TypedValue * Cynth::find_value_inside (std::string const & name) {
        auto iter = values.find(name);
        return iter != values.end()
            ? &iter->second
            : nullptr;
    }

    esl::tiny_vector<sem::CompleteType> * Cynth::find_type_inside (std::string const & name) {
        auto iter = types.find(name);
        return iter != types.end()
            ? &iter->second
            : nullptr;
    }

    sem::TypedValue * Cynth::find_value (std::string const & name) {
        auto inside = find_value_inside(name);
        if (!parent || inside)
            return inside;
        return parent->find_value(name);
    }
    */

    esl::tiny_vector<sem::CompleteType> * Cynth::find_type (std::string const & name) {
        auto inside = find_type_inside(name);
        if (!parent || inside)
            return inside;
        return parent->find_type(name);
    }

    Cynth make_child_context (Cynth & parent) {
        Cynth ctx;
        ctx.parent = &parent;
        return ctx;
    }

    template <typename Value>
    void Cynth::init_storage () {
        auto & stored = std::get<std::optional<sem::refval_container<Value>>>(referential);
        stored = RefvalContainer<Value>{};
    }

    template void Cynth::init_storage<sem::value::InValue>       ();
    template void Cynth::init_storage<sem::value::OutValue>      ();
    template void Cynth::init_storage<sem::value::ArrayValue>    ();
    template void Cynth::init_storage<sem::value::BufferValue>   ();
    template void Cynth::init_storage<sem::value::FunctionValue> ();

    template <typename Value>
    Cynth::RefvalContainer<Value> & Cynth::stored_values () {
        auto & stored = std::get<std::optional<refval_container<Value>>>(referential);
        if (stored)
            return *stored;
        if (!parent) {
            stored = refval_container<Value>{};
            return *stored;
        }
        return parent->stored_values<Value>();
    }

    template Cynth::RefvalContainer<sem::value::InValue>       & Cynth::stored_values ();
    template Cynth::RefvalContainer<sem::value::OutValue>      & Cynth::stored_values ();
    template Cynth::RefvalContainer<sem::value::ArrayValue>    & Cynth::stored_values ();
    template Cynth::RefvalContainer<sem::value::BufferValue>   & Cynth::stored_values ();
    template Cynth::RefvalContainer<sem::value::FunctionValue> & Cynth::stored_values ();

    template <typename Value>
    esl::reference_result<Value> Cynth::store_value (Value const & v) {
        auto & stored = stored_values<Value>();
        stored.push_front(v);
        return stored.front();
    }

    template esl::reference_result<sem::value::InValue>       Cynth::store_value (sem::value::InValue       const &);
    template esl::reference_result<sem::value::OutValue>      Cynth::store_value (sem::value::OutValue      const &);
    template esl::reference_result<sem::value::ArrayValue>    Cynth::store_value (sem::value::ArrayValue    const &);
    template esl::reference_result<sem::value::BufferValue>   Cynth::store_value (sem::value::BufferValue   const &);
    template esl::reference_result<sem::value::FunctionValue> Cynth::store_value (sem::value::FunctionValue const &);

}
#endif
