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
      case symbol_kind::S_expr_or_right: // expr_or_right
      case symbol_kind::S_expr_and_right: // expr_and_right
      case symbol_kind::S_expr_eq_right: // expr_eq_right
      case symbol_kind::S_expr_ord_right: // expr_ord_right
      case symbol_kind::S_expr_add_right: // expr_add_right
      case symbol_kind::S_expr_mul_right: // expr_mul_right
      case symbol_kind::S_expr_pow_right: // expr_pow_right
      case symbol_kind::S_expr_pre_right: // expr_pre_right
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
      case symbol_kind::S_node_add_right: // node_add_right
        value.YY_MOVE_OR_COPY< cynth::syn::node::Add > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_and: // node_and
      case symbol_kind::S_node_and_right: // node_and_right
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
      case symbol_kind::S_node_div_right: // node_div_right
        value.YY_MOVE_OR_COPY< cynth::syn::node::Div > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_eq: // node_eq
      case symbol_kind::S_node_eq_right: // node_eq_right
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
      case symbol_kind::S_node_ge_right: // node_ge_right
        value.YY_MOVE_OR_COPY< cynth::syn::node::Ge > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_gt: // node_gt
      case symbol_kind::S_node_gt_right: // node_gt_right
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
      case symbol_kind::S_node_le_right: // node_le_right
        value.YY_MOVE_OR_COPY< cynth::syn::node::Le > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_lt: // node_lt
      case symbol_kind::S_node_lt_right: // node_lt_right
        value.YY_MOVE_OR_COPY< cynth::syn::node::Lt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_minus: // node_minus
      case symbol_kind::S_node_minus_right: // node_minus_right
        value.YY_MOVE_OR_COPY< cynth::syn::node::Minus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_mod: // node_mod
      case symbol_kind::S_node_mod_right: // node_mod_right
        value.YY_MOVE_OR_COPY< cynth::syn::node::Mod > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_mul: // node_mul
      case symbol_kind::S_node_mul_right: // node_mul_right
        value.YY_MOVE_OR_COPY< cynth::syn::node::Mul > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_name: // node_name
        value.YY_MOVE_OR_COPY< cynth::syn::node::Name > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_ne: // node_ne
      case symbol_kind::S_node_ne_right: // node_ne_right
        value.YY_MOVE_OR_COPY< cynth::syn::node::Ne > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_not: // node_not
      case symbol_kind::S_node_not_right: // node_not_right
        value.YY_MOVE_OR_COPY< cynth::syn::node::Not > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_or: // node_or
      case symbol_kind::S_node_or_right: // node_or_right
        value.YY_MOVE_OR_COPY< cynth::syn::node::Or > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_out_type: // node_out_type
        value.YY_MOVE_OR_COPY< cynth::syn::node::OutType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_plus: // node_plus
      case symbol_kind::S_node_plus_right: // node_plus_right
        value.YY_MOVE_OR_COPY< cynth::syn::node::Plus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_pow: // node_pow
      case symbol_kind::S_node_pow_right: // node_pow_right
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
      case symbol_kind::S_node_sub_right: // node_sub_right
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
      case symbol_kind::S_ILLEGAL: // ILLEGAL
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
      case symbol_kind::S_expr_or_right: // expr_or_right
      case symbol_kind::S_expr_and_right: // expr_and_right
      case symbol_kind::S_expr_eq_right: // expr_eq_right
      case symbol_kind::S_expr_ord_right: // expr_ord_right
      case symbol_kind::S_expr_add_right: // expr_add_right
      case symbol_kind::S_expr_mul_right: // expr_mul_right
      case symbol_kind::S_expr_pow_right: // expr_pow_right
      case symbol_kind::S_expr_pre_right: // expr_pre_right
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
      case symbol_kind::S_node_add_right: // node_add_right
        value.move< cynth::syn::node::Add > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_and: // node_and
      case symbol_kind::S_node_and_right: // node_and_right
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
      case symbol_kind::S_node_div_right: // node_div_right
        value.move< cynth::syn::node::Div > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_eq: // node_eq
      case symbol_kind::S_node_eq_right: // node_eq_right
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
      case symbol_kind::S_node_ge_right: // node_ge_right
        value.move< cynth::syn::node::Ge > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_gt: // node_gt
      case symbol_kind::S_node_gt_right: // node_gt_right
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
      case symbol_kind::S_node_le_right: // node_le_right
        value.move< cynth::syn::node::Le > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_lt: // node_lt
      case symbol_kind::S_node_lt_right: // node_lt_right
        value.move< cynth::syn::node::Lt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_minus: // node_minus
      case symbol_kind::S_node_minus_right: // node_minus_right
        value.move< cynth::syn::node::Minus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_mod: // node_mod
      case symbol_kind::S_node_mod_right: // node_mod_right
        value.move< cynth::syn::node::Mod > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_mul: // node_mul
      case symbol_kind::S_node_mul_right: // node_mul_right
        value.move< cynth::syn::node::Mul > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_name: // node_name
        value.move< cynth::syn::node::Name > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_ne: // node_ne
      case symbol_kind::S_node_ne_right: // node_ne_right
        value.move< cynth::syn::node::Ne > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_not: // node_not
      case symbol_kind::S_node_not_right: // node_not_right
        value.move< cynth::syn::node::Not > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_or: // node_or
      case symbol_kind::S_node_or_right: // node_or_right
        value.move< cynth::syn::node::Or > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_out_type: // node_out_type
        value.move< cynth::syn::node::OutType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_plus: // node_plus
      case symbol_kind::S_node_plus_right: // node_plus_right
        value.move< cynth::syn::node::Plus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_pow: // node_pow
      case symbol_kind::S_node_pow_right: // node_pow_right
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
      case symbol_kind::S_node_sub_right: // node_sub_right
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
      case symbol_kind::S_ILLEGAL: // ILLEGAL
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
      case symbol_kind::S_expr_or_right: // expr_or_right
      case symbol_kind::S_expr_and_right: // expr_and_right
      case symbol_kind::S_expr_eq_right: // expr_eq_right
      case symbol_kind::S_expr_ord_right: // expr_ord_right
      case symbol_kind::S_expr_add_right: // expr_add_right
      case symbol_kind::S_expr_mul_right: // expr_mul_right
      case symbol_kind::S_expr_pow_right: // expr_pow_right
      case symbol_kind::S_expr_pre_right: // expr_pre_right
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
      case symbol_kind::S_node_add_right: // node_add_right
        value.copy< cynth::syn::node::Add > (that.value);
        break;

      case symbol_kind::S_node_and: // node_and
      case symbol_kind::S_node_and_right: // node_and_right
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
      case symbol_kind::S_node_div_right: // node_div_right
        value.copy< cynth::syn::node::Div > (that.value);
        break;

      case symbol_kind::S_node_eq: // node_eq
      case symbol_kind::S_node_eq_right: // node_eq_right
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
      case symbol_kind::S_node_ge_right: // node_ge_right
        value.copy< cynth::syn::node::Ge > (that.value);
        break;

      case symbol_kind::S_node_gt: // node_gt
      case symbol_kind::S_node_gt_right: // node_gt_right
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
      case symbol_kind::S_node_le_right: // node_le_right
        value.copy< cynth::syn::node::Le > (that.value);
        break;

      case symbol_kind::S_node_lt: // node_lt
      case symbol_kind::S_node_lt_right: // node_lt_right
        value.copy< cynth::syn::node::Lt > (that.value);
        break;

      case symbol_kind::S_node_minus: // node_minus
      case symbol_kind::S_node_minus_right: // node_minus_right
        value.copy< cynth::syn::node::Minus > (that.value);
        break;

      case symbol_kind::S_node_mod: // node_mod
      case symbol_kind::S_node_mod_right: // node_mod_right
        value.copy< cynth::syn::node::Mod > (that.value);
        break;

      case symbol_kind::S_node_mul: // node_mul
      case symbol_kind::S_node_mul_right: // node_mul_right
        value.copy< cynth::syn::node::Mul > (that.value);
        break;

      case symbol_kind::S_node_name: // node_name
        value.copy< cynth::syn::node::Name > (that.value);
        break;

      case symbol_kind::S_node_ne: // node_ne
      case symbol_kind::S_node_ne_right: // node_ne_right
        value.copy< cynth::syn::node::Ne > (that.value);
        break;

      case symbol_kind::S_node_not: // node_not
      case symbol_kind::S_node_not_right: // node_not_right
        value.copy< cynth::syn::node::Not > (that.value);
        break;

      case symbol_kind::S_node_or: // node_or
      case symbol_kind::S_node_or_right: // node_or_right
        value.copy< cynth::syn::node::Or > (that.value);
        break;

      case symbol_kind::S_node_out_type: // node_out_type
        value.copy< cynth::syn::node::OutType > (that.value);
        break;

      case symbol_kind::S_node_plus: // node_plus
      case symbol_kind::S_node_plus_right: // node_plus_right
        value.copy< cynth::syn::node::Plus > (that.value);
        break;

      case symbol_kind::S_node_pow: // node_pow
      case symbol_kind::S_node_pow_right: // node_pow_right
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
      case symbol_kind::S_node_sub_right: // node_sub_right
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
      case symbol_kind::S_ILLEGAL: // ILLEGAL
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
      case symbol_kind::S_expr_or_right: // expr_or_right
      case symbol_kind::S_expr_and_right: // expr_and_right
      case symbol_kind::S_expr_eq_right: // expr_eq_right
      case symbol_kind::S_expr_ord_right: // expr_ord_right
      case symbol_kind::S_expr_add_right: // expr_add_right
      case symbol_kind::S_expr_mul_right: // expr_mul_right
      case symbol_kind::S_expr_pow_right: // expr_pow_right
      case symbol_kind::S_expr_pre_right: // expr_pre_right
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
      case symbol_kind::S_node_add_right: // node_add_right
        value.move< cynth::syn::node::Add > (that.value);
        break;

      case symbol_kind::S_node_and: // node_and
      case symbol_kind::S_node_and_right: // node_and_right
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
      case symbol_kind::S_node_div_right: // node_div_right
        value.move< cynth::syn::node::Div > (that.value);
        break;

      case symbol_kind::S_node_eq: // node_eq
      case symbol_kind::S_node_eq_right: // node_eq_right
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
      case symbol_kind::S_node_ge_right: // node_ge_right
        value.move< cynth::syn::node::Ge > (that.value);
        break;

      case symbol_kind::S_node_gt: // node_gt
      case symbol_kind::S_node_gt_right: // node_gt_right
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
      case symbol_kind::S_node_le_right: // node_le_right
        value.move< cynth::syn::node::Le > (that.value);
        break;

      case symbol_kind::S_node_lt: // node_lt
      case symbol_kind::S_node_lt_right: // node_lt_right
        value.move< cynth::syn::node::Lt > (that.value);
        break;

      case symbol_kind::S_node_minus: // node_minus
      case symbol_kind::S_node_minus_right: // node_minus_right
        value.move< cynth::syn::node::Minus > (that.value);
        break;

      case symbol_kind::S_node_mod: // node_mod
      case symbol_kind::S_node_mod_right: // node_mod_right
        value.move< cynth::syn::node::Mod > (that.value);
        break;

      case symbol_kind::S_node_mul: // node_mul
      case symbol_kind::S_node_mul_right: // node_mul_right
        value.move< cynth::syn::node::Mul > (that.value);
        break;

      case symbol_kind::S_node_name: // node_name
        value.move< cynth::syn::node::Name > (that.value);
        break;

      case symbol_kind::S_node_ne: // node_ne
      case symbol_kind::S_node_ne_right: // node_ne_right
        value.move< cynth::syn::node::Ne > (that.value);
        break;

      case symbol_kind::S_node_not: // node_not
      case symbol_kind::S_node_not_right: // node_not_right
        value.move< cynth::syn::node::Not > (that.value);
        break;

      case symbol_kind::S_node_or: // node_or
      case symbol_kind::S_node_or_right: // node_or_right
        value.move< cynth::syn::node::Or > (that.value);
        break;

      case symbol_kind::S_node_out_type: // node_out_type
        value.move< cynth::syn::node::OutType > (that.value);
        break;

      case symbol_kind::S_node_plus: // node_plus
      case symbol_kind::S_node_plus_right: // node_plus_right
        value.move< cynth::syn::node::Plus > (that.value);
        break;

      case symbol_kind::S_node_pow: // node_pow
      case symbol_kind::S_node_pow_right: // node_pow_right
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
      case symbol_kind::S_node_sub_right: // node_sub_right
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
      case symbol_kind::S_ILLEGAL: // ILLEGAL
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
      case symbol_kind::S_expr_or_right: // expr_or_right
      case symbol_kind::S_expr_and_right: // expr_and_right
      case symbol_kind::S_expr_eq_right: // expr_eq_right
      case symbol_kind::S_expr_ord_right: // expr_ord_right
      case symbol_kind::S_expr_add_right: // expr_add_right
      case symbol_kind::S_expr_mul_right: // expr_mul_right
      case symbol_kind::S_expr_pow_right: // expr_pow_right
      case symbol_kind::S_expr_pre_right: // expr_pre_right
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
      case symbol_kind::S_node_add_right: // node_add_right
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_and: // node_and
      case symbol_kind::S_node_and_right: // node_and_right
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
      case symbol_kind::S_node_div_right: // node_div_right
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_eq: // node_eq
      case symbol_kind::S_node_eq_right: // node_eq_right
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
      case symbol_kind::S_node_ge_right: // node_ge_right
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_gt: // node_gt
      case symbol_kind::S_node_gt_right: // node_gt_right
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
      case symbol_kind::S_node_le_right: // node_le_right
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_lt: // node_lt
      case symbol_kind::S_node_lt_right: // node_lt_right
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_minus: // node_minus
      case symbol_kind::S_node_minus_right: // node_minus_right
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_mod: // node_mod
      case symbol_kind::S_node_mod_right: // node_mod_right
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_mul: // node_mul
      case symbol_kind::S_node_mul_right: // node_mul_right
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_name: // node_name
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_ne: // node_ne
      case symbol_kind::S_node_ne_right: // node_ne_right
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_not: // node_not
      case symbol_kind::S_node_not_right: // node_not_right
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_or: // node_or
      case symbol_kind::S_node_or_right: // node_or_right
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_out_type: // node_out_type
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_plus: // node_plus
      case symbol_kind::S_node_plus_right: // node_plus_right
        yylhs.value.emplace< int > (); // Modified.
        break;

      case symbol_kind::S_node_pow: // node_pow
      case symbol_kind::S_node_pow_right: // node_pow_right
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
      case symbol_kind::S_node_sub_right: // node_sub_right
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
      case symbol_kind::S_ILLEGAL: // ILLEGAL
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
#line 231 "gen/parser.y"
           {
        result.first  = {};
        result.second = true;
    }
