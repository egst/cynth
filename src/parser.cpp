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
  parser::parser (cynth::syn::node::Block & result_yyarg)
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
        value.YY_MOVE_OR_COPY< cynth::syn::category::ArrayElement > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_declaration: // cat_declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.YY_MOVE_OR_COPY< cynth::syn::category::Declaration > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< cynth::syn::category::Expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_range_decl: // cat_range_decl
      case symbol_kind::S_paren_range_decl: // paren_range_decl
        value.YY_MOVE_OR_COPY< cynth::syn::category::RangeDeclaration > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_statement: // cat_statement
      case symbol_kind::S_pure: // pure
        value.YY_MOVE_OR_COPY< cynth::syn::category::Statement > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_type: // cat_type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.YY_MOVE_OR_COPY< cynth::syn::category::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_add: // node_add
        value.YY_MOVE_OR_COPY< cynth::syn::node::Add > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_and: // node_and
        value.YY_MOVE_OR_COPY< cynth::syn::node::And > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_application: // node_application
        value.YY_MOVE_OR_COPY< cynth::syn::node::Application > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_array: // node_array
        value.YY_MOVE_OR_COPY< cynth::syn::node::Array > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_array_type: // node_array_type
        value.YY_MOVE_OR_COPY< cynth::syn::node::ArrayType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_assignment: // node_assignment
        value.YY_MOVE_OR_COPY< cynth::syn::node::Assignment > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_auto: // node_auto
        value.YY_MOVE_OR_COPY< cynth::syn::node::Auto > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_block: // node_block
        value.YY_MOVE_OR_COPY< cynth::syn::node::Block > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_bool: // node_bool
        value.YY_MOVE_OR_COPY< cynth::syn::node::Bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_buffer_type: // node_buffer_type
        value.YY_MOVE_OR_COPY< cynth::syn::node::BufferType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_const_type: // node_const_type
        value.YY_MOVE_OR_COPY< cynth::syn::node::ConstType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_conversion: // node_conversion
        value.YY_MOVE_OR_COPY< cynth::syn::node::Conversion > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_declaration: // node_declaration
        value.YY_MOVE_OR_COPY< cynth::syn::node::Declaration > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_definition: // node_definition
        value.YY_MOVE_OR_COPY< cynth::syn::node::Definition > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_div: // node_div
        value.YY_MOVE_OR_COPY< cynth::syn::node::Div > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_eq: // node_eq
        value.YY_MOVE_OR_COPY< cynth::syn::node::Eq > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_expr_for: // node_expr_for
        value.YY_MOVE_OR_COPY< cynth::syn::node::ExprFor > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.YY_MOVE_OR_COPY< cynth::syn::node::ExprIf > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_float: // node_float
        value.YY_MOVE_OR_COPY< cynth::syn::node::Float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_for: // node_for
        value.YY_MOVE_OR_COPY< cynth::syn::node::For > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.YY_MOVE_OR_COPY< cynth::syn::node::FunDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function: // node_function
        value.YY_MOVE_OR_COPY< cynth::syn::node::Function > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function_type: // node_function_type
        value.YY_MOVE_OR_COPY< cynth::syn::node::FunctionType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_ge: // node_ge
        value.YY_MOVE_OR_COPY< cynth::syn::node::Ge > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_gt: // node_gt
        value.YY_MOVE_OR_COPY< cynth::syn::node::Gt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_if: // node_if
        value.YY_MOVE_OR_COPY< cynth::syn::node::If > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_in_type: // node_in_type
        value.YY_MOVE_OR_COPY< cynth::syn::node::InType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_int: // node_int
        value.YY_MOVE_OR_COPY< cynth::syn::node::Int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_le: // node_le
        value.YY_MOVE_OR_COPY< cynth::syn::node::Le > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_lt: // node_lt
        value.YY_MOVE_OR_COPY< cynth::syn::node::Lt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_minus: // node_minus
        value.YY_MOVE_OR_COPY< cynth::syn::node::Minus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_mod: // node_mod
        value.YY_MOVE_OR_COPY< cynth::syn::node::Mod > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_mul: // node_mul
        value.YY_MOVE_OR_COPY< cynth::syn::node::Mul > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_name: // node_name
        value.YY_MOVE_OR_COPY< cynth::syn::node::Name > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_ne: // node_ne
        value.YY_MOVE_OR_COPY< cynth::syn::node::Ne > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_not: // node_not
        value.YY_MOVE_OR_COPY< cynth::syn::node::Not > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_or: // node_or
        value.YY_MOVE_OR_COPY< cynth::syn::node::Or > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_out_type: // node_out_type
        value.YY_MOVE_OR_COPY< cynth::syn::node::OutType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_plus: // node_plus
        value.YY_MOVE_OR_COPY< cynth::syn::node::Plus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_pow: // node_pow
        value.YY_MOVE_OR_COPY< cynth::syn::node::Pow > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_range_decl: // node_range_decl
        value.YY_MOVE_OR_COPY< cynth::syn::node::RangeDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_range_to: // node_range_to
        value.YY_MOVE_OR_COPY< cynth::syn::node::RangeTo > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_range_to_by: // node_range_to_by
        value.YY_MOVE_OR_COPY< cynth::syn::node::RangeToBy > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_return: // node_return
        value.YY_MOVE_OR_COPY< cynth::syn::node::Return > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_spread: // node_spread
        value.YY_MOVE_OR_COPY< cynth::syn::node::Spread > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_string: // node_string
        value.YY_MOVE_OR_COPY< cynth::syn::node::String > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_sub: // node_sub
        value.YY_MOVE_OR_COPY< cynth::syn::node::Sub > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_subscript: // node_subscript
        value.YY_MOVE_OR_COPY< cynth::syn::node::Subscript > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_type_def: // node_type_def
        value.YY_MOVE_OR_COPY< cynth::syn::node::TypeDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_type_name: // node_type_name
        value.YY_MOVE_OR_COPY< cynth::syn::node::TypeName > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_when: // node_when
        value.YY_MOVE_OR_COPY< cynth::syn::node::When > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_while: // node_while
        value.YY_MOVE_OR_COPY< cynth::syn::node::While > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.YY_MOVE_OR_COPY< esl::component_vector<cynth::syn::category::ArrayElement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.YY_MOVE_OR_COPY< esl::component_vector<cynth::syn::category::Declaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.YY_MOVE_OR_COPY< esl::component_vector<cynth::syn::category::Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_range_decl_list: // range_decl_list
        value.YY_MOVE_OR_COPY< esl::component_vector<cynth::syn::category::RangeDeclaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.YY_MOVE_OR_COPY< esl::component_vector<cynth::syn::category::Statement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_list: // type_list
        value.YY_MOVE_OR_COPY< esl::component_vector<cynth::syn::category::Type> > (YY_MOVE (that.value));
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
        value.move< cynth::syn::category::ArrayElement > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_declaration: // cat_declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.move< cynth::syn::category::Declaration > (YY_MOVE (that.value));
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
        value.move< cynth::syn::category::Expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_range_decl: // cat_range_decl
      case symbol_kind::S_paren_range_decl: // paren_range_decl
        value.move< cynth::syn::category::RangeDeclaration > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_statement: // cat_statement
      case symbol_kind::S_pure: // pure
        value.move< cynth::syn::category::Statement > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_type: // cat_type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.move< cynth::syn::category::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_add: // node_add
        value.move< cynth::syn::node::Add > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_and: // node_and
        value.move< cynth::syn::node::And > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_application: // node_application
        value.move< cynth::syn::node::Application > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_array: // node_array
        value.move< cynth::syn::node::Array > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_array_type: // node_array_type
        value.move< cynth::syn::node::ArrayType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_assignment: // node_assignment
        value.move< cynth::syn::node::Assignment > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_auto: // node_auto
        value.move< cynth::syn::node::Auto > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_block: // node_block
        value.move< cynth::syn::node::Block > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_bool: // node_bool
        value.move< cynth::syn::node::Bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_buffer_type: // node_buffer_type
        value.move< cynth::syn::node::BufferType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_const_type: // node_const_type
        value.move< cynth::syn::node::ConstType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_conversion: // node_conversion
        value.move< cynth::syn::node::Conversion > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_declaration: // node_declaration
        value.move< cynth::syn::node::Declaration > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_definition: // node_definition
        value.move< cynth::syn::node::Definition > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_div: // node_div
        value.move< cynth::syn::node::Div > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_eq: // node_eq
        value.move< cynth::syn::node::Eq > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_expr_for: // node_expr_for
        value.move< cynth::syn::node::ExprFor > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.move< cynth::syn::node::ExprIf > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_float: // node_float
        value.move< cynth::syn::node::Float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_for: // node_for
        value.move< cynth::syn::node::For > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.move< cynth::syn::node::FunDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function: // node_function
        value.move< cynth::syn::node::Function > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function_type: // node_function_type
        value.move< cynth::syn::node::FunctionType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_ge: // node_ge
        value.move< cynth::syn::node::Ge > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_gt: // node_gt
        value.move< cynth::syn::node::Gt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_if: // node_if
        value.move< cynth::syn::node::If > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_in_type: // node_in_type
        value.move< cynth::syn::node::InType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_int: // node_int
        value.move< cynth::syn::node::Int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_le: // node_le
        value.move< cynth::syn::node::Le > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_lt: // node_lt
        value.move< cynth::syn::node::Lt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_minus: // node_minus
        value.move< cynth::syn::node::Minus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_mod: // node_mod
        value.move< cynth::syn::node::Mod > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_mul: // node_mul
        value.move< cynth::syn::node::Mul > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_name: // node_name
        value.move< cynth::syn::node::Name > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_ne: // node_ne
        value.move< cynth::syn::node::Ne > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_not: // node_not
        value.move< cynth::syn::node::Not > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_or: // node_or
        value.move< cynth::syn::node::Or > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_out_type: // node_out_type
        value.move< cynth::syn::node::OutType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_plus: // node_plus
        value.move< cynth::syn::node::Plus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_pow: // node_pow
        value.move< cynth::syn::node::Pow > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_range_decl: // node_range_decl
        value.move< cynth::syn::node::RangeDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_range_to: // node_range_to
        value.move< cynth::syn::node::RangeTo > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_range_to_by: // node_range_to_by
        value.move< cynth::syn::node::RangeToBy > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_return: // node_return
        value.move< cynth::syn::node::Return > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_spread: // node_spread
        value.move< cynth::syn::node::Spread > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_string: // node_string
        value.move< cynth::syn::node::String > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_sub: // node_sub
        value.move< cynth::syn::node::Sub > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_subscript: // node_subscript
        value.move< cynth::syn::node::Subscript > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_type_def: // node_type_def
        value.move< cynth::syn::node::TypeDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_type_name: // node_type_name
        value.move< cynth::syn::node::TypeName > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_when: // node_when
        value.move< cynth::syn::node::When > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_while: // node_while
        value.move< cynth::syn::node::While > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.move< esl::component_vector<cynth::syn::category::ArrayElement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< esl::component_vector<cynth::syn::category::Declaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< esl::component_vector<cynth::syn::category::Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_range_decl_list: // range_decl_list
        value.move< esl::component_vector<cynth::syn::category::RangeDeclaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< esl::component_vector<cynth::syn::category::Statement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_list: // type_list
        value.move< esl::component_vector<cynth::syn::category::Type> > (YY_MOVE (that.value));
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
        value.copy< cynth::syn::category::ArrayElement > (that.value);
        break;

      case symbol_kind::S_cat_declaration: // cat_declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.copy< cynth::syn::category::Declaration > (that.value);
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
        value.copy< cynth::syn::category::Expression > (that.value);
        break;

      case symbol_kind::S_cat_range_decl: // cat_range_decl
      case symbol_kind::S_paren_range_decl: // paren_range_decl
        value.copy< cynth::syn::category::RangeDeclaration > (that.value);
        break;

      case symbol_kind::S_cat_statement: // cat_statement
      case symbol_kind::S_pure: // pure
        value.copy< cynth::syn::category::Statement > (that.value);
        break;

      case symbol_kind::S_cat_type: // cat_type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.copy< cynth::syn::category::Type > (that.value);
        break;

      case symbol_kind::S_node_add: // node_add
        value.copy< cynth::syn::node::Add > (that.value);
        break;

      case symbol_kind::S_node_and: // node_and
        value.copy< cynth::syn::node::And > (that.value);
        break;

      case symbol_kind::S_node_application: // node_application
        value.copy< cynth::syn::node::Application > (that.value);
        break;

      case symbol_kind::S_node_array: // node_array
        value.copy< cynth::syn::node::Array > (that.value);
        break;

      case symbol_kind::S_node_array_type: // node_array_type
        value.copy< cynth::syn::node::ArrayType > (that.value);
        break;

      case symbol_kind::S_node_assignment: // node_assignment
        value.copy< cynth::syn::node::Assignment > (that.value);
        break;

      case symbol_kind::S_node_auto: // node_auto
        value.copy< cynth::syn::node::Auto > (that.value);
        break;

      case symbol_kind::S_node_block: // node_block
        value.copy< cynth::syn::node::Block > (that.value);
        break;

      case symbol_kind::S_node_bool: // node_bool
        value.copy< cynth::syn::node::Bool > (that.value);
        break;

      case symbol_kind::S_node_buffer_type: // node_buffer_type
        value.copy< cynth::syn::node::BufferType > (that.value);
        break;

      case symbol_kind::S_node_const_type: // node_const_type
        value.copy< cynth::syn::node::ConstType > (that.value);
        break;

      case symbol_kind::S_node_conversion: // node_conversion
        value.copy< cynth::syn::node::Conversion > (that.value);
        break;

      case symbol_kind::S_node_declaration: // node_declaration
        value.copy< cynth::syn::node::Declaration > (that.value);
        break;

      case symbol_kind::S_node_definition: // node_definition
        value.copy< cynth::syn::node::Definition > (that.value);
        break;

      case symbol_kind::S_node_div: // node_div
        value.copy< cynth::syn::node::Div > (that.value);
        break;

      case symbol_kind::S_node_eq: // node_eq
        value.copy< cynth::syn::node::Eq > (that.value);
        break;

      case symbol_kind::S_node_expr_for: // node_expr_for
        value.copy< cynth::syn::node::ExprFor > (that.value);
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.copy< cynth::syn::node::ExprIf > (that.value);
        break;

      case symbol_kind::S_node_float: // node_float
        value.copy< cynth::syn::node::Float > (that.value);
        break;

      case symbol_kind::S_node_for: // node_for
        value.copy< cynth::syn::node::For > (that.value);
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.copy< cynth::syn::node::FunDef > (that.value);
        break;

      case symbol_kind::S_node_function: // node_function
        value.copy< cynth::syn::node::Function > (that.value);
        break;

      case symbol_kind::S_node_function_type: // node_function_type
        value.copy< cynth::syn::node::FunctionType > (that.value);
        break;

      case symbol_kind::S_node_ge: // node_ge
        value.copy< cynth::syn::node::Ge > (that.value);
        break;

      case symbol_kind::S_node_gt: // node_gt
        value.copy< cynth::syn::node::Gt > (that.value);
        break;

      case symbol_kind::S_node_if: // node_if
        value.copy< cynth::syn::node::If > (that.value);
        break;

      case symbol_kind::S_node_in_type: // node_in_type
        value.copy< cynth::syn::node::InType > (that.value);
        break;

      case symbol_kind::S_node_int: // node_int
        value.copy< cynth::syn::node::Int > (that.value);
        break;

      case symbol_kind::S_node_le: // node_le
        value.copy< cynth::syn::node::Le > (that.value);
        break;

      case symbol_kind::S_node_lt: // node_lt
        value.copy< cynth::syn::node::Lt > (that.value);
        break;

      case symbol_kind::S_node_minus: // node_minus
        value.copy< cynth::syn::node::Minus > (that.value);
        break;

      case symbol_kind::S_node_mod: // node_mod
        value.copy< cynth::syn::node::Mod > (that.value);
        break;

      case symbol_kind::S_node_mul: // node_mul
        value.copy< cynth::syn::node::Mul > (that.value);
        break;

      case symbol_kind::S_node_name: // node_name
        value.copy< cynth::syn::node::Name > (that.value);
        break;

      case symbol_kind::S_node_ne: // node_ne
        value.copy< cynth::syn::node::Ne > (that.value);
        break;

      case symbol_kind::S_node_not: // node_not
        value.copy< cynth::syn::node::Not > (that.value);
        break;

      case symbol_kind::S_node_or: // node_or
        value.copy< cynth::syn::node::Or > (that.value);
        break;

      case symbol_kind::S_node_out_type: // node_out_type
        value.copy< cynth::syn::node::OutType > (that.value);
        break;

      case symbol_kind::S_node_plus: // node_plus
        value.copy< cynth::syn::node::Plus > (that.value);
        break;

      case symbol_kind::S_node_pow: // node_pow
        value.copy< cynth::syn::node::Pow > (that.value);
        break;

      case symbol_kind::S_node_range_decl: // node_range_decl
        value.copy< cynth::syn::node::RangeDecl > (that.value);
        break;

      case symbol_kind::S_node_range_to: // node_range_to
        value.copy< cynth::syn::node::RangeTo > (that.value);
        break;

      case symbol_kind::S_node_range_to_by: // node_range_to_by
        value.copy< cynth::syn::node::RangeToBy > (that.value);
        break;

      case symbol_kind::S_node_return: // node_return
        value.copy< cynth::syn::node::Return > (that.value);
        break;

      case symbol_kind::S_node_spread: // node_spread
        value.copy< cynth::syn::node::Spread > (that.value);
        break;

      case symbol_kind::S_node_string: // node_string
        value.copy< cynth::syn::node::String > (that.value);
        break;

      case symbol_kind::S_node_sub: // node_sub
        value.copy< cynth::syn::node::Sub > (that.value);
        break;

      case symbol_kind::S_node_subscript: // node_subscript
        value.copy< cynth::syn::node::Subscript > (that.value);
        break;

      case symbol_kind::S_node_type_def: // node_type_def
        value.copy< cynth::syn::node::TypeDef > (that.value);
        break;

      case symbol_kind::S_node_type_name: // node_type_name
        value.copy< cynth::syn::node::TypeName > (that.value);
        break;

      case symbol_kind::S_node_when: // node_when
        value.copy< cynth::syn::node::When > (that.value);
        break;

      case symbol_kind::S_node_while: // node_while
        value.copy< cynth::syn::node::While > (that.value);
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.copy< esl::component_vector<cynth::syn::category::ArrayElement> > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.copy< esl::component_vector<cynth::syn::category::Declaration> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.copy< esl::component_vector<cynth::syn::category::Expression> > (that.value);
        break;

      case symbol_kind::S_range_decl_list: // range_decl_list
        value.copy< esl::component_vector<cynth::syn::category::RangeDeclaration> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< esl::component_vector<cynth::syn::category::Statement> > (that.value);
        break;

      case symbol_kind::S_type_list: // type_list
        value.copy< esl::component_vector<cynth::syn::category::Type> > (that.value);
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
        value.move< cynth::syn::category::ArrayElement > (that.value);
        break;

      case symbol_kind::S_cat_declaration: // cat_declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.move< cynth::syn::category::Declaration > (that.value);
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
        value.move< cynth::syn::category::Expression > (that.value);
        break;

      case symbol_kind::S_cat_range_decl: // cat_range_decl
      case symbol_kind::S_paren_range_decl: // paren_range_decl
        value.move< cynth::syn::category::RangeDeclaration > (that.value);
        break;

      case symbol_kind::S_cat_statement: // cat_statement
      case symbol_kind::S_pure: // pure
        value.move< cynth::syn::category::Statement > (that.value);
        break;

      case symbol_kind::S_cat_type: // cat_type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.move< cynth::syn::category::Type > (that.value);
        break;

      case symbol_kind::S_node_add: // node_add
        value.move< cynth::syn::node::Add > (that.value);
        break;

      case symbol_kind::S_node_and: // node_and
        value.move< cynth::syn::node::And > (that.value);
        break;

      case symbol_kind::S_node_application: // node_application
        value.move< cynth::syn::node::Application > (that.value);
        break;

      case symbol_kind::S_node_array: // node_array
        value.move< cynth::syn::node::Array > (that.value);
        break;

      case symbol_kind::S_node_array_type: // node_array_type
        value.move< cynth::syn::node::ArrayType > (that.value);
        break;

      case symbol_kind::S_node_assignment: // node_assignment
        value.move< cynth::syn::node::Assignment > (that.value);
        break;

      case symbol_kind::S_node_auto: // node_auto
        value.move< cynth::syn::node::Auto > (that.value);
        break;

      case symbol_kind::S_node_block: // node_block
        value.move< cynth::syn::node::Block > (that.value);
        break;

      case symbol_kind::S_node_bool: // node_bool
        value.move< cynth::syn::node::Bool > (that.value);
        break;

      case symbol_kind::S_node_buffer_type: // node_buffer_type
        value.move< cynth::syn::node::BufferType > (that.value);
        break;

      case symbol_kind::S_node_const_type: // node_const_type
        value.move< cynth::syn::node::ConstType > (that.value);
        break;

      case symbol_kind::S_node_conversion: // node_conversion
        value.move< cynth::syn::node::Conversion > (that.value);
        break;

      case symbol_kind::S_node_declaration: // node_declaration
        value.move< cynth::syn::node::Declaration > (that.value);
        break;

      case symbol_kind::S_node_definition: // node_definition
        value.move< cynth::syn::node::Definition > (that.value);
        break;

      case symbol_kind::S_node_div: // node_div
        value.move< cynth::syn::node::Div > (that.value);
        break;

      case symbol_kind::S_node_eq: // node_eq
        value.move< cynth::syn::node::Eq > (that.value);
        break;

      case symbol_kind::S_node_expr_for: // node_expr_for
        value.move< cynth::syn::node::ExprFor > (that.value);
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.move< cynth::syn::node::ExprIf > (that.value);
        break;

      case symbol_kind::S_node_float: // node_float
        value.move< cynth::syn::node::Float > (that.value);
        break;

      case symbol_kind::S_node_for: // node_for
        value.move< cynth::syn::node::For > (that.value);
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.move< cynth::syn::node::FunDef > (that.value);
        break;

      case symbol_kind::S_node_function: // node_function
        value.move< cynth::syn::node::Function > (that.value);
        break;

      case symbol_kind::S_node_function_type: // node_function_type
        value.move< cynth::syn::node::FunctionType > (that.value);
        break;

      case symbol_kind::S_node_ge: // node_ge
        value.move< cynth::syn::node::Ge > (that.value);
        break;

      case symbol_kind::S_node_gt: // node_gt
        value.move< cynth::syn::node::Gt > (that.value);
        break;

      case symbol_kind::S_node_if: // node_if
        value.move< cynth::syn::node::If > (that.value);
        break;

      case symbol_kind::S_node_in_type: // node_in_type
        value.move< cynth::syn::node::InType > (that.value);
        break;

      case symbol_kind::S_node_int: // node_int
        value.move< cynth::syn::node::Int > (that.value);
        break;

      case symbol_kind::S_node_le: // node_le
        value.move< cynth::syn::node::Le > (that.value);
        break;

      case symbol_kind::S_node_lt: // node_lt
        value.move< cynth::syn::node::Lt > (that.value);
        break;

      case symbol_kind::S_node_minus: // node_minus
        value.move< cynth::syn::node::Minus > (that.value);
        break;

      case symbol_kind::S_node_mod: // node_mod
        value.move< cynth::syn::node::Mod > (that.value);
        break;

      case symbol_kind::S_node_mul: // node_mul
        value.move< cynth::syn::node::Mul > (that.value);
        break;

      case symbol_kind::S_node_name: // node_name
        value.move< cynth::syn::node::Name > (that.value);
        break;

      case symbol_kind::S_node_ne: // node_ne
        value.move< cynth::syn::node::Ne > (that.value);
        break;

      case symbol_kind::S_node_not: // node_not
        value.move< cynth::syn::node::Not > (that.value);
        break;

      case symbol_kind::S_node_or: // node_or
        value.move< cynth::syn::node::Or > (that.value);
        break;

      case symbol_kind::S_node_out_type: // node_out_type
        value.move< cynth::syn::node::OutType > (that.value);
        break;

      case symbol_kind::S_node_plus: // node_plus
        value.move< cynth::syn::node::Plus > (that.value);
        break;

      case symbol_kind::S_node_pow: // node_pow
        value.move< cynth::syn::node::Pow > (that.value);
        break;

      case symbol_kind::S_node_range_decl: // node_range_decl
        value.move< cynth::syn::node::RangeDecl > (that.value);
        break;

      case symbol_kind::S_node_range_to: // node_range_to
        value.move< cynth::syn::node::RangeTo > (that.value);
        break;

      case symbol_kind::S_node_range_to_by: // node_range_to_by
        value.move< cynth::syn::node::RangeToBy > (that.value);
        break;

      case symbol_kind::S_node_return: // node_return
        value.move< cynth::syn::node::Return > (that.value);
        break;

      case symbol_kind::S_node_spread: // node_spread
        value.move< cynth::syn::node::Spread > (that.value);
        break;

      case symbol_kind::S_node_string: // node_string
        value.move< cynth::syn::node::String > (that.value);
        break;

      case symbol_kind::S_node_sub: // node_sub
        value.move< cynth::syn::node::Sub > (that.value);
        break;

      case symbol_kind::S_node_subscript: // node_subscript
        value.move< cynth::syn::node::Subscript > (that.value);
        break;

      case symbol_kind::S_node_type_def: // node_type_def
        value.move< cynth::syn::node::TypeDef > (that.value);
        break;

      case symbol_kind::S_node_type_name: // node_type_name
        value.move< cynth::syn::node::TypeName > (that.value);
        break;

      case symbol_kind::S_node_when: // node_when
        value.move< cynth::syn::node::When > (that.value);
        break;

      case symbol_kind::S_node_while: // node_while
        value.move< cynth::syn::node::While > (that.value);
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.move< esl::component_vector<cynth::syn::category::ArrayElement> > (that.value);
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< esl::component_vector<cynth::syn::category::Declaration> > (that.value);
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< esl::component_vector<cynth::syn::category::Expression> > (that.value);
        break;

      case symbol_kind::S_range_decl_list: // range_decl_list
        value.move< esl::component_vector<cynth::syn::category::RangeDeclaration> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< esl::component_vector<cynth::syn::category::Statement> > (that.value);
        break;

      case symbol_kind::S_type_list: // type_list
        value.move< esl::component_vector<cynth::syn::category::Type> > (that.value);
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
        yylhs.value.emplace< esl::component_vector<cynth::syn::category::ArrayElement> > ();
        break;

      case symbol_kind::S_decl_list: // decl_list
        yylhs.value.emplace< esl::component_vector<cynth::syn::category::Declaration> > ();
        break;

      case symbol_kind::S_expr_list: // expr_list
        yylhs.value.emplace< esl::component_vector<cynth::syn::category::Expression> > ();
        break;

      case symbol_kind::S_range_decl_list: // range_decl_list
        yylhs.value.emplace< esl::component_vector<cynth::syn::category::RangeDeclaration> > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        yylhs.value.emplace< esl::component_vector<cynth::syn::category::Statement> > ();
        break;

      case symbol_kind::S_type_list: // type_list
        yylhs.value.emplace< esl::component_vector<cynth::syn::category::Type> > ();
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
#line 206 "gen/parser.y"
           {
        result = {};
    }
