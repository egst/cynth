%code requires {
    #include "ast.hpp"
    #include "util.hpp"

    #include <string>
    #include <vector>
    #include <utility>
}

%code provides {
    namespace yy {
        parser::symbol_type yylex ();
    }
}

%require "3.2"
%language "c++"

%define api.token.constructor
%define api.value.type variant
%define api.value.automove
%parse-param { cynth::ast::node::Block & result }

%token <std::string> NAME
%token <std::string> TYPENAME
%token <std::string> INTEGER
%token <std::string> DECIMAL
%token <std::string> STRING
%token IF
%token ELSE
%token WHEN
%token TYPE
%token FN
%token BUFFER
%token AUTO
%token ASSGN
%token SEMI
%token COMMA
%token TO
%token BY
%token DOT3
%token RETURN
%token OPAREN
%token CPAREN
%token OBRACE
%token CBRACE
%token OBRACK
%token CBRACK
%token ADD
%token SUB
%token MUL
%token DIV
%token MOD
%token POW
%token NOT
%token AND
%token OR
%token EQ
%token NE
%token GE
%token LE
%token GT
%token LT

%nterm <int> start
%nterm <cynth::ast::category::Type>        type
%nterm <cynth::ast::category::Statement>   statement
%nterm <cynth::ast::category::Statement>   pure
%nterm <cynth::ast::category::Expression>  expression
%nterm <cynth::ast::category::Expression>  expr_or
%nterm <cynth::ast::category::Expression>  expr_and
%nterm <cynth::ast::category::Expression>  expr_eq
%nterm <cynth::ast::category::Expression>  expr_ord
%nterm <cynth::ast::category::Expression>  expr_add
%nterm <cynth::ast::category::Expression>  expr_mul
%nterm <cynth::ast::category::Expression>  expr_pow
%nterm <cynth::ast::category::Expression>  expr_pre
%nterm <cynth::ast::category::Expression>  expr_post
%nterm <cynth::ast::category::Expression>  expr_atom
%nterm <cynth::ast::category::Expression>  expr_right
%nterm <cynth::ast::category::Declaration> declaration
/*%nterm <cynth::ast::category::ArrayElem>   array_elem*/

/* Expressions: */
%nterm <cynth::ast::node::Or>          or
%nterm <cynth::ast::node::And>         and
%nterm <cynth::ast::node::Eq>          eq
%nterm <cynth::ast::node::Ne>          ne
%nterm <cynth::ast::node::Ge>          ge
%nterm <cynth::ast::node::Le>          le
%nterm <cynth::ast::node::Gt>          gt
%nterm <cynth::ast::node::Lt>          lt
%nterm <cynth::ast::node::Add>         add
%nterm <cynth::ast::node::Sub>         sub
%nterm <cynth::ast::node::Mul>         mul
%nterm <cynth::ast::node::Div>         div
%nterm <cynth::ast::node::Mod>         mod
%nterm <cynth::ast::node::Pow>         pow
%nterm <cynth::ast::node::Plus>        plus
%nterm <cynth::ast::node::Minus>       minus
%nterm <cynth::ast::node::Not>         not
%nterm <cynth::ast::node::Application> application
%nterm <cynth::ast::node::Conversion>  conversion
%nterm <cynth::ast::node::Subscript>   subscript

/* Types: */
%nterm <cynth::ast::node::Auto>          auto
%nterm <cynth::ast::node::FunctionType>  function_type
%nterm <cynth::ast::node::ArrayType>     array_type
%nterm <cynth::ast::node::DeclArrayType> decl_array_type
%nterm <cynth::ast::node::AutoArrayType> auto_array_type
%nterm <cynth::ast::node::BufferType>    buffer_type
%nterm <cynth::ast::node::TypeDecl>      type_decl

/* Declarations: */
%nterm <cynth::ast::node::SingleDecl> single_decl

/* Pure statements: */
%nterm <cynth::ast::node::Definition>  definition
%nterm <cynth::ast::node::Assignment>  assignment
%nterm <cynth::ast::node::TypeDef>     type_def
%nterm <cynth::ast::node::Return>      return
%nterm <cynth::ast::node::If>          if
%nterm <cynth::ast::node::When>        when
%nterm <cynth::ast::node::FunctionDef> function_def

/* Right consuming: */
%nterm <cynth::ast::node::ExprIf>   expr_if
%nterm <cynth::ast::node::Function> function

/* Names: */
%nterm <cynth::ast::node::Name>     name
%nterm <cynth::ast::node::TypeName> type_name

