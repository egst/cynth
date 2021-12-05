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
        value.YY_MOVE_OR_COPY< cynth::ast::category::ArrayElement > (YY_MOVE (that.value));
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
      case symbol_kind::S_expr_assgn_target: // expr_assgn_target
      case symbol_kind::S_paren_expr: // paren_expr
      case symbol_kind::S_void: // void
        value.YY_MOVE_OR_COPY< cynth::ast::category::Expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_range_decl: // cat_range_decl
      case symbol_kind::S_paren_range_decl: // paren_range_decl
        value.YY_MOVE_OR_COPY< cynth::ast::category::RangeDeclaration > (YY_MOVE (that.value));
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

      case symbol_kind::S_node_expr_for: // node_expr_for
        value.YY_MOVE_OR_COPY< cynth::ast::node::ExprFor > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.YY_MOVE_OR_COPY< cynth::ast::node::ExprIf > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_float: // node_float
        value.YY_MOVE_OR_COPY< cynth::ast::node::Float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_for: // node_for
        value.YY_MOVE_OR_COPY< cynth::ast::node::For > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.YY_MOVE_OR_COPY< cynth::ast::node::FunDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function: // node_function
        value.YY_MOVE_OR_COPY< cynth::ast::node::Function > (YY_MOVE (that.value));
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

      case symbol_kind::S_node_range_decl: // node_range_decl
        value.YY_MOVE_OR_COPY< cynth::ast::node::RangeDecl > (YY_MOVE (that.value));
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

      case symbol_kind::S_node_while: // node_while
        value.YY_MOVE_OR_COPY< cynth::ast::node::While > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.YY_MOVE_OR_COPY< esl::component_vector<cynth::ast::category::ArrayElement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.YY_MOVE_OR_COPY< esl::component_vector<cynth::ast::category::Declaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.YY_MOVE_OR_COPY< esl::component_vector<cynth::ast::category::Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_range_decl_list: // range_decl_list
        value.YY_MOVE_OR_COPY< esl::component_vector<cynth::ast::category::RangeDeclaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.YY_MOVE_OR_COPY< esl::component_vector<cynth::ast::category::Statement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_list: // type_list
        value.YY_MOVE_OR_COPY< esl::component_vector<cynth::ast::category::Type> > (YY_MOVE (that.value));
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
        value.move< cynth::ast::category::ArrayElement > (YY_MOVE (that.value));
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
      case symbol_kind::S_expr_assgn_target: // expr_assgn_target
      case symbol_kind::S_paren_expr: // paren_expr
      case symbol_kind::S_void: // void
        value.move< cynth::ast::category::Expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_range_decl: // cat_range_decl
      case symbol_kind::S_paren_range_decl: // paren_range_decl
        value.move< cynth::ast::category::RangeDeclaration > (YY_MOVE (that.value));
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

      case symbol_kind::S_node_expr_for: // node_expr_for
        value.move< cynth::ast::node::ExprFor > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.move< cynth::ast::node::ExprIf > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_float: // node_float
        value.move< cynth::ast::node::Float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_for: // node_for
        value.move< cynth::ast::node::For > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.move< cynth::ast::node::FunDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function: // node_function
        value.move< cynth::ast::node::Function > (YY_MOVE (that.value));
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

      case symbol_kind::S_node_range_decl: // node_range_decl
        value.move< cynth::ast::node::RangeDecl > (YY_MOVE (that.value));
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

      case symbol_kind::S_node_while: // node_while
        value.move< cynth::ast::node::While > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.move< esl::component_vector<cynth::ast::category::ArrayElement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< esl::component_vector<cynth::ast::category::Declaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< esl::component_vector<cynth::ast::category::Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_range_decl_list: // range_decl_list
        value.move< esl::component_vector<cynth::ast::category::RangeDeclaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< esl::component_vector<cynth::ast::category::Statement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_list: // type_list
        value.move< esl::component_vector<cynth::ast::category::Type> > (YY_MOVE (that.value));
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
        value.copy< cynth::ast::category::ArrayElement > (that.value);
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
      case symbol_kind::S_expr_assgn_target: // expr_assgn_target
      case symbol_kind::S_paren_expr: // paren_expr
      case symbol_kind::S_void: // void
        value.copy< cynth::ast::category::Expression > (that.value);
        break;

      case symbol_kind::S_cat_range_decl: // cat_range_decl
      case symbol_kind::S_paren_range_decl: // paren_range_decl
        value.copy< cynth::ast::category::RangeDeclaration > (that.value);
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

      case symbol_kind::S_node_expr_for: // node_expr_for
        value.copy< cynth::ast::node::ExprFor > (that.value);
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.copy< cynth::ast::node::ExprIf > (that.value);
        break;

      case symbol_kind::S_node_float: // node_float
        value.copy< cynth::ast::node::Float > (that.value);
        break;

      case symbol_kind::S_node_for: // node_for
        value.copy< cynth::ast::node::For > (that.value);
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.copy< cynth::ast::node::FunDef > (that.value);
        break;

      case symbol_kind::S_node_function: // node_function
        value.copy< cynth::ast::node::Function > (that.value);
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

      case symbol_kind::S_node_range_decl: // node_range_decl
        value.copy< cynth::ast::node::RangeDecl > (that.value);
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

      case symbol_kind::S_node_while: // node_while
        value.copy< cynth::ast::node::While > (that.value);
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.copy< esl::component_vector<cynth::ast::category::ArrayElement> > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.copy< esl::component_vector<cynth::ast::category::Declaration> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.copy< esl::component_vector<cynth::ast::category::Expression> > (that.value);
        break;

      case symbol_kind::S_range_decl_list: // range_decl_list
        value.copy< esl::component_vector<cynth::ast::category::RangeDeclaration> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< esl::component_vector<cynth::ast::category::Statement> > (that.value);
        break;

      case symbol_kind::S_type_list: // type_list
        value.copy< esl::component_vector<cynth::ast::category::Type> > (that.value);
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
        value.move< cynth::ast::category::ArrayElement > (that.value);
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
      case symbol_kind::S_expr_assgn_target: // expr_assgn_target
      case symbol_kind::S_paren_expr: // paren_expr
      case symbol_kind::S_void: // void
        value.move< cynth::ast::category::Expression > (that.value);
        break;

      case symbol_kind::S_cat_range_decl: // cat_range_decl
      case symbol_kind::S_paren_range_decl: // paren_range_decl
        value.move< cynth::ast::category::RangeDeclaration > (that.value);
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

      case symbol_kind::S_node_expr_for: // node_expr_for
        value.move< cynth::ast::node::ExprFor > (that.value);
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.move< cynth::ast::node::ExprIf > (that.value);
        break;

      case symbol_kind::S_node_float: // node_float
        value.move< cynth::ast::node::Float > (that.value);
        break;

      case symbol_kind::S_node_for: // node_for
        value.move< cynth::ast::node::For > (that.value);
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.move< cynth::ast::node::FunDef > (that.value);
        break;

      case symbol_kind::S_node_function: // node_function
        value.move< cynth::ast::node::Function > (that.value);
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

      case symbol_kind::S_node_range_decl: // node_range_decl
        value.move< cynth::ast::node::RangeDecl > (that.value);
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

      case symbol_kind::S_node_while: // node_while
        value.move< cynth::ast::node::While > (that.value);
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.move< esl::component_vector<cynth::ast::category::ArrayElement> > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< esl::component_vector<cynth::ast::category::Declaration> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< esl::component_vector<cynth::ast::category::Expression> > (that.value);
        break;

      case symbol_kind::S_range_decl_list: // range_decl_list
        value.move< esl::component_vector<cynth::ast::category::RangeDeclaration> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< esl::component_vector<cynth::ast::category::Statement> > (that.value);
        break;

      case symbol_kind::S_type_list: // type_list
        value.move< esl::component_vector<cynth::ast::category::Type> > (that.value);
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
      case symbol_kind::S_expr_assgn_target: // expr_assgn_target
      case symbol_kind::S_paren_expr: // paren_expr
      case symbol_kind::S_void: // void
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_cat_range_decl: // cat_range_decl
      case symbol_kind::S_paren_range_decl: // paren_range_decl
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

      case symbol_kind::S_node_expr_for: // node_expr_for
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_float: // node_float
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_for: // node_for
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_function: // node_function
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

      case symbol_kind::S_node_range_decl: // node_range_decl
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

      case symbol_kind::S_node_while: // node_while
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        yylhs.value.emplace< esl::component_vector<cynth::ast::category::ArrayElement> > ();
        break;

      case symbol_kind::S_decl_list: // decl_list
        yylhs.value.emplace< esl::component_vector<cynth::ast::category::Declaration> > ();
        break;

      case symbol_kind::S_expr_list: // expr_list
        yylhs.value.emplace< esl::component_vector<cynth::ast::category::Expression> > ();
        break;

      case symbol_kind::S_range_decl_list: // range_decl_list
        yylhs.value.emplace< esl::component_vector<cynth::ast::category::RangeDeclaration> > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        yylhs.value.emplace< esl::component_vector<cynth::ast::category::Statement> > ();
        break;

      case symbol_kind::S_type_list: // type_list
        yylhs.value.emplace< esl::component_vector<cynth::ast::category::Type> > ();
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
#line 202 "gen/parser.y"
           {
        result = {};
    }