#line 1941 "src/parser.cpp"
    break;

  case 3: // start: stmt_list
#line 209 "gen/parser.y"
                    {
        result = {YY_MOVE (yystack_[0].value.as < esl::component_vector<cynth::syn::category::Statement> > ())};
    }
#line 1949 "src/parser.cpp"
    break;

  case 4: // start: stmt_list SEMI
#line 212 "gen/parser.y"
                         {
        result = {YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::Statement> > ())};
    }
#line 1957 "src/parser.cpp"
    break;

  case 5: // cat_declaration: node_declaration
#line 219 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Declaration > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Declaration > ()); }
#line 1963 "src/parser.cpp"
    break;

  case 6: // cat_declaration: paren_decl
#line 220 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Declaration > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Declaration > ()); }
#line 1969 "src/parser.cpp"
    break;

  case 7: // cat_range_decl: node_range_decl
#line 223 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::RangeDeclaration > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::RangeDecl > ()); }
#line 1975 "src/parser.cpp"
    break;

  case 8: // cat_range_decl: paren_range_decl
#line 224 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::RangeDeclaration > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::RangeDeclaration > ()); }
#line 1981 "src/parser.cpp"
    break;

  case 9: // cat_array_elem: node_range_to
#line 227 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::RangeTo > ()); }
#line 1987 "src/parser.cpp"
    break;

  case 10: // cat_array_elem: node_range_to_by
