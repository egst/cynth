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
            std::variant<cynth::ast::node::None, types...> content;

            category ():
                content{cynth::ast::node::None{}} {}

            template <typename type> requires
                std::same_as<std::remove_reference_t<type>, cynth::ast::node::None> ||
                (std::same_as<std::remove_reference_t<type>, types> || ...)
            category (type && content):
                content{std::forward<type>(content)} {}

            /*category (category && other):
                content{std::move(other.content)} {}*/

            //template <typename... other_types, std::derived_from<category<other_types...>> t>
            //category (t && other):
            template <typename... other_types>
            category (category<other_types...> && other)
            //: content{std::move(other.content)} {}
            {
                std::visit (
                    [this] (auto && x) { this->content = std::move(x); },
                    other.content
                );
            }

            template <typename type>
            category & operator = (type && content) {
                content = std::forward<type>(content);
                return *this;
            }

            /*category & operator = (category && other) {
                content = std::move(other.content);
                return *this;
            }*/

            template <typename... other_types>
            category & operator = (category<other_types...> && other) {
                content = std::move(other.content);
                return *this;
            }

            category & base () const { return *static_cast<category*>(this); }
        };

    }

    namespace category {

        using expressible_category = base::category <
            node::Block,
            node::ExprIf,
            node::Name,
            node::Integer,
            node::Decimal,
            node::String
        >;
        struct Expressible: expressible_category {
            using expressible_category::expressible_category;
        };

        using statement_category = util::extend <
            expressible_category,
            node::If,
            node::When,
            node::Declaration,
            node::Definition,
            node::Assignment,
            node::Alias,
            node::Return
        >;
        struct Statement: statement_category {
            using statement_category::statement_category;
        };

        using type_category = base::category <
            node::Auto,
            node::TypeName,
            node::FunctionType,
            node::TupleType
        >;
        struct Type: type_category {
            using type_category::type_category;
        };

        using node_category = util::cat <
            statement_category,
            type_category
        >;
        struct Any: node_category {
            using node_category::node_category;
        };

        /*using keyword_category = base::category <
            token::Return,
            token::If,
            token::Else,
            token::When,
            token::While,
            token::For,
            token::In,
            token::To,
            token::By,
            token::Type,
            token::Buffer
        >;
        using symbol_category = base::category <
            token::Sep,
            token::OParen,
            token::CParen,
            token::OBrack,
            token::CBrack,
            token::OBrace,
            token::CBrace,
            token::Add,
            token::Sub,
            token::Mult,
            token::Div,
            token::Mod,
            token::Pow,
            token::Asgn,
            token::AddAsgn,
            token::SubAsgn,
            token::MultAsgn,
            token::DivAsgn,
            token::ModAsgn,
            token::PowAsgn,
            token::Eq,
            token::Ne,
            token::Ge,
            token::Le,
            token::Gt,
            token::Lt,
            token::Comma,
            token::Colon,
            token::Auto
        >;
        using token_category = util::extend<
            util::cat <
                keyword_category,
                symbol_category
            >,
            token::Name,
            token::TypeName,
            token::Integer,
            token::Decimal,
            token::String,
            token::NONE
        >;
        struct Token: token_category {
            using token_category::token_category;
            Token (int): token_category{token::NONE{}} {}
            template <typename t>
            category & operator = (t && x) {
                base() = std::forward<t>(x);
                return *this;
            }
            operator bool () const {
                return std::visit(
                    util::overload {
                        [] (token::NONE) { return false; },
                        [] (auto)        { return true;  },
                    },
                    content
                );
            }
        };*/

    }

}
