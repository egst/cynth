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
      case symbol_kind::S_cat_array_elem: // cat_array_elem
        value.YY_MOVE_OR_COPY< cynth::ast::category::ArrayElem > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_declaration: // cat_declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.YY_MOVE_OR_COPY< cynth::ast::category::Declaration > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_expression: // cat_expression
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

      case symbol_kind::S_cat_statement: // cat_statement
      case symbol_kind::S_pure: // pure
        value.YY_MOVE_OR_COPY< cynth::ast::category::Statement > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_type: // cat_type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.YY_MOVE_OR_COPY< cynth::ast::category::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_add: // node_add
        value.YY_MOVE_OR_COPY< cynth::ast::node::Add > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_and: // node_and
        value.YY_MOVE_OR_COPY< cynth::ast::node::And > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_application: // node_application
        value.YY_MOVE_OR_COPY< cynth::ast::node::Application > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_array: // node_array
        value.YY_MOVE_OR_COPY< cynth::ast::node::Array > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_array_type: // node_array_type
        value.YY_MOVE_OR_COPY< cynth::ast::node::ArrayType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_assignment: // node_assignment
        value.YY_MOVE_OR_COPY< cynth::ast::node::Assignment > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_auto: // node_auto
        value.YY_MOVE_OR_COPY< cynth::ast::node::Auto > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_block: // node_block
        value.YY_MOVE_OR_COPY< cynth::ast::node::Block > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_bool: // node_bool
        value.YY_MOVE_OR_COPY< cynth::ast::node::Bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_buffer_type: // node_buffer_type
        value.YY_MOVE_OR_COPY< cynth::ast::node::BufferType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_const_type: // node_const_type
        value.YY_MOVE_OR_COPY< cynth::ast::node::ConstType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_conversion: // node_conversion
        value.YY_MOVE_OR_COPY< cynth::ast::node::Conversion > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_declaration: // node_declaration
        value.YY_MOVE_OR_COPY< cynth::ast::node::Declaration > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_definition: // node_definition
        value.YY_MOVE_OR_COPY< cynth::ast::node::Definition > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_div: // node_div
        value.YY_MOVE_OR_COPY< cynth::ast::node::Div > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_eq: // node_eq
        value.YY_MOVE_OR_COPY< cynth::ast::node::Eq > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.YY_MOVE_OR_COPY< cynth::ast::node::ExprIf > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_float: // node_float
        value.YY_MOVE_OR_COPY< cynth::ast::node::Float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function: // node_function
        value.YY_MOVE_OR_COPY< cynth::ast::node::Function > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.YY_MOVE_OR_COPY< cynth::ast::node::FunctionDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function_type: // node_function_type
        value.YY_MOVE_OR_COPY< cynth::ast::node::FunctionType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_ge: // node_ge
        value.YY_MOVE_OR_COPY< cynth::ast::node::Ge > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_gt: // node_gt
        value.YY_MOVE_OR_COPY< cynth::ast::node::Gt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_if: // node_if
        value.YY_MOVE_OR_COPY< cynth::ast::node::If > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_int: // node_int
        value.YY_MOVE_OR_COPY< cynth::ast::node::Int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_le: // node_le
        value.YY_MOVE_OR_COPY< cynth::ast::node::Le > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_lt: // node_lt
        value.YY_MOVE_OR_COPY< cynth::ast::node::Lt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_minus: // node_minus
        value.YY_MOVE_OR_COPY< cynth::ast::node::Minus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_mod: // node_mod
        value.YY_MOVE_OR_COPY< cynth::ast::node::Mod > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_mul: // node_mul
        value.YY_MOVE_OR_COPY< cynth::ast::node::Mul > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_name: // node_name
        value.YY_MOVE_OR_COPY< cynth::ast::node::Name > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_ne: // node_ne
        value.YY_MOVE_OR_COPY< cynth::ast::node::Ne > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_not: // node_not
        value.YY_MOVE_OR_COPY< cynth::ast::node::Not > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_or: // node_or
        value.YY_MOVE_OR_COPY< cynth::ast::node::Or > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_plus: // node_plus
        value.YY_MOVE_OR_COPY< cynth::ast::node::Plus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_pow: // node_pow
        value.YY_MOVE_OR_COPY< cynth::ast::node::Pow > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_range_to: // node_range_to
        value.YY_MOVE_OR_COPY< cynth::ast::node::RangeTo > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_range_to_by: // node_range_to_by
        value.YY_MOVE_OR_COPY< cynth::ast::node::RangeToBy > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_return: // node_return
        value.YY_MOVE_OR_COPY< cynth::ast::node::Return > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_spread: // node_spread
        value.YY_MOVE_OR_COPY< cynth::ast::node::Spread > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_string: // node_string
        value.YY_MOVE_OR_COPY< cynth::ast::node::String > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_sub: // node_sub
        value.YY_MOVE_OR_COPY< cynth::ast::node::Sub > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_subscript: // node_subscript
        value.YY_MOVE_OR_COPY< cynth::ast::node::Subscript > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_type_decl: // node_type_decl
        value.YY_MOVE_OR_COPY< cynth::ast::node::TypeDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_type_def: // node_type_def
        value.YY_MOVE_OR_COPY< cynth::ast::node::TypeDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_type_name: // node_type_name
        value.YY_MOVE_OR_COPY< cynth::ast::node::TypeName > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_when: // node_when
        value.YY_MOVE_OR_COPY< cynth::ast::node::When > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.YY_MOVE_OR_COPY< cynth::ast::node::component_vector<cynth::ast::category::ArrayElem> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.YY_MOVE_OR_COPY< cynth::ast::node::component_vector<cynth::ast::category::Declaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.YY_MOVE_OR_COPY< cynth::ast::node::component_vector<cynth::ast::category::Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.YY_MOVE_OR_COPY< cynth::ast::node::component_vector<cynth::ast::category::Statement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_list: // type_list
        value.YY_MOVE_OR_COPY< cynth::ast::node::component_vector<cynth::ast::category::Type> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_start: // start
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_STRING: // STRING
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
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
      case symbol_kind::S_cat_array_elem: // cat_array_elem
        value.move< cynth::ast::category::ArrayElem > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_declaration: // cat_declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.move< cynth::ast::category::Declaration > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_expression: // cat_expression
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

      case symbol_kind::S_cat_statement: // cat_statement
      case symbol_kind::S_pure: // pure
        value.move< cynth::ast::category::Statement > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_type: // cat_type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.move< cynth::ast::category::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_add: // node_add
        value.move< cynth::ast::node::Add > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_and: // node_and
        value.move< cynth::ast::node::And > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_application: // node_application
        value.move< cynth::ast::node::Application > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_array: // node_array
        value.move< cynth::ast::node::Array > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_array_type: // node_array_type
        value.move< cynth::ast::node::ArrayType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_assignment: // node_assignment
        value.move< cynth::ast::node::Assignment > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_auto: // node_auto
        value.move< cynth::ast::node::Auto > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_block: // node_block
        value.move< cynth::ast::node::Block > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_bool: // node_bool
        value.move< cynth::ast::node::Bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_buffer_type: // node_buffer_type
        value.move< cynth::ast::node::BufferType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_const_type: // node_const_type
        value.move< cynth::ast::node::ConstType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_conversion: // node_conversion
        value.move< cynth::ast::node::Conversion > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_declaration: // node_declaration
        value.move< cynth::ast::node::Declaration > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_definition: // node_definition
        value.move< cynth::ast::node::Definition > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_div: // node_div
        value.move< cynth::ast::node::Div > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_eq: // node_eq
        value.move< cynth::ast::node::Eq > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.move< cynth::ast::node::ExprIf > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_float: // node_float
        value.move< cynth::ast::node::Float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function: // node_function
        value.move< cynth::ast::node::Function > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.move< cynth::ast::node::FunctionDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function_type: // node_function_type
        value.move< cynth::ast::node::FunctionType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_ge: // node_ge
        value.move< cynth::ast::node::Ge > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_gt: // node_gt
        value.move< cynth::ast::node::Gt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_if: // node_if
        value.move< cynth::ast::node::If > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_int: // node_int
        value.move< cynth::ast::node::Int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_le: // node_le
        value.move< cynth::ast::node::Le > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_lt: // node_lt
        value.move< cynth::ast::node::Lt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_minus: // node_minus
        value.move< cynth::ast::node::Minus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_mod: // node_mod
        value.move< cynth::ast::node::Mod > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_mul: // node_mul
        value.move< cynth::ast::node::Mul > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_name: // node_name
        value.move< cynth::ast::node::Name > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_ne: // node_ne
        value.move< cynth::ast::node::Ne > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_not: // node_not
        value.move< cynth::ast::node::Not > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_or: // node_or
        value.move< cynth::ast::node::Or > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_plus: // node_plus
        value.move< cynth::ast::node::Plus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_pow: // node_pow
        value.move< cynth::ast::node::Pow > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_range_to: // node_range_to
        value.move< cynth::ast::node::RangeTo > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_range_to_by: // node_range_to_by
        value.move< cynth::ast::node::RangeToBy > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_return: // node_return
        value.move< cynth::ast::node::Return > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_spread: // node_spread
        value.move< cynth::ast::node::Spread > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_string: // node_string
        value.move< cynth::ast::node::String > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_sub: // node_sub
        value.move< cynth::ast::node::Sub > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_subscript: // node_subscript
        value.move< cynth::ast::node::Subscript > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_type_decl: // node_type_decl
        value.move< cynth::ast::node::TypeDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_type_def: // node_type_def
        value.move< cynth::ast::node::TypeDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_type_name: // node_type_name
        value.move< cynth::ast::node::TypeName > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_when: // node_when
        value.move< cynth::ast::node::When > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.move< cynth::ast::node::component_vector<cynth::ast::category::ArrayElem> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< cynth::ast::node::component_vector<cynth::ast::category::Declaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< cynth::ast::node::component_vector<cynth::ast::category::Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< cynth::ast::node::component_vector<cynth::ast::category::Statement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_list: // type_list
        value.move< cynth::ast::node::component_vector<cynth::ast::category::Type> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_start: // start
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_STRING: // STRING
        value.move< std::string > (YY_MOVE (that.value));
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
      case symbol_kind::S_cat_array_elem: // cat_array_elem
        value.copy< cynth::ast::category::ArrayElem > (that.value);
        break;

      case symbol_kind::S_cat_declaration: // cat_declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.copy< cynth::ast::category::Declaration > (that.value);
        break;

      case symbol_kind::S_cat_expression: // cat_expression
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

      case symbol_kind::S_cat_statement: // cat_statement
      case symbol_kind::S_pure: // pure
        value.copy< cynth::ast::category::Statement > (that.value);
        break;

      case symbol_kind::S_cat_type: // cat_type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.copy< cynth::ast::category::Type > (that.value);
        break;

      case symbol_kind::S_node_add: // node_add
        value.copy< cynth::ast::node::Add > (that.value);
        break;

      case symbol_kind::S_node_and: // node_and
        value.copy< cynth::ast::node::And > (that.value);
        break;

      case symbol_kind::S_node_application: // node_application
        value.copy< cynth::ast::node::Application > (that.value);
        break;

      case symbol_kind::S_node_array: // node_array
        value.copy< cynth::ast::node::Array > (that.value);
        break;

      case symbol_kind::S_node_array_type: // node_array_type
        value.copy< cynth::ast::node::ArrayType > (that.value);
        break;

      case symbol_kind::S_node_assignment: // node_assignment
        value.copy< cynth::ast::node::Assignment > (that.value);
        break;

      case symbol_kind::S_node_auto: // node_auto
        value.copy< cynth::ast::node::Auto > (that.value);
        break;

      case symbol_kind::S_node_block: // node_block
        value.copy< cynth::ast::node::Block > (that.value);
        break;

      case symbol_kind::S_node_bool: // node_bool
        value.copy< cynth::ast::node::Bool > (that.value);
        break;

      case symbol_kind::S_node_buffer_type: // node_buffer_type
        value.copy< cynth::ast::node::BufferType > (that.value);
        break;

      case symbol_kind::S_node_const_type: // node_const_type
        value.copy< cynth::ast::node::ConstType > (that.value);
        break;

      case symbol_kind::S_node_conversion: // node_conversion
        value.copy< cynth::ast::node::Conversion > (that.value);
        break;

      case symbol_kind::S_node_declaration: // node_declaration
        value.copy< cynth::ast::node::Declaration > (that.value);
        break;

      case symbol_kind::S_node_definition: // node_definition
        value.copy< cynth::ast::node::Definition > (that.value);
        break;

      case symbol_kind::S_node_div: // node_div
        value.copy< cynth::ast::node::Div > (that.value);
        break;

      case symbol_kind::S_node_eq: // node_eq
        value.copy< cynth::ast::node::Eq > (that.value);
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.copy< cynth::ast::node::ExprIf > (that.value);
        break;

      case symbol_kind::S_node_float: // node_float
        value.copy< cynth::ast::node::Float > (that.value);
        break;

      case symbol_kind::S_node_function: // node_function
        value.copy< cynth::ast::node::Function > (that.value);
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.copy< cynth::ast::node::FunctionDef > (that.value);
        break;

      case symbol_kind::S_node_function_type: // node_function_type
        value.copy< cynth::ast::node::FunctionType > (that.value);
        break;

      case symbol_kind::S_node_ge: // node_ge
        value.copy< cynth::ast::node::Ge > (that.value);
        break;

      case symbol_kind::S_node_gt: // node_gt
        value.copy< cynth::ast::node::Gt > (that.value);
        break;

      case symbol_kind::S_node_if: // node_if
        value.copy< cynth::ast::node::If > (that.value);
        break;

      case symbol_kind::S_node_int: // node_int
        value.copy< cynth::ast::node::Int > (that.value);
        break;

      case symbol_kind::S_node_le: // node_le
        value.copy< cynth::ast::node::Le > (that.value);
        break;

      case symbol_kind::S_node_lt: // node_lt
        value.copy< cynth::ast::node::Lt > (that.value);
        break;

      case symbol_kind::S_node_minus: // node_minus
        value.copy< cynth::ast::node::Minus > (that.value);
        break;

      case symbol_kind::S_node_mod: // node_mod
        value.copy< cynth::ast::node::Mod > (that.value);
        break;

      case symbol_kind::S_node_mul: // node_mul
        value.copy< cynth::ast::node::Mul > (that.value);
        break;

      case symbol_kind::S_node_name: // node_name
        value.copy< cynth::ast::node::Name > (that.value);
        break;

      case symbol_kind::S_node_ne: // node_ne
        value.copy< cynth::ast::node::Ne > (that.value);
        break;

      case symbol_kind::S_node_not: // node_not
        value.copy< cynth::ast::node::Not > (that.value);
        break;

      case symbol_kind::S_node_or: // node_or
        value.copy< cynth::ast::node::Or > (that.value);
        break;

      case symbol_kind::S_node_plus: // node_plus
        value.copy< cynth::ast::node::Plus > (that.value);
        break;

      case symbol_kind::S_node_pow: // node_pow
        value.copy< cynth::ast::node::Pow > (that.value);
        break;

      case symbol_kind::S_node_range_to: // node_range_to
        value.copy< cynth::ast::node::RangeTo > (that.value);
        break;

      case symbol_kind::S_node_range_to_by: // node_range_to_by
        value.copy< cynth::ast::node::RangeToBy > (that.value);
        break;

      case symbol_kind::S_node_return: // node_return
        value.copy< cynth::ast::node::Return > (that.value);
        break;

      case symbol_kind::S_node_spread: // node_spread
        value.copy< cynth::ast::node::Spread > (that.value);
        break;

      case symbol_kind::S_node_string: // node_string
        value.copy< cynth::ast::node::String > (that.value);
        break;

      case symbol_kind::S_node_sub: // node_sub
        value.copy< cynth::ast::node::Sub > (that.value);
        break;

      case symbol_kind::S_node_subscript: // node_subscript
        value.copy< cynth::ast::node::Subscript > (that.value);
        break;

      case symbol_kind::S_node_type_decl: // node_type_decl
        value.copy< cynth::ast::node::TypeDecl > (that.value);
        break;

      case symbol_kind::S_node_type_def: // node_type_def
        value.copy< cynth::ast::node::TypeDef > (that.value);
        break;

      case symbol_kind::S_node_type_name: // node_type_name
        value.copy< cynth::ast::node::TypeName > (that.value);
        break;

      case symbol_kind::S_node_when: // node_when
        value.copy< cynth::ast::node::When > (that.value);
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.copy< cynth::ast::node::component_vector<cynth::ast::category::ArrayElem> > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.copy< cynth::ast::node::component_vector<cynth::ast::category::Declaration> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.copy< cynth::ast::node::component_vector<cynth::ast::category::Expression> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< cynth::ast::node::component_vector<cynth::ast::category::Statement> > (that.value);
        break;

      case symbol_kind::S_type_list: // type_list
        value.copy< cynth::ast::node::component_vector<cynth::ast::category::Type> > (that.value);
        break;

      case symbol_kind::S_start: // start
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_STRING: // STRING
        value.copy< std::string > (that.value);
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
      case symbol_kind::S_cat_array_elem: // cat_array_elem
        value.move< cynth::ast::category::ArrayElem > (that.value);
        break;

      case symbol_kind::S_cat_declaration: // cat_declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.move< cynth::ast::category::Declaration > (that.value);
        break;

      case symbol_kind::S_cat_expression: // cat_expression
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

      case symbol_kind::S_cat_statement: // cat_statement
      case symbol_kind::S_pure: // pure
        value.move< cynth::ast::category::Statement > (that.value);
        break;

      case symbol_kind::S_cat_type: // cat_type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.move< cynth::ast::category::Type > (that.value);
        break;

      case symbol_kind::S_node_add: // node_add
        value.move< cynth::ast::node::Add > (that.value);
        break;

      case symbol_kind::S_node_and: // node_and
        value.move< cynth::ast::node::And > (that.value);
        break;

      case symbol_kind::S_node_application: // node_application
        value.move< cynth::ast::node::Application > (that.value);
        break;

      case symbol_kind::S_node_array: // node_array
        value.move< cynth::ast::node::Array > (that.value);
        break;

      case symbol_kind::S_node_array_type: // node_array_type
        value.move< cynth::ast::node::ArrayType > (that.value);
        break;

      case symbol_kind::S_node_assignment: // node_assignment
        value.move< cynth::ast::node::Assignment > (that.value);
        break;

      case symbol_kind::S_node_auto: // node_auto
        value.move< cynth::ast::node::Auto > (that.value);
        break;

      case symbol_kind::S_node_block: // node_block
        value.move< cynth::ast::node::Block > (that.value);
        break;

      case symbol_kind::S_node_bool: // node_bool
        value.move< cynth::ast::node::Bool > (that.value);
        break;

      case symbol_kind::S_node_buffer_type: // node_buffer_type
        value.move< cynth::ast::node::BufferType > (that.value);
        break;

      case symbol_kind::S_node_const_type: // node_const_type
        value.move< cynth::ast::node::ConstType > (that.value);
        break;

      case symbol_kind::S_node_conversion: // node_conversion
        value.move< cynth::ast::node::Conversion > (that.value);
        break;

      case symbol_kind::S_node_declaration: // node_declaration
        value.move< cynth::ast::node::Declaration > (that.value);
        break;

      case symbol_kind::S_node_definition: // node_definition
        value.move< cynth::ast::node::Definition > (that.value);
        break;

      case symbol_kind::S_node_div: // node_div
        value.move< cynth::ast::node::Div > (that.value);
        break;

      case symbol_kind::S_node_eq: // node_eq
        value.move< cynth::ast::node::Eq > (that.value);
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.move< cynth::ast::node::ExprIf > (that.value);
        break;

      case symbol_kind::S_node_float: // node_float
        value.move< cynth::ast::node::Float > (that.value);
        break;

      case symbol_kind::S_node_function: // node_function
        value.move< cynth::ast::node::Function > (that.value);
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.move< cynth::ast::node::FunctionDef > (that.value);
        break;

      case symbol_kind::S_node_function_type: // node_function_type
        value.move< cynth::ast::node::FunctionType > (that.value);
        break;

      case symbol_kind::S_node_ge: // node_ge
        value.move< cynth::ast::node::Ge > (that.value);
        break;

      case symbol_kind::S_node_gt: // node_gt
        value.move< cynth::ast::node::Gt > (that.value);
        break;

      case symbol_kind::S_node_if: // node_if
        value.move< cynth::ast::node::If > (that.value);
        break;

      case symbol_kind::S_node_int: // node_int
        value.move< cynth::ast::node::Int > (that.value);
        break;

      case symbol_kind::S_node_le: // node_le
        value.move< cynth::ast::node::Le > (that.value);
        break;

      case symbol_kind::S_node_lt: // node_lt
        value.move< cynth::ast::node::Lt > (that.value);
        break;

      case symbol_kind::S_node_minus: // node_minus
        value.move< cynth::ast::node::Minus > (that.value);
        break;

      case symbol_kind::S_node_mod: // node_mod
        value.move< cynth::ast::node::Mod > (that.value);
        break;

      case symbol_kind::S_node_mul: // node_mul
        value.move< cynth::ast::node::Mul > (that.value);
        break;

      case symbol_kind::S_node_name: // node_name
        value.move< cynth::ast::node::Name > (that.value);
        break;

      case symbol_kind::S_node_ne: // node_ne
        value.move< cynth::ast::node::Ne > (that.value);
        break;

      case symbol_kind::S_node_not: // node_not
        value.move< cynth::ast::node::Not > (that.value);
        break;

      case symbol_kind::S_node_or: // node_or
        value.move< cynth::ast::node::Or > (that.value);
        break;

      case symbol_kind::S_node_plus: // node_plus
        value.move< cynth::ast::node::Plus > (that.value);
        break;

      case symbol_kind::S_node_pow: // node_pow
        value.move< cynth::ast::node::Pow > (that.value);
        break;

      case symbol_kind::S_node_range_to: // node_range_to
        value.move< cynth::ast::node::RangeTo > (that.value);
        break;

      case symbol_kind::S_node_range_to_by: // node_range_to_by
        value.move< cynth::ast::node::RangeToBy > (that.value);
        break;

      case symbol_kind::S_node_return: // node_return
        value.move< cynth::ast::node::Return > (that.value);
        break;

      case symbol_kind::S_node_spread: // node_spread
        value.move< cynth::ast::node::Spread > (that.value);
        break;

      case symbol_kind::S_node_string: // node_string
        value.move< cynth::ast::node::String > (that.value);
        break;

      case symbol_kind::S_node_sub: // node_sub
        value.move< cynth::ast::node::Sub > (that.value);
        break;

      case symbol_kind::S_node_subscript: // node_subscript
        value.move< cynth::ast::node::Subscript > (that.value);
        break;

      case symbol_kind::S_node_type_decl: // node_type_decl
        value.move< cynth::ast::node::TypeDecl > (that.value);
        break;

      case symbol_kind::S_node_type_def: // node_type_def
        value.move< cynth::ast::node::TypeDef > (that.value);
        break;

      case symbol_kind::S_node_type_name: // node_type_name
        value.move< cynth::ast::node::TypeName > (that.value);
        break;

      case symbol_kind::S_node_when: // node_when
        value.move< cynth::ast::node::When > (that.value);
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.move< cynth::ast::node::component_vector<cynth::ast::category::ArrayElem> > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< cynth::ast::node::component_vector<cynth::ast::category::Declaration> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< cynth::ast::node::component_vector<cynth::ast::category::Expression> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< cynth::ast::node::component_vector<cynth::ast::category::Statement> > (that.value);
        break;

      case symbol_kind::S_type_list: // type_list
        value.move< cynth::ast::node::component_vector<cynth::ast::category::Type> > (that.value);
        break;

      case symbol_kind::S_start: // start
        value.move< int > (that.value);
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_STRING: // STRING
        value.move< std::string > (that.value);
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
      case symbol_kind::S_cat_array_elem: // cat_array_elem
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_cat_declaration: // cat_declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_cat_expression: // cat_expression
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
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_cat_statement: // cat_statement
      case symbol_kind::S_pure: // pure
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_cat_type: // cat_type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_add: // node_add
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_and: // node_and
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_application: // node_application
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_array: // node_array
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_array_type: // node_array_type
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_assignment: // node_assignment
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_auto: // node_auto
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_block: // node_block
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_bool: // node_bool
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_buffer_type: // node_buffer_type
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_const_type: // node_const_type
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_conversion: // node_conversion
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_declaration: // node_declaration
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_definition: // node_definition
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_div: // node_div
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_eq: // node_eq
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_float: // node_float
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_function: // node_function
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_function_type: // node_function_type
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_ge: // node_ge
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_gt: // node_gt
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_if: // node_if
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_int: // node_int
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_le: // node_le
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_lt: // node_lt
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_minus: // node_minus
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_mod: // node_mod
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_mul: // node_mul
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_name: // node_name
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_ne: // node_ne
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_not: // node_not
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_or: // node_or
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_plus: // node_plus
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_pow: // node_pow
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_range_to: // node_range_to
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_range_to_by: // node_range_to_by
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_return: // node_return
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_spread: // node_spread
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_string: // node_string
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_sub: // node_sub
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_subscript: // node_subscript
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_type_decl: // node_type_decl
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_type_def: // node_type_def
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_type_name: // node_type_name
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_when: // node_when
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_decl_list: // decl_list
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_expr_list: // expr_list
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_type_list: // type_list
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_start: // start
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_STRING: // STRING
        yylhs.value.emplace< std::string > ();
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
#line 177 "gen/parser.y"
           {
        result = {};
    }
