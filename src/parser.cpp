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
      case symbol_kind::S_expressible: // expressible
        value.YY_MOVE_OR_COPY< cynth::ast::category::Expressible > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_pure: // pure
        value.YY_MOVE_OR_COPY< cynth::ast::category::Statement > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
        value.YY_MOVE_OR_COPY< cynth::ast::category::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_alias: // alias
        value.YY_MOVE_OR_COPY< cynth::ast::node::Alias > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.YY_MOVE_OR_COPY< cynth::ast::node::Assignment > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_auto: // auto
        value.YY_MOVE_OR_COPY< cynth::ast::node::Auto > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< cynth::ast::node::Block > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decimal: // decimal
        value.YY_MOVE_OR_COPY< cynth::ast::node::Decimal > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.YY_MOVE_OR_COPY< cynth::ast::node::Declaration > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
        value.YY_MOVE_OR_COPY< cynth::ast::node::Definition > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_if: // expr_if
        value.YY_MOVE_OR_COPY< cynth::ast::node::ExprIf > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_type: // function_type
        value.YY_MOVE_OR_COPY< cynth::ast::node::FunctionType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if: // if
        value.YY_MOVE_OR_COPY< cynth::ast::node::If > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_integer: // integer
        value.YY_MOVE_OR_COPY< cynth::ast::node::Integer > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_name: // name
        value.YY_MOVE_OR_COPY< cynth::ast::node::Name > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_return: // return
        value.YY_MOVE_OR_COPY< cynth::ast::node::Return > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_string: // string
        value.YY_MOVE_OR_COPY< cynth::ast::node::String > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tuple_type: // tuple_type
        value.YY_MOVE_OR_COPY< cynth::ast::node::TupleType > (YY_MOVE (that.value));
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

      case symbol_kind::S_block_list: // block_list
        value.YY_MOVE_OR_COPY< std::vector<cynth::ast::category::Statement *> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_type_list: // function_type_list
      case symbol_kind::S_tuple_type_list: // tuple_type_list
        value.YY_MOVE_OR_COPY< std::vector<cynth::ast::category::Type      *> > (YY_MOVE (that.value));
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
      case symbol_kind::S_expressible: // expressible
        value.move< cynth::ast::category::Expressible > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_pure: // pure
        value.move< cynth::ast::category::Statement > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
        value.move< cynth::ast::category::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_alias: // alias
        value.move< cynth::ast::node::Alias > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< cynth::ast::node::Assignment > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_auto: // auto
        value.move< cynth::ast::node::Auto > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.move< cynth::ast::node::Block > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decimal: // decimal
        value.move< cynth::ast::node::Decimal > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< cynth::ast::node::Declaration > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
        value.move< cynth::ast::node::Definition > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_if: // expr_if
        value.move< cynth::ast::node::ExprIf > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_type: // function_type
        value.move< cynth::ast::node::FunctionType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if: // if
        value.move< cynth::ast::node::If > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_integer: // integer
        value.move< cynth::ast::node::Integer > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_name: // name
        value.move< cynth::ast::node::Name > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_return: // return
        value.move< cynth::ast::node::Return > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_string: // string
        value.move< cynth::ast::node::String > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tuple_type: // tuple_type
        value.move< cynth::ast::node::TupleType > (YY_MOVE (that.value));
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

      case symbol_kind::S_block_list: // block_list
        value.move< std::vector<cynth::ast::category::Statement *> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_type_list: // function_type_list
      case symbol_kind::S_tuple_type_list: // tuple_type_list
        value.move< std::vector<cynth::ast::category::Type      *> > (YY_MOVE (that.value));
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
      case symbol_kind::S_expressible: // expressible
        value.copy< cynth::ast::category::Expressible > (that.value);
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_pure: // pure
        value.copy< cynth::ast::category::Statement > (that.value);
        break;

      case symbol_kind::S_type: // type
        value.copy< cynth::ast::category::Type > (that.value);
        break;

      case symbol_kind::S_alias: // alias
        value.copy< cynth::ast::node::Alias > (that.value);
        break;

      case symbol_kind::S_assignment: // assignment
        value.copy< cynth::ast::node::Assignment > (that.value);
        break;

      case symbol_kind::S_auto: // auto
        value.copy< cynth::ast::node::Auto > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.copy< cynth::ast::node::Block > (that.value);
        break;

      case symbol_kind::S_decimal: // decimal
        value.copy< cynth::ast::node::Decimal > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.copy< cynth::ast::node::Declaration > (that.value);
        break;

      case symbol_kind::S_definition: // definition
        value.copy< cynth::ast::node::Definition > (that.value);
        break;

      case symbol_kind::S_expr_if: // expr_if
        value.copy< cynth::ast::node::ExprIf > (that.value);
        break;

      case symbol_kind::S_function_type: // function_type
        value.copy< cynth::ast::node::FunctionType > (that.value);
        break;

      case symbol_kind::S_if: // if
        value.copy< cynth::ast::node::If > (that.value);
        break;

      case symbol_kind::S_integer: // integer
        value.copy< cynth::ast::node::Integer > (that.value);
        break;

      case symbol_kind::S_name: // name
        value.copy< cynth::ast::node::Name > (that.value);
        break;

      case symbol_kind::S_return: // return
        value.copy< cynth::ast::node::Return > (that.value);
        break;

      case symbol_kind::S_string: // string
        value.copy< cynth::ast::node::String > (that.value);
        break;

      case symbol_kind::S_tuple_type: // tuple_type
        value.copy< cynth::ast::node::TupleType > (that.value);
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

      case symbol_kind::S_block_list: // block_list
        value.copy< std::vector<cynth::ast::category::Statement *> > (that.value);
        break;

      case symbol_kind::S_function_type_list: // function_type_list
      case symbol_kind::S_tuple_type_list: // tuple_type_list
        value.copy< std::vector<cynth::ast::category::Type      *> > (that.value);
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
      case symbol_kind::S_expressible: // expressible
        value.move< cynth::ast::category::Expressible > (that.value);
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_pure: // pure
        value.move< cynth::ast::category::Statement > (that.value);
        break;

      case symbol_kind::S_type: // type
        value.move< cynth::ast::category::Type > (that.value);
        break;

      case symbol_kind::S_alias: // alias
        value.move< cynth::ast::node::Alias > (that.value);
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< cynth::ast::node::Assignment > (that.value);
        break;

      case symbol_kind::S_auto: // auto
        value.move< cynth::ast::node::Auto > (that.value);
        break;

      case symbol_kind::S_block: // block
        value.move< cynth::ast::node::Block > (that.value);
        break;

      case symbol_kind::S_decimal: // decimal
        value.move< cynth::ast::node::Decimal > (that.value);
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< cynth::ast::node::Declaration > (that.value);
        break;

      case symbol_kind::S_definition: // definition
        value.move< cynth::ast::node::Definition > (that.value);
        break;

      case symbol_kind::S_expr_if: // expr_if
        value.move< cynth::ast::node::ExprIf > (that.value);
        break;

      case symbol_kind::S_function_type: // function_type
        value.move< cynth::ast::node::FunctionType > (that.value);
        break;

      case symbol_kind::S_if: // if
        value.move< cynth::ast::node::If > (that.value);
        break;

      case symbol_kind::S_integer: // integer
        value.move< cynth::ast::node::Integer > (that.value);
        break;

      case symbol_kind::S_name: // name
        value.move< cynth::ast::node::Name > (that.value);
        break;

      case symbol_kind::S_return: // return
        value.move< cynth::ast::node::Return > (that.value);
        break;

      case symbol_kind::S_string: // string
        value.move< cynth::ast::node::String > (that.value);
        break;

      case symbol_kind::S_tuple_type: // tuple_type
        value.move< cynth::ast::node::TupleType > (that.value);
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

      case symbol_kind::S_block_list: // block_list
        value.move< std::vector<cynth::ast::category::Statement *> > (that.value);
        break;

      case symbol_kind::S_function_type_list: // function_type_list
      case symbol_kind::S_tuple_type_list: // tuple_type_list
        value.move< std::vector<cynth::ast::category::Type      *> > (that.value);
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
      case symbol_kind::S_expressible: // expressible
        yylhs.value.emplace< cynth::ast::category::Expressible > ();
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_pure: // pure
        yylhs.value.emplace< cynth::ast::category::Statement > ();
        break;

      case symbol_kind::S_type: // type
        yylhs.value.emplace< cynth::ast::category::Type > ();
        break;

      case symbol_kind::S_alias: // alias
        yylhs.value.emplace< cynth::ast::node::Alias > ();
        break;

      case symbol_kind::S_assignment: // assignment
        yylhs.value.emplace< cynth::ast::node::Assignment > ();
        break;

      case symbol_kind::S_auto: // auto
        yylhs.value.emplace< cynth::ast::node::Auto > ();
        break;

      case symbol_kind::S_block: // block
        yylhs.value.emplace< cynth::ast::node::Block > ();
        break;

      case symbol_kind::S_decimal: // decimal
        yylhs.value.emplace< cynth::ast::node::Decimal > ();
        break;

      case symbol_kind::S_declaration: // declaration
        yylhs.value.emplace< cynth::ast::node::Declaration > ();
        break;

      case symbol_kind::S_definition: // definition
        yylhs.value.emplace< cynth::ast::node::Definition > ();
        break;

      case symbol_kind::S_expr_if: // expr_if
        yylhs.value.emplace< cynth::ast::node::ExprIf > ();
        break;

      case symbol_kind::S_function_type: // function_type
        yylhs.value.emplace< cynth::ast::node::FunctionType > ();
        break;

      case symbol_kind::S_if: // if
        yylhs.value.emplace< cynth::ast::node::If > ();
        break;

      case symbol_kind::S_integer: // integer
        yylhs.value.emplace< cynth::ast::node::Integer > ();
        break;

      case symbol_kind::S_name: // name
        yylhs.value.emplace< cynth::ast::node::Name > ();
        break;

      case symbol_kind::S_return: // return
        yylhs.value.emplace< cynth::ast::node::Return > ();
        break;

      case symbol_kind::S_string: // string
        yylhs.value.emplace< cynth::ast::node::String > ();
        break;

      case symbol_kind::S_tuple_type: // tuple_type
        yylhs.value.emplace< cynth::ast::node::TupleType > ();
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

      case symbol_kind::S_block_list: // block_list
        yylhs.value.emplace< std::vector<cynth::ast::category::Statement *> > ();
        break;

      case symbol_kind::S_function_type_list: // function_type_list
      case symbol_kind::S_tuple_type_list: // tuple_type_list
        yylhs.value.emplace< std::vector<cynth::ast::category::Type      *> > ();
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
  case 2: // start: block_list
