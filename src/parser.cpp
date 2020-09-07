// A Bison parser, made by GNU Bison 3.7.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.hpp"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 117 "src/parser.cpp"

  /// Build a parser object.
  parser::parser (cynth::ast::node::Block & result_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      result (result_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.YY_MOVE_OR_COPY< cynth::ast::category::Declaration > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expr_or: // expr_or
      case symbol_kind::S_expr_and: // expr_and
      case symbol_kind::S_expr_eq: // expr_eq
      case symbol_kind::S_expr_ord: // expr_ord
      case symbol_kind::S_expr_add: // expr_add
      case symbol_kind::S_expr_mul: // expr_mul
      case symbol_kind::S_expr_pow: // expr_pow
      case symbol_kind::S_expr_pre: // expr_pre
      case symbol_kind::S_expr_post: // expr_post
      case symbol_kind::S_expr_atom: // expr_atom
      case symbol_kind::S_expr_right: // expr_right
      case symbol_kind::S_paren_expr: // paren_expr
      case symbol_kind::S_void: // void
        value.YY_MOVE_OR_COPY< cynth::ast::category::Expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_pure: // pure
        value.YY_MOVE_OR_COPY< cynth::ast::category::Statement > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.YY_MOVE_OR_COPY< cynth::ast::category::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_add: // add
        value.YY_MOVE_OR_COPY< cynth::ast::node::Add > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_and: // and
        value.YY_MOVE_OR_COPY< cynth::ast::node::And > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_application: // application
        value.YY_MOVE_OR_COPY< cynth::ast::node::Application > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_type: // array_type
        value.YY_MOVE_OR_COPY< cynth::ast::node::ArrayType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.YY_MOVE_OR_COPY< cynth::ast::node::Assignment > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_auto: // auto
        value.YY_MOVE_OR_COPY< cynth::ast::node::Auto > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_auto_array_type: // auto_array_type
        value.YY_MOVE_OR_COPY< cynth::ast::node::AutoArrayType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< cynth::ast::node::Block > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_buffer_type: // buffer_type
        value.YY_MOVE_OR_COPY< cynth::ast::node::BufferType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_conversion: // conversion
        value.YY_MOVE_OR_COPY< cynth::ast::node::Conversion > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decimal: // decimal
        value.YY_MOVE_OR_COPY< cynth::ast::node::Decimal > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_array_type: // decl_array_type
        value.YY_MOVE_OR_COPY< cynth::ast::node::DeclArrayType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
        value.YY_MOVE_OR_COPY< cynth::ast::node::Definition > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_div: // div
        value.YY_MOVE_OR_COPY< cynth::ast::node::Div > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_eq: // eq
        value.YY_MOVE_OR_COPY< cynth::ast::node::Eq > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_if: // expr_if
        value.YY_MOVE_OR_COPY< cynth::ast::node::ExprIf > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function: // function
        value.YY_MOVE_OR_COPY< cynth::ast::node::Function > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_def: // function_def
        value.YY_MOVE_OR_COPY< cynth::ast::node::FunctionDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_type: // function_type
        value.YY_MOVE_OR_COPY< cynth::ast::node::FunctionType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ge: // ge
        value.YY_MOVE_OR_COPY< cynth::ast::node::Ge > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_gt: // gt
        value.YY_MOVE_OR_COPY< cynth::ast::node::Gt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if: // if
        value.YY_MOVE_OR_COPY< cynth::ast::node::If > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_integer: // integer
        value.YY_MOVE_OR_COPY< cynth::ast::node::Integer > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_le: // le
        value.YY_MOVE_OR_COPY< cynth::ast::node::Le > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lt: // lt
        value.YY_MOVE_OR_COPY< cynth::ast::node::Lt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_minus: // minus
        value.YY_MOVE_OR_COPY< cynth::ast::node::Minus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod: // mod
        value.YY_MOVE_OR_COPY< cynth::ast::node::Mod > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mul: // mul
        value.YY_MOVE_OR_COPY< cynth::ast::node::Mul > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_name: // name
        value.YY_MOVE_OR_COPY< cynth::ast::node::Name > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ne: // ne
        value.YY_MOVE_OR_COPY< cynth::ast::node::Ne > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_not: // not
        value.YY_MOVE_OR_COPY< cynth::ast::node::Not > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_or: // or
        value.YY_MOVE_OR_COPY< cynth::ast::node::Or > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_plus: // plus
        value.YY_MOVE_OR_COPY< cynth::ast::node::Plus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_pow: // pow
        value.YY_MOVE_OR_COPY< cynth::ast::node::Pow > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_return: // return
        value.YY_MOVE_OR_COPY< cynth::ast::node::Return > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_single_decl: // single_decl
        value.YY_MOVE_OR_COPY< cynth::ast::node::SingleDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_string: // string
        value.YY_MOVE_OR_COPY< cynth::ast::node::String > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sub: // sub
        value.YY_MOVE_OR_COPY< cynth::ast::node::Sub > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_subscript: // subscript
        value.YY_MOVE_OR_COPY< cynth::ast::node::Subscript > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.YY_MOVE_OR_COPY< cynth::ast::node::TypeDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_def: // type_def
        value.YY_MOVE_OR_COPY< cynth::ast::node::TypeDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_name: // type_name
        value.YY_MOVE_OR_COPY< cynth::ast::node::TypeName > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_when: // when
        value.YY_MOVE_OR_COPY< cynth::ast::node::When > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_start: // start
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_DECIMAL: // DECIMAL
      case symbol_kind::S_STRING: // STRING
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.YY_MOVE_OR_COPY< std::vector<cynth::ast::category::Declaration *> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.YY_MOVE_OR_COPY< std::vector<cynth::ast::category::Expression  *> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.YY_MOVE_OR_COPY< std::vector<cynth::ast::category::Statement   *> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_list: // type_list
        value.YY_MOVE_OR_COPY< std::vector<cynth::ast::category::Type        *> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.move< cynth::ast::category::Declaration > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expr_or: // expr_or
      case symbol_kind::S_expr_and: // expr_and
      case symbol_kind::S_expr_eq: // expr_eq
      case symbol_kind::S_expr_ord: // expr_ord
      case symbol_kind::S_expr_add: // expr_add
      case symbol_kind::S_expr_mul: // expr_mul
      case symbol_kind::S_expr_pow: // expr_pow
      case symbol_kind::S_expr_pre: // expr_pre
      case symbol_kind::S_expr_post: // expr_post
      case symbol_kind::S_expr_atom: // expr_atom
      case symbol_kind::S_expr_right: // expr_right
      case symbol_kind::S_paren_expr: // paren_expr
      case symbol_kind::S_void: // void
        value.move< cynth::ast::category::Expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_pure: // pure
        value.move< cynth::ast::category::Statement > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.move< cynth::ast::category::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_add: // add
        value.move< cynth::ast::node::Add > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_and: // and
        value.move< cynth::ast::node::And > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_application: // application
        value.move< cynth::ast::node::Application > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_type: // array_type
        value.move< cynth::ast::node::ArrayType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< cynth::ast::node::Assignment > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_auto: // auto
        value.move< cynth::ast::node::Auto > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_auto_array_type: // auto_array_type
        value.move< cynth::ast::node::AutoArrayType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.move< cynth::ast::node::Block > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_buffer_type: // buffer_type
        value.move< cynth::ast::node::BufferType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_conversion: // conversion
        value.move< cynth::ast::node::Conversion > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decimal: // decimal
        value.move< cynth::ast::node::Decimal > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_array_type: // decl_array_type
        value.move< cynth::ast::node::DeclArrayType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
        value.move< cynth::ast::node::Definition > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_div: // div
        value.move< cynth::ast::node::Div > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_eq: // eq
        value.move< cynth::ast::node::Eq > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_if: // expr_if
        value.move< cynth::ast::node::ExprIf > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function: // function
        value.move< cynth::ast::node::Function > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_def: // function_def
        value.move< cynth::ast::node::FunctionDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_type: // function_type
        value.move< cynth::ast::node::FunctionType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ge: // ge
        value.move< cynth::ast::node::Ge > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_gt: // gt
        value.move< cynth::ast::node::Gt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if: // if
        value.move< cynth::ast::node::If > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_integer: // integer
        value.move< cynth::ast::node::Integer > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_le: // le
        value.move< cynth::ast::node::Le > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_lt: // lt
        value.move< cynth::ast::node::Lt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_minus: // minus
        value.move< cynth::ast::node::Minus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mod: // mod
        value.move< cynth::ast::node::Mod > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_mul: // mul
        value.move< cynth::ast::node::Mul > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_name: // name
        value.move< cynth::ast::node::Name > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ne: // ne
        value.move< cynth::ast::node::Ne > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_not: // not
        value.move< cynth::ast::node::Not > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_or: // or
        value.move< cynth::ast::node::Or > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_plus: // plus
        value.move< cynth::ast::node::Plus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_pow: // pow
        value.move< cynth::ast::node::Pow > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_return: // return
        value.move< cynth::ast::node::Return > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_single_decl: // single_decl
        value.move< cynth::ast::node::SingleDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_string: // string
        value.move< cynth::ast::node::String > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sub: // sub
        value.move< cynth::ast::node::Sub > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_subscript: // subscript
        value.move< cynth::ast::node::Subscript > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.move< cynth::ast::node::TypeDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_def: // type_def
        value.move< cynth::ast::node::TypeDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_name: // type_name
        value.move< cynth::ast::node::TypeName > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_when: // when
        value.move< cynth::ast::node::When > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_start: // start
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_DECIMAL: // DECIMAL
      case symbol_kind::S_STRING: // STRING
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< std::vector<cynth::ast::category::Declaration *> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< std::vector<cynth::ast::category::Expression  *> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<cynth::ast::category::Statement   *> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_list: // type_list
        value.move< std::vector<cynth::ast::category::Type        *> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.copy< cynth::ast::category::Declaration > (that.value);
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expr_or: // expr_or
      case symbol_kind::S_expr_and: // expr_and
      case symbol_kind::S_expr_eq: // expr_eq
      case symbol_kind::S_expr_ord: // expr_ord
      case symbol_kind::S_expr_add: // expr_add
      case symbol_kind::S_expr_mul: // expr_mul
      case symbol_kind::S_expr_pow: // expr_pow
      case symbol_kind::S_expr_pre: // expr_pre
      case symbol_kind::S_expr_post: // expr_post
      case symbol_kind::S_expr_atom: // expr_atom
      case symbol_kind::S_expr_right: // expr_right
      case symbol_kind::S_paren_expr: // paren_expr
      case symbol_kind::S_void: // void
        value.copy< cynth::ast::category::Expression > (that.value);
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_pure: // pure
        value.copy< cynth::ast::category::Statement > (that.value);
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.copy< cynth::ast::category::Type > (that.value);
        break;

      case symbol_kind::S_add: // add
        value.copy< cynth::ast::node::Add > (that.value);
        break;

      case symbol_kind::S_and: // and
        value.copy< cynth::ast::node::And > (that.value);
        break;

      case symbol_kind::S_application: // application
        value.copy< cynth::ast::node::Application > (that.value);
        break;

      case symbol_kind::S_array_type: // array_type
        value.copy< cynth::ast::node::ArrayType > (that.value);
        break;

      case symbol_kind::S_assignment: // assignment
        value.copy< cynth::ast::node::Assignment > (that.value);
        break;

      case symbol_kind::S_auto: // auto
        value.copy< cynth::ast::node::Auto > (that.value);
        break;

      case symbol_kind::S_auto_array_type: // auto_array_type
        value.copy< cynth::ast::node::AutoArrayType > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.copy< cynth::ast::node::Block > (that.value);
        break;

      case symbol_kind::S_buffer_type: // buffer_type
        value.copy< cynth::ast::node::BufferType > (that.value);
        break;

      case symbol_kind::S_conversion: // conversion
        value.copy< cynth::ast::node::Conversion > (that.value);
        break;

      case symbol_kind::S_decimal: // decimal
        value.copy< cynth::ast::node::Decimal > (that.value);
        break;

      case symbol_kind::S_decl_array_type: // decl_array_type
        value.copy< cynth::ast::node::DeclArrayType > (that.value);
        break;

      case symbol_kind::S_definition: // definition
        value.copy< cynth::ast::node::Definition > (that.value);
        break;

      case symbol_kind::S_div: // div
        value.copy< cynth::ast::node::Div > (that.value);
        break;

      case symbol_kind::S_eq: // eq
        value.copy< cynth::ast::node::Eq > (that.value);
        break;

      case symbol_kind::S_expr_if: // expr_if
        value.copy< cynth::ast::node::ExprIf > (that.value);
        break;

      case symbol_kind::S_function: // function
        value.copy< cynth::ast::node::Function > (that.value);
        break;

      case symbol_kind::S_function_def: // function_def
        value.copy< cynth::ast::node::FunctionDef > (that.value);
        break;

      case symbol_kind::S_function_type: // function_type
        value.copy< cynth::ast::node::FunctionType > (that.value);
        break;

      case symbol_kind::S_ge: // ge
        value.copy< cynth::ast::node::Ge > (that.value);
        break;

      case symbol_kind::S_gt: // gt
        value.copy< cynth::ast::node::Gt > (that.value);
        break;

      case symbol_kind::S_if: // if
        value.copy< cynth::ast::node::If > (that.value);
        break;

      case symbol_kind::S_integer: // integer
        value.copy< cynth::ast::node::Integer > (that.value);
        break;

      case symbol_kind::S_le: // le
        value.copy< cynth::ast::node::Le > (that.value);
        break;

      case symbol_kind::S_lt: // lt
        value.copy< cynth::ast::node::Lt > (that.value);
        break;

      case symbol_kind::S_minus: // minus
        value.copy< cynth::ast::node::Minus > (that.value);
        break;

      case symbol_kind::S_mod: // mod
        value.copy< cynth::ast::node::Mod > (that.value);
        break;

      case symbol_kind::S_mul: // mul
        value.copy< cynth::ast::node::Mul > (that.value);
        break;

      case symbol_kind::S_name: // name
        value.copy< cynth::ast::node::Name > (that.value);
        break;

      case symbol_kind::S_ne: // ne
        value.copy< cynth::ast::node::Ne > (that.value);
        break;

      case symbol_kind::S_not: // not
        value.copy< cynth::ast::node::Not > (that.value);
        break;

      case symbol_kind::S_or: // or
        value.copy< cynth::ast::node::Or > (that.value);
        break;

      case symbol_kind::S_plus: // plus
        value.copy< cynth::ast::node::Plus > (that.value);
        break;

      case symbol_kind::S_pow: // pow
        value.copy< cynth::ast::node::Pow > (that.value);
        break;

      case symbol_kind::S_return: // return
        value.copy< cynth::ast::node::Return > (that.value);
        break;

      case symbol_kind::S_single_decl: // single_decl
        value.copy< cynth::ast::node::SingleDecl > (that.value);
        break;

      case symbol_kind::S_string: // string
        value.copy< cynth::ast::node::String > (that.value);
        break;

      case symbol_kind::S_sub: // sub
        value.copy< cynth::ast::node::Sub > (that.value);
        break;

      case symbol_kind::S_subscript: // subscript
        value.copy< cynth::ast::node::Subscript > (that.value);
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.copy< cynth::ast::node::TypeDecl > (that.value);
        break;

      case symbol_kind::S_type_def: // type_def
        value.copy< cynth::ast::node::TypeDef > (that.value);
        break;

      case symbol_kind::S_type_name: // type_name
        value.copy< cynth::ast::node::TypeName > (that.value);
        break;

      case symbol_kind::S_when: // when
        value.copy< cynth::ast::node::When > (that.value);
        break;

      case symbol_kind::S_start: // start
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_DECIMAL: // DECIMAL
      case symbol_kind::S_STRING: // STRING
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.copy< std::vector<cynth::ast::category::Declaration *> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.copy< std::vector<cynth::ast::category::Expression  *> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< std::vector<cynth::ast::category::Statement   *> > (that.value);
        break;

      case symbol_kind::S_type_list: // type_list
        value.copy< std::vector<cynth::ast::category::Type        *> > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.move< cynth::ast::category::Declaration > (that.value);
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expr_or: // expr_or
      case symbol_kind::S_expr_and: // expr_and
      case symbol_kind::S_expr_eq: // expr_eq
      case symbol_kind::S_expr_ord: // expr_ord
      case symbol_kind::S_expr_add: // expr_add
      case symbol_kind::S_expr_mul: // expr_mul
      case symbol_kind::S_expr_pow: // expr_pow
      case symbol_kind::S_expr_pre: // expr_pre
      case symbol_kind::S_expr_post: // expr_post
      case symbol_kind::S_expr_atom: // expr_atom
      case symbol_kind::S_expr_right: // expr_right
      case symbol_kind::S_paren_expr: // paren_expr
      case symbol_kind::S_void: // void
        value.move< cynth::ast::category::Expression > (that.value);
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_pure: // pure
        value.move< cynth::ast::category::Statement > (that.value);
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.move< cynth::ast::category::Type > (that.value);
        break;

      case symbol_kind::S_add: // add
        value.move< cynth::ast::node::Add > (that.value);
        break;

      case symbol_kind::S_and: // and
        value.move< cynth::ast::node::And > (that.value);
        break;

      case symbol_kind::S_application: // application
        value.move< cynth::ast::node::Application > (that.value);
        break;

      case symbol_kind::S_array_type: // array_type
        value.move< cynth::ast::node::ArrayType > (that.value);
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< cynth::ast::node::Assignment > (that.value);
        break;

      case symbol_kind::S_auto: // auto
        value.move< cynth::ast::node::Auto > (that.value);
        break;

      case symbol_kind::S_auto_array_type: // auto_array_type
        value.move< cynth::ast::node::AutoArrayType > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.move< cynth::ast::node::Block > (that.value);
        break;

      case symbol_kind::S_buffer_type: // buffer_type
        value.move< cynth::ast::node::BufferType > (that.value);
        break;

      case symbol_kind::S_conversion: // conversion
        value.move< cynth::ast::node::Conversion > (that.value);
        break;

      case symbol_kind::S_decimal: // decimal
        value.move< cynth::ast::node::Decimal > (that.value);
        break;

      case symbol_kind::S_decl_array_type: // decl_array_type
        value.move< cynth::ast::node::DeclArrayType > (that.value);
        break;

      case symbol_kind::S_definition: // definition
        value.move< cynth::ast::node::Definition > (that.value);
        break;

      case symbol_kind::S_div: // div
        value.move< cynth::ast::node::Div > (that.value);
        break;

      case symbol_kind::S_eq: // eq
        value.move< cynth::ast::node::Eq > (that.value);
        break;

      case symbol_kind::S_expr_if: // expr_if
        value.move< cynth::ast::node::ExprIf > (that.value);
        break;

      case symbol_kind::S_function: // function
        value.move< cynth::ast::node::Function > (that.value);
        break;

      case symbol_kind::S_function_def: // function_def
        value.move< cynth::ast::node::FunctionDef > (that.value);
        break;

      case symbol_kind::S_function_type: // function_type
        value.move< cynth::ast::node::FunctionType > (that.value);
        break;

      case symbol_kind::S_ge: // ge
        value.move< cynth::ast::node::Ge > (that.value);
        break;

      case symbol_kind::S_gt: // gt
        value.move< cynth::ast::node::Gt > (that.value);
        break;

      case symbol_kind::S_if: // if
        value.move< cynth::ast::node::If > (that.value);
        break;

      case symbol_kind::S_integer: // integer
        value.move< cynth::ast::node::Integer > (that.value);
        break;

      case symbol_kind::S_le: // le
        value.move< cynth::ast::node::Le > (that.value);
        break;

      case symbol_kind::S_lt: // lt
        value.move< cynth::ast::node::Lt > (that.value);
        break;

      case symbol_kind::S_minus: // minus
        value.move< cynth::ast::node::Minus > (that.value);
        break;

      case symbol_kind::S_mod: // mod
        value.move< cynth::ast::node::Mod > (that.value);
        break;

      case symbol_kind::S_mul: // mul
        value.move< cynth::ast::node::Mul > (that.value);
        break;

      case symbol_kind::S_name: // name
        value.move< cynth::ast::node::Name > (that.value);
        break;

      case symbol_kind::S_ne: // ne
        value.move< cynth::ast::node::Ne > (that.value);
        break;

      case symbol_kind::S_not: // not
        value.move< cynth::ast::node::Not > (that.value);
        break;

      case symbol_kind::S_or: // or
        value.move< cynth::ast::node::Or > (that.value);
        break;

      case symbol_kind::S_plus: // plus
        value.move< cynth::ast::node::Plus > (that.value);
        break;

      case symbol_kind::S_pow: // pow
        value.move< cynth::ast::node::Pow > (that.value);
        break;

      case symbol_kind::S_return: // return
        value.move< cynth::ast::node::Return > (that.value);
        break;

      case symbol_kind::S_single_decl: // single_decl
        value.move< cynth::ast::node::SingleDecl > (that.value);
        break;

      case symbol_kind::S_string: // string
        value.move< cynth::ast::node::String > (that.value);
        break;

      case symbol_kind::S_sub: // sub
        value.move< cynth::ast::node::Sub > (that.value);
        break;

      case symbol_kind::S_subscript: // subscript
        value.move< cynth::ast::node::Subscript > (that.value);
        break;

      case symbol_kind::S_type_decl: // type_decl
        value.move< cynth::ast::node::TypeDecl > (that.value);
        break;

      case symbol_kind::S_type_def: // type_def
        value.move< cynth::ast::node::TypeDef > (that.value);
        break;

      case symbol_kind::S_type_name: // type_name
        value.move< cynth::ast::node::TypeName > (that.value);
        break;

      case symbol_kind::S_when: // when
        value.move< cynth::ast::node::When > (that.value);
        break;

      case symbol_kind::S_start: // start
        value.move< int > (that.value);
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_DECIMAL: // DECIMAL
      case symbol_kind::S_STRING: // STRING
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< std::vector<cynth::ast::category::Declaration *> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< std::vector<cynth::ast::category::Expression  *> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<cynth::ast::category::Statement   *> > (that.value);
        break;

      case symbol_kind::S_type_list: // type_list
        value.move< std::vector<cynth::ast::category::Type        *> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_declaration: // declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        yylhs.value.emplace< cynth::ast::category::Declaration > ();
        break;

      case symbol_kind::S_expression: // expression
      case symbol_kind::S_expr_or: // expr_or
      case symbol_kind::S_expr_and: // expr_and
      case symbol_kind::S_expr_eq: // expr_eq
      case symbol_kind::S_expr_ord: // expr_ord
      case symbol_kind::S_expr_add: // expr_add
      case symbol_kind::S_expr_mul: // expr_mul
      case symbol_kind::S_expr_pow: // expr_pow
      case symbol_kind::S_expr_pre: // expr_pre
      case symbol_kind::S_expr_post: // expr_post
      case symbol_kind::S_expr_atom: // expr_atom
      case symbol_kind::S_expr_right: // expr_right
      case symbol_kind::S_paren_expr: // paren_expr
      case symbol_kind::S_void: // void
        yylhs.value.emplace< cynth::ast::category::Expression > ();
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_pure: // pure
        yylhs.value.emplace< cynth::ast::category::Statement > ();
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        yylhs.value.emplace< cynth::ast::category::Type > ();
        break;

      case symbol_kind::S_add: // add
        yylhs.value.emplace< cynth::ast::node::Add > ();
        break;

      case symbol_kind::S_and: // and
        yylhs.value.emplace< cynth::ast::node::And > ();
        break;

      case symbol_kind::S_application: // application
        yylhs.value.emplace< cynth::ast::node::Application > ();
        break;

      case symbol_kind::S_array_type: // array_type
        yylhs.value.emplace< cynth::ast::node::ArrayType > ();
        break;

      case symbol_kind::S_assignment: // assignment
        yylhs.value.emplace< cynth::ast::node::Assignment > ();
        break;

      case symbol_kind::S_auto: // auto
        yylhs.value.emplace< cynth::ast::node::Auto > ();
        break;

      case symbol_kind::S_auto_array_type: // auto_array_type
        yylhs.value.emplace< cynth::ast::node::AutoArrayType > ();
        break;

      case symbol_kind::S_block: // block
        yylhs.value.emplace< cynth::ast::node::Block > ();
        break;

      case symbol_kind::S_buffer_type: // buffer_type
        yylhs.value.emplace< cynth::ast::node::BufferType > ();
        break;

      case symbol_kind::S_conversion: // conversion
        yylhs.value.emplace< cynth::ast::node::Conversion > ();
        break;

      case symbol_kind::S_decimal: // decimal
        yylhs.value.emplace< cynth::ast::node::Decimal > ();
        break;

      case symbol_kind::S_decl_array_type: // decl_array_type
        yylhs.value.emplace< cynth::ast::node::DeclArrayType > ();
        break;

      case symbol_kind::S_definition: // definition
        yylhs.value.emplace< cynth::ast::node::Definition > ();
        break;

      case symbol_kind::S_div: // div
        yylhs.value.emplace< cynth::ast::node::Div > ();
        break;

      case symbol_kind::S_eq: // eq
        yylhs.value.emplace< cynth::ast::node::Eq > ();
        break;

      case symbol_kind::S_expr_if: // expr_if
        yylhs.value.emplace< cynth::ast::node::ExprIf > ();
        break;

      case symbol_kind::S_function: // function
        yylhs.value.emplace< cynth::ast::node::Function > ();
        break;

      case symbol_kind::S_function_def: // function_def
        yylhs.value.emplace< cynth::ast::node::FunctionDef > ();
        break;

      case symbol_kind::S_function_type: // function_type
        yylhs.value.emplace< cynth::ast::node::FunctionType > ();
        break;

      case symbol_kind::S_ge: // ge
        yylhs.value.emplace< cynth::ast::node::Ge > ();
        break;

      case symbol_kind::S_gt: // gt
        yylhs.value.emplace< cynth::ast::node::Gt > ();
        break;

      case symbol_kind::S_if: // if
        yylhs.value.emplace< cynth::ast::node::If > ();
        break;

      case symbol_kind::S_integer: // integer
        yylhs.value.emplace< cynth::ast::node::Integer > ();
        break;

      case symbol_kind::S_le: // le
        yylhs.value.emplace< cynth::ast::node::Le > ();
        break;

      case symbol_kind::S_lt: // lt
        yylhs.value.emplace< cynth::ast::node::Lt > ();
        break;

      case symbol_kind::S_minus: // minus
        yylhs.value.emplace< cynth::ast::node::Minus > ();
        break;

      case symbol_kind::S_mod: // mod
        yylhs.value.emplace< cynth::ast::node::Mod > ();
        break;

      case symbol_kind::S_mul: // mul
        yylhs.value.emplace< cynth::ast::node::Mul > ();
        break;

      case symbol_kind::S_name: // name
        yylhs.value.emplace< cynth::ast::node::Name > ();
        break;

      case symbol_kind::S_ne: // ne
        yylhs.value.emplace< cynth::ast::node::Ne > ();
        break;

      case symbol_kind::S_not: // not
        yylhs.value.emplace< cynth::ast::node::Not > ();
        break;

      case symbol_kind::S_or: // or
        yylhs.value.emplace< cynth::ast::node::Or > ();
        break;

      case symbol_kind::S_plus: // plus
        yylhs.value.emplace< cynth::ast::node::Plus > ();
        break;

      case symbol_kind::S_pow: // pow
        yylhs.value.emplace< cynth::ast::node::Pow > ();
        break;

      case symbol_kind::S_return: // return
        yylhs.value.emplace< cynth::ast::node::Return > ();
        break;

      case symbol_kind::S_single_decl: // single_decl
        yylhs.value.emplace< cynth::ast::node::SingleDecl > ();
        break;

      case symbol_kind::S_string: // string
        yylhs.value.emplace< cynth::ast::node::String > ();
        break;

      case symbol_kind::S_sub: // sub
        yylhs.value.emplace< cynth::ast::node::Sub > ();
        break;

      case symbol_kind::S_subscript: // subscript
        yylhs.value.emplace< cynth::ast::node::Subscript > ();
        break;

      case symbol_kind::S_type_decl: // type_decl
        yylhs.value.emplace< cynth::ast::node::TypeDecl > ();
        break;

      case symbol_kind::S_type_def: // type_def
        yylhs.value.emplace< cynth::ast::node::TypeDef > ();
        break;

      case symbol_kind::S_type_name: // type_name
        yylhs.value.emplace< cynth::ast::node::TypeName > ();
        break;

      case symbol_kind::S_when: // when
        yylhs.value.emplace< cynth::ast::node::When > ();
        break;

      case symbol_kind::S_start: // start
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_DECIMAL: // DECIMAL
      case symbol_kind::S_STRING: // STRING
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_decl_list: // decl_list
        yylhs.value.emplace< std::vector<cynth::ast::category::Declaration *> > ();
        break;

      case symbol_kind::S_expr_list: // expr_list
        yylhs.value.emplace< std::vector<cynth::ast::category::Expression  *> > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        yylhs.value.emplace< std::vector<cynth::ast::category::Statement   *> > ();
        break;

      case symbol_kind::S_type_list: // type_list
        yylhs.value.emplace< std::vector<cynth::ast::category::Type        *> > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // start: %empty
#line 165 "gen/parser.y"
                          { result = {{}};    }
#line 1669 "src/parser.cpp"
    break;

  case 3: // start: stmt_list
#line 166 "gen/parser.y"
                          { result = {YY_MOVE (yystack_[0].value.as < std::vector<cynth::ast::category::Statement   *> > ())}; }
#line 1675 "src/parser.cpp"
    break;

  case 4: // start: stmt_list SEMI
#line 167 "gen/parser.y"
                          { result = {YY_MOVE (yystack_[1].value.as < std::vector<cynth::ast::category::Statement   *> > ())}; }
#line 1681 "src/parser.cpp"
    break;

  case 5: // statement: pure
#line 170 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ()); }
#line 1687 "src/parser.cpp"
    break;

  case 6: // statement: expression
#line 171 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1693 "src/parser.cpp"
    break;

  case 7: // pure: declaration
#line 174 "gen/parser.y"
                 { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Declaration > ()); }
#line 1699 "src/parser.cpp"
    break;

  case 8: // pure: definition
#line 175 "gen/parser.y"
                 { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Definition > ()); }
