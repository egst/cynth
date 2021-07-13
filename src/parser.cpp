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

      case symbol_kind::S_node_in_type: // node_in_type
        value.YY_MOVE_OR_COPY< cynth::ast::node::InType > (YY_MOVE (that.value));
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

      case symbol_kind::S_node_out_type: // node_out_type
        value.YY_MOVE_OR_COPY< cynth::ast::node::OutType > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< cynth::component_vector<cynth::ast::category::ArrayElem> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.YY_MOVE_OR_COPY< cynth::component_vector<cynth::ast::category::Declaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.YY_MOVE_OR_COPY< cynth::component_vector<cynth::ast::category::Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.YY_MOVE_OR_COPY< cynth::component_vector<cynth::ast::category::Statement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_list: // type_list
        value.YY_MOVE_OR_COPY< cynth::component_vector<cynth::ast::category::Type> > (YY_MOVE (that.value));
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

      case symbol_kind::S_node_in_type: // node_in_type
        value.move< cynth::ast::node::InType > (YY_MOVE (that.value));
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

      case symbol_kind::S_node_out_type: // node_out_type
        value.move< cynth::ast::node::OutType > (YY_MOVE (that.value));
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
        value.move< cynth::component_vector<cynth::ast::category::ArrayElem> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< cynth::component_vector<cynth::ast::category::Declaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< cynth::component_vector<cynth::ast::category::Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< cynth::component_vector<cynth::ast::category::Statement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_list: // type_list
        value.move< cynth::component_vector<cynth::ast::category::Type> > (YY_MOVE (that.value));
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

      case symbol_kind::S_node_in_type: // node_in_type
        value.copy< cynth::ast::node::InType > (that.value);
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

      case symbol_kind::S_node_out_type: // node_out_type
        value.copy< cynth::ast::node::OutType > (that.value);
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
        value.copy< cynth::component_vector<cynth::ast::category::ArrayElem> > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.copy< cynth::component_vector<cynth::ast::category::Declaration> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.copy< cynth::component_vector<cynth::ast::category::Expression> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< cynth::component_vector<cynth::ast::category::Statement> > (that.value);
        break;

      case symbol_kind::S_type_list: // type_list
        value.copy< cynth::component_vector<cynth::ast::category::Type> > (that.value);
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

      case symbol_kind::S_node_in_type: // node_in_type
        value.move< cynth::ast::node::InType > (that.value);
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

      case symbol_kind::S_node_out_type: // node_out_type
        value.move< cynth::ast::node::OutType > (that.value);
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
        value.move< cynth::component_vector<cynth::ast::category::ArrayElem> > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< cynth::component_vector<cynth::ast::category::Declaration> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< cynth::component_vector<cynth::ast::category::Expression> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< cynth::component_vector<cynth::ast::category::Statement> > (that.value);
        break;

      case symbol_kind::S_type_list: // type_list
        value.move< cynth::component_vector<cynth::ast::category::Type> > (that.value);
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

      case symbol_kind::S_node_in_type: // node_in_type
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

      case symbol_kind::S_node_out_type: // node_out_type
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
        yylhs.value.emplace< cynth::component_vector<cynth::ast::category::ArrayElem> > ();
        break;

      case symbol_kind::S_decl_list: // decl_list
        yylhs.value.emplace< cynth::component_vector<cynth::ast::category::Declaration> > ();
        break;

      case symbol_kind::S_expr_list: // expr_list
        yylhs.value.emplace< cynth::component_vector<cynth::ast::category::Expression> > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        yylhs.value.emplace< cynth::component_vector<cynth::ast::category::Statement> > ();
        break;

      case symbol_kind::S_type_list: // type_list
        yylhs.value.emplace< cynth::component_vector<cynth::ast::category::Type> > ();
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
#line 188 "gen/parser.y"
           {
        result = {};
    }
#line 1831 "src/parser.cpp"
    break;

  case 3: // start: stmt_list
#line 191 "gen/parser.y"
                    {
        result = {YY_MOVE (yystack_[0].value.as < cynth::component_vector<cynth::ast::category::Statement> > ())};
    }
#line 1839 "src/parser.cpp"
    break;

  case 4: // start: stmt_list SEMI
#line 194 "gen/parser.y"
                         {
        result = {YY_MOVE (yystack_[1].value.as < cynth::component_vector<cynth::ast::category::Statement> > ())};
    }
#line 1847 "src/parser.cpp"
    break;

  case 5: // cat_declaration: node_declaration
#line 201 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Declaration > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Declaration > ()); }
#line 1853 "src/parser.cpp"
    break;

  case 6: // cat_declaration: paren_decl
#line 202 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Declaration > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Declaration > ()); }
#line 1859 "src/parser.cpp"
    break;

  case 7: // cat_array_elem: node_range_to
#line 205 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::ArrayElem > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::RangeTo > ()); }
#line 1865 "src/parser.cpp"
    break;

  case 8: // cat_array_elem: node_range_to_by
#line 206 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::ArrayElem > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::RangeToBy > ()); }
#line 1871 "src/parser.cpp"
    break;

  case 9: // cat_array_elem: node_spread
#line 207 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::ArrayElem > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Spread > ()); }
#line 1877 "src/parser.cpp"
    break;

  case 10: // cat_array_elem: cat_expression
#line 208 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::ArrayElem > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1883 "src/parser.cpp"
    break;

  case 11: // cat_type: node_auto
#line 211 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Auto > ()); }
#line 1889 "src/parser.cpp"
    break;

  case 12: // cat_type: node_type_name
#line 212 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeName > ()); }
#line 1895 "src/parser.cpp"
    break;

  case 13: // cat_type: node_function_type
#line 213 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::FunctionType > ()); }
#line 1901 "src/parser.cpp"
    break;

  case 14: // cat_type: node_array_type
#line 214 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::ArrayType > ()); }
#line 1907 "src/parser.cpp"
    break;

  case 15: // cat_type: node_buffer_type
#line 215 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::BufferType > ()); }
#line 1913 "src/parser.cpp"
    break;

  case 16: // cat_type: node_type_decl
#line 216 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeDecl > ()); }
#line 1919 "src/parser.cpp"
    break;

  case 17: // cat_type: node_const_type
#line 217 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::ConstType > ()); }
#line 1925 "src/parser.cpp"
    break;

  case 18: // cat_type: node_in_type
#line 218 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::InType > ()); }
#line 1931 "src/parser.cpp"
    break;

  case 19: // cat_type: node_out_type
#line 219 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::OutType > ()); }
#line 1937 "src/parser.cpp"
    break;

  case 20: // cat_type: paren_type
#line 220 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()); }
#line 1943 "src/parser.cpp"
    break;

  case 21: // cat_expression: expr_or
#line 223 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1949 "src/parser.cpp"
    break;

  case 22: // cat_expression: expr_right
#line 224 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1955 "src/parser.cpp"
    break;

  case 23: // cat_statement: pure
#line 227 "gen/parser.y"
                   { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ()); }
#line 1961 "src/parser.cpp"
    break;

  case 24: // cat_statement: cat_expression
