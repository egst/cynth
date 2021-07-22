#pragma once

#include "result.hpp"
#include "asg/types.hpp"
#include "asg/values.hpp"
#include "asg/interface.hpp"
#include "context_types.hpp"

#include <tuple>
#include <string>
#include <vector>
#include <forward_list>
#include <unordered_map>

namespace cynth {

    struct context {
        std::unordered_map<std::string, typed_value> values;
        std::unordered_map<std::string, type_vector> types;

        context * parent;

        context ();

        context (context const &) = default;
        context (context &&)      = default;

        result<void> define_value (std::string, typed_value  const &);
        result<void> define_value (std::string, value_vector const &);
        result<void> define_type  (std::string, type_vector  const &);

        typed_value * find_value_inside (std::string const &);
        type_vector * find_type_inside  (std::string const &);
        typed_value * find_value        (std::string const &);
        type_vector * find_type         (std::string const &);

        template <typename Value>
        void init_storage ();

        template <typename Value>
        refval_container<Value> & stored_values ();

        template <typename Value>
        reference_result<Value> store_value (Value const &);

    private:
        // Only contexts associated with the scope of a function or the global (outer) scope
        // contain these values, that are referenced by variables of referential types in inner scopes.
        // These values may remain allocated here even though the variables,
        // through which they were initialized, might not be in context anymore.

        std::tuple <
            std::optional<refval_container<asg::value::InValue>>,
            std::optional<refval_container<asg::value::OutValue>>,
            std::optional<refval_container<asg::value::ArrayValue>>,
            std::optional<refval_container<asg::value::BufferValue>>
        > referential;
    };

    context make_child_context (context & parent);

}
