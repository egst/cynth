#pragma once

#include "ast/tokens.hpp"
#include "ast/nodes.hpp"
#include "ast/categories.hpp"

#include "util.hpp"

#include <string>
#include <tuple>
#include <variant>
#include <string>
#include <concepts>

#include <iostream>

namespace cynth::ast {

    namespace detail {
        // Dereference a pointer:
        template <typename t>
        t & deref (t * pointer) {
            return *pointer;
        }
        // Make a reference view over a range of pointers:
        template <util::range t> //requires requires (t a) { {*a.begin()} -> util::pointer; }
        util::reference_view<t> deref (t & pointers) {
            return pointers;
        }
        // Identity otherwise:
        template <typename t>
        t & deref (t & reference) {
            return reference;
        }

    }

    template <auto index, typename t> requires std::same_as<decltype(index), typename t::component_name>
    decltype(auto) get (t & target) {
        return detail::deref(std::get<index>(target.components));
    }

    template <auto index, typename t> requires std::same_as<decltype(index), typename t::component_name>
    decltype(auto) get_raw (t & target) {
        return std::get<index>(target.components);
    }

    namespace detail {
        struct display_functor {
            std::string operator () (node::Auto const &) const {
                return "$";
            }
            std::string operator () (node::TypeName const & n) const {
                return get<node::TypeName::name>(n);
            }
            std::string operator () (node::FunctionType const & n) const {
                return (*this)(get<node::FunctionType::output>(n)) + " " + util::parenthesized((*this)(get<node::FunctionType::input>(n)));
            }
            std::string operator () (node::ArrayType const & n) const {
                return (*this)(get<node::ArrayType::type>(n)) + " [" + (*this)(get<node::ArrayType::size>(n)) + "]";
            }
            std::string operator () (node::AutoArrayType const & n) const {
                return (*this)(get<node::AutoArrayType::type>(n)) + " [$]";
            }
            std::string operator () (node::DeclArrayType const & n) const {
                return (*this)(get<node::DeclArrayType::value_type>(n)) + " [" + (*this)(get<node::DeclArrayType::size_decl>(n)) + "]";
            }
            std::string operator () (node::BufferType const & n) const {
                return "buffer [" + (*this)(get<node::BufferType::size>(n)) + "]";
            }
            std::string operator () (node::TypeDecl const & n) const {
                return "type " + (*this)(get<node::TypeDecl::name>(n));
            }
            std::string operator () (node::TupleType const & n) const {
                return "(" + util::join(", ", util::lift{*this}(get<node::TupleType::types>(n))) + ")";
            }

            std::string operator () (node::SingleDecl const & n) const {
                return (*this)(get<node::SingleDecl::type>(n)) + " " + (*this)(get<node::SingleDecl::name>(n));
            }
            std::string operator () (node::TupleDecl const & n) const {
                return "(" + util::join(", ", util::lift{*this}(get<node::TupleDecl::declarations>(n))) + ")";
            }

            std::string operator () (node::Name const & n) const {
                return get<node::Name::name>(n);
            }
            std::string operator () (node::Boolean const & n) const {
                return get<node::Boolean::value>(n) ? "true" : "false";
            }
            std::string operator () (node::Integer const & n) const {
                return std::to_string(get<node::Integer::value>(n));
            }
            std::string operator () (node::Decimal const & n) const {
                return std::to_string(get<node::Decimal::value>(n));
            }
            std::string operator () (node::String const & n) const {
                return "\"" + get<node::String::value>(n) + "\"";
            }
            std::string operator () (node::Array const & n) const {
                return "[" + util::join(", ", util::lift{*this}(get<node::Array::elements>(n))) + "]";
            }

            std::string operator () (node::RangeTo const & n) const {
                return (*this)(get<node::RangeTo::from>(n)) + " to " + (*this)(get<node::RangeTo::to>(n));
            }
            std::string operator () (node::RangeToBy const & n) const {
                return (*this)(get<node::RangeToBy::from>(n)) + " to " + (*this)(get<node::RangeToBy::to>(n)) + " by " + (*this)(get<node::RangeToBy::by>(n));
            }
            std::string operator () (node::Spread const & n) const {
                return "..." + (*this)(get<node::Spread::container>(n));
            }

