#include "asg/util.hpp"

#include "config.hpp"
#include "lift.hpp"
#include "context.hpp"
#include "asg/declarations.hpp"
#include "asg/values.hpp"
#include "asg/targets.hpp"
#include "asg/interface.hpp"
#include "ast/categories/expression.hpp"
#include "ast/categories/array_elem.hpp"
#include "ast/nodes/expressions.hpp"
#include "util/general.hpp"
#include "util/container.hpp"

namespace cynth {

    result<void> asg::define (
        context & ctx,
        tuple_vector<asg::complete_decl>   const & decls,
        tuple_vector<asg::value::complete> const & values
    ) {
        auto value_begin = values.begin();

        for (auto & decl : decls) {
            if (static_cast<std::size_t>(values.end() - value_begin) < decl.type.size())
                return result_error{"Less values than types in a definition."};

            tuple_vector<asg::value::complete> value;
            // TODO: Why none of these options work?
            //value.assign(value_begin, value_begin + decl.type.size());
            //value.reserve(decl.type.size());
            //std::copy(value_begin, value_begin + decl.type.size(), std::back_inserter(value));
            for (auto it = value_begin; it != value_begin + decl.type.size(); ++it) {
                value.push_back(*it);
            }

            value_begin += decl.type.size();

            // Convert to the correct type:
            auto conversion_results = asg::convert(value, decl.type);
            if (!conversion_results)
                return conversion_results.error();
            auto conversion_result = util::unite_results(*conversion_results);
            if (!conversion_result)
                return conversion_result.error();
            auto converted = *std::move(conversion_result);

            auto define_result = ctx.define_value(decl.name, converted);
            if (!define_result)
                return define_result.error();
        }

        if (value_begin != values.end())
            return result_error{"More values than types in a definition."};

        return {};
    }

    namespace detail {

        template <typename T>
        result<asg::value::complete> default_value (context &, T const &);

        template <> result<asg::value::complete> default_value<asg::type::Bool>   (context & ctx, asg::type::Bool   const &);
        template <> result<asg::value::complete> default_value<asg::type::Int>    (context & ctx, asg::type::Int    const &);
        template <> result<asg::value::complete> default_value<asg::type::Float>  (context & ctx, asg::type::Float  const &);
        template <> result<asg::value::complete> default_value<asg::type::Const>  (context & ctx, asg::type::Const  const &);
        template <> result<asg::value::complete> default_value<asg::type::In>     (context & ctx, asg::type::In     const &);
        template <> result<asg::value::complete> default_value<asg::type::Out>    (context & ctx, asg::type::Out    const &);
        template <> result<asg::value::complete> default_value<asg::type::Array>  (context & ctx, asg::type::Array  const &);
        template <> result<asg::value::complete> default_value<asg::type::Buffer> (context & ctx, asg::type::Buffer const &);

        template <> result<asg::value::complete> default_value<asg::type::String>   (context & ctx, asg::type::String   const &);
        template <> result<asg::value::complete> default_value<asg::type::Function> (context & ctx, asg::type::Function const &);

    }

    constexpr auto default_value = [] (context & ctx) {
        return [&ctx] (auto const & type) {
            return detail::default_value(ctx, type);
        };
    };

    template <>
    result<asg::value::complete> detail::default_value<asg::type::Bool> (context &, asg::type::Bool const &) {
        return asg::value::make_bool(false);
    }

    template <>
    result<asg::value::complete> detail::default_value<asg::type::Int> (context &, asg::type::Int const &) {
        return asg::value::make_int(0);
    }

    template <>
    result<asg::value::complete> detail::default_value<asg::type::Float> (context &, asg::type::Float const &) {
        return asg::value::make_float(0);
    }