#line 1705 "src/parser.cpp"
    break;

  case 9: // pure: assignment
#line 176 "gen/parser.y"
                 { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Assignment > ()); }
#line 1711 "src/parser.cpp"
    break;

  case 10: // pure: type_def
#line 177 "gen/parser.y"
                 { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeDef > ()); }
#line 1717 "src/parser.cpp"
    break;

  case 11: // pure: function_def
#line 178 "gen/parser.y"
                 { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::FunctionDef > ()); }
#line 1723 "src/parser.cpp"
    break;

  case 12: // pure: return
#line 179 "gen/parser.y"
                 { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Return > ()); }
#line 1729 "src/parser.cpp"
    break;

  case 13: // pure: if
#line 180 "gen/parser.y"
                 { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::If > ()); }
#line 1735 "src/parser.cpp"
    break;

  case 14: // pure: when
#line 181 "gen/parser.y"
                 { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::When > ()); }
#line 1741 "src/parser.cpp"
    break;

  case 15: // expression: expr_or
#line 184 "gen/parser.y"
    { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1747 "src/parser.cpp"
    break;

  case 16: // expression: expr_right
#line 185 "gen/parser.y"
    { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1753 "src/parser.cpp"
    break;

  case 17: // expr_or: or
#line 188 "gen/parser.y"
       { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Or > ()); }
#line 1759 "src/parser.cpp"
    break;

  case 18: // expr_or: expr_and
#line 189 "gen/parser.y"
    { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1765 "src/parser.cpp"
    break;

  case 19: // expr_and: and
#line 192 "gen/parser.y"
        { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::And > ()); }
#line 1771 "src/parser.cpp"
    break;

  case 20: // expr_and: expr_eq
#line 193 "gen/parser.y"
    { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1777 "src/parser.cpp"
    break;

  case 21: // expr_eq: eq
#line 196 "gen/parser.y"
       { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Eq > ()); }
#line 1783 "src/parser.cpp"
    break;

  case 22: // expr_eq: ne
#line 197 "gen/parser.y"
       { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Ne > ()); }