#line 228 "gen/parser.y"
                   { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 1967 "src/parser.cpp"
    break;

  case 25: // pure: node_declaration
#line 233 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Declaration > ()); }
#line 1973 "src/parser.cpp"
    break;

  case 26: // pure: node_definition
#line 234 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Definition > ()); }
#line 1979 "src/parser.cpp"
    break;

  case 27: // pure: node_assignment
#line 235 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Assignment > ()); }
#line 1985 "src/parser.cpp"
    break;

  case 28: // pure: node_type_def
#line 236 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeDef > ()); }
#line 1991 "src/parser.cpp"
    break;

  case 29: // pure: node_function_def
#line 237 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::FunctionDef > ()); }
#line 1997 "src/parser.cpp"
    break;

  case 30: // pure: node_return
#line 238 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Return > ()); }
#line 2003 "src/parser.cpp"
    break;

  case 31: // pure: node_if
#line 239 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::If > ()); }
#line 2009 "src/parser.cpp"
    break;

  case 32: // pure: node_when
#line 240 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::When > ()); }
#line 2015 "src/parser.cpp"
    break;

  case 33: // expr_or: node_or
#line 243 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Or > ()); }
#line 2021 "src/parser.cpp"
    break;

  case 34: // expr_or: expr_and
#line 244 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2027 "src/parser.cpp"
    break;

  case 35: // expr_and: node_and
#line 247 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::And > ()); }
#line 2033 "src/parser.cpp"
    break;

  case 36: // expr_and: expr_eq
#line 248 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2039 "src/parser.cpp"
    break;

  case 37: // expr_eq: node_eq
#line 251 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Eq > ()); }
#line 2045 "src/parser.cpp"
    break;

  case 38: // expr_eq: node_ne
#line 252 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Ne > ()); }
#line 2051 "src/parser.cpp"
    break;

  case 39: // expr_eq: expr_ord
#line 253 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2057 "src/parser.cpp"
    break;

  case 40: // expr_ord: node_ge
#line 256 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Ge > ()); }
#line 2063 "src/parser.cpp"
    break;

  case 41: // expr_ord: node_le
#line 257 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Le > ()); }
#line 2069 "src/parser.cpp"
    break;

  case 42: // expr_ord: node_gt
#line 258 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Gt > ()); }
#line 2075 "src/parser.cpp"
    break;

  case 43: // expr_ord: node_lt
#line 259 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Lt > ()); }
#line 2081 "src/parser.cpp"
    break;

  case 44: // expr_ord: expr_add
#line 260 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2087 "src/parser.cpp"
    break;

  case 45: // expr_add: node_add
#line 263 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Add > ()); }
#line 2093 "src/parser.cpp"
    break;

  case 46: // expr_add: node_sub
#line 264 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Sub > ()); }
#line 2099 "src/parser.cpp"
    break;

  case 47: // expr_add: expr_mul
#line 265 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2105 "src/parser.cpp"
    break;

  case 48: // expr_mul: node_mul
#line 268 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Mul > ()); }
#line 2111 "src/parser.cpp"
    break;

  case 49: // expr_mul: node_div
#line 269 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Div > ()); }
#line 2117 "src/parser.cpp"
    break;

  case 50: // expr_mul: node_mod
#line 270 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Mod > ()); }
#line 2123 "src/parser.cpp"
    break;

  case 51: // expr_mul: expr_pow
#line 271 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2129 "src/parser.cpp"
    break;

  case 52: // expr_pow: node_pow
#line 274 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Pow > ()); }
#line 2135 "src/parser.cpp"
    break;

  case 53: // expr_pow: expr_pre
#line 275 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2141 "src/parser.cpp"
    break;

  case 54: // expr_pre: node_minus
#line 278 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Minus > ()); }
#line 2147 "src/parser.cpp"
    break;

  case 55: // expr_pre: node_plus
#line 279 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Plus > ()); }
#line 2153 "src/parser.cpp"
    break;

  case 56: // expr_pre: node_not
#line 280 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Not > ()); }
#line 2159 "src/parser.cpp"
    break;

  case 57: // expr_pre: expr_post
#line 281 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2165 "src/parser.cpp"
    break;

  case 58: // expr_post: node_application
#line 284 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Application > ()); }
#line 2171 "src/parser.cpp"
    break;

  case 59: // expr_post: node_conversion
#line 285 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Conversion > ()); }
#line 2177 "src/parser.cpp"
    break;

  case 60: // expr_post: node_subscript
#line 286 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Subscript > ()); }
#line 2183 "src/parser.cpp"
    break;

  case 61: // expr_post: expr_atom
#line 287 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2189 "src/parser.cpp"
    break;

  case 62: // expr_atom: node_name
#line 290 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Name > ()); }
#line 2195 "src/parser.cpp"
    break;

  case 63: // expr_atom: node_bool
#line 291 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Bool > ()); }
#line 2201 "src/parser.cpp"
    break;

  case 64: // expr_atom: node_int
#line 292 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Int > ()); }
#line 2207 "src/parser.cpp"
    break;

  case 65: // expr_atom: node_float
#line 293 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Float > ()); }
#line 2213 "src/parser.cpp"
    break;

  case 66: // expr_atom: node_string
#line 294 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::String > ()); }
#line 2219 "src/parser.cpp"
    break;

  case 67: // expr_atom: node_block
#line 295 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Block > ()); }
#line 2225 "src/parser.cpp"
    break;

  case 68: // expr_atom: node_array
#line 296 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Array > ()); }
#line 2231 "src/parser.cpp"
    break;

  case 69: // expr_atom: paren_expr
#line 297 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2237 "src/parser.cpp"
    break;

  case 70: // expr_right: node_expr_if
#line 300 "gen/parser.y"
                  { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::ExprIf > ()); }
#line 2243 "src/parser.cpp"
    break;

  case 71: // expr_right: node_function
#line 301 "gen/parser.y"
                  { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Function > ()); }
#line 2249 "src/parser.cpp"
    break;

  case 72: // paren_type: OPAREN cat_type CPAREN
#line 306 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ());
    }
#line 2257 "src/parser.cpp"
    break;

  case 73: // paren_type: OPAREN type_list CPAREN
#line 309 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::category::Type > () = cynth::ast::node::TupleType{YY_MOVE (yystack_[1].value.as < cynth::component_vector<cynth::ast::category::Type> > ())};
    }
#line 2265 "src/parser.cpp"
    break;

  case 74: // paren_type: OPAREN type_list COMMA CPAREN
#line 312 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::category::Type > () = cynth::ast::node::TupleType{YY_MOVE (yystack_[2].value.as < cynth::component_vector<cynth::ast::category::Type> > ())};
    }
#line 2273 "src/parser.cpp"
    break;

  case 75: // void_type: OPAREN CPAREN
#line 317 "gen/parser.y"
                  {
        yylhs.value.as < cynth::ast::category::Type > () = cynth::ast::node::TupleType{};
    }
#line 2281 "src/parser.cpp"
    break;

  case 76: // node_auto: AUTO
#line 322 "gen/parser.y"
         {
        yylhs.value.as < cynth::ast::node::Auto > () = {};
    }