#line 2072 "src/parser.cpp"
    break;

  case 3: // start: stmt_list
#line 235 "gen/parser.y"
                    {
        result.first  = {YY_MOVE (yystack_[0].value.as < esl::component_vector<cynth::syn::category::Statement> > ())};
        result.second = true;
    }
#line 2081 "src/parser.cpp"
    break;

  case 4: // start: stmt_list SEMI
#line 239 "gen/parser.y"
                         {
        result.first  = {YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::Statement> > ())};
        result.second = true;
    }
#line 2090 "src/parser.cpp"
    break;

  case 5: // start: ILLEGAL
#line 243 "gen/parser.y"
                   {
        result.first  = {};
        result.second = true;
        std::cout << "invalid token:" << YY_MOVE (yystack_[0].value.as < std::string > ()) << '\n';
    }
#line 2100 "src/parser.cpp"
    break;

  case 6: // start: error
#line 248 "gen/parser.y"
          {
        result.first  = {};
        result.second = false;
    }
#line 2109 "src/parser.cpp"
    break;

  case 7: // cat_declaration: node_declaration
#line 256 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Declaration > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Declaration > ()); }
#line 2115 "src/parser.cpp"
    break;

  case 8: // cat_declaration: paren_decl
#line 257 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Declaration > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Declaration > ()); }
#line 2121 "src/parser.cpp"
    break;

  case 9: // cat_range_decl: node_range_decl
#line 260 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::RangeDeclaration > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::RangeDecl > ()); }
#line 2127 "src/parser.cpp"
    break;

  case 10: // cat_range_decl: paren_range_decl
#line 261 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::RangeDeclaration > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::RangeDeclaration > ()); }
#line 2133 "src/parser.cpp"
    break;

  case 11: // cat_array_elem: node_range_to
#line 264 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::RangeTo > ()); }
#line 2139 "src/parser.cpp"
    break;

  case 12: // cat_array_elem: node_range_to_by
#line 265 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::RangeToBy > ()); }
#line 2145 "src/parser.cpp"
    break;

  case 13: // cat_array_elem: node_spread
#line 266 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Spread > ()); }
#line 2151 "src/parser.cpp"
    break;

  case 14: // cat_array_elem: cat_expression
#line 267 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::ArrayElement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2157 "src/parser.cpp"
    break;

  case 15: // cat_type: node_auto
#line 270 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Auto > ()); }
#line 2163 "src/parser.cpp"
    break;

  case 16: // cat_type: node_type_name
#line 271 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::TypeName > ()); }
#line 2169 "src/parser.cpp"
    break;

  case 17: // cat_type: node_function_type
#line 272 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::FunctionType > ()); }
#line 2175 "src/parser.cpp"
    break;

  case 18: // cat_type: node_array_type
#line 273 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::ArrayType > ()); }
#line 2181 "src/parser.cpp"
    break;

  case 19: // cat_type: node_buffer_type
#line 274 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::BufferType > ()); }
#line 2187 "src/parser.cpp"
    break;

  case 20: // cat_type: node_const_type
#line 278 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::ConstType > ()); }
#line 2193 "src/parser.cpp"
    break;

  case 21: // cat_type: node_in_type
#line 279 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::InType > ()); }
#line 2199 "src/parser.cpp"
    break;

  case 22: // cat_type: node_out_type
#line 280 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::OutType > ()); }
#line 2205 "src/parser.cpp"
    break;

  case 23: // cat_type: paren_type
#line 281 "gen/parser.y"
                       { yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ()); }
#line 2211 "src/parser.cpp"
    break;

  case 24: // cat_expression: expr_or
