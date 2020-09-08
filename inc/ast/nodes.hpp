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
        struct Type;
        struct Declaration;
        struct Expression;
        struct Statement;
        struct ArrayElem;
    }

    namespace node {

        //// Types ////

        using auto_node = base::node<>;
        struct Auto: auto_node {
            using auto_node::auto_node;
        };

        using type_name_node = base::node <
            std::string
        >;
        struct TypeName: type_name_node {
            using type_name_node::type_name_node;
            enum component_name {
                name
            };
        };

        using function_type_node = base::node <
            category::Type *,
            category::Type *
        >;
        struct FunctionType: function_type_node {
            using function_type_node::function_type_node;
            enum component_name {
                output,
                input
            };
        };

        using array_type_node = base::node <
            category::Type *,
            category::Expression *
        >;
        struct ArrayType: array_type_node {
            using array_type_node::array_type_node;
            enum component_name {
                type,
                size
            };
        };

        using auto_array_type_node = base::node <
            category::Type *
        >;
        struct AutoArrayType: auto_array_type_node {
            using auto_array_type_node::auto_array_type_node;
            enum component_name {
                type
            };
        };

        using decl_array_type_node = base::node <
            category::Type *,
            category::Declaration *
        >;
        struct DeclArrayType: decl_array_type_node {
            using decl_array_type_node::decl_array_type_node;
            enum component_name {
                value_type,
                size_decl
            };
        };

        using buffer_type_node = base::node <
            category::Expression *
        >;
        struct BufferType: buffer_type_node {
            using buffer_type_node::buffer_type_node;
            enum component_name {
                size
            };
        };

        using type_decl_node = base::node <
            node::TypeName
        >;
        struct TypeDecl: type_decl_node {
            using type_decl_node::type_decl_node;
            enum component_name {
                name
            };
        };

        using tuple_type_node = base::node <
            std::vector<category::Type *>
        >;
        struct TupleType: tuple_type_node {
            using tuple_type_node::tuple_type_node;
            enum component_name {
                types
            };
        };

        //// Expressions ////

        using name_node = base::node <
            std::string
        >;
        struct Name: name_node {
            using name_node::name_node;
            enum component_name {
                name
            };
        };

        using boolean_node = base::node <
            bool
        >;
        struct Boolean: boolean_node {
            using boolean_node::boolean_node;
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

        using un_node  = base::node<category::Expression *>;
        using bin_node = base::node<category::Expression *, category::Expression *>;
        using conversion_node = base::node <
            category::Type *,
            category::Expression *
        >;
        struct Or:          bin_node        { using bin_node::bin_node;               enum component_name { lhs, rhs }; };
        struct And:         bin_node        { using bin_node::bin_node;               enum component_name { lhs, rhs }; };
        struct Eq:          bin_node        { using bin_node::bin_node;               enum component_name { lhs, rhs }; };
        struct Ne:          bin_node        { using bin_node::bin_node;               enum component_name { lhs, rhs }; };
        struct Ge:          bin_node        { using bin_node::bin_node;               enum component_name { lhs, rhs }; };
        struct Le:          bin_node        { using bin_node::bin_node;               enum component_name { lhs, rhs }; };
        struct Gt:          bin_node        { using bin_node::bin_node;               enum component_name { lhs, rhs }; };
        struct Lt:          bin_node        { using bin_node::bin_node;               enum component_name { lhs, rhs }; };
        struct Add:         bin_node        { using bin_node::bin_node;               enum component_name { lhs, rhs }; };
        struct Sub:         bin_node        { using bin_node::bin_node;               enum component_name { lhs, rhs }; };
        struct Mul:         bin_node        { using bin_node::bin_node;               enum component_name { lhs, rhs }; };
        struct Div:         bin_node        { using bin_node::bin_node;               enum component_name { lhs, rhs }; };
        struct Mod:         bin_node        { using bin_node::bin_node;               enum component_name { lhs, rhs }; };
        struct Pow:         bin_node        { using bin_node::bin_node;               enum component_name { lhs, rhs }; };
        struct Minus:       un_node         { using un_node::un_node;                 enum component_name { argument }; };
        struct Plus:        un_node         { using un_node::un_node;                 enum component_name { argument }; };
        struct Not:         un_node         { using un_node::un_node;                 enum component_name { argument }; };
        struct Application: bin_node        { using bin_node::bin_node;               enum component_name { function,  arguments }; };
        struct Subscript:   bin_node        { using bin_node::bin_node;               enum component_name { container, index     }; };
        struct Conversion:  conversion_node { using conversion_node::conversion_node; enum component_name { type,      value     }; };

        using block_node = base::node <
            std::vector<category::Statement *>
        >;
        struct Block: block_node {
            using block_node::block_node;
            enum component_name {
                statements
            };
        };

        using exprif_node = base::node <
            category::Expression *,
            category::Expression *,
            category::Expression *
        >;
        struct ExprIf: exprif_node {
            using exprif_node::exprif_node;
            enum component_name {
                condition,
                positive,
                negative
            };
        };

        using function_node = base::node <
            category::Type *,
            category::Declaration *,
            category::Expression *
        >;
        struct Function: function_node {
            using function_node::function_node;
            enum component_name {
                output,
                input,
                body
            };
        };

        using array_node = base::node <
            std::vector<category::ArrayElem *>
        >;
        struct Array: array_node {
            using array_node::array_node;
            enum component_name {
                elements
            };
        };

        using tuple_node = base::node <
            std::vector<category::Expression *>
        >;
        struct Tuple: tuple_node {
            using tuple_node::tuple_node;
            enum component_name {
                values
            };
        };

        //// Array literal elements ////

        using range_to_node = base::node <
            category::Expression *,
            category::Expression *
        >;
        struct RangeTo: range_to_node {
            using range_to_node::range_to_node;
            enum component_name {
                from,
                to
            };
        };

        using range_to_by_node = base::node <
            category::Expression *,
            category::Expression *,
            category::Expression *
        >;
        struct RangeToBy: range_to_by_node {
            using range_to_by_node::range_to_by_node;
            enum component_name {
                from,
                to,
                by
            };
        };

        using spread_node = base::node <
            category::Expression *
        >;
        struct Spread: spread_node {
            using spread_node::spread_node;
            enum component_name {
                container
            };
        };

        //// Declarations ////

        using single_decl_node = base::node <
            node::Name,
            category::Type *
        >;
        struct SingleDecl: single_decl_node {
            using single_decl_node::single_decl_node;
            enum component_name {
                name,
                type
            };
        };

        using tuple_decl_node = base::node <
            std::vector<category::Declaration *>
        >;
        struct TupleDecl: tuple_decl_node {
            using tuple_decl_node::tuple_decl_node;
            enum component_name {
                declarations,
            };
        };

        //// Statements ////

        using if_node = base::node <
            category::Expression *,
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

        using when_node = base::node <
            category::Expression *,
            category::Statement *
        >;
        struct When: when_node {
            using when_node::when_node;
            enum component_name {
                condition,
                branch
            };
        };

        using definition_node = base::node <
            category::Declaration *,
            category::Expression *
        >;
        struct Definition: definition_node {
            using definition_node::definition_node;
            enum component_name {
                pattern,
                value
            };
        };

        using type_def_node = base::node <
            node::TypeName,
            category::Type *
        >;
        struct TypeDef: type_def_node {
            using type_def_node::type_def_node;
            enum component_name {
                name,
                type
            };
        };

        using function_def_node = base::node <
            category::Type *,
            category::Declaration *,
            node::Name,
            category::Expression *
        >;
        struct FunctionDef: function_def_node {
            using function_def_node::function_def_node;
            enum component_name {
                output,
                input,
                name,
                body
            };
        };

        using assignment_node = base::node <
            node::Name,
            category::Expression *
        >;
        struct Assignment: assignment_node {
            using assignment_node::assignment_node;
            enum component_name {
                name,
                value
            };
        };

        using return_node = base::node <
            category::Expression *
        >;
        struct Return: return_node {
            using return_node::return_node;
            enum component_name {
                value
            };
        };

    }
}
