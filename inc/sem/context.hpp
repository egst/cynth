#pragma once

#include "result.hpp"
#include "sem/types.hpp"
#include "sem/values.hpp"
#include "sem/interface.hpp"
#include "sem/context_types.hpp"

#include <tuple>
#include <string>
#include <vector>
#include <forward_list>
#include <unordered_map>

namespace cynth::sem {

    struct context {
        std::unordered_map<std::string, typed_value_vector> values;
        std::unordered_map<std::string, type_vector>        types;

        context * parent;

        context ();

        context (context const &) = default;
        context (context &&)      = default;

        result<void> define_value (std::string, typed_value        const &);
        result<void> define_value (std::string, typed_value_vector const &);
        result<void> define_type  (std::string, complete_type      const &);
        result<void> define_type  (std::string, type_vector        const &);

        // TODO?
        result<void> define_value (tuple_vector<complete_decl> const &, tuple_vector<complete_value> const &);
        result<void> declare      (tuple_vector<complete_decl> const &);

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

    protected:
        // Only contexts associated with the scope of a function or the global (outer) scope
        // contain these values, that are referenced by variables of referential types in inner scopes.
        // These values may remain allocated here even though the variables,
        // through which they were initialized, might not be in context anymore.
        // Right now, only arrays might be stored in function scope,
        // other referential values are only stored in the global scope.

        std::tuple <
            std::optional<refval_container<value::InValue>>,
            std::optional<refval_container<value::OutValue>>,
            std::optional<refval_container<value::ArrayValue>>,
            std::optional<refval_container<value::BufferValue>>,
            std::optional<refval_container<value::FunctionValue>>
        > referential;
    };

    context make_child_context (context & parent);

}