#line 284 "gen/parser.y"
                  { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2217 "src/parser.cpp"
    break;

  case 25: // cat_expression: expr_or_right
#line 285 "gen/parser.y"
                  { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2223 "src/parser.cpp"
    break;

  case 26: // cat_statement: pure
#line 288 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ()); }
#line 2229 "src/parser.cpp"
    break;

  case 27: // cat_statement: cat_expression
#line 289 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2235 "src/parser.cpp"
    break;

  case 28: // pure: cat_declaration
#line 294 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Declaration > ()); }
#line 2241 "src/parser.cpp"
    break;

  case 29: // pure: node_definition
#line 295 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Definition > ()); }
#line 2247 "src/parser.cpp"
    break;

  case 30: // pure: node_assignment
#line 296 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Assignment > ()); }
#line 2253 "src/parser.cpp"
    break;

  case 31: // pure: node_type_def
#line 297 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::TypeDef > ()); }
#line 2259 "src/parser.cpp"
    break;

  case 32: // pure: node_function_def
#line 298 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::FunDef > ()); }
#line 2265 "src/parser.cpp"
    break;

  case 33: // pure: node_return
#line 299 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Return > ()); }
#line 2271 "src/parser.cpp"
    break;

  case 34: // pure: node_if
#line 300 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::If > ()); }
#line 2277 "src/parser.cpp"
    break;

  case 35: // pure: node_for
#line 301 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::For > ()); }
#line 2283 "src/parser.cpp"
    break;

  case 36: // pure: node_while
#line 302 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::While > ()); }
#line 2289 "src/parser.cpp"
    break;

  case 37: // pure: node_when
#line 303 "gen/parser.y"
                      { yylhs.value.as < cynth::syn::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::When > ()); }
#line 2295 "src/parser.cpp"
    break;

  case 38: // expr_or: node_or
#line 306 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Or > ()); }
#line 2301 "src/parser.cpp"
    break;

  case 39: // expr_or: expr_and
#line 307 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2307 "src/parser.cpp"
    break;

  case 40: // expr_or_right: node_or_right
#line 310 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Or > ()); }
#line 2313 "src/parser.cpp"
    break;

  case 41: // expr_or_right: expr_and_right
#line 311 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2319 "src/parser.cpp"
    break;

  case 42: // expr_and: node_and
#line 314 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::And > ()); }
#line 2325 "src/parser.cpp"
    break;

  case 43: // expr_and: expr_eq
#line 315 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2331 "src/parser.cpp"
    break;

  case 44: // expr_and_right: node_and_right
#line 318 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::And > ()); }
#line 2337 "src/parser.cpp"
    break;

  case 45: // expr_and_right: expr_eq_right
#line 319 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2343 "src/parser.cpp"
    break;

  case 46: // expr_eq: node_eq
#line 322 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Eq > ()); }
#line 2349 "src/parser.cpp"
    break;

  case 47: // expr_eq: node_ne
#line 323 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Ne > ()); }
#line 2355 "src/parser.cpp"
    break;

  case 48: // expr_eq: expr_ord
#line 324 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2361 "src/parser.cpp"
    break;

  case 49: // expr_eq_right: node_eq_right
#line 327 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Eq > ()); }
#line 2367 "src/parser.cpp"
    break;

  case 50: // expr_eq_right: node_ne_right
#line 328 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Ne > ()); }
#line 2373 "src/parser.cpp"
    break;

  case 51: // expr_eq_right: expr_ord_right
#line 329 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2379 "src/parser.cpp"
    break;

  case 52: // expr_ord: node_ge
#line 332 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Ge > ()); }
#line 2385 "src/parser.cpp"
    break;

  case 53: // expr_ord: node_le
#line 333 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Le > ()); }
#line 2391 "src/parser.cpp"
    break;

  case 54: // expr_ord: node_gt
#line 334 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Gt > ()); }
#line 2397 "src/parser.cpp"
    break;

  case 55: // expr_ord: node_lt
#line 335 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Lt > ()); }
#line 2403 "src/parser.cpp"
    break;

  case 56: // expr_ord: expr_add
#line 336 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2409 "src/parser.cpp"
    break;

  case 57: // expr_ord_right: node_ge_right
#line 339 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Ge > ()); }
#line 2415 "src/parser.cpp"
    break;

  case 58: // expr_ord_right: node_le_right
#line 340 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Le > ()); }
#line 2421 "src/parser.cpp"
    break;

  case 59: // expr_ord_right: node_gt_right
#line 341 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Gt > ()); }
#line 2427 "src/parser.cpp"
    break;

  case 60: // expr_ord_right: node_lt_right
#line 342 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Lt > ()); }
#line 2433 "src/parser.cpp"
    break;

  case 61: // expr_ord_right: expr_add_right
#line 343 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2439 "src/parser.cpp"
    break;

  case 62: // expr_add: node_add
#line 346 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Add > ()); }
#line 2445 "src/parser.cpp"
    break;

  case 63: // expr_add: node_sub
#line 347 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Sub > ()); }
#line 2451 "src/parser.cpp"
    break;

  case 64: // expr_add: expr_mul
#line 348 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2457 "src/parser.cpp"
    break;

  case 65: // expr_add_right: node_add_right
#line 351 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Add > ()); }
#line 2463 "src/parser.cpp"
    break;

  case 66: // expr_add_right: node_sub_right
#line 352 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Sub > ()); }
#line 2469 "src/parser.cpp"
    break;

  case 67: // expr_add_right: expr_mul_right
#line 353 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2475 "src/parser.cpp"
    break;

  case 68: // expr_mul: node_mul
#line 356 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Mul > ()); }
#line 2481 "src/parser.cpp"
    break;

  case 69: // expr_mul: node_div
#line 357 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Div > ()); }
#line 2487 "src/parser.cpp"
    break;

  case 70: // expr_mul: node_mod
#line 358 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Mod > ()); }
#line 2493 "src/parser.cpp"
    break;

  case 71: // expr_mul: expr_pow
#line 359 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2499 "src/parser.cpp"
    break;

  case 72: // expr_mul_right: node_mul_right
#line 362 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Mul > ()); }
#line 2505 "src/parser.cpp"
    break;

  case 73: // expr_mul_right: node_div_right
#line 363 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Div > ()); }
#line 2511 "src/parser.cpp"
    break;

  case 74: // expr_mul_right: node_mod_right
#line 364 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Mod > ()); }
#line 2517 "src/parser.cpp"
    break;

  case 75: // expr_mul_right: expr_pow_right
#line 365 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2523 "src/parser.cpp"
    break;

  case 76: // expr_pow: node_pow
#line 368 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Pow > ()); }
#line 2529 "src/parser.cpp"
    break;

  case 77: // expr_pow: expr_pre
#line 369 "gen/parser.y"
             { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2535 "src/parser.cpp"
    break;

  case 78: // expr_pow_right: node_pow_right
#line 372 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Pow > ()); }
#line 2541 "src/parser.cpp"
    break;

  case 79: // expr_pow_right: expr_pre_right
#line 373 "gen/parser.y"
                   { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2547 "src/parser.cpp"
    break;

  case 80: // expr_pre: node_minus
#line 376 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Minus > ()); }
#line 2553 "src/parser.cpp"
    break;

  case 81: // expr_pre: node_plus
#line 377 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Plus > ()); }
#line 2559 "src/parser.cpp"
    break;

  case 82: // expr_pre: node_not
#line 378 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Not > ()); }
#line 2565 "src/parser.cpp"
    break;

  case 83: // expr_pre: expr_post
#line 379 "gen/parser.y"
               { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2571 "src/parser.cpp"
    break;

  case 84: // expr_pre_right: node_minus_right
#line 382 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Minus > ()); }
#line 2577 "src/parser.cpp"
    break;

  case 85: // expr_pre_right: node_plus_right
#line 383 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Plus > ()); }
#line 2583 "src/parser.cpp"
    break;

  case 86: // expr_pre_right: node_not_right
#line 384 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Not > ()); }
#line 2589 "src/parser.cpp"
    break;

  case 87: // expr_pre_right: expr_right
#line 385 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2595 "src/parser.cpp"
    break;

  case 88: // expr_post: node_application
#line 388 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Application > ()); }
#line 2601 "src/parser.cpp"
    break;

  case 89: // expr_post: node_conversion
#line 389 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Conversion > ()); }
#line 2607 "src/parser.cpp"
    break;

  case 90: // expr_post: node_subscript
#line 390 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Subscript > ()); }
#line 2613 "src/parser.cpp"
    break;

  case 91: // expr_post: expr_atom
#line 391 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2619 "src/parser.cpp"
    break;

  case 92: // expr_atom: node_name
#line 394 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Name > ()); }
#line 2625 "src/parser.cpp"
    break;

  case 93: // expr_atom: node_bool
#line 395 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Bool > ()); }
#line 2631 "src/parser.cpp"
    break;

  case 94: // expr_atom: node_int
#line 396 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Int > ()); }
#line 2637 "src/parser.cpp"
    break;

  case 95: // expr_atom: node_float
#line 397 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Float > ()); }
#line 2643 "src/parser.cpp"
    break;

  case 96: // expr_atom: node_string
#line 398 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::String > ()); }
#line 2649 "src/parser.cpp"
    break;

  case 97: // expr_atom: node_block
#line 399 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Block > ()); }
#line 2655 "src/parser.cpp"
    break;

  case 98: // expr_atom: node_array
#line 400 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Array > ()); }
#line 2661 "src/parser.cpp"
    break;

  case 99: // expr_atom: paren_expr
#line 401 "gen/parser.y"
                { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2667 "src/parser.cpp"
    break;

  case 100: // expr_right: node_expr_if
#line 404 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::ExprIf > ()); }
#line 2673 "src/parser.cpp"
    break;

  case 101: // expr_right: node_expr_for
#line 405 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::ExprFor > ()); }
#line 2679 "src/parser.cpp"
    break;

  case 102: // expr_right: node_function
#line 406 "gen/parser.y"
                     { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Function > ()); }
#line 2685 "src/parser.cpp"
    break;

  case 103: // expr_assgn_target: expr_post
#line 409 "gen/parser.y"
              { yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()); }
#line 2691 "src/parser.cpp"
    break;

  case 104: // paren_type: OPAREN cat_type CPAREN
#line 414 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::category::Type > () = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ());
    }
#line 2699 "src/parser.cpp"
    break;

  case 105: // paren_type: OPAREN type_list CPAREN
#line 417 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::category::Type > () = cynth::syn::node::TupleType{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::Type> > ())};
    }
#line 2707 "src/parser.cpp"
    break;

  case 106: // paren_type: OPAREN type_list COMMA CPAREN
#line 420 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::category::Type > () = cynth::syn::node::TupleType{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Type> > ())};
    }
#line 2715 "src/parser.cpp"
    break;

  case 107: // void_type: OPAREN CPAREN
#line 425 "gen/parser.y"
                  {
        yylhs.value.as < cynth::syn::category::Type > () = cynth::syn::node::TupleType{};
    }
#line 2723 "src/parser.cpp"
    break;

  case 108: // void_type: VOID
#line 428 "gen/parser.y"
         {
        yylhs.value.as < cynth::syn::category::Type > () = cynth::syn::node::TupleType{};
    }
#line 2731 "src/parser.cpp"
    break;

  case 109: // node_auto: AUTO
#line 433 "gen/parser.y"
         {
        yylhs.value.as < cynth::syn::node::Auto > () = {};
    }
#line 2739 "src/parser.cpp"
    break;

  case 110: // node_type_name: TYPENAME
#line 438 "gen/parser.y"
                   {
        yylhs.value.as < cynth::syn::node::TypeName > () = {YY_MOVE (yystack_[0].value.as < std::string > ())};
    }
#line 2747 "src/parser.cpp"
    break;

  case 111: // node_const_type: cat_type CONST
#line 443 "gen/parser.y"
                         {
        yylhs.value.as < cynth::syn::node::ConstType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ())};
    }
#line 2755 "src/parser.cpp"
    break;

  case 112: // node_in_type: cat_type IN
#line 448 "gen/parser.y"
                      {
        yylhs.value.as < cynth::syn::node::InType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ())};
    }
#line 2763 "src/parser.cpp"
    break;

  case 113: // node_out_type: cat_type OUT
#line 453 "gen/parser.y"
                       {
        yylhs.value.as < cynth::syn::node::OutType > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ())};
    }
#line 2771 "src/parser.cpp"
    break;

  case 114: // node_function_type: cat_type paren_type
#line 458 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::syn::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 2779 "src/parser.cpp"
    break;

  case 115: // node_function_type: void_type paren_type
#line 461 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 2787 "src/parser.cpp"
    break;

  case 116: // node_function_type: cat_type void_type
#line 464 "gen/parser.y"
                                {
        yylhs.value.as < cynth::syn::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 2795 "src/parser.cpp"
    break;

  case 117: // node_function_type: void_type void_type
#line 467 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::syn::node::FunctionType > () = {.output = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 2803 "src/parser.cpp"
    break;

  case 118: // node_array_type: cat_type OBRACK cat_expression CBRACK
#line 472 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::syn::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .size = cynth::syn::category::Pattern{YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ())}};
    }
#line 2811 "src/parser.cpp"
    break;

  case 119: // node_array_type: cat_type OBRACK AUTO CBRACK
#line 475 "gen/parser.y"
                                      {
        yylhs.value.as < cynth::syn::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .size = esl::optional_component<cynth::syn::category::Pattern>{}};
    }
