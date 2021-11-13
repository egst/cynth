#include "sem/util.hpp"

#include "config.hpp"
#include "lift.hpp"
#include "sem/context.hpp"
#include "sem/declarations.hpp"
#include "sem/values.hpp"
#include "sem/targets.hpp"
#include "sem/interface.hpp"
#include "ast/categories/expression.hpp"
#include "ast/categories/array_elem.hpp"
#include "ast/nodes/expressions.hpp"
#include "util/general.hpp"
#include "util/container.hpp"

namespace cynth {

    result<std::pair<integral, sem::range_vector>> sem::for_decls (sem::context & ctx, ast::category::RangeDecl declarations) {
        integral size = 0;
        range_vector iter_decls;

        auto decls_result = util::unite_results(sem::complete(ctx)(ast::eval_range_decl(ctx)(declarations)));
        if (!decls_result)
            return {decls_result.error()};
        auto decls = *std::move(decls_result);

        iter_decls.reserve(decls.size());

        // TODO: Clean this up...
        for (auto & range_decl : decls) {
            auto range_result = lift::category_component{util::overload {
                [] (sem::value::Array && value) -> result<sem::value::Array> {
                    return std::move(value);
                },
                [] (sem::value::Const && value) -> result<sem::value::Array> {
                    return lift::category_component{util::overload {
                        [] (sem::value::Array && value) -> result<sem::value::Array> {
                            return std::move(value);
                        },
                        [] (auto &&) -> result<sem::value::Array> {
                            return result_error{"Range in a for loop must be an array."};
                        }
                    }} (std::move(value.value));
                    // TODO: Check if there are any consequencess of loosing constness here.
                },
                [] (auto &&) -> result<sem::value::Array> {
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

    result<std::pair<sem::array_vector, sem::array_type>> sem::array_elems (
        sem::context & ctx,
        component_vector<ast::category::ArrayElem> const & elements
    ) {
        std::optional<sem::array_type> result_type;
        sem::array_vector              result_values; // component_vector<component_vector<value::complete>>
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
                    auto   type  = sem::value_type(value); // tuple_vector<type::complete>
                    if (type.size() == 0)
                        return result_error{"Cannot use the void value as an array element."};
                    // TODO: Overload sem::common to work with optional inputs.
                    if (result_type) {
                        auto common_results = sem::common(type, *result_type);
                        if (!common_results)
                            return common_results.error();
                        result_type = result_to_optional(util::unite_results(*common_results));
                    } else {
                        result_type = std::optional{std::move(type)};
                    }
                    // TODO
                    //result_type = std::optional{util::init<tuple_vector>(sem::type::complete{sem::type::Int{}})};
                    //auto wrapped = component_vector<sem::value::complete>{std::move(value)};
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

    // Note: This doesn't consider cases where the type introduces a declaration, e.g. `Int [Int size] arr`.
    std::vector<std::string> sem::detail::decl_names (sem::complete_decl const & decl) {
        return util::init<std::vector>(decl.name);
    }

    sem::context sem::function_capture (
        component_vector <sem::complete_decl>        const & parameters,
        component        <ast::category::Expression> const & body
    ) {
        auto r = sem::declaration_names(parameters);
        return {};
    }

}