#line 1791 "src/parser.cpp"
    break;

  case 3: // start: stmt_list
#line 183 "gen/parser.y"
                    {
        result = {YY_MOVE (yystack_[0].value.as < cynth::ast::node::component_vector<cynth::ast::category::Statement> > ())};
    }
#line 1799 "src/parser.cpp"
    break;

  case 4: // start: stmt_list SEMI
#line 186 "gen/parser.y"
                         {
        result = {YY_MOVE (yystack_[1].value.as < cynth::ast::node::component_vector<cynth::ast::category::Statement> > ())};
    }
#line 1807 "src/parser.cpp"
    break;

  case 5: // cat_declaration: node_declaration
#line 193 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Declaration > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Declaration > ()); }
#line 1813 "src/parser.cpp"
    break;

  case 6: // cat_declaration: paren_decl
#line 194 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Declaration > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Declaration > ()); }
#line 1819 "src/parser.cpp"
    break;

  case 7: // cat_array_elem: node_range_to
#line 197 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::ArrayElem > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::RangeTo > ()); }
#line 1825 "src/parser.cpp"
    break;

  case 8: // cat_array_elem: node_range_to_by
#line 198 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::ArrayElem > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::RangeToBy > ()); }
#line 1831 "src/parser.cpp"
    break;

  case 9: // cat_array_elem: node_spread