#line 1789 "src/parser.cpp"
    break;

  case 23: // expr_eq: expr_ord
#line 198 "gen/parser.y"
    { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1795 "src/parser.cpp"
    break;

  case 24: // expr_ord: ge
#line 201 "gen/parser.y"
       { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Ge > ()); }
#line 1801 "src/parser.cpp"
    break;

  case 25: // expr_ord: le
#line 202 "gen/parser.y"
       { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Le > ()); }
#line 1807 "src/parser.cpp"
    break;

  case 26: // expr_ord: gt
#line 203 "gen/parser.y"
       { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Gt > ()); }
#line 1813 "src/parser.cpp"
    break;

  case 27: // expr_ord: lt
#line 204 "gen/parser.y"
       { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Lt > ()); }
#line 1819 "src/parser.cpp"
    break;

  case 28: // expr_ord: expr_add
#line 205 "gen/parser.y"
    { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1825 "src/parser.cpp"
    break;

  case 29: // expr_add: add
#line 208 "gen/parser.y"
        { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Add > ()); }
#line 1831 "src/parser.cpp"
    break;

  case 30: // expr_add: sub
#line 209 "gen/parser.y"
        { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Sub > ()); }
#line 1837 "src/parser.cpp"
    break;

  case 31: // expr_add: expr_mul