#line 1961 "src/parser.cpp"
    break;

  case 3: // start: stmt_list
#line 205 "gen/parser.y"
                    {
        result = {YY_MOVE (yystack_[0].value.as < esl::component_vector<cynth::ast::category::Statement> > ())};
    }
#line 1969 "src/parser.cpp"
    break;

  case 4: // start: stmt_list SEMI
#line 208 "gen/parser.y"
                         {
        result = {YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::ast::category::Statement> > ())};
    }
#line 1977 "src/parser.cpp"
    break;

  case 5: // cat_declaration: node_declaration
#line 215 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Declaration > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Declaration > ()); }
#line 1983 "src/parser.cpp"
    break;

  case 6: // cat_declaration: paren_decl
#line 216 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Declaration > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Declaration > ()); }
#line 1989 "src/parser.cpp"
    break;

  case 7: // cat_range_decl: node_range_decl
#line 219 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::RangeDeclaration > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::RangeDecl > ()); }
#line 1995 "src/parser.cpp"
    break;

  case 8: // cat_range_decl: paren_range_decl
#line 220 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::RangeDeclaration > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::RangeDeclaration > ()); }
#line 2001 "src/parser.cpp"
    break;

  case 9: // cat_array_elem: node_range_to
#line 223 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::RangeTo > ()); }
#line 2007 "src/parser.cpp"
    break;

  case 10: // cat_array_elem: node_range_to_by
#line 224 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::RangeToBy > ()); }
#line 2013 "src/parser.cpp"
    break;

  case 11: // cat_array_elem: node_spread
#line 225 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Spread > ()); }
#line 2019 "src/parser.cpp"
    break;

  case 12: // cat_array_elem: cat_expression
#line 226 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2025 "src/parser.cpp"
    break;

  case 13: // cat_type: node_auto
#line 229 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Auto > ()); }
#line 2031 "src/parser.cpp"
    break;

  case 14: // cat_type: node_type_name
#line 230 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeName > ()); }
#line 2037 "src/parser.cpp"
    break;

  case 15: // cat_type: node_function_type
#line 231 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::FunctionType > ()); }
#line 2043 "src/parser.cpp"
    break;

  case 16: // cat_type: node_array_type
#line 232 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::ArrayType > ()); }
#line 2049 "src/parser.cpp"
    break;

  case 17: // cat_type: node_buffer_type
#line 233 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::BufferType > ()); }
#line 2055 "src/parser.cpp"
    break;

  case 18: // cat_type: node_type_decl
#line 234 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeDecl > ()); }
#line 2061 "src/parser.cpp"
    break;

  case 19: // cat_type: node_const_type
#line 235 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::ConstType > ()); }
#line 2067 "src/parser.cpp"
    break;

  case 20: // cat_type: node_in_type
#line 236 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::InType > ()); }
#line 2073 "src/parser.cpp"
    break;

  case 21: // cat_type: node_out_type
#line 237 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::OutType > ()); }
#line 2079 "src/parser.cpp"
    break;

  case 22: // cat_type: paren_type
#line 238 "gen/parser.y"
                       { yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()); }
#line 2085 "src/parser.cpp"
    break;

  case 23: // cat_expression: expr_or
#line 241 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2091 "src/parser.cpp"
    break;

  case 24: // cat_expression: expr_right
#line 242 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2097 "src/parser.cpp"
    break;

  case 25: // cat_statement: pure
#line 245 "gen/parser.y"
                   { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ()); }
#line 2103 "src/parser.cpp"
    break;

  case 26: // cat_statement: cat_expression
#line 246 "gen/parser.y"
                   { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2109 "src/parser.cpp"
    break;

  case 27: // pure: node_declaration
#line 251 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Declaration > ()); }
#line 2115 "src/parser.cpp"
    break;

  case 28: // pure: node_definition
#line 252 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Definition > ()); }
#line 2121 "src/parser.cpp"
    break;

  case 29: // pure: node_assignment
#line 253 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Assignment > ()); }
#line 2127 "src/parser.cpp"
    break;

  case 30: // pure: node_type_def
#line 254 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeDef > ()); }
#line 2133 "src/parser.cpp"
    break;

  case 31: // pure: node_function_def
#line 255 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::FunDef > ()); }
#line 2139 "src/parser.cpp"
    break;

  case 32: // pure: node_return
#line 256 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Return > ()); }
#line 2145 "src/parser.cpp"
    break;

  case 33: // pure: node_if
#line 257 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::If > ()); }
#line 2151 "src/parser.cpp"
    break;

  case 34: // pure: node_for
#line 258 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::For > ()); }
#line 2157 "src/parser.cpp"
    break;

  case 35: // pure: node_while
#line 259 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::While > ()); }
#line 2163 "src/parser.cpp"
    break;

  case 36: // pure: node_when
#line 260 "gen/parser.y"
                      { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::When > ()); }
#line 2169 "src/parser.cpp"
    break;

  case 37: // expr_or: node_or
#line 263 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Or > ()); }
#line 2175 "src/parser.cpp"
    break;

  case 38: // expr_or: expr_and
#line 264 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2181 "src/parser.cpp"
    break;

  case 39: // expr_and: node_and
#line 267 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::And > ()); }
#line 2187 "src/parser.cpp"
    break;

  case 40: // expr_and: expr_eq
#line 268 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2193 "src/parser.cpp"
    break;

  case 41: // expr_eq: node_eq
#line 271 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Eq > ()); }
#line 2199 "src/parser.cpp"
    break;

  case 42: // expr_eq: node_ne
#line 272 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Ne > ()); }
#line 2205 "src/parser.cpp"
    break;

  case 43: // expr_eq: expr_ord
#line 273 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2211 "src/parser.cpp"
    break;

  case 44: // expr_ord: node_ge
#line 276 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Ge > ()); }
#line 2217 "src/parser.cpp"
    break;

  case 45: // expr_ord: node_le
#line 277 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Le > ()); }
#line 2223 "src/parser.cpp"
    break;

  case 46: // expr_ord: node_gt
#line 278 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Gt > ()); }
#line 2229 "src/parser.cpp"
    break;

  case 47: // expr_ord: node_lt
#line 279 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Lt > ()); }
#line 2235 "src/parser.cpp"
    break;

  case 48: // expr_ord: expr_add
#line 280 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2241 "src/parser.cpp"
    break;

  case 49: // expr_add: node_add
#line 283 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Add > ()); }
#line 2247 "src/parser.cpp"
    break;

  case 50: // expr_add: node_sub
#line 284 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Sub > ()); }
#line 2253 "src/parser.cpp"
    break;

  case 51: // expr_add: expr_mul
#line 285 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2259 "src/parser.cpp"
    break;

  case 52: // expr_mul: node_mul
#line 288 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Mul > ()); }
#line 2265 "src/parser.cpp"
    break;

  case 53: // expr_mul: node_div
#line 289 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Div > ()); }
#line 2271 "src/parser.cpp"
    break;

  case 54: // expr_mul: node_mod
#line 290 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Mod > ()); }
#line 2277 "src/parser.cpp"
    break;

  case 55: // expr_mul: expr_pow
#line 291 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2283 "src/parser.cpp"
    break;

  case 56: // expr_pow: node_pow
#line 294 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Pow > ()); }
#line 2289 "src/parser.cpp"
    break;

  case 57: // expr_pow: expr_pre
