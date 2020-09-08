#pragma once

//#include "ast/tokens.hpp" 
#include "ast/nodes.hpp" 

#include "util.hpp" 

#include <variant>
#include <utility>
#include <concepts>

namespace cynth::ast {

    namespace base {

        template <typename... types>
        struct category {
            std::variant<types...> content;

            category (): content{} {}

            category (category && other): 
                content{std::move(other.content)} {}

            template <typename... other_types>
            category (category<other_types...> && other) {
                std::visit (
                    [this] (auto && x) { this->content = std::move(x); },
                    other.content
                );
            }

            category (std::variant<types...> && content):
                content{std::move(content)} {}

            template <typename type> requires (std::same_as<std::remove_reference_t<type>, types> || ...)
            category (type && content):
                content{std::forward<type>(content)} {}

            category & operator = (category && other) {
                content = std::move(other.content);
                return *this;
            }

            template <typename... other_types>
            category & operator = (category<other_types...> && other) {
                std::visit (
                    [this] (auto && x) { this->content = std::move(x); },
                    other.content
                );
                return *this;
            }

            category & operator = (std::variant<types...> && other_content) {
                content = std::move(other_content);
                return *this;
            }

            template <typename type> requires (std::same_as<std::remove_reference_t<type>, types> || ...)
            category & operator= (type && other_content) {
                content = std::forward<type>(other_content);
                return *this;
            }

            category & base () { return static_cast<category &>(*this); }
        };

    }

    namespace category {

        using type_category = base::category <
            node::Auto,
            node::TypeName,
            node::FunctionType,
            node::ArrayType,
            node::AutoArrayType,
            node::DeclArrayType,
            node::BufferType,
            node::TypeDecl,
            node::TupleType
        >;
        struct Type: type_category {
            using type_category::type_category;
            /*using type_category::operator=;*/
            template <typename t> Type & operator = (t && x) { base() = std::forward<t>(x); return *this; }
        };

        using expression_category = base::category <
            node::Name,
            node::Boolean, node::Integer, node::Decimal, node::String,
            node::Not,     node::Or,      node::And,
            node::Eq,      node::Ne,      node::Ge,      node::Le,  node::Gt,  node::Lt,
            node::Add,     node::Sub,     node::Mul,     node::Div, node::Mod, node::Pow,
            node::Plus,    node::Minus,
            node::Application,
            node::Subscript,
            node::Conversion,
            node::Block,
            node::ExprIf,
            node::Function,
            node::Array,
            node::Tuple
        >;
        struct Expression: expression_category {
            using expression_category::expression_category;
            /*using expression_category::operator=;*/
            template <typename t> Expression & operator = (t && x) { base() = std::forward<t>(x); return *this; }
        };

        using declaration_category = base::category <
            node::SingleDecl,
            node::TupleDecl
        >;
        struct Declaration: declaration_category {
            using declaration_category::declaration_category;
            /*using declaration_category::operator=;*/
            template <typename t> Declaration & operator = (t && x) { base() = std::forward<t>(x); return *this; }
        };

        using array_elem_category = util::extend <
            expression_category,
            node::RangeTo,
            node::RangeToBy,
            node::Spread
        >;
        struct ArrayElem: array_elem_category {
            using array_elem_category::array_elem_category;
            /*using array_elem_category::operator=;*/
            template <typename t> ArrayElem & operator = (t && x) { base() = std::forward<t>(x); return *this; }
        };

        using statement_category = util::extend <
            util::cat <
                expression_category,
                declaration_category
            >,
            node::If,
            node::When,
            node::Definition,
            node::TypeDef,
            node::FunctionDef,
            node::Assignment,
            node::Return
        >;
        struct Statement: statement_category {
            using statement_category::statement_category;
            /*using statement_category::operator=;*/
            template <typename t> Statement & operator = (t && x) { base() = std::forward<t>(x); return *this; }
        };

    }

}