#line 2819 "src/parser.cpp"
    break;

  case 120: // node_array_type: cat_type OBRACK CBRACK
#line 478 "gen/parser.y"
                                 {
        yylhs.value.as < cynth::syn::node::ArrayType > () = {.type = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Type > ()), .size = esl::optional_component<cynth::syn::category::Pattern>{}};
    }
#line 2827 "src/parser.cpp"
    break;

  case 121: // node_array_type: cat_type OBRACK cat_declaration CBRACK
#line 481 "gen/parser.y"
                                                            {
        yylhs.value.as < cynth::syn::node::ArrayType > () = {.type = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .size = cynth::syn::category::Pattern{YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ())}};
    }
#line 2835 "src/parser.cpp"
    break;

  case 122: // node_buffer_type: BUFFER OBRACK cat_expression CBRACK
#line 486 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::syn::node::BufferType > () = {.size = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ())};
    }
#line 2843 "src/parser.cpp"
    break;

  case 123: // paren_range_decl: OPAREN cat_range_decl CPAREN
#line 500 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::syn::category::RangeDeclaration > () = YY_MOVE (yystack_[1].value.as < cynth::syn::category::RangeDeclaration > ());
    }
#line 2851 "src/parser.cpp"
    break;

  case 124: // paren_range_decl: OPAREN range_decl_list CPAREN
#line 503 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::category::RangeDeclaration > () = cynth::syn::node::TupleRangeDecl{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::RangeDeclaration> > ())};
    }
#line 2859 "src/parser.cpp"
    break;

  case 125: // paren_range_decl: OPAREN range_decl_list COMMA CPAREN
#line 506 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::syn::category::RangeDeclaration > () = cynth::syn::node::TupleRangeDecl{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::RangeDeclaration> > ())};
    }
#line 2867 "src/parser.cpp"
    break;

  case 126: // paren_decl: OPAREN cat_declaration CPAREN
#line 511 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::syn::category::Declaration > () = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ());
    }
#line 2875 "src/parser.cpp"
    break;

  case 127: // paren_decl: OPAREN decl_list CPAREN
#line 514 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::category::Declaration > () = cynth::syn::node::TupleDecl{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::Declaration> > ())};
    }
#line 2883 "src/parser.cpp"
    break;

  case 128: // paren_decl: OPAREN decl_list COMMA CPAREN
#line 517 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::category::Declaration > () = cynth::syn::node::TupleDecl{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Declaration> > ())};
    }
#line 2891 "src/parser.cpp"
    break;

  case 129: // void_decl: OPAREN CPAREN
#line 522 "gen/parser.y"
                  {
        yylhs.value.as < cynth::syn::category::Declaration > () = cynth::syn::node::TupleDecl{};
    }
#line 2899 "src/parser.cpp"
    break;

  case 130: // node_declaration: cat_type node_name
#line 527 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Declaration > () = {.name = YY_MOVE (yystack_[0].value.as < cynth::syn::node::Name > ()), .type = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ())};
    }
#line 2907 "src/parser.cpp"
    break;

  case 131: // node_range_decl: cat_declaration IN cat_expression
#line 532 "gen/parser.y"
                                                   {
        yylhs.value.as < cynth::syn::node::RangeDecl > () = {.declaration = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Declaration > ()), .range = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2915 "src/parser.cpp"
    break;

  case 132: // node_range_to: cat_expression TO cat_expression
#line 539 "gen/parser.y"
                                               {
        yylhs.value.as < cynth::syn::node::RangeTo > () = {.from = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), .to = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2923 "src/parser.cpp"
    break;

  case 133: // node_range_to_by: cat_expression TO cat_expression BY cat_expression
#line 544 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::syn::node::RangeToBy > () = {.from = YY_MOVE (yystack_[4].value.as < cynth::syn::category::Expression > ()), .to = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), .by = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2931 "src/parser.cpp"
    break;

  case 134: // node_spread: ELIP cat_expression
#line 549 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Spread > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 2939 "src/parser.cpp"
    break;

  case 135: // paren_expr: OPAREN cat_expression CPAREN
#line 556 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::syn::category::Expression > () = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ());
    }
#line 2947 "src/parser.cpp"
    break;

  case 136: // paren_expr: OPAREN expr_list CPAREN
#line 559 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::category::Expression > () = cynth::syn::node::Tuple{YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::Expression> > ())};
    }
#line 2955 "src/parser.cpp"
    break;

  case 137: // paren_expr: OPAREN expr_list COMMA CPAREN
#line 562 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::category::Expression > () = cynth::syn::node::Tuple{YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Expression> > ())};
    }
#line 2963 "src/parser.cpp"
    break;

  case 138: // void: OPAREN CPAREN
#line 567 "gen/parser.y"
                  {
        yylhs.value.as < cynth::syn::category::Expression > () = cynth::syn::node::Tuple{};
    }
#line 2971 "src/parser.cpp"
    break;

  case 139: // node_name: NAME
#line 572 "gen/parser.y"
               {
        yylhs.value.as < cynth::syn::node::Name > () = {YY_MOVE (yystack_[0].value.as < std::string > ())};
    }
#line 2979 "src/parser.cpp"
    break;

  case 140: // node_block: OBRACE CBRACE
#line 577 "gen/parser.y"
                  {
        yylhs.value.as < cynth::syn::node::Block > () = {};
    }
#line 2987 "src/parser.cpp"
    break;

  case 141: // node_block: OBRACE stmt_list CBRACE
#line 580 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::node::Block > () = {YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::Statement> > ())};
    }
#line 2995 "src/parser.cpp"
    break;

  case 142: // node_block: OBRACE stmt_list SEMI CBRACE
#line 583 "gen/parser.y"
                                       {
        yylhs.value.as < cynth::syn::node::Block > () = {YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Statement> > ())};
    }
#line 3003 "src/parser.cpp"
    break;

  case 143: // node_bool: TRUE
#line 590 "gen/parser.y"
         {
        yylhs.value.as < cynth::syn::node::Bool > () = {true};
    }
#line 3011 "src/parser.cpp"
    break;

  case 144: // node_bool: FALSE
#line 593 "gen/parser.y"
          {
        yylhs.value.as < cynth::syn::node::Bool > () = {false};
    }
#line 3019 "src/parser.cpp"
    break;

  case 145: // node_int: INT
#line 598 "gen/parser.y"
        {
        yylhs.value.as < cynth::syn::node::Int > () = {esl::stoi<cynth::sem::Integral>(YY_MOVE (yystack_[0].value.as < std::string > ()))}; // TODO: The sem::Integral type should be obtainable from syn::node::Int
    }
#line 3027 "src/parser.cpp"
    break;

  case 146: // node_float: FLOAT
#line 603 "gen/parser.y"
          {
        yylhs.value.as < cynth::syn::node::Float > () = {std::stof(YY_MOVE (yystack_[0].value.as < std::string > ()))};
    }
#line 3035 "src/parser.cpp"
    break;

  case 147: // node_string: STRING
#line 608 "gen/parser.y"
           {
        yylhs.value.as < cynth::syn::node::String > () = {esl::trim(YY_MOVE (yystack_[0].value.as < std::string > ()))};
    }
#line 3043 "src/parser.cpp"
    break;

  case 148: // node_function: cat_type FN paren_decl cat_expression