#line 228 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::RangeToBy > ()); }
#line 1993 "src/parser.cpp"
    break;

  case 11: // cat_array_elem: node_spread
#line 229 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Spread > ()); }
#line 1999 "src/parser.cpp"
    break;

  case 12: // cat_array_elem: cat_expression
#line 230 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2005 "src/parser.cpp"
    break;

  case 13: // cat_type: node_auto
#line 233 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Auto > ()); }
#line 2011 "src/parser.cpp"
    break;

  case 14: // cat_type: node_type_name
#line 234 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::TypeName > ()); }
#line 2017 "src/parser.cpp"
    break;

  case 15: // cat_type: node_function_type
#line 235 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::FunctionType > ()); }
#line 2023 "src/parser.cpp"
    break;

  case 16: // cat_type: node_array_type
#line 236 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::ArrayType > ()); }
#line 2029 "src/parser.cpp"
    break;

  case 17: // cat_type: node_buffer_type
#line 237 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::BufferType > ()); }
#line 2035 "src/parser.cpp"
    break;

  case 18: // cat_type: node_const_type
#line 241 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::ConstType > ()); }
#line 2041 "src/parser.cpp"
    break;

  case 19: // cat_type: node_in_type
#line 242 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::InType > ()); }
#line 2047 "src/parser.cpp"
    break;

  case 20: // cat_type: node_out_type
#line 243 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::OutType > ()); }
#line 2053 "src/parser.cpp"
    break;

  case 21: // cat_type: paren_type
#line 244 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ()); }
#line 2059 "src/parser.cpp"
    break;

  case 22: // cat_expression: expr_or
#line 247 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2065 "src/parser.cpp"
    break;

  case 23: // cat_expression: expr_right
#line 248 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2071 "src/parser.cpp"
    break;

  case 24: // cat_statement: pure
#line 251 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ()); }
#line 2077 "src/parser.cpp"
    break;

  case 25: // cat_statement: cat_expression
#line 252 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2083 "src/parser.cpp"
    break;

  case 26: // pure: node_declaration
#line 257 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Declaration > ()); }
#line 2089 "src/parser.cpp"
    break;

  case 27: // pure: node_definition