#line 210 "gen/parser.y"
    { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1843 "src/parser.cpp"
    break;

  case 32: // expr_mul: mul
#line 213 "gen/parser.y"
        { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Mul > ()); }
#line 1849 "src/parser.cpp"
    break;

  case 33: // expr_mul: div
#line 214 "gen/parser.y"
        { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Div > ()); }
#line 1855 "src/parser.cpp"
    break;

  case 34: // expr_mul: mod
#line 215 "gen/parser.y"
        { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Mod > ()); }
#line 1861 "src/parser.cpp"
    break;

  case 35: // expr_mul: expr_pow
#line 216 "gen/parser.y"
    { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1867 "src/parser.cpp"
    break;

  case 36: // expr_pow: pow
#line 219 "gen/parser.y"
        { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Pow > ()); }
#line 1873 "src/parser.cpp"
    break;

  case 37: // expr_pow: expr_pre
#line 220 "gen/parser.y"
    { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1879 "src/parser.cpp"
    break;

  case 38: // expr_pre: minus
#line 223 "gen/parser.y"
          { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Minus > ()); }
#line 1885 "src/parser.cpp"
    break;

  case 39: // expr_pre: plus
#line 224 "gen/parser.y"
          { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Plus > ()); }
#line 1891 "src/parser.cpp"
    break;

  case 40: // expr_pre: not
#line 225 "gen/parser.y"
          { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Not > ()); }
#line 1897 "src/parser.cpp"
    break;

  case 41: // expr_pre: expr_post
#line 226 "gen/parser.y"
    { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1903 "src/parser.cpp"
    break;

  case 42: // expr_post: application
#line 229 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Application > ()); }
#line 1909 "src/parser.cpp"
    break;

  case 43: // expr_post: conversion
#line 230 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Conversion > ()); }
#line 1915 "src/parser.cpp"
    break;

  case 44: // expr_post: subscript
#line 231 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Subscript > ()); }
#line 1921 "src/parser.cpp"
    break;

  case 45: // expr_post: expr_atom
#line 232 "gen/parser.y"
    { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1927 "src/parser.cpp"
    break;

  case 46: // expr_atom: name
#line 235 "gen/parser.y"
            { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Name > ()); }
#line 1933 "src/parser.cpp"
    break;

  case 47: // expr_atom: integer
#line 236 "gen/parser.y"
            { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Integer > ()); }
#line 1939 "src/parser.cpp"
    break;

  case 48: // expr_atom: decimal
#line 237 "gen/parser.y"
            { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Decimal > ()); }
#line 1945 "src/parser.cpp"
    break;

  case 49: // expr_atom: string
#line 238 "gen/parser.y"
            { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::String > ()); }
#line 1951 "src/parser.cpp"
    break;

  case 50: // expr_atom: block
#line 239 "gen/parser.y"
            { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Block > ()); }
#line 1957 "src/parser.cpp"
    break;

  case 51: // expr_atom: paren_expr
