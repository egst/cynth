#pragma once

#include "result.hpp"
#include "asg/types.hpp"
#include "asg/values.hpp"
#include "asg/interface.hpp"

#include <string>
#include <unordered_map>

namespace cynth {

    struct context {
        template <typename T>
        using vector = tuple_vector<T>;

        using value = vector<asg::value ::complete>;
        using type  = vector<asg::type  ::complete>;

        struct typed_value {
            value value;
            type  type;
        };

        std::unordered_map<std::string, typed_value> values;
        std::unordered_map<std::string, type>  types;

        context * parent;

        context (): parent{nullptr} {}

        context (context const & other) = default;
        context (context &&      other) = default;

        result<void> define_value (std::string name, typed_value const & v) {
            if (find_value_inside(name))
                return error{"Cannot redefine a value in the same scope."};
            values.insert({name, v});
            return {};
        }

        result<void> define_value (std::string name, value const & v) {
            if (find_value_inside(name))
                return error{"Cannot redefine a value in the same scope."};
            values.insert({name, {v, asg::value_type(v)}});
            return {};
        }

        result<void> define_type (std::string name, type const & t) {
            if (find_type_inside(name))
                return error{"Cannot redefine a type in the same scope."};
            types.insert({name, t});
            return {};
        }

        typed_value * find_value_inside (std::string const & name) {
            auto iter = values.find(name);
            return iter != values.end()
                ? &iter->second
                : nullptr;
        }

        type * find_type_inside (std::string const & name) {
            auto iter = types.find(name);
            return iter != types.end()
                ? &iter->second
                : nullptr;
        }

        typed_value * find_value (std::string const & name) {
            auto inside = find_value_inside(name);
            if (!parent || inside)
                return inside;
            return parent->find_value(name);
        }

        type * find_type (std::string const & name) {
            auto inside = find_type_inside(name);
            if (!parent || inside)
                return inside;
            return parent->find_type(name);
        }
    };

    context make_child_context (context & parent);

}