/* Literals: */
%nterm <cynth::ast::node::Integer> integer
%nterm <cynth::ast::node::Decimal> decimal
%nterm <cynth::ast::node::String>  string
/*%nterm <cynth::ast::node::Array>   array*/

/* Array literal elements: */
/*%nterm <cynth::ast::node::RangeTo>   range_to
%nterm <cynth::ast::node::RangeToBy> range_to_by
%nterm <cynth::ast::node::Spread>    spread*/

/* Composite: */
%nterm <cynth::ast::node::Block>           block
%nterm <cynth::ast::category::Expression>  paren_expr
%nterm <cynth::ast::category::Declaration> paren_decl
%nterm <cynth::ast::category::Type>        paren_type
%nterm <cynth::ast::category::Expression>  void
%nterm <cynth::ast::category::Type>        void_type
%nterm <cynth::ast::category::Declaration> void_decl

/* Temporary: */
%nterm <std::vector<cynth::ast::category::Expression  *>> expr_list
%nterm <std::vector<cynth::ast::category::Statement   *>> stmt_list
%nterm <std::vector<cynth::ast::category::Declaration *>> decl_list
%nterm <std::vector<cynth::ast::category::Type        *>> type_list
/*%nterm <std::vector<cynth::ast::category::ArrayElem   *>> array_elem_list*/

%%

start:
     %empty               { result = {{}};    } |
     stmt_list[list]      { result = {$list}; } |
     stmt_list[list] SEMI { result = {$list}; }

statement:
    pure       { $$ = $1; } |
    expression { $$ = $1; }

pure:
    declaration  { $$ = $1; } |
    definition   { $$ = $1; } |
    assignment   { $$ = $1; } |
    type_def     { $$ = $1; } |
    function_def { $$ = $1; } |
    return       { $$ = $1; } |
    if           { $$ = $1; } |
    when         { $$ = $1; }

expression:
    expr_or |
    expr_right

expr_or:
    or { $$ = $1; } |
    expr_and

expr_and:
    and { $$ = $1; } |
    expr_eq

expr_eq:
    eq { $$ = $1; } |
    ne { $$ = $1; } |
    expr_ord

expr_ord:
    ge { $$ = $1; } |
    le { $$ = $1; } |
    gt { $$ = $1; } |
    lt { $$ = $1; } |
    expr_add

expr_add:
    add { $$ = $1; } |
    sub { $$ = $1; } |
    expr_mul

expr_mul:
    mul { $$ = $1; } |
    div { $$ = $1; } |
    mod { $$ = $1; } |
    expr_pow

expr_pow:
    pow { $$ = $1; } |
    expr_pre

expr_pre:
    minus { $$ = $1; } |
    plus  { $$ = $1; } |
    not   { $$ = $1; } |
    expr_post

expr_post:
    application { $$ = $1; } |
    conversion  { $$ = $1; } |
    subscript   { $$ = $1; } |
    expr_atom

expr_atom:
    name    { $$ = $1; } |
    integer { $$ = $1; } |
    decimal { $$ = $1; } |
    string  { $$ = $1; } |
    block   { $$ = $1; } |
    /*array   { $$ = $1; } |*/
    paren_expr

expr_right:
    expr_if  { $$ = $1; } |
    function { $$ = $1; }

or:  expr_mul[lhs] OR  expr_pow[rhs] { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }
and: expr_mul[lhs] AND expr_pow[rhs] { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }
eq:  expr_mul[lhs] EQ  expr_pow[rhs] { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }
ne:  expr_mul[lhs] NE  expr_pow[rhs] { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }
ge:  expr_mul[lhs] GE  expr_pow[rhs] { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }
le:  expr_mul[lhs] LE  expr_pow[rhs] { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }
gt:  expr_mul[lhs] GT  expr_pow[rhs] { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }
lt:  expr_mul[lhs] LT  expr_pow[rhs] { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }
add: expr_mul[lhs] ADD expr_pow[rhs] { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }
sub: expr_mul[lhs] SUB expr_pow[rhs] { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }
mul: expr_mul[lhs] MUL expr_pow[rhs] { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }
div: expr_mul[lhs] DIV expr_pow[rhs] { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }
mod: expr_mul[lhs] MOD expr_pow[rhs] { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }

pow: expr_pre[lhs] POW expr_pow[rhs] { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }

minus: SUB expr_pre[rhs] { $$ = {cynth::util::alloc($rhs)}; }
plus:  ADD expr_pre[rhs] { $$ = {cynth::util::alloc($rhs)}; }
not:   NOT expr_pre[rhs] { $$ = {cynth::util::alloc($rhs)}; }