#line 295 "gen/parser.y"
             { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2295 "src/parser.cpp"
    break;

  case 58: // expr_pre: node_minus
#line 298 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Minus > ()); }
#line 2301 "src/parser.cpp"
    break;

  case 59: // expr_pre: node_plus
#line 299 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Plus > ()); }
#line 2307 "src/parser.cpp"
    break;

  case 60: // expr_pre: node_not
#line 300 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Not > ()); }
#line 2313 "src/parser.cpp"
    break;

  case 61: // expr_pre: expr_post
#line 301 "gen/parser.y"
               { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2319 "src/parser.cpp"
    break;

  case 62: // expr_post: node_application
#line 304 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Application > ()); }
#line 2325 "src/parser.cpp"
    break;

  case 63: // expr_post: node_conversion
#line 305 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Conversion > ()); }
#line 2331 "src/parser.cpp"
    break;

  case 64: // expr_post: node_subscript
#line 306 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Subscript > ()); }
#line 2337 "src/parser.cpp"
    break;

  case 65: // expr_post: expr_atom
#line 307 "gen/parser.y"
                     { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2343 "src/parser.cpp"
    break;

  case 66: // expr_atom: node_name
#line 310 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Name > ()); }
#line 2349 "src/parser.cpp"
    break;

  case 67: // expr_atom: node_bool
#line 311 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Bool > ()); }
#line 2355 "src/parser.cpp"
    break;

  case 68: // expr_atom: node_int
#line 312 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Int > ()); }
#line 2361 "src/parser.cpp"
    break;

  case 69: // expr_atom: node_float
#line 313 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Float > ()); }
#line 2367 "src/parser.cpp"
    break;

  case 70: // expr_atom: node_string
#line 314 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::String > ()); }
#line 2373 "src/parser.cpp"
    break;

  case 71: // expr_atom: node_block
#line 315 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Block > ()); }
#line 2379 "src/parser.cpp"
    break;

  case 72: // expr_atom: node_array
#line 316 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Array > ()); }
#line 2385 "src/parser.cpp"
    break;

  case 73: // expr_atom: paren_expr
#line 317 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2391 "src/parser.cpp"
    break;

  case 74: // expr_right: node_expr_if
#line 320 "gen/parser.y"
                  { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::ExprIf > ()); }
#line 2397 "src/parser.cpp"
    break;

  case 75: // expr_right: node_expr_for
#line 321 "gen/parser.y"
                  { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::ExprFor > ()); }
#line 2403 "src/parser.cpp"
    break;

  case 76: // expr_right: node_function
#line 322 "gen/parser.y"
                  { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Function > ()); }
#line 2409 "src/parser.cpp"
    break;

  case 77: // expr_assgn_target: expr_post
#line 325 "gen/parser.y"
              { yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()); }
#line 2415 "src/parser.cpp"
    break;

  case 78: // paren_type: OPAREN cat_type CPAREN
#line 330 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::category::Type > () = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ());
    }
#line 2423 "src/parser.cpp"
    break;

  case 79: // paren_type: OPAREN type_list CPAREN
#line 333 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::category::Type > () = cynth::ast::node::TupleType{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::ast::category::Type> > ())};
    }
#line 2431 "src/parser.cpp"
    break;

  case 80: // paren_type: OPAREN type_list COMMA CPAREN
#line 336 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::category::Type > () = cynth::ast::node::TupleType{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::ast::category::Type> > ())};
    }
#line 2439 "src/parser.cpp"
    break;

  case 81: // void_type: OPAREN CPAREN
#line 341 "gen/parser.y"
                  {
        yylhs.value.as < cynth::ast::category::Type > () = cynth::ast::node::TupleType{};
    }
#line 2447 "src/parser.cpp"
    break;

  case 82: // void_type: VOID
#line 344 "gen/parser.y"
         {
        yylhs.value.as < cynth::ast::category::Type > () = cynth::ast::node::TupleType{};
    }
#line 2455 "src/parser.cpp"
    break;

  case 83: // node_auto: AUTO
#line 349 "gen/parser.y"
         {
        yylhs.value.as < cynth::ast::node::Auto > () = {};
    }
#line 2463 "src/parser.cpp"
    break;

  case 84: // node_type_name: TYPENAME
#line 354 "gen/parser.y"
                   {
        yylhs.value.as < cynth::ast::node::TypeName > () = {YY_MOVE (yystack_[0].value.as < std::string > ())};
    }
#line 2471 "src/parser.cpp"
    break;

  case 85: // node_const_type: cat_type CONST
#line 359 "gen/parser.y"
                         {
        yylhs.value.as < cynth::ast::node::ConstType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ())};
    }
#line 2479 "src/parser.cpp"
    break;

  case 86: // node_in_type: cat_type IN
#line 364 "gen/parser.y"
                      {
        yylhs.value.as < cynth::ast::node::InType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ())};
    }
#line 2487 "src/parser.cpp"
    break;

  case 87: // node_out_type: cat_type OUT
#line 369 "gen/parser.y"
                       {
        yylhs.value.as < cynth::ast::node::OutType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ())};
    }
#line 2495 "src/parser.cpp"
    break;

  case 88: // node_function_type: cat_type paren_type
#line 374 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::ast::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2503 "src/parser.cpp"
    break;

  case 89: // node_function_type: void_type paren_type
#line 377 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2511 "src/parser.cpp"
    break;

  case 90: // node_function_type: cat_type void_type
#line 380 "gen/parser.y"
                                {
        yylhs.value.as < cynth::ast::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2519 "src/parser.cpp"
    break;

  case 91: // node_function_type: void_type void_type
#line 383 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::ast::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 2527 "src/parser.cpp"
    break;

  case 92: // node_array_type: cat_type OBRACK cat_expression CBRACK
#line 388 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::ast::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .size = cynth::ast::category::Pattern{YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ())}};
    }
#line 2535 "src/parser.cpp"
    break;

  case 93: // node_array_type: cat_type OBRACK AUTO CBRACK
#line 391 "gen/parser.y"
                                      {
        yylhs.value.as < cynth::ast::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .size = esl::optional_component<cynth::ast::category::Pattern>{}};
    }
#line 2543 "src/parser.cpp"
    break;

  case 94: // node_array_type: cat_type OBRACK CBRACK
#line 394 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::ast::node::ArrayType > () = {.type = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Type > ()), .size = esl::optional_component<cynth::ast::category::Pattern>{}};
    }
#line 2551 "src/parser.cpp"
    break;

  case 95: // node_array_type: cat_type OBRACK cat_declaration CBRACK
#line 397 "gen/parser.y"
                                                            {
        yylhs.value.as < cynth::ast::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .size = cynth::ast::category::Pattern{YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ())}};
    }
#line 2559 "src/parser.cpp"
    break;

  case 96: // node_buffer_type: BUFFER OBRACK cat_expression CBRACK
#line 402 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::ast::node::BufferType > () = {.size = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ())};
    }
#line 2567 "src/parser.cpp"
    break;

  case 97: // node_type_decl: TYPE node_type_name
#line 407 "gen/parser.y"
                              {
        yylhs.value.as < cynth::ast::node::TypeDecl > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeName > ())};
    }
#line 2575 "src/parser.cpp"
    break;

  case 98: // paren_range_decl: OPAREN cat_range_decl CPAREN
#line 414 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::ast::category::RangeDeclaration > () = YY_MOVE (yystack_[1].value.as < cynth::ast::category::RangeDeclaration > ());
    }
#line 2583 "src/parser.cpp"
    break;

  case 99: // paren_range_decl: OPAREN range_decl_list CPAREN
#line 417 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::category::RangeDeclaration > () = cynth::ast::node::TupleRangeDecl{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::ast::category::RangeDeclaration> > ())};
    }
#line 2591 "src/parser.cpp"
    break;

  case 100: // paren_range_decl: OPAREN range_decl_list COMMA CPAREN
#line 420 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::ast::category::RangeDeclaration > () = cynth::ast::node::TupleRangeDecl{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::ast::category::RangeDeclaration> > ())};
    }
#line 2599 "src/parser.cpp"
    break;

  case 101: // paren_decl: OPAREN cat_declaration CPAREN
#line 425 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::ast::category::Declaration > () = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ());
    }
#line 2607 "src/parser.cpp"
    break;

  case 102: // paren_decl: OPAREN decl_list CPAREN
#line 428 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::category::Declaration > () = cynth::ast::node::TupleDecl{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::ast::category::Declaration> > ())};
    }
#line 2615 "src/parser.cpp"
    break;

  case 103: // paren_decl: OPAREN decl_list COMMA CPAREN
#line 431 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::category::Declaration > () = cynth::ast::node::TupleDecl{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::ast::category::Declaration> > ())};
    }
#line 2623 "src/parser.cpp"
    break;

  case 104: // void_decl: OPAREN CPAREN