#line 199 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::ArrayElem > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Spread > ()); }
#line 1837 "src/parser.cpp"
    break;

  case 10: // cat_array_elem: cat_expression
#line 200 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::ArrayElem > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1843 "src/parser.cpp"
    break;

  case 11: // cat_type: node_auto
#line 203 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Auto > ()); }
#line 1849 "src/parser.cpp"
    break;

  case 12: // cat_type: node_type_name
#line 204 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeName > ()); }
#line 1855 "src/parser.cpp"
    break;

  case 13: // cat_type: node_function_type
#line 205 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::FunctionType > ()); }
#line 1861 "src/parser.cpp"
    break;

  case 14: // cat_type: node_array_type
#line 206 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::ArrayType > ()); }
#line 1867 "src/parser.cpp"
    break;

  case 15: // cat_type: node_buffer_type
#line 207 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::BufferType > ()); }
#line 1873 "src/parser.cpp"
    break;

  case 16: // cat_type: node_type_decl
#line 208 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeDecl > ()); }
#line 1879 "src/parser.cpp"
    break;

  case 17: // cat_type: node_const_type
#line 209 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::ConstType > ()); }
#line 1885 "src/parser.cpp"
    break;

  case 18: // cat_type: paren_type
#line 210 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()); }
#line 1891 "src/parser.cpp"
    break;

  case 19: // cat_expression: expr_or
#line 213 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1897 "src/parser.cpp"
    break;

  case 20: // cat_expression: expr_right
#line 214 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1903 "src/parser.cpp"
    break;

  case 21: // cat_statement: pure
#line 217 "gen/parser.y"
                   { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ()); }
#line 1909 "src/parser.cpp"
    break;

  case 22: // cat_statement: cat_expression
