#include "asg/util.hpp"

#include "config.hpp"
#include "lift.hpp"
#include "context.hpp"
#include "asg/declarations.hpp"
#include "asg/values.hpp"
#include "asg/interface.hpp"
#include "ast/categories/expression.hpp"
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
                return error{"Less values than types in a declaration."};

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
            return error{"More values than types in a declaration."};

        return {};
    }

    result<void> asg::declare (
        context & ctx,
        tuple_vector<asg::complete_decl> const & decls
    ) {
        for (auto & decl : decls) {
            auto const_check = util::unite_results(lift::category_component{util::overload {
                [] (asg::type::Const const &) -> cynth::result<void> {
                    return error{"Cannot declare a const value with no definition."};
                },
                [] <typename Type> (Type &&) -> cynth::result<void> requires (!util::same_as_no_cvref<Type, asg::type::Const>) {
                    return {};
                }
            }} (decl.type));
            if (!const_check)
                return const_check.error();

            auto define_result = ctx.define_value(decl.name, {.value = {}, .type = decl.type});
            if (!define_result)
                return define_result.error();
        }

        return {};
    }

    //template <>
    result<tuple_vector<std::string>> asg::detail::eval_name_node (ast::node::Name const & node) {
        return util::init<tuple_vector>(*node.name);
    }

    //template <>
    result<tuple_vector<std::string>> asg::detail::eval_name_node (ast::node::Tuple const & node) {
        tuple_vector<std::string> result;
        auto names = lift::category_component{asg::eval_name}(node.values);
        for (auto & name_result : names) {
            if (!name_result)
                return name_result.error();
            for (auto name : *name_result)
                result.push_back(name);
        }
        return result;
    }

}