#line 100 "gen/parser.y"
                    { result = node::Block{YY_MOVE (yystack_[0].value.as < std::vector<cynth::ast::category::Statement *> > ())}; }
#line 1009 "src/parser.cpp"
    break;

  case 3: // start: block_list SEMI
#line 101 "gen/parser.y"
                    { result = node::Block{YY_MOVE (yystack_[1].value.as < std::vector<cynth::ast::category::Statement *> > ())}; }
#line 1015 "src/parser.cpp"
    break;

  case 4: // type: type_name
#line 104 "gen/parser.y"
                  { yylhs.value.as < cynth::ast::category::Type > () = category::Type{YY_MOVE (yystack_[0].value.as < cynth::ast::node::TypeName > ())}; }
#line 1021 "src/parser.cpp"
    break;

  case 5: // type: auto
#line 105 "gen/parser.y"
                  { yylhs.value.as < cynth::ast::category::Type > () = category::Type{YY_MOVE (yystack_[0].value.as < cynth::ast::node::Auto > ())}; }
#line 1027 "src/parser.cpp"
    break;

  case 6: // type: function_type
#line 106 "gen/parser.y"
                  { yylhs.value.as < cynth::ast::category::Type > () = category::Type{YY_MOVE (yystack_[0].value.as < cynth::ast::node::FunctionType > ())}; }