#line 218 "gen/parser.y"
                   { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1915 "src/parser.cpp"
    break;

  case 23: // pure: node_declaration
#line 223 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Declaration > ()); }
#line 1921 "src/parser.cpp"
    break;

  case 24: // pure: node_definition
#line 224 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Definition > ()); }
#line 1927 "src/parser.cpp"
    break;

  case 25: // pure: node_assignment
#line 225 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Assignment > ()); }
#line 1933 "src/parser.cpp"
    break;

  case 26: // pure: node_type_def
#line 226 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeDef > ()); }
#line 1939 "src/parser.cpp"
    break;

  case 27: // pure: node_function_def
#line 227 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::FunctionDef > ()); }
#line 1945 "src/parser.cpp"
    break;

  case 28: // pure: node_return
#line 228 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Return > ()); }
#line 1951 "src/parser.cpp"
    break;

  case 29: // pure: node_if
#line 229 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::If > ()); }
#line 1957 "src/parser.cpp"
    break;

  case 30: // pure: node_when
#line 230 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::When > ()); }
#line 1963 "src/parser.cpp"
    break;

  case 31: // expr_or: node_or
#line 233 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Or > ()); }
#line 1969 "src/parser.cpp"
    break;

  case 32: // expr_or: expr_and
#line 234 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1975 "src/parser.cpp"
    break;

  case 33: // expr_and: node_and
#line 237 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::And > ()); }
#line 1981 "src/parser.cpp"
    break;

  case 34: // expr_and: expr_eq
#line 238 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1987 "src/parser.cpp"
    break;

  case 35: // expr_eq: node_eq
#line 241 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Eq > ()); }
#line 1993 "src/parser.cpp"
    break;

  case 36: // expr_eq: node_ne
#line 242 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Ne > ()); }
#line 1999 "src/parser.cpp"
    break;

  case 37: // expr_eq: expr_ord
#line 243 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2005 "src/parser.cpp"
    break;

  case 38: // expr_ord: node_ge
#line 246 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Ge > ()); }
#line 2011 "src/parser.cpp"
    break;

  case 39: // expr_ord: node_le
#line 247 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Le > ()); }
#line 2017 "src/parser.cpp"
    break;

  case 40: // expr_ord: node_gt
#line 248 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Gt > ()); }
#line 2023 "src/parser.cpp"
    break;

  case 41: // expr_ord: node_lt
#line 249 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Lt > ()); }
#line 2029 "src/parser.cpp"
    break;

  case 42: // expr_ord: expr_add
#line 250 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2035 "src/parser.cpp"
    break;

  case 43: // expr_add: node_add
#line 253 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Add > ()); }
#line 2041 "src/parser.cpp"
    break;

  case 44: // expr_add: node_sub
#line 254 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Sub > ()); }
#line 2047 "src/parser.cpp"
    break;

  case 45: // expr_add: expr_mul
#line 255 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2053 "src/parser.cpp"
    break;

  case 46: // expr_mul: node_mul
#line 258 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Mul > ()); }
#line 2059 "src/parser.cpp"
    break;

  case 47: // expr_mul: node_div
#line 259 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Div > ()); }
#line 2065 "src/parser.cpp"
    break;

  case 48: // expr_mul: node_mod
#line 260 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Mod > ()); }
#line 2071 "src/parser.cpp"
    break;

  case 49: // expr_mul: expr_pow
#line 261 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2077 "src/parser.cpp"
    break;

  case 50: // expr_pow: node_pow
#line 264 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Pow > ()); }
#line 2083 "src/parser.cpp"
    break;

  case 51: // expr_pow: expr_pre
#line 265 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2089 "src/parser.cpp"
    break;

  case 52: // expr_pre: node_minus
#line 268 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Minus > ()); }
#line 2095 "src/parser.cpp"
    break;

  case 53: // expr_pre: node_plus
#line 269 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Plus > ()); }
#line 2101 "src/parser.cpp"
    break;

  case 54: // expr_pre: node_not
#line 270 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Not > ()); }
#line 2107 "src/parser.cpp"
    break;

  case 55: // expr_pre: expr_post
#line 271 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2113 "src/parser.cpp"
    break;

  case 56: // expr_post: node_application
#line 274 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Application > ()); }
#line 2119 "src/parser.cpp"
    break;

  case 57: // expr_post: node_conversion
#line 275 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Conversion > ()); }
#line 2125 "src/parser.cpp"
    break;

  case 58: // expr_post: node_subscript
#line 276 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Subscript > ()); }
#line 2131 "src/parser.cpp"
    break;

  case 59: // expr_post: expr_atom
#line 277 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2137 "src/parser.cpp"
    break;

  case 60: // expr_atom: node_name
#line 280 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Name > ()); }
#line 2143 "src/parser.cpp"
    break;

  case 61: // expr_atom: node_bool
#line 281 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Bool > ()); }
#line 2149 "src/parser.cpp"
    break;

  case 62: // expr_atom: node_int
#line 282 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Int > ()); }
#line 2155 "src/parser.cpp"
    break;

  case 63: // expr_atom: node_float
#line 283 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Float > ()); }
#line 2161 "src/parser.cpp"
    break;

  case 64: // expr_atom: node_string
#line 284 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::String > ()); }
#line 2167 "src/parser.cpp"
    break;

  case 65: // expr_atom: node_block
#line 285 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Block > ()); }
#line 2173 "src/parser.cpp"
    break;

  case 66: // expr_atom: node_array
#line 286 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Array > ()); }
#line 2179 "src/parser.cpp"
    break;

  case 67: // expr_atom: paren_expr
#line 287 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2185 "src/parser.cpp"
    break;

  case 68: // expr_right: node_expr_if
#line 290 "gen/parser.y"
                  { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::ExprIf > ()); }
#line 2191 "src/parser.cpp"
    break;

  case 69: // expr_right: node_function
#line 291 "gen/parser.y"
                  { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Function > ()); }
#line 2197 "src/parser.cpp"
    break;

  case 70: // paren_type: OPAREN cat_type CPAREN
#line 296 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ());
    }
#line 2205 "src/parser.cpp"
    break;

  case 71: // paren_type: OPAREN type_list CPAREN
#line 299 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::category::Type > () = cynth::ast::node::TupleType{YY_MOVE (yystack_[1].value.as < cynth::ast::node::component_vector<cynth::ast::category::Type> > ())};
    }
#line 2213 "src/parser.cpp"
    break;

  case 72: // paren_type: OPAREN type_list COMMA CPAREN
#line 302 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::category::Type > () = cynth::ast::node::TupleType{YY_MOVE (yystack_[2].value.as < cynth::ast::node::component_vector<cynth::ast::category::Type> > ())};
    }
#line 2221 "src/parser.cpp"
    break;

  case 73: // void_type: OPAREN CPAREN
#line 307 "gen/parser.y"
                  {
        yylhs.value.as < cynth::ast::category::Type > () = cynth::ast::node::TupleType{};
    }
#line 2229 "src/parser.cpp"
    break;

  case 74: // node_auto: AUTO
#line 312 "gen/parser.y"
         {
        yylhs.value.as < cynth::ast::node::Auto > () = {};
    }
#line 2237 "src/parser.cpp"
    break;

  case 75: // node_type_name: TYPENAME
#line 317 "gen/parser.y"
                   {
        yylhs.value.as < cynth::ast::node::TypeName > () = {YY_MOVE (yystack_[0].value.as < std::string > ())};
    }
#line 2245 "src/parser.cpp"
    break;

  case 76: // node_const_type: cat_type CONST
#line 322 "gen/parser.y"
                         {
        yylhs.value.as < cynth::ast::node::ConstType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ())};
    }
#line 2253 "src/parser.cpp"
    break;

  case 77: // node_function_type: cat_type paren_type
#line 327 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::ast::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2261 "src/parser.cpp"
    break;

  case 78: // node_function_type: void_type paren_type
#line 330 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2269 "src/parser.cpp"
    break;

  case 79: // node_function_type: cat_type void_type
#line 333 "gen/parser.y"
                                {
        yylhs.value.as < cynth::ast::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2277 "src/parser.cpp"
    break;

  case 80: // node_function_type: void_type void_type
#line 336 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::ast::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2285 "src/parser.cpp"
    break;

  case 81: // node_array_type: cat_type OBRACK cat_expression CBRACK
#line 341 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::ast::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .size = cynth::ast::category::Pattern{YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ())}};
    }
#line 2293 "src/parser.cpp"
    break;

  case 82: // node_array_type: cat_type OBRACK AUTO CBRACK
#line 344 "gen/parser.y"
                                      {
        yylhs.value.as < cynth::ast::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .size = cynth::ast::node::optional_component<cynth::ast::category::Pattern>{}};
    }
#line 2301 "src/parser.cpp"
    break;

  case 83: // node_array_type: cat_type OBRACK CBRACK
#line 347 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::ast::node::ArrayType > () = {.type = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Type > ()), .size = cynth::ast::node::optional_component<cynth::ast::category::Pattern>{}};
    }
#line 2309 "src/parser.cpp"
    break;

  case 84: // node_array_type: cat_type OBRACK cat_declaration CBRACK
#line 350 "gen/parser.y"
                                                            {
        yylhs.value.as < cynth::ast::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .size = cynth::ast::category::Pattern{YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ())}};
    }
#line 2317 "src/parser.cpp"
    break;

  case 85: // node_buffer_type: BUFFER OBRACK cat_expression CBRACK
#line 355 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::ast::node::BufferType > () = {.size = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ())};
    }
#line 2325 "src/parser.cpp"
    break;

  case 86: // node_type_decl: TYPE node_type_name
#line 360 "gen/parser.y"
                              {
        yylhs.value.as < cynth::ast::node::TypeDecl > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeName > ())};
    }
#line 2333 "src/parser.cpp"
    break;

  case 87: // paren_decl: OPAREN cat_declaration CPAREN
#line 367 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::ast::category::Declaration > () = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ());
    }
#line 2341 "src/parser.cpp"
    break;

  case 88: // paren_decl: OPAREN decl_list CPAREN