application: expr_post[lhs] paren_expr[rhs]               { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; } |
             expr_post[lhs] void[rhs]                     { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }
conversion:  type[lhs]      paren_expr[rhs]               { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }
subscript:   expr_post[lhs] OBRACK expression[rhs] CBRACK { $$ = {cynth::util::alloc($lhs), cynth::util::alloc($rhs)}; }

type:
    auto            { $$ = $1; } |
    type_name       { $$ = $1; } |
    function_type   { $$ = $1; } |
    array_type      { $$ = $1; } |
    buffer_type     { $$ = $1; } |
    decl_array_type { $$ = $1; } |
    auto_array_type { $$ = $1; } |
    type_decl       { $$ = $1; } |
    paren_type      { $$ = $1; }

function_type:
    type[out]      paren_type[in] { $$ = {cynth::util::alloc($out), cynth::util::alloc($in)}; } |
    void_type[out] paren_type[in] { $$ = {cynth::util::alloc($out), cynth::util::alloc($in)}; } |
    type[out]      void_type[in]       { $$ = {cynth::util::alloc($out), cynth::util::alloc($in)}; } |
    void_type[out] void_type[in]       { $$ = {cynth::util::alloc($out), cynth::util::alloc($in)}; }

array_type:
    type   OBRACK expression[size] CBRACK { $$ = {cynth::util::alloc($type), cynth::util::alloc($size)}; }
buffer_type:
    BUFFER OBRACK expression[size] CBRACK { $$ = {cynth::util::alloc($size)}; }
auto_array_type:
    type[val_type] OBRACK AUTO CBRACK { $$ = {cynth::util::alloc($val_type)}; } |
    type[val_type] OBRACK      CBRACK { $$ = {cynth::util::alloc($val_type)}; }
decl_array_type:
    type[val_type] OBRACK declaration[size_decl] CBRACK { $$ = {cynth::util::alloc($val_type), cynth::util::alloc($size_decl)}; }

declaration:
    single_decl { $$ = $1; } |
    paren_decl  { $$ = $1; }

single_decl: type name      { $$ = {$name, cynth::util::alloc($type)}; }
type_decl:   TYPE type_name { $$ = {$type_name};                       }

definition: declaration[target]    ASSGN expression[val] { $$ = {cynth::util::alloc($target), cynth::util::alloc($val)}; }
assignment: name[target]           ASSGN expression[val] { $$ = {$target,                     cynth::util::alloc($val)}; }
type_def:   TYPE type_name[target] ASSGN type[val]       { $$ = {$target,                     cynth::util::alloc($val)}; }

return:
    RETURN expression[val] { $$ = {cynth::util::alloc($val)}; } |
    RETURN void[val]       { $$ = {cynth::util::alloc($val)}; } |
    RETURN                 { $$ = {cynth::util::alloc(cynth::ast::category::Expression{cynth::ast::node::Tuple{}})}; }

if:      IF paren_expr[cond]   pure[pos]       ELSE pure[neg]       { $$ = {cynth::util::alloc($cond), cynth::util::alloc($pos), cynth::util::alloc($neg)}; }
expr_if: IF paren_expr[cond]   expression[pos] ELSE expression[neg] { $$ = {cynth::util::alloc($cond), cynth::util::alloc($pos), cynth::util::alloc($neg)}; }
when:    WHEN paren_expr[cond] statement[pos]                       { $$ = {cynth::util::alloc($cond), cynth::util::alloc($pos)}; }

function_def:
    type[out]      name paren_decl[in] expression[body] { $$ = {cynth::util::alloc($out), cynth::util::alloc($in), $name, cynth::util::alloc($body)}; } |
    void_type[out] name paren_decl[in] expression[body] { $$ = {cynth::util::alloc($out), cynth::util::alloc($in), $name, cynth::util::alloc($body)}; } |
    type[out]      name void_decl[in]  expression[body] { $$ = {cynth::util::alloc($out), cynth::util::alloc($in), $name, cynth::util::alloc($body)}; } |
    void_type[out] name void_decl[in]  expression[body] { $$ = {cynth::util::alloc($out), cynth::util::alloc($in), $name, cynth::util::alloc($body)}; }