#line 1033 "src/parser.cpp"
    break;

  case 7: // type: tuple_type
#line 107 "gen/parser.y"
                  { yylhs.value.as < cynth::ast::category::Type > () = category::Type{YY_MOVE (yystack_[0].value.as < cynth::ast::node::TupleType > ())}; }
#line 1039 "src/parser.cpp"
    break;

  case 8: // statement: expressible
#line 110 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Statement > () = category::Statement{YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expressible > ())}; }
#line 1045 "src/parser.cpp"
    break;

  case 9: // statement: pure
#line 111 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Statement > () = YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ()); }
#line 1051 "src/parser.cpp"
    break;

  case 10: // pure: declaration
#line 114 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Statement > () = category::Statement{YY_MOVE (yystack_[0].value.as < cynth::ast::node::Declaration > ())}; }
#line 1057 "src/parser.cpp"
    break;

  case 11: // pure: definition
#line 115 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Statement > () = category::Statement{YY_MOVE (yystack_[0].value.as < cynth::ast::node::Definition > ())}; }
#line 1063 "src/parser.cpp"
    break;

  case 12: // pure: assignment
#line 116 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Statement > () = category::Statement{YY_MOVE (yystack_[0].value.as < cynth::ast::node::Assignment > ())}; }
#line 1069 "src/parser.cpp"
    break;

  case 13: // pure: alias