    template <>
    result<asg::value::complete> detail::default_value<asg::type::Const> (context & ctx, asg::type::Const const & constant) {
        //return result_error{"No default value for a const type."};
        auto value = lift::category_component{cynth::default_value(ctx)}(constant.type);
        if (!value)
            return value.error();
        return asg::value::complete{asg::value::Const{*value}};
    }

    template <>
    result<asg::value::complete> detail::default_value<asg::type::In> (context & ctx, asg::type::In const & input) {
        auto value = lift::category_component{cynth::default_value(ctx)}(input.type);
        if (!value)
            return value.error();
        auto stored = ctx.store_value(asg::value::InValue {
            .value = *value
        });
        return asg::value::complete{asg::value::In{stored.get()}};
    }

    template <>
    result<asg::value::complete> detail::default_value<asg::type::Out> (context & ctx, asg::type::Out const & input) {
        auto value = lift::category_component{cynth::default_value(ctx)}(input.type);
        if (!value)
            return value.error();
        auto stored = ctx.store_value(asg::value::OutValue {
            .value = *value
        });
        return asg::value::complete{asg::value::Out{stored.get()}};
    }

    template <>
    result<asg::value::complete> detail::default_value<asg::type::Array> (context & ctx, asg::type::Array const & array) {
        auto value = util::unite_results(lift::category_component{cynth::default_value(ctx)}(array.type));
        if (!value)
            return value.error();
        tuple_vector<tuple_vector<asg::value::complete>> values(array.size, *value);
        auto stored = ctx.store_value(asg::value::ArrayValue {
            .value = values
        });
        auto type_copy = array.type;
        return asg::value::make_array(stored.get(), std::move(type_copy), array.size);
    }

    template <>
    result<asg::value::complete> detail::default_value<asg::type::Buffer> (context & ctx, asg::type::Buffer const & buffer) {
        asg::value::Buffer::vector values(buffer.size, 0);
        auto stored = ctx.store_value(asg::value::BufferValue {
            .value = values
        });
        return asg::value::make_buffer(stored.get(), buffer.size);
    }

    template <>
    result<asg::value::complete> detail::default_value<asg::type::String> (context &, asg::type::String const &) {
        return result_error{"Default string values are not supported yet."};
    }

    template <>
    result<asg::value::complete> detail::default_value<asg::type::Function> (context &, asg::type::Function const &) {
        return result_error{"No default value for a function."};
    }

    result<void> asg::declare (
        context & ctx,
        tuple_vector<asg::complete_decl> const & decls
    ) {
        for (auto & decl : decls) {
            auto const_check = util::unite_results(lift::category_component{util::overload {
                [] (asg::type::Const const &) -> cynth::result<void> {
                    return result_error{"Cannot declare a const value with no definition."};
                },
                // Note: Buffers and functions are implicitly const.
                // Input values are also implicitly const, but input values specifically can never be defined, only declared.
                [] (asg::type::Buffer const &) -> cynth::result<void> {
                    return result_error{"Cannot declare a buffer with no generator definition."};
                },
                [] (asg::type::Function const &) -> cynth::result<void> {
                    return result_error{"Cannot declare a function with no definition."};
                },
                [] <typename Type> (Type &&) -> cynth::result<void>
                requires
                    (!util::same_as_no_cvref<Type, asg::type::Const>) &&
                    (!util::same_as_no_cvref<Type, asg::type::Buffer>) &&
                    (!util::same_as_no_cvref<Type, asg::type::Function>)
                {
                    return {};
                }
            }} (decl.type));
            if (!const_check)
                return const_check.error();

            auto init_result = util::unite_results(lift::category_component{default_value(ctx)}(decl.type));
            if (!init_result)
                return init_result.error();

            auto define_result = ctx.define_value(decl.name, typed_value{.value = *std::move(init_result), .type = decl.type});
            if (!define_result)
                return define_result.error();
        }

        return {};
    }

