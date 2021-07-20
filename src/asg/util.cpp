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
                return result_error{"Less values than types in a declaration."};

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
            return result_error{"More values than types in a declaration."};

        return {};
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
                [] <typename Type> (Type &&) -> cynth::result<void> requires (!util::same_as_no_cvref<Type, asg::type::Const>) {
                    return {};
                }
            }} (decl.type));
            if (!const_check)
                return const_check.error();

            auto define_result = ctx.define_value(decl.name, typed_value{.value = {}, .type = decl.type});
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