#line 117 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Statement > () = category::Statement{YY_MOVE (yystack_[0].value.as < cynth::ast::node::Alias > ())}; }
#line 1075 "src/parser.cpp"
    break;

  case 14: // pure: return
#line 118 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Statement > () = category::Statement{YY_MOVE (yystack_[0].value.as < cynth::ast::node::Return > ())}; }
#line 1081 "src/parser.cpp"
    break;

  case 15: // pure: if
#line 119 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Statement > () = category::Statement{YY_MOVE (yystack_[0].value.as < cynth::ast::node::If > ())}; }
#line 1087 "src/parser.cpp"
    break;

  case 16: // pure: when
#line 120 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Statement > () = category::Statement{YY_MOVE (yystack_[0].value.as < cynth::ast::node::When > ())}; }
#line 1093 "src/parser.cpp"
    break;

  case 17: // expressible: OPAREN expressible CPAREN
#line 123 "gen/parser.y"
                                    { yylhs.value.as < cynth::ast::category::Expressible > () = YY_MOVE (yystack_[1].value.as < cynth::ast::category::Expressible > ()); }
#line 1099 "src/parser.cpp"
    break;

  case 18: // expressible: name
#line 124 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expressible > () = category::Expressible{YY_MOVE (yystack_[0].value.as < cynth::ast::node::Name > ())}; }
#line 1105 "src/parser.cpp"
    break;

  case 19: // expressible: block
#line 125 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expressible > () = category::Expressible{YY_MOVE (yystack_[0].value.as < cynth::ast::node::Block > ())}; }
#line 1111 "src/parser.cpp"
    break;

  case 20: // expressible: integer
#line 126 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expressible > () = category::Expressible{YY_MOVE (yystack_[0].value.as < cynth::ast::node::Integer > ())}; }
#line 1117 "src/parser.cpp"
    break;

  case 21: // expressible: decimal
#line 127 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expressible > () = category::Expressible{YY_MOVE (yystack_[0].value.as < cynth::ast::node::Decimal > ())}; }
#line 1123 "src/parser.cpp"
    break;

  case 22: // expressible: string
#line 128 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expressible > () = category::Expressible{YY_MOVE (yystack_[0].value.as < cynth::ast::node::String > ())}; }
#line 1129 "src/parser.cpp"
    break;

  case 23: // expressible: expr_if