#line 613 "gen/parser.y"
                                                         {
        yylhs.value.as < cynth::syn::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3051 "src/parser.cpp"
    break;

  case 149: // node_function: void_type FN paren_decl cat_expression
#line 616 "gen/parser.y"
                                                          {
        yylhs.value.as < cynth::syn::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3059 "src/parser.cpp"
    break;

  case 150: // node_function: cat_type FN void_decl cat_expression
#line 619 "gen/parser.y"
                                                        {
        yylhs.value.as < cynth::syn::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3067 "src/parser.cpp"
    break;

  case 151: // node_function: void_type FN void_decl cat_expression
#line 622 "gen/parser.y"
                                                         {
        yylhs.value.as < cynth::syn::node::Function > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3075 "src/parser.cpp"
    break;

  case 152: // node_array: OBRACK CBRACK
#line 627 "gen/parser.y"
                  {
        yylhs.value.as < cynth::syn::node::Array > () = {};
    }
#line 3083 "src/parser.cpp"
    break;

  case 153: // node_array: OBRACK array_elem_list CBRACK
#line 630 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::node::Array > () = {YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::ArrayElement> > ())};
    }
#line 3091 "src/parser.cpp"
    break;

  case 154: // node_array: OBRACK array_elem_list COMMA CBRACK
#line 633 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::syn::node::Array > () = {YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::ArrayElement> > ())};
    }
#line 3099 "src/parser.cpp"
    break;

  case 155: // node_or: expr_or OR expr_and
#line 640 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::node::Or > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3107 "src/parser.cpp"
    break;

  case 156: // node_or_right: expr_or OR expr_and_right
#line 645 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::node::Or > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3115 "src/parser.cpp"
    break;

  case 157: // node_and: expr_and AND expr_eq
#line 650 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::And > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3123 "src/parser.cpp"
    break;

  case 158: // node_and_right: expr_and AND expr_eq_right
#line 655 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::syn::node::And > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3131 "src/parser.cpp"
    break;

  case 159: // node_eq: expr_eq EQ expr_ord
#line 660 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::node::Eq > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3139 "src/parser.cpp"
    break;

  case 160: // node_eq_right: expr_eq EQ expr_ord_right
#line 665 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::node::Eq > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3147 "src/parser.cpp"
    break;

  case 161: // node_ne: expr_eq NE expr_ord
#line 670 "gen/parser.y"
                                  {
        yylhs.value.as < cynth::syn::node::Ne > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3155 "src/parser.cpp"
    break;

  case 162: // node_ne_right: expr_eq NE expr_ord_right
#line 675 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::node::Ne > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3163 "src/parser.cpp"
    break;

  case 163: // node_ge: expr_ord GE expr_add
#line 680 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Ge > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3171 "src/parser.cpp"
    break;

  case 164: // node_ge_right: expr_ord GE expr_add_right
#line 685 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::syn::node::Ge > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3179 "src/parser.cpp"
    break;

  case 165: // node_le: expr_ord LE expr_add
#line 690 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Le > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3187 "src/parser.cpp"
    break;

  case 166: // node_le_right: expr_ord LE expr_add_right
#line 695 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::syn::node::Le > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3195 "src/parser.cpp"
    break;

  case 167: // node_gt: expr_ord GT expr_add
#line 700 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Gt > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3203 "src/parser.cpp"
    break;

  case 168: // node_gt_right: expr_ord GT expr_add_right
#line 705 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::syn::node::Gt > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3211 "src/parser.cpp"
    break;

  case 169: // node_lt: expr_ord LT expr_add
#line 710 "gen/parser.y"
                                   {
        yylhs.value.as < cynth::syn::node::Lt > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3219 "src/parser.cpp"
    break;

  case 170: // node_lt_right: expr_ord LT expr_add_right
#line 715 "gen/parser.y"
                                         {
        yylhs.value.as < cynth::syn::node::Lt > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3227 "src/parser.cpp"
    break;

  case 171: // node_add: expr_add ADD expr_mul
#line 720 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Add > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3235 "src/parser.cpp"
    break;

  case 172: // node_add_right: expr_add ADD expr_mul_right
#line 725 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::syn::node::Add > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3243 "src/parser.cpp"
    break;

  case 173: // node_sub: expr_add SUB expr_mul
#line 730 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Sub > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3251 "src/parser.cpp"
    break;

  case 174: // node_sub_right: expr_add SUB expr_mul_right
#line 735 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::syn::node::Sub > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3259 "src/parser.cpp"
    break;

  case 175: // node_mul: expr_mul MUL expr_pow
#line 740 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Mul > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3267 "src/parser.cpp"
    break;

  case 176: // node_mul_right: expr_mul MUL expr_pow_right
#line 745 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::syn::node::Mul > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3275 "src/parser.cpp"
    break;

  case 177: // node_div: expr_mul DIV expr_pow
#line 750 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Div > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3283 "src/parser.cpp"
    break;

  case 178: // node_div_right: expr_mul DIV expr_pow_right
#line 755 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::syn::node::Div > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3291 "src/parser.cpp"
    break;

  case 179: // node_mod: expr_mul MOD expr_pow
#line 760 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Mod > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3299 "src/parser.cpp"
    break;

  case 180: // node_mod_right: expr_mul MOD expr_pow_right
#line 765 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::syn::node::Mod > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3307 "src/parser.cpp"
    break;

  case 181: // node_pow: expr_pre POW expr_pow
#line 770 "gen/parser.y"
                                    {
        yylhs.value.as < cynth::syn::node::Pow > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3315 "src/parser.cpp"
    break;

  case 182: // node_pow_right: expr_pre POW expr_pow_right
#line 775 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::syn::node::Pow > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3323 "src/parser.cpp"
    break;

  case 183: // node_minus: SUB expr_pre
#line 780 "gen/parser.y"
                      {
        yylhs.value.as < cynth::syn::node::Minus > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3331 "src/parser.cpp"
    break;

  case 184: // node_minus_right: SUB expr_right
#line 785 "gen/parser.y"
                        {
        yylhs.value.as < cynth::syn::node::Minus > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3339 "src/parser.cpp"
    break;

  case 185: // node_plus: ADD expr_pre
#line 790 "gen/parser.y"
                      {
        yylhs.value.as < cynth::syn::node::Plus > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3347 "src/parser.cpp"
    break;

  case 186: // node_plus_right: ADD expr_right
#line 795 "gen/parser.y"
                        {
        yylhs.value.as < cynth::syn::node::Plus > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3355 "src/parser.cpp"
    break;

  case 187: // node_not: NOT expr_pre
#line 800 "gen/parser.y"
                      {
        yylhs.value.as < cynth::syn::node::Not > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3363 "src/parser.cpp"
    break;

  case 188: // node_not_right: NOT expr_right
#line 805 "gen/parser.y"
                        {
        yylhs.value.as < cynth::syn::node::Not > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3371 "src/parser.cpp"
    break;

  case 189: // node_application: expr_post paren_expr
#line 810 "gen/parser.y"
                                              {
        yylhs.value.as < cynth::syn::node::Application > () = {.function = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ()), .arguments = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3379 "src/parser.cpp"
    break;

  case 190: // node_application: expr_post void
#line 813 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::node::Application > () = {.function = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ()), .arguments = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3387 "src/parser.cpp"
    break;

  case 191: // node_conversion: cat_type paren_expr
#line 818 "gen/parser.y"
                                        {
        yylhs.value.as < cynth::syn::node::Conversion > () = {.type = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Type > ()), .argument = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3395 "src/parser.cpp"
    break;

  case 192: // node_subscript: expr_post OBRACK array_elem_list CBRACK
#line 823 "gen/parser.y"
                                                                 {
        yylhs.value.as < cynth::syn::node::Subscript > () = {.container = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ()), .location = YY_MOVE (yystack_[1].value.as < esl::component_vector<cynth::syn::category::ArrayElement> > ())};
    }
#line 3403 "src/parser.cpp"
    break;

  case 193: // node_subscript: expr_post OBRACK CBRACK
#line 826 "gen/parser.y"
                                       {
        yylhs.value.as < cynth::syn::node::Subscript > () = {.container = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), .location = {}};
    }
#line 3411 "src/parser.cpp"
    break;

  case 194: // node_expr_if: IF paren_expr cat_expression ELSE cat_expression
#line 831 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::syn::node::ExprIf > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ()), .positiveBranch = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), .negativeBranch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3419 "src/parser.cpp"
    break;

  case 195: // node_expr_for: FOR paren_range_decl cat_expression
#line 836 "gen/parser.y"
                                                    {
        yylhs.value.as < cynth::syn::node::ExprFor > () = {.declarations = YY_MOVE (yystack_[1].value.as < cynth::syn::category::RangeDeclaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3427 "src/parser.cpp"
    break;

  case 196: // node_definition: cat_declaration ASSGN cat_expression
#line 843 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::syn::node::Definition > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Declaration > ()), .value = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3435 "src/parser.cpp"
    break;

  case 197: // node_assignment: expr_assgn_target ASSGN cat_expression
#line 848 "gen/parser.y"
                                                        {
        yylhs.value.as < cynth::syn::node::Assignment > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), .value = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3443 "src/parser.cpp"
    break;

  case 198: // node_type_def: TYPE node_type_name ASSGN cat_type
#line 853 "gen/parser.y"
                                                     {
        yylhs.value.as < cynth::syn::node::TypeDef > () = {.target = YY_MOVE (yystack_[2].value.as < cynth::syn::node::TypeName > ()), .type = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 3451 "src/parser.cpp"
    break;

  case 199: // node_function_def: cat_type node_name paren_decl cat_expression
#line 858 "gen/parser.y"
                                                                      {
        yylhs.value.as < cynth::syn::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::syn::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3459 "src/parser.cpp"
    break;

  case 200: // node_function_def: void_type node_name paren_decl cat_expression
#line 861 "gen/parser.y"
                                                                       {
        yylhs.value.as < cynth::syn::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::syn::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3467 "src/parser.cpp"
    break;

  case 201: // node_function_def: cat_type node_name void_decl cat_expression
#line 864 "gen/parser.y"
                                                                     {
        yylhs.value.as < cynth::syn::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::syn::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3475 "src/parser.cpp"
    break;

  case 202: // node_function_def: void_type node_name void_decl cat_expression
#line 867 "gen/parser.y"
                                                                      {
        yylhs.value.as < cynth::syn::node::FunDef > () = {.output = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Type > ()), .input = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Declaration > ()), .name = YY_MOVE (yystack_[2].value.as < cynth::syn::node::Name > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3483 "src/parser.cpp"
    break;

  case 203: // node_return: RETURN cat_expression
#line 872 "gen/parser.y"
                               {
        yylhs.value.as < cynth::syn::node::Return > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3491 "src/parser.cpp"
    break;

  case 204: // node_return: RETURN void
#line 875 "gen/parser.y"
                     {
        yylhs.value.as < cynth::syn::node::Return > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3499 "src/parser.cpp"
    break;

  case 205: // node_return: RETURN
#line 878 "gen/parser.y"
           {
        yylhs.value.as < cynth::syn::node::Return > () = {cynth::syn::category::Expression{cynth::syn::node::Tuple{}}};
    }
#line 3507 "src/parser.cpp"
    break;

  case 206: // node_if: IF paren_expr pure ELSE pure
#line 883 "gen/parser.y"
                                                 {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ()), .positiveBranch = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Statement > ()), .negativeBranch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3515 "src/parser.cpp"
    break;

  case 207: // node_if: IF paren_expr pure SEMI ELSE pure
#line 886 "gen/parser.y"
                                                      {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[4].value.as < cynth::syn::category::Expression > ()), .positiveBranch = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Statement > ()), .negativeBranch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3523 "src/parser.cpp"
    break;

  case 208: // node_if: IF paren_expr cat_expression ELSE pure
#line 889 "gen/parser.y"
                                                           {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ()), .positiveBranch = cynth::syn::category::Statement{YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ())}, .negativeBranch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3531 "src/parser.cpp"
    break;

  case 209: // node_if: IF paren_expr cat_expression SEMI ELSE pure
#line 892 "gen/parser.y"
                                                                {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[4].value.as < cynth::syn::category::Expression > ()), .positiveBranch = cynth::syn::category::Statement{YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ())}, .negativeBranch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3539 "src/parser.cpp"
    break;

  case 210: // node_if: IF paren_expr pure ELSE cat_expression
#line 895 "gen/parser.y"
                                                           {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Expression > ()), .positiveBranch = YY_MOVE (yystack_[2].value.as < cynth::syn::category::Statement > ()), .negativeBranch = cynth::syn::category::Statement{YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())}};
    }
#line 3547 "src/parser.cpp"
    break;

  case 211: // node_if: IF paren_expr pure SEMI ELSE cat_expression
#line 898 "gen/parser.y"
                                                                {
        yylhs.value.as < cynth::syn::node::If > () = {.condition = YY_MOVE (yystack_[4].value.as < cynth::syn::category::Expression > ()), .positiveBranch = YY_MOVE (yystack_[3].value.as < cynth::syn::category::Statement > ()), .negativeBranch = cynth::syn::category::Statement{YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())}};
    }
#line 3555 "src/parser.cpp"
    break;

  case 212: // node_when: WHEN paren_expr cat_statement
#line 903 "gen/parser.y"
                                             {
        yylhs.value.as < cynth::syn::node::When > () = {.condition = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ()), .branch = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3563 "src/parser.cpp"
    break;

  case 213: // node_for: FOR paren_range_decl pure
#line 908 "gen/parser.y"
                                          {
        yylhs.value.as < cynth::syn::node::For > () = {.declarations = YY_MOVE (yystack_[1].value.as < cynth::syn::category::RangeDeclaration > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3571 "src/parser.cpp"
    break;

  case 214: // node_while: WHILE paren_expr cat_statement
#line 913 "gen/parser.y"
                                               {
        yylhs.value.as < cynth::syn::node::While > () = {.condition = YY_MOVE (yystack_[1].value.as < cynth::syn::category::Expression > ()), .body = YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3579 "src/parser.cpp"
    break;

  case 215: // array_elem_list: cat_array_elem
#line 920 "gen/parser.y"
                          {
        yylhs.value.as < esl::component_vector<cynth::syn::category::ArrayElement> > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::ArrayElement > ())};
    }
#line 3587 "src/parser.cpp"
    break;

  case 216: // array_elem_list: array_elem_list COMMA cat_array_elem
#line 923 "gen/parser.y"
                                                     {
        yylhs.value.as < esl::component_vector<cynth::syn::category::ArrayElement> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::ArrayElement > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::ArrayElement> > ()));
    }
#line 3595 "src/parser.cpp"
    break;

  case 217: // stmt_list: cat_statement
#line 928 "gen/parser.y"
                         {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Statement> > () = {YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ())};
    }
#line 3603 "src/parser.cpp"
    break;

  case 218: // stmt_list: stmt_list SEMI cat_statement
#line 931 "gen/parser.y"
                                             {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Statement> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::Statement > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Statement> > ()));
    }
#line 3611 "src/parser.cpp"
    break;

  case 219: // type_list: cat_type COMMA cat_type
#line 936 "gen/parser.y"
                                           {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Type> > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Type > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ())};
    }
#line 3619 "src/parser.cpp"
    break;

  case 220: // type_list: type_list COMMA cat_type
#line 939 "gen/parser.y"
                                         {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Type> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::Type > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Type> > ()));
    }
#line 3627 "src/parser.cpp"
    break;

  case 221: // expr_list: cat_expression COMMA cat_expression
#line 944 "gen/parser.y"
                                                       {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Expression> > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ())};
    }
#line 3635 "src/parser.cpp"
    break;

  case 222: // expr_list: expr_list COMMA cat_expression
#line 947 "gen/parser.y"
                                               {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Expression> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::Expression > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Expression> > ()));
    }
#line 3643 "src/parser.cpp"
    break;

  case 223: // decl_list: cat_declaration COMMA cat_declaration
#line 952 "gen/parser.y"
                                                         {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Declaration> > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::Declaration > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::Declaration > ())};
    }
#line 3651 "src/parser.cpp"
    break;

  case 224: // decl_list: decl_list COMMA cat_declaration
#line 955 "gen/parser.y"
                                                {
        yylhs.value.as < esl::component_vector<cynth::syn::category::Declaration> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::Declaration > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::Declaration> > ()));
    }
#line 3659 "src/parser.cpp"
    break;

  case 225: // range_decl_list: cat_range_decl COMMA cat_range_decl
#line 960 "gen/parser.y"
                                                       {
        yylhs.value.as < esl::component_vector<cynth::syn::category::RangeDeclaration> > () = {YY_MOVE (yystack_[2].value.as < cynth::syn::category::RangeDeclaration > ()), YY_MOVE (yystack_[0].value.as < cynth::syn::category::RangeDeclaration > ())};
    }
#line 3667 "src/parser.cpp"
    break;

  case 226: // range_decl_list: range_decl_list COMMA cat_range_decl
#line 963 "gen/parser.y"
                                                     {
        yylhs.value.as < esl::component_vector<cynth::syn::category::RangeDeclaration> > () = esl::push_back(YY_MOVE (yystack_[0].value.as < cynth::syn::category::RangeDeclaration > ()), YY_MOVE (yystack_[2].value.as < esl::component_vector<cynth::syn::category::RangeDeclaration> > ()));
    }
#line 3675 "src/parser.cpp"
    break;


#line 3679 "src/parser.cpp"

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





  const short parser::yypact_ninf_ = -278;

  const signed char parser::yytable_ninf_ = -108;

  const short
  parser::yypact_[] =
  {
      56,  -278,  -278,  -278,  -278,  -278,  -278,    -7,    -7,    19,
      -7,    46,    20,  1015,  -278,  -278,  -278,   735,   464,   615,
    -278,  1055,  1055,  1055,  -278,    79,    10,    93,  -278,  -278,
    -278,    62,    74,    55,   275,    94,   292,  -278,    95,   100,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
     118,  -278,    67,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
     142,  1095,   575,   575,   240,   575,   575,   151,  1095,    -7,
      19,   775,  1132,  -278,    51,    -4,  -278,  -278,    80,    28,
     121,   168,   182,   185,  -278,   -17,  1095,   815,  -278,  -278,
     141,  -278,  -278,  -278,    52,  1135,  1135,  1135,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,   153,  -278,  -278,  -278,   855,
    -278,  -278,  -278,   153,  1095,  1095,  1095,  1095,  1095,  1095,
    1095,  1095,  1095,  1095,  1095,  1095,  1095,  1095,  1095,   895,
     655,  -278,  -278,  1095,   153,   146,  -278,  -278,   153,   575,
       5,     8,  -278,   154,   483,   164,   194,    53,  -278,  -278,
     202,  -278,  -278,  -278,   421,   156,  1095,  1095,    83,  1188,
     421,  -278,  -278,  1114,  -278,  1095,  -278,   181,  -278,   244,
    -278,   935,  -278,   534,  -278,  -278,  1095,   695,  -278,   612,
     247,  1095,  1095,   179,  -278,    10,   200,   204,  1095,  1095,
    -278,    74,  -278,    55,  -278,   275,  -278,   275,  -278,    94,
    -278,    94,  -278,    94,  -278,    94,  -278,   292,  -278,   292,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,    85,  -278,  1095,  1095,  1201,  1095,  1095,  -278,   575,
     193,   575,   219,   410,   163,  1095,   240,  -278,   314,  -278,
     652,  -278,   233,   652,   387,  -278,  -278,  -278,   652,  -278,
    -278,  -278,  -278,  -278,   222,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,   975,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  1175,  -278,  -278,   575,  -278,  -278,  -278,
    -278,  1095,  1095,    -7,    19,   500,  -278,    51,     9,  -278,
    -278,  -278,   575,  1175,    11,  1175
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     6,   139,   110,   145,   146,   147,     0,     0,     0,
       0,     0,     0,   205,   143,   144,   109,     0,     0,     0,
     108,     0,     0,     0,     5,     0,     0,    28,    27,   217,
      26,    24,    39,    43,    48,    56,    64,    71,    77,    83,
      91,    25,    41,    45,    51,    61,    67,    75,    79,    87,
       0,    23,     0,    15,    16,    20,    21,    22,    17,    18,
      19,     8,     7,    99,    92,    97,    93,    94,    95,    96,
     102,    98,    38,    42,    46,    47,    52,    53,    54,    55,
      62,    63,    68,    69,    70,    76,    81,    80,    82,    40,
      44,    49,    50,    57,    58,    59,    60,    65,    66,    72,
      73,    74,    78,    85,    84,    86,    88,    89,    90,   100,
     101,    29,    30,    32,    31,    33,    34,    37,    35,    36,
       3,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   203,    83,     0,   204,   107,     0,     0,
       0,     0,     0,     0,   140,     0,     0,     0,   152,   215,
      14,    11,    12,    13,     0,     0,     0,     0,   185,   186,
     183,   184,   187,   188,     1,     0,   111,   112,   113,     0,
     114,   116,   191,   130,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   189,   190,     0,     0,     0,   115,   117,     0,     4,
       0,     0,   212,     0,     0,     0,     0,     0,    10,     9,
       0,   195,   213,   214,     0,     0,     0,     0,   138,     0,
       0,   104,   130,     0,   126,     0,   135,     0,   105,     0,
     127,     0,   136,     0,   141,   134,     0,     0,   153,     0,
       0,     0,     0,   109,   120,     0,     0,     0,     0,     0,
     196,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   138,
     193,     0,   197,     0,     0,     0,     0,     0,   218,     0,
       0,     0,     0,     0,     0,     0,     0,   123,     0,   124,
     198,   122,     0,   219,     0,   223,   221,   106,   220,   128,
     224,   137,   222,   142,   132,   154,   216,   129,   148,   150,
     119,   121,   118,   199,   201,     0,   192,   149,   151,   200,
     202,   194,   208,     0,   210,   206,     0,   131,   225,   125,
     226,     0,     0,     0,     0,     0,   209,   103,     0,   211,
     207,   133,     0,     0,     0,     0
  };

  const short
  parser::yypgoto_[] =
  {
    -278,  -278,    23,   148,  -277,  -235,   273,  -122,    75,  -278,
      86,    81,   -25,   278,    47,   175,   -14,    37,  -278,  -278,
      96,    92,    76,   393,    82,   414,  -278,   346,  -278,     2,
       0,  -278,   269,  -278,  -278,  -278,  -278,  -278,  -278,  -162,
      -3,   -78,  -278,  -278,  -278,  -278,  -278,    39,   268,   -10,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,    98,  -278,
     276
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,    25,   132,    27,   206,   149,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,   134,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
     135,    53,    54,    55,    56,    57,    58,    59,    60,    61,
     208,   242,    62,   209,   151,   152,   153,    63,   192,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   141,   142,   210,   154,   143,
     120
  };

  const short
  parser::yytable_[] =
  {
      52,   202,   316,   241,   213,   233,   125,   158,   160,   162,
     194,   248,     2,     2,   289,   234,   173,   291,    52,   338,
     355,   340,   121,    26,   165,   195,   171,   290,   170,   166,
     292,    20,   283,   290,   167,   168,   286,    39,   195,   147,
     138,    26,   198,   169,    20,    20,   122,   123,   124,   126,
       3,   223,   197,   128,   196,    39,    -2,     1,   224,     2,
       3,     4,     5,     6,     7,   172,     8,     9,    10,    11,
       2,    12,    13,    14,    15,   237,    16,   288,   191,   164,
     189,   194,   195,     2,   190,    17,   238,    18,    20,    19,
     316,    20,    21,    22,   165,   249,   195,  -107,    23,   166,
     177,   178,    20,   220,   167,   168,   175,    24,   325,   147,
     221,   288,  -107,   169,   174,    20,   284,   176,  -107,   326,
     287,  -103,    52,    52,   207,    52,    52,   217,   222,   189,
     183,   184,   171,   190,   170,   197,   188,   196,   171,   193,
     170,   158,   160,   162,   225,    26,    26,   204,    26,    26,
       3,   226,   255,   257,   219,   207,   207,   207,     3,    39,
      39,    12,    39,    39,   199,   139,    16,   236,   216,    12,
     219,   172,   214,   191,    16,   195,   137,   172,   239,   239,
     239,    20,   240,   203,   137,     3,   223,   295,   295,    20,
     301,   227,   245,   224,   222,   207,    12,   201,   228,    52,
     212,    16,   333,   207,   171,   229,   170,   197,   231,   196,
     195,   307,   230,   320,   207,   232,    20,   296,   285,   171,
     207,   170,    26,   207,   297,   298,   293,   207,   336,   207,
     267,   269,   299,    52,   321,   222,    39,   300,   322,   171,
     207,   170,   341,   303,     3,   171,   204,   170,     3,   342,
     308,     3,   204,   256,   258,    12,    26,   253,   172,    12,
      16,   251,    12,   204,    16,   268,   270,    16,   254,   203,
      39,   252,   205,   304,   309,    20,   304,   317,   172,    20,
     127,   136,    20,   222,   172,   171,   133,   170,   281,    52,
     140,    52,   150,   171,   145,   170,   207,     0,   207,     0,
     171,     0,   170,   171,   207,   170,     0,     0,   171,     0,
     170,     0,    26,     0,    26,     0,     0,   246,     3,   204,
       0,   204,   179,   180,   181,   182,    39,   293,    39,    12,
     185,   186,   187,   348,    16,   173,    52,     0,   198,     0,
       0,   353,     0,   203,   339,   171,     0,   170,   197,    20,
     196,   294,    52,   348,     0,   348,   345,     0,     0,    26,
     271,   273,   275,   277,   332,     0,   335,   159,   161,   163,
     347,   305,     0,    39,     0,    26,   345,   310,   345,     0,
       0,     0,   352,     0,   172,     0,   191,     0,   139,    39,
     347,     3,   347,     0,   140,   200,     0,     0,   211,     0,
       0,   215,    12,     0,   140,     0,     0,    16,   346,     0,
       0,   350,     0,     2,     0,     0,   304,   137,     0,   235,
     140,     0,    20,     0,     0,     3,     0,   201,   212,   166,
     332,     0,     0,   220,   167,   168,    12,     0,     0,   195,
     221,    16,   247,   169,   205,    20,   205,   250,     0,     0,
     195,     0,   139,     0,     0,     0,    20,   259,   261,   263,
     265,     0,   140,   150,     0,     0,   282,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,     0,    12,
      13,    14,    15,     0,    16,     0,     2,     0,     0,   302,
     211,     0,     0,    17,     0,    18,   144,    19,   306,    20,
      21,    22,   166,     2,   312,     0,    23,   167,   168,   314,
     150,     0,   195,     0,   318,   319,   169,     0,    20,   166,
       0,   323,   324,     0,   167,   168,     0,     0,     0,   147,
       0,     0,     0,   169,     0,    20,     0,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,    11,     0,    12,
      13,    14,    15,     0,    16,     0,   327,   328,     0,   329,
     330,     0,   331,    17,   334,    18,   313,    19,   337,    20,
      21,    22,   260,   262,   264,   266,    23,     0,     2,     3,
       4,     5,     6,     7,     0,     8,     9,    10,    11,     0,
      12,    13,    14,    15,     0,    16,     0,     0,   150,   272,
     274,   276,   278,     0,    17,     0,    18,     0,    19,   349,
      20,    21,    22,     0,   331,   351,     0,    23,     2,     3,
       4,     5,     6,   129,     0,   354,   130,     0,     0,     0,
      12,   166,    14,    15,     0,    16,   167,   168,     0,     0,
       0,   147,     0,   146,   147,   169,    18,    20,    19,   148,
      20,    21,    22,     0,     0,     0,     0,    23,     2,     3,
       4,     5,     6,   129,     0,     0,   130,     0,     0,     0,
      12,   166,    14,    15,     0,    16,   167,   168,     0,     0,
       0,   195,     0,   146,   147,   169,    18,    20,    19,   280,
      20,    21,    22,     0,     0,     0,     0,    23,     2,     3,
       4,     5,     6,   129,     0,     0,   130,     0,     0,     0,
      12,     0,    14,    15,     0,    16,     0,     0,     0,     0,
       0,     0,     0,   146,   147,     0,    18,     0,    19,   315,
      20,    21,    22,     0,     0,     0,     0,    23,     2,     3,
       4,     5,     6,   129,     0,     0,   130,     0,     0,     0,
      12,     0,    14,    15,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,    17,   137,    18,     0,    19,     0,
      20,    21,    22,     0,     0,     0,     0,    23,     2,     3,
       4,     5,     6,   129,     0,     0,   130,     0,     0,     0,
      12,     0,    14,    15,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,   147,   218,    18,     0,    19,     0,
      20,    21,    22,     0,     0,     0,     0,    23,     2,     3,
       4,     5,     6,   129,     0,     0,   130,     0,     0,     0,
      12,     0,    14,    15,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,   147,   137,    18,     0,    19,     0,
      20,    21,    22,     0,     0,     0,     0,    23,     2,     3,
       4,     5,     6,   129,     0,     0,   130,     0,     0,     0,
      12,     0,    14,    15,     0,   243,     0,     0,     0,     0,
       0,     0,     0,     0,    17,     0,    18,     0,    19,   244,
      20,    21,    22,     0,     0,     0,     0,    23,     2,     3,
       4,     5,     6,   129,     0,     0,   130,     0,     0,     0,
      12,     0,    14,    15,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,   147,   279,    18,     0,    19,     0,
      20,    21,    22,     0,     0,     0,     0,    23,     2,     3,
       4,     5,     6,   129,     0,     0,   130,     0,     0,     0,
      12,     0,    14,    15,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,   147,   311,    18,     0,    19,     0,
      20,    21,    22,     0,     0,     0,     0,    23,     2,     3,
       4,     5,     6,   129,     0,     0,   130,     0,     0,     0,
      12,     0,    14,    15,     0,    16,     0,     0,     0,     0,
       0,     0,     0,   146,   147,     0,    18,     0,    19,     0,
      20,    21,    22,     0,     0,     0,     0,    23,     2,     3,
       4,     5,     6,   129,     0,     0,   130,     0,     0,     0,
      12,     0,    14,    15,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,   131,     0,    18,     0,    19,     0,
      20,    21,    22,     0,     0,     0,     0,    23,     2,     3,
       4,     5,     6,   129,     0,     0,   130,     0,     0,     0,
      12,     0,    14,    15,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,   147,     0,    18,     0,    19,     0,
      20,   155,   156,     0,     0,     0,     0,   157,     2,     3,
       4,     5,     6,   129,     0,     0,   130,     0,     0,     0,
      12,     0,    14,    15,     0,    16,     0,     0,     3,     0,
       0,     0,     0,     0,   147,     0,    18,     0,    19,    12,
      20,    21,    22,     0,    16,     0,     0,    23,     2,     3,
       4,     5,     6,   304,     0,     0,   165,     0,     0,    20,
      12,   166,    14,    15,     0,    16,   167,   168,     0,     0,
       0,   147,     0,     0,   147,   169,    18,    20,    19,     0,
      20,   155,   156,     0,     0,     0,     0,   157,     2,     3,
       4,     5,     6,   343,     0,     8,   344,    10,    11,     0,
      12,    13,    14,    15,     0,    16,     0,     0,     0,     0,
       0,     0,   165,     0,    17,     0,    18,   166,    19,     0,
      20,   220,   167,   168,     0,     0,     0,   147,   221,     0,
     166,   169,     0,    20,   220,   167,   168,     0,     0,     0,
     195,   221,     0,     0,   169,     0,    20
  };

  const short
  parser::yycheck_[] =
  {
       0,   123,   237,   165,   126,    22,     9,    21,    22,    23,
      14,   173,     3,     3,     9,    32,    26,     9,    18,   296,
       9,   298,    29,     0,    14,    29,    26,    22,    26,    19,
      22,    35,   194,    22,    24,    25,   198,     0,    29,    29,
      17,    18,    52,    33,    35,    35,     7,     8,    29,    10,
       4,    23,    52,    33,    52,    18,     0,     1,    30,     3,
       4,     5,     6,     7,     8,    26,    10,    11,    12,    13,
       3,    15,    16,    17,    18,    23,    20,   199,    39,     0,
      29,    14,    29,     3,    33,    29,    34,    31,    35,    33,
     325,    35,    36,    37,    14,   173,    29,    14,    42,    19,
      45,    46,    35,    23,    24,    25,    44,    51,    23,    29,
      30,   233,    29,    33,    21,    35,   194,    43,    35,    34,
     198,    21,   122,   123,   124,   125,   126,   130,   138,    29,
      36,    37,   132,    33,   132,   135,    41,   135,   138,    21,
     138,   155,   156,   157,    23,   122,   123,   124,   125,   126,
       4,    30,   177,   178,   131,   155,   156,   157,     4,   122,
     123,    15,   125,   126,    22,    17,    20,    26,   129,    15,
     147,   132,    21,   134,    20,    29,    30,   138,   155,   156,
     157,    35,    29,    29,    30,     4,    23,    24,    24,    35,
      34,    23,   169,    30,   204,   195,    15,   122,    30,   199,
     125,    20,     9,   203,   204,    23,   204,   207,    23,   207,
      29,    30,    30,    34,   214,    30,    35,    23,   195,   219,
     220,   219,   199,   223,    30,    23,   203,   227,     9,   229,
     183,   184,    30,   233,    34,   245,   199,   214,    34,   239,
     240,   239,     9,   220,     4,   245,   223,   245,     4,    27,
     227,     4,   229,   177,   178,    15,   233,   176,   219,    15,
      20,   175,    15,   240,    20,   183,   184,    20,   176,    29,
     233,   175,   124,    29,    30,    35,    29,    30,   239,    35,
      11,    13,    35,   293,   245,   285,    13,   285,   190,   289,
      17,   291,    19,   293,    18,   293,   296,    -1,   298,    -1,
     300,    -1,   300,   303,   304,   303,    -1,    -1,   308,    -1,
     308,    -1,   289,    -1,   291,    -1,    -1,   169,     4,   296,
      -1,   298,    47,    48,    49,    50,   289,   304,   291,    15,
      38,    39,    40,   333,    20,   345,   336,    -1,   348,    -1,
      -1,   344,    -1,    29,    30,   345,    -1,   345,   348,    35,
     348,   203,   352,   353,    -1,   355,   333,    -1,    -1,   336,
     185,   186,   187,   188,   289,    -1,   291,    21,    22,    23,
     333,   223,    -1,   336,    -1,   352,   353,   229,   355,    -1,
      -1,    -1,   343,    -1,   345,    -1,   347,    -1,   240,   352,
     353,     4,   355,    -1,   121,   122,    -1,    -1,   125,    -1,
      -1,   128,    15,    -1,   131,    -1,    -1,    20,   333,    -1,
      -1,   336,    -1,     3,    -1,    -1,    29,    30,    -1,   146,
     147,    -1,    35,    -1,    -1,     4,    -1,   352,   353,    19,
     355,    -1,    -1,    23,    24,    25,    15,    -1,    -1,    29,
      30,    20,   169,    33,   296,    35,   298,   174,    -1,    -1,
      29,    -1,   304,    -1,    -1,    -1,    35,   179,   180,   181,
     182,    -1,   189,   190,    -1,    -1,   193,     3,     4,     5,
       6,     7,     8,    -1,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    -1,    20,    -1,     3,    -1,    -1,   216,
     217,    -1,    -1,    29,    -1,    31,    32,    33,   225,    35,
      36,    37,    19,     3,   231,    -1,    42,    24,    25,   236,
     237,    -1,    29,    -1,   241,   242,    33,    -1,    35,    19,
      -1,   248,   249,    -1,    24,    25,    -1,    -1,    -1,    29,
      -1,    -1,    -1,    33,    -1,    35,    -1,     3,     4,     5,
       6,     7,     8,    -1,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    -1,    20,    -1,   283,   284,    -1,   286,
     287,    -1,   289,    29,   291,    31,    32,    33,   295,    35,
      36,    37,   179,   180,   181,   182,    42,    -1,     3,     4,
       5,     6,     7,     8,    -1,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    -1,    20,    -1,    -1,   325,   185,
     186,   187,   188,    -1,    29,    -1,    31,    -1,    33,   336,
      35,    36,    37,    -1,   341,   342,    -1,    42,     3,     4,
       5,     6,     7,     8,    -1,   352,    11,    -1,    -1,    -1,
      15,    19,    17,    18,    -1,    20,    24,    25,    -1,    -1,
      -1,    29,    -1,    28,    29,    33,    31,    35,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    42,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      15,    19,    17,    18,    -1,    20,    24,    25,    -1,    -1,
      -1,    29,    -1,    28,    29,    33,    31,    35,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    42,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      15,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    -1,    31,    -1,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    42,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      15,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    31,    -1,    33,    -1,
      35,    36,    37,    -1,    -1,    -1,    -1,    42,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      15,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    31,    -1,    33,    -1,
      35,    36,    37,    -1,    -1,    -1,    -1,    42,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      15,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    31,    -1,    33,    -1,
      35,    36,    37,    -1,    -1,    -1,    -1,    42,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      15,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    31,    -1,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    42,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      15,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    31,    -1,    33,    -1,
      35,    36,    37,    -1,    -1,    -1,    -1,    42,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      15,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    31,    -1,    33,    -1,
      35,    36,    37,    -1,    -1,    -1,    -1,    42,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      15,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    -1,    31,    -1,    33,    -1,
      35,    36,    37,    -1,    -1,    -1,    -1,    42,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      15,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    31,    -1,    33,    -1,
      35,    36,    37,    -1,    -1,    -1,    -1,    42,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      15,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    31,    -1,    33,    -1,
      35,    36,    37,    -1,    -1,    -1,    -1,    42,     3,     4,
       5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,    -1,
      15,    -1,    17,    18,    -1,    20,    -1,    -1,     4,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    31,    -1,    33,    15,
      35,    36,    37,    -1,    20,    -1,    -1,    42,     3,     4,
       5,     6,     7,    29,    -1,    -1,    14,    -1,    -1,    35,
      15,    19,    17,    18,    -1,    20,    24,    25,    -1,    -1,
      -1,    29,    -1,    -1,    29,    33,    31,    35,    33,    -1,
      35,    36,    37,    -1,    -1,    -1,    -1,    42,     3,     4,
       5,     6,     7,     8,    -1,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    14,    -1,    29,    -1,    31,    19,    33,    -1,
      35,    23,    24,    25,    -1,    -1,    -1,    29,    30,    -1,
      19,    33,    -1,    35,    23,    24,    25,    -1,    -1,    -1,
      29,    30,    -1,    -1,    33,    -1,    35
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     1,     3,     4,     5,     6,     7,     8,    10,    11,
      12,    13,    15,    16,    17,    18,    20,    29,    31,    33,
      35,    36,    37,    42,    51,    53,    54,    55,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    94,    99,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     162,    29,    99,    99,    29,    92,    99,    84,    33,     8,
      11,    29,    54,    58,    69,    82,   100,    30,    54,    55,
      58,   157,   158,   161,    32,   162,    28,    29,    34,    57,
      58,    96,    97,    98,   160,    36,    37,    42,    68,    79,
      68,    79,    68,    79,     0,    14,    19,    24,    25,    33,
      81,    82,    99,   101,    21,    44,    43,    45,    46,    47,
      48,    49,    50,    36,    37,    38,    39,    40,    41,    29,
      33,    99,   100,    21,    14,    29,    81,    82,   101,    22,
      58,    60,    59,    29,    54,    55,    56,    82,    92,    95,
     159,    58,    60,    59,    21,    58,    99,    92,    30,    54,
      23,    30,   101,    23,    30,    23,    30,    23,    30,    23,
      30,    23,    30,    22,    32,    58,    26,    23,    34,    54,
      29,    91,    93,    20,    34,    54,    55,    58,    91,    93,
      58,    62,    72,    63,    73,    64,    74,    64,    74,    65,
      75,    65,    75,    65,    75,    65,    75,    66,    76,    66,
      76,    67,    77,    67,    77,    67,    77,    67,    77,    30,
      34,   160,    58,    91,    93,    54,    91,    93,    59,     9,
      22,     9,    22,    54,    55,    24,    23,    30,    23,    30,
      54,    34,    58,    54,    29,    55,    58,    30,    54,    30,
      55,    30,    58,    32,    58,    34,    57,    30,    58,    58,
      34,    34,    34,    58,    58,    23,    34,    58,    58,    58,
      58,    58,    60,     9,    58,    60,     9,    58,    56,    30,
      56,     9,    27,     8,    11,    54,    60,    69,    82,    58,
      60,    58,    99,    92,    58,     9
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    52,    53,    53,    53,    53,    53,    55,    55,    56,
      56,    57,    57,    57,    57,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    58,    58,    59,    59,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    61,    61,
      71,    71,    62,    62,    72,    72,    63,    63,    63,    73,
      73,    73,    64,    64,    64,    64,    64,    74,    74,    74,
      74,    74,    65,    65,    65,    75,    75,    75,    66,    66,
      66,    66,    76,    76,    76,    76,    67,    67,    77,    77,
      68,    68,    68,    68,    78,    78,    78,    78,    69,    69,
      69,    69,    70,    70,    70,    70,    70,    70,    70,    70,
      79,    79,    79,    80,    81,    81,    81,    82,    82,    83,
      84,    85,    86,    87,    88,    88,    88,    88,    89,    89,
      89,    89,    90,    92,    92,    92,    91,    91,    91,    93,
      94,    95,    96,    97,    98,    99,    99,    99,   100,   101,
     102,   102,   102,   103,   103,   104,   105,   106,   107,   107,
     107,   107,   108,   108,   108,   109,   126,   110,   127,   111,
     128,   112,   129,   113,   130,   114,   131,   115,   132,   116,
     133,   117,   134,   118,   135,   119,   136,   120,   137,   121,
     138,   122,   139,   124,   141,   123,   140,   125,   142,   143,
     143,   144,   145,   145,   146,   147,   148,   149,   151,   150,
     150,   150,   150,   152,   152,   152,   153,   153,   153,   153,
     153,   153,   154,   155,   156,   160,   160,   162,   162,   157,
     157,   161,   161,   158,   158,   159,   159
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     4,     2,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     2,     4,     4,
       3,     4,     4,     3,     3,     4,     3,     3,     4,     2,
       2,     3,     3,     5,     2,     3,     3,     4,     2,     1,
       2,     3,     4,     1,     1,     1,     1,     1,     4,     4,
       4,     4,     2,     3,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     4,     3,     5,     3,     3,     3,     4,     4,
       4,     4,     4,     2,     2,     1,     5,     6,     5,     6,
       5,     6,     3,     3,     3,     1,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3
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
  "expr_or_right", "expr_and_right", "expr_eq_right", "expr_ord_right",
  "expr_add_right", "expr_mul_right", "expr_pow_right", "expr_pre_right",
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
  "node_minus", "node_not", "node_or_right", "node_and_right",
  "node_eq_right", "node_ne_right", "node_ge_right", "node_le_right",
  "node_gt_right", "node_lt_right", "node_add_right", "node_sub_right",
  "node_mul_right", "node_div_right", "node_mod_right", "node_pow_right",
  "node_plus_right", "node_minus_right", "node_not_right",
  "node_application", "node_conversion", "node_subscript", "node_expr_if",
  "node_expr_for", "node_definition", "node_assignment",
  "node_function_def", "node_type_def", "node_return", "node_if",
  "node_when", "node_for", "node_while", "type_list", "decl_list",
  "range_decl_list", "array_elem_list", "expr_list", "stmt_list", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   231,   231,   235,   239,   243,   248,   256,   257,   260,
     261,   264,   265,   266,   267,   270,   271,   272,   273,   274,
     278,   279,   280,   281,   284,   285,   288,   289,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   306,   307,
     310,   311,   314,   315,   318,   319,   322,   323,   324,   327,
     328,   329,   332,   333,   334,   335,   336,   339,   340,   341,
     342,   343,   346,   347,   348,   351,   352,   353,   356,   357,
     358,   359,   362,   363,   364,   365,   368,   369,   372,   373,
     376,   377,   378,   379,   382,   383,   384,   385,   388,   389,
     390,   391,   394,   395,   396,   397,   398,   399,   400,   401,
     404,   405,   406,   409,   414,   417,   420,   425,   428,   433,
     438,   443,   448,   453,   458,   461,   464,   467,   472,   475,
     478,   481,   486,   500,   503,   506,   511,   514,   517,   522,
     527,   532,   539,   544,   549,   556,   559,   562,   567,   572,
     577,   580,   583,   590,   593,   598,   603,   608,   613,   616,
     619,   622,   627,   630,   633,   640,   645,   650,   655,   660,
     665,   670,   675,   680,   685,   690,   695,   700,   705,   710,
     715,   720,   725,   730,   735,   740,   745,   750,   755,   760,
     765,   770,   775,   780,   785,   790,   795,   800,   805,   810,
     813,   818,   823,   826,   831,   836,   843,   848,   853,   858,
     861,   864,   867,   872,   875,   878,   883,   886,   889,   892,
     895,   898,   903,   908,   913,   920,   923,   928,   931,   936,
     939,   944,   947,   952,   955,   960,   963
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
#line 4440 "src/parser.cpp"

#line 967 "gen/parser.y"


void yy::parser::error (std::string const & msg) {
    std::cerr << "parser error: " << msg << '\n';
}
