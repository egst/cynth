%code requires {
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
}

%code provides {
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
}

%require "3.2"
%language "c++"

%define api.token.constructor
%define api.value.type variant
%define api.value.automove

%token <std::string> NAME
%token <std::string> TYPENAME

%token <std::string> INTEGER
%token <std::string> DECIMAL
%token <std::string> STRING

%token IF
%token ELSE
%token WHEN
%token TYPE
%token AUTO
%token RETURN
%token OPAREN
%token CPAREN
%token OBRACE
%token CBRACE
%token ASGN
%token SEMI
%token COMMA

%parse-param { cynth::ast::node::Block & result }

%nterm <int> start

%nterm <cynth::ast::category::Type>        type
%nterm <cynth::ast::category::Expressible> expressible
%nterm <cynth::ast::category::Statement>   statement
%nterm <cynth::ast::category::Statement>   pure

%nterm <cynth::ast::node::Integer>      integer
%nterm <cynth::ast::node::Decimal>      decimal
%nterm <cynth::ast::node::String>       string
%nterm <cynth::ast::node::Name>         name
%nterm <cynth::ast::node::TypeName>     type_name
%nterm <cynth::ast::node::FunctionType> function_type
%nterm <cynth::ast::node::TupleType>    tuple_type
%nterm <cynth::ast::node::Auto>         auto
%nterm <cynth::ast::node::Declaration>  declaration
%nterm <cynth::ast::node::Definition>   definition
%nterm <cynth::ast::node::Assignment>   assignment
%nterm <cynth::ast::node::Alias>        alias
%nterm <cynth::ast::node::Return>       return
%nterm <cynth::ast::node::Block>        block
%nterm <cynth::ast::node::If>           if
%nterm <cynth::ast::node::ExprIf>       expr_if
%nterm <cynth::ast::node::When>         when

%nterm <std::vector<cynth::ast::category::Statement *>> block_list
%nterm <std::vector<cynth::ast::category::Type      *>> function_type_list
%nterm <std::vector<cynth::ast::category::Type      *>> tuple_type_list

%%

start:
    block_list      { result = node::Block{$block_list}; } |
    block_list SEMI { result = node::Block{$block_list}; }

type:
    type_name     { $$ = category::Type{$1}; } |
    auto          { $$ = category::Type{$1}; } |
    function_type { $$ = category::Type{$1}; } |
    tuple_type    { $$ = category::Type{$1}; }

statement:
    expressible { $$ = category::Statement{$1}; } |
    pure        { $$ = $1; }

pure:
    declaration { $$ = category::Statement{$1}; } |
    definition  { $$ = category::Statement{$1}; } |
    assignment  { $$ = category::Statement{$1}; } |
    alias       { $$ = category::Statement{$1}; } |
    return      { $$ = category::Statement{$1}; } |
    if          { $$ = category::Statement{$1}; } |
    when        { $$ = category::Statement{$1}; }

expressible:
    OPAREN expressible[expr] CPAREN { $$ = $expr; } |
    name        { $$ = category::Expressible{$1}; } |
    block       { $$ = category::Expressible{$1}; } |
    integer     { $$ = category::Expressible{$1}; } |
    decimal     { $$ = category::Expressible{$1}; } |
    string      { $$ = category::Expressible{$1}; } |
    expr_if     { $$ = category::Expressible{$1}; }

integer: INTEGER {
    $$ = node::Integer{util::stoi($INTEGER)};
}
decimal: DECIMAL {
    $$ = node::Decimal{std::stof($DECIMAL)};
}
string: STRING {
    $$ = node::String{util::trim($STRING)};
}
name: NAME {
    $$ = node::Name{$NAME};
}

auto: AUTO {
    $$ = node::Auto{};
}
type_name: TYPENAME {
    $$ = node::TypeName{$TYPENAME};
}
function_type:
    type[ret] OPAREN type_list[params]       CPAREN { $$ = node::FunctionType{alloc($ret), $params}; } |
    type[ret] OPAREN type_list[params] COMMA CPAREN { $$ = node::FunctionType{alloc($ret), $params}; }
tuple_type:
    OPAREN type_list[list]       CPAREN { $$ = node::TupleType{$list}; } |
    OPAREN type_list[list] COMMA CPAREN { $$ = node::TupleType{$list}; }
pattern:
    type                                     { $$ =  }
    OPAREN type_list[params]       CPAREN { $$ = node::FunctionType{alloc($ret), $params}; } |
    OPAREN type_list[params] COMMA CPAREN { $$ = node::FunctionType{alloc($ret), $params}; }
type_list:
    %empty {
        $$ = {};
    } |
    type {
        $$ = {alloc($type)};
    } |
    function_type_list[rest] COMMA type {
        auto rest = $rest;
        $$ = util::push(alloc($type), rest);
    }

declaration: type name {
    $$ = node::Declaration{alloc($name), alloc($type)};
}
definition: type name ASGN expressible {
    $$ = node::Definition{alloc($name), alloc($type), alloc($expressible)};
}
assignment: name ASGN expressible {
    $$ = node::Assignment{alloc($name), alloc($expressible)};
}
alias: TYPE type_name ASGN type {
    $$ = node::Alias{alloc($type_name), alloc($type)};
}

return: RETURN expressible {
    $$ = node::Return{alloc($expressible)};
}
block:
    OBRACE block_list      CBRACE { $$ = node::Block{$block_list}; } |
    OBRACE block_list SEMI CBRACE { $$ = node::Block{$block_list}; }
block_list:
    %empty {
        $$ = {};
    } |
    statement {
        $$ = {alloc($statement)};
    } |
    block_list[rest] SEMI statement {
        auto rest = $rest;
        $$ = util::push(alloc($statement), rest);
    }

if: IF OPAREN expressible[cond] CPAREN pure[pos] ELSE pure[neg] {
    $$ = node::If{alloc($cond), alloc($pos), alloc($neg)};
}
expr_if: IF OPAREN expressible[cond] CPAREN expressible[pos] ELSE expressible[neg] {
    $$ = node::ExprIf{alloc($cond), alloc($pos), alloc($neg)};
}
when: WHEN OPAREN expressible[cond] CPAREN statement[pos] {
    $$ = node::When{alloc($cond), alloc($pos)};
}

%%

void yy::parser::error (std::string const & msg) {
    std::cerr << msg << '\n';
}