            std::string operator () (node::Or    const & n) const { return "(" + (*this)(get<node::Or ::lhs>(n)) + " || " + (*this)(get<node::Or ::rhs>(n)) + ")"; }
            std::string operator () (node::And   const & n) const { return "(" + (*this)(get<node::And::lhs>(n)) + " && " + (*this)(get<node::And::rhs>(n)) + ")"; }
            std::string operator () (node::Eq    const & n) const { return "(" + (*this)(get<node::Eq ::lhs>(n)) + " == " + (*this)(get<node::Eq ::rhs>(n)) + ")"; }
            std::string operator () (node::Ne    const & n) const { return "(" + (*this)(get<node::Ne ::lhs>(n)) + " != " + (*this)(get<node::Ne ::rhs>(n)) + ")"; }
            std::string operator () (node::Ge    const & n) const { return "(" + (*this)(get<node::Ge ::lhs>(n)) + " >= " + (*this)(get<node::Ge ::rhs>(n)) + ")"; }
            std::string operator () (node::Le    const & n) const { return "(" + (*this)(get<node::Le ::lhs>(n)) + " <= " + (*this)(get<node::Le ::rhs>(n)) + ")"; }
            std::string operator () (node::Gt    const & n) const { return "(" + (*this)(get<node::Gt ::lhs>(n)) + " > "  + (*this)(get<node::Gt ::rhs>(n)) + ")"; }
            std::string operator () (node::Lt    const & n) const { return "(" + (*this)(get<node::Lt ::lhs>(n)) + " < "  + (*this)(get<node::Lt ::rhs>(n)) + ")"; }
            std::string operator () (node::Add   const & n) const { return "(" + (*this)(get<node::Add::lhs>(n)) + " + "  + (*this)(get<node::Add::rhs>(n)) + ")"; }
            std::string operator () (node::Sub   const & n) const { return "(" + (*this)(get<node::Sub::lhs>(n)) + " - "  + (*this)(get<node::Sub::rhs>(n)) + ")"; }
            std::string operator () (node::Mul   const & n) const { return "(" + (*this)(get<node::Mul::lhs>(n)) + " * "  + (*this)(get<node::Mul::rhs>(n)) + ")"; }
            std::string operator () (node::Div   const & n) const { return "(" + (*this)(get<node::Div::lhs>(n)) + " / "  + (*this)(get<node::Div::rhs>(n)) + ")"; }
            std::string operator () (node::Mod   const & n) const { return "(" + (*this)(get<node::Mod::lhs>(n)) + " % "  + (*this)(get<node::Mod::rhs>(n)) + ")"; }
            std::string operator () (node::Pow   const & n) const { return "(" + (*this)(get<node::Pow::lhs>(n)) + " ^ "  + (*this)(get<node::Pow::rhs>(n)) + ")"; }
            std::string operator () (node::Plus  const & n) const { return "+" + (*this)(get<node::Plus ::argument>(n)); }
            std::string operator () (node::Minus const & n) const { return "-" + (*this)(get<node::Minus::argument>(n)); }
            std::string operator () (node::Not   const & n) const { return "!" + (*this)(get<node::Not  ::argument>(n)); }
            std::string operator () (node::Application const & n) const {
                return (*this)(get<node::Application::function>(n)) + util::parenthesized((*this)(get<node::Application::arguments>(n)));
            }
            std::string operator () (node::Subscript const & n) const {
                return (*this)(get<node::Subscript::container>(n)) + "[" + (*this)(get<node::Subscript::index>(n)) + "]";
            }
            std::string operator () (node::Conversion const & n) const {
                return (*this)(get<node::Conversion::type>(n)) + util::parenthesized((*this)(get<node::Conversion::value>(n)));
            }

            std::string operator () (node::Block const & n) const {
                return "{\n" + util::join(";\n", util::lift{*this}(get<node::Block::statements>(n))) + "\n}";
            }
            std::string operator () (node::ExprIf const & n) const {
                return
                    "if " + util::parenthesized((*this)(get<node::ExprIf::condition>(n))) + " " +
                    (*this)(get<node::ExprIf::positive>(n)) + " else " +
                    (*this)(get<node::ExprIf::negative>(n));
            }
            std::string operator () (node::Function const & n) const {
                return
                    (*this)(get<node::Function::output>(n)) + " " +
                    "fn " + util::parenthesized((*this)(get<node::Function::input>(n))) + " " +
                    (*this)(get<node::Function::body>(n));
            }
            std::string operator () (node::Tuple const & n) const {
                return "(" + util::join(", ", util::lift{*this}(get<node::Tuple::values>(n))) + ")";
            }

            std::string operator () (node::When const & n) const {
                return "when " + util::parenthesized((*this)(get<node::When::condition>(n))) + " " + (*this)(get<node::When::branch>(n));
            }
            std::string operator () (node::If const & n) const {
                return
                    "if " + util::parenthesized((*this)(get<node::If::condition>(n))) + " " +
                    (*this)(get<node::If::positive>(n)) + " else " +
                    (*this)(get<node::If::negative>(n));
            }
            std::string operator () (node::Definition const & n) const {
                return (*this)(get<node::Definition::pattern>(n)) + " = " + (*this)(get<node::Definition::value>(n));
            }
            std::string operator () (node::TypeDef const & n) const {
                return "type " + (*this)(get<node::TypeDef::name>(n)) + " = " + (*this)(get<node::TypeDef::type>(n));
            }
            std::string operator () (node::FunctionDef const & n) const {
                return
                    (*this)(get<node::FunctionDef::output>(n)) + " " +
                    (*this)(get<node::FunctionDef::name>(n)) + " " +
                    util::parenthesized((*this)(get<node::FunctionDef::input>(n))) + " " +
                    (*this)(get<node::FunctionDef::body>(n));
            }
            std::string operator () (node::Assignment const & n) const {
                return (*this)(get<node::Assignment::name>(n)) + " = " + (*this)(get<node::Assignment::value>(n));
            }
            std::string operator () (node::Return const & n) const {
                return "return " + (*this)(get<node::Return::value>(n));
            }

            template <typename t> requires requires (t a) { a.content; } // TODO: Check if it's a variant.
            std::string operator () (t const & c) const {
                return std::visit(*this, c.content);
            }

            /*template <typename t>
            std::string operator () (t const & x) {
                //static_assert(false, "No implementation of display."); // TODO
                return "";
            }*/
        };
    }

    constexpr detail::display_functor display;

}