#line 129 "gen/parser.y"
                { yylhs.value.as < cynth::ast::category::Expressible > () = category::Expressible{YY_MOVE (yystack_[0].value.as < cynth::ast::node::ExprIf > ())}; }
#line 1135 "src/parser.cpp"
    break;

  case 24: // integer: INTEGER
#line 131 "gen/parser.y"
                 {
    yylhs.value.as < cynth::ast::node::Integer > () = node::Integer{util::stoi(YY_MOVE (yystack_[0].value.as < std::string > ()))};
}
#line 1143 "src/parser.cpp"
    break;

  case 25: // decimal: DECIMAL
#line 134 "gen/parser.y"
                 {
    yylhs.value.as < cynth::ast::node::Decimal > () = node::Decimal{std::stof(YY_MOVE (yystack_[0].value.as < std::string > ()))};
}
#line 1151 "src/parser.cpp"
    break;

  case 26: // string: STRING
#line 137 "gen/parser.y"
               {
    yylhs.value.as < cynth::ast::node::String > () = node::String{util::trim(YY_MOVE (yystack_[0].value.as < std::string > ()))};
}
#line 1159 "src/parser.cpp"
    break;

  case 27: // name: NAME
#line 140 "gen/parser.y"
           {
    yylhs.value.as < cynth::ast::node::Name > () = node::Name{YY_MOVE (yystack_[0].value.as < std::string > ())};
}
#line 1167 "src/parser.cpp"
    break;

  case 28: // auto: AUTO
#line 144 "gen/parser.y"
           {
    yylhs.value.as < cynth::ast::node::Auto > () = node::Auto{};
}
#line 1175 "src/parser.cpp"
    break;

  case 29: // type_name: TYPENAME
#line 147 "gen/parser.y"
                    {
    yylhs.value.as < cynth::ast::node::TypeName > () = node::TypeName{YY_MOVE (yystack_[0].value.as < std::string > ())};
}
#line 1183 "src/parser.cpp"
    break;

  case 30: // function_type: type OPAREN function_type_list CPAREN
#line 151 "gen/parser.y"
                                                             { yylhs.value.as < cynth::ast::node::FunctionType > () = node::FunctionType{alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ())), YY_MOVE (yystack_[1].value.as < std::vector<cynth::ast::category::Type      *> > ())}; }
#line 1189 "src/parser.cpp"
    break;

  case 31: // function_type: type OPAREN function_type_list COMMA CPAREN
#line 152 "gen/parser.y"
                                                             { yylhs.value.as < cynth::ast::node::FunctionType > () = node::FunctionType{alloc(YY_MOVE (yystack_[4].value.as < cynth::ast::category::Type > ())), YY_MOVE (yystack_[2].value.as < std::vector<cynth::ast::category::Type      *> > ())}; }
#line 1195 "src/parser.cpp"
    break;

  case 32: // function_type_list: %empty
#line 154 "gen/parser.y"
           {
        yylhs.value.as < std::vector<cynth::ast::category::Type      *> > () = {};
    }
#line 1203 "src/parser.cpp"
    break;

  case 33: // function_type_list: type
#line 157 "gen/parser.y"
         {
        yylhs.value.as < std::vector<cynth::ast::category::Type      *> > () = {alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()))};
    }
#line 1211 "src/parser.cpp"
    break;

  case 34: // function_type_list: function_type_list COMMA type
#line 160 "gen/parser.y"
                                        {
        auto rest = YY_MOVE (yystack_[2].value.as < std::vector<cynth::ast::category::Type      *> > ());
        yylhs.value.as < std::vector<cynth::ast::category::Type      *> > () = util::push(alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())), rest);
    }
#line 1220 "src/parser.cpp"
    break;

  case 35: // tuple_type: OPAREN tuple_type_list CPAREN
#line 165 "gen/parser.y"
                                              { yylhs.value.as < cynth::ast::node::TupleType > () = node::TupleType{YY_MOVE (yystack_[1].value.as < std::vector<cynth::ast::category::Type      *> > ())}; }
#line 1226 "src/parser.cpp"
    break;

  case 36: // tuple_type: OPAREN tuple_type_list COMMA CPAREN