#line 436 "gen/parser.y"
                  {
        yylhs.value.as < cynth::ast::category::Declaration > () = cynth::ast::node::TupleDecl{};
    }
#line 2631 "src/parser.cpp"
    break;

  case 105: // node_declaration: cat_type node_name
#line 441 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Declaration > () = {.name = YY_MOVE (yystack_[0].value.as < cynth::ast::node::Name > ()), .type = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ())};
    }
#line 2639 "src/parser.cpp"
    break;

  case 106: // node_range_decl: cat_declaration IN cat_expression
#line 446 "gen/parser.y"
                                                   {
        yylhs.value.as < cynth::ast::node::RangeDecl > () = {.declaration = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Declaration > ()), .range = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2647 "src/parser.cpp"
    break;

  case 107: // node_range_to: cat_expression TO cat_expression
#line 453 "gen/parser.y"
                                               {
        yylhs.value.as < cynth::ast::node::RangeTo > () = {.from = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), .to = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2655 "src/parser.cpp"
    break;

  case 108: // node_range_to_by: cat_expression TO cat_expression BY cat_expression
#line 458 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::ast::node::RangeToBy > () = {.from = YY_MOVE (yystack_[4].value.as < cynth::ast::category::Expression > ()), .to = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), .by = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2663 "src/parser.cpp"
    break;

  case 109: // node_spread: ELIP cat_expression
#line 463 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Spread > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2671 "src/parser.cpp"
    break;

  case 110: // paren_expr: OPAREN cat_expression CPAREN
#line 470 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::ast::category::Expression > () = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ());
    }
#line 2679 "src/parser.cpp"
    break;

  case 111: // paren_expr: OPAREN expr_list CPAREN
#line 473 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::category::Expression > () = cynth::ast::node::Tuple{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::ast::category::Expression> > ())};
    }
#line 2687 "src/parser.cpp"
    break;

  case 112: // paren_expr: OPAREN expr_list COMMA CPAREN
#line 476 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::category::Expression > () = cynth::ast::node::Tuple{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::ast::category::Expression> > ())};
    }
#line 2695 "src/parser.cpp"
    break;

  case 113: // void: OPAREN CPAREN
#line 481 "gen/parser.y"
                  {
        yylhs.value.as < cynth::ast::category::Expression > () = cynth::ast::node::Tuple{};
    }
#line 2703 "src/parser.cpp"
    break;

  case 114: // node_name: NAME
#line 486 "gen/parser.y"
               {
        yylhs.value.as < cynth::ast::node::Name > () = {YY_MOVE (yystack_[0].value.as < std::string > ())};
    }
#line 2711 "src/parser.cpp"
    break;

  case 115: // node_block: OBRACE CBRACE
#line 491 "gen/parser.y"
                  {
        yylhs.value.as < cynth::ast::node::Block > () = {};
    }
#line 2719 "src/parser.cpp"
    break;

  case 116: // node_block: OBRACE stmt_list CBRACE
#line 494 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::node::Block > () = {YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::ast::category::Statement> > ())};
    }
#line 2727 "src/parser.cpp"
    break;

  case 117: // node_block: OBRACE stmt_list SEMI CBRACE
#line 497 "gen/parser.y"
                                       {
        yylhs.value.as < cynth::ast::node::Block > () = {YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::ast::category::Statement> > ())};
    }
#line 2735 "src/parser.cpp"
    break;

  case 118: // node_bool: TRUE
#line 504 "gen/parser.y"
         {
        yylhs.value.as < cynth::ast::node::Bool > () = {true};
    }
#line 2743 "src/parser.cpp"
    break;

  case 119: // node_bool: FALSE
#line 507 "gen/parser.y"
          {
        yylhs.value.as < cynth::ast::node::Bool > () = {false};
    }
#line 2751 "src/parser.cpp"
    break;

  case 120: // node_int: INT
#line 512 "gen/parser.y"
        {
        yylhs.value.as < cynth::ast::node::Int > () = {esl::stoi<cynth::sem::Integral>(YY_MOVE (yystack_[0].value.as < std::string > ()))}; // TODO: The sem::Integral type should be obtainable from ast::node::Int
    }
#line 2759 "src/parser.cpp"
    break;

  case 121: // node_float: FLOAT
#line 517 "gen/parser.y"
          {
        yylhs.value.as < cynth::ast::node::Float > () = {std::stof(YY_MOVE (yystack_[0].value.as < std::string > ()))};
    }
#line 2767 "src/parser.cpp"
    break;

  case 122: // node_string: STRING
#line 522 "gen/parser.y"
           {
        yylhs.value.as < cynth::ast::node::String > () = {esl::trim(YY_MOVE (yystack_[0].value.as < std::string > ()))};
    }
#line 2775 "src/parser.cpp"
    break;

  case 123: // node_function: cat_type FN paren_decl cat_expression
