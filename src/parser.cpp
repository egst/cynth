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
  parser::parser (std::pair<cynth::syn::node::Block &, bool &> result_yyarg)
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
        result.first  = {};
        result.second = true;
    }
#line 1942 "src/parser.cpp"
    break;

  case 3: // start: stmt_list
#line 210 "gen/parser.y"
                    {
        result.first  = {YY_MOVE (yystack_[0].value.as < esl::component_vector<cynth::syn::category::Statement> > ())};
        result.second = true;
    }
#line 1951 "src/parser.cpp"
    break;

  case 4: // start: stmt_list SEMI
#line 214 "gen/parser.y"
                         {
        result.first  = {YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::Statement> > ())};
        result.second = true;
    }
#line 1960 "src/parser.cpp"
    break;

  case 5: // start: error
#line 218 "gen/parser.y"
          {
        result.first  = {};
        result.second = false;
    }
#line 1969 "src/parser.cpp"
    break;

  case 6: // cat_declaration: node_declaration
#line 226 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Declaration > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Declaration > ()); }
#line 1975 "src/parser.cpp"
    break;

  case 7: // cat_declaration: paren_decl
#line 227 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Declaration > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Declaration > ()); }
#line 1981 "src/parser.cpp"
    break;

  case 8: // cat_range_decl: node_range_decl
#line 230 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::RangeDeclaration > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::RangeDecl > ()); }
#line 1987 "src/parser.cpp"
    break;

  case 9: // cat_range_decl: paren_range_decl
#line 231 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::RangeDeclaration > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::RangeDeclaration > ()); }
#line 1993 "src/parser.cpp"
    break;

  case 10: // cat_array_elem: node_range_to
#line 234 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::RangeTo > ()); }
#line 1999 "src/parser.cpp"
    break;

  case 11: // cat_array_elem: node_range_to_by
#line 235 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::RangeToBy > ()); }
#line 2005 "src/parser.cpp"
    break;

  case 12: // cat_array_elem: node_spread
#line 236 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Spread > ()); }
#line 2011 "src/parser.cpp"
    break;

  case 13: // cat_array_elem: cat_expression
#line 237 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2017 "src/parser.cpp"
    break;

  case 14: // cat_type: node_auto
#line 240 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Auto > ()); }
#line 2023 "src/parser.cpp"
    break;

  case 15: // cat_type: node_type_name
#line 241 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::TypeName > ()); }
#line 2029 "src/parser.cpp"
    break;

  case 16: // cat_type: node_function_type
#line 242 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::FunctionType > ()); }
#line 2035 "src/parser.cpp"
    break;

  case 17: // cat_type: node_array_type
#line 243 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::ArrayType > ()); }
#line 2041 "src/parser.cpp"
    break;

  case 18: // cat_type: node_buffer_type
#line 244 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::BufferType > ()); }
#line 2047 "src/parser.cpp"
    break;

  case 19: // cat_type: node_const_type
#line 248 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::ConstType > ()); }
#line 2053 "src/parser.cpp"
    break;

  case 20: // cat_type: node_in_type
#line 249 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::InType > ()); }
#line 2059 "src/parser.cpp"
    break;

  case 21: // cat_type: node_out_type
#line 250 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::OutType > ()); }
#line 2065 "src/parser.cpp"
    break;

  case 22: // cat_type: paren_type
#line 251 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ()); }
#line 2071 "src/parser.cpp"
    break;

  case 23: // cat_expression: expr_or
#line 254 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2077 "src/parser.cpp"
    break;

  case 24: // cat_expression: expr_right
#line 255 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2083 "src/parser.cpp"
    break;

  case 25: // cat_statement: pure
#line 258 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ()); }
#line 2089 "src/parser.cpp"
    break;

  case 26: // cat_statement: cat_expression
#line 259 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2095 "src/parser.cpp"
    break;

  case 27: // pure: node_declaration
#line 264 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Declaration > ()); }
#line 2101 "src/parser.cpp"
    break;

  case 28: // pure: node_definition
#line 265 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Definition > ()); }
#line 2107 "src/parser.cpp"
    break;

  case 29: // pure: node_assignment
#line 266 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Assignment > ()); }
#line 2113 "src/parser.cpp"
    break;

  case 30: // pure: node_type_def
#line 267 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::TypeDef > ()); }
#line 2119 "src/parser.cpp"
    break;

  case 31: // pure: node_function_def
#line 268 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::FunDef > ()); }
#line 2125 "src/parser.cpp"
    break;

  case 32: // pure: node_return
#line 269 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Return > ()); }
#line 2131 "src/parser.cpp"
    break;

  case 33: // pure: node_if
#line 270 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::If > ()); }
#line 2137 "src/parser.cpp"
    break;

  case 34: // pure: node_for
#line 271 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::For > ()); }
#line 2143 "src/parser.cpp"
    break;

  case 35: // pure: node_while
#line 272 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::While > ()); }
#line 2149 "src/parser.cpp"
    break;

  case 36: // pure: node_when
#line 273 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::When > ()); }
#line 2155 "src/parser.cpp"
    break;

  case 37: // expr_or: node_or
#line 276 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Or > ()); }
#line 2161 "src/parser.cpp"
    break;

  case 38: // expr_or: expr_and
#line 277 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2167 "src/parser.cpp"
    break;

  case 39: // expr_and: node_and
#line 280 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::And > ()); }
#line 2173 "src/parser.cpp"
    break;

  case 40: // expr_and: expr_eq
#line 281 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2179 "src/parser.cpp"
    break;

  case 41: // expr_eq: node_eq
#line 284 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Eq > ()); }
#line 2185 "src/parser.cpp"
    break;

  case 42: // expr_eq: node_ne
#line 285 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Ne > ()); }
#line 2191 "src/parser.cpp"
    break;

  case 43: // expr_eq: expr_ord
#line 286 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2197 "src/parser.cpp"
    break;

  case 44: // expr_ord: node_ge
#line 289 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Ge > ()); }
#line 2203 "src/parser.cpp"
    break;

  case 45: // expr_ord: node_le
#line 290 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Le > ()); }
#line 2209 "src/parser.cpp"
    break;

  case 46: // expr_ord: node_gt
#line 291 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Gt > ()); }
#line 2215 "src/parser.cpp"
    break;

  case 47: // expr_ord: node_lt
#line 292 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Lt > ()); }
#line 2221 "src/parser.cpp"
    break;

  case 48: // expr_ord: expr_add
#line 293 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2227 "src/parser.cpp"
    break;

  case 49: // expr_add: node_add
#line 296 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Add > ()); }
#line 2233 "src/parser.cpp"
    break;

  case 50: // expr_add: node_sub
#line 297 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Sub > ()); }
#line 2239 "src/parser.cpp"
    break;

  case 51: // expr_add: expr_mul
#line 298 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2245 "src/parser.cpp"
    break;

  case 52: // expr_mul: node_mul
#line 301 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Mul > ()); }
#line 2251 "src/parser.cpp"
    break;

  case 53: // expr_mul: node_div
#line 302 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Div > ()); }
#line 2257 "src/parser.cpp"
    break;

  case 54: // expr_mul: node_mod
#line 303 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Mod > ()); }
#line 2263 "src/parser.cpp"
    break;

  case 55: // expr_mul: expr_pow
