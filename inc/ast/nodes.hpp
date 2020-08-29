#pragma once

#include "util.hpp" 

#include <tuple>
#include <string>
#include <vector>
#include <utility>
#include <type_traits>

namespace cynth::ast {

    namespace base {

        namespace detail {
            constexpr util::overload free = {
                [] <typename t> (t * pointer) {
                    if (pointer)
                        delete pointer;
                },
                [] <util::constrained_range<std::is_pointer> t> (t & pointers) {
                    for (auto const & pointer : pointers) if (pointer)
                        delete pointer;
                },
                [] <typename t> (t &&) {}
            };

            constexpr util::overload reset = {
                [] <typename t> (t * & pointer) {
                    pointer = nullptr;
                },
                [] <util::constrained_range<std::is_pointer> t> (t & pointers) {
                    pointers = {};
                },
                [] <typename t> (t &&) {}
            };
        }

        template <typename... types>
        struct node {
            std::tuple<types...> components;

            node (): components{} {}

            node (types &&... components): components{std::move(components)...} {}

            node (node && other): components{std::move(other.components)} {
                other.reset();
            }

            node & operator = (node && other) {
                components = std::move(other.components);
                other.reset();
                return *this;
            }

            void reset () {
                util::tuple_foreach(detail::reset, components);
            }

            ~node () {
                util::tuple_foreach(detail::free, components);
            }
        };

        template <>
        struct node<> {
            std::tuple<> components;

            node () {}
        };

    }

    namespace category {
        struct Expressible;
        struct Statement;
        struct Type;
    }

    namespace node {

        using type_name_node = base::node <
            std::string
        >;
        struct TypeName: type_name_node {
            using type_name_node::type_name_node;
            enum component_name {
                name
            };
        };

        using auto_node = base::node<>;
        struct Auto: auto_node {
            using auto_node::auto_node;
        };

        using function_type_node = base::node <
            category::Type *,
            std::vector<category::Type *>
        >;
        struct FunctionType: function_type_node {
            using function_type_node::function_type_node;
            enum component_name {
                return_type,
                parameter_types
            };
        };

        using tuple_type_node = base::node <
            std::vector<category::Type *>
        >;
        struct TupleType: tuple_type_node {
            using tuple_type_node::tuple_type_node;
            enum component_name {
                rest
            };
        };

        using name_node = base::node <
            std::string
        >;
        struct Name: name_node {
            using name_node::name_node;
            enum component_name {
                name
            };
        };

        using block_node = base::node <
            std::vector<category::Statement *>
        >;
        struct Block: block_node {
            using block_node::block_node;
            enum component_name {
                statements
            };
        };

        using when_node = base::node <
            category::Expressible *,
            category::Statement *
        >;
        struct When: when_node {
            using when_node::when_node;
            enum component_name {
                condition,
                branch
            };
        };

        using if_node = base::node <
            category::Expressible *,
            category::Statement *,
            category::Statement *
        >;
        struct If: if_node {
            using if_node::if_node;
            enum component_name {
                condition,
                positive,
                negative
            };
        };

        using exprif_node = base::node <
            category::Expressible *,
            category::Expressible *,
            category::Expressible *
        >;
        struct ExprIf: exprif_node {
            using exprif_node::exprif_node;
            enum component_name {
                condition,
                positive,
                negative
            };
        };

        using alias_node = base::node <
            node::TypeName *,
            category::Type *
        >;
        struct Alias: alias_node {
            using alias_node::alias_node;
            enum component_name {
                name,
                type
            };
        };

        using declaration_node = base::node <
            node::Name *,
            category::Type *
        >;
        struct Declaration: declaration_node {
            using declaration_node::declaration_node;
            enum component_name {
                name,
                type
            };
        };

        using definition_node = base::node <
            node::Name *,
            category::Type *,
            category::Expressible *
        >;
        struct Definition: definition_node {
            using definition_node::definition_node;
            enum component_name {
                name,
                type,
                value
            };
        };

        using assignment_node = base::node <
            node::Name *,
            category::Expressible *
        >;
        struct Assignment: assignment_node {
            using assignment_node::assignment_node;
            enum component_name {
                name,
                value
            };
        };

        using return_node = base::node <
            category::Expressible *
        >;
        struct Return: return_node {
            using return_node::return_node;
            enum component_name {
                value
            };
        };

        using integer_node = base::node <
            int
        >;
        struct Integer: integer_node {
            using integer_node::integer_node;
            enum component_name {
                value
            };
        };

        using decimal_node = base::node <
            float
        >;
        struct Decimal: decimal_node {
            using decimal_node::decimal_node;
            enum component_name {
                value
            };
        };

        using string_node = base::node <
            std::string
        >;
        struct String: string_node {
            using string_node::string_node;
            enum component_name {
                value
            };
        };

        struct None {};

    }
}