#line 2289 "src/parser.cpp"
    break;

  case 77: // node_type_name: TYPENAME
#line 327 "gen/parser.y"
                   {
        yylhs.value.as < cynth::ast::node::TypeName > () = {YY_MOVE (yystack_[0].value.as < std::string > ())};
    }
#line 2297 "src/parser.cpp"
    break;

  case 78: // node_const_type: cat_type CONST
#line 332 "gen/parser.y"
                         {
        yylhs.value.as < cynth::ast::node::ConstType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ())};
    }
#line 2305 "src/parser.cpp"
    break;

  case 79: // node_in_type: cat_type IN
#line 337 "gen/parser.y"
                      {
        yylhs.value.as < cynth::ast::node::InType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ())};
    }
#line 2313 "src/parser.cpp"
    break;

  case 80: // node_out_type: cat_type OUT
#line 342 "gen/parser.y"
                       {
        yylhs.value.as < cynth::ast::node::OutType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ())};
    }
#line 2321 "src/parser.cpp"
    break;

  case 81: // node_function_type: cat_type paren_type
#line 347 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::ast::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2329 "src/parser.cpp"
    break;

  case 82: // node_function_type: void_type paren_type
#line 350 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2337 "src/parser.cpp"
    break;

  case 83: // node_function_type: cat_type void_type
#line 353 "gen/parser.y"
                                {
        yylhs.value.as < cynth::ast::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2345 "src/parser.cpp"
    break;

  case 84: // node_function_type: void_type void_type
#line 356 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::ast::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2353 "src/parser.cpp"
    break;

  case 85: // node_array_type: cat_type OBRACK cat_expression CBRACK
#line 361 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::ast::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .size = cynth::ast::category::Pattern{YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ())}};
    }
#line 2361 "src/parser.cpp"
    break;

  case 86: // node_array_type: cat_type OBRACK AUTO CBRACK
#line 364 "gen/parser.y"
                                      {
        yylhs.value.as < cynth::ast::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .size = cynth::optional_component<cynth::ast::category::Pattern>{}};
    }
#line 2369 "src/parser.cpp"
    break;

  case 87: // node_array_type: cat_type OBRACK CBRACK
#line 367 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::ast::node::ArrayType > () = {.type = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Type > ()), .size = cynth::optional_component<cynth::ast::category::Pattern>{}};
    }
#line 2377 "src/parser.cpp"
    break;

  case 88: // node_array_type: cat_type OBRACK cat_declaration CBRACK
#line 370 "gen/parser.y"
                                                            {
        yylhs.value.as < cynth::ast::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .size = cynth::ast::category::Pattern{YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ())}};
    }
#line 2385 "src/parser.cpp"
    break;

  case 89: // node_buffer_type: BUFFER OBRACK cat_expression CBRACK
#line 375 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::ast::node::BufferType > () = {.size = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ())};
    }
#line 2393 "src/parser.cpp"
    break;

  case 90: // node_type_decl: TYPE node_type_name
#line 380 "gen/parser.y"
                              {
        yylhs.value.as < cynth::ast::node::TypeDecl > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeName > ())};
    }
#line 2401 "src/parser.cpp"
    break;

  case 91: // paren_decl: OPAREN cat_declaration CPAREN
#line 387 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::ast::category::Declaration > () = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ());
    }
#line 2409 "src/parser.cpp"
    break;

  case 92: // paren_decl: OPAREN decl_list CPAREN
#line 390 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::category::Declaration > () = cynth::ast::node::TupleDecl{YY_MOVE (yystack_[1].value.as < cynth::component_vector<cynth::ast::category::Declaration> > ())};
    }
#line 2417 "src/parser.cpp"
    break;

  case 93: // paren_decl: OPAREN decl_list COMMA CPAREN
#line 393 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::category::Declaration > () = cynth::ast::node::TupleDecl{YY_MOVE (yystack_[2].value.as < cynth::component_vector<cynth::ast::category::Declaration> > ())};
    }
#line 2425 "src/parser.cpp"
    break;

  case 94: // void_decl: OPAREN CPAREN
#line 398 "gen/parser.y"
                  {
        yylhs.value.as < cynth::ast::category::Declaration > () = cynth::ast::node::TupleDecl{};
    }
#line 2433 "src/parser.cpp"
    break;

  case 95: // node_declaration: cat_type node_name
#line 403 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Declaration > () = {.name = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Name > ()), .type = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ())};
    }
#line 2441 "src/parser.cpp"
    break;

  case 96: // node_range_to: cat_expression TO cat_expression
#line 410 "gen/parser.y"
                                               {
        yylhs.value.as < cynth::ast::node::RangeTo > () = {.from = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), .to = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2449 "src/parser.cpp"
    break;

  case 97: // node_range_to_by: cat_expression TO cat_expression BY cat_expression
#line 415 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::ast::node::RangeToBy > () = {.from = YY_MOVE (yystack_[4].value.as < cynth::ast::category::Expression > ()), .to = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), .by = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2457 "src/parser.cpp"
    break;

  case 98: // node_spread: ELIP cat_expression
#line 420 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Spread > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2465 "src/parser.cpp"
    break;

  case 99: // paren_expr: OPAREN cat_expression CPAREN
#line 427 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ());
    }
#line 2473 "src/parser.cpp"
    break;

  case 100: // paren_expr: OPAREN expr_list CPAREN
#line 430 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::category::Expression > () = cynth::ast::node::Tuple{YY_MOVE (yystack_[1].value.as < cynth::component_vector<cynth::ast::category::Expression> > ())};
    }
#line 2481 "src/parser.cpp"
    break;

  case 101: // paren_expr: OPAREN expr_list COMMA CPAREN
#line 433 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::category::Expression > () = cynth::ast::node::Tuple{YY_MOVE (yystack_[2].value.as < cynth::component_vector<cynth::ast::category::Expression> > ())};
    }
#line 2489 "src/parser.cpp"
    break;

  case 102: // void: OPAREN CPAREN
#line 438 "gen/parser.y"
                  {
        yylhs.value.as < cynth::ast::category::Expression > () = cynth::ast::node::Tuple{};
    }
#line 2497 "src/parser.cpp"
    break;

  case 103: // node_name: NAME
#line 443 "gen/parser.y"
               {
        yylhs.value.as < cynth::ast::node::Name > () = {YY_MOVE (yystack_[0].value.as < std::string > ())};
    }
#line 2505 "src/parser.cpp"
    break;

  case 104: // node_block: OBRACE CBRACE
#line 448 "gen/parser.y"
                  {
        yylhs.value.as < cynth::ast::node::Block > () = {};
    }
#line 2513 "src/parser.cpp"
    break;

  case 105: // node_block: OBRACE stmt_list CBRACE
#line 451 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::node::Block > () = {YY_MOVE (yystack_[1].value.as < cynth::component_vector<cynth::ast::category::Statement> > ())};
    }
#line 2521 "src/parser.cpp"
    break;

  case 106: // node_block: OBRACE stmt_list SEMI CBRACE
