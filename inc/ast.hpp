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

    namespace detail {
        struct display_functor {
            // Nodes:
            std::string operator () (node::Auto const &) const {
                return "$";
            }
            std::string operator () (node::TypeName const & n) const {
                return get<node::TypeName::name>(n);
            }
            std::string operator () (node::FunctionType const & n) const {
                return
                    (*this)(get<node::FunctionType::return_type>(n)) +
                    "(" + util::join(", ", util::lift{*this}(get<node::FunctionType::parameter_types>(n))) + ")";
            }
            std::string operator () (node::TupleType const & n) const {
                return "(" + util::join(", ", util::lift{*this}(get<node::TupleType::types>(n))) + ")";
            }
            std::string operator () (node::Name const & n) const {
                return get<node::Name::name>(n);
            }
            std::string operator () (node::Block const & n) const {
                return "{\n" + util::join(";\n", util::lift{*this}(get<node::Block::statements>(n))) + "\n}";
                /*std::string result = "{\n";
                for (auto const & stmt : get<node::Block::statements>(n))
                    result += (*this)(stmt) + ";\n";
                return result + "}";*/
            }
            std::string operator () (node::When const & n) const {
                return "when (" + (*this)(get<node::When::condition>(n)) + ") " + (*this)(get<node::When::branch>(n));
            }
            std::string operator () (node::If const & n) const {
                return
                    "if (" + (*this)(get<node::If::condition>(n)) + ") " +
                    (*this)(get<node::If::positive>(n)) + " else " +
                    (*this)(get<node::If::negative>(n));
            }
            std::string operator () (node::ExprIf const & n) const {
                return
                    "if (" + (*this)(get<node::ExprIf::condition>(n)) + ") " +
                    (*this)(get<node::ExprIf::positive>(n)) + " else " +
                    (*this)(get<node::ExprIf::negative>(n));
            }
            std::string operator () (node::Alias const & n) const {
                return "type " + (*this)(get<node::Alias::name>(n)) + " = " + (*this)(get<node::Alias::type>(n));
            }
            std::string operator () (node::Declaration const & n) const {
                return (*this)(get<node::Declaration::type>(n)) + " " + (*this)(get<node::Declaration::name>(n));
            }
            std::string operator () (node::Definition const & n) const {
                return (*this)(get<node::Definition::type>(n)) + " " + (*this)(get<node::Definition::name>(n)) + " = " + (*this)(get<node::Definition::value>(n));
            }
            std::string operator () (node::Assignment const & n) const {
                return (*this)(get<node::Assignment::name>(n)) + " = " + (*this)(get<node::Assignment::value>(n));
            }
            std::string operator () (node::Return const & n) const {
                return "return " + (*this)(get<node::Return::value>(n));
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
            std::string operator () (node::None const &) const {
                return "NONE";
            }

            // Tokens:
            /*std::string operator () (token::Name     const & t) const { return "Name("     + t.content + ")"; }
            std::string operator () (token::TypeName const & t) const { return "TypeName(" + t.content + ")"; }
            std::string operator () (token::Integer  const & t) const { return "Integer("  + t.content + ")"; }
            std::string operator () (token::Decimal  const & t) const { return "Decimal("  + t.content + ")"; }
            std::string operator () (token::String   const & t) const { return "String("   + t.content + ")"; }
            std::string operator () (token::Return   const &)   const { return "Return";   }
            std::string operator () (token::If       const &)   const { return "If";       }
            std::string operator () (token::Else     const &)   const { return "Else";     }
            std::string operator () (token::When     const &)   const { return "When";     }
            std::string operator () (token::While    const &)   const { return "While";    }
            std::string operator () (token::For      const &)   const { return "For";      }
            std::string operator () (token::In       const &)   const { return "In";       }
            std::string operator () (token::To       const &)   const { return "To";       }
            std::string operator () (token::By       const &)   const { return "By";       }
            std::string operator () (token::Type     const &)   const { return "Type";     }
            std::string operator () (token::Buffer   const &)   const { return "Buffer";   }
            std::string operator () (token::OParen   const &)   const { return "OParen";   }
            std::string operator () (token::CParen   const &)   const { return "CParen";   }
            std::string operator () (token::OBrack   const &)   const { return "OBrack";   }
            std::string operator () (token::CBrack   const &)   const { return "CBrack";   }
            std::string operator () (token::OBrace   const &)   const { return "OBrace";   }
            std::string operator () (token::CBrace   const &)   const { return "CBrace";   }
            std::string operator () (token::Add      const &)   const { return "Add";      }
            std::string operator () (token::Sub      const &)   const { return "Sub";      }
            std::string operator () (token::Mult     const &)   const { return "Mult";     }
            std::string operator () (token::Div      const &)   const { return "Div";      }
            std::string operator () (token::Mod      const &)   const { return "Mod";      }
            std::string operator () (token::Pow      const &)   const { return "Pow";      }
            std::string operator () (token::Asgn     const &)   const { return "Asgn";     }
            std::string operator () (token::AddAsgn  const &)   const { return "AddAsgn";  }
            std::string operator () (token::SubAsgn  const &)   const { return "SubAsgn";  }
            std::string operator () (token::MultAsgn const &)   const { return "MultAsgn"; }
            std::string operator () (token::DivAsgn  const &)   const { return "MultAsgn"; }
            std::string operator () (token::ModAsgn  const &)   const { return "ModAsgn";  }
            std::string operator () (token::PowAsgn  const &)   const { return "PowAsgn";  }
            std::string operator () (token::Eq       const &)   const { return "Eq";       }
            std::string operator () (token::Ne       const &)   const { return "Ne";       }
            std::string operator () (token::Ge       const &)   const { return "Ge";       }
            std::string operator () (token::Le       const &)   const { return "Le";       }
            std::string operator () (token::Gt       const &)   const { return "Gt";       }
            std::string operator () (token::Lt       const &)   const { return "Lt";       }
            std::string operator () (token::Comma    const &)   const { return "Comma";    }
            std::string operator () (token::Colon    const &)   const { return "Colon";    }
            std::string operator () (token::Sep      const &)   const { return "Sep";      }
            std::string operator () (token::Auto     const &)   const { return "Auto";     }
            std::string operator () (token::NONE     const &)   const { return "NONE";     }*/

            // Categories:
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