#line 258 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Definition > ()); }
#line 2095 "src/parser.cpp"
    break;

  case 28: // pure: node_assignment
#line 259 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Assignment > ()); }
#line 2101 "src/parser.cpp"
    break;

  case 29: // pure: node_type_def
#line 260 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::TypeDef > ()); }
#line 2107 "src/parser.cpp"
    break;

  case 30: // pure: node_function_def
#line 261 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::FunDef > ()); }
#line 2113 "src/parser.cpp"
    break;

  case 31: // pure: node_return
#line 262 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Return > ()); }
#line 2119 "src/parser.cpp"
    break;

  case 32: // pure: node_if
#line 263 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::If > ()); }
#line 2125 "src/parser.cpp"
    break;

  case 33: // pure: node_for
#line 264 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::For > ()); }
#line 2131 "src/parser.cpp"
    break;

  case 34: // pure: node_while
#line 265 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::While > ()); }
#line 2137 "src/parser.cpp"
    break;

  case 35: // pure: node_when
#line 266 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::When > ()); }
#line 2143 "src/parser.cpp"
    break;

  case 36: // expr_or: node_or
#line 269 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Or > ()); }
#line 2149 "src/parser.cpp"
    break;

  case 37: // expr_or: expr_and
#line 270 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2155 "src/parser.cpp"
    break;

  case 38: // expr_and: node_and
#line 273 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::And > ()); }
#line 2161 "src/parser.cpp"
    break;

  case 39: // expr_and: expr_eq
#line 274 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2167 "src/parser.cpp"
    break;

  case 40: // expr_eq: node_eq
#line 277 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Eq > ()); }
#line 2173 "src/parser.cpp"
    break;

  case 41: // expr_eq: node_ne
#line 278 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Ne > ()); }
#line 2179 "src/parser.cpp"
    break;

  case 42: // expr_eq: expr_ord
#line 279 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2185 "src/parser.cpp"
    break;

  case 43: // expr_ord: node_ge
#line 282 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Ge > ()); }
#line 2191 "src/parser.cpp"
    break;

  case 44: // expr_ord: node_le
#line 283 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Le > ()); }
#line 2197 "src/parser.cpp"
    break;

  case 45: // expr_ord: node_gt
#line 284 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Gt > ()); }
#line 2203 "src/parser.cpp"
    break;

  case 46: // expr_ord: node_lt
#line 285 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Lt > ()); }
#line 2209 "src/parser.cpp"
    break;

  case 47: // expr_ord: expr_add
#line 286 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2215 "src/parser.cpp"
    break;

  case 48: // expr_add: node_add
#line 289 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Add > ()); }
#line 2221 "src/parser.cpp"
    break;

  case 49: // expr_add: node_sub
#line 290 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Sub > ()); }
#line 2227 "src/parser.cpp"
    break;

  case 50: // expr_add: expr_mul
#line 291 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2233 "src/parser.cpp"
    break;

  case 51: // expr_mul: node_mul
#line 294 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Mul > ()); }
#line 2239 "src/parser.cpp"
    break;

  case 52: // expr_mul: node_div
#line 295 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Div > ()); }
#line 2245 "src/parser.cpp"
    break;

  case 53: // expr_mul: node_mod
#line 296 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Mod > ()); }
#line 2251 "src/parser.cpp"
    break;

  case 54: // expr_mul: expr_pow
#line 297 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2257 "src/parser.cpp"
    break;

  case 55: // expr_pow: node_pow
#line 300 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Pow > ()); }
#line 2263 "src/parser.cpp"
    break;

  case 56: // expr_pow: expr_pre
#line 301 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2269 "src/parser.cpp"
    break;

  case 57: // expr_pre: node_minus
#line 304 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Minus > ()); }
#line 2275 "src/parser.cpp"
    break;

  case 58: // expr_pre: node_plus
#line 305 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Plus > ()); }
#line 2281 "src/parser.cpp"
    break;

  case 59: // expr_pre: node_not
#line 306 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Not > ()); }
#line 2287 "src/parser.cpp"
    break;

  case 60: // expr_pre: expr_post
#line 307 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2293 "src/parser.cpp"
    break;

  case 61: // expr_post: node_application
#line 310 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Application > ()); }
#line 2299 "src/parser.cpp"
    break;

  case 62: // expr_post: node_conversion
#line 311 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Conversion > ()); }
#line 2305 "src/parser.cpp"
    break;

  case 63: // expr_post: node_subscript
#line 312 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Subscript > ()); }
#line 2311 "src/parser.cpp"
    break;

  case 64: // expr_post: expr_atom
#line 313 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2317 "src/parser.cpp"
    break;

  case 65: // expr_atom: node_name
#line 316 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Name > ()); }
#line 2323 "src/parser.cpp"
    break;

  case 66: // expr_atom: node_bool
#line 317 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Bool > ()); }
#line 2329 "src/parser.cpp"
    break;

  case 67: // expr_atom: node_int
#line 318 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Int > ()); }
#line 2335 "src/parser.cpp"
    break;

  case 68: // expr_atom: node_float
#line 319 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Float > ()); }
#line 2341 "src/parser.cpp"
    break;

  case 69: // expr_atom: node_string
#line 320 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::String > ()); }
#line 2347 "src/parser.cpp"
    break;

  case 70: // expr_atom: node_block
#line 321 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Block > ()); }
#line 2353 "src/parser.cpp"
    break;

  case 71: // expr_atom: node_array
#line 322 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Array > ()); }
#line 2359 "src/parser.cpp"
    break;

  case 72: // expr_atom: paren_expr
#line 323 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2365 "src/parser.cpp"
    break;

  case 73: // expr_right: node_expr_if
#line 326 "gen/parser.y"
                  { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::ExprIf > ()); }
#line 2371 "src/parser.cpp"
    break;

  case 74: // expr_right: node_expr_for
#line 327 "gen/parser.y"
                  { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::ExprFor > ()); }
#line 2377 "src/parser.cpp"
    break;

  case 75: // expr_right: node_function
#line 328 "gen/parser.y"
                  { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Function > ()); }
#line 2383 "src/parser.cpp"
    break;

  case 76: // expr_assgn_target: expr_post
#line 331 "gen/parser.y"
              { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2389 "src/parser.cpp"
    break;

  case 77: // paren_type: OPAREN cat_type CPAREN
#line 336 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ());
    }
#line 2397 "src/parser.cpp"
    break;

  case 78: // paren_type: OPAREN type_list CPAREN
#line 339 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::category::Type > () = cynth::syn::node::TupleType{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::Type> > ())};
    }
#line 2405 "src/parser.cpp"
    break;

  case 79: // paren_type: OPAREN type_list COMMA CPAREN
#line 342 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::category::Type > () = cynth::syn::node::TupleType{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Type> > ())};
    }
#line 2413 "src/parser.cpp"
    break;

  case 80: // void_type: OPAREN CPAREN
#line 347 "gen/parser.y"
                  {
        yylhs.value.as < cynth::syn::category::Type > () = cynth::syn::node::TupleType{};
    }
#line 2421 "src/parser.cpp"
    break;

  case 81: // void_type: VOID
#line 350 "gen/parser.y"
         {
        yylhs.value.as < cynth::syn::category::Type > () = cynth::syn::node::TupleType{};
    }
#line 2429 "src/parser.cpp"
    break;

  case 82: // node_auto: AUTO
#line 355 "gen/parser.y"
         {
        yylhs.value.as < cynth::syn::node::Auto > () = {};
    }
#line 2437 "src/parser.cpp"
    break;

  case 83: // node_type_name: TYPENAME
#line 360 "gen/parser.y"
                   {
        yylhs.value.as < cynth::syn::node::TypeName > () = {YY_MOVE (yystack_[0].value.as < std::string > ())};
    }
#line 2445 "src/parser.cpp"
    break;

  case 84: // node_const_type: cat_type CONST
#line 365 "gen/parser.y"
                         {
        yylhs.value.as < cynth::syn::node::ConstType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ())};
    }
#line 2453 "src/parser.cpp"
    break;

  case 85: // node_in_type: cat_type IN
#line 370 "gen/parser.y"
                      {
        yylhs.value.as < cynth::syn::node::InType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ())};
    }
#line 2461 "src/parser.cpp"
    break;

  case 86: // node_out_type: cat_type OUT
#line 375 "gen/parser.y"
                       {
        yylhs.value.as < cynth::syn::node::OutType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ())};
    }
#line 2469 "src/parser.cpp"
    break;

  case 87: // node_function_type: cat_type paren_type
#line 380 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::syn::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 2477 "src/parser.cpp"
    break;

  case 88: // node_function_type: void_type paren_type
#line 383 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 2485 "src/parser.cpp"
    break;

  case 89: // node_function_type: cat_type void_type
#line 386 "gen/parser.y"
                                {
        yylhs.value.as < cynth::syn::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 2493 "src/parser.cpp"
    break;

  case 90: // node_function_type: void_type void_type
#line 389 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::syn::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 2501 "src/parser.cpp"
    break;

  case 91: // node_array_type: cat_type OBRACK cat_expression CBRACK
#line 394 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::syn::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .size = cynth::syn::category::Pattern{YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ())}};
    }
#line 2509 "src/parser.cpp"
    break;

  case 92: // node_array_type: cat_type OBRACK AUTO CBRACK
#line 397 "gen/parser.y"
                                      {
        yylhs.value.as < cynth::syn::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .size = esl::optional_component<cynth::syn::category::Pattern>{}};
    }
#line 2517 "src/parser.cpp"
    break;

  case 93: // node_array_type: cat_type OBRACK CBRACK
#line 400 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::syn::node::ArrayType > () = {.type = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Type > ()), .size = esl::optional_component<cynth::syn::category::Pattern>{}};
    }
#line 2525 "src/parser.cpp"
    break;

  case 94: // node_array_type: cat_type OBRACK cat_declaration CBRACK
#line 403 "gen/parser.y"
                                                            {
        yylhs.value.as < cynth::syn::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .size = cynth::syn::category::Pattern{YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ())}};
    }
#line 2533 "src/parser.cpp"
    break;

  case 95: // node_buffer_type: BUFFER OBRACK cat_expression CBRACK
#line 408 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::syn::node::BufferType > () = {.size = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ())};
    }
#line 2541 "src/parser.cpp"
    break;

  case 96: // paren_range_decl: OPAREN cat_range_decl CPAREN
#line 422 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::syn::category::RangeDeclaration > () = YY_MOVE (yystack_[1].value.as < cynth::syn::category::RangeDeclaration > ());
    }