#line 454 "gen/parser.y"
                                       {
        yylhs.value.as < cynth::ast::node::Block > () = {YY_MOVE (yystack_[2].value.as < cynth::component_vector<cynth::ast::category::Statement> > ())};
    }
#line 2529 "src/parser.cpp"
    break;

  case 107: // node_bool: TRUE
#line 461 "gen/parser.y"
         {
        yylhs.value.as < cynth::ast::node::Bool > () = {true};
    }
#line 2537 "src/parser.cpp"
    break;

  case 108: // node_bool: FALSE
#line 464 "gen/parser.y"
          {
        yylhs.value.as < cynth::ast::node::Bool > () = {false};
    }
#line 2545 "src/parser.cpp"
    break;

  case 109: // node_int: INT
#line 469 "gen/parser.y"
        {
        yylhs.value.as < cynth::ast::node::Int > () = {cynth::util::stoi(YY_MOVE (yystack_[0].value.as < std::string > ()))};
    }
#line 2553 "src/parser.cpp"
    break;

  case 110: // node_float: FLOAT
#line 474 "gen/parser.y"
          {
        yylhs.value.as < cynth::ast::node::Float > () = {std::stof(YY_MOVE (yystack_[0].value.as < std::string > ()))};
    }
#line 2561 "src/parser.cpp"
    break;

  case 111: // node_string: STRING
#line 479 "gen/parser.y"
           {
        yylhs.value.as < cynth::ast::node::String > () = {cynth::util::trim(YY_MOVE (yystack_[0].value.as < std::string > ()))};
    }
#line 2569 "src/parser.cpp"
    break;

  case 112: // node_function: cat_type FN paren_decl cat_expression
#line 484 "gen/parser.y"
                                                         {
        yylhs.value.as < cynth::ast::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2577 "src/parser.cpp"
    break;

  case 113: // node_function: void_type FN paren_decl cat_expression
#line 487 "gen/parser.y"
                                                          {
        yylhs.value.as < cynth::ast::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2585 "src/parser.cpp"
    break;

  case 114: // node_function: cat_type FN void_decl cat_expression
#line 490 "gen/parser.y"
                                                        {
        yylhs.value.as < cynth::ast::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2593 "src/parser.cpp"
    break;

  case 115: // node_function: void_type FN void_decl cat_expression
#line 493 "gen/parser.y"
                                                         {
        yylhs.value.as < cynth::ast::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2601 "src/parser.cpp"
    break;

  case 116: // node_array: OBRACK CBRACK
#line 498 "gen/parser.y"
                  {
        yylhs.value.as < cynth::ast::node::Array > () = {};
    }
#line 2609 "src/parser.cpp"
    break;

  case 117: // node_array: OBRACK array_elem_list CBRACK
#line 501 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::node::Array > () = {YY_MOVE (yystack_[1].value.as < cynth::component_vector<cynth::ast::category::ArrayElem> > ())};
    }
#line 2617 "src/parser.cpp"
    break;

  case 118: // node_array: OBRACK array_elem_list SEMI CBRACK
#line 504 "gen/parser.y"
                                             {
        yylhs.value.as < cynth::ast::node::Array > () = {YY_MOVE (yystack_[2].value.as < cynth::component_vector<cynth::ast::category::ArrayElem> > ())};
    }
#line 2625 "src/parser.cpp"
    break;

  case 119: // node_or: expr_or OR expr_and
#line 511 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::node::Or > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2633 "src/parser.cpp"
    break;

  case 120: // node_and: expr_and AND expr_eq
#line 516 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::And > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2641 "src/parser.cpp"
    break;

  case 121: // node_eq: expr_eq EQ expr_ord
#line 521 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::node::Eq > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2649 "src/parser.cpp"
    break;

  case 122: // node_ne: expr_eq NE expr_ord
#line 526 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::node::Ne > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2657 "src/parser.cpp"
    break;

  case 123: // node_ge: expr_ord GE expr_add
#line 531 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Ge > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2665 "src/parser.cpp"
    break;

  case 124: // node_le: expr_ord LE expr_add
#line 536 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Le > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2673 "src/parser.cpp"
    break;

  case 125: // node_gt: expr_ord GT expr_add
#line 541 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Gt > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2681 "src/parser.cpp"
    break;

  case 126: // node_lt: expr_ord LT expr_add
#line 546 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Lt > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2689 "src/parser.cpp"
    break;

  case 127: // node_add: expr_add ADD expr_mul
#line 551 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Add > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2697 "src/parser.cpp"
    break;

  case 128: // node_sub: expr_add SUB expr_mul
#line 556 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Sub > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2705 "src/parser.cpp"
    break;

  case 129: // node_mul: expr_mul MUL expr_pow
#line 561 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Mul > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2713 "src/parser.cpp"
    break;

  case 130: // node_div: expr_mul DIV expr_pow
#line 566 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Div > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2721 "src/parser.cpp"
    break;

  case 131: // node_mod: expr_mul MOD expr_pow
#line 571 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Mod > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2729 "src/parser.cpp"
    break;

  case 132: // node_pow: expr_pre POW expr_pow
#line 576 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Pow > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2737 "src/parser.cpp"
    break;

  case 133: // node_minus: SUB expr_pre
#line 581 "gen/parser.y"
                      {
        yylhs.value.as < cynth::ast::node::Minus > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2745 "src/parser.cpp"
    break;

  case 134: // node_plus: ADD expr_pre
#line 586 "gen/parser.y"
                      {
        yylhs.value.as < cynth::ast::node::Plus > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2753 "src/parser.cpp"
    break;

  case 135: // node_not: NOT expr_pre
#line 591 "gen/parser.y"
                      {
        yylhs.value.as < cynth::ast::node::Not > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2761 "src/parser.cpp"
    break;

  case 136: // node_application: expr_post paren_expr
#line 596 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::ast::node::Application > () = {.function = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ()), .arguments = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2769 "src/parser.cpp"
    break;

  case 137: // node_application: expr_post void
#line 599 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::node::Application > () = {.function = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ()), .arguments = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2777 "src/parser.cpp"
    break;

  case 138: // node_conversion: cat_type paren_expr
#line 604 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::node::Conversion > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()), .argument = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2785 "src/parser.cpp"
    break;

  case 139: // node_subscript: expr_post OBRACK array_elem_list CBRACK
#line 609 "gen/parser.y"
                                                                 {
        yylhs.value.as < cynth::ast::node::Subscript > () = {.container = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Expression > ()), .location = YY_MOVE (yystack_[1].value.as < cynth::component_vector<cynth::ast::category::ArrayElem> > ())};
    }
#line 2793 "src/parser.cpp"
    break;

  case 140: // node_expr_if: IF paren_expr cat_expression ELSE cat_expression
#line 614 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::ast::node::ExprIf > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Expression > ()), .positive_branch = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), .negative_branch = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2801 "src/parser.cpp"
    break;

  case 141: // node_definition: cat_declaration ASSGN cat_expression
#line 621 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::ast::node::Definition > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Declaration > ()), .value = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2809 "src/parser.cpp"
    break;

  case 142: // node_assignment: cat_expression ASSGN cat_expression
#line 626 "gen/parser.y"
                                                     {
        yylhs.value.as < cynth::ast::node::Assignment > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), .value = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2817 "src/parser.cpp"
    break;

  case 143: // node_type_def: TYPE node_type_name ASSGN cat_type
#line 631 "gen/parser.y"
                                                     {
        yylhs.value.as < cynth::ast::node::TypeDef > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::ast::node::TypeName > ()), .type = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2825 "src/parser.cpp"
    break;

  case 144: // node_function_def: cat_type node_name paren_decl cat_expression
#line 636 "gen/parser.y"
                                                                      {
        yylhs.value.as < cynth::ast::node::FunctionDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2833 "src/parser.cpp"
    break;

  case 145: // node_function_def: void_type node_name paren_decl cat_expression
#line 639 "gen/parser.y"
                                                                       {
        yylhs.value.as < cynth::ast::node::FunctionDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2841 "src/parser.cpp"
    break;

  case 146: // node_function_def: cat_type node_name void_decl cat_expression
#line 642 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::ast::node::FunctionDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2849 "src/parser.cpp"
    break;

  case 147: // node_function_def: void_type node_name void_decl cat_expression
#line 645 "gen/parser.y"
                                                                      {
        yylhs.value.as < cynth::ast::node::FunctionDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2857 "src/parser.cpp"
    break;

  case 148: // node_return: RETURN cat_expression
#line 650 "gen/parser.y"
                               {
        yylhs.value.as < cynth::ast::node::Return > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2865 "src/parser.cpp"
    break;

  case 149: // node_return: RETURN void
#line 653 "gen/parser.y"
                     {
        yylhs.value.as < cynth::ast::node::Return > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2873 "src/parser.cpp"
    break;

  case 150: // node_return: RETURN
#line 656 "gen/parser.y"
           {
        yylhs.value.as < cynth::ast::node::Return > () = {cynth::ast::category::Expression{cynth::ast::node::Tuple{}}};
    }
#line 2881 "src/parser.cpp"
    break;

  case 151: // node_if: IF paren_expr pure ELSE pure
#line 661 "gen/parser.y"
                                                 {
        yylhs.value.as < cynth::ast::node::If > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Expression > ()), .positive_branch = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Statement > ()), .negative_branch = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ())};
    }
#line 2889 "src/parser.cpp"
    break;

  case 152: // node_when: WHEN paren_expr cat_statement
#line 666 "gen/parser.y"
                                             {
        yylhs.value.as < cynth::ast::node::When > () = {.condition = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ()), .branch = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ())};
    }
#line 2897 "src/parser.cpp"
    break;

  case 153: // array_elem_list: cat_array_elem
#line 673 "gen/parser.y"
                          {
        yylhs.value.as < cynth::component_vector<cynth::ast::category::ArrayElem> > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::ArrayElem > ())};
    }
#line 2905 "src/parser.cpp"
    break;

  case 154: // array_elem_list: array_elem_list COMMA cat_array_elem
#line 676 "gen/parser.y"
                                                     {
        yylhs.value.as < cynth::component_vector<cynth::ast::category::ArrayElem> > () = cynth::util::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::ArrayElem > ()), YY_MOVE (yystack_[2].value.as < cynth::component_vector<cynth::ast::category::ArrayElem> > ()));
    }