#line 166 "gen/parser.y"
                                              { yylhs.value.as < cynth::ast::node::TupleType > () = node::TupleType{YY_MOVE (yystack_[2].value.as < std::vector<cynth::ast::category::Type      *> > ())}; }
#line 1232 "src/parser.cpp"
    break;

  case 37: // tuple_type_list: %empty
#line 168 "gen/parser.y"
           {
        yylhs.value.as < std::vector<cynth::ast::category::Type      *> > () = {};
    }
#line 1240 "src/parser.cpp"
    break;

  case 38: // tuple_type_list: type
#line 171 "gen/parser.y"
         {
        yylhs.value.as < std::vector<cynth::ast::category::Type      *> > () = {alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()))};
    }
#line 1248 "src/parser.cpp"
    break;

  case 39: // tuple_type_list: tuple_type_list COMMA type
#line 174 "gen/parser.y"
                                     {
        auto rest = YY_MOVE (yystack_[2].value.as < std::vector<cynth::ast::category::Type      *> > ());
        yylhs.value.as < std::vector<cynth::ast::category::Type      *> > () = util::push(alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ())), rest);
    }
#line 1257 "src/parser.cpp"
    break;

  case 40: // declaration: type name
#line 179 "gen/parser.y"
                       {
    yylhs.value.as < cynth::ast::node::Declaration > () = node::Declaration{alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::node::Name > ())), alloc(YY_MOVE (yystack_[1].value.as < cynth::ast::category::Type > ()))};
}
#line 1265 "src/parser.cpp"
    break;

  case 41: // definition: type name ASGN expressible
#line 182 "gen/parser.y"
                                       {
    yylhs.value.as < cynth::ast::node::Definition > () = node::Definition{alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ())), alloc(YY_MOVE (yystack_[3].value.as < cynth::ast::category::Type > ())), alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expressible > ()))};
}
#line 1273 "src/parser.cpp"
    break;

  case 42: // assignment: name ASGN expressible
#line 185 "gen/parser.y"
                                  {
    yylhs.value.as < cynth::ast::node::Assignment > () = node::Assignment{alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::node::Name > ())), alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expressible > ()))};
}
#line 1281 "src/parser.cpp"
    break;

  case 43: // alias: TYPE type_name ASGN type
#line 188 "gen/parser.y"
                                {
    yylhs.value.as < cynth::ast::node::Alias > () = node::Alias{alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::node::TypeName > ())), alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Type > ()))};
}
#line 1289 "src/parser.cpp"
    break;

  case 44: // return: RETURN expressible
#line 192 "gen/parser.y"
                           {
    yylhs.value.as < cynth::ast::node::Return > () = node::Return{alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expressible > ()))};
}
#line 1297 "src/parser.cpp"
    break;

  case 45: // block: OBRACE block_list CBRACE
#line 196 "gen/parser.y"
                                  { yylhs.value.as < cynth::ast::node::Block > () = node::Block{YY_MOVE (yystack_[1].value.as < std::vector<cynth::ast::category::Statement *> > ())}; }
#line 1303 "src/parser.cpp"
    break;

  case 46: // block: OBRACE block_list SEMI CBRACE
#line 197 "gen/parser.y"
                                  { yylhs.value.as < cynth::ast::node::Block > () = node::Block{YY_MOVE (yystack_[2].value.as < std::vector<cynth::ast::category::Statement *> > ())}; }
#line 1309 "src/parser.cpp"
    break;

  case 47: // block_list: %empty
#line 199 "gen/parser.y"
           {
        yylhs.value.as < std::vector<cynth::ast::category::Statement *> > () = {};
    }
#line 1317 "src/parser.cpp"
    break;

  case 48: // block_list: statement
#line 202 "gen/parser.y"
              {
        yylhs.value.as < std::vector<cynth::ast::category::Statement *> > () = {alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ()))};
    }
#line 1325 "src/parser.cpp"
    break;

  case 49: // block_list: block_list SEMI statement