function:
    type[out]      FN paren_decl[in] expression[body] { $$ = {cynth::util::alloc($out), cynth::util::alloc($in), cynth::util::alloc($body)}; } |
    void_type[out] FN paren_decl[in] expression[body] { $$ = {cynth::util::alloc($out), cynth::util::alloc($in), cynth::util::alloc($body)}; } |
    type[out]      FN void_decl[in]  expression[body] { $$ = {cynth::util::alloc($out), cynth::util::alloc($in), cynth::util::alloc($body)}; } |
    void_type[out] FN void_decl[in]  expression[body] { $$ = {cynth::util::alloc($out), cynth::util::alloc($in), cynth::util::alloc($body)}; }

auto:      AUTO     { $$ = {};   }
type_name: TYPENAME { $$ = {$1}; }
name:      NAME     { $$ = {$1}; }
integer:   INTEGER  { $$ = {cynth::util::stoi($1)}; }
decimal:   DECIMAL  { $$ = {std::stof($1)};         }
string:    STRING   { $$ = {cynth::util::trim($1)}; }

void:      OPAREN CPAREN { $$ = cynth::ast::node::Tuple{};     }
void_type: OPAREN CPAREN { $$ = cynth::ast::node::TupleType{}; }
void_decl: OPAREN CPAREN { $$ = cynth::ast::node::TupleDecl{}; }

/*array_elem:
    range_to    { $$ = $1; } |
    range_to_by { $$ = $1; } |
    spread      { $$ = $1; } |
    expression  { $$ = $1; }

range_to:    expression[from] TO expression[to]                   { $$ = {cynth::util::alloc($from), cynth::util::alloc($to)}; }
range_to_by: expression[from] TO expression[to] BY expression[by] { $$ = {cynth::util::alloc($from), cynth::util::alloc($to), cynth::util::alloc($by)}; }
spread:      DOT3 expression[container]                           { $$ = {cynth::util::alloc($container)}; }

array:
    OBRACK                            CBRACK { $$ = {{}};    } |
    OBRACK array_elem_list[list]      CBRACK { $$ = {$list}; } |
    OBRACK array_elem_list[list] SEMI CBRACK { $$ = {$list}; }
array_elem_list:
    array_elem[first] {
        $$ = {cynth::util::alloc($first)};
    } |
    array_elem_list[rest] COMMA array_elem[next] {
        $$ = cynth::util::push(cynth::util::alloc($next), $rest);
    }*/

block:
    OBRACE                      CBRACE { $$ = {{}};    } |
    OBRACE stmt_list[list]      CBRACE { $$ = {$list}; } |
    OBRACE stmt_list[list] SEMI CBRACE { $$ = {$list}; }
stmt_list:
    statement[first] {
        $$ = {cynth::util::alloc($first)};
    } |
    stmt_list[rest] SEMI statement[next] {
        $$ = cynth::util::push(cynth::util::alloc($next), $rest);
    }

paren_type:
    OPAREN type[single]          CPAREN { $$ = $single; } |
    OPAREN type_list[list]       CPAREN { $$ = cynth::ast::node::TupleType{$list}; } |
    OPAREN type_list[list] COMMA CPAREN { $$ = cynth::ast::node::TupleType{$list}; }
type_list:
    type[first] COMMA type[second] {
        $$ = {cynth::util::alloc($first), cynth::util::alloc($second)};
    } |
    type_list[rest] COMMA type[next] {
        $$ = cynth::util::push(cynth::util::alloc($next), $rest);
    }

paren_expr:
    OPAREN expression[single]    CPAREN { $$ = $single; } |
    OPAREN expr_list[list]       CPAREN { $$ = cynth::ast::node::Tuple{$list}; } |
    OPAREN expr_list[list] COMMA CPAREN { $$ = cynth::ast::node::Tuple{$list}; }
expr_list:
    expression[first] COMMA expression[second] {
        $$ = {cynth::util::alloc($first), cynth::util::alloc($second)};
    } |
    expr_list[rest] COMMA expression[next] {
        $$ = cynth::util::push(cynth::util::alloc($next), $rest);
    }

paren_decl:
    OPAREN declaration[single]   CPAREN { $$ = $single; } |
    OPAREN decl_list[list]       CPAREN { $$ = cynth::ast::node::TupleDecl{$list}; } |
    OPAREN decl_list[list] COMMA CPAREN { $$ = cynth::ast::node::TupleDecl{$list}; }
decl_list:
    declaration[first] COMMA declaration[second] {
        $$ = {cynth::util::alloc($first), cynth::util::alloc($second)};
    } |
    decl_list[rest] COMMA declaration[next] {
        $$ = cynth::util::push(cynth::util::alloc($next), $rest);
    }

%%

void yy::parser::error (std::string const & msg) {
    std::cerr << msg << '\n';
}