#line 2913 "src/parser.cpp"
    break;

  case 155: // stmt_list: cat_statement
#line 681 "gen/parser.y"
                         {
        yylhs.value.as < cynth::component_vector<cynth::ast::category::Statement> > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ())};
    }
#line 2921 "src/parser.cpp"
    break;

  case 156: // stmt_list: stmt_list SEMI cat_statement
#line 684 "gen/parser.y"
                                             {
        yylhs.value.as < cynth::component_vector<cynth::ast::category::Statement> > () = cynth::util::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ()), YY_MOVE (yystack_[2].value.as < cynth::component_vector<cynth::ast::category::Statement> > ()));
    }
#line 2929 "src/parser.cpp"
    break;

  case 157: // type_list: cat_type COMMA cat_type
#line 689 "gen/parser.y"
                                           {
        yylhs.value.as < cynth::component_vector<cynth::ast::category::Type> > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Type > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2937 "src/parser.cpp"
    break;

  case 158: // type_list: type_list COMMA cat_type
#line 692 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::component_vector<cynth::ast::category::Type> > () = cynth::util::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()), YY_MOVE (yystack_[2].value.as < cynth::component_vector<cynth::ast::category::Type> > ()));
    }
#line 2945 "src/parser.cpp"
    break;

  case 159: // expr_list: cat_expression COMMA cat_expression
#line 697 "gen/parser.y"
                                                       {
        yylhs.value.as < cynth::component_vector<cynth::ast::category::Expression> > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2953 "src/parser.cpp"
    break;

  case 160: // expr_list: expr_list COMMA cat_expression
#line 700 "gen/parser.y"
                                               {
        yylhs.value.as < cynth::component_vector<cynth::ast::category::Expression> > () = cynth::util::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[2].value.as < cynth::component_vector<cynth::ast::category::Expression> > ()));
    }
#line 2961 "src/parser.cpp"
    break;

  case 161: // decl_list: cat_declaration COMMA cat_declaration
#line 705 "gen/parser.y"
                                                         {
        yylhs.value.as < cynth::component_vector<cynth::ast::category::Declaration> > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Declaration > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Declaration > ())};
    }
#line 2969 "src/parser.cpp"
    break;

  case 162: // decl_list: decl_list COMMA cat_declaration
#line 708 "gen/parser.y"
                                                {
        yylhs.value.as < cynth::component_vector<cynth::ast::category::Declaration> > () = cynth::util::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Declaration > ()), YY_MOVE (yystack_[2].value.as < cynth::component_vector<cynth::ast::category::Declaration> > ()));
    }
#line 2977 "src/parser.cpp"
    break;