#line 241 "gen/parser.y"
    { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1963 "src/parser.cpp"
    break;

  case 52: // expr_right: expr_if
#line 244 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::ExprIf > ()); }
#line 1969 "src/parser.cpp"
    break;

  case 53: // expr_right: function
#line 245 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Function > ()); }
#line 1975 "src/parser.cpp"
    break;

  case 54: // or: expr_mul OR expr_pow
#line 247 "gen/parser.y"
                                     { yylhs.value.as < cynth::ast::node::Or > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 1981 "src/parser.cpp"
    break;

  case 55: // and: expr_mul AND expr_pow
#line 248 "gen/parser.y"
                                     { yylhs.value.as < cynth::ast::node::And > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 1987 "src/parser.cpp"
    break;

  case 56: // eq: expr_mul EQ expr_pow
#line 249 "gen/parser.y"
                                     { yylhs.value.as < cynth::ast::node::Eq > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 1993 "src/parser.cpp"
    break;

  case 57: // ne: expr_mul NE expr_pow
#line 250 "gen/parser.y"
                                     { yylhs.value.as < cynth::ast::node::Ne > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 1999 "src/parser.cpp"
    break;

  case 58: // ge: expr_mul GE expr_pow
#line 251 "gen/parser.y"
                                     { yylhs.value.as < cynth::ast::node::Ge > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2005 "src/parser.cpp"
    break;

  case 59: // le: expr_mul LE expr_pow
#line 252 "gen/parser.y"
                                     { yylhs.value.as < cynth::ast::node::Le > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2011 "src/parser.cpp"
    break;

  case 60: // gt: expr_mul GT expr_pow
#line 253 "gen/parser.y"
                                     { yylhs.value.as < cynth::ast::node::Gt > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2017 "src/parser.cpp"
    break;

  case 61: // lt: expr_mul LT expr_pow
#line 254 "gen/parser.y"
                                     { yylhs.value.as < cynth::ast::node::Lt > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2023 "src/parser.cpp"
    break;

  case 62: // add: expr_mul ADD expr_pow
#line 255 "gen/parser.y"
                                     { yylhs.value.as < cynth::ast::node::Add > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2029 "src/parser.cpp"
    break;

  case 63: // sub: expr_mul SUB expr_pow
#line 256 "gen/parser.y"
                                     { yylhs.value.as < cynth::ast::node::Sub > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2035 "src/parser.cpp"
    break;

  case 64: // mul: expr_mul MUL expr_pow
#line 257 "gen/parser.y"
                                     { yylhs.value.as < cynth::ast::node::Mul > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2041 "src/parser.cpp"
    break;

  case 65: // div: expr_mul DIV expr_pow
#line 258 "gen/parser.y"
                                     { yylhs.value.as < cynth::ast::node::Div > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2047 "src/parser.cpp"
    break;

  case 66: // mod: expr_mul MOD expr_pow
#line 259 "gen/parser.y"
                                     { yylhs.value.as < cynth::ast::node::Mod > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2053 "src/parser.cpp"
    break;

  case 67: // pow: expr_pre POW expr_pow
#line 261 "gen/parser.y"
                                     { yylhs.value.as < cynth::ast::node::Pow > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2059 "src/parser.cpp"
    break;

  case 68: // minus: SUB expr_pre
#line 263 "gen/parser.y"
                         { yylhs.value.as < cynth::ast::node::Minus > () = {cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2065 "src/parser.cpp"
    break;

  case 69: // plus: ADD expr_pre
#line 264 "gen/parser.y"
                         { yylhs.value.as < cynth::ast::node::Plus > () = {cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2071 "src/parser.cpp"
    break;

  case 70: // not: NOT expr_pre
#line 265 "gen/parser.y"
                         { yylhs.value.as < cynth::ast::node::Not > () = {cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2077 "src/parser.cpp"
    break;

  case 71: // application: expr_post paren_expr
#line 267 "gen/parser.y"
                                                          { yylhs.value.as < cynth::ast::node::Application > () = {cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2083 "src/parser.cpp"
    break;

  case 72: // application: expr_post void
#line 268 "gen/parser.y"
                                                          { yylhs.value.as < cynth::ast::node::Application > () = {cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2089 "src/parser.cpp"
    break;

  case 73: // conversion: type paren_expr
#line 269 "gen/parser.y"
                                                          { yylhs.value.as < cynth::ast::node::Conversion > () = {cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2095 "src/parser.cpp"
    break;

  case 74: // subscript: expr_post OBRACK expression CBRACK
#line 270 "gen/parser.y"
                                                          { yylhs.value.as < cynth::ast::node::Subscript > () = {cynth::util::alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ()))}; }
#line 2101 "src/parser.cpp"
    break;

  case 75: // type: auto
#line 273 "gen/parser.y"
                    { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Auto > ()); }
#line 2107 "src/parser.cpp"
    break;

  case 76: // type: type_name
#line 274 "gen/parser.y"
                    { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeName > ()); }
#line 2113 "src/parser.cpp"
    break;

  case 77: // type: function_type
#line 275 "gen/parser.y"
                    { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::FunctionType > ()); }
#line 2119 "src/parser.cpp"
    break;

  case 78: // type: array_type
#line 276 "gen/parser.y"
                    { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::ArrayType > ()); }
#line 2125 "src/parser.cpp"
    break;

  case 79: // type: buffer_type
#line 277 "gen/parser.y"
                    { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::BufferType > ()); }
#line 2131 "src/parser.cpp"
    break;

  case 80: // type: decl_array_type
#line 278 "gen/parser.y"
                    { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::DeclArrayType > ()); }
#line 2137 "src/parser.cpp"
    break;

  case 81: // type: auto_array_type
#line 279 "gen/parser.y"
                    { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::AutoArrayType > ()); }
#line 2143 "src/parser.cpp"
    break;

  case 82: // type: type_decl
#line 280 "gen/parser.y"
                    { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeDecl > ()); }
#line 2149 "src/parser.cpp"
    break;

  case 83: // type: paren_type
#line 281 "gen/parser.y"
                    { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()); }
#line 2155 "src/parser.cpp"
    break;

  case 84: // function_type: type paren_type
#line 284 "gen/parser.y"
                                  { yylhs.value.as < cynth::ast::node::FunctionType > () = {cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()))}; }
#line 2161 "src/parser.cpp"
    break;

  case 85: // function_type: void_type paren_type
#line 285 "gen/parser.y"
                                  { yylhs.value.as < cynth::ast::node::FunctionType > () = {cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()))}; }
#line 2167 "src/parser.cpp"
    break;

  case 86: // function_type: type void_type
#line 286 "gen/parser.y"
                                       { yylhs.value.as < cynth::ast::node::FunctionType > () = {cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()))}; }
#line 2173 "src/parser.cpp"
    break;

  case 87: // function_type: void_type void_type
#line 287 "gen/parser.y"
                                       { yylhs.value.as < cynth::ast::node::FunctionType > () = {cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()))}; }
#line 2179 "src/parser.cpp"
    break;

  case 88: // array_type: type OBRACK expression CBRACK
#line 290 "gen/parser.y"
                                          { yylhs.value.as < cynth::ast::node::ArrayType > () = {cynth::util::alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ()))}; }
#line 2185 "src/parser.cpp"
    break;

  case 89: // buffer_type: BUFFER OBRACK expression CBRACK
#line 292 "gen/parser.y"
                                          { yylhs.value.as < cynth::ast::node::BufferType > () = {cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ()))}; }
#line 2191 "src/parser.cpp"
    break;

  case 90: // auto_array_type: type OBRACK AUTO CBRACK
#line 294 "gen/parser.y"
                                      { yylhs.value.as < cynth::ast::node::AutoArrayType > () = {cynth::util::alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()))}; }
#line 2197 "src/parser.cpp"
    break;

  case 91: // auto_array_type: type OBRACK CBRACK
#line 295 "gen/parser.y"
                                      { yylhs.value.as < cynth::ast::node::AutoArrayType > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Type > ()))}; }
#line 2203 "src/parser.cpp"
    break;

  case 92: // decl_array_type: type OBRACK declaration CBRACK
#line 297 "gen/parser.y"
                                                        { yylhs.value.as < cynth::ast::node::DeclArrayType > () = {cynth::util::alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()))}; }
#line 2209 "src/parser.cpp"
    break;

  case 93: // declaration: single_decl
#line 300 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Declaration > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::SingleDecl > ()); }
#line 2215 "src/parser.cpp"
    break;

  case 94: // declaration: paren_decl
#line 301 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Declaration > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Declaration > ()); }
#line 2221 "src/parser.cpp"
    break;

  case 95: // single_decl: type name
#line 303 "gen/parser.y"
                            { yylhs.value.as < cynth::ast::node::SingleDecl > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::node::Name > ()), cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()))}; }
#line 2227 "src/parser.cpp"
    break;

  case 96: // type_decl: TYPE type_name
#line 304 "gen/parser.y"
                            { yylhs.value.as < cynth::ast::node::TypeDecl > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeName > ())};                       }
#line 2233 "src/parser.cpp"
    break;

  case 97: // definition: declaration ASSGN expression
#line 306 "gen/parser.y"
                                                         { yylhs.value.as < cynth::ast::node::Definition > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Declaration > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2239 "src/parser.cpp"
    break;

  case 98: // assignment: name ASSGN expression
#line 307 "gen/parser.y"
                                                         { yylhs.value.as < cynth::ast::node::Assignment > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()),                     cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2245 "src/parser.cpp"
    break;

  case 99: // type_def: TYPE type_name ASSGN type
#line 308 "gen/parser.y"
                                                         { yylhs.value.as < cynth::ast::node::TypeDef > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::node::TypeName > ()),                     cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()))}; }
#line 2251 "src/parser.cpp"
    break;

  case 100: // return: RETURN expression