#line 527 "gen/parser.y"
                                                         {
        yylhs.value.as < cynth::ast::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2783 "src/parser.cpp"
    break;

  case 124: // node_function: void_type FN paren_decl cat_expression
#line 530 "gen/parser.y"
                                                          {
        yylhs.value.as < cynth::ast::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2791 "src/parser.cpp"
    break;

  case 125: // node_function: cat_type FN void_decl cat_expression
#line 533 "gen/parser.y"
                                                        {
        yylhs.value.as < cynth::ast::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2799 "src/parser.cpp"
    break;

  case 126: // node_function: void_type FN void_decl cat_expression
#line 536 "gen/parser.y"
                                                         {
        yylhs.value.as < cynth::ast::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2807 "src/parser.cpp"
    break;

  case 127: // node_array: OBRACK CBRACK
#line 541 "gen/parser.y"
                  {
        yylhs.value.as < cynth::ast::node::Array > () = {};
    }
#line 2815 "src/parser.cpp"
    break;

  case 128: // node_array: OBRACK array_elem_list CBRACK
#line 544 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::node::Array > () = {YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::ast::category::ArrayElement> > ())};
    }
#line 2823 "src/parser.cpp"
    break;

  case 129: // node_array: OBRACK array_elem_list SEMI CBRACK
#line 547 "gen/parser.y"
                                             {
        yylhs.value.as < cynth::ast::node::Array > () = {YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::ast::category::ArrayElement> > ())};
    }
#line 2831 "src/parser.cpp"
    break;

  case 130: // node_or: expr_or OR expr_and
#line 554 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::node::Or > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2839 "src/parser.cpp"
    break;

  case 131: // node_and: expr_and AND expr_eq
#line 559 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::And > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2847 "src/parser.cpp"
    break;

  case 132: // node_eq: expr_eq EQ expr_ord
#line 564 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::node::Eq > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2855 "src/parser.cpp"
    break;

  case 133: // node_ne: expr_eq NE expr_ord
#line 569 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::ast::node::Ne > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2863 "src/parser.cpp"
    break;

  case 134: // node_ge: expr_ord GE expr_add
#line 574 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Ge > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2871 "src/parser.cpp"
    break;

  case 135: // node_le: expr_ord LE expr_add
#line 579 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Le > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2879 "src/parser.cpp"
    break;

  case 136: // node_gt: expr_ord GT expr_add
#line 584 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Gt > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2887 "src/parser.cpp"
    break;

  case 137: // node_lt: expr_ord LT expr_add
#line 589 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::ast::node::Lt > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2895 "src/parser.cpp"
    break;

  case 138: // node_add: expr_add ADD expr_mul
#line 594 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Add > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2903 "src/parser.cpp"
    break;

  case 139: // node_sub: expr_add SUB expr_mul
#line 599 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Sub > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2911 "src/parser.cpp"
    break;

  case 140: // node_mul: expr_mul MUL expr_pow
#line 604 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Mul > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2919 "src/parser.cpp"
    break;

  case 141: // node_div: expr_mul DIV expr_pow
#line 609 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Div > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2927 "src/parser.cpp"
    break;

  case 142: // node_mod: expr_mul MOD expr_pow
#line 614 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Mod > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2935 "src/parser.cpp"
    break;

  case 143: // node_pow: expr_pre POW expr_pow
#line 619 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::ast::node::Pow > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2943 "src/parser.cpp"
    break;

  case 144: // node_minus: SUB expr_pre
#line 624 "gen/parser.y"
                      {
        yylhs.value.as < cynth::ast::node::Minus > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2951 "src/parser.cpp"
    break;

  case 145: // node_plus: ADD expr_pre
#line 629 "gen/parser.y"
                      {
        yylhs.value.as < cynth::ast::node::Plus > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2959 "src/parser.cpp"
    break;

  case 146: // node_not: NOT expr_pre
#line 634 "gen/parser.y"
                      {
        yylhs.value.as < cynth::ast::node::Not > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2967 "src/parser.cpp"
    break;

  case 147: // node_application: expr_post paren_expr
#line 639 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::ast::node::Application > () = {.function = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ()), .arguments = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2975 "src/parser.cpp"
    break;

  case 148: // node_application: expr_post void
#line 642 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::node::Application > () = {.function = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ()), .arguments = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2983 "src/parser.cpp"
    break;

  case 149: // node_conversion: cat_type paren_expr
#line 647 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::ast::node::Conversion > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()), .argument = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 2991 "src/parser.cpp"
    break;

  case 150: // node_subscript: expr_post OBRACK array_elem_list CBRACK
#line 652 "gen/parser.y"
                                                                 {
        yylhs.value.as < cynth::ast::node::Subscript > () = {.container = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Expression > ()), .location = YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::ast::category::ArrayElement> > ())};
    }
#line 2999 "src/parser.cpp"
    break;

  case 151: // node_subscript: expr_post OBRACK CBRACK
#line 655 "gen/parser.y"
                                       {
        yylhs.value.as < cynth::ast::node::Subscript > () = {.container = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), .location = {}};
    }
#line 3007 "src/parser.cpp"
    break;

  case 152: // node_expr_if: IF paren_expr cat_expression ELSE cat_expression
#line 660 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::ast::node::ExprIf > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Expression > ()), .positive_branch = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), .negative_branch = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 3015 "src/parser.cpp"
    break;

  case 153: // node_expr_for: FOR paren_range_decl cat_expression
#line 665 "gen/parser.y"
                                                    {
        yylhs.value.as < cynth::ast::node::ExprFor > () = {.declarations = YY_MOVE (yystack_[1].value.as < cynth::ast::category::RangeDeclaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 3023 "src/parser.cpp"
    break;

  case 154: // node_definition: cat_declaration ASSGN cat_expression
#line 672 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::ast::node::Definition > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Declaration > ()), .value = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 3031 "src/parser.cpp"
    break;

  case 155: // node_assignment: expr_assgn_target ASSGN cat_expression
#line 677 "gen/parser.y"
                                                        {
        yylhs.value.as < cynth::ast::node::Assignment > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), .value = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 3039 "src/parser.cpp"
    break;

  case 156: // node_type_def: TYPE node_type_name ASSGN cat_type
#line 682 "gen/parser.y"
                                                     {
        yylhs.value.as < cynth::ast::node::TypeDef > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::ast::node::TypeName > ()), .type = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 3047 "src/parser.cpp"
    break;

  case 157: // node_function_def: cat_type node_name paren_decl cat_expression
#line 687 "gen/parser.y"
                                                                      {
        yylhs.value.as < cynth::ast::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 3055 "src/parser.cpp"
    break;

  case 158: // node_function_def: void_type node_name paren_decl cat_expression
#line 690 "gen/parser.y"
                                                                       {
        yylhs.value.as < cynth::ast::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 3063 "src/parser.cpp"
    break;

  case 159: // node_function_def: cat_type node_name void_decl cat_expression
#line 693 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::ast::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 3071 "src/parser.cpp"
    break;

  case 160: // node_function_def: void_type node_name void_decl cat_expression
#line 696 "gen/parser.y"
                                                                      {
        yylhs.value.as < cynth::ast::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 3079 "src/parser.cpp"
    break;

  case 161: // node_return: RETURN cat_expression
#line 701 "gen/parser.y"
                               {
        yylhs.value.as < cynth::ast::node::Return > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 3087 "src/parser.cpp"
    break;

  case 162: // node_return: RETURN void
#line 704 "gen/parser.y"
                     {
        yylhs.value.as < cynth::ast::node::Return > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 3095 "src/parser.cpp"
    break;

  case 163: // node_return: RETURN
#line 707 "gen/parser.y"
           {
        yylhs.value.as < cynth::ast::node::Return > () = {cynth::ast::category::Expression{cynth::ast::node::Tuple{}}};
    }
#line 3103 "src/parser.cpp"
    break;

  case 164: // node_if: IF paren_expr pure ELSE pure
#line 712 "gen/parser.y"
                                                 {
        yylhs.value.as < cynth::ast::node::If > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Expression > ()), .positive_branch = YY_MOVE (yystack_[2].value.as < cynth::ast::category::Statement > ()), .negative_branch = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ())};
    }
#line 3111 "src/parser.cpp"
    break;

  case 165: // node_if: IF paren_expr pure SEMI ELSE pure
#line 715 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::ast::node::If > () = {.condition = YY_MOVE (yystack_[4].value.as < cynth::ast::category::Expression > ()), .positive_branch = YY_MOVE (yystack_[3].value.as < cynth::ast::category::Statement > ()), .negative_branch = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ())};
    }
#line 3119 "src/parser.cpp"
    break;

  case 166: // node_when: WHEN paren_expr cat_statement
#line 720 "gen/parser.y"
                                             {
        yylhs.value.as < cynth::ast::node::When > () = {.condition = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ()), .branch = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ())};
    }
#line 3127 "src/parser.cpp"
    break;

  case 167: // node_for: FOR paren_range_decl pure
#line 725 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::ast::node::For > () = {.declarations = YY_MOVE (yystack_[1].value.as < cynth::ast::category::RangeDeclaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ())};
    }
#line 3135 "src/parser.cpp"
    break;

  case 168: // node_while: WHILE paren_expr cat_statement
#line 730 "gen/parser.y"
                                               {
        yylhs.value.as < cynth::ast::node::While > () = {.condition = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expression > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ())};
    }
#line 3143 "src/parser.cpp"
    break;

  case 169: // array_elem_list: cat_array_elem
#line 737 "gen/parser.y"
                          {
        yylhs.value.as < esl::component_vector<cynth::ast::category::ArrayElement> > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::ArrayElement > ())};
    }
#line 3151 "src/parser.cpp"
    break;

  case 170: // array_elem_list: array_elem_list COMMA cat_array_elem
#line 740 "gen/parser.y"
                                                     {
        yylhs.value.as < esl::component_vector<cynth::ast::category::ArrayElement> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::ArrayElement > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::ast::category::ArrayElement> > ()));
    }
#line 3159 "src/parser.cpp"
    break;

  case 171: // stmt_list: cat_statement
#line 745 "gen/parser.y"
                         {
        yylhs.value.as < esl::component_vector<cynth::ast::category::Statement> > () = {YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ())};
    }
#line 3167 "src/parser.cpp"
    break;

  case 172: // stmt_list: stmt_list SEMI cat_statement
#line 748 "gen/parser.y"
                                             {
        yylhs.value.as < esl::component_vector<cynth::ast::category::Statement> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::ast::category::Statement> > ()));
    }
#line 3175 "src/parser.cpp"
    break;

  case 173: // type_list: cat_type COMMA cat_type
#line 753 "gen/parser.y"
                                           {
        yylhs.value.as < esl::component_vector<cynth::ast::category::Type> > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Type > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())};
    }
#line 3183 "src/parser.cpp"
    break;

  case 174: // type_list: type_list COMMA cat_type
#line 756 "gen/parser.y"
                                         {
        yylhs.value.as < esl::component_vector<cynth::ast::category::Type> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::ast::category::Type> > ()));
    }
#line 3191 "src/parser.cpp"
    break;

  case 175: // expr_list: cat_expression COMMA cat_expression
#line 761 "gen/parser.y"
                                                       {
        yylhs.value.as < esl::component_vector<cynth::ast::category::Expression> > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ())};
    }
#line 3199 "src/parser.cpp"
    break;

  case 176: // expr_list: expr_list COMMA cat_expression
#line 764 "gen/parser.y"
                                               {
        yylhs.value.as < esl::component_vector<cynth::ast::category::Expression> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expression > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::ast::category::Expression> > ()));
    }
#line 3207 "src/parser.cpp"
    break;

  case 177: // decl_list: cat_declaration COMMA cat_declaration
#line 769 "gen/parser.y"
                                                         {
        yylhs.value.as < esl::component_vector<cynth::ast::category::Declaration> > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::Declaration > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::Declaration > ())};
    }
#line 3215 "src/parser.cpp"
    break;

  case 178: // decl_list: decl_list COMMA cat_declaration
#line 772 "gen/parser.y"
                                                {
        yylhs.value.as < esl::component_vector<cynth::ast::category::Declaration> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Declaration > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::ast::category::Declaration> > ()));
    }