#line 2981 "src/parser.cpp"

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





  const signed char parser::yypact_ninf_ = -124;

  const signed char parser::yytable_ninf_ = -76;

  const short
  parser::yypact_[] =
  {
     417,  -124,  -124,  -124,  -124,  -124,   -23,   -23,     5,    31,
     760,  -124,  -124,  -124,   501,    45,   464,   318,   318,   318,
      46,    82,    49,    54,  -124,  -124,    24,    43,     1,   261,
     137,   196,  -124,    59,    55,  -124,  -124,  -124,    42,  -124,
    -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,    73,
    -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
    -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
    -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
    -124,  -124,  -124,  -124,  -124,  -124,  -124,    90,   797,   417,
     417,    83,   797,   -23,     5,   538,   461,  -124,    -4,  -124,
    -124,   817,    67,    86,  -124,    99,   101,   103,  -124,    -8,
     797,   575,  -124,  -124,    92,  -124,  -124,  -124,   133,   609,
    -124,    98,  -124,  -124,  -124,   105,  -124,  -124,  -124,   612,
    -124,  -124,  -124,   105,   797,   797,   318,   318,   318,   318,
     318,   318,   318,   318,   318,   318,   318,   318,   318,   318,
     649,   686,  -124,  -124,   105,    53,  -124,  -124,   105,   417,
      58,   119,  -124,   180,   118,   797,  -124,    15,   829,   180,
    -124,  -124,   436,  -124,   797,  -124,   284,  -124,   384,  -124,
     723,  -124,   260,  -124,  -124,   797,   124,   686,  -124,   390,
     797,   797,   129,  -124,    82,   132,   135,   797,   797,  -124,
    -124,    43,     1,   261,   261,   137,   137,   137,   137,   196,
     196,  -124,  -124,  -124,  -124,  -124,     8,   797,   797,   841,
     797,   797,  -124,   797,   417,   683,  -124,   121,   683,   425,
       3,  -124,  -124,  -124,   683,  -124,  -124,  -124,  -124,  -124,
     110,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
    -124,  -124,  -124,  -124,  -124,  -124,  -124,    54,  -124,   337,
     797,  -124
  };

  const unsigned char
  parser::yydefact_[] =
  {
       2,   103,    77,   109,   110,   111,     0,     0,     0,     0,
     150,   107,   108,    76,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    24,   155,    23,    21,    34,    36,    39,
      44,    47,    51,    53,    57,    61,    22,    20,     0,    11,
      12,    17,    18,    19,    13,    14,    15,    16,     6,    25,
      69,    62,    67,    63,    64,    65,    66,    71,    68,    33,
      35,    37,    38,    40,    41,    42,    43,    45,    46,    48,
      49,    50,    52,    55,    54,    56,    58,    59,    60,    70,
      26,    27,    29,    28,    30,    31,    32,     3,     0,     0,
       0,    90,     0,     0,     0,     0,     0,   148,     0,   149,
      75,     0,     0,     0,     5,     0,     0,     0,   104,     0,
       0,     0,   116,   153,    10,     7,     8,     9,     0,     0,
     134,     0,   133,   135,     1,     0,    78,    79,    80,     0,
      81,    83,   138,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   136,   137,     0,     0,    82,    84,     0,     4,
       0,     0,   152,     0,     0,     0,    90,   102,     0,     0,
      72,    95,     0,    91,     0,    99,     0,    73,     0,    92,
       0,   100,     0,   105,    98,     0,     0,     0,   117,     0,
       0,     0,    76,    87,     0,     0,     0,     0,     0,   141,
     142,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   102,     0,     0,     0,     0,
       0,     0,   156,     0,     0,   143,    89,     0,   157,     0,
       0,   161,   159,    74,   158,    93,   162,   101,   160,   106,
      96,   118,   154,    94,   112,   114,    86,    88,    85,   144,
     146,   139,   113,   115,   145,   147,   140,     0,   151,     0,
       0,    97
  };

  const short
  parser::yypgoto_[] =
  {
    -124,  -124,   237,   -12,    -2,    23,   -89,   -73,  -124,    51,
      62,    57,   229,    91,   311,   231,  -124,  -124,  -124,    85,
       0,  -124,    -3,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
    -122,  -123,    33,  -124,  -124,  -124,     7,   145,   -14,  -124,
    -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
    -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
    -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,
    -124,  -124,  -124,  -124,  -124,  -124,    39,  -124,   177
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,    20,    96,    22,   113,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      98,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,   191,    49,   115,   116,   117,    50,    99,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,   105,   106,   118,   107,    87
  };

  const short
  parser::yytable_[] =
  {
      38,   162,   102,   190,    88,    91,     1,   133,   154,     2,
     198,   197,   182,    89,    90,    38,   161,   121,   121,   121,
     126,   131,   183,   155,   158,   127,   128,   -75,   132,   187,
     155,   218,   217,    97,   129,   221,   220,   103,   157,   114,
     251,   152,   -75,   138,   139,     1,   124,   104,     1,     2,
       3,     4,     5,     6,   154,     7,     8,     2,     9,    10,
      11,    12,    92,    13,    94,   136,     9,   223,   134,   155,
     222,    13,    14,   135,    15,   108,    16,   135,    17,    18,
     155,   100,   150,   137,    19,     1,   151,   171,   172,    38,
      38,   166,    -5,   222,   125,   173,   131,   149,   157,   126,
     165,   131,   163,   132,   127,   128,   130,   174,   132,   111,
     159,   103,   160,   129,   175,   164,   185,   195,   103,   131,
     176,   157,   178,   156,   180,   155,   132,   177,   224,   179,
     223,   181,   189,   184,   103,   260,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     226,   258,   196,   186,   187,   121,   241,   199,   200,    38,
     231,   246,   104,   121,   247,   188,   236,   248,   131,   121,
     144,   145,   121,   103,   114,   132,   121,   102,   121,   153,
     171,   130,    38,   156,     2,   242,   130,   201,   227,   121,
     216,    94,   109,     9,   131,   203,   204,   232,    13,   202,
       0,   132,     0,   238,   130,   104,   156,   155,   240,     0,
     114,   104,     0,   244,   245,     0,   171,   102,     0,   131,
     249,   250,   104,     0,    38,   131,     0,     0,   131,   121,
     131,   146,   147,   148,   131,   209,   210,    21,     0,     0,
     252,   253,     0,   254,   255,   171,   256,   257,   120,   122,
     123,   101,    21,   130,   119,   119,   119,     0,     0,   131,
       0,     0,   104,     1,     2,     3,     4,     5,     6,     0,
       7,     8,     0,     9,    10,    11,    12,     0,    13,   130,
       0,     0,     0,   261,     0,     0,     0,    14,     2,    15,
     239,    16,     0,    17,    18,    94,     0,     9,     0,    19,
       0,     0,    13,     0,   130,   140,   141,   142,   143,     0,
     130,   155,   233,   130,     0,   130,     0,     0,     0,   130,
       0,     1,     2,     3,     4,     5,    21,    21,     0,    94,
       0,     9,   168,    11,    12,     0,    13,     0,     0,     0,
       1,     0,     0,     0,   130,   111,     0,    15,   168,    16,
       0,    17,    18,     0,   126,     0,     0,    19,   169,   127,
     128,     0,     0,     0,   155,   170,   194,     0,   129,   205,
     206,   207,   208,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,     0,     2,     0,
       0,     0,   219,     0,     2,    94,    21,     9,     0,     0,
     225,    94,    13,     9,     0,     0,   228,     0,    13,   230,
       0,   229,   235,   234,     0,   230,     0,   229,   243,    21,
       1,     2,     3,     4,     5,     6,   230,     7,     8,     2,
       9,    10,    11,    12,     0,    13,    94,     0,     9,     0,
       2,     0,     0,    13,    14,     0,    15,    94,    16,     9,
      17,    18,   229,   100,    13,     0,    19,   211,   212,   213,
     214,    21,     0,   229,     0,     0,   259,     1,     2,     3,
       4,     5,    93,   125,     0,    94,     0,     9,   126,    11,
      12,     0,    13,   127,   128,     0,     0,     0,   111,     0,
     110,   111,   129,    15,     0,    16,   112,    17,    18,     0,
       0,     0,     0,    19,     1,     2,     3,     4,     5,    93,
       0,     0,    94,     0,     9,     0,    11,    12,     0,    13,
       0,     0,     0,     0,     0,     0,     0,     0,    14,   100,
      15,     0,    16,     0,    17,    18,     0,     0,     0,     0,
      19,     1,     2,     3,     4,     5,    93,     0,     0,    94,
       0,     9,     0,    11,    12,     0,    13,     0,     0,     0,
       0,     0,     0,     0,     0,   111,   167,    15,     0,    16,
       0,    17,    18,     0,     0,     0,     0,    19,     1,     2,
       3,     4,     5,    93,     0,     0,    94,     0,     9,     0,
      11,    12,     0,    13,     0,     0,     0,     0,     0,     0,
       0,     0,   111,   100,    15,     0,    16,     0,    17,    18,
       0,     0,     0,     0,    19,     1,     2,     3,     4,     5,
      93,     0,     0,    94,     0,     9,   126,    11,    12,     0,
     192,   127,   128,     0,     0,     0,   111,     0,     0,    14,
     129,    15,     0,    16,   193,    17,    18,     0,     0,     0,
       0,    19,     1,     2,     3,     4,     5,    93,     0,     0,
      94,     0,     9,     0,    11,    12,     0,    13,     0,     0,
       0,     0,     0,     0,     0,     0,   111,   215,    15,     0,
      16,     0,    17,    18,     0,     0,     0,     0,    19,     1,
       2,     3,     4,     5,    93,     0,     0,    94,     0,     9,
     126,    11,    12,     0,    13,   127,   128,     0,     0,     0,
     155,     0,   110,   111,   129,    15,     0,    16,     0,    17,
      18,     0,     0,     0,     0,    19,     1,     2,     3,     4,
       5,    93,     0,     0,    94,     0,     9,     0,    11,    12,
       0,    13,     0,     0,     0,     0,     0,     0,     0,     0,
     111,   237,    15,     0,    16,     0,    17,    18,     0,     0,
       0,     0,    19,     1,     2,     3,     4,     5,    93,     0,
       0,    94,     0,     9,     0,    11,    12,     0,    13,     0,
       0,     0,     0,     0,     0,     0,     0,    95,     0,    15,
       0,    16,     0,    17,    18,     0,     0,     0,     0,    19,
       1,     2,     3,     4,     5,    93,     0,     0,    94,     0,
       9,     0,    11,    12,     0,    13,     0,     0,     0,     0,
       1,     0,     0,     0,   111,     0,    15,     0,    16,   125,
      17,    18,     0,     0,   126,     0,    19,     0,   169,   127,
     128,   125,     0,     0,   111,   170,   126,     0,   129,     0,
     169,   127,   128,     0,     0,     0,   111,   170,   126,     0,
     129,     0,   169,   127,   128,     0,     0,     0,   155,   170,
       0,     0,   129
  };

  const short
  parser::yycheck_[] =
  {
       0,    90,    14,   125,    27,     8,     3,    21,    12,     4,
     133,   133,    20,     6,     7,    15,    89,    17,    18,    19,
      17,    21,    30,    27,    38,    22,    23,    12,    21,    21,
      27,   154,   154,    10,    31,   158,   158,    14,    38,    16,
      32,    34,    27,    42,    43,     3,     0,    14,     3,     4,
       5,     6,     7,     8,    12,    10,    11,     4,    13,    14,
      15,    16,    31,    18,    11,    41,    13,     9,    19,    27,
     159,    18,    27,    19,    29,    30,    31,    19,    33,    34,
      27,    28,    27,    40,    39,     3,    31,   101,    21,    89,
      90,    94,    19,   182,    12,    28,    96,    38,    98,    17,
      93,   101,    19,    96,    22,    23,    21,    21,   101,    27,
      20,    88,    89,    31,    28,    92,    24,   129,    95,   119,
      21,   121,    21,    38,    21,    27,   119,    28,     9,    28,
       9,    28,    27,   110,   111,    25,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
      32,   224,   129,    20,    21,   155,    32,   134,   135,   159,
     172,    32,   129,   163,    32,    32,   178,    32,   168,   169,
      33,    34,   172,   150,   151,   168,   176,   189,   178,    34,
     194,    96,   182,    98,     4,   187,   101,   136,   165,   189,
     151,    11,    15,    13,   194,   138,   139,   174,    18,   137,
      -1,   194,    -1,   180,   119,   172,   121,    27,   185,    -1,
     187,   178,    -1,   190,   191,    -1,   230,   229,    -1,   219,
     197,   198,   189,    -1,   224,   225,    -1,    -1,   228,   229,
     230,    35,    36,    37,   234,   144,   145,     0,    -1,    -1,
     217,   218,    -1,   220,   221,   259,   223,   224,    17,    18,
      19,    14,    15,   168,    17,    18,    19,    -1,    -1,   259,
      -1,    -1,   229,     3,     4,     5,     6,     7,     8,    -1,
      10,    11,    -1,    13,    14,    15,    16,    -1,    18,   194,
      -1,    -1,    -1,   260,    -1,    -1,    -1,    27,     4,    29,
      30,    31,    -1,    33,    34,    11,    -1,    13,    -1,    39,
      -1,    -1,    18,    -1,   219,    44,    45,    46,    47,    -1,
     225,    27,    28,   228,    -1,   230,    -1,    -1,    -1,   234,
      -1,     3,     4,     5,     6,     7,    89,    90,    -1,    11,
      -1,    13,    95,    15,    16,    -1,    18,    -1,    -1,    -1,
       3,    -1,    -1,    -1,   259,    27,    -1,    29,   111,    31,
      -1,    33,    34,    -1,    17,    -1,    -1,    39,    21,    22,
      23,    -1,    -1,    -1,    27,    28,   129,    -1,    31,   140,
     141,   142,   143,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,    -1,     4,    -1,
      -1,    -1,   155,    -1,     4,    11,   159,    13,    -1,    -1,
     163,    11,    18,    13,    -1,    -1,   169,    -1,    18,   172,
      -1,    27,    28,   176,    -1,   178,    -1,    27,    28,   182,
       3,     4,     5,     6,     7,     8,   189,    10,    11,     4,
      13,    14,    15,    16,    -1,    18,    11,    -1,    13,    -1,
       4,    -1,    -1,    18,    27,    -1,    29,    11,    31,    13,
      33,    34,    27,    28,    18,    -1,    39,   146,   147,   148,
     149,   224,    -1,    27,    -1,    -1,   229,     3,     4,     5,
       6,     7,     8,    12,    -1,    11,    -1,    13,    17,    15,
      16,    -1,    18,    22,    23,    -1,    -1,    -1,    27,    -1,
      26,    27,    31,    29,    -1,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    39,     3,     4,     5,     6,     7,     8,
      -1,    -1,    11,    -1,    13,    -1,    15,    16,    -1,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,
      29,    -1,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,
      39,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    13,    -1,    15,    16,    -1,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    28,    29,    -1,    31,
      -1,    33,    34,    -1,    -1,    -1,    -1,    39,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    13,    -1,
      15,    16,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    28,    29,    -1,    31,    -1,    33,    34,
      -1,    -1,    -1,    -1,    39,     3,     4,     5,     6,     7,
       8,    -1,    -1,    11,    -1,    13,    17,    15,    16,    -1,
      18,    22,    23,    -1,    -1,    -1,    27,    -1,    -1,    27,
      31,    29,    -1,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    39,     3,     4,     5,     6,     7,     8,    -1,    -1,
      11,    -1,    13,    -1,    15,    16,    -1,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    29,    -1,
      31,    -1,    33,    34,    -1,    -1,    -1,    -1,    39,     3,
       4,     5,     6,     7,     8,    -1,    -1,    11,    -1,    13,
      17,    15,    16,    -1,    18,    22,    23,    -1,    -1,    -1,
      27,    -1,    26,    27,    31,    29,    -1,    31,    -1,    33,
      34,    -1,    -1,    -1,    -1,    39,     3,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    13,    -1,    15,    16,
      -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    28,    29,    -1,    31,    -1,    33,    34,    -1,    -1,
      -1,    -1,    39,     3,     4,     5,     6,     7,     8,    -1,
      -1,    11,    -1,    13,    -1,    15,    16,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    29,
      -1,    31,    -1,    33,    34,    -1,    -1,    -1,    -1,    39,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      13,    -1,    15,    16,    -1,    18,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    -1,    27,    -1,    29,    -1,    31,    12,
      33,    34,    -1,    -1,    17,    -1,    39,    -1,    21,    22,
      23,    12,    -1,    -1,    27,    28,    17,    -1,    31,    -1,
      21,    22,    23,    -1,    -1,    -1,    27,    28,    17,    -1,
      31,    -1,    21,    22,    23,    -1,    -1,    -1,    27,    28,
      -1,    -1,    31
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,     8,    10,    11,    13,
      14,    15,    16,    18,    27,    29,    31,    33,    34,    39,
      50,    51,    52,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    81,
      85,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   127,    27,    85,
      85,    71,    31,     8,    11,    27,    51,    54,    69,    86,
      28,    51,    52,    54,    81,   123,   124,   126,    30,   127,
      26,    27,    32,    53,    54,    82,    83,    84,   125,    51,
      64,    69,    64,    64,     0,    12,    17,    22,    23,    31,
      68,    69,    85,    87,    19,    19,    41,    40,    42,    43,
      44,    45,    46,    47,    33,    34,    35,    36,    37,    38,
      27,    31,    85,    86,    12,    27,    68,    69,    87,    20,
      54,    56,    55,    19,    54,    85,    71,    28,    51,    21,
      28,    87,    21,    28,    21,    28,    21,    28,    21,    28,
      21,    28,    20,    30,    54,    24,    20,    21,    32,    27,
      79,    80,    18,    32,    51,    52,    54,    79,    80,    54,
      54,    58,    59,    60,    60,    61,    61,    61,    61,    62,
      62,    63,    63,    63,    63,    28,   125,    79,    80,    51,
      79,    80,    55,     9,     9,    51,    32,    54,    51,    27,
      51,    52,    54,    28,    51,    28,    52,    28,    54,    30,
      54,    32,    53,    28,    54,    54,    32,    32,    32,    54,
      54,    32,    54,    54,    54,    54,    54,    54,    56,    51,
      25,    54
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    49,    50,    50,    50,    52,    52,    53,    53,    53,
      53,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    54,    54,    55,    55,    56,    56,    56,    56,    56,
      56,    56,    56,    57,    57,    58,    58,    59,    59,    59,
      60,    60,    60,    60,    60,    61,    61,    61,    62,    62,
      62,    62,    63,    63,    64,    64,    64,    64,    65,    65,
      65,    65,    66,    66,    66,    66,    66,    66,    66,    66,
      67,    67,    68,    68,    68,    69,    70,    71,    72,    73,
      74,    75,    75,    75,    75,    76,    76,    76,    76,    77,
      78,    79,    79,    79,    80,    81,    82,    83,    84,    85,
      85,    85,    86,    87,    88,    88,    88,    89,    89,    90,
      91,    92,    93,    93,    93,    93,    94,    94,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   110,   109,   111,   112,   112,   113,   114,
     115,   116,   117,   119,   118,   118,   118,   118,   120,   120,
     120,   121,   122,   125,   125,   127,   127,   123,   123,   126,
     126,   124,   124
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
       1,     1,     3,     3,     4,     2,     1,     1,     2,     2,
       2,     2,     2,     2,     2,     4,     4,     3,     4,     4,
       2,     3,     3,     4,     2,     2,     3,     5,     2,     3,
       3,     4,     2,     1,     2,     3,     4,     1,     1,     1,
       1,     1,     4,     4,     4,     4,     2,     3,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     2,     2,     4,
       5,     3,     3,     4,     4,     4,     4,     4,     2,     2,
       1,     5,     3,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     3
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
  "IN", "OUT", "TO", "BY", "ELIP", "OPAREN", "CPAREN", "OBRACE", "CBRACE",
  "OBRACK", "CBRACK", "ADD", "SUB", "MUL", "DIV", "MOD", "POW", "NOT",
  "AND", "OR", "EQ", "NE", "GE", "LE", "GT", "LT", "ILLEGAL", "$accept",
  "start", "cat_type", "cat_declaration", "cat_array_elem",
  "cat_expression", "cat_statement", "pure", "expr_or", "expr_and",
  "expr_eq", "expr_ord", "expr_add", "expr_mul", "expr_pow", "expr_pre",
  "expr_post", "expr_atom", "expr_right", "paren_type", "void_type",
  "node_auto", "node_type_name", "node_const_type", "node_in_type",
  "node_out_type", "node_function_type", "node_array_type",
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
       0,   188,   188,   191,   194,   201,   202,   205,   206,   207,
     208,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   223,   224,   227,   228,   233,   234,   235,   236,   237,
     238,   239,   240,   243,   244,   247,   248,   251,   252,   253,
     256,   257,   258,   259,   260,   263,   264,   265,   268,   269,
     270,   271,   274,   275,   278,   279,   280,   281,   284,   285,
     286,   287,   290,   291,   292,   293,   294,   295,   296,   297,
     300,   301,   306,   309,   312,   317,   322,   327,   332,   337,
     342,   347,   350,   353,   356,   361,   364,   367,   370,   375,
     380,   387,   390,   393,   398,   403,   410,   415,   420,   427,
     430,   433,   438,   443,   448,   451,   454,   461,   464,   469,
     474,   479,   484,   487,   490,   493,   498,   501,   504,   511,
     516,   521,   526,   531,   536,   541,   546,   551,   556,   561,
     566,   571,   576,   581,   586,   591,   596,   599,   604,   609,
     614,   621,   626,   631,   636,   639,   642,   645,   650,   653,
     656,   661,   666,   673,   676,   681,   684,   689,   692,   697,
     700,   705,   708
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
#line 3608 "src/parser.cpp"

#line 712 "gen/parser.y"


void yy::parser::error (std::string const & msg) {
    // TODO: There's a syntax error every time for some reason.
    //std::cerr << "parser error: " << msg << '\n';
}