    result<std::pair<integral, asg::range_vector>> asg::for_decls (context & ctx, ast::category::RangeDecl declarations) {
        integral size = 0;
        range_vector iter_decls;

        auto decls_result = util::unite_results(asg::complete(ast::eval_range_decl(ctx)(declarations)));
        if (!decls_result)
            return {decls_result.error()};
        auto decls = *std::move(decls_result);

        iter_decls.reserve(decls.size());

        // TODO: Clean this up...
        for (auto & range_decl : decls) {
            auto range_result = lift::category_component{util::overload {
                [] (asg::value::Array && value) -> result<asg::value::Array> {
                    return std::move(value);
                },
                [] (asg::value::Const && value) -> result<asg::value::Array> {
                    return lift::category_component{util::overload {
                        [] (asg::value::Array && value) -> result<asg::value::Array> {
                            return std::move(value);
                        },
                        [] (auto &&) -> result<asg::value::Array> {
                            return result_error{"Range in a for loop must be an array."};
                        }
                    }} (std::move(value.value));
                    // TODO: Check if there are any consequencess of loosing constness here.
                },
                [] (auto &&) -> result<asg::value::Array> {
                    return result_error{"Range in a for loop must be an array."};
                }
            }} (std::move(range_decl.range));
            if (!range_result)
                return {range_result.error()};

            size = size == 0
                ? range_result->size
                : std::min(size, range_result->size);
            iter_decls.push_back(std::pair{
                std::move(range_decl.declaration),
                *std::move(range_result)
            });
        }

        return std::pair{size, iter_decls};
    }

    result<std::pair<asg::array_vector, asg::array_type>> asg::array_elems (
        context & ctx,
        component_vector<ast::category::ArrayElem> const & elements
    ) {
        std::optional<asg::array_type> result_type;
        asg::array_vector              result_values; // component_vector<component_vector<value::complete>>
        result_values.reserve(elements.size());       // Reserve at least the lowest size estimate.

        for (auto & element : elements) {
            auto result = lift::category{util::overload {
                [] (ast::node::RangeTo const &) -> cynth::result<void> {
                    // TODO
                    return result_error{"Range array elements are not supported yet."};
                },
                [] (ast::node::RangeToBy const &) -> cynth::result<void> {
                    // TODO
                    return result_error{"Range array elements are not supported yet."};
                },
                [] (ast::node::Spread const &) -> cynth::result<void> {
                    // TODO
                    return result_error{"Spread array elements are not supported yet."};
                },
                [&ctx, &result_type, &result_values] <ast::interface::expression T> (T const & e) -> cynth::result<void> {
                    auto result = util::unite_results(ast::evaluate(ctx)(e)); // evaluation_result aka tuple_vector<result<value::complete>> -> result<tuple_vector<value::complete>>
                    if (!result)
                        return result.error();
                    auto & value = *result;                // tuple_vector<value::complete> &
                    auto   type  = asg::value_type(value); // tuple_vector<type::complete>
                    if (type.size() == 0)
                        return result_error{"Cannot use the void value as an array element."};
                    // TODO: Overload asg::common to work with optional inputs.
                    if (result_type) {
                        auto common_results = asg::common(type, *result_type);
                        if (!common_results)
                            return common_results.error();
                        result_type = result_to_optional(util::unite_results(*common_results));
                    } else {
                        result_type = std::optional{std::move(type)};
                    }
                    // TODO
                    //result_type = std::optional{util::init<tuple_vector>(asg::type::complete{asg::type::Int{}})};
                    //auto wrapped = component_vector<asg::value::complete>{std::move(value)};
                    //result_values.push_back(std::move(wrapped));
                    result_values.push_back(std::move(value));
                    return {};
                }
            }}(element);
            if (!result)
                return {result.error()};
        }

        if (result_values.size() == 0)
            return {{
                {},
                {}
            }};

        if (!result_type)
            return {result_error{"No common type for an array."}};

        return {{
            std::move(result_values),
            std::move(*result_type)
        }};
    }

}