#line 2549 "src/parser.cpp"
    break;

  case 97: // paren_range_decl: OPAREN range_decl_list CPAREN
#line 425 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::category::RangeDeclaration > () = cynth::syn::node::TupleRangeDecl{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::RangeDeclaration> > ())};
    }
#line 2557 "src/parser.cpp"
    break;

  case 98: // paren_range_decl: OPAREN range_decl_list COMMA CPAREN
#line 428 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::syn::category::RangeDeclaration > () = cynth::syn::node::TupleRangeDecl{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::RangeDeclaration> > ())};
    }
#line 2565 "src/parser.cpp"
    break;

  case 99: // paren_decl: OPAREN cat_declaration CPAREN
#line 433 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::syn::category::Declaration > () = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ());
    }
#line 2573 "src/parser.cpp"
    break;

  case 100: // paren_decl: OPAREN decl_list CPAREN
#line 436 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::category::Declaration > () = cynth::syn::node::TupleDecl{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::Declaration> > ())};
    }
#line 2581 "src/parser.cpp"
    break;

  case 101: // paren_decl: OPAREN decl_list COMMA CPAREN
#line 439 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::category::Declaration > () = cynth::syn::node::TupleDecl{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Declaration> > ())};
    }
#line 2589 "src/parser.cpp"
    break;

  case 102: // void_decl: OPAREN CPAREN
#line 444 "gen/parser.y"
                  {
        yylhs.value.as < cynth::syn::category::Declaration > () = cynth::syn::node::TupleDecl{};
    }
#line 2597 "src/parser.cpp"
    break;

  case 103: // node_declaration: cat_type node_name
#line 449 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Declaration > () = {.name = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Name > ()), .type = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ())};
    }
#line 2605 "src/parser.cpp"
    break;

  case 104: // node_range_decl: cat_declaration IN cat_expression
#line 454 "gen/parser.y"
                                                   {
        yylhs.value.as < cynth::syn::node::RangeDecl > () = {.declaration = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Declaration > ()), .range = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2613 "src/parser.cpp"
    break;

  case 105: // node_range_to: cat_expression TO cat_expression
#line 461 "gen/parser.y"
                                               {
        yylhs.value.as < cynth::syn::node::RangeTo > () = {.from = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), .to = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2621 "src/parser.cpp"
    break;

  case 106: // node_range_to_by: cat_expression TO cat_expression BY cat_expression
#line 466 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::syn::node::RangeToBy > () = {.from = YY_MOVE (yystack_[4].value.as < cynth::syn::category::Expression > ()), .to = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), .by = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2629 "src/parser.cpp"
    break;

  case 107: // node_spread: ELIP cat_expression
#line 471 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Spread > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2637 "src/parser.cpp"
    break;

  case 108: // paren_expr: OPAREN cat_expression CPAREN
#line 478 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ());
    }
#line 2645 "src/parser.cpp"
    break;

  case 109: // paren_expr: OPAREN expr_list CPAREN
#line 481 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::category::Expression > () = cynth::syn::node::Tuple{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::Expression> > ())};
    }
#line 2653 "src/parser.cpp"
    break;

  case 110: // paren_expr: OPAREN expr_list COMMA CPAREN
#line 484 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::category::Expression > () = cynth::syn::node::Tuple{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Expression> > ())};
    }
#line 2661 "src/parser.cpp"
    break;

  case 111: // void: OPAREN CPAREN
#line 489 "gen/parser.y"
                  {
        yylhs.value.as < cynth::syn::category::Expression > () = cynth::syn::node::Tuple{};
    }
#line 2669 "src/parser.cpp"
    break;

  case 112: // node_name: NAME
#line 494 "gen/parser.y"
               {
        yylhs.value.as < cynth::syn::node::Name > () = {YY_MOVE (yystack_[0].value.as < std::string > ())};
    }
#line 2677 "src/parser.cpp"
    break;

  case 113: // node_block: OBRACE CBRACE
#line 499 "gen/parser.y"
                  {
        yylhs.value.as < cynth::syn::node::Block > () = {};
    }
#line 2685 "src/parser.cpp"
    break;

  case 114: // node_block: OBRACE stmt_list CBRACE
#line 502 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::node::Block > () = {YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::Statement> > ())};
    }
#line 2693 "src/parser.cpp"
    break;

  case 115: // node_block: OBRACE stmt_list SEMI CBRACE
#line 505 "gen/parser.y"
                                       {
        yylhs.value.as < cynth::syn::node::Block > () = {YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Statement> > ())};
    }
#line 2701 "src/parser.cpp"
    break;

  case 116: // node_bool: TRUE
#line 512 "gen/parser.y"
         {
        yylhs.value.as < cynth::syn::node::Bool > () = {true};
    }
#line 2709 "src/parser.cpp"
    break;

  case 117: // node_bool: FALSE
#line 515 "gen/parser.y"
          {
        yylhs.value.as < cynth::syn::node::Bool > () = {false};
    }
#line 2717 "src/parser.cpp"
    break;

  case 118: // node_int: INT
#line 520 "gen/parser.y"
        {
        yylhs.value.as < cynth::syn::node::Int > () = {esl::stoi<cynth::sem::Integral>(YY_MOVE (yystack_[0].value.as < std::string > ()))}; // TODO: The sem::Integral type should be obtainable from syn::node::Int
    }
#line 2725 "src/parser.cpp"
    break;

  case 119: // node_float: FLOAT
#line 525 "gen/parser.y"
          {
        yylhs.value.as < cynth::syn::node::Float > () = {std::stof(YY_MOVE (yystack_[0].value.as < std::string > ()))};
    }
#line 2733 "src/parser.cpp"
    break;

  case 120: // node_string: STRING
#line 530 "gen/parser.y"
           {
        yylhs.value.as < cynth::syn::node::String > () = {esl::trim(YY_MOVE (yystack_[0].value.as < std::string > ()))};
    }
#line 2741 "src/parser.cpp"
    break;

  case 121: // node_function: cat_type FN paren_decl cat_expression