#line 304 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2269 "src/parser.cpp"
    break;

  case 56: // expr_pow: node_pow
#line 307 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Pow > ()); }
#line 2275 "src/parser.cpp"
    break;

  case 57: // expr_pow: expr_pre
#line 308 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2281 "src/parser.cpp"
    break;

  case 58: // expr_pre: node_minus
#line 311 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Minus > ()); }
#line 2287 "src/parser.cpp"
    break;

  case 59: // expr_pre: node_plus
#line 312 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Plus > ()); }
#line 2293 "src/parser.cpp"
    break;

  case 60: // expr_pre: node_not
#line 313 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Not > ()); }
#line 2299 "src/parser.cpp"
    break;

  case 61: // expr_pre: expr_post
#line 314 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2305 "src/parser.cpp"
    break;

  case 62: // expr_post: node_application
#line 317 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Application > ()); }
#line 2311 "src/parser.cpp"
    break;

  case 63: // expr_post: node_conversion
#line 318 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Conversion > ()); }
#line 2317 "src/parser.cpp"
    break;

  case 64: // expr_post: node_subscript
#line 319 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Subscript > ()); }
#line 2323 "src/parser.cpp"
    break;

  case 65: // expr_post: expr_atom
#line 320 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2329 "src/parser.cpp"
    break;

  case 66: // expr_atom: node_name
#line 323 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Name > ()); }
#line 2335 "src/parser.cpp"
    break;

  case 67: // expr_atom: node_bool
#line 324 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Bool > ()); }
#line 2341 "src/parser.cpp"
    break;

  case 68: // expr_atom: node_int
#line 325 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Int > ()); }
#line 2347 "src/parser.cpp"
    break;

  case 69: // expr_atom: node_float
#line 326 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Float > ()); }
#line 2353 "src/parser.cpp"
    break;

  case 70: // expr_atom: node_string
#line 327 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::String > ()); }
#line 2359 "src/parser.cpp"
    break;

  case 71: // expr_atom: node_block
#line 328 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Block > ()); }
#line 2365 "src/parser.cpp"
    break;

  case 72: // expr_atom: node_array
#line 329 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Array > ()); }
#line 2371 "src/parser.cpp"
    break;

  case 73: // expr_atom: paren_expr
#line 330 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2377 "src/parser.cpp"
    break;

  case 74: // expr_right: node_expr_if
#line 333 "gen/parser.y"
                  { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::ExprIf > ()); }
#line 2383 "src/parser.cpp"
    break;

  case 75: // expr_right: node_expr_for
#line 334 "gen/parser.y"
                  { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::ExprFor > ()); }
#line 2389 "src/parser.cpp"
    break;

  case 76: // expr_right: node_function
#line 335 "gen/parser.y"
                  { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Function > ()); }
#line 2395 "src/parser.cpp"
    break;

  case 77: // expr_assgn_target: expr_post
#line 338 "gen/parser.y"
              { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2401 "src/parser.cpp"
    break;

  case 78: // paren_type: OPAREN cat_type CPAREN
#line 343 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ());
    }
#line 2409 "src/parser.cpp"
    break;

  case 79: // paren_type: OPAREN type_list CPAREN
#line 346 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::category::Type > () = cynth::syn::node::TupleType{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::Type> > ())};
    }
#line 2417 "src/parser.cpp"
    break;

  case 80: // paren_type: OPAREN type_list COMMA CPAREN
#line 349 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::category::Type > () = cynth::syn::node::TupleType{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Type> > ())};
    }
#line 2425 "src/parser.cpp"
    break;

  case 81: // void_type: OPAREN CPAREN
#line 354 "gen/parser.y"
                  {
        yylhs.value.as < cynth::syn::category::Type > () = cynth::syn::node::TupleType{};
    }
#line 2433 "src/parser.cpp"
    break;

  case 82: // void_type: VOID
#line 357 "gen/parser.y"
         {
        yylhs.value.as < cynth::syn::category::Type > () = cynth::syn::node::TupleType{};
    }
#line 2441 "src/parser.cpp"
    break;

  case 83: // node_auto: AUTO
#line 362 "gen/parser.y"
         {
        yylhs.value.as < cynth::syn::node::Auto > () = {};
    }
#line 2449 "src/parser.cpp"
    break;

  case 84: // node_type_name: TYPENAME
#line 367 "gen/parser.y"
                   {
        yylhs.value.as < cynth::syn::node::TypeName > () = {YY_MOVE (yystack_[0].value.as < std::string > ())};
    }
#line 2457 "src/parser.cpp"
    break;

  case 85: // node_const_type: cat_type CONST
#line 372 "gen/parser.y"
                         {
        yylhs.value.as < cynth::syn::node::ConstType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ())};
    }
#line 2465 "src/parser.cpp"
    break;

  case 86: // node_in_type: cat_type IN
#line 377 "gen/parser.y"
                      {
        yylhs.value.as < cynth::syn::node::InType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ())};
    }
#line 2473 "src/parser.cpp"
    break;

  case 87: // node_out_type: cat_type OUT
#line 382 "gen/parser.y"
                       {
        yylhs.value.as < cynth::syn::node::OutType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ())};
    }
#line 2481 "src/parser.cpp"
    break;

  case 88: // node_function_type: cat_type paren_type
#line 387 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::syn::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 2489 "src/parser.cpp"
    break;

  case 89: // node_function_type: void_type paren_type
#line 390 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 2497 "src/parser.cpp"
    break;

  case 90: // node_function_type: cat_type void_type
#line 393 "gen/parser.y"
                                {
        yylhs.value.as < cynth::syn::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 2505 "src/parser.cpp"
    break;

  case 91: // node_function_type: void_type void_type
#line 396 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::syn::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 2513 "src/parser.cpp"
    break;

  case 92: // node_array_type: cat_type OBRACK cat_expression CBRACK
#line 401 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::syn::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .size = cynth::syn::category::Pattern{YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ())}};
    }
#line 2521 "src/parser.cpp"
    break;

  case 93: // node_array_type: cat_type OBRACK AUTO CBRACK
#line 404 "gen/parser.y"
                                      {
        yylhs.value.as < cynth::syn::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .size = esl::optional_component<cynth::syn::category::Pattern>{}};
    }
#line 2529 "src/parser.cpp"
    break;

  case 94: // node_array_type: cat_type OBRACK CBRACK
#line 407 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::syn::node::ArrayType > () = {.type = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Type > ()), .size = esl::optional_component<cynth::syn::category::Pattern>{}};
    }
#line 2537 "src/parser.cpp"
    break;

  case 95: // node_array_type: cat_type OBRACK cat_declaration CBRACK
#line 410 "gen/parser.y"
                                                            {
        yylhs.value.as < cynth::syn::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .size = cynth::syn::category::Pattern{YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ())}};
    }
#line 2545 "src/parser.cpp"
    break;

  case 96: // node_buffer_type: BUFFER OBRACK cat_expression CBRACK
#line 415 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::syn::node::BufferType > () = {.size = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ())};
    }
#line 2553 "src/parser.cpp"
    break;

  case 97: // paren_range_decl: OPAREN cat_range_decl CPAREN
#line 429 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::syn::category::RangeDeclaration > () = YY_MOVE (yystack_[1].value.as < cynth::syn::category::RangeDeclaration > ());
    }