#line 370 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::category::Declaration > () = cynth::ast::node::TupleDecl{YY_MOVE (yystack_[1].value.as < cynth::ast::node::component_vector<cynth::ast::category::Declaration> > ())};
    }
#line 2349 "src/parser.cpp"
    break;

  case 89: // paren_decl: OPAREN decl_list COMMA CPAREN
#line 373 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::category::Declaration > () = cynth::ast::node::TupleDecl{YY_MOVE (yystack_[2].value.as < cynth::ast::node::component_vector<cynth::ast::category::Declaration> > ())};
    }
#line 2357 "src/parser.cpp"
    break;

  case 90: // void_decl: OPAREN CPAREN
#line 378 "gen/parser.y"
                  {
        yylhs.value.as < cynth::ast::category::Declaration > () = cynth::ast::node::TupleDecl{};
    }
#line 2365 "src/parser.cpp"
    break;

  case 91: // node_declaration: cat_type node_name
#line 383 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Declaration > () = {.name = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Name > ()), .type = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ())};
    }
#line 2373 "src/parser.cpp"
    break;

  case 92: // node_range_to: cat_expression TO cat_expression
#line 390 "gen/parser.y"
                                               {
        yylhs.value.as < cynth::ast::node::RangeTo > () = {.from = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), .to = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2381 "src/parser.cpp"
    break;

  case 93: // node_range_to_by: cat_expression TO cat_expression BY cat_expression
#line 395 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::ast::node::RangeToBy > () = {.from = YY_MOVE (yystack_[4].value.as < cynth::ast::category::Expression > ()), .to = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), .by = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2389 "src/parser.cpp"
    break;

  case 94: // node_spread: ELIP cat_expression
#line 400 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Spread > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2397 "src/parser.cpp"
    break;

  case 95: // paren_expr: OPAREN cat_expression CPAREN
#line 407 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ());
    }
#line 2405 "src/parser.cpp"
    break;

  case 96: // paren_expr: OPAREN expr_list CPAREN
#line 410 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::category::Expression > () = cynth::ast::node::Tuple{YY_MOVE (yystack_[1].value.as < cynth::ast::node::component_vector<cynth::ast::category::Expression> > ())};
    }
#line 2413 "src/parser.cpp"
    break;

  case 97: // paren_expr: OPAREN expr_list COMMA CPAREN
#line 413 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::category::Expression > () = cynth::ast::node::Tuple{YY_MOVE (yystack_[2].value.as < cynth::ast::node::component_vector<cynth::ast::category::Expression> > ())};
    }
#line 2421 "src/parser.cpp"
    break;

  case 98: // void: OPAREN CPAREN
#line 418 "gen/parser.y"
                  {
        yylhs.value.as < cynth::ast::category::Expression > () = cynth::ast::node::Tuple{};
    }
#line 2429 "src/parser.cpp"
    break;

  case 99: // node_name: NAME
#line 423 "gen/parser.y"
               {
        yylhs.value.as < cynth::ast::node::Name > () = {YY_MOVE (yystack_[0].value.as < std::string > ())};
    }
#line 2437 "src/parser.cpp"
    break;

  case 100: // node_block: OBRACE CBRACE
#line 428 "gen/parser.y"
                  {
        yylhs.value.as < cynth::ast::node::Block > () = {};
    }
#line 2445 "src/parser.cpp"
    break;

  case 101: // node_block: OBRACE stmt_list CBRACE
#line 431 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::node::Block > () = {YY_MOVE (yystack_[1].value.as < cynth::ast::node::component_vector<cynth::ast::category::Statement> > ())};
    }
#line 2453 "src/parser.cpp"
    break;

  case 102: // node_block: OBRACE stmt_list SEMI CBRACE
#line 434 "gen/parser.y"
                                       {
        yylhs.value.as < cynth::ast::node::Block > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::node::component_vector<cynth::ast::category::Statement> > ())};
    }
#line 2461 "src/parser.cpp"
    break;

  case 103: // node_bool: TRUE
#line 441 "gen/parser.y"
         {
        yylhs.value.as < cynth::ast::node::Bool > () = {true};
    }
#line 2469 "src/parser.cpp"
    break;

  case 104: // node_bool: FALSE
#line 444 "gen/parser.y"
          {
        yylhs.value.as < cynth::ast::node::Bool > () = {false};
    }
#line 2477 "src/parser.cpp"
    break;

  case 105: // node_int: INT
#line 449 "gen/parser.y"
        {
        yylhs.value.as < cynth::ast::node::Int > () = {cynth::util::stoi(YY_MOVE (yystack_[0].value.as < std::string > ()))};
    }
#line 2485 "src/parser.cpp"
    break;

  case 106: // node_float: FLOAT
#line 454 "gen/parser.y"
          {
        yylhs.value.as < cynth::ast::node::Float > () = {std::stof(YY_MOVE (yystack_[0].value.as < std::string > ()))};
    }
#line 2493 "src/parser.cpp"
    break;

  case 107: // node_string: STRING
#line 459 "gen/parser.y"
           {
        yylhs.value.as < cynth::ast::node::String > () = {cynth::util::trim(YY_MOVE (yystack_[0].value.as < std::string > ()))};
    }
#line 2501 "src/parser.cpp"
    break;

  case 108: // node_function: cat_type FN paren_decl cat_expression
#line 464 "gen/parser.y"
                                                         {
        yylhs.value.as < cynth::ast::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2509 "src/parser.cpp"
    break;

  case 109: // node_function: void_type FN paren_decl cat_expression
#line 467 "gen/parser.y"
                                                          {
        yylhs.value.as < cynth::ast::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2517 "src/parser.cpp"
    break;

  case 110: // node_function: cat_type FN void_decl cat_expression
#line 470 "gen/parser.y"
                                                        {
        yylhs.value.as < cynth::ast::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2525 "src/parser.cpp"
    break;

  case 111: // node_function: void_type FN void_decl cat_expression
#line 473 "gen/parser.y"
                                                         {
        yylhs.value.as < cynth::ast::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2533 "src/parser.cpp"
    break;

  case 112: // node_array: OBRACK CBRACK
#line 478 "gen/parser.y"
                  {
        yylhs.value.as < cynth::ast::node::Array > () = {};
    }
#line 2541 "src/parser.cpp"
    break;

  case 113: // node_array: OBRACK array_elem_list CBRACK
#line 481 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::node::Array > () = {YY_MOVE (yystack_[1].value.as < cynth::ast::node::component_vector<cynth::ast::category::ArrayElem> > ())};
    }
#line 2549 "src/parser.cpp"
    break;

  case 114: // node_array: OBRACK array_elem_list SEMI CBRACK
#line 484 "gen/parser.y"
                                             {
        yylhs.value.as < cynth::ast::node::Array > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::node::component_vector<cynth::ast::category::ArrayElem> > ())};
    }
#line 2557 "src/parser.cpp"
    break;

  case 115: // node_or: expr_or OR expr_and
#line 491 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::node::Or > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2565 "src/parser.cpp"
    break;

  case 116: // node_and: expr_and AND expr_eq
#line 496 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::And > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2573 "src/parser.cpp"
    break;

  case 117: // node_eq: expr_eq EQ expr_ord
#line 501 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::node::Eq > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2581 "src/parser.cpp"
    break;

  case 118: // node_ne: expr_eq NE expr_ord
#line 506 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::node::Ne > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2589 "src/parser.cpp"
    break;

  case 119: // node_ge: expr_ord GE expr_add
#line 511 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Ge > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2597 "src/parser.cpp"
    break;

  case 120: // node_le: expr_ord LE expr_add
#line 516 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Le > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2605 "src/parser.cpp"
    break;

  case 121: // node_gt: expr_ord GT expr_add
#line 521 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Gt > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2613 "src/parser.cpp"
    break;

  case 122: // node_lt: expr_ord LT expr_add
#line 526 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Lt > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2621 "src/parser.cpp"
    break;

  case 123: // node_add: expr_add ADD expr_mul
#line 531 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Add > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2629 "src/parser.cpp"
    break;

  case 124: // node_sub: expr_add SUB expr_mul
#line 536 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Sub > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2637 "src/parser.cpp"
    break;

  case 125: // node_mul: expr_mul MUL expr_pow
#line 541 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Mul > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2645 "src/parser.cpp"
    break;

  case 126: // node_div: expr_mul DIV expr_pow
#line 546 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Div > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2653 "src/parser.cpp"
    break;

  case 127: // node_mod: expr_mul MOD expr_pow
#line 551 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Mod > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2661 "src/parser.cpp"
    break;

  case 128: // node_pow: expr_pre POW expr_pow
#line 556 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Pow > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2669 "src/parser.cpp"
    break;

  case 129: // node_minus: SUB expr_pre
#line 561 "gen/parser.y"
                      {
        yylhs.value.as < cynth::ast::node::Minus > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2677 "src/parser.cpp"
    break;

  case 130: // node_plus: ADD expr_pre
#line 566 "gen/parser.y"
                      {
        yylhs.value.as < cynth::ast::node::Plus > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2685 "src/parser.cpp"
    break;

  case 131: // node_not: NOT expr_pre
#line 571 "gen/parser.y"
                      {
        yylhs.value.as < cynth::ast::node::Not > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2693 "src/parser.cpp"
    break;

  case 132: // node_application: expr_post paren_expr
#line 576 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::ast::node::Application > () = {.function = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ()), .arguments = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2701 "src/parser.cpp"
    break;

  case 133: // node_application: expr_post void
#line 579 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::node::Application > () = {.function = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ()), .arguments = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2709 "src/parser.cpp"
    break;

  case 134: // node_conversion: cat_type paren_expr
#line 584 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::node::Conversion > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()), .argument = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2717 "src/parser.cpp"
    break;

  case 135: // node_subscript: expr_post OBRACK array_elem_list CBRACK
#line 589 "gen/parser.y"
                                                                 {
        yylhs.value.as < cynth::ast::node::Subscript > () = {.container = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Expression > ()), .location = YY_MOVE (yystack_[1].value.as < cynth::ast::node::component_vector<cynth::ast::category::ArrayElem> > ())};
    }
#line 2725 "src/parser.cpp"
    break;

  case 136: // node_expr_if: IF paren_expr cat_expression ELSE cat_expression
#line 594 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::ast::node::ExprIf > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Expression > ()), .positive_branch = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), .negative_branch = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2733 "src/parser.cpp"
    break;

  case 137: // node_definition: cat_declaration ASSGN cat_expression
#line 601 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::ast::node::Definition > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Declaration > ()), .value = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2741 "src/parser.cpp"
    break;

  case 138: // node_assignment: cat_expression ASSGN cat_expression
#line 606 "gen/parser.y"
                                                     {
        yylhs.value.as < cynth::ast::node::Assignment > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), .value = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2749 "src/parser.cpp"
    break;

  case 139: // node_type_def: TYPE node_type_name ASSGN cat_type
#line 611 "gen/parser.y"
                                                     {
        yylhs.value.as < cynth::ast::node::TypeDef > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::ast::node::TypeName > ()), .type = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2757 "src/parser.cpp"
    break;

  case 140: // node_function_def: cat_type node_name paren_decl cat_expression
#line 616 "gen/parser.y"
                                                                      {
        yylhs.value.as < cynth::ast::node::FunctionDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2765 "src/parser.cpp"
    break;

  case 141: // node_function_def: void_type node_name paren_decl cat_expression
#line 619 "gen/parser.y"
                                                                       {
        yylhs.value.as < cynth::ast::node::FunctionDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2773 "src/parser.cpp"
    break;

  case 142: // node_function_def: cat_type node_name void_decl cat_expression
#line 622 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::ast::node::FunctionDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2781 "src/parser.cpp"
    break;

  case 143: // node_function_def: void_type node_name void_decl cat_expression
#line 625 "gen/parser.y"
                                                                      {
        yylhs.value.as < cynth::ast::node::FunctionDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2789 "src/parser.cpp"
    break;

  case 144: // node_return: RETURN cat_expression
#line 630 "gen/parser.y"
                               {
        yylhs.value.as < cynth::ast::node::Return > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2797 "src/parser.cpp"
    break;

  case 145: // node_return: RETURN void
#line 633 "gen/parser.y"
                     {
        yylhs.value.as < cynth::ast::node::Return > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2805 "src/parser.cpp"
    break;

  case 146: // node_return: RETURN
#line 636 "gen/parser.y"
           {
        yylhs.value.as < cynth::ast::node::Return > () = {cynth::ast::category::Expression{cynth::ast::node::Tuple{}}};
    }
#line 2813 "src/parser.cpp"
    break;

  case 147: // node_if: IF paren_expr pure ELSE pure
#line 641 "gen/parser.y"
                                                 {
        yylhs.value.as < cynth::ast::node::If > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Expression > ()), .positive_branch = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Statement > ()), .negative_branch = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ())};
    }
#line 2821 "src/parser.cpp"
    break;

  case 148: // node_when: WHEN paren_expr cat_statement
#line 646 "gen/parser.y"
                                             {
        yylhs.value.as < cynth::ast::node::When > () = {.condition = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ()), .branch = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ())};
    }
#line 2829 "src/parser.cpp"
    break;

  case 149: // array_elem_list: cat_array_elem
#line 653 "gen/parser.y"
                          {
        yylhs.value.as < cynth::ast::node::component_vector<cynth::ast::category::ArrayElem> > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::ArrayElem > ())};
    }
