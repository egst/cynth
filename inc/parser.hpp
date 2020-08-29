// A Bison parser, made by GNU Bison 3.7.1.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file src/parser.hpp
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_SRC_PARSER_HPP_INCLUDED
# define YY_YY_SRC_PARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 1 "gen/parser.y"

    #include "ast.hpp"
    #include "util.hpp"

    #include <string>
    #include <utility>
    #include <type_traits>

    using namespace cynth;
    using namespace cynth::ast;

    template <typename t>
    t * alloc (t && x) {
        return new t{std::forward<t>(x)};
    }

#line 66 "src/parser.hpp"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif


#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

namespace yy {
#line 200 "src/parser.hpp"




  /// A Bison parser.
  class parser
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    semantic_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    semantic_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // expressible
      char dummy1[sizeof (cynth::ast::category::Expressible)];

      // statement
      // pure
      char dummy2[sizeof (cynth::ast::category::Statement)];

      // type
      char dummy3[sizeof (cynth::ast::category::Type)];

      // alias
      char dummy4[sizeof (cynth::ast::node::Alias)];

      // assignment
      char dummy5[sizeof (cynth::ast::node::Assignment)];

      // auto
      char dummy6[sizeof (cynth::ast::node::Auto)];

      // block
      char dummy7[sizeof (cynth::ast::node::Block)];

      // decimal
      char dummy8[sizeof (cynth::ast::node::Decimal)];

      // declaration
      char dummy9[sizeof (cynth::ast::node::Declaration)];

      // definition
      char dummy10[sizeof (cynth::ast::node::Definition)];

      // expr_if
      char dummy11[sizeof (cynth::ast::node::ExprIf)];

      // function_type
      char dummy12[sizeof (cynth::ast::node::FunctionType)];

      // if
      char dummy13[sizeof (cynth::ast::node::If)];

      // integer
      char dummy14[sizeof (cynth::ast::node::Integer)];

      // name
      char dummy15[sizeof (cynth::ast::node::Name)];

      // return
      char dummy16[sizeof (cynth::ast::node::Return)];

      // string
      char dummy17[sizeof (cynth::ast::node::String)];

      // tuple_type
      char dummy18[sizeof (cynth::ast::node::TupleType)];

      // type_name
      char dummy19[sizeof (cynth::ast::node::TypeName)];

      // when
      char dummy20[sizeof (cynth::ast::node::When)];

      // start
      char dummy21[sizeof (int)];

      // NAME
      // TYPENAME
      // INTEGER
      // DECIMAL
      // STRING
      char dummy22[sizeof (std::string)];

      // block_list
      char dummy23[sizeof (std::vector<cynth::ast::category::Statement *>)];