#line 205 "gen/parser.y"
                                    {
        auto rest = YY_MOVE (yystack_[2].value.as < std::vector<cynth::ast::category::Statement *> > ());
        yylhs.value.as < std::vector<cynth::ast::category::Statement *> > () = util::push(alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ())), rest);
    }
#line 1334 "src/parser.cpp"
    break;

  case 50: // if: IF OPAREN expressible CPAREN pure ELSE pure
#line 210 "gen/parser.y"
                                                                {
    yylhs.value.as < cynth::ast::node::If > () = node::If{alloc(YY_MOVE (yystack_[4].value.as < cynth::ast::category::Expressible > ())), alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Statement > ())), alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ()))};
}
#line 1342 "src/parser.cpp"
    break;

  case 51: // expr_if: IF OPAREN expressible CPAREN expressible ELSE expressible
#line 213 "gen/parser.y"
                                                                                   {
    yylhs.value.as < cynth::ast::node::ExprIf > () = node::ExprIf{alloc(YY_MOVE (yystack_[4].value.as < cynth::ast::category::Expressible > ())), alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expressible > ())), alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Expressible > ()))};
}
#line 1350 "src/parser.cpp"
    break;

  case 52: // when: WHEN OPAREN expressible CPAREN statement
#line 216 "gen/parser.y"
                                                          {
    yylhs.value.as < cynth::ast::node::When > () = node::When{alloc(YY_MOVE (yystack_[2].value.as < cynth::ast::category::Expressible > ())), alloc(YY_MOVE (yystack_[0].value.as < cynth::ast::category::Statement > ()))};
}
#line 1358 "src/parser.cpp"
    break;


