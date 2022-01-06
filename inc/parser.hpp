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
 ** \file inc/parser.hpp
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_INC_PARSER_HPP_INCLUDED
# define YY_YY_INC_PARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 1 "gen/parser.y"


    #include <string>

    #include "esl/string.hpp"
    #include "esl/containers.hpp"

    #include "syn/all.hpp"
    #include "sem/numeric_types.hpp"


#line 61 "inc/parser.hpp"


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
#line 195 "inc/parser.hpp"




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
      // cat_array_elem
      char dummy1[sizeof (cynth::syn::category::ArrayElement)];

      // cat_declaration
      // paren_decl
      // void_decl
      char dummy2[sizeof (cynth::syn::category::Declaration)];

      // cat_expression
      // expr_or
      // expr_and
      // expr_eq
      // expr_ord
      // expr_add
      // expr_mul
      // expr_pow
      // expr_pre
      // expr_post
      // expr_atom
      // expr_right
      // expr_assgn_target
      // paren_expr
      // void
      char dummy3[sizeof (cynth::syn::category::Expression)];

      // cat_range_decl
      // paren_range_decl
      char dummy4[sizeof (cynth::syn::category::RangeDeclaration)];

      // cat_statement
      // pure
      char dummy5[sizeof (cynth::syn::category::Statement)];

      // cat_type
      // paren_type
      // void_type
      char dummy6[sizeof (cynth::syn::category::Type)];

      // node_add
      char dummy7[sizeof (cynth::syn::node::Add)];

      // node_and
      char dummy8[sizeof (cynth::syn::node::And)];

      // node_application
      char dummy9[sizeof (cynth::syn::node::Application)];

      // node_array
      char dummy10[sizeof (cynth::syn::node::Array)];

      // node_array_type
      char dummy11[sizeof (cynth::syn::node::ArrayType)];

      // node_assignment
      char dummy12[sizeof (cynth::syn::node::Assignment)];

      // node_auto
      char dummy13[sizeof (cynth::syn::node::Auto)];

      // node_block
      char dummy14[sizeof (cynth::syn::node::Block)];

      // node_bool
      char dummy15[sizeof (cynth::syn::node::Bool)];

      // node_buffer_type
      char dummy16[sizeof (cynth::syn::node::BufferType)];

      // node_const_type
      char dummy17[sizeof (cynth::syn::node::ConstType)];

      // node_conversion
      char dummy18[sizeof (cynth::syn::node::Conversion)];

      // node_declaration
      char dummy19[sizeof (cynth::syn::node::Declaration)];

      // node_definition
      char dummy20[sizeof (cynth::syn::node::Definition)];

      // node_div
      char dummy21[sizeof (cynth::syn::node::Div)];

      // node_eq
      char dummy22[sizeof (cynth::syn::node::Eq)];

      // node_expr_for
      char dummy23[sizeof (cynth::syn::node::ExprFor)];

      // node_expr_if
      char dummy24[sizeof (cynth::syn::node::ExprIf)];

      // node_float
      char dummy25[sizeof (cynth::syn::node::Float)];

      // node_for
      char dummy26[sizeof (cynth::syn::node::For)];

      // node_function_def
      char dummy27[sizeof (cynth::syn::node::FunDef)];

      // node_function
      char dummy28[sizeof (cynth::syn::node::Function)];

      // node_function_type
      char dummy29[sizeof (cynth::syn::node::FunctionType)];

      // node_ge
      char dummy30[sizeof (cynth::syn::node::Ge)];

      // node_gt
      char dummy31[sizeof (cynth::syn::node::Gt)];

      // node_if
      char dummy32[sizeof (cynth::syn::node::If)];

      // node_in_type
      char dummy33[sizeof (cynth::syn::node::InType)];

      // node_int
      char dummy34[sizeof (cynth::syn::node::Int)];

      // node_le
      char dummy35[sizeof (cynth::syn::node::Le)];

      // node_lt
      char dummy36[sizeof (cynth::syn::node::Lt)];

      // node_minus
      char dummy37[sizeof (cynth::syn::node::Minus)];

      // node_mod
      char dummy38[sizeof (cynth::syn::node::Mod)];

      // node_mul
      char dummy39[sizeof (cynth::syn::node::Mul)];

      // node_name
      char dummy40[sizeof (cynth::syn::node::Name)];

      // node_ne
      char dummy41[sizeof (cynth::syn::node::Ne)];

      // node_not
      char dummy42[sizeof (cynth::syn::node::Not)];

      // node_or
      char dummy43[sizeof (cynth::syn::node::Or)];

      // node_out_type
      char dummy44[sizeof (cynth::syn::node::OutType)];

      // node_plus
      char dummy45[sizeof (cynth::syn::node::Plus)];

      // node_pow
      char dummy46[sizeof (cynth::syn::node::Pow)];

      // node_range_decl
      char dummy47[sizeof (cynth::syn::node::RangeDecl)];

      // node_range_to
      char dummy48[sizeof (cynth::syn::node::RangeTo)];

      // node_range_to_by
      char dummy49[sizeof (cynth::syn::node::RangeToBy)];

      // node_return
      char dummy50[sizeof (cynth::syn::node::Return)];

      // node_spread
      char dummy51[sizeof (cynth::syn::node::Spread)];

      // node_string
      char dummy52[sizeof (cynth::syn::node::String)];

      // node_sub
      char dummy53[sizeof (cynth::syn::node::Sub)];

      // node_subscript
      char dummy54[sizeof (cynth::syn::node::Subscript)];

      // node_type_def
      char dummy55[sizeof (cynth::syn::node::TypeDef)];

      // node_type_name
      char dummy56[sizeof (cynth::syn::node::TypeName)];

      // node_when
      char dummy57[sizeof (cynth::syn::node::When)];

      // node_while
      char dummy58[sizeof (cynth::syn::node::While)];

      // array_elem_list
      char dummy59[sizeof (esl::component_vector<cynth::syn::category::ArrayElement>)];

      // decl_list
      char dummy60[sizeof (esl::component_vector<cynth::syn::category::Declaration>)];

      // expr_list
      char dummy61[sizeof (esl::component_vector<cynth::syn::category::Expression>)];

      // range_decl_list
      char dummy62[sizeof (esl::component_vector<cynth::syn::category::RangeDeclaration>)];

      // stmt_list
      char dummy63[sizeof (esl::component_vector<cynth::syn::category::Statement>)];

      // type_list
      char dummy64[sizeof (esl::component_vector<cynth::syn::category::Type>)];

      // start
      char dummy65[sizeof (int)];

      // NAME
      // TYPENAME
      // INT
      // FLOAT
      // STRING
      char dummy66[sizeof (std::string)];
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
    INT = 260,                     // INT
    FLOAT = 261,                   // FLOAT
    STRING = 262,                  // STRING
    IF = 263,                      // IF
    ELSE = 264,                    // ELSE
    WHEN = 265,                    // WHEN
    FOR = 266,                     // FOR
    WHILE = 267,                   // WHILE
    TYPE = 268,                    // TYPE
    FN = 269,                      // FN
    BUFFER = 270,                  // BUFFER
    RETURN = 271,                  // RETURN
    TRUE = 272,                    // TRUE
    FALSE = 273,                   // FALSE
    CONST = 274,                   // CONST
    AUTO = 275,                    // AUTO
    ASSGN = 276,                   // ASSGN
    SEMI = 277,                    // SEMI
    COMMA = 278,                   // COMMA
    IN = 279,                      // IN
    OUT = 280,                     // OUT
    TO = 281,                      // TO
    BY = 282,                      // BY
    ELIP = 283,                    // ELIP
    OPAREN = 284,                  // OPAREN
    CPAREN = 285,                  // CPAREN
    OBRACE = 286,                  // OBRACE
    CBRACE = 287,                  // CBRACE
    OBRACK = 288,                  // OBRACK
    CBRACK = 289,                  // CBRACK
    VOID = 290,                    // VOID
    ADD = 291,                     // ADD
    SUB = 292,                     // SUB
    MUL = 293,                     // MUL
    DIV = 294,                     // DIV
    MOD = 295,                     // MOD
    POW = 296,                     // POW
    NOT = 297,                     // NOT
    AND = 298,                     // AND
    OR = 299,                      // OR
    EQ = 300,                      // EQ
    NE = 301,                      // NE
    GE = 302,                      // GE
    LE = 303,                      // LE
    GT = 304,                      // GT
    LT = 305,                      // LT
    ILLEGAL = 306                  // ILLEGAL
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
        YYNTOKENS = 52, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_NAME = 3,                              // NAME
        S_TYPENAME = 4,                          // TYPENAME
        S_INT = 5,                               // INT
        S_FLOAT = 6,                             // FLOAT
        S_STRING = 7,                            // STRING
        S_IF = 8,                                // IF
        S_ELSE = 9,                              // ELSE
        S_WHEN = 10,                             // WHEN
        S_FOR = 11,                              // FOR
        S_WHILE = 12,                            // WHILE
        S_TYPE = 13,                             // TYPE
        S_FN = 14,                               // FN
        S_BUFFER = 15,                           // BUFFER
        S_RETURN = 16,                           // RETURN
        S_TRUE = 17,                             // TRUE
        S_FALSE = 18,                            // FALSE
        S_CONST = 19,                            // CONST
        S_AUTO = 20,                             // AUTO
        S_ASSGN = 21,                            // ASSGN
        S_SEMI = 22,                             // SEMI
        S_COMMA = 23,                            // COMMA
        S_IN = 24,                               // IN
        S_OUT = 25,                              // OUT
        S_TO = 26,                               // TO
        S_BY = 27,                               // BY
        S_ELIP = 28,                             // ELIP
        S_OPAREN = 29,                           // OPAREN
        S_CPAREN = 30,                           // CPAREN
        S_OBRACE = 31,                           // OBRACE
        S_CBRACE = 32,                           // CBRACE
        S_OBRACK = 33,                           // OBRACK
        S_CBRACK = 34,                           // CBRACK
        S_VOID = 35,                             // VOID
        S_ADD = 36,                              // ADD
        S_SUB = 37,                              // SUB
        S_MUL = 38,                              // MUL
        S_DIV = 39,                              // DIV
        S_MOD = 40,                              // MOD
        S_POW = 41,                              // POW
        S_NOT = 42,                              // NOT
        S_AND = 43,                              // AND
        S_OR = 44,                               // OR
        S_EQ = 45,                               // EQ
        S_NE = 46,                               // NE
        S_GE = 47,                               // GE
        S_LE = 48,                               // LE
        S_GT = 49,                               // GT
        S_LT = 50,                               // LT
        S_ILLEGAL = 51,                          // ILLEGAL
        S_YYACCEPT = 52,                         // $accept
        S_start = 53,                            // start
        S_cat_type = 54,                         // cat_type
        S_cat_declaration = 55,                  // cat_declaration
        S_cat_range_decl = 56,                   // cat_range_decl
        S_cat_array_elem = 57,                   // cat_array_elem
        S_cat_expression = 58,                   // cat_expression
        S_cat_statement = 59,                    // cat_statement
        S_pure = 60,                             // pure
        S_expr_or = 61,                          // expr_or
        S_expr_and = 62,                         // expr_and
        S_expr_eq = 63,                          // expr_eq
        S_expr_ord = 64,                         // expr_ord
        S_expr_add = 65,                         // expr_add
        S_expr_mul = 66,                         // expr_mul
        S_expr_pow = 67,                         // expr_pow
        S_expr_pre = 68,                         // expr_pre
        S_expr_post = 69,                        // expr_post
        S_expr_atom = 70,                        // expr_atom
        S_expr_right = 71,                       // expr_right
        S_expr_assgn_target = 72,                // expr_assgn_target
        S_paren_type = 73,                       // paren_type
        S_void_type = 74,                        // void_type
        S_node_auto = 75,                        // node_auto
        S_node_type_name = 76,                   // node_type_name
        S_node_const_type = 77,                  // node_const_type
        S_node_in_type = 78,                     // node_in_type
        S_node_out_type = 79,                    // node_out_type
        S_node_function_type = 80,               // node_function_type
        S_node_array_type = 81,                  // node_array_type
        S_node_buffer_type = 82,                 // node_buffer_type
        S_paren_decl = 83,                       // paren_decl
        S_paren_range_decl = 84,                 // paren_range_decl
        S_void_decl = 85,                        // void_decl
        S_node_declaration = 86,                 // node_declaration
        S_node_range_decl = 87,                  // node_range_decl
        S_node_range_to = 88,                    // node_range_to
        S_node_range_to_by = 89,                 // node_range_to_by
        S_node_spread = 90,                      // node_spread
        S_paren_expr = 91,                       // paren_expr
        S_void = 92,                             // void
        S_node_name = 93,                        // node_name
        S_node_block = 94,                       // node_block
        S_node_bool = 95,                        // node_bool
        S_node_int = 96,                         // node_int
        S_node_float = 97,                       // node_float
        S_node_string = 98,                      // node_string
        S_node_function = 99,                    // node_function
        S_node_array = 100,                      // node_array
        S_node_or = 101,                         // node_or
        S_node_and = 102,                        // node_and
        S_node_eq = 103,                         // node_eq
        S_node_ne = 104,                         // node_ne
        S_node_ge = 105,                         // node_ge
        S_node_le = 106,                         // node_le
        S_node_gt = 107,                         // node_gt
        S_node_lt = 108,                         // node_lt
        S_node_add = 109,                        // node_add
        S_node_sub = 110,                        // node_sub
        S_node_mul = 111,                        // node_mul
        S_node_div = 112,                        // node_div
        S_node_mod = 113,                        // node_mod
        S_node_pow = 114,                        // node_pow
        S_node_plus = 115,                       // node_plus
        S_node_minus = 116,                      // node_minus
        S_node_not = 117,                        // node_not
        S_node_application = 118,                // node_application
        S_node_conversion = 119,                 // node_conversion
        S_node_subscript = 120,                  // node_subscript
        S_node_expr_if = 121,                    // node_expr_if
        S_node_expr_for = 122,                   // node_expr_for
        S_node_definition = 123,                 // node_definition
        S_node_assignment = 124,                 // node_assignment
        S_node_function_def = 125,               // node_function_def
        S_node_type_def = 126,                   // node_type_def
        S_node_return = 127,                     // node_return
        S_node_if = 128,                         // node_if
        S_node_when = 129,                       // node_when
        S_node_for = 130,                        // node_for
        S_node_while = 131,                      // node_while
        S_type_list = 132,                       // type_list
        S_decl_list = 133,                       // decl_list
        S_range_decl_list = 134,                 // range_decl_list
        S_array_elem_list = 135,                 // array_elem_list
        S_expr_list = 136,                       // expr_list
        S_stmt_list = 137                        // stmt_list
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
      case symbol_kind::S_cat_array_elem: // cat_array_elem
        value.move< cynth::syn::category::ArrayElement > (std::move (that.value));
        break;

      case symbol_kind::S_cat_declaration: // cat_declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.move< cynth::syn::category::Declaration > (std::move (that.value));
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
        value.move< cynth::syn::category::Expression > (std::move (that.value));
        break;

      case symbol_kind::S_cat_range_decl: // cat_range_decl
      case symbol_kind::S_paren_range_decl: // paren_range_decl
        value.move< cynth::syn::category::RangeDeclaration > (std::move (that.value));
        break;

      case symbol_kind::S_cat_statement: // cat_statement
      case symbol_kind::S_pure: // pure
        value.move< cynth::syn::category::Statement > (std::move (that.value));
        break;

      case symbol_kind::S_cat_type: // cat_type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.move< cynth::syn::category::Type > (std::move (that.value));
        break;

      case symbol_kind::S_node_add: // node_add
        value.move< cynth::syn::node::Add > (std::move (that.value));
        break;

      case symbol_kind::S_node_and: // node_and
        value.move< cynth::syn::node::And > (std::move (that.value));
        break;

      case symbol_kind::S_node_application: // node_application
        value.move< cynth::syn::node::Application > (std::move (that.value));
        break;

      case symbol_kind::S_node_array: // node_array
        value.move< cynth::syn::node::Array > (std::move (that.value));
        break;

      case symbol_kind::S_node_array_type: // node_array_type
        value.move< cynth::syn::node::ArrayType > (std::move (that.value));
        break;

      case symbol_kind::S_node_assignment: // node_assignment
        value.move< cynth::syn::node::Assignment > (std::move (that.value));
        break;

      case symbol_kind::S_node_auto: // node_auto
        value.move< cynth::syn::node::Auto > (std::move (that.value));
        break;

      case symbol_kind::S_node_block: // node_block
        value.move< cynth::syn::node::Block > (std::move (that.value));
        break;

      case symbol_kind::S_node_bool: // node_bool
        value.move< cynth::syn::node::Bool > (std::move (that.value));
        break;

      case symbol_kind::S_node_buffer_type: // node_buffer_type
        value.move< cynth::syn::node::BufferType > (std::move (that.value));
        break;

      case symbol_kind::S_node_const_type: // node_const_type
        value.move< cynth::syn::node::ConstType > (std::move (that.value));
        break;

      case symbol_kind::S_node_conversion: // node_conversion
        value.move< cynth::syn::node::Conversion > (std::move (that.value));
        break;

      case symbol_kind::S_node_declaration: // node_declaration
        value.move< cynth::syn::node::Declaration > (std::move (that.value));
        break;

      case symbol_kind::S_node_definition: // node_definition
        value.move< cynth::syn::node::Definition > (std::move (that.value));
        break;

      case symbol_kind::S_node_div: // node_div
        value.move< cynth::syn::node::Div > (std::move (that.value));
        break;

      case symbol_kind::S_node_eq: // node_eq
        value.move< cynth::syn::node::Eq > (std::move (that.value));
        break;

      case symbol_kind::S_node_expr_for: // node_expr_for
        value.move< cynth::syn::node::ExprFor > (std::move (that.value));
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.move< cynth::syn::node::ExprIf > (std::move (that.value));
        break;

      case symbol_kind::S_node_float: // node_float
        value.move< cynth::syn::node::Float > (std::move (that.value));
        break;

      case symbol_kind::S_node_for: // node_for
        value.move< cynth::syn::node::For > (std::move (that.value));
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.move< cynth::syn::node::FunDef > (std::move (that.value));
        break;

      case symbol_kind::S_node_function: // node_function
        value.move< cynth::syn::node::Function > (std::move (that.value));
        break;

      case symbol_kind::S_node_function_type: // node_function_type
        value.move< cynth::syn::node::FunctionType > (std::move (that.value));
        break;

      case symbol_kind::S_node_ge: // node_ge
        value.move< cynth::syn::node::Ge > (std::move (that.value));
        break;

      case symbol_kind::S_node_gt: // node_gt
        value.move< cynth::syn::node::Gt > (std::move (that.value));
        break;

      case symbol_kind::S_node_if: // node_if
        value.move< cynth::syn::node::If > (std::move (that.value));
        break;

      case symbol_kind::S_node_in_type: // node_in_type
        value.move< cynth::syn::node::InType > (std::move (that.value));
        break;

      case symbol_kind::S_node_int: // node_int
        value.move< cynth::syn::node::Int > (std::move (that.value));
        break;

      case symbol_kind::S_node_le: // node_le
        value.move< cynth::syn::node::Le > (std::move (that.value));
        break;

      case symbol_kind::S_node_lt: // node_lt
        value.move< cynth::syn::node::Lt > (std::move (that.value));
        break;

      case symbol_kind::S_node_minus: // node_minus
        value.move< cynth::syn::node::Minus > (std::move (that.value));
        break;

      case symbol_kind::S_node_mod: // node_mod
        value.move< cynth::syn::node::Mod > (std::move (that.value));
        break;

      case symbol_kind::S_node_mul: // node_mul
        value.move< cynth::syn::node::Mul > (std::move (that.value));
        break;

      case symbol_kind::S_node_name: // node_name
        value.move< cynth::syn::node::Name > (std::move (that.value));
        break;

      case symbol_kind::S_node_ne: // node_ne
        value.move< cynth::syn::node::Ne > (std::move (that.value));
        break;

      case symbol_kind::S_node_not: // node_not
        value.move< cynth::syn::node::Not > (std::move (that.value));
        break;

      case symbol_kind::S_node_or: // node_or
        value.move< cynth::syn::node::Or > (std::move (that.value));
        break;

      case symbol_kind::S_node_out_type: // node_out_type
        value.move< cynth::syn::node::OutType > (std::move (that.value));
        break;

      case symbol_kind::S_node_plus: // node_plus
        value.move< cynth::syn::node::Plus > (std::move (that.value));
        break;

      case symbol_kind::S_node_pow: // node_pow
        value.move< cynth::syn::node::Pow > (std::move (that.value));
        break;

      case symbol_kind::S_node_range_decl: // node_range_decl
        value.move< cynth::syn::node::RangeDecl > (std::move (that.value));
        break;

      case symbol_kind::S_node_range_to: // node_range_to
        value.move< cynth::syn::node::RangeTo > (std::move (that.value));
        break;

      case symbol_kind::S_node_range_to_by: // node_range_to_by
        value.move< cynth::syn::node::RangeToBy > (std::move (that.value));
        break;

      case symbol_kind::S_node_return: // node_return
        value.move< cynth::syn::node::Return > (std::move (that.value));
        break;

      case symbol_kind::S_node_spread: // node_spread
        value.move< cynth::syn::node::Spread > (std::move (that.value));
        break;

      case symbol_kind::S_node_string: // node_string
        value.move< cynth::syn::node::String > (std::move (that.value));
        break;

      case symbol_kind::S_node_sub: // node_sub
        value.move< cynth::syn::node::Sub > (std::move (that.value));
        break;

      case symbol_kind::S_node_subscript: // node_subscript
        value.move< cynth::syn::node::Subscript > (std::move (that.value));
        break;

      case symbol_kind::S_node_type_def: // node_type_def
        value.move< cynth::syn::node::TypeDef > (std::move (that.value));
        break;

      case symbol_kind::S_node_type_name: // node_type_name
        value.move< cynth::syn::node::TypeName > (std::move (that.value));
        break;

      case symbol_kind::S_node_when: // node_when
        value.move< cynth::syn::node::When > (std::move (that.value));
        break;

      case symbol_kind::S_node_while: // node_while
        value.move< cynth::syn::node::While > (std::move (that.value));
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.move< esl::component_vector<cynth::syn::category::ArrayElement> > (std::move (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< esl::component_vector<cynth::syn::category::Declaration> > (std::move (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< esl::component_vector<cynth::syn::category::Expression> > (std::move (that.value));
        break;

      case symbol_kind::S_range_decl_list: // range_decl_list
        value.move< esl::component_vector<cynth::syn::category::RangeDeclaration> > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< esl::component_vector<cynth::syn::category::Statement> > (std::move (that.value));
        break;

      case symbol_kind::S_type_list: // type_list
        value.move< esl::component_vector<cynth::syn::category::Type> > (std::move (that.value));
        break;

      case symbol_kind::S_start: // start
        value.move< int > (std::move (that.value));
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_STRING: // STRING
        value.move< std::string > (std::move (that.value));
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
      basic_symbol (typename Base::kind_type t, cynth::syn::category::ArrayElement&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::category::ArrayElement& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::category::Declaration&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::category::Declaration& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::category::Expression&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::category::Expression& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::category::RangeDeclaration&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::category::RangeDeclaration& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::category::Statement&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::category::Statement& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::category::Type&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::category::Type& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Add&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Add& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::And&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::And& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Application&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Application& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Array&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Array& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::ArrayType&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::ArrayType& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Assignment&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Assignment& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Auto&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Auto& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Block&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Block& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Bool&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Bool& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::BufferType&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::BufferType& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::ConstType&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::ConstType& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Conversion&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Conversion& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Declaration&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Declaration& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Definition&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Definition& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Div&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Div& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Eq&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Eq& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::ExprFor&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::ExprFor& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::ExprIf&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::ExprIf& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Float&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Float& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::For&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::For& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::FunDef&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::FunDef& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Function&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Function& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::FunctionType&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::FunctionType& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Ge&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Ge& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Gt&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Gt& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::If&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::If& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::InType&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::InType& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Int&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Int& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Le&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Le& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Lt&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Lt& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Minus&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Minus& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Mod&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Mod& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Mul&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Mul& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Name&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Name& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Ne&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Ne& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Not&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Not& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Or&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Or& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::OutType&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::OutType& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Plus&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Plus& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Pow&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Pow& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::RangeDecl&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::RangeDecl& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::RangeTo&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::RangeTo& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::RangeToBy&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::RangeToBy& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Return&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Return& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Spread&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Spread& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::String&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::String& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Sub&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Sub& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::Subscript&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::Subscript& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::TypeDef&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::TypeDef& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::TypeName&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::TypeName& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::When&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::When& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, cynth::syn::node::While&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const cynth::syn::node::While& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, esl::component_vector<cynth::syn::category::ArrayElement>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const esl::component_vector<cynth::syn::category::ArrayElement>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, esl::component_vector<cynth::syn::category::Declaration>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const esl::component_vector<cynth::syn::category::Declaration>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, esl::component_vector<cynth::syn::category::Expression>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const esl::component_vector<cynth::syn::category::Expression>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, esl::component_vector<cynth::syn::category::RangeDeclaration>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const esl::component_vector<cynth::syn::category::RangeDeclaration>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, esl::component_vector<cynth::syn::category::Statement>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const esl::component_vector<cynth::syn::category::Statement>& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, esl::component_vector<cynth::syn::category::Type>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const esl::component_vector<cynth::syn::category::Type>& v)
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
      case symbol_kind::S_cat_array_elem: // cat_array_elem
        value.template destroy< cynth::syn::category::ArrayElement > ();
        break;

      case symbol_kind::S_cat_declaration: // cat_declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.template destroy< cynth::syn::category::Declaration > ();
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
        value.template destroy< cynth::syn::category::Expression > ();
        break;

      case symbol_kind::S_cat_range_decl: // cat_range_decl
      case symbol_kind::S_paren_range_decl: // paren_range_decl
        value.template destroy< cynth::syn::category::RangeDeclaration > ();
        break;

      case symbol_kind::S_cat_statement: // cat_statement
      case symbol_kind::S_pure: // pure
        value.template destroy< cynth::syn::category::Statement > ();
        break;

      case symbol_kind::S_cat_type: // cat_type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.template destroy< cynth::syn::category::Type > ();
        break;

      case symbol_kind::S_node_add: // node_add
        value.template destroy< cynth::syn::node::Add > ();
        break;

      case symbol_kind::S_node_and: // node_and
        value.template destroy< cynth::syn::node::And > ();
        break;

      case symbol_kind::S_node_application: // node_application
        value.template destroy< cynth::syn::node::Application > ();
        break;

      case symbol_kind::S_node_array: // node_array
        value.template destroy< cynth::syn::node::Array > ();
        break;

      case symbol_kind::S_node_array_type: // node_array_type
        value.template destroy< cynth::syn::node::ArrayType > ();
        break;

      case symbol_kind::S_node_assignment: // node_assignment
        value.template destroy< cynth::syn::node::Assignment > ();
        break;

      case symbol_kind::S_node_auto: // node_auto
        value.template destroy< cynth::syn::node::Auto > ();
        break;

      case symbol_kind::S_node_block: // node_block
        value.template destroy< cynth::syn::node::Block > ();
        break;

      case symbol_kind::S_node_bool: // node_bool
        value.template destroy< cynth::syn::node::Bool > ();
        break;

      case symbol_kind::S_node_buffer_type: // node_buffer_type
        value.template destroy< cynth::syn::node::BufferType > ();
        break;

      case symbol_kind::S_node_const_type: // node_const_type
        value.template destroy< cynth::syn::node::ConstType > ();
        break;

      case symbol_kind::S_node_conversion: // node_conversion
        value.template destroy< cynth::syn::node::Conversion > ();
        break;

      case symbol_kind::S_node_declaration: // node_declaration
        value.template destroy< cynth::syn::node::Declaration > ();
        break;

      case symbol_kind::S_node_definition: // node_definition
        value.template destroy< cynth::syn::node::Definition > ();
        break;

      case symbol_kind::S_node_div: // node_div
        value.template destroy< cynth::syn::node::Div > ();
        break;

      case symbol_kind::S_node_eq: // node_eq
        value.template destroy< cynth::syn::node::Eq > ();
        break;

      case symbol_kind::S_node_expr_for: // node_expr_for
        value.template destroy< cynth::syn::node::ExprFor > ();
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.template destroy< cynth::syn::node::ExprIf > ();
        break;

      case symbol_kind::S_node_float: // node_float
        value.template destroy< cynth::syn::node::Float > ();
        break;

      case symbol_kind::S_node_for: // node_for
        value.template destroy< cynth::syn::node::For > ();
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.template destroy< cynth::syn::node::FunDef > ();
        break;

      case symbol_kind::S_node_function: // node_function
        value.template destroy< cynth::syn::node::Function > ();
        break;

      case symbol_kind::S_node_function_type: // node_function_type
        value.template destroy< cynth::syn::node::FunctionType > ();
        break;

      case symbol_kind::S_node_ge: // node_ge
        value.template destroy< cynth::syn::node::Ge > ();
        break;

      case symbol_kind::S_node_gt: // node_gt
        value.template destroy< cynth::syn::node::Gt > ();
        break;

      case symbol_kind::S_node_if: // node_if
        value.template destroy< cynth::syn::node::If > ();
        break;

      case symbol_kind::S_node_in_type: // node_in_type
        value.template destroy< cynth::syn::node::InType > ();
        break;

      case symbol_kind::S_node_int: // node_int
        value.template destroy< cynth::syn::node::Int > ();
        break;

      case symbol_kind::S_node_le: // node_le
        value.template destroy< cynth::syn::node::Le > ();
        break;

      case symbol_kind::S_node_lt: // node_lt
        value.template destroy< cynth::syn::node::Lt > ();
        break;

      case symbol_kind::S_node_minus: // node_minus
        value.template destroy< cynth::syn::node::Minus > ();
        break;

      case symbol_kind::S_node_mod: // node_mod
        value.template destroy< cynth::syn::node::Mod > ();
        break;

      case symbol_kind::S_node_mul: // node_mul
        value.template destroy< cynth::syn::node::Mul > ();
        break;

      case symbol_kind::S_node_name: // node_name
        value.template destroy< cynth::syn::node::Name > ();
        break;

      case symbol_kind::S_node_ne: // node_ne
        value.template destroy< cynth::syn::node::Ne > ();
        break;

      case symbol_kind::S_node_not: // node_not
        value.template destroy< cynth::syn::node::Not > ();
        break;

      case symbol_kind::S_node_or: // node_or
        value.template destroy< cynth::syn::node::Or > ();
        break;

      case symbol_kind::S_node_out_type: // node_out_type
        value.template destroy< cynth::syn::node::OutType > ();
        break;

      case symbol_kind::S_node_plus: // node_plus
        value.template destroy< cynth::syn::node::Plus > ();
        break;

      case symbol_kind::S_node_pow: // node_pow
        value.template destroy< cynth::syn::node::Pow > ();
        break;

      case symbol_kind::S_node_range_decl: // node_range_decl
        value.template destroy< cynth::syn::node::RangeDecl > ();
        break;

      case symbol_kind::S_node_range_to: // node_range_to
        value.template destroy< cynth::syn::node::RangeTo > ();
        break;

      case symbol_kind::S_node_range_to_by: // node_range_to_by
        value.template destroy< cynth::syn::node::RangeToBy > ();
        break;

      case symbol_kind::S_node_return: // node_return
        value.template destroy< cynth::syn::node::Return > ();
        break;

      case symbol_kind::S_node_spread: // node_spread
        value.template destroy< cynth::syn::node::Spread > ();
        break;

      case symbol_kind::S_node_string: // node_string
        value.template destroy< cynth::syn::node::String > ();
        break;

      case symbol_kind::S_node_sub: // node_sub
        value.template destroy< cynth::syn::node::Sub > ();
        break;

      case symbol_kind::S_node_subscript: // node_subscript
        value.template destroy< cynth::syn::node::Subscript > ();
        break;

      case symbol_kind::S_node_type_def: // node_type_def
        value.template destroy< cynth::syn::node::TypeDef > ();
        break;

      case symbol_kind::S_node_type_name: // node_type_name
        value.template destroy< cynth::syn::node::TypeName > ();
        break;

      case symbol_kind::S_node_when: // node_when
        value.template destroy< cynth::syn::node::When > ();
        break;

      case symbol_kind::S_node_while: // node_while
        value.template destroy< cynth::syn::node::While > ();
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.template destroy< esl::component_vector<cynth::syn::category::ArrayElement> > ();
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.template destroy< esl::component_vector<cynth::syn::category::Declaration> > ();
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.template destroy< esl::component_vector<cynth::syn::category::Expression> > ();
        break;

      case symbol_kind::S_range_decl_list: // range_decl_list
        value.template destroy< esl::component_vector<cynth::syn::category::RangeDeclaration> > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.template destroy< esl::component_vector<cynth::syn::category::Statement> > ();
        break;

      case symbol_kind::S_type_list: // type_list
        value.template destroy< esl::component_vector<cynth::syn::category::Type> > ();
        break;

      case symbol_kind::S_start: // start
        value.template destroy< int > ();
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_STRING: // STRING
        value.template destroy< std::string > ();
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
        YY_ASSERT (tok == token::YYEOF || tok == token::YYerror || tok == token::YYUNDEF || tok == token::IF || tok == token::ELSE || tok == token::WHEN || tok == token::FOR || tok == token::WHILE || tok == token::TYPE || tok == token::FN || tok == token::BUFFER || tok == token::RETURN || tok == token::TRUE || tok == token::FALSE || tok == token::CONST || tok == token::AUTO || tok == token::ASSGN || tok == token::SEMI || tok == token::COMMA || tok == token::IN || tok == token::OUT || tok == token::TO || tok == token::BY || tok == token::ELIP || tok == token::OPAREN || tok == token::CPAREN || tok == token::OBRACE || tok == token::CBRACE || tok == token::OBRACK || tok == token::CBRACK || tok == token::VOID || tok == token::ADD || tok == token::SUB || tok == token::MUL || tok == token::DIV || tok == token::MOD || tok == token::POW || tok == token::NOT || tok == token::AND || tok == token::OR || tok == token::EQ || tok == token::NE || tok == token::GE || tok == token::LE || tok == token::GT || tok == token::LT || tok == token::ILLEGAL);
      }
#else
      symbol_type (int tok)
        : super_type(token_type (tok))
      {
        YY_ASSERT (tok == token::YYEOF || tok == token::YYerror || tok == token::YYUNDEF || tok == token::IF || tok == token::ELSE || tok == token::WHEN || tok == token::FOR || tok == token::WHILE || tok == token::TYPE || tok == token::FN || tok == token::BUFFER || tok == token::RETURN || tok == token::TRUE || tok == token::FALSE || tok == token::CONST || tok == token::AUTO || tok == token::ASSGN || tok == token::SEMI || tok == token::COMMA || tok == token::IN || tok == token::OUT || tok == token::TO || tok == token::BY || tok == token::ELIP || tok == token::OPAREN || tok == token::CPAREN || tok == token::OBRACE || tok == token::CBRACE || tok == token::OBRACK || tok == token::CBRACK || tok == token::VOID || tok == token::ADD || tok == token::SUB || tok == token::MUL || tok == token::DIV || tok == token::MOD || tok == token::POW || tok == token::NOT || tok == token::AND || tok == token::OR || tok == token::EQ || tok == token::NE || tok == token::GE || tok == token::LE || tok == token::GT || tok == token::LT || tok == token::ILLEGAL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v)
        : super_type(token_type (tok), std::move (v))
      {
        YY_ASSERT (tok == token::NAME || tok == token::TYPENAME || tok == token::INT || tok == token::FLOAT || tok == token::STRING);
      }
#else
      symbol_type (int tok, const std::string& v)
        : super_type(token_type (tok), v)
      {
        YY_ASSERT (tok == token::NAME || tok == token::TYPENAME || tok == token::INT || tok == token::FLOAT || tok == token::STRING);
      }
#endif
    };

    /// Build a parser object.
    parser (std::pair<cynth::syn::node::Block &, bool &> result_yyarg);
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
      make_INT (std::string v)
      {
        return symbol_type (token::INT, std::move (v));
      }
#else
      static
      symbol_type
      make_INT (const std::string& v)
      {
        return symbol_type (token::INT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT (std::string v)
      {
        return symbol_type (token::FLOAT, std::move (v));
      }
#else
      static
      symbol_type
      make_FLOAT (const std::string& v)
      {
        return symbol_type (token::FLOAT, v);
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
      make_FOR ()
      {
        return symbol_type (token::FOR);
      }
#else
      static
      symbol_type
      make_FOR ()
      {
        return symbol_type (token::FOR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE ()
      {
        return symbol_type (token::WHILE);
      }
#else
      static
      symbol_type
      make_WHILE ()
      {
        return symbol_type (token::WHILE);
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
      make_FN ()
      {
        return symbol_type (token::FN);
      }
#else
      static
      symbol_type
      make_FN ()
      {
        return symbol_type (token::FN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BUFFER ()
      {
        return symbol_type (token::BUFFER);
      }
#else
      static
      symbol_type
      make_BUFFER ()
      {
        return symbol_type (token::BUFFER);
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
      make_TRUE ()
      {
        return symbol_type (token::TRUE);
      }
#else
      static
      symbol_type
      make_TRUE ()
      {
        return symbol_type (token::TRUE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FALSE ()
      {
        return symbol_type (token::FALSE);
      }
#else
      static
      symbol_type
      make_FALSE ()
      {
        return symbol_type (token::FALSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CONST ()
      {
        return symbol_type (token::CONST);
      }
#else
      static
      symbol_type
      make_CONST ()
      {
        return symbol_type (token::CONST);
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
      make_ASSGN ()
      {
        return symbol_type (token::ASSGN);
      }
#else
      static
      symbol_type
      make_ASSGN ()
      {
        return symbol_type (token::ASSGN);
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
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IN ()
      {
        return symbol_type (token::IN);
      }
#else
      static
      symbol_type
      make_IN ()
      {
        return symbol_type (token::IN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OUT ()
      {
        return symbol_type (token::OUT);
      }
#else
      static
      symbol_type
      make_OUT ()
      {
        return symbol_type (token::OUT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TO ()
      {
        return symbol_type (token::TO);
      }
#else
      static
      symbol_type
      make_TO ()
      {
        return symbol_type (token::TO);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BY ()
      {
        return symbol_type (token::BY);
      }
#else
      static
      symbol_type
      make_BY ()
      {
        return symbol_type (token::BY);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELIP ()
      {
        return symbol_type (token::ELIP);
      }
#else
      static
      symbol_type
      make_ELIP ()
      {
        return symbol_type (token::ELIP);
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
      make_OBRACK ()
      {
        return symbol_type (token::OBRACK);
      }
#else
      static
      symbol_type
      make_OBRACK ()
      {
        return symbol_type (token::OBRACK);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CBRACK ()
      {
        return symbol_type (token::CBRACK);
      }
#else
      static
      symbol_type
      make_CBRACK ()
      {
        return symbol_type (token::CBRACK);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VOID ()
      {
        return symbol_type (token::VOID);
      }
#else
      static
      symbol_type
      make_VOID ()
      {
        return symbol_type (token::VOID);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ADD ()
      {
        return symbol_type (token::ADD);
      }
#else
      static
      symbol_type
      make_ADD ()
      {
        return symbol_type (token::ADD);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB ()
      {
        return symbol_type (token::SUB);
      }
#else
      static
      symbol_type
      make_SUB ()
      {
        return symbol_type (token::SUB);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MUL ()
      {
        return symbol_type (token::MUL);
      }
#else
      static
      symbol_type
      make_MUL ()
      {
        return symbol_type (token::MUL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIV ()
      {
        return symbol_type (token::DIV);
      }
#else
      static
      symbol_type
      make_DIV ()
      {
        return symbol_type (token::DIV);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MOD ()
      {
        return symbol_type (token::MOD);
      }
#else
      static
      symbol_type
      make_MOD ()
      {
        return symbol_type (token::MOD);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_POW ()
      {
        return symbol_type (token::POW);
      }
#else
      static
      symbol_type
      make_POW ()
      {
        return symbol_type (token::POW);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT ()
      {
        return symbol_type (token::NOT);
      }
#else
      static
      symbol_type
      make_NOT ()
      {
        return symbol_type (token::NOT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND ()
      {
        return symbol_type (token::AND);
      }
#else
      static
      symbol_type
      make_AND ()
      {
        return symbol_type (token::AND);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR ()
      {
        return symbol_type (token::OR);
      }
#else
      static
      symbol_type
      make_OR ()
      {
        return symbol_type (token::OR);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQ ()
      {
        return symbol_type (token::EQ);
      }
#else
      static
      symbol_type
      make_EQ ()
      {
        return symbol_type (token::EQ);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NE ()
      {
        return symbol_type (token::NE);
      }
#else
      static
      symbol_type
      make_NE ()
      {
        return symbol_type (token::NE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GE ()
      {
        return symbol_type (token::GE);
      }
#else
      static
      symbol_type
      make_GE ()
      {
        return symbol_type (token::GE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LE ()
      {
        return symbol_type (token::LE);
      }
#else
      static
      symbol_type
      make_LE ()
      {
        return symbol_type (token::LE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GT ()
      {
        return symbol_type (token::GT);
      }
#else
      static
      symbol_type
      make_GT ()
      {
        return symbol_type (token::GT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LT ()
      {
        return symbol_type (token::LT);
      }
#else
      static
      symbol_type
      make_LT ()
      {
        return symbol_type (token::LT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ILLEGAL ()
      {
        return symbol_type (token::ILLEGAL);
      }
#else
      static
      symbol_type
      make_ILLEGAL ()
      {
        return symbol_type (token::ILLEGAL);
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
    typedef short state_type;

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

    static const short yypact_ninf_;
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
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const unsigned char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const unsigned char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const unsigned char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
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
      yylast_ = 1290,     ///< Last index in yytable_.
      yynnts_ = 86,  ///< Number of nonterminal symbols.
      yyfinal_ = 134 ///< Termination state number.
    };


    // User arguments.
    std::pair<cynth::syn::node::Block &, bool &> result;

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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
    };
    // Last valid token kind.
    const int code_max = 306;

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
      case symbol_kind::S_cat_array_elem: // cat_array_elem
        value.copy< cynth::syn::category::ArrayElement > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_declaration: // cat_declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.copy< cynth::syn::category::Declaration > (YY_MOVE (that.value));
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
        value.copy< cynth::syn::category::Expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_range_decl: // cat_range_decl
      case symbol_kind::S_paren_range_decl: // paren_range_decl
        value.copy< cynth::syn::category::RangeDeclaration > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_statement: // cat_statement
      case symbol_kind::S_pure: // pure
        value.copy< cynth::syn::category::Statement > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cat_type: // cat_type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.copy< cynth::syn::category::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_add: // node_add
        value.copy< cynth::syn::node::Add > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_and: // node_and
        value.copy< cynth::syn::node::And > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_application: // node_application
        value.copy< cynth::syn::node::Application > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_array: // node_array
        value.copy< cynth::syn::node::Array > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_array_type: // node_array_type
        value.copy< cynth::syn::node::ArrayType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_assignment: // node_assignment
        value.copy< cynth::syn::node::Assignment > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_auto: // node_auto
        value.copy< cynth::syn::node::Auto > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_block: // node_block
        value.copy< cynth::syn::node::Block > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_bool: // node_bool
        value.copy< cynth::syn::node::Bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_buffer_type: // node_buffer_type
        value.copy< cynth::syn::node::BufferType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_const_type: // node_const_type
        value.copy< cynth::syn::node::ConstType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_conversion: // node_conversion
        value.copy< cynth::syn::node::Conversion > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_declaration: // node_declaration
        value.copy< cynth::syn::node::Declaration > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_definition: // node_definition
        value.copy< cynth::syn::node::Definition > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_div: // node_div
        value.copy< cynth::syn::node::Div > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_eq: // node_eq
        value.copy< cynth::syn::node::Eq > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_expr_for: // node_expr_for
        value.copy< cynth::syn::node::ExprFor > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.copy< cynth::syn::node::ExprIf > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_float: // node_float
        value.copy< cynth::syn::node::Float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_for: // node_for
        value.copy< cynth::syn::node::For > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.copy< cynth::syn::node::FunDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function: // node_function
        value.copy< cynth::syn::node::Function > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_function_type: // node_function_type
        value.copy< cynth::syn::node::FunctionType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_ge: // node_ge
        value.copy< cynth::syn::node::Ge > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_gt: // node_gt
        value.copy< cynth::syn::node::Gt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_if: // node_if
        value.copy< cynth::syn::node::If > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_in_type: // node_in_type
        value.copy< cynth::syn::node::InType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_int: // node_int
        value.copy< cynth::syn::node::Int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_le: // node_le
        value.copy< cynth::syn::node::Le > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_lt: // node_lt
        value.copy< cynth::syn::node::Lt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_minus: // node_minus
        value.copy< cynth::syn::node::Minus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_mod: // node_mod
        value.copy< cynth::syn::node::Mod > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_mul: // node_mul
        value.copy< cynth::syn::node::Mul > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_name: // node_name
        value.copy< cynth::syn::node::Name > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_ne: // node_ne
        value.copy< cynth::syn::node::Ne > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_not: // node_not
        value.copy< cynth::syn::node::Not > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_or: // node_or
        value.copy< cynth::syn::node::Or > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_out_type: // node_out_type
        value.copy< cynth::syn::node::OutType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_plus: // node_plus
        value.copy< cynth::syn::node::Plus > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_pow: // node_pow
        value.copy< cynth::syn::node::Pow > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_range_decl: // node_range_decl
        value.copy< cynth::syn::node::RangeDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_range_to: // node_range_to
        value.copy< cynth::syn::node::RangeTo > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_range_to_by: // node_range_to_by
        value.copy< cynth::syn::node::RangeToBy > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_return: // node_return
        value.copy< cynth::syn::node::Return > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_spread: // node_spread
        value.copy< cynth::syn::node::Spread > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_string: // node_string
        value.copy< cynth::syn::node::String > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_sub: // node_sub
        value.copy< cynth::syn::node::Sub > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_subscript: // node_subscript
        value.copy< cynth::syn::node::Subscript > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_type_def: // node_type_def
        value.copy< cynth::syn::node::TypeDef > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_type_name: // node_type_name
        value.copy< cynth::syn::node::TypeName > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_when: // node_when
        value.copy< cynth::syn::node::When > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_node_while: // node_while
        value.copy< cynth::syn::node::While > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.copy< esl::component_vector<cynth::syn::category::ArrayElement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.copy< esl::component_vector<cynth::syn::category::Declaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.copy< esl::component_vector<cynth::syn::category::Expression> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_range_decl_list: // range_decl_list
        value.copy< esl::component_vector<cynth::syn::category::RangeDeclaration> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< esl::component_vector<cynth::syn::category::Statement> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_list: // type_list
        value.copy< esl::component_vector<cynth::syn::category::Type> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_start: // start
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_STRING: // STRING
        value.copy< std::string > (YY_MOVE (that.value));
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
      case symbol_kind::S_cat_array_elem: // cat_array_elem
        value.move< cynth::syn::category::ArrayElement > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_cat_declaration: // cat_declaration
      case symbol_kind::S_paren_decl: // paren_decl
      case symbol_kind::S_void_decl: // void_decl
        value.move< cynth::syn::category::Declaration > (YY_MOVE (s.value));
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
        value.move< cynth::syn::category::Expression > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_cat_range_decl: // cat_range_decl
      case symbol_kind::S_paren_range_decl: // paren_range_decl
        value.move< cynth::syn::category::RangeDeclaration > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_cat_statement: // cat_statement
      case symbol_kind::S_pure: // pure
        value.move< cynth::syn::category::Statement > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_cat_type: // cat_type
      case symbol_kind::S_paren_type: // paren_type
      case symbol_kind::S_void_type: // void_type
        value.move< cynth::syn::category::Type > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_add: // node_add
        value.move< cynth::syn::node::Add > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_and: // node_and
        value.move< cynth::syn::node::And > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_application: // node_application
        value.move< cynth::syn::node::Application > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_array: // node_array
        value.move< cynth::syn::node::Array > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_array_type: // node_array_type
        value.move< cynth::syn::node::ArrayType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_assignment: // node_assignment
        value.move< cynth::syn::node::Assignment > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_auto: // node_auto
        value.move< cynth::syn::node::Auto > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_block: // node_block
        value.move< cynth::syn::node::Block > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_bool: // node_bool
        value.move< cynth::syn::node::Bool > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_buffer_type: // node_buffer_type
        value.move< cynth::syn::node::BufferType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_const_type: // node_const_type
        value.move< cynth::syn::node::ConstType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_conversion: // node_conversion
        value.move< cynth::syn::node::Conversion > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_declaration: // node_declaration
        value.move< cynth::syn::node::Declaration > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_definition: // node_definition
        value.move< cynth::syn::node::Definition > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_div: // node_div
        value.move< cynth::syn::node::Div > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_eq: // node_eq
        value.move< cynth::syn::node::Eq > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_expr_for: // node_expr_for
        value.move< cynth::syn::node::ExprFor > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_expr_if: // node_expr_if
        value.move< cynth::syn::node::ExprIf > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_float: // node_float
        value.move< cynth::syn::node::Float > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_for: // node_for
        value.move< cynth::syn::node::For > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_function_def: // node_function_def
        value.move< cynth::syn::node::FunDef > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_function: // node_function
        value.move< cynth::syn::node::Function > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_function_type: // node_function_type
        value.move< cynth::syn::node::FunctionType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_ge: // node_ge
        value.move< cynth::syn::node::Ge > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_gt: // node_gt
        value.move< cynth::syn::node::Gt > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_if: // node_if
        value.move< cynth::syn::node::If > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_in_type: // node_in_type
        value.move< cynth::syn::node::InType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_int: // node_int
        value.move< cynth::syn::node::Int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_le: // node_le
        value.move< cynth::syn::node::Le > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_lt: // node_lt
        value.move< cynth::syn::node::Lt > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_minus: // node_minus
        value.move< cynth::syn::node::Minus > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_mod: // node_mod
        value.move< cynth::syn::node::Mod > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_mul: // node_mul
        value.move< cynth::syn::node::Mul > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_name: // node_name
        value.move< cynth::syn::node::Name > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_ne: // node_ne
        value.move< cynth::syn::node::Ne > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_not: // node_not
        value.move< cynth::syn::node::Not > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_or: // node_or
        value.move< cynth::syn::node::Or > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_out_type: // node_out_type
        value.move< cynth::syn::node::OutType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_plus: // node_plus
        value.move< cynth::syn::node::Plus > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_pow: // node_pow
        value.move< cynth::syn::node::Pow > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_range_decl: // node_range_decl
        value.move< cynth::syn::node::RangeDecl > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_range_to: // node_range_to
        value.move< cynth::syn::node::RangeTo > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_range_to_by: // node_range_to_by
        value.move< cynth::syn::node::RangeToBy > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_return: // node_return
        value.move< cynth::syn::node::Return > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_spread: // node_spread
        value.move< cynth::syn::node::Spread > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_string: // node_string
        value.move< cynth::syn::node::String > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_sub: // node_sub
        value.move< cynth::syn::node::Sub > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_subscript: // node_subscript
        value.move< cynth::syn::node::Subscript > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_type_def: // node_type_def
        value.move< cynth::syn::node::TypeDef > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_type_name: // node_type_name
        value.move< cynth::syn::node::TypeName > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_when: // node_when
        value.move< cynth::syn::node::When > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_node_while: // node_while
        value.move< cynth::syn::node::While > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_array_elem_list: // array_elem_list
        value.move< esl::component_vector<cynth::syn::category::ArrayElement> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_decl_list: // decl_list
        value.move< esl::component_vector<cynth::syn::category::Declaration> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr_list: // expr_list
        value.move< esl::component_vector<cynth::syn::category::Expression> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_range_decl_list: // range_decl_list
        value.move< esl::component_vector<cynth::syn::category::RangeDeclaration> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< esl::component_vector<cynth::syn::category::Statement> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_list: // type_list
        value.move< esl::component_vector<cynth::syn::category::Type> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_start: // start
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_NAME: // NAME
      case symbol_kind::S_TYPENAME: // TYPENAME
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_FLOAT: // FLOAT
      case symbol_kind::S_STRING: // STRING
        value.move< std::string > (YY_MOVE (s.value));
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
#line 4218 "inc/parser.hpp"


// "%code provides" blocks.
#line 13 "gen/parser.y"


    namespace yy {

        parser::symbol_type yylex ();

    }


#line 4232 "inc/parser.hpp"


#endif // !YY_YY_INC_PARSER_HPP_INCLUDED