#line 535 "gen/parser.y"
                                                         {
        yylhs.value.as < cynth::syn::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2749 "src/parser.cpp"
    break;

  case 122: // node_function: void_type FN paren_decl cat_expression
#line 538 "gen/parser.y"
                                                          {
        yylhs.value.as < cynth::syn::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2757 "src/parser.cpp"
    break;

  case 123: // node_function: cat_type FN void_decl cat_expression
#line 541 "gen/parser.y"
                                                        {
        yylhs.value.as < cynth::syn::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2765 "src/parser.cpp"
    break;

  case 124: // node_function: void_type FN void_decl cat_expression
#line 544 "gen/parser.y"
                                                         {
        yylhs.value.as < cynth::syn::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2773 "src/parser.cpp"
    break;

  case 125: // node_array: OBRACK CBRACK
#line 549 "gen/parser.y"
                  {
        yylhs.value.as < cynth::syn::node::Array > () = {};
    }
#line 2781 "src/parser.cpp"
    break;

  case 126: // node_array: OBRACK array_elem_list CBRACK
#line 552 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::node::Array > () = {YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::ArrayElement> > ())};
    }
#line 2789 "src/parser.cpp"
    break;

  case 127: // node_array: OBRACK array_elem_list SEMI CBRACK
#line 555 "gen/parser.y"
                                             {
        yylhs.value.as < cynth::syn::node::Array > () = {YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::ArrayElement> > ())};
    }
#line 2797 "src/parser.cpp"
    break;

  case 128: // node_or: expr_or OR expr_and
#line 562 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::node::Or > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2805 "src/parser.cpp"
    break;

  case 129: // node_and: expr_and AND expr_eq
#line 567 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::And > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2813 "src/parser.cpp"
    break;

  case 130: // node_eq: expr_eq EQ expr_ord
#line 572 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::node::Eq > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2821 "src/parser.cpp"
    break;

  case 131: // node_ne: expr_eq NE expr_ord
#line 577 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::node::Ne > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2829 "src/parser.cpp"
    break;

  case 132: // node_ge: expr_ord GE expr_add
#line 582 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Ge > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2837 "src/parser.cpp"
    break;

  case 133: // node_le: expr_ord LE expr_add
#line 587 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Le > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2845 "src/parser.cpp"
    break;

  case 134: // node_gt: expr_ord GT expr_add
#line 592 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Gt > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2853 "src/parser.cpp"
    break;

  case 135: // node_lt: expr_ord LT expr_add
#line 597 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Lt > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2861 "src/parser.cpp"
    break;

  case 136: // node_add: expr_add ADD expr_mul
#line 602 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Add > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2869 "src/parser.cpp"
    break;

  case 137: // node_sub: expr_add SUB expr_mul
#line 607 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Sub > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2877 "src/parser.cpp"
    break;

  case 138: // node_mul: expr_mul MUL expr_pow
#line 612 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Mul > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2885 "src/parser.cpp"
    break;

  case 139: // node_div: expr_mul DIV expr_pow
#line 617 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Div > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2893 "src/parser.cpp"
    break;

  case 140: // node_mod: expr_mul MOD expr_pow
#line 622 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Mod > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2901 "src/parser.cpp"
    break;

  case 141: // node_pow: expr_pre POW expr_pow
#line 627 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Pow > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2909 "src/parser.cpp"
    break;

  case 142: // node_minus: SUB expr_pre
#line 632 "gen/parser.y"
                      {
        yylhs.value.as < cynth::syn::node::Minus > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2917 "src/parser.cpp"
    break;

  case 143: // node_plus: ADD expr_pre
#line 637 "gen/parser.y"
                      {
        yylhs.value.as < cynth::syn::node::Plus > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2925 "src/parser.cpp"
    break;

  case 144: // node_not: NOT expr_pre
#line 642 "gen/parser.y"
                      {
        yylhs.value.as < cynth::syn::node::Not > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2933 "src/parser.cpp"
    break;

  case 145: // node_application: expr_post paren_expr
#line 647 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::syn::node::Application > () = {.function = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ()), .arguments = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2941 "src/parser.cpp"
    break;

  case 146: // node_application: expr_post void
#line 650 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::node::Application > () = {.function = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ()), .arguments = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2949 "src/parser.cpp"
    break;

  case 147: // node_conversion: cat_type paren_expr
#line 655 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::node::Conversion > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ()), .argument = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2957 "src/parser.cpp"
    break;

  case 148: // node_subscript: expr_post OBRACK array_elem_list CBRACK
#line 660 "gen/parser.y"
                                                                 {
        yylhs.value.as < cynth::syn::node::Subscript > () = {.container = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ()), .location = YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::ArrayElement> > ())};
    }
#line 2965 "src/parser.cpp"
    break;

  case 149: // node_subscript: expr_post OBRACK CBRACK
#line 663 "gen/parser.y"
                                       {
        yylhs.value.as < cynth::syn::node::Subscript > () = {.container = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), .location = {}};
    }
#line 2973 "src/parser.cpp"
    break;

  case 150: // node_expr_if: IF paren_expr cat_expression ELSE cat_expression
#line 668 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::syn::node::ExprIf > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ()), .positiveBranch = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), .negativeBranch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2981 "src/parser.cpp"
    break;

  case 151: // node_expr_for: FOR paren_range_decl cat_expression
#line 673 "gen/parser.y"
                                                    {
        yylhs.value.as < cynth::syn::node::ExprFor > () = {.declarations = YY_MOVE (yystack_[1].value.as < cynth::syn::category::RangeDeclaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2989 "src/parser.cpp"
    break;

  case 152: // node_definition: cat_declaration ASSGN cat_expression
#line 680 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::syn::node::Definition > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Declaration > ()), .value = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2997 "src/parser.cpp"
    break;

  case 153: // node_assignment: expr_assgn_target ASSGN cat_expression
#line 685 "gen/parser.y"
                                                        {
        yylhs.value.as < cynth::syn::node::Assignment > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), .value = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3005 "src/parser.cpp"
    break;

  case 154: // node_type_def: TYPE node_type_name ASSGN cat_type
#line 690 "gen/parser.y"
                                                     {
        yylhs.value.as < cynth::syn::node::TypeDef > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::syn::node::TypeName > ()), .type = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 3013 "src/parser.cpp"
    break;

  case 155: // node_function_def: cat_type node_name paren_decl cat_expression
#line 695 "gen/parser.y"
                                                                      {
        yylhs.value.as < cynth::syn::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::syn::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3021 "src/parser.cpp"
    break;

  case 156: // node_function_def: void_type node_name paren_decl cat_expression
#line 698 "gen/parser.y"
                                                                       {
        yylhs.value.as < cynth::syn::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::syn::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3029 "src/parser.cpp"
    break;

  case 157: // node_function_def: cat_type node_name void_decl cat_expression
#line 701 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::syn::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::syn::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3037 "src/parser.cpp"
    break;

  case 158: // node_function_def: void_type node_name void_decl cat_expression
#line 704 "gen/parser.y"
                                                                      {
        yylhs.value.as < cynth::syn::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::syn::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3045 "src/parser.cpp"
    break;

  case 159: // node_return: RETURN cat_expression
#line 709 "gen/parser.y"
                               {
        yylhs.value.as < cynth::syn::node::Return > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3053 "src/parser.cpp"
    break;

  case 160: // node_return: RETURN void
#line 712 "gen/parser.y"
                     {
        yylhs.value.as < cynth::syn::node::Return > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3061 "src/parser.cpp"
    break;

  case 161: // node_return: RETURN
#line 715 "gen/parser.y"
           {
        yylhs.value.as < cynth::syn::node::Return > () = {cynth::syn::category::Expression{cynth::syn::node::Tuple{}}};
    }
#line 3069 "src/parser.cpp"
    break;

  case 162: // node_if: IF paren_expr pure ELSE pure
#line 720 "gen/parser.y"
                                                 {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ()), .positiveBranch = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Statement > ()), .negativeBranch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3077 "src/parser.cpp"
    break;

  case 163: // node_if: IF paren_expr pure SEMI ELSE pure
#line 723 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[4].value.as < cynth::syn::category::Expression > ()), .positiveBranch = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Statement > ()), .negativeBranch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3085 "src/parser.cpp"
    break;

  case 164: // node_if: IF paren_expr cat_expression ELSE pure
#line 726 "gen/parser.y"
                                                           {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ()), .positiveBranch = cynth::syn::category::Statement{YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ())}, .negativeBranch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3093 "src/parser.cpp"
    break;

  case 165: // node_if: IF paren_expr cat_expression SEMI ELSE pure
#line 729 "gen/parser.y"
                                                                {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[4].value.as < cynth::syn::category::Expression > ()), .positiveBranch = cynth::syn::category::Statement{YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ())}, .negativeBranch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3101 "src/parser.cpp"
    break;

  case 166: // node_if: IF paren_expr pure ELSE cat_expression
#line 732 "gen/parser.y"
                                                           {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ()), .positiveBranch = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Statement > ()), .negativeBranch = cynth::syn::category::Statement{YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())}};
    }
#line 3109 "src/parser.cpp"
    break;

  case 167: // node_if: IF paren_expr pure SEMI ELSE cat_expression
#line 735 "gen/parser.y"
                                                                {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[4].value.as < cynth::syn::category::Expression > ()), .positiveBranch = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Statement > ()), .negativeBranch = cynth::syn::category::Statement{YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())}};
    }
#line 3117 "src/parser.cpp"
    break;

  case 168: // node_when: WHEN paren_expr cat_statement
#line 740 "gen/parser.y"
                                             {
        yylhs.value.as < cynth::syn::node::When > () = {.condition = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ()), .branch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3125 "src/parser.cpp"
    break;

  case 169: // node_for: FOR paren_range_decl pure
#line 745 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::syn::node::For > () = {.declarations = YY_MOVE (yystack_[1].value.as < cynth::syn::category::RangeDeclaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3133 "src/parser.cpp"
    break;

  case 170: // node_while: WHILE paren_expr cat_statement
#line 750 "gen/parser.y"
                                               {
        yylhs.value.as < cynth::syn::node::While > () = {.condition = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3141 "src/parser.cpp"
    break;

  case 171: // array_elem_list: cat_array_elem
#line 757 "gen/parser.y"
                          {
        yylhs.value.as < esl::component_vector<cynth::syn::category::ArrayElement> > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::ArrayElement > ())};
    }
#line 3149 "src/parser.cpp"
    break;

  case 172: // array_elem_list: array_elem_list COMMA cat_array_elem
#line 760 "gen/parser.y"
                                                     {
        yylhs.value.as < esl::component_vector<cynth::syn::category::ArrayElement> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::ArrayElement > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::ArrayElement> > ()));
    }
#line 3157 "src/parser.cpp"
    break;

  case 173: // stmt_list: cat_statement
#line 765 "gen/parser.y"
                         {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Statement> > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3165 "src/parser.cpp"
    break;

  case 174: // stmt_list: stmt_list SEMI cat_statement
#line 768 "gen/parser.y"
                                             {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Statement> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Statement> > ()));
    }
#line 3173 "src/parser.cpp"
    break;

  case 175: // type_list: cat_type COMMA cat_type
#line 773 "gen/parser.y"
                                           {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Type> > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Type > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 3181 "src/parser.cpp"
    break;

  case 176: // type_list: type_list COMMA cat_type
#line 776 "gen/parser.y"
                                         {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Type> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Type> > ()));
    }
#line 3189 "src/parser.cpp"
    break;

  case 177: // expr_list: cat_expression COMMA cat_expression
#line 781 "gen/parser.y"
                                                       {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Expression> > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3197 "src/parser.cpp"
    break;

  case 178: // expr_list: expr_list COMMA cat_expression
#line 784 "gen/parser.y"
                                               {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Expression> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Expression> > ()));
    }
#line 3205 "src/parser.cpp"
    break;

  case 179: // decl_list: cat_declaration COMMA cat_declaration
#line 789 "gen/parser.y"
                                                         {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Declaration> > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Declaration > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Declaration > ())};
    }
#line 3213 "src/parser.cpp"
    break;

  case 180: // decl_list: decl_list COMMA cat_declaration
#line 792 "gen/parser.y"
                                                {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Declaration> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::Declaration > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Declaration> > ()));
    }
#line 3221 "src/parser.cpp"
    break;

  case 181: // range_decl_list: cat_range_decl COMMA cat_range_decl
#line 797 "gen/parser.y"
                                                       {
        yylhs.value.as < esl::component_vector<cynth::syn::category::RangeDeclaration> > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::RangeDeclaration > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::RangeDeclaration > ())};
    }
#line 3229 "src/parser.cpp"
    break;

  case 182: // range_decl_list: range_decl_list COMMA cat_range_decl
#line 800 "gen/parser.y"
                                                     {
        yylhs.value.as < esl::component_vector<cynth::syn::category::RangeDeclaration> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::RangeDeclaration > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::RangeDeclaration> > ()));
    }
#line 3237 "src/parser.cpp"
    break;