#line 2561 "src/parser.cpp"
    break;

  case 98: // paren_range_decl: OPAREN range_decl_list CPAREN
#line 432 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::category::RangeDeclaration > () = cynth::syn::node::TupleRangeDecl{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::RangeDeclaration> > ())};
    }
#line 2569 "src/parser.cpp"
    break;

  case 99: // paren_range_decl: OPAREN range_decl_list COMMA CPAREN
#line 435 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::syn::category::RangeDeclaration > () = cynth::syn::node::TupleRangeDecl{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::RangeDeclaration> > ())};
    }
#line 2577 "src/parser.cpp"
    break;

  case 100: // paren_decl: OPAREN cat_declaration CPAREN
#line 440 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::syn::category::Declaration > () = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ());
    }
#line 2585 "src/parser.cpp"
    break;

  case 101: // paren_decl: OPAREN decl_list CPAREN
#line 443 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::category::Declaration > () = cynth::syn::node::TupleDecl{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::Declaration> > ())};
    }
#line 2593 "src/parser.cpp"
    break;

  case 102: // paren_decl: OPAREN decl_list COMMA CPAREN
#line 446 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::category::Declaration > () = cynth::syn::node::TupleDecl{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Declaration> > ())};
    }
#line 2601 "src/parser.cpp"
    break;

  case 103: // void_decl: OPAREN CPAREN
#line 451 "gen/parser.y"
                  {
        yylhs.value.as < cynth::syn::category::Declaration > () = cynth::syn::node::TupleDecl{};
    }
#line 2609 "src/parser.cpp"
    break;

  case 104: // node_declaration: cat_type node_name
#line 456 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Declaration > () = {.name = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Name > ()), .type = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ())};
    }
#line 2617 "src/parser.cpp"
    break;

  case 105: // node_range_decl: cat_declaration IN cat_expression
#line 461 "gen/parser.y"
                                                   {
        yylhs.value.as < cynth::syn::node::RangeDecl > () = {.declaration = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Declaration > ()), .range = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2625 "src/parser.cpp"
    break;

  case 106: // node_range_to: cat_expression TO cat_expression
#line 468 "gen/parser.y"
                                               {
        yylhs.value.as < cynth::syn::node::RangeTo > () = {.from = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), .to = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2633 "src/parser.cpp"
    break;

  case 107: // node_range_to_by: cat_expression TO cat_expression BY cat_expression
#line 473 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::syn::node::RangeToBy > () = {.from = YY_MOVE (yystack_[4].value.as < cynth::syn::category::Expression > ()), .to = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), .by = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2641 "src/parser.cpp"
    break;

  case 108: // node_spread: ELIP cat_expression
#line 478 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Spread > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2649 "src/parser.cpp"
    break;

  case 109: // paren_expr: OPAREN cat_expression CPAREN
#line 485 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ());
    }
#line 2657 "src/parser.cpp"
    break;

  case 110: // paren_expr: OPAREN expr_list CPAREN
#line 488 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::category::Expression > () = cynth::syn::node::Tuple{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::Expression> > ())};
    }
#line 2665 "src/parser.cpp"
    break;

  case 111: // paren_expr: OPAREN expr_list COMMA CPAREN
#line 491 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::category::Expression > () = cynth::syn::node::Tuple{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Expression> > ())};
    }
#line 2673 "src/parser.cpp"
    break;

  case 112: // void: OPAREN CPAREN
#line 496 "gen/parser.y"
                  {
        yylhs.value.as < cynth::syn::category::Expression > () = cynth::syn::node::Tuple{};
    }
#line 2681 "src/parser.cpp"
    break;

  case 113: // node_name: NAME
#line 501 "gen/parser.y"
               {
        yylhs.value.as < cynth::syn::node::Name > () = {YY_MOVE (yystack_[0].value.as < std::string > ())};
    }
#line 2689 "src/parser.cpp"
    break;

  case 114: // node_block: OBRACE CBRACE
#line 506 "gen/parser.y"
                  {
        yylhs.value.as < cynth::syn::node::Block > () = {};
    }
#line 2697 "src/parser.cpp"
    break;

  case 115: // node_block: OBRACE stmt_list CBRACE
#line 509 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::node::Block > () = {YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::Statement> > ())};
    }
#line 2705 "src/parser.cpp"
    break;

  case 116: // node_block: OBRACE stmt_list SEMI CBRACE
#line 512 "gen/parser.y"
                                       {
        yylhs.value.as < cynth::syn::node::Block > () = {YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Statement> > ())};
    }
#line 2713 "src/parser.cpp"
    break;

  case 117: // node_bool: TRUE
#line 519 "gen/parser.y"
         {
        yylhs.value.as < cynth::syn::node::Bool > () = {true};
    }
#line 2721 "src/parser.cpp"
    break;

  case 118: // node_bool: FALSE
#line 522 "gen/parser.y"
          {
        yylhs.value.as < cynth::syn::node::Bool > () = {false};
    }
#line 2729 "src/parser.cpp"
    break;

  case 119: // node_int: INT
#line 527 "gen/parser.y"
        {
        yylhs.value.as < cynth::syn::node::Int > () = {esl::stoi<cynth::sem::Integral>(YY_MOVE (yystack_[0].value.as < std::string > ()))}; // TODO: The sem::Integral type should be obtainable from syn::node::Int
    }
#line 2737 "src/parser.cpp"
    break;

  case 120: // node_float: FLOAT
#line 532 "gen/parser.y"
          {
        yylhs.value.as < cynth::syn::node::Float > () = {std::stof(YY_MOVE (yystack_[0].value.as < std::string > ()))};
    }
#line 2745 "src/parser.cpp"
    break;

  case 121: // node_string: STRING
#line 537 "gen/parser.y"
           {
        yylhs.value.as < cynth::syn::node::String > () = {esl::trim(YY_MOVE (yystack_[0].value.as < std::string > ()))};
    }
#line 2753 "src/parser.cpp"
    break;

  case 122: // node_function: cat_type FN paren_decl cat_expression