#line 2837 "src/parser.cpp"
    break;

  case 150: // array_elem_list: array_elem_list COMMA cat_array_elem
#line 656 "gen/parser.y"
                                                     {
        yylhs.value.as < cynth::ast::node::component_vector<cynth::ast::category::ArrayElem> > () = cynth::util::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::ArrayElem > ()), YY_MOVE (yystack_[2].value.as < cynth::ast::node::component_vector<cynth::ast::category::ArrayElem> > ()));
    }
#line 2845 "src/parser.cpp"
    break;

  case 151: // stmt_list: cat_statement
#line 661 "gen/parser.y"
                         {
        yylhs.value.as < cynth::ast::node::component_vector<cynth::ast::category::Statement> > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ())};
    }
#line 2853 "src/parser.cpp"
    break;

  case 152: // stmt_list: stmt_list SEMI cat_statement
#line 664 "gen/parser.y"
                                             {
        yylhs.value.as < cynth::ast::node::component_vector<cynth::ast::category::Statement> > () = cynth::util::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ()), YY_MOVE (yystack_[2].value.as < cynth::ast::node::component_vector<cynth::ast::category::Statement> > ()));
    }
#line 2861 "src/parser.cpp"
    break;

  case 153: // type_list: cat_type COMMA cat_type
#line 669 "gen/parser.y"
                                           {
        yylhs.value.as < cynth::ast::node::component_vector<cynth::ast::category::Type> > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Type > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2869 "src/parser.cpp"
    break;

  case 154: // type_list: type_list COMMA cat_type
#line 672 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::ast::node::component_vector<cynth::ast::category::Type> > () = cynth::util::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()), YY_MOVE (yystack_[2].value.as < cynth::ast::node::component_vector<cynth::ast::category::Type> > ()));
    }
#line 2877 "src/parser.cpp"
    break;

  case 155: // expr_list: cat_expression COMMA cat_expression
#line 677 "gen/parser.y"
                                                       {
        yylhs.value.as < cynth::ast::node::component_vector<cynth::ast::category::Expression> > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2885 "src/parser.cpp"
    break;

  case 156: // expr_list: expr_list COMMA cat_expression
#line 680 "gen/parser.y"
                                               {
        yylhs.value.as < cynth::ast::node::component_vector<cynth::ast::category::Expression> > () = cynth::util::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[2].value.as < cynth::ast::node::component_vector<cynth::ast::category::Expression> > ()));
    }
#line 2893 "src/parser.cpp"
    break;

  case 157: // decl_list: cat_declaration COMMA cat_declaration
#line 685 "gen/parser.y"
                                                         {
        yylhs.value.as < cynth::ast::node::component_vector<cynth::ast::category::Declaration> > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Declaration > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Declaration > ())};
    }
#line 2901 "src/parser.cpp"
    break;

  case 158: // decl_list: decl_list COMMA cat_declaration
#line 688 "gen/parser.y"
                                                {
        yylhs.value.as < cynth::ast::node::component_vector<cynth::ast::category::Declaration> > () = cynth::util::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Declaration > ()), YY_MOVE (yystack_[2].value.as < cynth::ast::node::component_vector<cynth::ast::category::Declaration> > ()));
    }
#line 2909 "src/parser.cpp"
    break;