#line 3223 "src/parser.cpp"
    break;

  case 179: // range_decl_list: cat_range_decl COMMA cat_range_decl
#line 777 "gen/parser.y"
                                                       {
        yylhs.value.as < esl::component_vector<cynth::ast::category::RangeDeclaration> > () = {YY_MOVE (yystack_[2].value.as < cynth::ast::category::RangeDeclaration > ()), YY_MOVE (yystack_[0].value.as < cynth::ast::category::RangeDeclaration > ())};
    }
#line 3231 "src/parser.cpp"
    break;

  case 180: // range_decl_list: range_decl_list COMMA cat_range_decl
#line 780 "gen/parser.y"
                                                     {
        yylhs.value.as < esl::component_vector<cynth::ast::category::RangeDeclaration> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::ast::category::RangeDeclaration > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::ast::category::RangeDeclaration> > ()));
    }
#line 3239 "src/parser.cpp"
    break;


#line 3243 "src/parser.cpp"

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





  const short parser::yypact_ninf_ = -133;

  const signed char parser::yytable_ninf_ = -82;

  const short
  parser::yypact_[] =
  {
     597,  -133,  -133,  -133,  -133,  -133,   -22,   -22,    33,   -22,
      63,   -21,   997,  -133,  -133,  -133,   717,    41,   637,  -133,
     470,   470,   470,    91,   551,   107,  -133,  -133,  -133,    88,
      95,   -17,   178,     4,   195,  -133,   105,    61,  -133,  -133,
     143,  -133,    52,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,   160,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,   161,  1037,   597,   597,   391,   597,
     597,   175,  1037,   -22,    33,    63,   757,   110,  -133,    94,
      36,  -133,  -133,   490,   -20,     3,  -133,   114,   139,   142,
    -133,   -13,  1037,   797,  -133,  -133,   168,  -133,  -133,  -133,
      46,   149,  -133,    57,  -133,  -133,  -133,   177,  -133,  -133,
    -133,   837,  -133,  -133,  -133,   177,  1037,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     470,   877,   677,  -133,  -133,  1037,   177,   173,  -133,  -133,
     177,   597,   191,    -7,  -133,   241,    60,   187,   157,  -133,
    -133,   174,  -133,  -133,  -133,  1127,   188,  1037,  1037,  -133,
      87,  1149,  1127,  -133,  -133,  1146,  -133,  1037,  -133,   359,
    -133,  1087,  -133,   917,  -133,   524,  -133,  -133,  1037,   203,
     957,  -133,  1100,  1037,  1037,   205,  -133,   551,   207,   210,
    1037,  1037,  -133,    95,   -17,   178,   178,     4,     4,     4,
       4,   195,   195,  -133,  -133,  -133,  -133,  -133,  -133,   102,
    -133,  1037,  1037,  1164,  1037,  1037,  -133,  1037,  1077,   212,
     544,    96,  1037,   391,  -133,  1119,  -133,   634,  -133,   634,
    1123,  -133,  -133,  -133,   634,  -133,  -133,  -133,  -133,  -133,
     202,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,   -22,    33,   367,
    -133,    94,     8,  1077,  -133,  -133,  -133,  -133,  1037,  1077,
    1077,  -133,  -133
  };

  const unsigned char
  parser::yydefact_[] =
  {
       2,   114,    84,   120,   121,   122,     0,     0,     0,     0,
       0,     0,   163,   118,   119,    83,     0,     0,     0,    82,
       0,     0,     0,     0,     0,     0,    26,   171,    25,    23,
      38,    40,    43,    48,    51,    55,    57,    61,    65,    24,
       0,    22,     0,    13,    14,    19,    20,    21,    15,    16,
      17,    18,     6,    27,    73,    66,    71,    67,    68,    69,
      70,    76,    72,    37,    39,    41,    42,    44,    45,    46,
      47,    49,    50,    52,    53,    54,    56,    59,    58,    60,
      62,    63,    64,    74,    75,    28,    29,    31,    30,    32,
      33,    36,    34,    35,     3,     0,     0,     0,     0,     0,
       0,    97,     0,     0,     0,     0,     0,     0,   161,    61,
       0,   162,    81,     0,     0,     0,     5,     0,     0,     0,
     115,     0,     0,     0,   127,   169,    12,     9,    10,    11,
       0,     0,   145,     0,   144,   146,     1,     0,    85,    86,
      87,     0,    88,    90,   149,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   147,   148,     0,     0,     0,    89,    91,
       0,     4,     0,     0,   166,     0,     0,     0,     0,     8,
       7,     0,   153,   167,   168,     0,     0,     0,     0,    97,
     113,     0,     0,    78,   105,     0,   101,     0,   110,     0,
      79,     0,   102,     0,   111,     0,   116,   109,     0,     0,
       0,   128,     0,     0,     0,    83,    94,     0,     0,     0,
       0,     0,   154,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   113,   151,     0,
     155,     0,     0,     0,     0,     0,   172,     0,     0,     0,
       0,     0,     0,     0,    98,     0,    99,   156,    96,   173,
       0,   177,   175,    80,   174,   103,   178,   112,   176,   117,
     107,   129,   170,   104,   123,   125,    93,    95,    92,   157,
     159,   150,   124,   126,   158,   160,   152,     0,     0,     0,
     164,    77,     0,     0,   106,   179,   100,   180,     0,     0,
       0,   165,   108
  };

  const short
  parser::yypgoto_[] =
  {
    -133,  -133,   198,    72,   -92,    39,   220,   -96,   -69,  -133,
      99,   103,   -45,   155,    54,   171,   120,    18,  -133,  -133,
    -133,   335,     0,  -133,     6,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -106,    17,  -132,   226,  -133,  -133,  -133,  -133,
      -1,   240,   -10,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,   100,  -133,   246
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,    23,   107,    25,   178,   125,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,   109,    38,    39,
      40,    41,   110,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,   179,   214,    53,   180,   127,   128,   129,
      54,   164,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,   117,   118,   181,   130,   119,    94
  };

  const short
  parser::yytable_[] =
  {
      42,   174,   248,   195,   184,    96,    97,    95,   100,   205,
     196,     1,   102,   221,   145,   249,   101,    42,    37,   206,
     133,   133,   133,   144,   143,    99,   197,   173,   149,   150,
     183,   213,   170,   198,   242,    37,   163,   167,   245,   220,
     155,   156,   169,    19,     1,     2,     3,     4,     5,     6,
     166,     7,     8,     9,    10,     1,    11,    12,    13,    14,
     241,    15,    98,     1,   244,   167,   166,     2,   209,   210,
      16,    19,    17,   120,    18,   246,    19,    20,    21,   138,
     211,   167,   -77,    22,   139,   140,   167,    19,   114,   167,
     161,   136,    19,   141,   162,    19,    42,    42,   133,    42,
      42,   -81,   187,   194,   225,   226,   144,   143,   163,   246,
     169,   189,   144,   143,    37,    37,   -81,    37,    37,   195,
     252,   188,   -81,   161,   137,   210,   196,   162,   146,   138,
     144,   143,   147,   169,   139,   140,   281,   199,   148,   123,
     132,   134,   135,   141,   200,    19,   160,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   295,   201,   297,   165,   203,   194,   133,   138,   202,
     177,    42,   204,   139,   140,   133,   143,     2,   123,   290,
     253,    -5,   141,   171,    19,   133,   105,   254,    11,    37,
     144,   143,   133,    15,   208,   133,   185,   255,    24,   133,
     247,   133,   167,   112,   256,    42,   212,   194,    19,   231,
     232,   252,   133,   218,   113,    24,   144,   143,   131,   131,
     131,   293,   258,    37,   301,   151,   152,   153,   154,   298,
     173,   183,   108,   157,   158,   159,   115,   271,   126,   276,
     194,   277,   116,   143,   278,     2,   223,   251,   292,   272,
     143,   224,   111,   133,   105,   133,    11,   143,     0,   143,
     133,    15,   239,   121,   143,     0,   291,   261,     0,     0,
     175,   112,     0,   266,     0,     0,    19,     0,     0,   145,
       0,     0,   170,     0,   114,     0,   299,     0,   144,   143,
     163,     0,   169,   292,    24,    24,   176,    24,    24,   292,
     292,     0,     0,     0,   191,   300,   227,   228,   229,   230,
       0,   291,     0,     0,     0,   115,   172,   291,   291,   182,
       0,   191,   186,     0,   116,   177,   115,   177,   233,   234,
     235,   236,   114,     0,     0,     0,     0,     0,     0,   217,
       0,     0,   207,   115,     0,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   142,
       0,   219,     0,     2,     0,   243,   222,   116,     0,    24,
       1,     0,   105,   250,    11,     0,     0,   168,     0,    15,
       0,   115,   126,   257,     0,   240,   138,     0,   167,   263,
     259,   139,   140,   176,    19,     2,   123,   264,     0,   176,
     141,   116,    19,    24,   105,     0,    11,   172,   182,     0,
     176,    15,     0,     0,     0,     0,     0,   262,     0,     0,
     175,   116,     0,   268,     0,     0,    19,   116,   270,     0,
     126,     0,     0,   274,   275,     0,     0,     0,   116,     0,
     279,   280,   142,     0,     0,   168,   289,     0,   142,     0,
       0,   176,     0,   176,     0,     0,     0,     0,   250,     0,
       0,   282,   283,     0,   284,   285,   142,   286,   168,     0,
       0,     0,   294,     1,     2,     3,     4,     5,     0,   116,
       0,   116,     0,   105,     0,    11,   116,    13,    14,     0,
      15,   289,     0,     1,     0,     0,     0,   289,   289,   123,
       0,    17,     0,    18,   137,    19,    20,    21,     0,   138,
       0,   142,    22,   192,   139,   140,     0,     0,   302,   123,
     193,     0,     0,   141,     0,    19,   142,     1,     2,     3,
       4,     5,     6,     0,     7,     8,     9,    10,     0,    11,
      12,    13,    14,     0,    15,     0,     0,     1,     0,     0,
       0,     0,   142,    16,     1,    17,   269,    18,     0,    19,
      20,    21,     0,   138,     0,   137,    22,   192,   139,   140,
     138,     0,     0,   167,   193,   139,   140,   141,   142,    19,
     123,     0,     0,     0,   141,   142,    19,     0,     0,     0,
       0,     0,   142,     0,   142,     0,     0,     0,     0,   142,
       1,     2,     3,     4,     5,     6,     0,     7,     8,     9,
      10,     0,    11,    12,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,   142,     0,    16,   168,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   103,     0,     0,   104,     0,
     105,     0,    11,   138,    13,    14,     0,    15,   139,   140,
       0,     0,     0,   167,     0,   122,   123,   141,    17,    19,
      18,   124,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   103,     0,     0,   104,     0,
     105,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,   122,   123,     0,    17,     0,
      18,   238,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   103,     0,     0,   104,     0,
     105,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,    16,   112,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   103,     0,     0,   104,     0,
     105,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,   123,   190,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   103,     0,     0,   104,     0,
     105,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,   123,   112,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   103,     0,     0,   104,     0,
     105,     0,    11,     0,    13,    14,     0,   215,     0,     0,
       0,     0,     0,     0,     0,     0,    16,     0,    17,     0,
      18,   216,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   103,     0,     0,   104,     0,
     105,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,   123,   237,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   103,     0,     0,   104,     0,
     105,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,   123,   267,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   103,     0,     0,   104,     0,
     105,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,   122,   123,     0,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   103,     0,     0,   104,     0,
     105,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,   106,     0,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   103,     0,     0,   104,     0,
     105,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,   123,     0,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   287,     0,     7,   288,     9,
      10,     2,    11,    12,    13,    14,     0,    15,     0,     0,
     105,     0,    11,     0,     2,     0,    16,    15,    17,     0,
      18,     0,    19,   105,     0,    11,   260,   265,     0,     0,
      15,     0,    19,     2,     0,     0,     0,     2,     0,   260,
     273,     2,   105,     0,    11,    19,   105,     0,    11,    15,
     105,     0,    11,    15,     0,     0,     0,    15,   175,   296,
       2,     0,   260,   112,    19,     0,   167,     0,    19,   105,
       0,    11,    19,   137,     0,     0,    15,     0,   138,     0,
       0,     0,   192,   139,   140,   260,     0,     0,   123,   193,
       0,    19,   141,   138,    19,     0,     0,   192,   139,   140,
       0,     0,     0,   167,   193,     0,     0,   141,     0,    19
  };

  const short
  parser::yycheck_[] =
  {
       0,    97,     9,    23,   100,     6,     7,    29,     9,    22,
      30,     3,    33,   145,    24,    22,    10,    17,     0,    32,
      20,    21,    22,    24,    24,     8,    23,    96,    45,    46,
      99,   137,    42,    30,   166,    17,    37,    29,   170,   145,
      36,    37,    42,    35,     3,     4,     5,     6,     7,     8,
      14,    10,    11,    12,    13,     3,    15,    16,    17,    18,
     166,    20,    29,     3,   170,    29,    14,     4,    22,    23,
      29,    35,    31,    32,    33,   171,    35,    36,    37,    19,
      34,    29,    21,    42,    24,    25,    29,    35,    16,    29,
      29,     0,    35,    33,    33,    35,    96,    97,    98,    99,
     100,    14,   103,   113,   149,   150,   107,   107,   109,   205,
     110,   105,   113,   113,    96,    97,    29,    99,   100,    23,
      24,   104,    35,    29,    14,    23,    30,    33,    21,    19,
     131,   131,    44,   133,    24,    25,    34,    23,    43,    29,
      20,    21,    22,    33,    30,    35,    41,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   253,    23,   255,    21,    23,   176,   167,    19,    30,
      98,   171,    30,    24,    25,   175,   176,     4,    29,   248,
      23,    21,    33,    22,    35,   185,    13,    30,    15,   171,
     191,   191,   192,    20,    26,   195,    21,    23,     0,   199,
       9,   201,    29,    30,    30,   205,    29,   217,    35,   155,
     156,    24,   212,   141,    16,    17,   217,   217,    20,    21,
      22,     9,    34,   205,   293,    47,    48,    49,    50,    27,
     299,   300,    12,    38,    39,    40,    16,    34,    18,    34,
     250,    34,    16,   243,    34,     4,   147,   175,   248,   210,
     250,   148,    12,   253,    13,   255,    15,   257,    -1,   259,
     260,    20,   162,    17,   264,    -1,   248,   195,    -1,    -1,
      29,    30,    -1,   201,    -1,    -1,    35,    -1,    -1,   289,
      -1,    -1,   292,    -1,   212,    -1,   287,    -1,   289,   289,
     291,    -1,   292,   293,    96,    97,    98,    99,   100,   299,
     300,    -1,    -1,    -1,   106,   288,   151,   152,   153,   154,
      -1,   293,    -1,    -1,    -1,    95,    96,   299,   300,    99,
      -1,   123,   102,    -1,    98,   253,   106,   255,   157,   158,
     159,   160,   260,    -1,    -1,    -1,    -1,    -1,    -1,   141,
      -1,    -1,   122,   123,    -1,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,    24,
      -1,   141,    -1,     4,    -1,   167,   146,   141,    -1,   171,
       3,    -1,    13,   175,    15,    -1,    -1,    42,    -1,    20,
      -1,   161,   162,   185,    -1,   165,    19,    -1,    29,    30,
     192,    24,    25,   195,    35,     4,    29,   199,    -1,   201,
      33,   175,    35,   205,    13,    -1,    15,   187,   188,    -1,
     212,    20,    -1,    -1,    -1,    -1,    -1,   197,    -1,    -1,
      29,   195,    -1,   203,    -1,    -1,    35,   201,   208,    -1,
     210,    -1,    -1,   213,   214,    -1,    -1,    -1,   212,    -1,
     220,   221,   107,    -1,    -1,   110,   248,    -1,   113,    -1,
      -1,   253,    -1,   255,    -1,    -1,    -1,    -1,   260,    -1,
      -1,   241,   242,    -1,   244,   245,   131,   247,   133,    -1,
      -1,    -1,   252,     3,     4,     5,     6,     7,    -1,   253,
      -1,   255,    -1,    13,    -1,    15,   260,    17,    18,    -1,
      20,   293,    -1,     3,    -1,    -1,    -1,   299,   300,    29,
      -1,    31,    -1,    33,    14,    35,    36,    37,    -1,    19,
      -1,   176,    42,    23,    24,    25,    -1,    -1,   298,    29,
      30,    -1,    -1,    33,    -1,    35,   191,     3,     4,     5,
       6,     7,     8,    -1,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    -1,    20,    -1,    -1,     3,    -1,    -1,
      -1,    -1,   217,    29,     3,    31,    32,    33,    -1,    35,
      36,    37,    -1,    19,    -1,    14,    42,    23,    24,    25,
      19,    -1,    -1,    29,    30,    24,    25,    33,   243,    35,
      29,    -1,    -1,    -1,    33,   250,    35,    -1,    -1,    -1,
      -1,    -1,   257,    -1,   259,    -1,    -1,    -1,    -1,   264,
       3,     4,     5,     6,     7,     8,    -1,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,   289,    -1,    29,   292,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      13,    -1,    15,    19,    17,    18,    -1,    20,    24,    25,
      -1,    -1,    -1,    29,    -1,    28,    29,    33,    31,    35,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      13,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    31,    -1,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      13,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      13,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      13,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      13,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      13,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      13,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      13,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      13,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      13,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    10,    11,    12,
      13,     4,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      13,    -1,    15,    -1,     4,    -1,    29,    20,    31,    -1,
      33,    -1,    35,    13,    -1,    15,    29,    30,    -1,    -1,
      20,    -1,    35,     4,    -1,    -1,    -1,     4,    -1,    29,
      30,     4,    13,    -1,    15,    35,    13,    -1,    15,    20,
      13,    -1,    15,    20,    -1,    -1,    -1,    20,    29,    30,
       4,    -1,    29,    30,    35,    -1,    29,    -1,    35,    13,
      -1,    15,    35,    14,    -1,    -1,    20,    -1,    19,    -1,
      -1,    -1,    23,    24,    25,    29,    -1,    -1,    29,    30,
      -1,    35,    33,    19,    35,    -1,    -1,    23,    24,    25,
      -1,    -1,    -1,    29,    30,    -1,    -1,    33,    -1,    35
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,     8,    10,    11,    12,
      13,    15,    16,    17,    18,    20,    29,    31,    33,    35,
      36,    37,    42,    53,    54,    55,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    87,    92,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   138,    29,    92,    92,    29,    85,
      92,    76,    33,     8,    11,    13,    29,    54,    58,    69,
      74,    93,    30,    54,    55,    58,    87,   133,   134,   137,
      32,   138,    28,    29,    34,    57,    58,    89,    90,    91,
     136,    54,    68,    74,    68,    68,     0,    14,    19,    24,
      25,    33,    73,    74,    92,    94,    21,    44,    43,    45,
      46,    47,    48,    49,    50,    36,    37,    38,    39,    40,
      41,    29,    33,    92,    93,    21,    14,    29,    73,    74,
      94,    22,    58,    60,    59,    29,    54,    55,    56,    85,
      88,   135,    58,    60,    59,    21,    58,    92,    85,    76,
      30,    54,    23,    30,    94,    23,    30,    23,    30,    23,
      30,    23,    30,    23,    30,    22,    32,    58,    26,    22,
      23,    34,    29,    84,    86,    20,    34,    54,    55,    58,
      84,    86,    58,    62,    63,    64,    64,    65,    65,    65,
      65,    66,    66,    67,    67,    67,    67,    30,    34,   136,
      58,    84,    86,    54,    84,    86,    59,     9,     9,    22,
      54,    55,    24,    23,    30,    23,    30,    54,    34,    54,
      29,    55,    58,    30,    54,    30,    55,    30,    58,    32,
      58,    34,    57,    30,    58,    58,    34,    34,    34,    58,
      58,    34,    58,    58,    58,    58,    58,     8,    11,    54,
      60,    69,    74,     9,    58,    56,    30,    56,    27,    92,
      85,    60,    58
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    52,    53,    53,    53,    55,    55,    56,    56,    57,
      57,    57,    57,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    58,    58,    59,    59,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    61,    61,    62,
      62,    63,    63,    63,    64,    64,    64,    64,    64,    65,
      65,    65,    66,    66,    66,    66,    67,    67,    68,    68,
      68,    68,    69,    69,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    71,    72,    73,    73,
      73,    74,    74,    75,    76,    77,    78,    79,    80,    80,
      80,    80,    81,    81,    81,    81,    82,    83,    85,    85,
      85,    84,    84,    84,    86,    87,    88,    89,    90,    91,
      92,    92,    92,    93,    94,    95,    95,    95,    96,    96,
      97,    98,    99,   100,   100,   100,   100,   101,   101,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   117,   116,   118,   119,   119,   120,
     121,   121,   122,   123,   124,   125,   127,   126,   126,   126,
     126,   128,   128,   128,   129,   129,   130,   131,   132,   136,
     136,   138,   138,   133,   133,   137,   137,   134,   134,   135,
     135
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
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       4,     2,     1,     1,     1,     2,     2,     2,     2,     2,
       2,     2,     4,     4,     3,     4,     4,     2,     3,     3,
       4,     3,     3,     4,     2,     2,     3,     3,     5,     2,
       3,     3,     4,     2,     1,     2,     3,     4,     1,     1,
       1,     1,     1,     4,     4,     4,     4,     2,     3,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     2,     2,     2,
       4,     3,     5,     3,     3,     3,     4,     4,     4,     4,
       4,     2,     2,     1,     5,     6,     3,     3,     3,     1,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "NAME", "TYPENAME",
  "INT", "FLOAT", "STRING", "IF", "ELSE", "WHEN", "FOR", "WHILE", "TYPE",
  "FN", "BUFFER", "RETURN", "TRUE", "FALSE", "CONST", "AUTO", "ASSGN",
  "SEMI", "COMMA", "IN", "OUT", "TO", "BY", "ELIP", "OPAREN", "CPAREN",
  "OBRACE", "CBRACE", "OBRACK", "CBRACK", "VOID", "ADD", "SUB", "MUL",
  "DIV", "MOD", "POW", "NOT", "AND", "OR", "EQ", "NE", "GE", "LE", "GT",
  "LT", "ILLEGAL", "$accept", "start", "cat_type", "cat_declaration",
  "cat_range_decl", "cat_array_elem", "cat_expression", "cat_statement",
  "pure", "expr_or", "expr_and", "expr_eq", "expr_ord", "expr_add",
  "expr_mul", "expr_pow", "expr_pre", "expr_post", "expr_atom",
  "expr_right", "expr_assgn_target", "paren_type", "void_type",
  "node_auto", "node_type_name", "node_const_type", "node_in_type",
  "node_out_type", "node_function_type", "node_array_type",
  "node_buffer_type", "node_type_decl", "paren_decl", "paren_range_decl",
  "void_decl", "node_declaration", "node_range_decl", "node_range_to",
  "node_range_to_by", "node_spread", "paren_expr", "void", "node_name",
  "node_block", "node_bool", "node_int", "node_float", "node_string",
  "node_function", "node_array", "node_or", "node_and", "node_eq",
  "node_ne", "node_ge", "node_le", "node_gt", "node_lt", "node_add",
  "node_sub", "node_mul", "node_div", "node_mod", "node_pow", "node_plus",
  "node_minus", "node_not", "node_application", "node_conversion",
  "node_subscript", "node_expr_if", "node_expr_for", "node_definition",
  "node_assignment", "node_function_def", "node_type_def", "node_return",
  "node_if", "node_when", "node_for", "node_while", "type_list",
  "decl_list", "range_decl_list", "array_elem_list", "expr_list",
  "stmt_list", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   202,   202,   205,   208,   215,   216,   219,   220,   223,
     224,   225,   226,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   241,   242,   245,   246,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   263,   264,   267,
     268,   271,   272,   273,   276,   277,   278,   279,   280,   283,
     284,   285,   288,   289,   290,   291,   294,   295,   298,   299,
     300,   301,   304,   305,   306,   307,   310,   311,   312,   313,
     314,   315,   316,   317,   320,   321,   322,   325,   330,   333,
     336,   341,   344,   349,   354,   359,   364,   369,   374,   377,
     380,   383,   388,   391,   394,   397,   402,   407,   414,   417,
     420,   425,   428,   431,   436,   441,   446,   453,   458,   463,
     470,   473,   476,   481,   486,   491,   494,   497,   504,   507,
     512,   517,   522,   527,   530,   533,   536,   541,   544,   547,
     554,   559,   564,   569,   574,   579,   584,   589,   594,   599,
     604,   609,   614,   619,   624,   629,   634,   639,   642,   647,
     652,   655,   660,   665,   672,   677,   682,   687,   690,   693,
     696,   701,   704,   707,   712,   715,   720,   725,   730,   737,
     740,   745,   748,   753,   756,   761,   764,   769,   772,   777,
     780
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
#line 3957 "src/parser.cpp"

#line 784 "gen/parser.y"


void yy::parser::error (std::string const & msg) {
    // TODO: There's a syntax error every time for some reason.
    //std::cerr << "parser error: " << msg << '\n';
}