#line 542 "gen/parser.y"
                                                         {
        yylhs.value.as < cynth::syn::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2761 "src/parser.cpp"
    break;

  case 123: // node_function: void_type FN paren_decl cat_expression
#line 545 "gen/parser.y"
                                                          {
        yylhs.value.as < cynth::syn::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2769 "src/parser.cpp"
    break;

  case 124: // node_function: cat_type FN void_decl cat_expression
#line 548 "gen/parser.y"
                                                        {
        yylhs.value.as < cynth::syn::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2777 "src/parser.cpp"
    break;

  case 125: // node_function: void_type FN void_decl cat_expression
#line 551 "gen/parser.y"
                                                         {
        yylhs.value.as < cynth::syn::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2785 "src/parser.cpp"
    break;

  case 126: // node_array: OBRACK CBRACK
#line 556 "gen/parser.y"
                  {
        yylhs.value.as < cynth::syn::node::Array > () = {};
    }
#line 2793 "src/parser.cpp"
    break;

  case 127: // node_array: OBRACK array_elem_list CBRACK
#line 559 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::node::Array > () = {YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::ArrayElement> > ())};
    }
#line 2801 "src/parser.cpp"
    break;

  case 128: // node_array: OBRACK array_elem_list SEMI CBRACK
#line 562 "gen/parser.y"
                                             {
        yylhs.value.as < cynth::syn::node::Array > () = {YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::ArrayElement> > ())};
    }
#line 2809 "src/parser.cpp"
    break;

  case 129: // node_or: expr_or OR expr_and
#line 569 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::node::Or > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2817 "src/parser.cpp"
    break;

  case 130: // node_and: expr_and AND expr_eq
#line 574 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::And > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2825 "src/parser.cpp"
    break;

  case 131: // node_eq: expr_eq EQ expr_ord
#line 579 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::node::Eq > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2833 "src/parser.cpp"
    break;

  case 132: // node_ne: expr_eq NE expr_ord
#line 584 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::node::Ne > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2841 "src/parser.cpp"
    break;

  case 133: // node_ge: expr_ord GE expr_add
#line 589 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Ge > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2849 "src/parser.cpp"
    break;

  case 134: // node_le: expr_ord LE expr_add
#line 594 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Le > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2857 "src/parser.cpp"
    break;

  case 135: // node_gt: expr_ord GT expr_add
#line 599 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Gt > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2865 "src/parser.cpp"
    break;

  case 136: // node_lt: expr_ord LT expr_add
#line 604 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Lt > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2873 "src/parser.cpp"
    break;

  case 137: // node_add: expr_add ADD expr_mul
#line 609 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Add > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2881 "src/parser.cpp"
    break;

  case 138: // node_sub: expr_add SUB expr_mul
#line 614 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Sub > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2889 "src/parser.cpp"
    break;

  case 139: // node_mul: expr_mul MUL expr_pow
#line 619 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Mul > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2897 "src/parser.cpp"
    break;

  case 140: // node_div: expr_mul DIV expr_pow
#line 624 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Div > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2905 "src/parser.cpp"
    break;

  case 141: // node_mod: expr_mul MOD expr_pow
#line 629 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Mod > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2913 "src/parser.cpp"
    break;

  case 142: // node_pow: expr_pre POW expr_pow
#line 634 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Pow > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2921 "src/parser.cpp"
    break;

  case 143: // node_minus: SUB expr_pre
#line 639 "gen/parser.y"
                      {
        yylhs.value.as < cynth::syn::node::Minus > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2929 "src/parser.cpp"
    break;

  case 144: // node_plus: ADD expr_pre
#line 644 "gen/parser.y"
                      {
        yylhs.value.as < cynth::syn::node::Plus > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2937 "src/parser.cpp"
    break;

  case 145: // node_not: NOT expr_pre
#line 649 "gen/parser.y"
                      {
        yylhs.value.as < cynth::syn::node::Not > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2945 "src/parser.cpp"
    break;

  case 146: // node_application: expr_post paren_expr
#line 654 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::syn::node::Application > () = {.function = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ()), .arguments = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2953 "src/parser.cpp"
    break;

  case 147: // node_application: expr_post void
#line 657 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::node::Application > () = {.function = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ()), .arguments = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2961 "src/parser.cpp"
    break;

  case 148: // node_conversion: cat_type paren_expr
#line 662 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::node::Conversion > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ()), .argument = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2969 "src/parser.cpp"
    break;

  case 149: // node_subscript: expr_post OBRACK array_elem_list CBRACK
#line 667 "gen/parser.y"
                                                                 {
        yylhs.value.as < cynth::syn::node::Subscript > () = {.container = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ()), .location = YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::ArrayElement> > ())};
    }
#line 2977 "src/parser.cpp"
    break;

  case 150: // node_subscript: expr_post OBRACK CBRACK
#line 670 "gen/parser.y"
                                       {
        yylhs.value.as < cynth::syn::node::Subscript > () = {.container = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), .location = {}};
    }
#line 2985 "src/parser.cpp"
    break;

  case 151: // node_expr_if: IF paren_expr cat_expression ELSE cat_expression
#line 675 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::syn::node::ExprIf > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ()), .positiveBranch = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), .negativeBranch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2993 "src/parser.cpp"
    break;

  case 152: // node_expr_for: FOR paren_range_decl cat_expression
#line 680 "gen/parser.y"
                                                    {
        yylhs.value.as < cynth::syn::node::ExprFor > () = {.declarations = YY_MOVE (yystack_[1].value.as < cynth::syn::category::RangeDeclaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3001 "src/parser.cpp"
    break;

  case 153: // node_definition: cat_declaration ASSGN cat_expression
#line 687 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::syn::node::Definition > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Declaration > ()), .value = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3009 "src/parser.cpp"
    break;

  case 154: // node_assignment: expr_assgn_target ASSGN cat_expression
#line 692 "gen/parser.y"
                                                        {
        yylhs.value.as < cynth::syn::node::Assignment > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), .value = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3017 "src/parser.cpp"
    break;

  case 155: // node_type_def: TYPE node_type_name ASSGN cat_type
#line 697 "gen/parser.y"
                                                     {
        yylhs.value.as < cynth::syn::node::TypeDef > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::syn::node::TypeName > ()), .type = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 3025 "src/parser.cpp"
    break;

  case 156: // node_function_def: cat_type node_name paren_decl cat_expression
#line 702 "gen/parser.y"
                                                                      {
        yylhs.value.as < cynth::syn::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::syn::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3033 "src/parser.cpp"
    break;

  case 157: // node_function_def: void_type node_name paren_decl cat_expression
#line 705 "gen/parser.y"
                                                                       {
        yylhs.value.as < cynth::syn::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::syn::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3041 "src/parser.cpp"
    break;

  case 158: // node_function_def: cat_type node_name void_decl cat_expression
#line 708 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::syn::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::syn::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3049 "src/parser.cpp"
    break;

  case 159: // node_function_def: void_type node_name void_decl cat_expression
#line 711 "gen/parser.y"
                                                                      {
        yylhs.value.as < cynth::syn::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::syn::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3057 "src/parser.cpp"
    break;

  case 160: // node_return: RETURN cat_expression
#line 716 "gen/parser.y"
                               {
        yylhs.value.as < cynth::syn::node::Return > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3065 "src/parser.cpp"
    break;

  case 161: // node_return: RETURN void
#line 719 "gen/parser.y"
                     {
        yylhs.value.as < cynth::syn::node::Return > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3073 "src/parser.cpp"
    break;

  case 162: // node_return: RETURN
#line 722 "gen/parser.y"
           {
        yylhs.value.as < cynth::syn::node::Return > () = {cynth::syn::category::Expression{cynth::syn::node::Tuple{}}};
    }
#line 3081 "src/parser.cpp"
    break;

  case 163: // node_if: IF paren_expr pure ELSE pure
#line 727 "gen/parser.y"
                                                 {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ()), .positiveBranch = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Statement > ()), .negativeBranch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3089 "src/parser.cpp"
    break;

  case 164: // node_if: IF paren_expr pure SEMI ELSE pure
#line 730 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[4].value.as < cynth::syn::category::Expression > ()), .positiveBranch = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Statement > ()), .negativeBranch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3097 "src/parser.cpp"
    break;

  case 165: // node_if: IF paren_expr cat_expression ELSE pure
#line 733 "gen/parser.y"
                                                           {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ()), .positiveBranch = cynth::syn::category::Statement{YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ())}, .negativeBranch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3105 "src/parser.cpp"
    break;

  case 166: // node_if: IF paren_expr cat_expression SEMI ELSE pure
#line 736 "gen/parser.y"
                                                                {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[4].value.as < cynth::syn::category::Expression > ()), .positiveBranch = cynth::syn::category::Statement{YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ())}, .negativeBranch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3113 "src/parser.cpp"
    break;

  case 167: // node_if: IF paren_expr pure ELSE cat_expression
#line 739 "gen/parser.y"
                                                           {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ()), .positiveBranch = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Statement > ()), .negativeBranch = cynth::syn::category::Statement{YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())}};
    }
#line 3121 "src/parser.cpp"
    break;

  case 168: // node_if: IF paren_expr pure SEMI ELSE cat_expression
#line 742 "gen/parser.y"
                                                                {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[4].value.as < cynth::syn::category::Expression > ()), .positiveBranch = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Statement > ()), .negativeBranch = cynth::syn::category::Statement{YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())}};
    }