#line 311 "gen/parser.y"
                           { yylhs.value.as < cynth::ast::node::Return > () = {cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2257 "src/parser.cpp"
    break;

  case 101: // return: RETURN void
#line 312 "gen/parser.y"
                           { yylhs.value.as < cynth::ast::node::Return > () = {cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2263 "src/parser.cpp"
    break;

  case 102: // return: RETURN
#line 313 "gen/parser.y"
                           { yylhs.value.as < cynth::ast::node::Return > () = {cynth::util::alloc(cynth::ast::category::Expression{cynth::ast::node::Tuple{}})}; }
#line 2269 "src/parser.cpp"
    break;

  case 103: // if: IF paren_expr pure ELSE pure
#line 315 "gen/parser.y"
                                                                    { yylhs.value.as < cynth::ast::node::If > () = {cynth::util::alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Statement > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ()))}; }
#line 2275 "src/parser.cpp"
    break;

  case 104: // expr_if: IF paren_expr expression ELSE expression
#line 316 "gen/parser.y"
                                                                    { yylhs.value.as < cynth::ast::node::ExprIf > () = {cynth::util::alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2281 "src/parser.cpp"
    break;

  case 105: // when: WHEN paren_expr statement
#line 317 "gen/parser.y"
                                                                    { yylhs.value.as < cynth::ast::node::When > () = {cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ()))}; }
#line 2287 "src/parser.cpp"
    break;

  case 106: // function_def: type name paren_decl expression
#line 320 "gen/parser.y"
                                                        { yylhs.value.as < cynth::ast::node::FunctionDef > () = {cynth::util::alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ())), YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2293 "src/parser.cpp"
    break;

  case 107: // function_def: void_type name paren_decl expression
#line 321 "gen/parser.y"
                                                        { yylhs.value.as < cynth::ast::node::FunctionDef > () = {cynth::util::alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ())), YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2299 "src/parser.cpp"
    break;

  case 108: // function_def: type name void_decl expression
#line 322 "gen/parser.y"
                                                        { yylhs.value.as < cynth::ast::node::FunctionDef > () = {cynth::util::alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ())), YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2305 "src/parser.cpp"
    break;

  case 109: // function_def: void_type name void_decl expression
#line 323 "gen/parser.y"
                                                        { yylhs.value.as < cynth::ast::node::FunctionDef > () = {cynth::util::alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ())), YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2311 "src/parser.cpp"
    break;

  case 110: // function: type FN paren_decl expression
#line 326 "gen/parser.y"
                                                      { yylhs.value.as < cynth::ast::node::Function > () = {cynth::util::alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2317 "src/parser.cpp"
    break;

  case 111: // function: void_type FN paren_decl expression
#line 327 "gen/parser.y"
                                                      { yylhs.value.as < cynth::ast::node::Function > () = {cynth::util::alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2323 "src/parser.cpp"
    break;

  case 112: // function: type FN void_decl expression
#line 328 "gen/parser.y"
                                                      { yylhs.value.as < cynth::ast::node::Function > () = {cynth::util::alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2329 "src/parser.cpp"
    break;

  case 113: // function: void_type FN void_decl expression
#line 329 "gen/parser.y"
                                                      { yylhs.value.as < cynth::ast::node::Function > () = {cynth::util::alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))}; }
#line 2335 "src/parser.cpp"
    break;

  case 114: // auto: AUTO
#line 331 "gen/parser.y"
                    { yylhs.value.as < cynth::ast::node::Auto > () = {};   }
#line 2341 "src/parser.cpp"
    break;

  case 115: // type_name: TYPENAME
#line 332 "gen/parser.y"
                    { yylhs.value.as < cynth::ast::node::TypeName > () = {YY_MOVE (yystack_[0].value.as < std::string > ())}; }
#line 2347 "src/parser.cpp"
    break;

  case 116: // name: NAME
#line 333 "gen/parser.y"
                    { yylhs.value.as < cynth::ast::node::Name > () = {YY_MOVE (yystack_[0].value.as < std::string > ())}; }
#line 2353 "src/parser.cpp"
    break;

  case 117: // integer: INTEGER
#line 334 "gen/parser.y"
                    { yylhs.value.as < cynth::ast::node::Integer > () = {cynth::util::stoi(YY_MOVE (yystack_[0].value.as < std::string > ()))}; }
#line 2359 "src/parser.cpp"
    break;

  case 118: // decimal: DECIMAL
#line 335 "gen/parser.y"
                    { yylhs.value.as < cynth::ast::node::Decimal > () = {std::stof(YY_MOVE (yystack_[0].value.as < std::string > ()))};         }
#line 2365 "src/parser.cpp"
    break;

  case 119: // string: STRING
#line 336 "gen/parser.y"
                    { yylhs.value.as < cynth::ast::node::String > () = {cynth::util::trim(YY_MOVE (yystack_[0].value.as < std::string > ()))}; }
#line 2371 "src/parser.cpp"
    break;

  case 120: // void: OPAREN CPAREN
#line 338 "gen/parser.y"
                         { yylhs.value.as < cynth::ast::category::Expression > () = cynth::ast::node::Tuple{};     }
#line 2377 "src/parser.cpp"
    break;

  case 121: // void_type: OPAREN CPAREN
#line 339 "gen/parser.y"
                         { yylhs.value.as < cynth::ast::category::Type > () = cynth::ast::node::TupleType{}; }
#line 2383 "src/parser.cpp"
    break;

  case 122: // void_decl: OPAREN CPAREN
#line 340 "gen/parser.y"
                         { yylhs.value.as < cynth::ast::category::Declaration > () = cynth::ast::node::TupleDecl{}; }
#line 2389 "src/parser.cpp"
    break;

  case 123: // block: OBRACE CBRACE
#line 365 "gen/parser.y"
                                       { yylhs.value.as < cynth::ast::node::Block > () = {{}};    }
#line 2395 "src/parser.cpp"
    break;

  case 124: // block: OBRACE stmt_list CBRACE
#line 366 "gen/parser.y"
                                       { yylhs.value.as < cynth::ast::node::Block > () = {YY_MOVE (yystack_[1].value.as < std::vector<cynth::ast::category::Statement   *> > ())}; }
#line 2401 "src/parser.cpp"
    break;

  case 125: // block: OBRACE stmt_list SEMI CBRACE
#line 367 "gen/parser.y"
                                       { yylhs.value.as < cynth::ast::node::Block > () = {YY_MOVE (yystack_[2].value.as < std::vector<cynth::ast::category::Statement   *> > ())}; }
#line 2407 "src/parser.cpp"
    break;

  case 126: // stmt_list: statement
#line 369 "gen/parser.y"
                     {
        yylhs.value.as < std::vector<cynth::ast::category::Statement   *> > () = {cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ()))};
    }
#line 2415 "src/parser.cpp"
    break;

  case 127: // stmt_list: stmt_list SEMI statement
#line 372 "gen/parser.y"
                                         {
        yylhs.value.as < std::vector<cynth::ast::category::Statement   *> > () = cynth::util::push(cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ())), YY_MOVE (yystack_[2].value.as < std::vector<cynth::ast::category::Statement   *> > ()));
    }
#line 2423 "src/parser.cpp"
    break;

  case 128: // paren_type: OPAREN type CPAREN
#line 377 "gen/parser.y"
                                        { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()); }
#line 2429 "src/parser.cpp"
    break;

  case 129: // paren_type: OPAREN type_list CPAREN
#line 378 "gen/parser.y"
                                        { yylhs.value.as < cynth::ast::category::Type > () = cynth::ast::node::TupleType{YY_MOVE (yystack_[1].value.as < std::vector<cynth::ast::category::Type        *> > ())}; }
#line 2435 "src/parser.cpp"
    break;

  case 130: // paren_type: OPAREN type_list COMMA CPAREN
#line 379 "gen/parser.y"
                                        { yylhs.value.as < cynth::ast::category::Type > () = cynth::ast::node::TupleType{YY_MOVE (yystack_[2].value.as < std::vector<cynth::ast::category::Type        *> > ())}; }
#line 2441 "src/parser.cpp"
    break;

  case 131: // type_list: type COMMA type
#line 381 "gen/parser.y"
                                   {
        yylhs.value.as < std::vector<cynth::ast::category::Type        *> > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Type > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()))};
    }
#line 2449 "src/parser.cpp"
    break;

  case 132: // type_list: type_list COMMA type
#line 384 "gen/parser.y"
                                     {
        yylhs.value.as < std::vector<cynth::ast::category::Type        *> > () = cynth::util::push(cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())), YY_MOVE (yystack_[2].value.as < std::vector<cynth::ast::category::Type        *> > ()));
    }
#line 2457 "src/parser.cpp"
    break;

  case 133: // paren_expr: OPAREN expression CPAREN
#line 389 "gen/parser.y"
                                        { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ()); }
#line 2463 "src/parser.cpp"
    break;

  case 134: // paren_expr: OPAREN expr_list CPAREN
#line 390 "gen/parser.y"
                                        { yylhs.value.as < cynth::ast::category::Expression > () = cynth::ast::node::Tuple{YY_MOVE (yystack_[1].value.as < std::vector<cynth::ast::category::Expression  *> > ())}; }
#line 2469 "src/parser.cpp"
    break;

  case 135: // paren_expr: OPAREN expr_list COMMA CPAREN
#line 391 "gen/parser.y"
                                        { yylhs.value.as < cynth::ast::category::Expression > () = cynth::ast::node::Tuple{YY_MOVE (yystack_[2].value.as < std::vector<cynth::ast::category::Expression  *> > ())}; }
#line 2475 "src/parser.cpp"
    break;

  case 136: // expr_list: expression COMMA expression
#line 393 "gen/parser.y"
                                               {
        yylhs.value.as < std::vector<cynth::ast::category::Expression  *> > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()))};
    }
#line 2483 "src/parser.cpp"
    break;

  case 137: // expr_list: expr_list COMMA expression
#line 396 "gen/parser.y"
                                           {
        yylhs.value.as < std::vector<cynth::ast::category::Expression  *> > () = cynth::util::push(cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())), YY_MOVE (yystack_[2].value.as < std::vector<cynth::ast::category::Expression  *> > ()));
    }
#line 2491 "src/parser.cpp"
    break;

  case 138: // paren_decl: OPAREN declaration CPAREN
#line 401 "gen/parser.y"
                                        { yylhs.value.as < cynth::ast::category::Declaration > () = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()); }
#line 2497 "src/parser.cpp"
    break;

  case 139: // paren_decl: OPAREN decl_list CPAREN
#line 402 "gen/parser.y"
                                        { yylhs.value.as < cynth::ast::category::Declaration > () = cynth::ast::node::TupleDecl{YY_MOVE (yystack_[1].value.as < std::vector<cynth::ast::category::Declaration *> > ())}; }
#line 2503 "src/parser.cpp"
    break;

  case 140: // paren_decl: OPAREN decl_list COMMA CPAREN
#line 403 "gen/parser.y"
                                        { yylhs.value.as < cynth::ast::category::Declaration > () = cynth::ast::node::TupleDecl{YY_MOVE (yystack_[2].value.as < std::vector<cynth::ast::category::Declaration *> > ())}; }
#line 2509 "src/parser.cpp"
    break;

  case 141: // decl_list: declaration COMMA declaration
#line 405 "gen/parser.y"
                                                 {
        yylhs.value.as < std::vector<cynth::ast::category::Declaration *> > () = {cynth::util::alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Declaration > ())), cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Declaration > ()))};
    }
#line 2517 "src/parser.cpp"
    break;

  case 142: // decl_list: decl_list COMMA declaration
#line 408 "gen/parser.y"
                                            {
        yylhs.value.as < std::vector<cynth::ast::category::Declaration *> > () = cynth::util::push(cynth::util::alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Declaration > ())), YY_MOVE (yystack_[2].value.as < std::vector<cynth::ast::category::Declaration *> > ()));
    }
#line 2525 "src/parser.cpp"
    break;