#line 2913 "src/parser.cpp"

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





  const signed char parser::yypact_ninf_ = -126;

  const signed char parser::yytable_ninf_ = -74;

  const short
  parser::yypact_[] =
  {
     425,  -126,  -126,  -126,  -126,  -126,   -20,   -20,     4,    49,
     740,  -126,  -126,  -126,   495,    38,   460,   290,   290,   290,
      23,    47,    71,    73,  -126,  -126,    62,    74,    17,   196,
     118,    96,  -126,    79,     8,  -126,  -126,  -126,    70,  -126,
    -126,  -126,  -126,  -126,  -126,  -126,  -126,   108,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,   132,   775,   425,   425,   162,
     775,   -20,     4,   530,    97,  -126,    -5,  -126,  -126,    81,
      34,    53,  -126,    59,    82,    92,  -126,   128,   775,   565,
    -126,  -126,   149,  -126,  -126,  -126,    41,   144,  -126,   158,
    -126,  -126,  -126,   159,  -126,   600,  -126,  -126,  -126,   159,
     775,   775,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   290,   290,   290,   290,   635,   670,  -126,  -126,
     159,   307,  -126,  -126,   159,   425,    -3,   184,  -126,   540,
     164,   775,  -126,    14,    99,   540,  -126,  -126,   575,  -126,
     775,  -126,   394,  -126,   433,  -126,   705,  -126,   341,  -126,
    -126,   775,   175,   670,  -126,   468,   775,   775,   178,  -126,
      47,   180,   181,   775,   775,  -126,  -126,    74,    17,   196,
     196,   118,   118,   118,   118,    96,    96,  -126,  -126,  -126,
    -126,  -126,     1,   775,   775,   253,   775,   775,  -126,   775,
     425,   174,  -126,   195,   174,   505,     7,  -126,  -126,  -126,
     174,  -126,  -126,  -126,  -126,  -126,   189,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,    73,  -126,   206,   775,  -126
  };

  const unsigned char
  parser::yydefact_[] =
  {
       2,    99,    75,   105,   106,   107,     0,     0,     0,     0,
     146,   103,   104,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,   151,    21,    19,    32,    34,    37,
      42,    45,    49,    51,    55,    59,    20,    18,     0,    11,
      12,    17,    13,    14,    15,    16,     6,    23,    67,    60,
      65,    61,    62,    63,    64,    69,    66,    31,    33,    35,
      36,    38,    39,    40,    41,    43,    44,    46,    47,    48,
      50,    53,    52,    54,    56,    57,    58,    68,    24,    25,
      27,    26,    28,    29,    30,     3,     0,     0,     0,    86,
       0,     0,     0,     0,     0,   144,     0,   145,    73,     0,
       0,     0,     5,     0,     0,     0,   100,     0,     0,     0,
     112,   149,    10,     7,     8,     9,     0,     0,   130,     0,
     129,   131,     1,     0,    76,     0,    77,    79,   134,    91,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   132,   133,
       0,     0,    78,    80,     0,     4,     0,     0,   148,     0,
       0,     0,    86,    98,     0,     0,    70,    91,     0,    87,
       0,    95,     0,    71,     0,    88,     0,    96,     0,   101,
      94,     0,     0,     0,   113,     0,     0,     0,    74,    83,
       0,     0,     0,     0,     0,   137,   138,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,    98,     0,     0,     0,     0,     0,     0,   152,     0,
       0,   139,    85,     0,   153,     0,     0,   157,   155,    72,
     154,    89,   158,    97,   156,   102,    92,   114,   150,    90,
     108,   110,    82,    84,    81,   140,   142,   135,   109,   111,
     141,   143,   136,     0,   147,     0,     0,    93
  };

  const short
  parser::yypgoto_[] =
  {
    -126,  -126,   249,    21,    36,    67,   -87,   -73,  -126,    85,
      89,    28,   152,    26,   186,   169,  -126,  -126,  -126,    83,
       0,  -126,    -6,  -126,  -126,  -126,  -126,  -126,  -120,  -125,
      33,  -126,  -126,  -126,     6,   199,   -10,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,    87,  -126,   214
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,    20,    94,    22,   111,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      96,    39,    40,    41,    42,    43,    44,    45,    46,   187,
      47,   113,   114,   115,    48,    97,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,   103,   104,   116,   105,    85
  };

  const short
  parser::yytable_[] =
  {
      38,   158,    89,   186,   194,    86,   219,   150,     2,   193,
       1,   129,    87,    88,   157,    38,   131,   119,   119,   119,
     151,   127,   183,   122,   124,   214,   -73,   128,   154,   217,
     213,   247,   151,   146,   216,   100,   125,   147,   153,   -73,
     148,     1,     2,     3,     4,     5,     6,   102,     7,     8,
       1,     9,    10,    11,    12,   168,    13,   134,   135,   123,
     169,   182,   183,    14,   124,    15,   106,    16,   218,    17,
      18,   184,   109,     1,   170,    19,   125,    95,    90,   171,
     172,   101,   150,   112,     1,   173,   162,    38,    38,   167,
     130,   218,   131,   123,   127,   151,   153,   161,   124,   127,
     128,   132,   165,   174,   126,   128,   109,   166,   175,   123,
     125,   123,   133,   176,   124,   145,   124,   127,   177,   153,
     165,   152,   109,   128,   109,   166,   125,    -5,   125,   142,
     143,   144,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   191,   254,   178,   140,
     141,   119,   155,   101,   156,    38,   179,   160,   102,   119,
     101,   124,   199,   200,   127,   119,   205,   206,   119,   109,
     128,   181,   119,   125,   119,   180,   101,   126,    38,   152,
     167,   159,   126,   151,   185,   119,   118,   120,   121,   227,
     127,   124,   192,   220,   222,   232,   128,   195,   196,   151,
     126,   102,   152,   125,   219,   237,   100,   102,   242,     1,
     243,   244,   256,   101,   112,   127,   167,   197,   102,   238,
      38,   127,   198,   124,   127,   119,   127,   165,   223,   107,
     127,   151,   166,   149,   212,   125,     0,   228,   136,   137,
     138,   139,     0,   234,     0,   167,   100,   126,   236,    21,
     112,     0,     0,   240,   241,   127,     0,     0,   102,     0,
     245,   246,     0,    99,    21,     0,   117,   117,   117,     0,
     124,     0,     0,   126,   165,     0,     0,     0,   151,   166,
     248,   249,   125,   250,   251,     0,   252,   253,   201,   202,
     203,   204,     0,     1,     2,     3,     4,     5,   126,     0,
       0,    92,     0,     9,   126,    11,    12,   126,    13,   126,
       0,     2,     0,   126,     0,   109,     0,    15,    92,    16,
       9,    17,    18,   257,     0,    13,     0,    19,   207,   208,
     209,   210,   151,    98,     0,     0,    21,    21,   126,     0,
       0,     0,   164,     0,     1,     2,     3,     4,     5,     6,
       0,     7,     8,     0,     9,    10,    11,    12,   164,    13,
       0,     0,     0,     0,     0,     0,    14,     0,    15,   235,
      16,     0,    17,    18,   190,     0,     0,     0,    19,     0,
       0,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,     0,     0,     0,     2,     0,
     215,     0,     0,     0,    21,    92,     0,     9,   221,     0,
       0,     0,    13,     0,   224,     0,     0,   226,     0,   151,
     229,   230,     0,   226,     0,     0,     0,    21,     1,     2,
       3,     4,     5,     6,   226,     7,     8,     2,     9,    10,
      11,    12,     0,    13,    92,     0,     9,     0,     0,     0,
      14,    13,    15,     0,    16,     0,    17,    18,   225,   231,
       0,     0,    19,     1,     2,     3,     4,     5,    91,    21,
       0,    92,     2,     9,   255,    11,    12,     0,    13,    92,
       0,     9,     0,     0,   108,   109,    13,    15,     0,    16,
     110,    17,    18,   225,   239,     0,     0,    19,     1,     2,
       3,     4,     5,    91,     0,     0,    92,     0,     9,     2,
      11,    12,     0,    13,     0,     0,    92,     0,     9,     0,
      14,    98,    15,    13,    16,     0,    17,    18,     0,     0,
     225,    98,    19,     1,     2,     3,     4,     5,    91,     0,
       0,    92,     0,     9,     2,    11,    12,     0,    13,     0,
       0,    92,     0,     9,     0,   109,   163,    15,    13,    16,
       0,    17,    18,     0,     0,   151,     0,    19,     1,     2,
       3,     4,     5,    91,     0,     0,    92,     0,     9,     2,
      11,    12,     0,    13,     0,     0,    92,     0,     9,     0,
     109,    98,    15,    13,    16,     0,    17,    18,     0,     0,
     225,     0,    19,     1,     2,     3,     4,     5,    91,     0,
       0,    92,     0,     9,     0,    11,    12,     0,   188,     0,
       0,     0,     0,     0,     0,    14,     0,    15,     0,    16,
     189,    17,    18,     0,     0,     0,     0,    19,     1,     2,
       3,     4,     5,    91,     0,     0,    92,     0,     9,     0,
      11,    12,     0,    13,     0,     0,     0,     0,     0,     0,
     109,   211,    15,     0,    16,     0,    17,    18,     0,     0,
       0,     0,    19,     1,     2,     3,     4,     5,    91,     0,
       0,    92,     0,     9,     0,    11,    12,     0,    13,     0,
       0,     0,     0,     0,   108,   109,     0,    15,     0,    16,
       0,    17,    18,     0,     0,     0,     0,    19,     1,     2,
       3,     4,     5,    91,     0,     0,    92,     0,     9,     0,
      11,    12,     0,    13,     0,     0,     0,     0,     0,     0,
     109,   233,    15,     0,    16,     0,    17,    18,     0,     0,
       0,     0,    19,     1,     2,     3,     4,     5,    91,     0,
       0,    92,     0,     9,     0,    11,    12,     0,    13,     0,
       0,     0,     0,     0,     0,    93,     0,    15,     0,    16,
       0,    17,    18,     0,     0,     0,     0,    19,     1,     2,
       3,     4,     5,    91,     0,     0,    92,     0,     9,     0,
      11,    12,     0,    13,     0,     0,     0,     0,     0,     0,
     109,     0,    15,     0,    16,     0,    17,    18,     0,     0,
       0,     0,    19
  };

  const short
  parser::yycheck_[] =
  {
       0,    88,     8,   123,   129,    25,     9,    12,     4,   129,
       3,    21,     6,     7,    87,    15,    19,    17,    18,    19,
      25,    21,    21,     0,    17,   150,    12,    21,    38,   154,
     150,    30,    25,    25,   154,    14,    29,    29,    38,    25,
      34,     3,     4,     5,     6,     7,     8,    14,    10,    11,
       3,    13,    14,    15,    16,    21,    18,    40,    41,    12,
      26,    20,    21,    25,    17,    27,    28,    29,   155,    31,
      32,    30,    25,     3,    21,    37,    29,    10,    29,    26,
      21,    14,    12,    16,     3,    26,    92,    87,    88,    99,
      19,   178,    19,    12,    94,    25,    96,    91,    17,    99,
      94,    39,    21,    21,    21,    99,    25,    26,    26,    12,
      29,    12,    38,    21,    17,    36,    17,   117,    26,   119,
      21,    38,    25,   117,    25,    26,    29,    19,    29,    33,
      34,    35,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   125,   220,    20,    31,
      32,   151,    20,    86,    87,   155,    28,    90,   125,   159,
      93,    17,   134,   135,   164,   165,   140,   141,   168,    25,
     164,    22,   172,    29,   174,   108,   109,    94,   178,    96,
     190,    19,    99,    25,    25,   185,    17,    18,    19,   168,
     190,    17,   125,     9,    30,   174,   190,   130,   131,    25,
     117,   168,   119,    29,     9,    30,   185,   174,    30,     3,
      30,    30,    23,   146,   147,   215,   226,   132,   185,   183,
     220,   221,   133,    17,   224,   225,   226,    21,   161,    15,
     230,    25,    26,    34,   147,    29,    -1,   170,    42,    43,
      44,    45,    -1,   176,    -1,   255,   225,   164,   181,     0,
     183,    -1,    -1,   186,   187,   255,    -1,    -1,   225,    -1,
     193,   194,    -1,    14,    15,    -1,    17,    18,    19,    -1,
      17,    -1,    -1,   190,    21,    -1,    -1,    -1,    25,    26,
     213,   214,    29,   216,   217,    -1,   219,   220,   136,   137,
     138,   139,    -1,     3,     4,     5,     6,     7,   215,    -1,
      -1,    11,    -1,    13,   221,    15,    16,   224,    18,   226,
      -1,     4,    -1,   230,    -1,    25,    -1,    27,    11,    29,
      13,    31,    32,   256,    -1,    18,    -1,    37,   142,   143,
     144,   145,    25,    26,    -1,    -1,    87,    88,   255,    -1,
      -1,    -1,    93,    -1,     3,     4,     5,     6,     7,     8,
      -1,    10,    11,    -1,    13,    14,    15,    16,   109,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    28,
      29,    -1,    31,    32,   125,    -1,    -1,    -1,    37,    -1,
      -1,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,    -1,    -1,    -1,     4,    -1,
     151,    -1,    -1,    -1,   155,    11,    -1,    13,   159,    -1,
      -1,    -1,    18,    -1,   165,    -1,    -1,   168,    -1,    25,
      26,   172,    -1,   174,    -1,    -1,    -1,   178,     3,     4,
       5,     6,     7,     8,   185,    10,    11,     4,    13,    14,
      15,    16,    -1,    18,    11,    -1,    13,    -1,    -1,    -1,
      25,    18,    27,    -1,    29,    -1,    31,    32,    25,    26,
      -1,    -1,    37,     3,     4,     5,     6,     7,     8,   220,
      -1,    11,     4,    13,   225,    15,    16,    -1,    18,    11,
      -1,    13,    -1,    -1,    24,    25,    18,    27,    -1,    29,
      30,    31,    32,    25,    26,    -1,    -1,    37,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    13,     4,
      15,    16,    -1,    18,    -1,    -1,    11,    -1,    13,    -1,
      25,    26,    27,    18,    29,    -1,    31,    32,    -1,    -1,
      25,    26,    37,     3,     4,     5,     6,     7,     8,    -1,
      -1,    11,    -1,    13,     4,    15,    16,    -1,    18,    -1,
      -1,    11,    -1,    13,    -1,    25,    26,    27,    18,    29,
      -1,    31,    32,    -1,    -1,    25,    -1,    37,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    13,     4,
      15,    16,    -1,    18,    -1,    -1,    11,    -1,    13,    -1,
      25,    26,    27,    18,    29,    -1,    31,    32,    -1,    -1,
      25,    -1,    37,     3,     4,     5,     6,     7,     8,    -1,
      -1,    11,    -1,    13,    -1,    15,    16,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    29,
      30,    31,    32,    -1,    -1,    -1,    -1,    37,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    13,    -1,
      15,    16,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    26,    27,    -1,    29,    -1,    31,    32,    -1,    -1,
      -1,    -1,    37,     3,     4,     5,     6,     7,     8,    -1,
      -1,    11,    -1,    13,    -1,    15,    16,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    24,    25,    -1,    27,    -1,    29,
      -1,    31,    32,    -1,    -1,    -1,    -1,    37,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    13,    -1,
      15,    16,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    26,    27,    -1,    29,    -1,    31,    32,    -1,    -1,
      -1,    -1,    37,     3,     4,     5,     6,     7,     8,    -1,
      -1,    11,    -1,    13,    -1,    15,    16,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    29,
      -1,    31,    32,    -1,    -1,    -1,    -1,    37,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    13,    -1,
      15,    16,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    29,    -1,    31,    32,    -1,    -1,
      -1,    -1,    37
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,     8,    10,    11,    13,
      14,    15,    16,    18,    25,    27,    29,    31,    32,    37,
      48,    49,    50,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    77,    81,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   123,    25,    81,    81,    69,
      29,     8,    11,    25,    49,    52,    67,    82,    26,    49,
      50,    52,    77,   119,   120,   122,    28,   123,    24,    25,
      30,    51,    52,    78,    79,    80,   121,    49,    62,    67,
      62,    62,     0,    12,    17,    29,    66,    67,    81,    83,
      19,    19,    39,    38,    40,    41,    42,    43,    44,    45,
      31,    32,    33,    34,    35,    36,    25,    29,    81,    82,
      12,    25,    66,    67,    83,    20,    52,    54,    53,    19,
      52,    81,    69,    26,    49,    21,    26,    83,    21,    26,
      21,    26,    21,    26,    21,    26,    21,    26,    20,    28,
      52,    22,    20,    21,    30,    25,    75,    76,    18,    30,
      49,    50,    52,    75,    76,    52,    52,    56,    57,    58,
      58,    59,    59,    59,    59,    60,    60,    61,    61,    61,
      61,    26,   121,    75,    76,    49,    75,    76,    53,     9,
       9,    49,    30,    52,    49,    25,    49,    50,    52,    26,
      49,    26,    50,    26,    52,    28,    52,    30,    51,    26,
      52,    52,    30,    30,    30,    52,    52,    30,    52,    52,
      52,    52,    52,    52,    54,    49,    23,    52
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    47,    48,    48,    48,    50,    50,    51,    51,    51,
      51,    49,    49,    49,    49,    49,    49,    49,    49,    52,
      52,    53,    53,    54,    54,    54,    54,    54,    54,    54,
      54,    55,    55,    56,    56,    57,    57,    57,    58,    58,
      58,    58,    58,    59,    59,    59,    60,    60,    60,    60,
      61,    61,    62,    62,    62,    62,    63,    63,    63,    63,
      64,    64,    64,    64,    64,    64,    64,    64,    65,    65,
      66,    66,    66,    67,    68,    69,    70,    71,    71,    71,
      71,    72,    72,    72,    72,    73,    74,    75,    75,    75,
      76,    77,    78,    79,    80,    81,    81,    81,    82,    83,
      84,    84,    84,    85,    85,    86,    87,    88,    89,    89,
      89,    89,    90,    90,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   106,
     105,   107,   108,   108,   109,   110,   111,   112,   113,   115,
     114,   114,   114,   114,   116,   116,   116,   117,   118,   121,
     121,   123,   123,   119,   119,   122,   122,   120,   120
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     4,     2,     1,     1,     2,     2,     2,     2,
       2,     4,     4,     3,     4,     4,     2,     3,     3,     4,
       2,     2,     3,     5,     2,     3,     3,     4,     2,     1,
       2,     3,     4,     1,     1,     1,     1,     1,     4,     4,
       4,     4,     2,     3,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     2,     2,     4,     5,     3,     3,     4,
       4,     4,     4,     4,     2,     2,     1,     5,     3,     1,
       3,     1,     3,     3,     3,     3,     3,     3,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "NAME", "TYPENAME",
  "INT", "FLOAT", "STRING", "IF", "ELSE", "WHEN", "TYPE", "FN", "BUFFER",
  "RETURN", "TRUE", "FALSE", "CONST", "AUTO", "ASSGN", "SEMI", "COMMA",
  "TO", "BY", "ELIP", "OPAREN", "CPAREN", "OBRACE", "CBRACE", "OBRACK",
  "CBRACK", "ADD", "SUB", "MUL", "DIV", "MOD", "POW", "NOT", "AND", "OR",
  "EQ", "NE", "GE", "LE", "GT", "LT", "ILLEGAL", "$accept", "start",
  "cat_type", "cat_declaration", "cat_array_elem", "cat_expression",
  "cat_statement", "pure", "expr_or", "expr_and", "expr_eq", "expr_ord",
  "expr_add", "expr_mul", "expr_pow", "expr_pre", "expr_post", "expr_atom",
  "expr_right", "paren_type", "void_type", "node_auto", "node_type_name",
  "node_const_type", "node_function_type", "node_array_type",
  "node_buffer_type", "node_type_decl", "paren_decl", "void_decl",
  "node_declaration", "node_range_to", "node_range_to_by", "node_spread",
  "paren_expr", "void", "node_name", "node_block", "node_bool", "node_int",
  "node_float", "node_string", "node_function", "node_array", "node_or",
  "node_and", "node_eq", "node_ne", "node_ge", "node_le", "node_gt",
  "node_lt", "node_add", "node_sub", "node_mul", "node_div", "node_mod",
  "node_pow", "node_plus", "node_minus", "node_not", "node_application",
  "node_conversion", "node_subscript", "node_expr_if", "node_definition",
  "node_assignment", "node_function_def", "node_type_def", "node_return",
  "node_if", "node_when", "type_list", "decl_list", "array_elem_list",
  "expr_list", "stmt_list", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   177,   177,   183,   186,   193,   194,   197,   198,   199,
     200,   203,   204,   205,   206,   207,   208,   209,   210,   213,
     214,   217,   218,   223,   224,   225,   226,   227,   228,   229,
     230,   233,   234,   237,   238,   241,   242,   243,   246,   247,
     248,   249,   250,   253,   254,   255,   258,   259,   260,   261,
     264,   265,   268,   269,   270,   271,   274,   275,   276,   277,
     280,   281,   282,   283,   284,   285,   286,   287,   290,   291,
     296,   299,   302,   307,   312,   317,   322,   327,   330,   333,
     336,   341,   344,   347,   350,   355,   360,   367,   370,   373,
     378,   383,   390,   395,   400,   407,   410,   413,   418,   423,
     428,   431,   434,   441,   444,   449,   454,   459,   464,   467,
     470,   473,   478,   481,   484,   491,   496,   501,   506,   511,
     516,   521,   526,   531,   536,   541,   546,   551,   556,   561,
     566,   571,   576,   579,   584,   589,   594,   601,   606,   611,
     616,   619,   622,   625,   630,   633,   636,   641,   646,   653,
     656,   661,   664,   669,   672,   677,   680,   685,   688
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
#line 3521 "src/parser.cpp"

#line 692 "gen/parser.y"


void yy::parser::error (std::string const & msg) {
    std::cerr << msg << '\n';
}