#line 3129 "src/parser.cpp"
    break;

  case 169: // node_when: WHEN paren_expr cat_statement
#line 747 "gen/parser.y"
                                             {
        yylhs.value.as < cynth::syn::node::When > () = {.condition = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ()), .branch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3137 "src/parser.cpp"
    break;

  case 170: // node_for: FOR paren_range_decl pure
#line 752 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::syn::node::For > () = {.declarations = YY_MOVE (yystack_[1].value.as < cynth::syn::category::RangeDeclaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3145 "src/parser.cpp"
    break;

  case 171: // node_while: WHILE paren_expr cat_statement
#line 757 "gen/parser.y"
                                               {
        yylhs.value.as < cynth::syn::node::While > () = {.condition = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3153 "src/parser.cpp"
    break;

  case 172: // array_elem_list: cat_array_elem
#line 764 "gen/parser.y"
                          {
        yylhs.value.as < esl::component_vector<cynth::syn::category::ArrayElement> > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::ArrayElement > ())};
    }
#line 3161 "src/parser.cpp"
    break;

  case 173: // array_elem_list: array_elem_list COMMA cat_array_elem
#line 767 "gen/parser.y"
                                                     {
        yylhs.value.as < esl::component_vector<cynth::syn::category::ArrayElement> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::ArrayElement > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::ArrayElement> > ()));
    }
#line 3169 "src/parser.cpp"
    break;

  case 174: // stmt_list: cat_statement
#line 772 "gen/parser.y"
                         {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Statement> > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3177 "src/parser.cpp"
    break;

  case 175: // stmt_list: stmt_list SEMI cat_statement
#line 775 "gen/parser.y"
                                             {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Statement> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Statement> > ()));
    }
#line 3185 "src/parser.cpp"
    break;

  case 176: // type_list: cat_type COMMA cat_type
#line 780 "gen/parser.y"
                                           {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Type> > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Type > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 3193 "src/parser.cpp"
    break;

  case 177: // type_list: type_list COMMA cat_type
#line 783 "gen/parser.y"
                                         {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Type> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Type> > ()));
    }
#line 3201 "src/parser.cpp"
    break;

  case 178: // expr_list: cat_expression COMMA cat_expression
#line 788 "gen/parser.y"
                                                       {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Expression> > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3209 "src/parser.cpp"
    break;

  case 179: // expr_list: expr_list COMMA cat_expression
#line 791 "gen/parser.y"
                                               {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Expression> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Expression> > ()));
    }
#line 3217 "src/parser.cpp"
    break;

  case 180: // decl_list: cat_declaration COMMA cat_declaration
#line 796 "gen/parser.y"
                                                         {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Declaration> > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Declaration > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Declaration > ())};
    }
#line 3225 "src/parser.cpp"
    break;

  case 181: // decl_list: decl_list COMMA cat_declaration
#line 799 "gen/parser.y"
                                                {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Declaration> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::Declaration > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Declaration> > ()));
    }
#line 3233 "src/parser.cpp"
    break;

  case 182: // range_decl_list: cat_range_decl COMMA cat_range_decl
#line 804 "gen/parser.y"
                                                       {
        yylhs.value.as < esl::component_vector<cynth::syn::category::RangeDeclaration> > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::RangeDeclaration > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::RangeDeclaration > ())};
    }
#line 3241 "src/parser.cpp"
    break;

  case 183: // range_decl_list: range_decl_list COMMA cat_range_decl
#line 807 "gen/parser.y"
                                                     {
        yylhs.value.as < esl::component_vector<cynth::syn::category::RangeDeclaration> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::RangeDeclaration > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::RangeDeclaration> > ()));
    }
#line 3249 "src/parser.cpp"
    break;


