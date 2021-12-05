#include "sem/context.hpp"

#include "esl/component.hpp"

namespace esl {

    using cynth::sem::Context;

    template <>
    void component_deleter<Context>::operator () (Context * ptr) const {
        delete ptr;
    }

    template <>
    Context * component_allocator<Context>::operator () (
        Context const & other
    ) const {
        return new Context{other};
    }

    template <>
    Context * component_allocator<Context>::operator () (Context && other) const {
        return new Context{std::move(other)};
    }

}

// TODO
#if 0
namespace cynth {

    sem::context::context (): parent{nullptr} {}

    result<void> sem::context::define_value (std::string name, typed_value const & v) {
        /*
        if (find_value_inside(name))
            return result_error{"Cannot redefine a value in the same scope."};
        values.insert({name, v});
        */
        return {};
    }

    result<void> sem::context::define_value (
        tuple_vector<sem::complete_decl>   const & decls,
        tuple_vector<sem::value::complete> const & values
    ) {
        /*
        auto value_begin = values.begin();

        for (auto & decl : decls) {
            if (static_cast<std::size_t>(values.end() - value_begin) < decl.type.size())
                return result_error{"Less values than types in a definition."};

            tuple_vector<sem::value::complete> value;
            // TODO: Why none of these options work?
            //value.assign(value_begin, value_begin + decl.type.size());
            //value.reserve(decl.type.size());
            //std::copy(value_begin, value_begin + decl.type.size(), std::back_inserter(value));
            for (auto it = value_begin; it != value_begin + decl.type.size(); ++it) {
                value.push_back(*it);
            }

            value_begin += decl.type.size();

            // Convert to the correct type:
            auto conversion_results = sem::convert(*this)(value, decl.type);
            if (!conversion_results)
                return conversion_results.error();
            auto conversion_result = util::unite_results(*conversion_results);
            if (!conversion_result)
                return conversion_result.error();
            auto converted = *std::move(conversion_result);

            auto define_result = define_value(decl.name, converted);
            if (!define_result)
                return define_result.error();
        }

        if (value_begin != values.end())
            return result_error{"More values than types in a definition."};
        */

        return {};
    }

    namespace detail {

        template <typename T>
        result<sem::value::complete> default_value (sem::context &, T const &);

        template <> result<sem::value::complete> default_value<sem::type::Bool>   (sem::context & ctx, sem::type::Bool   const &);
        template <> result<sem::value::complete> default_value<sem::type::Int>    (sem::context & ctx, sem::type::Int    const &);
        template <> result<sem::value::complete> default_value<sem::type::Float>  (sem::context & ctx, sem::type::Float  const &);
        template <> result<sem::value::complete> default_value<sem::type::Const>  (sem::context & ctx, sem::type::Const  const &);
        template <> result<sem::value::complete> default_value<sem::type::In>     (sem::context & ctx, sem::type::In     const &);
        template <> result<sem::value::complete> default_value<sem::type::Out>    (sem::context & ctx, sem::type::Out    const &);
        template <> result<sem::value::complete> default_value<sem::type::Array>  (sem::context & ctx, sem::type::Array  const &);
        template <> result<sem::value::complete> default_value<sem::type::Buffer> (sem::context & ctx, sem::type::Buffer const &);

        template <> result<sem::value::complete> default_value<sem::type::String>   (sem::context & ctx, sem::type::String   const &);
        template <> result<sem::value::complete> default_value<sem::type::Function> (sem::context & ctx, sem::type::Function const &);

    }

    constexpr auto default_value = [] (sem::context & ctx) {
        return [&ctx] (auto const & type) {
            return detail::default_value(ctx, type);
        };
    };

    template <>
    result<sem::value::complete> detail::default_value<sem::type::Bool> (sem::context &, sem::type::Bool const &) {
        return sem::value::make_bool(false);
    }

    template <>
    result<sem::value::complete> detail::default_value<sem::type::Int> (sem::context &, sem::type::Int const &) {
        return sem::value::make_int(0);
    }

    template <>
    result<sem::value::complete> detail::default_value<sem::type::Float> (sem::context &, sem::type::Float const &) {
        return sem::value::make_float(0);
    }

    template <>
    result<sem::value::complete> detail::default_value<sem::type::Const> (sem::context & ctx, sem::type::Const const & constant) {
        //return result_error{"No default value for a const type."};
        auto value = lift::category_component{cynth::default_value(ctx)}(constant.type);
        if (!value)
            return value.error();
        return sem::value::complete{sem::value::Const{*value}};
    }

    template <>
    result<sem::value::complete> detail::default_value<sem::type::In> (sem::context & ctx, sem::type::In const & input) {
        auto value = lift::category_component{cynth::default_value(ctx)}(input.type);
        if (!value)
            return value.error();
        auto stored = ctx.store_value(sem::value::InValue {
            .value = *value
        });
        return sem::value::complete{sem::value::In {
            .value = stored.get(),
            .type  = input.type
        }};
    }

    template <>
    result<sem::value::complete> detail::default_value<sem::type::Out> (sem::context & ctx, sem::type::Out const & output) {
        auto value = lift::category_component{cynth::default_value(ctx)}(output.type);
        if (!value)
            return value.error();
        auto stored = ctx.store_value(sem::value::OutValue {
            .value = *value
        });
        return sem::value::complete{sem::value::Out {
            .value = stored.get(),
            .type  = output.type
        }};
    }