#line 1362 "src/parser.cpp"

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





  const signed char parser::yypact_ninf_ = -63;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
      97,   -63,   -63,   -63,   -63,   -63,   -11,    -4,    16,   -63,
      31,   111,    97,    23,     5,   -63,   -63,   -63,   -63,   -63,
     -63,    14,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,
     -63,   -63,   -63,   -63,   -63,    25,    31,    31,    15,    28,
      31,   -63,   -63,    34,    35,    10,    -8,   -63,    12,    39,
      31,    97,    37,    44,    12,    31,   -63,   -63,     3,   -63,
      82,    12,    34,    20,    31,   -63,   -63,    97,    97,    34,
      46,   -63,    34,   -63,   -63,    50,   -63,    54,    57,   -63,
      31,   -63,    34,    31,   118,   -63,    55,   -63,    14,    31,
      58,   118
  };

  const signed char
  parser::yydefact_[] =
  {
      47,    27,    29,    24,    25,    26,     0,     0,     0,    28,
       0,    37,    47,     0,     0,     8,    48,     9,    20,    21,
      22,    18,     4,     6,     7,     5,    10,    11,    12,    13,
      14,    19,    15,    23,    16,     2,     0,     0,     0,     0,
       0,    44,    18,    38,     0,     0,     0,     1,    32,    40,
       0,     3,     0,     0,     0,     0,    17,    35,     0,    45,
       0,    37,    33,     0,     0,    42,    49,     0,     0,    43,
       0,    36,    39,    46,    30,     0,    41,     0,     0,    52,
       0,    31,    34,     0,     0,    51,     0,    50,     0,     0,
       0,     0
  };

  const signed char
  parser::yypgoto_[] =
  {
     -63,   -63,    -5,    -9,   -47,   -62,   -63,   -63,   -63,     0,
      64,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,
     -63,   -63,   -63,    63,   -63,   -63
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    42,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    63,    45
  };

  const signed char
  parser::yytable_[] =
  {
      21,    41,    44,    36,    66,    78,    43,     2,     1,    59,
      37,    60,    21,    66,    49,     9,     2,    61,    71,    48,
       2,    79,    87,    47,     9,    57,    61,    52,    53,    78,
      58,    44,    50,    54,     1,    74,     3,     4,     5,    39,
      75,    65,    55,    62,    51,    40,    70,    12,    48,    69,
      56,    21,    67,    72,     2,    76,    43,    64,    77,    68,
      21,    80,     9,    83,    61,    81,    84,    21,    21,    89,
      82,    77,    38,    91,    85,    46,     0,     0,     0,     0,
      90,     0,     0,     0,    88,     1,     2,     3,     4,     5,
       6,    88,     7,     8,     9,    10,    11,     0,    12,    73,
       1,     2,     3,     4,     5,     6,     0,     7,     8,     9,
      10,    11,     0,    12,     1,     2,     3,     4,     5,    39,
       0,     1,     2,     9,     0,    11,    86,    12,     7,     8,
       9,    10,    61
  };

  const signed char
  parser::yycheck_[] =
  {
       0,    10,    11,    14,    51,    67,    11,     4,     3,    17,
      14,    19,    12,    60,    14,    12,     4,    14,    15,    14,
       4,    68,    84,     0,    12,    15,    14,    36,    37,    91,
      20,    40,    18,    18,     3,    15,     5,     6,     7,     8,
      20,    50,    14,    48,    19,    14,    55,    16,    14,    54,
      15,    51,    15,    58,     4,    64,    61,    18,    67,    15,
      60,    15,    12,     9,    14,    15,     9,    67,    68,    14,
      75,    80,     8,    15,    83,    12,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    -1,    84,     3,     4,     5,     6,     7,
       8,    91,    10,    11,    12,    13,    14,    -1,    16,    17,
       3,     4,     5,     6,     7,     8,    -1,    10,    11,    12,
      13,    14,    -1,    16,     3,     4,     5,     6,     7,     8,
      -1,     3,     4,    12,    -1,    14,     8,    16,    10,    11,
      12,    13,    14
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,     8,    10,    11,    12,
      13,    14,    16,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    14,    14,    31,     8,
      14,    24,    30,    23,    24,    46,    44,     0,    14,    30,
      18,    19,    24,    24,    18,    14,    15,    15,    20,    17,
      19,    14,    23,    45,    18,    24,    25,    15,    15,    23,
      24,    15,    23,    17,    15,    20,    24,    24,    26,    25,
      15,    15,    23,     9,     9,    24,     8,    26,    30,    14,
      24,    15
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    21,    22,    22,    23,    23,    23,    23,    25,    25,
      26,    26,    26,    26,    26,    26,    26,    24,    24,    24,
      24,    24,    24,    24,    27,    28,    29,    30,    34,    31,
      32,    32,    45,    45,    45,    33,    33,    46,    46,    46,
      35,    36,    37,    38,    39,    40,    40,    44,    44,    44,
      41,    42,    43
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     5,     0,     1,     3,     3,     4,     0,     1,     3,
       2,     4,     3,     4,     2,     3,     4,     0,     1,     3,
       7,     7,     5
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "NAME", "TYPENAME",
  "INTEGER", "DECIMAL", "STRING", "IF", "ELSE", "WHEN", "TYPE", "AUTO",
  "RETURN", "OPAREN", "CPAREN", "OBRACE", "CBRACE", "ASGN", "SEMI",
  "COMMA", "$accept", "start", "type", "expressible", "statement", "pure",
  "integer", "decimal", "string", "name", "type_name", "function_type",
  "tuple_type", "auto", "declaration", "definition", "assignment", "alias",
  "return", "block", "if", "expr_if", "when", "block_list",
  "function_type_list", "tuple_type_list", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   100,   100,   101,   104,   105,   106,   107,   110,   111,
     114,   115,   116,   117,   118,   119,   120,   123,   124,   125,
     126,   127,   128,   129,   131,   134,   137,   140,   144,   147,
     151,   152,   154,   157,   160,   165,   166,   168,   171,   174,
     179,   182,   185,   188,   192,   196,   197,   199,   202,   205,
     210,   213,   216
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
#line 1732 "src/parser.cpp"

#line 220 "gen/parser.y"


void yy::parser::error (std::string const & msg) {
    std::cerr << msg << '\n';
}