      // function_type_list
      // tuple_type_list
      char dummy24[sizeof (std::vector<cynth::ast::category::Type      *>)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    YYEOF = 0,                     // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    NAME = 258,                    // NAME
    TYPENAME = 259,                // TYPENAME
    INTEGER = 260,                 // INTEGER
    DECIMAL = 261,                 // DECIMAL
    STRING = 262,                  // STRING
    IF = 263,                      // IF
    ELSE = 264,                    // ELSE
    WHEN = 265,                    // WHEN
    TYPE = 266,                    // TYPE
    AUTO = 267,                    // AUTO
    RETURN = 268,                  // RETURN
    OPAREN = 269,                  // OPAREN
    CPAREN = 270,                  // CPAREN
    OBRACE = 271,                  // OBRACE
    CBRACE = 272,                  // CBRACE
    ASGN = 273,                    // ASGN
    SEMI = 274,                    // SEMI
    COMMA = 275                    // COMMA
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 21, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_NAME = 3,                              // NAME
        S_TYPENAME = 4,                          // TYPENAME
        S_INTEGER = 5,                           // INTEGER
        S_DECIMAL = 6,                           // DECIMAL
        S_STRING = 7,                            // STRING
        S_IF = 8,                                // IF
        S_ELSE = 9,                              // ELSE
        S_WHEN = 10,                             // WHEN
        S_TYPE = 11,                             // TYPE
        S_AUTO = 12,                             // AUTO
        S_RETURN = 13,                           // RETURN
        S_OPAREN = 14,                           // OPAREN
        S_CPAREN = 15,                           // CPAREN
        S_OBRACE = 16,                           // OBRACE
        S_CBRACE = 17,                           // CBRACE
        S_ASGN = 18,                             // ASGN
        S_SEMI = 19,                             // SEMI
        S_COMMA = 20,                            // COMMA
        S_YYACCEPT = 21,                         // $accept
        S_start = 22,                            // start
        S_type = 23,                             // type
        S_expressible = 24,                      // expressible
        S_statement = 25,                        // statement
        S_pure = 26,                             // pure
        S_integer = 27,                          // integer
        S_decimal = 28,                          // decimal
        S_string = 29,                           // string
        S_name = 30,                             // name
        S_type_name = 31,                        // type_name
        S_function_type = 32,                    // function_type
        S_tuple_type = 33,                       // tuple_type
        S_auto = 34,                             // auto
        S_declaration = 35,                      // declaration
        S_definition = 36,                       // definition
        S_assignment = 37,                       // assignment
        S_alias = 38,                            // alias
        S_return = 39,                           // return
        S_block = 40,                            // block
        S_if = 41,                               // if
        S_expr_if = 42,                          // expr_if
        S_when = 43,                             // when
        S_block_list = 44,                       // block_list
        S_function_type_list = 45,               // function_type_list
        S_tuple_type_list = 46                   // tuple_type_list
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
      {
        switch (this->kind ())
    {
      case symbol_kind::S_expressible: // expressible
        value.move< cynth::ast::category::Expressible > (std::move (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_pure: // pure
        value.move< cynth::ast::category::Statement > (std::move (that.value));
        break;

      case symbol_kind::S_type: // type
        value.move< cynth::ast::category::Type > (std::move (that.value));
        break;

      case symbol_kind::S_alias: // alias
        value.move< cynth::ast::node::Alias > (std::move (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< cynth::ast::node::Assignment > (std::move (that.value));
        break;

      case symbol_kind::S_auto: // auto
        value.move< cynth::ast::node::Auto > (std::move (that.value));
        break;

      case symbol_kind::S_block: // block
        value.move< cynth::ast::node::Block > (std::move (that.value));
        break;

      case symbol_kind::S_decimal: // decimal
        value.move< cynth::ast::node::Decimal > (std::move (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< cynth::ast::node::Declaration > (std::move (that.value));
        break;

      case symbol_kind::S_definition: // definition
        value.move< cynth::ast::node::Definition > (std::move (that.value));
        break;

      case symbol_kind::S_expr_if: // expr_if
        value.move< cynth::ast::node::ExprIf > (std::move (that.value));
        break;

      case symbol_kind::S_function_type: // function_type
        value.move< cynth::ast::node::FunctionType > (std::move (that.value));
        break;

      case symbol_kind::S_if: // if
        value.move< cynth::ast::node::If > (std::move (that.value));
        break;

      case symbol_kind::S_integer: // integer
        value.move< cynth::ast::node::Integer > (std::move (that.value));
        break;

      case symbol_kind::S_name: // name
        value.move< cynth::ast::node::Name > (std::move (that.value));
        break;

      case symbol_kind::S_return: // return
        value.move< cynth::ast::node::Return > (std::move (that.value));
        break;

      case symbol_kind::S_string: // string
        value.move< cynth::ast::node::String > (std::move (that.value));
        break;

      case symbol_kind::S_tuple_type: // tuple_type
        value.move< cynth::ast::node::TupleType > (std::move (that.value));
        break;

      case symbol_kind::S_type_name: // type_name
        value.move< cynth::ast::node::TypeName > (std::move (that.value));
        break;

      case symbol_kind::S_when: // when
        value.move< cynth::ast::node::When > (std::move (that.value));
        break;

      case symbol_kind::S_start: // start
        value.move< int > (std::move (that.value));
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_DECIMAL: // DECIMAL
      case symbol_kind::S_STRING: // STRING
        value.move< std::string > (std::move (that.value));
        break;

      case symbol_kind::S_block_list: // block_list
        value.move< std::vector<cynth::ast::category::Statement *> > (std::move (that.value));
        break;

      case symbol_kind::S_function_type_list: // function_type_list
      case symbol_kind::S_tuple_type_list: // tuple_type_list
        value.move< std::vector<cynth::ast::category::Type      *> > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#else
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::category::Expressible&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::category::Expressible& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::category::Statement&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::category::Statement& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::category::Type&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::category::Type& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::Alias&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::Alias& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::Assignment&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::Assignment& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::Auto&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::Auto& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::Block&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::Block& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::Decimal&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::Decimal& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::Declaration&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::Declaration& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::Definition&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::Definition& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::ExprIf&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::ExprIf& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::FunctionType&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::FunctionType& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::If&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::If& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::Integer&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::Integer& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::Name&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::Name& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::Return&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::Return& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::String&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::String& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::TupleType&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::TupleType& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::TypeName&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::TypeName& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::ast::node::When&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::ast::node::When& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<cynth::ast::category::Statement *>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<cynth::ast::category::Statement *>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<cynth::ast::category::Type      *>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<cynth::ast::category::Type      *>& v)
        : Base (t)
        , value (v)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_expressible: // expressible
        value.template destroy< cynth::ast::category::Expressible > ();
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_pure: // pure
        value.template destroy< cynth::ast::category::Statement > ();
        break;

      case symbol_kind::S_type: // type
        value.template destroy< cynth::ast::category::Type > ();
        break;

      case symbol_kind::S_alias: // alias
        value.template destroy< cynth::ast::node::Alias > ();
        break;

      case symbol_kind::S_assignment: // assignment
        value.template destroy< cynth::ast::node::Assignment > ();
        break;

      case symbol_kind::S_auto: // auto
        value.template destroy< cynth::ast::node::Auto > ();
        break;

      case symbol_kind::S_block: // block
        value.template destroy< cynth::ast::node::Block > ();
        break;

      case symbol_kind::S_decimal: // decimal
        value.template destroy< cynth::ast::node::Decimal > ();
        break;

      case symbol_kind::S_declaration: // declaration
        value.template destroy< cynth::ast::node::Declaration > ();
        break;

      case symbol_kind::S_definition: // definition
        value.template destroy< cynth::ast::node::Definition > ();
        break;

      case symbol_kind::S_expr_if: // expr_if
        value.template destroy< cynth::ast::node::ExprIf > ();
        break;

      case symbol_kind::S_function_type: // function_type
        value.template destroy< cynth::ast::node::FunctionType > ();
        break;

      case symbol_kind::S_if: // if
        value.template destroy< cynth::ast::node::If > ();
        break;

      case symbol_kind::S_integer: // integer
        value.template destroy< cynth::ast::node::Integer > ();
        break;

      case symbol_kind::S_name: // name
        value.template destroy< cynth::ast::node::Name > ();
        break;

      case symbol_kind::S_return: // return
        value.template destroy< cynth::ast::node::Return > ();
        break;

      case symbol_kind::S_string: // string
        value.template destroy< cynth::ast::node::String > ();
        break;

      case symbol_kind::S_tuple_type: // tuple_type
        value.template destroy< cynth::ast::node::TupleType > ();
        break;

      case symbol_kind::S_type_name: // type_name
        value.template destroy< cynth::ast::node::TypeName > ();
        break;

      case symbol_kind::S_when: // when
        value.template destroy< cynth::ast::node::When > ();
        break;

      case symbol_kind::S_start: // start
        value.template destroy< int > ();
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_DECIMAL: // DECIMAL
      case symbol_kind::S_STRING: // STRING
        value.template destroy< std::string > ();
        break;

      case symbol_kind::S_block_list: // block_list
        value.template destroy< std::vector<cynth::ast::category::Statement *> > ();
        break;

      case symbol_kind::S_function_type_list: // function_type_list
      case symbol_kind::S_tuple_type_list: // tuple_type_list
        value.template destroy< std::vector<cynth::ast::category::Type      *> > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

#if YYDEBUG || 0
      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }
#endif // #if YYDEBUG || 0


      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that);
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok)
        : super_type(token_type (tok))
      {
        YY_ASSERT (tok == token::YYEOF || tok == token::YYerror || tok == token::YYUNDEF || tok == token::IF || tok == token::ELSE || tok == token::WHEN || tok == token::TYPE || tok == token::AUTO || tok == token::RETURN || tok == token::OPAREN || tok == token::CPAREN || tok == token::OBRACE || tok == token::CBRACE || tok == token::ASGN || tok == token::SEMI || tok == token::COMMA);
      }
#else
      symbol_type (int tok)
        : super_type(token_type (tok))
      {
        YY_ASSERT (tok == token::YYEOF || tok == token::YYerror || tok == token::YYUNDEF || tok == token::IF || tok == token::ELSE || tok == token::WHEN || tok == token::TYPE || tok == token::AUTO || tok == token::RETURN || tok == token::OPAREN || tok == token::CPAREN || tok == token::OBRACE || tok == token::CBRACE || tok == token::ASGN || tok == token::SEMI || tok == token::COMMA);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v)
        : super_type(token_type (tok), std::move (v))
      {
        YY_ASSERT (tok == token::NAME || tok == token::TYPENAME || tok == token::INTEGER || tok == token::DECIMAL || tok == token::STRING);
      }
#else
      symbol_type (int tok, const std::string& v)
        : super_type(token_type (tok), v)
      {
        YY_ASSERT (tok == token::NAME || tok == token::TYPENAME || tok == token::INTEGER || tok == token::DECIMAL || tok == token::STRING);
      }
#endif
    };

    /// Build a parser object.
    parser (cynth::ast::node::Block & result_yyarg);
    virtual ~parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser (const parser&) = delete;
    /// Non copyable.
    parser& operator= (const parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

#if YYDEBUG || 0
    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);
#endif // #if YYDEBUG || 0


    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYEOF ()
      {
        return symbol_type (token::YYEOF);
      }
#else
      static
      symbol_type
      make_YYEOF ()
      {
        return symbol_type (token::YYEOF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#else
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#else
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NAME (std::string v)
      {
        return symbol_type (token::NAME, std::move (v));
      }
#else
      static
      symbol_type
      make_NAME (const std::string& v)
      {
        return symbol_type (token::NAME, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TYPENAME (std::string v)
      {
        return symbol_type (token::TYPENAME, std::move (v));
      }
#else
      static
      symbol_type
      make_TYPENAME (const std::string& v)
      {
        return symbol_type (token::TYPENAME, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTEGER (std::string v)
      {
        return symbol_type (token::INTEGER, std::move (v));
      }
#else
      static
      symbol_type
      make_INTEGER (const std::string& v)
      {
        return symbol_type (token::INTEGER, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DECIMAL (std::string v)
      {
        return symbol_type (token::DECIMAL, std::move (v));
      }
#else
      static
      symbol_type
      make_DECIMAL (const std::string& v)
      {
        return symbol_type (token::DECIMAL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING (std::string v)
      {
        return symbol_type (token::STRING, std::move (v));
      }
#else
      static
      symbol_type
      make_STRING (const std::string& v)
      {
        return symbol_type (token::STRING, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF ()
      {
        return symbol_type (token::IF);
      }
#else
      static
      symbol_type
      make_IF ()
      {
        return symbol_type (token::IF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE ()
      {
        return symbol_type (token::ELSE);
      }
#else
      static
      symbol_type
      make_ELSE ()
      {
        return symbol_type (token::ELSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHEN ()
      {
        return symbol_type (token::WHEN);
      }
#else
      static
      symbol_type
      make_WHEN ()
      {
        return symbol_type (token::WHEN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TYPE ()
      {
        return symbol_type (token::TYPE);
      }
#else
      static
      symbol_type
      make_TYPE ()
      {
        return symbol_type (token::TYPE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AUTO ()
      {
        return symbol_type (token::AUTO);
      }
#else
      static
      symbol_type
      make_AUTO ()
      {
        return symbol_type (token::AUTO);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETURN ()
      {
        return symbol_type (token::RETURN);
      }
#else
      static
      symbol_type
      make_RETURN ()
      {
        return symbol_type (token::RETURN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OPAREN ()
      {
        return symbol_type (token::OPAREN);
      }
#else
      static
      symbol_type
      make_OPAREN ()
      {
        return symbol_type (token::OPAREN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CPAREN ()
      {
        return symbol_type (token::CPAREN);
      }
#else
      static
      symbol_type
      make_CPAREN ()
      {
        return symbol_type (token::CPAREN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OBRACE ()
      {
        return symbol_type (token::OBRACE);
      }
#else
      static
      symbol_type
      make_OBRACE ()
      {
        return symbol_type (token::OBRACE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CBRACE ()
      {
        return symbol_type (token::CBRACE);
      }
#else
      static
      symbol_type
      make_CBRACE ()
      {
        return symbol_type (token::CBRACE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASGN ()
      {
        return symbol_type (token::ASGN);
      }
#else
      static
      symbol_type
      make_ASGN ()
      {
        return symbol_type (token::ASGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMI ()
      {
        return symbol_type (token::SEMI);
      }
#else
      static
      symbol_type
      make_SEMI ()
      {
        return symbol_type (token::SEMI);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA ()
      {
        return symbol_type (token::COMMA);
      }
#else
      static
      symbol_type
      make_COMMA ()
      {
        return symbol_type (token::COMMA);
      }
#endif


  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef signed char state_type;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);

#if YYDEBUG || 0
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif // #if YYDEBUG || 0


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const signed char yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const signed char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const signed char yytable_[];

    static const signed char yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const signed char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const unsigned char yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yylast_ = 132,     ///< Last index in yytable_.
      yynnts_ = 26,  ///< Number of nonterminal symbols.
      yyfinal_ = 47 ///< Termination state number.
    };


    // User arguments.
    cynth::ast::node::Block & result;

  };

  inline
  parser::symbol_kind_type
  parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20
    };
    // Last valid token kind.
    const int code_max = 275;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->kind ())
    {
      case symbol_kind::S_expressible: // expressible
        value.copy< cynth::ast::category::Expressible > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_pure: // pure
        value.copy< cynth::ast::category::Statement > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
        value.copy< cynth::ast::category::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_alias: // alias
        value.copy< cynth::ast::node::Alias > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.copy< cynth::ast::node::Assignment > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_auto: // auto
        value.copy< cynth::ast::node::Auto > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block: // block
        value.copy< cynth::ast::node::Block > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decimal: // decimal
        value.copy< cynth::ast::node::Decimal > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.copy< cynth::ast::node::Declaration > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
        value.copy< cynth::ast::node::Definition > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_if: // expr_if
        value.copy< cynth::ast::node::ExprIf > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_type: // function_type
        value.copy< cynth::ast::node::FunctionType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_if: // if
        value.copy< cynth::ast::node::If > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_integer: // integer
        value.copy< cynth::ast::node::Integer > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_name: // name
        value.copy< cynth::ast::node::Name > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_return: // return
        value.copy< cynth::ast::node::Return > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_string: // string
        value.copy< cynth::ast::node::String > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_tuple_type: // tuple_type
        value.copy< cynth::ast::node::TupleType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_name: // type_name
        value.copy< cynth::ast::node::TypeName > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_when: // when
        value.copy< cynth::ast::node::When > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_start: // start
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_DECIMAL: // DECIMAL
      case symbol_kind::S_STRING: // STRING
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_block_list: // block_list
        value.copy< std::vector<cynth::ast::category::Statement *> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function_type_list: // function_type_list
      case symbol_kind::S_tuple_type_list: // tuple_type_list
        value.copy< std::vector<cynth::ast::category::Type      *> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_expressible: // expressible
        value.move< cynth::ast::category::Expressible > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_pure: // pure
        value.move< cynth::ast::category::Statement > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type: // type
        value.move< cynth::ast::category::Type > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_alias: // alias
        value.move< cynth::ast::node::Alias > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< cynth::ast::node::Assignment > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_auto: // auto
        value.move< cynth::ast::node::Auto > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_block: // block
        value.move< cynth::ast::node::Block > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_decimal: // decimal
        value.move< cynth::ast::node::Decimal > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_declaration: // declaration
        value.move< cynth::ast::node::Declaration > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_definition: // definition
        value.move< cynth::ast::node::Definition > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr_if: // expr_if
        value.move< cynth::ast::node::ExprIf > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_function_type: // function_type
        value.move< cynth::ast::node::FunctionType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_if: // if
        value.move< cynth::ast::node::If > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_integer: // integer
        value.move< cynth::ast::node::Integer > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_name: // name
        value.move< cynth::ast::node::Name > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_return: // return
        value.move< cynth::ast::node::Return > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_string: // string
        value.move< cynth::ast::node::String > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_tuple_type: // tuple_type
        value.move< cynth::ast::node::TupleType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_name: // type_name
        value.move< cynth::ast::node::TypeName > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_when: // when
        value.move< cynth::ast::node::When > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_start: // start
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INTEGER: // INTEGER
      case symbol_kind::S_DECIMAL: // DECIMAL
      case symbol_kind::S_STRING: // STRING
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_block_list: // block_list
        value.move< std::vector<cynth::ast::category::Statement *> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_function_type_list: // function_type_list
      case symbol_kind::S_tuple_type_list: // tuple_type_list
        value.move< std::vector<cynth::ast::category::Type      *> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_kind.
  inline
  parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  inline
  parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  inline
  void
  parser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  inline
  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

} // yy
#line 2283 "src/parser.hpp"


// "%code provides" blocks.
#line 18 "gen/parser.y"

    namespace yy {

        parser::symbol_type yylex ();

    }

    namespace cynth::ast::reg {

        template <typename t>
        util::registry<t> r;

        template <typename t>
        t * push (t && x) {
            return &r<std::remove_reference_t<t>>.push(std::forward<t>(x));
        }

    }

#line 2307 "src/parser.hpp"


#endif // !YY_YY_SRC_PARSER_HPP_INCLUDED