#line 3241 "src/parser.cpp"

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





  const short parser::yypact_ninf_ = -135;

  const signed char parser::yytable_ninf_ = -81;

  const short
  parser::yypact_[] =
  {
     637,  -135,  -135,  -135,  -135,  -135,     4,     4,    16,     4,
      33,    34,  1037,  -135,  -135,  -135,   757,   516,   677,  -135,
    1117,  1117,  1117,    70,    36,    65,  -135,  -135,  -135,    48,
      77,   -33,   418,   154,    50,  -135,   101,   -10,  -135,  -135,
     150,  -135,   158,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,   161,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,   157,  1077,   637,   637,   355,   637,   637,
     164,  1077,     4,    16,   797,   201,  -135,    -1,    27,  -135,
    -135,    24,     6,    28,  -135,    94,   113,   114,  -135,    96,
    1077,   837,  -135,  -135,   171,  -135,  -135,  -135,    53,   241,
    -135,   146,  -135,  -135,  -135,   170,  -135,  -135,  -135,   877,
    -135,  -135,  -135,   170,  1077,  1117,  1117,  1117,  1117,  1117,
    1117,  1117,  1117,  1117,  1117,  1117,  1117,  1117,  1117,   917,
     717,  -135,  -135,  1077,   170,   203,  -135,  -135,   170,   637,
      -7,    -6,  -135,   377,    90,   189,   137,  -135,  -135,   140,
    -135,  -135,  -135,   398,   183,  1077,  1077,    98,  1170,   398,
    -135,  -135,  1096,  -135,  1077,  -135,   427,  -135,   449,  -135,
     957,  -135,   597,  -135,  -135,  1077,   185,   997,  -135,   468,
    1077,  1077,   188,  -135,    36,   190,   193,  1077,  1077,  -135,
      77,   -33,   418,   418,   154,   154,   154,   154,    50,    50,
    -135,  -135,  -135,  -135,  -135,  -135,    68,  -135,  1077,  1077,
    1183,  1077,  1077,  -135,   637,   212,   637,   219,    49,   111,
    1077,   355,  -135,   551,  -135,   390,  -135,   226,   390,   553,
    -135,  -135,  -135,   390,  -135,  -135,  -135,  -135,  -135,   210,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  1157,  -135,  -135,
     637,  -135,  -135,  -135,  -135,  1077,  1077,     4,    16,    97,
    -135,    -1,    11,  -135,  -135,  -135,   637,  1157,    -4,  1157
  };

  const unsigned char
  parser::yydefact_[] =
  {
       2,   112,    83,   118,   119,   120,     0,     0,     0,     0,
       0,     0,   161,   116,   117,    82,     0,     0,     0,    81,
       0,     0,     0,     0,     0,     0,    25,   173,    24,    22,
      37,    39,    42,    47,    50,    54,    56,    60,    64,    23,
       0,    21,     0,    13,    14,    18,    19,    20,    15,    16,
      17,     6,    26,    72,    65,    70,    66,    67,    68,    69,
      75,    71,    36,    38,    40,    41,    43,    44,    45,    46,
      48,    49,    51,    52,    53,    55,    58,    57,    59,    61,
      62,    63,    73,    74,    27,    28,    30,    29,    31,    32,
      35,    33,    34,     3,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   159,    60,     0,   160,
      80,     0,     0,     0,     5,     0,     0,     0,   113,     0,
       0,     0,   125,   171,    12,     9,    10,    11,     0,     0,
     143,     0,   142,   144,     1,     0,    84,    85,    86,     0,
      87,    89,   147,   103,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   145,   146,     0,     0,     0,    88,    90,     0,     4,
       0,     0,   168,     0,     0,     0,     0,     8,     7,     0,
     151,   169,   170,     0,     0,     0,     0,   111,     0,     0,
      77,   103,     0,    99,     0,   108,     0,    78,     0,   100,
       0,   109,     0,   114,   107,     0,     0,     0,   126,     0,
       0,     0,    82,    93,     0,     0,     0,     0,     0,   152,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   111,   149,     0,   153,     0,     0,
       0,     0,     0,   174,     0,     0,     0,     0,     0,     0,
       0,     0,    96,     0,    97,   154,    95,     0,   175,     0,
     179,   177,    79,   176,   101,   180,   110,   178,   115,   105,
     127,   172,   102,   121,   123,    92,    94,    91,   155,   157,
     148,   122,   124,   156,   158,   150,   164,     0,   166,   162,
       0,   104,   181,    98,   182,     0,     0,     0,     0,     0,
     165,    76,     0,   167,   163,   106,     0,     0,     0,     0
  };

  const short
  parser::yypgoto_[] =
  {
    -135,  -135,   184,    69,   -73,    32,   300,   -92,   -15,  -135,
     102,    95,    47,   363,    58,   407,   118,     8,  -135,  -135,
    -135,   321,     0,  -135,   233,  -135,  -135,  -135,  -135,  -135,
    -135,  -134,    -2,  -133,   187,  -135,  -135,  -135,  -135,    57,
     237,     2,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,   104,  -135,   239
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,    23,   105,    25,   176,   123,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,   107,    38,    39,
      40,    41,   108,    43,    44,    45,    46,    47,    48,    49,
      50,    51,   177,   211,    52,   178,   125,   126,   127,    53,
     162,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
     115,   116,   179,   128,   117,    93
  };

  const short
  parser::yytable_[] =
  {
      42,   210,   244,   246,   172,   309,    98,   182,    37,   217,
     218,   -76,   147,   148,     1,   245,   247,    42,   245,   159,
     131,   131,   131,   160,   141,    37,   143,     1,   159,   192,
     238,   239,   160,    94,   241,   242,   193,     2,   135,     1,
     165,   164,   167,   136,   168,    97,    19,   189,   137,   138,
     135,   194,     1,   121,   190,   136,   165,   139,   195,    19,
     137,   138,    19,    95,    96,   121,    99,   101,   136,   139,
     134,    19,   189,   137,   138,   206,   207,   243,   165,   190,
     171,   142,   139,   181,    19,   112,   144,   208,   155,   156,
     157,   207,   145,     1,   161,    42,    42,   131,    42,    42,
       1,   186,   280,    37,    37,   141,    37,    37,   167,   136,
     243,   141,   -80,   191,   137,   138,   136,   196,   202,   165,
     146,   137,   138,   139,   197,    19,   121,   -80,   203,   141,
     139,   167,    19,   -80,   192,   250,   198,   200,   130,   132,
     133,   193,   158,   199,   201,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   185,
     251,     1,   142,   253,   161,   131,   175,   252,   142,    42,
     254,   163,   164,   131,   141,   165,   191,    37,   292,   169,
     294,    19,    -5,   131,    24,   183,   142,   165,   141,   131,
     153,   154,   131,    19,   222,   223,   131,   205,   131,   209,
     111,    24,    42,   114,   129,   129,   129,     2,   215,   131,
      37,   228,   229,   250,   141,   135,   191,   256,    11,   270,
     136,   287,   275,    15,   276,   137,   138,   277,   290,   286,
     121,   289,   165,   110,   139,   295,    19,   296,    19,   271,
     141,   221,   249,   100,    42,   142,    42,   220,   141,   109,
     191,   131,    37,   131,    37,   141,   119,     0,   141,   131,
     136,   260,     0,   141,   236,   137,   138,   265,     0,     0,
     121,   142,   300,     0,   139,   304,    19,     0,   112,    24,
      24,   174,    24,    24,   114,     0,     0,   302,   188,     0,
      42,   171,   181,     0,   286,   301,   307,     0,    37,   141,
       0,   143,   167,     0,   168,   188,    42,   302,     0,   302,
       0,     0,   106,     0,    37,   301,   113,   301,   124,     0,
     175,     0,   175,   214,     0,     0,   114,     0,   112,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,     0,     0,   140,     0,     0,     0,   240,
       0,     0,     0,    24,   306,     0,   142,   248,   161,     2,
     114,     0,     0,   166,     0,     0,     0,   255,     0,     0,
      11,     0,     0,   258,     0,    15,   174,     0,     0,   114,
     263,     2,   174,     0,   173,   114,    24,     0,     0,     0,
      19,     0,    11,   174,   113,   170,   114,    15,   180,     0,
       0,   184,     2,     0,   113,     0,   173,   110,     0,   136,
       0,     0,    19,    11,   137,   138,     0,     0,    15,   165,
     204,   113,     0,   139,     0,    19,   140,   165,    24,   166,
      24,     2,   140,    19,     0,   174,     0,   174,   114,   216,
     114,     0,    11,   248,   219,     0,   114,    15,     0,     0,
     140,     0,   166,     2,     0,     0,   165,   262,     0,   113,
     124,     0,    19,   237,    11,   149,   150,   151,   152,    15,
       0,   299,     2,     0,    24,     0,     0,     0,   259,   264,
       0,     0,     0,    11,    19,   257,   180,     0,    15,     0,
      24,   299,     0,   299,   261,   140,     0,   259,   272,     0,
     267,     0,     0,    19,     0,   269,     0,   124,     0,   140,
     273,   274,   224,   225,   226,   227,     0,   278,   279,     1,
       2,     3,     4,     5,     6,     0,     7,     8,     9,    10,
       0,    11,    12,    13,    14,   140,    15,     0,   281,   282,
       0,   283,   284,     0,   285,    16,   288,    17,   118,    18,
     291,    19,    20,    21,     0,     2,     0,     2,    22,     0,
       0,   140,   230,   231,   232,   233,    11,     0,    11,   140,
       0,    15,     0,    15,     0,     0,   140,     0,     0,   140,
     173,   293,   259,   110,   140,     0,    19,     0,    19,     0,
     303,     0,     0,     0,     0,   285,   305,     0,     0,     0,
       1,     2,     3,     4,     5,     6,   308,     7,     8,     9,
      10,     0,    11,    12,    13,    14,     0,    15,     0,     0,
     140,     0,     0,   166,     0,     0,    16,     0,    17,   268,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,     6,     0,     7,     8,     9,
      10,     0,    11,    12,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,    16,     0,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   102,     0,     0,   103,     0,
       0,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,   120,   121,     0,    17,     0,
      18,   122,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   102,     0,     0,   103,     0,
       0,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,   120,   121,     0,    17,     0,
      18,   235,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   102,     0,     0,   103,     0,
       0,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,    16,   110,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   102,     0,     0,   103,     0,
       0,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,   121,   187,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   102,     0,     0,   103,     0,
       0,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,   121,   110,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   102,     0,     0,   103,     0,
       0,     0,    11,     0,    13,    14,     0,   212,     0,     0,
       0,     0,     0,     0,     0,     0,    16,     0,    17,     0,
      18,   213,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   102,     0,     0,   103,     0,
       0,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,   121,   234,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   102,     0,     0,   103,     0,
       0,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,   121,   266,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   102,     0,     0,   103,     0,
       0,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,   120,   121,     0,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   102,     0,     0,   103,     0,
       0,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,   104,     0,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   102,     0,     0,   103,     0,
       0,     0,    11,     0,    13,    14,     0,    15,     0,     0,
       2,     0,     0,     0,     0,     0,   121,     0,    17,     0,
      18,    11,    19,    20,    21,     0,    15,     0,     0,    22,
       1,     2,     3,     4,     5,   259,     0,     0,     0,     0,
       0,    19,    11,     0,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,   121,     0,    17,     0,
      18,     0,    19,    20,    21,     0,     0,     0,     0,    22,
       1,     2,     3,     4,     5,   297,     0,     7,   298,     9,
      10,     0,    11,    12,    13,    14,     0,    15,     0,     0,
       0,     0,     0,     0,   135,     0,    16,     0,    17,   136,
      18,     0,    19,   189,   137,   138,     0,     0,     0,   121,
     190,     0,   136,   139,     0,    19,   189,   137,   138,     0,
       0,     0,   165,   190,     0,     0,   139,     0,    19
  };

  const short
  parser::yycheck_[] =
  {
       0,   135,     9,     9,    96,     9,     8,    99,     0,   143,
     143,    21,    45,    46,     3,    22,    22,    17,    22,    29,
      20,    21,    22,    33,    24,    17,    24,     3,    29,    23,
     164,   164,    33,    29,   168,   168,    30,     4,    14,     3,
      29,    14,    42,    19,    42,    29,    35,    23,    24,    25,
      14,    23,     3,    29,    30,    19,    29,    33,    30,    35,
      24,    25,    35,     6,     7,    29,     9,    33,    19,    33,
       0,    35,    23,    24,    25,    22,    23,   169,    29,    30,
      95,    24,    33,    98,    35,    16,    21,    34,    38,    39,
      40,    23,    44,     3,    37,    95,    96,    97,    98,    99,
       3,   103,    34,    95,    96,   105,    98,    99,   108,    19,
     202,   111,    14,   111,    24,    25,    19,    23,    22,    29,
      43,    24,    25,    33,    30,    35,    29,    29,    32,   129,
      33,   131,    35,    35,    23,    24,    23,    23,    20,    21,
      22,    30,    41,    30,    30,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   102,
      23,     3,   105,    23,   107,   165,    97,    30,   111,   169,
      30,    21,    14,   173,   174,    29,   174,   169,   251,    22,
     253,    35,    21,   183,     0,    21,   129,    29,   188,   189,
      36,    37,   192,    35,   147,   148,   196,    26,   198,    29,
      16,    17,   202,    16,    20,    21,    22,     4,   139,   209,
     202,   153,   154,    24,   214,    14,   214,    34,    15,    34,
      19,     9,    34,    20,    34,    24,    25,    34,     9,   244,
      29,   246,    29,    30,    33,     9,    35,    27,    35,   207,
     240,   146,   173,    10,   244,   188,   246,   145,   248,    12,
     248,   251,   244,   253,   246,   255,    17,    -1,   258,   259,
      19,   192,    -1,   263,   160,    24,    25,   198,    -1,    -1,
      29,   214,   287,    -1,    33,   290,    35,    -1,   209,    95,
      96,    97,    98,    99,    97,    -1,    -1,   287,   104,    -1,
     290,   306,   307,    -1,   309,   287,   298,    -1,   290,   299,
      -1,   299,   302,    -1,   302,   121,   306,   307,    -1,   309,
      -1,    -1,    12,    -1,   306,   307,    16,   309,    18,    -1,
     251,    -1,   253,   139,    -1,    -1,   139,    -1,   259,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,    -1,    -1,    24,    -1,    -1,    -1,   165,
      -1,    -1,    -1,   169,   297,    -1,   299,   173,   301,     4,
     173,    -1,    -1,    42,    -1,    -1,    -1,   183,    -1,    -1,
      15,    -1,    -1,   189,    -1,    20,   192,    -1,    -1,   192,
     196,     4,   198,    -1,    29,   198,   202,    -1,    -1,    -1,
      35,    -1,    15,   209,    94,    95,   209,    20,    98,    -1,
      -1,   101,     4,    -1,   104,    -1,    29,    30,    -1,    19,
      -1,    -1,    35,    15,    24,    25,    -1,    -1,    20,    29,
     120,   121,    -1,    33,    -1,    35,   105,    29,   244,   108,
     246,     4,   111,    35,    -1,   251,    -1,   253,   251,   139,
     253,    -1,    15,   259,   144,    -1,   259,    20,    -1,    -1,
     129,    -1,   131,     4,    -1,    -1,    29,    30,    -1,   159,
     160,    -1,    35,   163,    15,    47,    48,    49,    50,    20,
      -1,   287,     4,    -1,   290,    -1,    -1,    -1,    29,    30,
      -1,    -1,    -1,    15,    35,   185,   186,    -1,    20,    -1,
     306,   307,    -1,   309,   194,   174,    -1,    29,    30,    -1,
     200,    -1,    -1,    35,    -1,   205,    -1,   207,    -1,   188,
     210,   211,   149,   150,   151,   152,    -1,   217,   218,     3,
       4,     5,     6,     7,     8,    -1,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,   214,    20,    -1,   238,   239,
      -1,   241,   242,    -1,   244,    29,   246,    31,    32,    33,
     250,    35,    36,    37,    -1,     4,    -1,     4,    42,    -1,
      -1,   240,   155,   156,   157,   158,    15,    -1,    15,   248,
      -1,    20,    -1,    20,    -1,    -1,   255,    -1,    -1,   258,
      29,    30,    29,    30,   263,    -1,    35,    -1,    35,    -1,
     290,    -1,    -1,    -1,    -1,   295,   296,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,   306,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    -1,    20,    -1,    -1,
     299,    -1,    -1,   302,    -1,    -1,    29,    -1,    31,    32,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    31,    -1,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    31,    -1,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    -1,    11,    -1,
      -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
       4,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,
      33,    15,    35,    36,    37,    -1,    20,    -1,    -1,    42,
       3,     4,     5,     6,     7,    29,    -1,    -1,    -1,    -1,
      -1,    35,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,
      33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
       3,     4,     5,     6,     7,     8,    -1,    10,    11,    12,
      13,    -1,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    14,    -1,    29,    -1,    31,    19,
      33,    -1,    35,    23,    24,    25,    -1,    -1,    -1,    29,
      30,    -1,    19,    33,    -1,    35,    23,    24,    25,    -1,
      -1,    -1,    29,    30,    -1,    -1,    33,    -1,    35
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,     8,    10,    11,    12,
      13,    15,    16,    17,    18,    20,    29,    31,    33,    35,
      36,    37,    42,    53,    54,    55,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    86,    91,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   137,    29,    91,    91,    29,    84,    91,
      76,    33,     8,    11,    29,    54,    58,    69,    74,    92,
      30,    54,    55,    58,    86,   132,   133,   136,    32,   137,
      28,    29,    34,    57,    58,    88,    89,    90,   135,    54,
      68,    74,    68,    68,     0,    14,    19,    24,    25,    33,
      73,    74,    91,    93,    21,    44,    43,    45,    46,    47,
      48,    49,    50,    36,    37,    38,    39,    40,    41,    29,
      33,    91,    92,    21,    14,    29,    73,    74,    93,    22,
      58,    60,    59,    29,    54,    55,    56,    84,    87,   134,
      58,    60,    59,    21,    58,    91,    84,    30,    54,    23,
      30,    93,    23,    30,    23,    30,    23,    30,    23,    30,
      23,    30,    22,    32,    58,    26,    22,    23,    34,    29,
      83,    85,    20,    34,    54,    55,    58,    83,    85,    58,
      62,    63,    64,    64,    65,    65,    65,    65,    66,    66,
      67,    67,    67,    67,    30,    34,   135,    58,    83,    85,
      54,    83,    85,    59,     9,    22,     9,    22,    54,    55,
      24,    23,    30,    23,    30,    54,    34,    58,    54,    29,
      55,    58,    30,    54,    30,    55,    30,    58,    32,    58,
      34,    57,    30,    58,    58,    34,    34,    34,    58,    58,
      34,    58,    58,    58,    58,    58,    60,     9,    58,    60,
       9,    58,    56,    30,    56,     9,    27,     8,    11,    54,
      60,    69,    74,    58,    60,    58,    91,    84,    58,     9
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    52,    53,    53,    53,    55,    55,    56,    56,    57,
      57,    57,    57,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    58,    58,    59,    59,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    61,    61,    62,    62,
      63,    63,    63,    64,    64,    64,    64,    64,    65,    65,
      65,    66,    66,    66,    66,    67,    67,    68,    68,    68,
      68,    69,    69,    69,    69,    70,    70,    70,    70,    70,
      70,    70,    70,    71,    71,    71,    72,    73,    73,    73,
      74,    74,    75,    76,    77,    78,    79,    80,    80,    80,
      80,    81,    81,    81,    81,    82,    84,    84,    84,    83,
      83,    83,    85,    86,    87,    88,    89,    90,    91,    91,
      91,    92,    93,    94,    94,    94,    95,    95,    96,    97,
      98,    99,    99,    99,    99,   100,   100,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   116,   115,   117,   118,   118,   119,   120,   120,
     121,   122,   123,   124,   126,   125,   125,   125,   125,   127,
     127,   127,   128,   128,   128,   128,   128,   128,   129,   130,
     131,   135,   135,   137,   137,   132,   132,   136,   136,   133,
     133,   134,   134
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
       1,     1,     1,     1,     1,     1,     1,     3,     3,     4,
       2,     1,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     4,     4,     3,     4,     4,     3,     3,     4,     3,
       3,     4,     2,     2,     3,     3,     5,     2,     3,     3,
       4,     2,     1,     2,     3,     4,     1,     1,     1,     1,
       1,     4,     4,     4,     4,     2,     3,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     2,     2,     4,     3,
       5,     3,     3,     3,     4,     4,     4,     4,     4,     2,
       2,     1,     5,     6,     5,     6,     5,     6,     3,     3,
       3,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3
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
  "node_buffer_type", "paren_decl", "paren_range_decl", "void_decl",
  "node_declaration", "node_range_decl", "node_range_to",
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
       0,   206,   206,   209,   212,   219,   220,   223,   224,   227,
     228,   229,   230,   233,   234,   235,   236,   237,   241,   242,
     243,   244,   247,   248,   251,   252,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   269,   270,   273,   274,
     277,   278,   279,   282,   283,   284,   285,   286,   289,   290,
     291,   294,   295,   296,   297,   300,   301,   304,   305,   306,
     307,   310,   311,   312,   313,   316,   317,   318,   319,   320,
     321,   322,   323,   326,   327,   328,   331,   336,   339,   342,
     347,   350,   355,   360,   365,   370,   375,   380,   383,   386,
     389,   394,   397,   400,   403,   408,   422,   425,   428,   433,
     436,   439,   444,   449,   454,   461,   466,   471,   478,   481,
     484,   489,   494,   499,   502,   505,   512,   515,   520,   525,
     530,   535,   538,   541,   544,   549,   552,   555,   562,   567,
     572,   577,   582,   587,   592,   597,   602,   607,   612,   617,
     622,   627,   632,   637,   642,   647,   650,   655,   660,   663,
     668,   673,   680,   685,   690,   695,   698,   701,   704,   709,
     712,   715,   720,   723,   726,   729,   732,   735,   740,   745,
     750,   757,   760,   765,   768,   773,   776,   781,   784,   789,
     792,   797,   800
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
#line 3959 "src/parser.cpp"

#line 804 "gen/parser.y"


void yy::parser::error (std::string const & msg) {
    // TODO: There's a syntax error every time for some reason.
    std::cerr << "parser error: " << msg << '\n';
}