#line 3253 "src/parser.cpp"

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





  const short parser::yypact_ninf_ = -140;

  const signed char parser::yytable_ninf_ = -82;

  const short
  parser::yypact_[] =
  {
      47,  -140,  -140,  -140,  -140,  -140,  -140,    10,    10,    42,
      10,    31,    48,  1068,  -140,  -140,  -140,   581,   628,   748,
    -140,  1148,  1148,  1148,    93,   407,    82,  -140,  -140,  -140,
      81,    98,    71,   182,   151,   197,  -140,    87,    12,  -140,
    -140,   123,  -140,    -1,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,   152,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,   155,  1108,   708,   708,   163,   708,
     708,   159,  1108,    10,    42,   828,   444,  -140,   135,    56,
    -140,  -140,   243,   -13,    14,  -140,    85,    96,   108,  -140,
      34,  1108,   868,  -140,  -140,   180,  -140,  -140,  -140,   -14,
     745,  -140,   173,  -140,  -140,  -140,   187,  -140,  -140,  -140,
     908,  -140,  -140,  -140,   187,  1108,  1148,  1148,  1148,  1148,
    1148,  1148,  1148,  1148,  1148,  1148,  1148,  1148,  1148,  1148,
     948,   788,  -140,  -140,  1108,   187,    57,  -140,  -140,   187,
     708,    -3,     7,  -140,    75,   176,   201,   139,  -140,  -140,
     142,  -140,  -140,  -140,   418,   214,  1108,  1108,    59,   509,
     418,  -140,  -140,   501,  -140,  1108,  -140,   107,  -140,   156,
    -140,   988,  -140,   668,  -140,  -140,  1108,   216,  1028,  -140,
     353,  1108,  1108,   217,  -140,   407,   219,   224,  1108,  1108,
    -140,    98,    71,   182,   182,   151,   151,   151,   151,   197,
     197,  -140,  -140,  -140,  -140,  -140,  -140,     4,  -140,  1108,
    1108,   535,  1108,  1108,  -140,   708,   234,   708,   252,   110,
      45,  1108,   163,  -140,   400,  -140,   785,  -140,   256,   785,
     456,  -140,  -140,  -140,   785,  -140,  -140,  -140,  -140,  -140,
     250,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  1188,  -140,
    -140,   708,  -140,  -140,  -140,  -140,  1108,  1108,    10,    42,
     209,  -140,   135,    11,  -140,  -140,  -140,   708,  1188,    92,
    1188
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     5,   113,    84,   119,   120,   121,     0,     0,     0,
       0,     0,     0,   162,   117,   118,    83,     0,     0,     0,
      82,     0,     0,     0,     0,     0,     0,    26,   174,    25,
      23,    38,    40,    43,    48,    51,    55,    57,    61,    65,
      24,     0,    22,     0,    14,    15,    19,    20,    21,    16,
      17,    18,     7,    27,    73,    66,    71,    67,    68,    69,
      70,    76,    72,    37,    39,    41,    42,    44,    45,    46,
      47,    49,    50,    52,    53,    54,    56,    59,    58,    60,
      62,    63,    64,    74,    75,    28,    29,    31,    30,    32,
      33,    36,    34,    35,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   160,    61,     0,
     161,    81,     0,     0,     0,     6,     0,     0,     0,   114,
       0,     0,     0,   126,   172,    13,    10,    11,    12,     0,
       0,   144,     0,   143,   145,     1,     0,    85,    86,    87,
       0,    88,    90,   148,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   146,   147,     0,     0,     0,    89,    91,     0,
       4,     0,     0,   169,     0,     0,     0,     0,     9,     8,
       0,   152,   170,   171,     0,     0,     0,     0,   112,     0,
       0,    78,   104,     0,   100,     0,   109,     0,    79,     0,
     101,     0,   110,     0,   115,   108,     0,     0,     0,   127,
       0,     0,     0,    83,    94,     0,     0,     0,     0,     0,
     153,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   112,   150,     0,   154,     0,
       0,     0,     0,     0,   175,     0,     0,     0,     0,     0,
       0,     0,     0,    97,     0,    98,   155,    96,     0,   176,
       0,   180,   178,    80,   177,   102,   181,   111,   179,   116,
     106,   128,   173,   103,   122,   124,    93,    95,    92,   156,
     158,   149,   123,   125,   157,   159,   151,   165,     0,   167,
     163,     0,   105,   182,    99,   183,     0,     0,     0,     0,
       0,   166,    77,     0,   168,   164,   107,     0,     0,     0,
       0
  };

  const short
  parser::yypgoto_[] =
  {
    -140,  -140,   196,   165,   -32,    62,   306,   -96,   -84,  -140,
     133,   143,    91,   134,   120,   171,   299,    24,  -140,  -140,
    -140,   366,     0,  -140,   271,  -140,  -140,  -140,  -140,  -140,
    -140,  -133,    -2,  -139,   309,  -140,  -140,  -140,  -140,   273,
     276,     6,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,   138,  -140,   284
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,    24,   106,    26,   177,   124,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,   108,    39,    40,
      41,    42,   109,    44,    45,    46,    47,    48,    49,    50,
      51,    52,   178,   212,    53,   179,   126,   127,   128,    54,
     163,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
     116,   117,   180,   129,   118,    94
  };

  const short
  parser::yytable_[] =
  {
      43,   173,     2,   211,   183,   219,   245,    99,   207,   208,
     193,   218,   172,   165,     2,   182,   247,   194,    43,   246,
     209,   132,   132,   132,    38,   142,   240,   208,   166,   248,
     243,   144,   239,   -77,    20,     3,   242,   195,   281,    95,
     166,   160,    38,   168,   196,   161,    20,    -2,     1,   169,
       2,     3,     4,     5,     6,     7,   203,     8,     9,    10,
      11,     3,    12,    13,    14,    15,   204,    16,   193,   251,
     165,    98,    12,   -81,   244,   194,    17,    16,    18,     3,
      19,   102,    20,    21,    22,   166,   166,   111,   -81,    23,
      12,    20,    20,   135,   -81,    16,    43,    43,   132,    43,
      43,   310,   187,   145,   174,   111,   142,   244,   197,   168,
      20,     3,   142,     2,   246,   198,   148,   149,   192,   199,
      38,    38,    12,    38,    38,   146,   200,    16,   159,   137,
     142,   201,   168,   190,   138,   139,   166,   263,   202,   166,
     191,   147,    20,   140,   164,    20,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
       3,   287,   252,   290,   160,   254,   132,     3,   161,   253,
      43,    12,   255,    -6,   132,   142,    16,   170,    12,     2,
     184,   192,   113,    16,   132,   260,   265,   154,   155,   142,
     132,    20,   174,   132,    38,   137,    25,   132,    20,   132,
     138,   139,   166,    43,   301,   166,   206,   305,    20,   140,
     132,    20,     2,   112,    25,   142,   210,   130,   130,   130,
     293,   192,   295,   172,   182,   251,   287,    38,   137,   150,
     151,   152,   153,   138,   139,   156,   157,   158,   122,   223,
     224,   142,   140,   288,    20,    43,     2,    43,   257,   142,
     271,   276,   132,   277,   132,   192,   142,   136,   278,   142,
     132,   291,   137,   176,   142,   296,   190,   138,   139,    38,
     272,    38,   122,   191,   229,   230,   140,   297,    20,   221,
      96,    97,   101,   100,   225,   226,   227,   228,   303,   110,
     222,    43,    25,    25,   175,    25,    25,   308,   143,   237,
     142,   189,   120,   168,     0,   216,   144,    43,   303,   169,
     303,   162,   302,     0,     0,    38,     0,     0,   189,   107,
     131,   133,   134,   114,     0,   125,   115,   231,   232,   233,
     234,    38,   302,     0,   302,     0,   215,     0,     0,   250,
       0,     0,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,     0,     3,   261,     0,
       0,     0,   241,     0,   266,     0,    25,     0,    12,     0,
     249,     0,     0,    16,     0,   113,   186,     0,     0,   143,
     256,   162,   260,   273,     0,   143,   259,     0,    20,   175,
       0,   141,     0,   264,     0,   175,     0,     0,     0,    25,
       0,   114,   171,   143,     3,   181,   175,   115,   185,   167,
       2,   114,     0,     0,     0,    12,     0,   176,     0,   176,
      16,   136,     3,     0,     0,   113,   137,   205,   114,   174,
     294,   138,   139,    12,     0,    20,   122,     0,    16,     0,
     140,    25,    20,    25,     0,     0,   217,   166,   175,   115,
     175,   220,     0,    20,     0,     0,   249,     0,   136,     0,
       3,     0,   143,   137,     0,     0,   114,   125,   138,   139,
     238,    12,   141,   122,     0,   167,    16,   140,   141,    20,
       0,     0,     0,   115,   300,   260,   111,    25,   143,     0,
       0,    20,   258,   181,     0,     0,   141,     0,   167,     0,
       0,   262,   115,    25,   300,     3,   300,   268,   115,     0,
       0,     0,   270,     0,   125,     0,    12,   274,   275,   115,
       0,    16,     0,   136,   279,   280,     0,     0,   137,     0,
     260,     0,   190,   138,   139,     0,    20,     0,   122,   191,
       0,   141,   140,     0,    20,   282,   283,     0,   284,   285,
       0,   286,     0,   289,   137,   141,     0,   292,   190,   138,
     139,   115,     0,   115,   166,   191,     0,     0,   140,   115,
      20,   307,     0,   143,     0,   162,     0,     0,     0,     0,
       0,   141,     0,     0,     2,     3,     4,     5,     6,   103,
       0,     0,   104,     0,     0,     0,    12,   304,    14,    15,
       0,    16,   286,   306,     0,     0,     0,   141,     0,     0,
      17,   111,    18,   309,    19,   141,    20,    21,    22,     0,
       0,     0,   141,    23,     0,   141,     0,     0,     0,     0,
     141,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,     0,    12,    13,    14,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,    17,     0,    18,
     119,    19,     0,    20,    21,    22,   141,     0,     0,   167,
      23,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,     0,    12,    13,    14,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,    17,     0,    18,
     269,    19,     0,    20,    21,    22,     0,     0,     0,     0,
      23,     2,     3,     4,     5,     6,     7,     0,     8,     9,
      10,    11,     0,    12,    13,    14,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,    17,     0,    18,
       0,    19,     0,    20,    21,    22,     0,     0,     0,     0,
      23,     2,     3,     4,     5,     6,   103,     0,     0,   104,
       0,     0,     0,    12,   137,    14,    15,     0,    16,   138,
     139,     0,     0,     0,   122,     0,   121,   122,   140,    18,
      20,    19,   123,    20,    21,    22,     0,     0,     0,     0,
      23,     2,     3,     4,     5,     6,   103,     0,     0,   104,
       0,     0,     0,    12,   137,    14,    15,     0,    16,   138,
     139,     0,     0,     0,   166,     0,   121,   122,   140,    18,
      20,    19,   236,    20,    21,    22,     0,     0,     0,     0,
      23,     2,     3,     4,     5,     6,   103,     0,     0,   104,
       0,     0,     0,    12,     0,    14,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,   122,   188,    18,
       0,    19,     0,    20,    21,    22,     0,     0,     0,     0,
      23,     2,     3,     4,     5,     6,   103,     0,     0,   104,
       0,     0,     0,    12,     0,    14,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,   122,   111,    18,
       0,    19,     0,    20,    21,    22,     0,     0,     0,     0,
      23,     2,     3,     4,     5,     6,   103,     0,     0,   104,
       0,     0,     0,    12,     0,    14,    15,     0,   213,     0,
       0,     0,     0,     0,     0,     0,     0,    17,     0,    18,
       0,    19,   214,    20,    21,    22,     0,     0,     0,     0,
      23,     2,     3,     4,     5,     6,   103,     0,     0,   104,
       0,     0,     0,    12,     0,    14,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,   122,   235,    18,
       0,    19,     0,    20,    21,    22,     0,     0,     0,     0,
      23,     2,     3,     4,     5,     6,   103,     0,     0,   104,
       0,     0,     0,    12,     0,    14,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,   122,   267,    18,
       0,    19,     0,    20,    21,    22,     0,     0,     0,     0,
      23,     2,     3,     4,     5,     6,   103,     0,     0,   104,
       0,     0,     0,    12,     0,    14,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,   121,   122,     0,    18,
       0,    19,     0,    20,    21,    22,     0,     0,     0,     0,
      23,     2,     3,     4,     5,     6,   103,     0,     0,   104,
       0,     0,     0,    12,     0,    14,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,   105,     0,    18,
       0,    19,     0,    20,    21,    22,     0,     0,     0,     0,
      23,     2,     3,     4,     5,     6,   103,     0,     0,   104,
       0,     0,     0,    12,     0,    14,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,   122,     0,    18,
       0,    19,     0,    20,    21,    22,     0,     0,     0,     0,
      23,     2,     3,     4,     5,     6,     0,     0,     0,     0,
       0,     0,     0,    12,     0,    14,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,   122,     0,    18,
       0,    19,     0,    20,    21,    22,     0,     0,     0,     0,
      23,     2,     3,     4,     5,     6,   298,     0,     8,   299,
      10,    11,     0,    12,    13,    14,    15,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,    17,     0,    18,
       0,    19,     0,    20
  };

  const short
  parser::yycheck_[] =
  {
       0,    97,     3,   136,   100,   144,     9,     9,    22,    23,
      23,   144,    96,    14,     3,    99,     9,    30,    18,    22,
      34,    21,    22,    23,     0,    25,   165,    23,    29,    22,
     169,    25,   165,    21,    35,     4,   169,    23,    34,    29,
      29,    29,    18,    43,    30,    33,    35,     0,     1,    43,
       3,     4,     5,     6,     7,     8,    22,    10,    11,    12,
      13,     4,    15,    16,    17,    18,    32,    20,    23,    24,
      14,    29,    15,    14,   170,    30,    29,    20,    31,     4,
      33,    33,    35,    36,    37,    29,    29,    30,    29,    42,
      15,    35,    35,     0,    35,    20,    96,    97,    98,    99,
     100,     9,   104,    21,    29,    30,   106,   203,    23,   109,
      35,     4,   112,     3,    22,    30,    45,    46,   112,    23,
      96,    97,    15,    99,   100,    44,    30,    20,    41,    19,
     130,    23,   132,    23,    24,    25,    29,    30,    30,    29,
      30,    43,    35,    33,    21,    35,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
       4,   245,    23,   247,    29,    23,   166,     4,    33,    30,
     170,    15,    30,    21,   174,   175,    20,    22,    15,     3,
      21,   175,    17,    20,   184,    29,    30,    36,    37,   189,
     190,    35,    29,   193,   170,    19,     0,   197,    35,   199,
      24,    25,    29,   203,   288,    29,    26,   291,    35,    33,
     210,    35,     3,    17,    18,   215,    29,    21,    22,    23,
     252,   215,   254,   307,   308,    24,   310,   203,    19,    47,
      48,    49,    50,    24,    25,    38,    39,    40,    29,   148,
     149,   241,    33,     9,    35,   245,     3,   247,    34,   249,
      34,    34,   252,    34,   254,   249,   256,    14,    34,   259,
     260,     9,    19,    98,   264,     9,    23,    24,    25,   245,
     208,   247,    29,    30,   154,   155,    33,    27,    35,   146,
       7,     8,    11,    10,   150,   151,   152,   153,   288,    13,
     147,   291,    96,    97,    98,    99,   100,   299,    25,   161,
     300,   105,    18,   303,    -1,   140,   300,   307,   308,   303,
     310,    38,   288,    -1,    -1,   291,    -1,    -1,   122,    13,
      21,    22,    23,    17,    -1,    19,    17,   156,   157,   158,
     159,   307,   308,    -1,   310,    -1,   140,    -1,    -1,   174,
      -1,    -1,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,    -1,     4,   193,    -1,
      -1,    -1,   166,    -1,   199,    -1,   170,    -1,    15,    -1,
     174,    -1,    -1,    20,    -1,   210,   103,    -1,    -1,   106,
     184,   108,    29,    30,    -1,   112,   190,    -1,    35,   193,
      -1,    25,    -1,   197,    -1,   199,    -1,    -1,    -1,   203,
      -1,    95,    96,   130,     4,    99,   210,    98,   102,    43,
       3,   105,    -1,    -1,    -1,    15,    -1,   252,    -1,   254,
      20,    14,     4,    -1,    -1,   260,    19,   121,   122,    29,
      30,    24,    25,    15,    -1,    35,    29,    -1,    20,    -1,
      33,   245,    35,   247,    -1,    -1,   140,    29,   252,   140,
     254,   145,    -1,    35,    -1,    -1,   260,    -1,    14,    -1,
       4,    -1,   189,    19,    -1,    -1,   160,   161,    24,    25,
     164,    15,   106,    29,    -1,   109,    20,    33,   112,    35,
      -1,    -1,    -1,   174,   288,    29,    30,   291,   215,    -1,
      -1,    35,   186,   187,    -1,    -1,   130,    -1,   132,    -1,
      -1,   195,   193,   307,   308,     4,   310,   201,   199,    -1,
      -1,    -1,   206,    -1,   208,    -1,    15,   211,   212,   210,
      -1,    20,    -1,    14,   218,   219,    -1,    -1,    19,    -1,
      29,    -1,    23,    24,    25,    -1,    35,    -1,    29,    30,
      -1,   175,    33,    -1,    35,   239,   240,    -1,   242,   243,
      -1,   245,    -1,   247,    19,   189,    -1,   251,    23,    24,
      25,   252,    -1,   254,    29,    30,    -1,    -1,    33,   260,
      35,   298,    -1,   300,    -1,   302,    -1,    -1,    -1,    -1,
      -1,   215,    -1,    -1,     3,     4,     5,     6,     7,     8,
      -1,    -1,    11,    -1,    -1,    -1,    15,   291,    17,    18,
      -1,    20,   296,   297,    -1,    -1,    -1,   241,    -1,    -1,
      29,    30,    31,   307,    33,   249,    35,    36,    37,    -1,
      -1,    -1,   256,    42,    -1,   259,    -1,    -1,    -1,    -1,
     264,     3,     4,     5,     6,     7,     8,    -1,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,
      32,    33,    -1,    35,    36,    37,   300,    -1,    -1,   303,
      42,     3,     4,     5,     6,     7,     8,    -1,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,
      32,    33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,     3,     4,     5,     6,     7,     8,    -1,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,
      -1,    33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    15,    19,    17,    18,    -1,    20,    24,
      25,    -1,    -1,    -1,    29,    -1,    28,    29,    33,    31,
      35,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    15,    19,    17,    18,    -1,    20,    24,
      25,    -1,    -1,    -1,    29,    -1,    28,    29,    33,    31,
      35,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      -1,    33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      -1,    33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,
      -1,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      -1,    33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      -1,    33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    31,
      -1,    33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,
      -1,    33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,     3,     4,     5,     6,     7,     8,    -1,    -1,    11,
      -1,    -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,
      -1,    33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,
      -1,    33,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,     3,     4,     5,     6,     7,     8,    -1,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,
      -1,    33,    -1,    35
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     1,     3,     4,     5,     6,     7,     8,    10,    11,
      12,    13,    15,    16,    17,    18,    20,    29,    31,    33,
      35,    36,    37,    42,    53,    54,    55,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    86,    91,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   137,    29,    91,    91,    29,    84,
      91,    76,    33,     8,    11,    29,    54,    58,    69,    74,
      92,    30,    54,    55,    58,    86,   132,   133,   136,    32,
     137,    28,    29,    34,    57,    58,    88,    89,    90,   135,
      54,    68,    74,    68,    68,     0,    14,    19,    24,    25,
      33,    73,    74,    91,    93,    21,    44,    43,    45,    46,
      47,    48,    49,    50,    36,    37,    38,    39,    40,    41,
      29,    33,    91,    92,    21,    14,    29,    73,    74,    93,
      22,    58,    60,    59,    29,    54,    55,    56,    84,    87,
     134,    58,    60,    59,    21,    58,    91,    84,    30,    54,
      23,    30,    93,    23,    30,    23,    30,    23,    30,    23,
      30,    23,    30,    22,    32,    58,    26,    22,    23,    34,
      29,    83,    85,    20,    34,    54,    55,    58,    83,    85,
      58,    62,    63,    64,    64,    65,    65,    65,    65,    66,
      66,    67,    67,    67,    67,    30,    34,   135,    58,    83,
      85,    54,    83,    85,    59,     9,    22,     9,    22,    54,
      55,    24,    23,    30,    23,    30,    54,    34,    58,    54,
      29,    55,    58,    30,    54,    30,    55,    30,    58,    32,
      58,    34,    57,    30,    58,    58,    34,    34,    34,    58,
      58,    34,    58,    58,    58,    58,    58,    60,     9,    58,
      60,     9,    58,    56,    30,    56,     9,    27,     8,    11,
      54,    60,    69,    74,    58,    60,    58,    91,    84,    58,
       9
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    52,    53,    53,    53,    53,    55,    55,    56,    56,
      57,    57,    57,    57,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    58,    58,    59,    59,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    61,    61,    62,
      62,    63,    63,    63,    64,    64,    64,    64,    64,    65,
      65,    65,    66,    66,    66,    66,    67,    67,    68,    68,
      68,    68,    69,    69,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    71,    72,    73,    73,
      73,    74,    74,    75,    76,    77,    78,    79,    80,    80,
      80,    80,    81,    81,    81,    81,    82,    84,    84,    84,
      83,    83,    83,    85,    86,    87,    88,    89,    90,    91,
      91,    91,    92,    93,    94,    94,    94,    95,    95,    96,
      97,    98,    99,    99,    99,    99,   100,   100,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   116,   115,   117,   118,   118,   119,   120,
     120,   121,   122,   123,   124,   126,   125,   125,   125,   125,
     127,   127,   127,   128,   128,   128,   128,   128,   128,   129,
     130,   131,   135,   135,   137,   137,   132,   132,   136,   136,
     133,   133,   134,   134
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
       2,     2,     4,     4,     3,     4,     4,     3,     3,     4,
       3,     3,     4,     2,     2,     3,     3,     5,     2,     3,
       3,     4,     2,     1,     2,     3,     4,     1,     1,     1,
       1,     1,     4,     4,     4,     4,     2,     3,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     2,     2,     4,
       3,     5,     3,     3,     3,     4,     4,     4,     4,     4,
       2,     2,     1,     5,     6,     5,     6,     5,     6,     3,
       3,     3,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3
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
       0,   206,   206,   210,   214,   218,   226,   227,   230,   231,
     234,   235,   236,   237,   240,   241,   242,   243,   244,   248,
     249,   250,   251,   254,   255,   258,   259,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   276,   277,   280,
     281,   284,   285,   286,   289,   290,   291,   292,   293,   296,
     297,   298,   301,   302,   303,   304,   307,   308,   311,   312,
     313,   314,   317,   318,   319,   320,   323,   324,   325,   326,
     327,   328,   329,   330,   333,   334,   335,   338,   343,   346,
     349,   354,   357,   362,   367,   372,   377,   382,   387,   390,
     393,   396,   401,   404,   407,   410,   415,   429,   432,   435,
     440,   443,   446,   451,   456,   461,   468,   473,   478,   485,
     488,   491,   496,   501,   506,   509,   512,   519,   522,   527,
     532,   537,   542,   545,   548,   551,   556,   559,   562,   569,
     574,   579,   584,   589,   594,   599,   604,   609,   614,   619,
     624,   629,   634,   639,   644,   649,   654,   657,   662,   667,
     670,   675,   680,   687,   692,   697,   702,   705,   708,   711,
     716,   719,   722,   727,   730,   733,   736,   739,   742,   747,
     752,   757,   764,   767,   772,   775,   780,   783,   788,   791,
     796,   799,   804,   807
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
#line 3976 "src/parser.cpp"

#line 811 "gen/parser.y"


void yy::parser::error (std::string const & msg) {
    // TODO: There's a syntax error every time for some reason.
    std::cerr << "parser error: " << msg << '\n';
}