#line 2529 "src/parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0





  const signed char parser::yypact_ninf_ = -106;

  const signed char parser::yytable_ninf_ = -122;

  const short
  parser::yypact_[] =
  {
     524,  -106,  -106,  -106,  -106,  -106,   -12,   -12,    11,    -3,
    -106,   684,   347,   460,   748,   748,   748,    42,    66,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,   755,  -106,    24,
      65,  -106,  -106,    64,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,    80,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
      94,   107,   716,   524,   524,    99,   716,   -12,    11,   556,
      -5,  -106,  -106,  -106,    25,  -106,    49,   -14,    -1,    36,
      53,    98,  -106,    23,   588,    91,  -106,   102,  -106,  -106,
    -106,   105,    22,   105,  -106,  -106,  -106,   748,   748,   748,
     748,   748,   748,   748,   748,   748,   748,   748,   748,   748,
     748,   620,   716,  -106,  -106,   716,   716,   105,   207,   105,
    -106,  -106,   524,   121,   124,  -106,    97,   110,   716,  -106,
      43,   202,    97,  -106,  -106,   716,  -106,   149,  -106,   652,
    -106,   234,  -106,   334,  -106,   492,  -106,   420,   716,   716,
     111,  -106,    66,   116,   118,   716,   716,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,   125,  -106,  -106,   716,   716,    76,   716,   716,
    -106,   136,   716,   100,  -106,   100,  -106,   543,    38,  -106,
    -106,  -106,  -106,  -106,  -106,   100,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
     -12,    38,  -106,    80,     2,  -106,    51,   136
  };

  const unsigned char
  parser::yydefact_[] =
  {
       2,   116,   115,   117,   118,   119,     0,     0,     0,     0,
     114,   102,     0,     0,     0,     0,     0,     0,     0,   126,
       5,     6,    15,    18,    20,    23,    28,    31,    35,    37,
      41,    45,    16,     7,    17,    19,    21,    22,    24,    25,
      26,    27,    29,    30,    32,    33,    34,    36,    39,    38,
      40,    42,    43,    44,    75,    77,    78,    80,    81,    79,
      82,    93,     8,     9,    10,    12,    13,    14,    11,    52,
      53,    46,    76,    47,    48,    49,    50,    51,    94,    83,
       0,     3,     0,     0,     0,    96,     0,     0,     0,     0,
       0,   100,    46,   101,     0,   121,     0,     0,     0,     0,
       0,     0,   123,     0,     0,     0,    69,     0,    68,    70,
       1,     0,     0,    95,    73,    84,    86,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    71,    72,     0,     0,     0,     0,     0,
      85,    87,     4,     0,     0,   105,     0,     0,     0,    96,
     120,     0,     0,   128,    95,     0,   133,     0,   138,     0,
     134,     0,   139,     0,   129,     0,   124,     0,     0,     0,
     114,    91,     0,     0,     0,     0,     0,    62,    63,    64,
      65,    66,    55,    54,    56,    57,    58,    59,    60,    61,
      67,   120,     0,    97,    98,     0,     0,     0,     0,     0,
     127,     0,     0,    99,    89,   131,   136,     0,     0,   141,
     135,   137,   140,   142,   130,   132,   125,   122,   110,   112,
      90,    88,    92,   106,   108,    74,   111,   113,   107,   109,
       0,     0,   103,     0,     0,   104,     0,     0
  };

  const short
  parser::yypgoto_[] =
  {
    -106,  -106,   166,   -80,   -81,   260,  -106,  -106,  -106,  -106,
    -106,  -106,   681,   174,  -106,  -106,  -106,    55,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,    45,    -7,  -106,  -106,  -106,
    -106,    13,  -105,   217,   104,     0,   -99,  -106,   141,  -106,
    -106
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,    17,    90,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    92,    72,    73,    74,    75,
      76,    77,    78,    79,    93,   107,   169,    99,    81,   100,
     101
  };

  const short
  parser::yytable_[] =
  {
      80,    85,   143,   155,   145,     1,   168,   111,   175,   156,
      82,    94,    94,    80,   176,     2,   157,   104,   116,    83,
      84,   112,   158,    86,   138,     1,     2,     3,     4,     5,
      87,   114,   195,    88,   198,     9,   170,   137,   196,   165,
     199,     1,   110,   133,    12,    71,    13,   138,   166,   171,
      14,    15,     1,   159,     1,  -121,    16,   130,    71,   160,
     138,   111,   200,   113,   112,  -121,   152,    98,   152,     1,
     161,   104,   153,   138,   153,   112,   162,   112,   111,   135,
     141,   149,    94,    80,    80,   200,    94,   131,   104,    94,
     116,   132,   112,   152,   141,   136,   116,     1,   138,   153,
     148,     2,   112,   114,    94,   116,   137,   141,    88,   114,
       9,    10,    94,   104,   146,   163,   138,   112,   114,   138,
     232,   164,   138,   142,   138,   139,   112,   167,    71,    71,
     201,    94,    94,   202,   134,    94,    94,   204,   220,     1,
       2,   154,    80,   221,   230,   222,     7,     8,    94,     9,
      10,   116,   225,     2,   103,    94,   143,    11,   207,    94,
      88,     0,     9,    10,   114,    80,    18,   174,    94,    94,
       0,   207,   116,     0,     0,    94,    94,     0,    96,    18,
     105,   105,   105,     0,     0,   114,     0,    71,   106,   108,
     109,     0,     0,     0,     0,    94,    94,   116,    94,    94,
       0,   234,    94,   116,     0,   116,     0,     0,   116,     0,
      71,     2,   209,     0,   111,   116,   213,   154,    88,   152,
       9,    10,    98,     0,   104,   153,     0,     0,   112,   138,
      95,   116,     0,     0,   141,   115,   116,   234,     2,     0,
       0,     0,     0,   237,     0,    88,   233,     9,    10,    18,
      18,     0,     0,   154,     0,   151,   207,   212,     0,     0,
       0,     0,    98,     0,     0,     0,     0,     0,     0,     0,
     151,    91,    97,     0,     0,     0,   113,     0,   172,   139,
       0,   154,   233,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   140,     0,     0,
       0,     0,     0,     0,   197,     0,     0,   115,    18,     0,
       0,   140,   203,   115,     0,     0,     0,     0,   205,     0,
       0,     0,   115,   208,   140,     0,     0,   208,     0,   215,
       0,    18,     0,   208,     0,     0,     0,     0,     2,     0,
       0,     0,    97,   144,     0,    88,   147,     9,    10,    97,
       1,     2,     3,     4,     5,    87,   138,   214,    88,     0,
       9,    10,     0,     0,    97,     0,     0,   231,   115,    12,
      95,    13,   173,   236,     0,    14,    15,     0,     0,     0,
       0,    16,     0,     0,     0,     0,     0,     0,     0,   115,
       0,    97,   192,     0,     0,   193,   194,     0,     0,     0,
       0,     0,     0,   231,     0,     0,     0,     0,   144,     0,
       0,     0,     0,     0,   115,   206,     0,     0,     0,   211,
     115,     0,   115,     0,     2,   115,     0,     0,   218,   219,
       0,    88,   115,     9,    10,   223,   224,     0,     0,     0,
       0,     0,   207,   217,     0,     0,     0,     0,   115,     0,
       0,   140,     0,   115,     0,   226,   227,     0,   228,   229,
       0,     0,   235,     1,     2,     3,     4,     5,     6,     0,
       7,     8,     0,     9,    10,     0,     0,     0,     0,     0,
       0,    11,    12,     0,    13,   102,     0,     0,    14,    15,
       0,     0,     0,     0,    16,     1,     2,     3,     4,     5,
       6,     0,     7,     8,     0,     9,    10,     0,     0,     0,
       0,     0,     0,    11,    12,     0,    13,   216,     0,     0,
      14,    15,     0,     0,     0,     0,    16,     1,     2,     3,
       4,     5,     6,     0,     7,     8,     0,     9,    10,     0,
       0,     0,     0,     0,     0,    11,    12,     2,    13,     0,
       0,     0,    14,    15,    88,     0,     9,    10,    16,     1,
       2,     3,     4,     5,    87,   207,    95,    88,     0,     9,
      10,     0,     0,     0,     0,     0,     0,     0,   104,   150,
      13,     0,     0,     0,    14,    15,     0,     0,     0,     0,
      16,     1,     2,     3,     4,     5,    87,     0,     0,    88,
       0,     9,    10,     0,     0,     0,     0,     0,     0,     0,
     104,    95,    13,     0,     0,     0,    14,    15,     0,     0,
       0,     0,    16,     1,     2,     3,     4,     5,    87,     0,
       0,    88,     0,     9,    10,     0,     0,     0,     0,     0,
       0,     0,   104,   191,    13,     0,     0,     0,    14,    15,
       0,     0,     0,     0,    16,     1,     2,     3,     4,     5,
      87,     0,     0,    88,     0,     9,    10,     0,     0,     0,
       0,     0,     0,     0,   104,   210,    13,     0,     0,     0,
      14,    15,     0,     0,     0,     0,    16,     1,     2,     3,
       4,     5,    87,     0,     0,    88,     0,     9,    10,     0,
       0,     0,     0,     0,     0,     0,    89,     0,    13,     0,
       0,     0,    14,    15,     0,     0,     0,     0,    16,     1,
       2,     3,     4,     5,    87,     0,     0,    88,     0,     9,
      10,     0,     0,     0,     0,     0,     0,     0,   104,     0,
      13,     0,     0,     0,    14,    15,     0,     0,     0,     0,
      16,     1,     2,     3,     4,     5,     0,     0,     0,    88,
       0,     9,    10,     0,     0,     0,     0,     0,     0,     0,
     104,     0,    13,     0,     0,     0,    14,    15,     0,     0,
       0,     0,    16,   117,   118,   119,   120,   121,     0,     0,
     122,   123,   124,   125,   126,   127,   128,   129,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190
  };

  const short
  parser::yycheck_[] =
  {
       0,     8,    83,    17,    84,     3,   111,    12,   113,    23,
      22,    11,    12,    13,   113,     4,    17,    22,    18,     6,
       7,    26,    23,    26,    22,     3,     4,     5,     6,     7,
       8,    18,   137,    11,   139,    13,    14,    12,   137,    16,
     139,     3,     0,    30,    22,     0,    24,    22,    25,    27,
      28,    29,     3,    17,     3,    12,    34,    33,    13,    23,
      22,    12,   142,    18,    26,    22,    17,    12,    17,     3,
      17,    22,    23,    22,    23,    26,    23,    26,    12,    15,
      80,    88,    82,    83,    84,   165,    86,    22,    22,    89,
      90,    26,    26,    17,    94,    15,    96,     3,    22,    23,
      87,     4,    26,    90,   104,   105,    12,   107,    11,    96,
      13,    14,   112,    22,    15,    17,    22,    26,   105,    22,
     201,    23,    22,    16,    22,    80,    26,    22,    83,    84,
       9,   131,   132,     9,    30,   135,   136,    27,    27,     3,
       4,    96,   142,    27,     8,    27,    10,    11,   148,    13,
      14,   151,    27,     4,    13,   155,   237,    21,    22,   159,
      11,    -1,    13,    14,   151,   165,     0,   112,   168,   169,
      -1,    22,   172,    -1,    -1,   175,   176,    -1,    12,    13,
      14,    15,    16,    -1,    -1,   172,    -1,   142,    14,    15,
      16,    -1,    -1,    -1,    -1,   195,   196,   197,   198,   199,
      -1,   201,   202,   203,    -1,   205,    -1,    -1,   208,    -1,
     165,     4,   157,    -1,    12,   215,   161,   172,    11,    17,
      13,    14,   167,    -1,    22,    23,    -1,    -1,    26,    22,
      23,   231,    -1,    -1,   234,    18,   236,   237,     4,    -1,
      -1,    -1,    -1,   230,    -1,    11,   201,    13,    14,    83,
      84,    -1,    -1,   208,    -1,    89,    22,    23,    -1,    -1,
      -1,    -1,   207,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,    11,    12,    -1,    -1,    -1,   231,    -1,   112,   234,
      -1,   236,   237,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,    80,    -1,    -1,
      -1,    -1,    -1,    -1,   138,    -1,    -1,    90,   142,    -1,
      -1,    94,   146,    96,    -1,    -1,    -1,    -1,   152,    -1,
      -1,    -1,   105,   157,   107,    -1,    -1,   161,    -1,   163,
      -1,   165,    -1,   167,    -1,    -1,    -1,    -1,     4,    -1,
      -1,    -1,    82,    83,    -1,    11,    86,    13,    14,    89,
       3,     4,     5,     6,     7,     8,    22,    23,    11,    -1,
      13,    14,    -1,    -1,   104,    -1,    -1,   201,   151,    22,
      23,    24,   112,   207,    -1,    28,    29,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,
      -1,   131,   132,    -1,    -1,   135,   136,    -1,    -1,    -1,
      -1,    -1,    -1,   237,    -1,    -1,    -1,    -1,   148,    -1,
      -1,    -1,    -1,    -1,   197,   155,    -1,    -1,    -1,   159,
     203,    -1,   205,    -1,     4,   208,    -1,    -1,   168,   169,
      -1,    11,   215,    13,    14,   175,   176,    -1,    -1,    -1,
      -1,    -1,    22,    23,    -1,    -1,    -1,    -1,   231,    -1,
      -1,   234,    -1,   236,    -1,   195,   196,    -1,   198,   199,
      -1,    -1,   202,     3,     4,     5,     6,     7,     8,    -1,
      10,    11,    -1,    13,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    22,    -1,    24,    25,    -1,    -1,    28,    29,
      -1,    -1,    -1,    -1,    34,     3,     4,     5,     6,     7,
       8,    -1,    10,    11,    -1,    13,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    22,    -1,    24,    25,    -1,    -1,
      28,    29,    -1,    -1,    -1,    -1,    34,     3,     4,     5,
       6,     7,     8,    -1,    10,    11,    -1,    13,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    22,     4,    24,    -1,
      -1,    -1,    28,    29,    11,    -1,    13,    14,    34,     3,
       4,     5,     6,     7,     8,    22,    23,    11,    -1,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    23,
      24,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,
      34,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      22,    23,    24,    -1,    -1,    -1,    28,    29,    -1,    -1,
      -1,    -1,    34,     3,     4,     5,     6,     7,     8,    -1,
      -1,    11,    -1,    13,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    22,    23,    24,    -1,    -1,    -1,    28,    29,
      -1,    -1,    -1,    -1,    34,     3,     4,     5,     6,     7,
       8,    -1,    -1,    11,    -1,    13,    14,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    22,    23,    24,    -1,    -1,    -1,
      28,    29,    -1,    -1,    -1,    -1,    34,     3,     4,     5,
       6,     7,     8,    -1,    -1,    11,    -1,    13,    14,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    22,    -1,    24,    -1,
      -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    34,     3,
       4,     5,     6,     7,     8,    -1,    -1,    11,    -1,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    -1,
      24,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,
      34,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      -1,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      22,    -1,    24,    -1,    -1,    -1,    28,    29,    -1,    -1,
      -1,    -1,    34,    28,    29,    30,    31,    32,    -1,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,     8,    10,    11,    13,
      14,    21,    22,    24,    28,    29,    34,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     108,   111,    22,   104,   104,    99,    26,     8,    11,    22,
      45,    48,    98,   107,   108,    23,    45,    48,    60,   110,
     112,   113,    25,   111,    22,    45,    56,   108,    56,    56,
       0,    12,    26,    98,   104,   106,   108,    28,    29,    30,
      31,    32,    35,    36,    37,    38,    39,    40,    41,    42,
      33,    22,    26,   104,   107,    15,    15,    12,    22,    98,
     106,   108,    16,    47,    48,    46,    15,    48,   104,    99,
      23,    45,    17,    23,    98,    17,    23,    17,    23,    17,
      23,    17,    23,    17,    23,    16,    25,    22,   105,   109,
      14,    27,    45,    48,    60,   105,   109,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    23,    48,    48,    48,   105,   109,    45,   105,   109,
      46,     9,     9,    45,    27,    45,    48,    22,    45,    60,
      23,    48,    23,    60,    23,    45,    25,    23,    48,    48,
      27,    27,    27,    48,    48,    27,    48,    48,    48,    48,
       8,    45,    47,    98,   108,    48,    45,   104
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    43,    44,    44,    44,    46,    46,    47,    47,    47,
      47,    47,    47,    47,    47,    48,    48,    49,    49,    50,
      50,    51,    51,    51,    52,    52,    52,    52,    52,    53,
      53,    53,    54,    54,    54,    54,    55,    55,    56,    56,
      56,    56,    57,    57,    57,    57,    58,    58,    58,    58,
      58,    58,    59,    59,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    76,    75,
      77,    78,    78,    79,    80,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    82,    82,    82,    82,    83,    86,
      85,    85,    84,    60,    60,    88,    87,    89,    90,    91,
      92,    92,    92,    93,    96,    94,    95,    95,    95,    95,
      97,    97,    97,    97,    81,    99,    98,   100,   101,   102,
     107,   108,   109,   103,   103,   103,   111,   111,   106,   106,
     106,   113,   113,   104,   104,   104,   110,   110,   105,   105,
     105,   112,   112
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     2,     2,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     4,     4,
       4,     3,     4,     1,     1,     2,     2,     3,     3,     4,
       2,     2,     1,     5,     5,     3,     4,     4,     4,     4,
       4,     4,     4,     4,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     3,     4,     1,     3,     3,     3,
       4,     3,     3,     3,     3,     4,     3,     3,     3,     3,
       4,     3,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "NAME", "TYPENAME",
  "INTEGER", "DECIMAL", "STRING", "IF", "ELSE", "WHEN", "TYPE", "FN",
  "BUFFER", "AUTO", "ASSGN", "SEMI", "COMMA", "TO", "BY", "DOT3", "RETURN",
  "OPAREN", "CPAREN", "OBRACE", "CBRACE", "OBRACK", "CBRACK", "ADD", "SUB",
  "MUL", "DIV", "MOD", "POW", "NOT", "AND", "OR", "EQ", "NE", "GE", "LE",
  "GT", "LT", "$accept", "start", "type", "statement", "pure",
  "expression", "expr_or", "expr_and", "expr_eq", "expr_ord", "expr_add",
  "expr_mul", "expr_pow", "expr_pre", "expr_post", "expr_atom",
  "expr_right", "declaration", "or", "and", "eq", "ne", "ge", "le", "gt",
  "lt", "add", "sub", "mul", "div", "mod", "pow", "plus", "minus", "not",
  "application", "conversion", "subscript", "auto", "function_type",
  "array_type", "decl_array_type", "auto_array_type", "buffer_type",
  "type_decl", "single_decl", "definition", "assignment", "type_def",
  "return", "if", "when", "function_def", "expr_if", "function", "name",
  "type_name", "integer", "decimal", "string", "block", "paren_expr",
  "paren_decl", "paren_type", "void", "void_type", "void_decl",
  "expr_list", "stmt_list", "decl_list", "type_list", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   165,   165,   166,   167,   170,   171,   174,   175,   176,
     177,   178,   179,   180,   181,   184,   185,   188,   189,   192,
     193,   196,   197,   198,   201,   202,   203,   204,   205,   208,
     209,   210,   213,   214,   215,   216,   219,   220,   223,   224,
     225,   226,   229,   230,   231,   232,   235,   236,   237,   238,
     239,   241,   244,   245,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   261,   263,   264,
     265,   267,   268,   269,   270,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   284,   285,   286,   287,   290,   292,
     294,   295,   297,   300,   301,   303,   304,   306,   307,   308,
     311,   312,   313,   315,   316,   317,   320,   321,   322,   323,
     326,   327,   328,   329,   331,   332,   333,   334,   335,   336,
     338,   339,   340,   365,   366,   367,   369,   372,   377,   378,
     379,   381,   384,   389,   390,   391,   393,   396,   401,   402,
     403,   405,   408
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 3123 "src/parser.cpp"

#line 412 "gen/parser.y"


void yy::parser::error (std::string const & msg) {
    std::cerr << msg << '\n';
}