    template <>
    result<sem::value::complete> detail::default_value<sem::type::Array> (sem::context & ctx, sem::type::Array const & array) {
        auto value = util::unite_results(lift::category_component{cynth::default_value(ctx)}(array.type));
        if (!value)
            return value.error();
        tuple_vector<tuple_vector<sem::value::complete>> values(array.size, *value);
        auto stored = ctx.store_value(sem::value::ArrayValue {
            .value = values
        });
        auto type_copy = array.type;
        return sem::value::make_array(stored.get(), std::move(type_copy), array.size);
    }

    template <>
    result<sem::value::complete> detail::default_value<sem::type::Buffer> (sem::context & ctx, sem::type::Buffer const & buffer) {
        sem::value::Buffer::vector values(buffer.size, 0);
        auto stored = ctx.store_value(sem::value::BufferValue {
            .value = values
        });
        return sem::value::make_buffer(stored.get(), buffer.size);
    }

    template <>
    result<sem::value::complete> detail::default_value<sem::type::String> (sem::context &, sem::type::String const &) {
        return result_error{"Default string values are not supported yet."};
    }

    template <>
    result<sem::value::complete> detail::default_value<sem::type::Function> (sem::context &, sem::type::Function const &) {
        return result_error{"No default value for a function."};
    }

    result<void> sem::context::declare (tuple_vector<sem::complete_decl> const & decls) {
        /*
        for (auto & decl : decls) {
            auto const_check = util::unite_results(lift::category_component{util::overload {
                [] (sem::type::Const const &) -> cynth::result<void> {
                    return result_error{"Cannot declare a const value with no definition."};
                },
                // Note: Buffers and functions are implicitly const.
                // Input values are also implicitly const, but input values specifically can never be defined, only declared.
                [] (sem::type::Buffer const &) -> cynth::result<void> {
                    return result_error{"Cannot declare a buffer with no generator definition."};
                },
                [] (sem::type::Function const &) -> cynth::result<void> {
                    return result_error{"Cannot declare a function with no definition."};
                },
                [] <typename Type> (Type &&) -> cynth::result<void>
                requires
                    (!util::same_as_no_cvref<Type, sem::type::Const>) &&
                    (!util::same_as_no_cvref<Type, sem::type::Buffer>) &&
                    (!util::same_as_no_cvref<Type, sem::type::Function>)
                {
                    return {};
                }
            }} (decl.type));
            if (!const_check)
                return const_check.error();

            auto init_result = util::unite_results(lift::category_component{default_value(*this)}(decl.type));
            if (!init_result)
                return init_result.error();

            auto define_result = define_value(decl.name, typed_value{.type = decl.type, .value = *std::move(init_result)});
            if (!define_result)
                return define_result.error();
        }
        */

        return {};
    }

    result<void> sem::context::define_type (std::string name, type_vector const & t) {
        if (find_type_inside(name))
            return result_error{"Cannot redefine a type in the same scope."};
        types.insert({name, t});
        return {};
    }

#if 0
    sem::typed_value * sem::context::find_value_inside (std::string const & name) {
        auto iter = values.find(name);
        return iter != values.end()
            ? &iter->second
            : nullptr;
    }

    sem::type_vector * sem::context::find_type_inside (std::string const & name) {
        auto iter = types.find(name);
        return iter != types.end()
            ? &iter->second
            : nullptr;
    }

    sem::typed_value * sem::context::find_value (std::string const & name) {
        auto inside = find_value_inside(name);
        if (!parent || inside)
            return inside;
        return parent->find_value(name);
    }
#endif

    sem::type_vector * sem::context::find_type (std::string const & name) {
        auto inside = find_type_inside(name);
        if (!parent || inside)
            return inside;
        return parent->find_type(name);
    }

    sem::context make_child_context (sem::context & parent) {
        sem::context ctx;
        ctx.parent = &parent;
        return ctx;
    }

    template <typename Value>
    void sem::context::init_storage () {
        auto & stored = std::get<std::optional<sem::refval_container<Value>>>(referential);
        stored = sem::refval_container<Value>{};
    }

    template void sem::context::init_storage<sem::value::InValue>       ();
    template void sem::context::init_storage<sem::value::OutValue>      ();
    template void sem::context::init_storage<sem::value::ArrayValue>    ();
    template void sem::context::init_storage<sem::value::BufferValue>   ();
    template void sem::context::init_storage<sem::value::FunctionValue> ();

    template <typename Value>
    sem::refval_container<Value> & sem::context::stored_values () {
        auto & stored = std::get<std::optional<refval_container<Value>>>(referential);
        if (stored)
            return *stored;
        if (!parent) {
            stored = refval_container<Value>{};
            return *stored;
        }
        return parent->stored_values<Value>();
    }

    template sem::refval_container<sem::value::InValue>       & sem::context::stored_values ();
    template sem::refval_container<sem::value::OutValue>      & sem::context::stored_values ();
    template sem::refval_container<sem::value::ArrayValue>    & sem::context::stored_values ();
    template sem::refval_container<sem::value::BufferValue>   & sem::context::stored_values ();
    template sem::refval_container<sem::value::FunctionValue> & sem::context::stored_values ();

    template <typename Value>
    reference_result<Value> sem::context::store_value (Value const & v) {
        auto & stored = stored_values<Value>();
        stored.push_front(v);
        return stored.front();
    }

    template reference_result<sem::value::InValue>       sem::context::store_value (sem::value::InValue       const &);
    template reference_result<sem::value::OutValue>      sem::context::store_value (sem::value::OutValue      const &);
    template reference_result<sem::value::ArrayValue>    sem::context::store_value (sem::value::ArrayValue    const &);
    template reference_result<sem::value::BufferValue>   sem::context::store_value (sem::value::BufferValue   const &);
    template reference_result<sem::value::FunctionValue> sem::context::store_value (sem::value::FunctionValue const &);

}
#endif
