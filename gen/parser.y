%code requires {

    #include "ast.hpp"
    #include "util/string.hpp"
    #include "util/general.hpp"

    //#include <string>
    //#include <vector>
    //#include <utility>

}

%code provides {

    namespace yy {

        parser::symbol_type yylex ();

    }

}

%require "3.2"
%language "c++"

/* TODO: %define api.namespace ... */
/*%define parse.assert*/
%define api.token.constructor
%define api.value.type variant
%define api.value.automove
%parse-param { cynth::ast::node::Block & result }

%token <std::string> NAME
%token <std::string> TYPENAME
%token <std::string> INT
%token <std::string> FLOAT
%token <std::string> STRING
%token IF
%token ELSE
%token WHEN
%token TYPE
%token FN
%token BUFFER
%token RETURN
%token TRUE
%token FALSE
%token CONST
%token AUTO
%token ASSGN
%token SEMI
%token COMMA
%token IN
%token OUT
%token TO
%token BY
%token ELIP
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
%token ILLEGAL

/*  Naming convention:
    Non-terminals representing an AST node or category directly are prefixed with `node_` or `cat_` respectively.
    Oter non-terminals have no such prefix. Such terminals include:
    * Temporary structures that will form a part of an AST node. E.g. expr_list, stmt_list.
    * Purely syntactic categories. E.g. pure, expr_or.
    * Elements that may be represented by a single AST node as well as the tuple equivalent thereof depending on the number of elements. E.g. paren_expr, paren_type.
    * Elements representing a node with specific properties. E.g. void, void_type. */

%nterm <int> start

/* [categories] */
%nterm <cynth::ast::category::Type>        cat_type
%nterm <cynth::ast::category::Declaration> cat_declaration
%nterm <cynth::ast::category::ArrayElem>   cat_array_elem
%nterm <cynth::ast::category::Expression>  cat_expression
%nterm <cynth::ast::category::Statement>   cat_statement

/* [syntactic categories] */
%nterm <cynth::ast::category::Statement>   pure
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

/* [types] */
%nterm <cynth::ast::category::Type>        paren_type
%nterm <cynth::ast::category::Type>        void_type
%nterm <cynth::ast::node::Auto>            node_auto
%nterm <cynth::ast::node::TypeName>        node_type_name
%nterm <cynth::ast::node::ConstType>       node_const_type
%nterm <cynth::ast::node::InType>          node_in_type
%nterm <cynth::ast::node::OutType>         node_out_type
%nterm <cynth::ast::node::FunctionType>    node_function_type
%nterm <cynth::ast::node::ArrayType>       node_array_type
%nterm <cynth::ast::node::BufferType>      node_buffer_type
%nterm <cynth::ast::node::TypeDecl>        node_type_decl

/* [declarations] */
%nterm <cynth::ast::category::Declaration> paren_decl
%nterm <cynth::ast::category::Declaration> void_decl
%nterm <cynth::ast::node::Declaration>     node_declaration

/* [array elements] */
%nterm <cynth::ast::node::RangeTo>         node_range_to
%nterm <cynth::ast::node::RangeToBy>       node_range_to_by
%nterm <cynth::ast::node::Spread>          node_spread

/* [expressions] */
%nterm <cynth::ast::category::Expression>  paren_expr
%nterm <cynth::ast::category::Expression>  void
%nterm <cynth::ast::node::Name>            node_name
%nterm <cynth::ast::node::Block>           node_block
/* (literals) */
%nterm <cynth::ast::node::Bool>            node_bool
%nterm <cynth::ast::node::Int>             node_int
%nterm <cynth::ast::node::Float>           node_float
%nterm <cynth::ast::node::String>          node_string
%nterm <cynth::ast::node::Function>        node_function
%nterm <cynth::ast::node::Array>           node_array
/* (operators) */
%nterm <cynth::ast::node::Or>              node_or
%nterm <cynth::ast::node::And>             node_and
%nterm <cynth::ast::node::Eq>              node_eq
%nterm <cynth::ast::node::Ne>              node_ne
%nterm <cynth::ast::node::Ge>              node_ge
%nterm <cynth::ast::node::Le>              node_le
%nterm <cynth::ast::node::Gt>              node_gt
%nterm <cynth::ast::node::Lt>              node_lt
%nterm <cynth::ast::node::Add>             node_add
%nterm <cynth::ast::node::Sub>             node_sub
%nterm <cynth::ast::node::Mul>             node_mul
%nterm <cynth::ast::node::Div>             node_div
%nterm <cynth::ast::node::Mod>             node_mod
%nterm <cynth::ast::node::Pow>             node_pow
%nterm <cynth::ast::node::Plus>            node_plus
%nterm <cynth::ast::node::Minus>           node_minus
%nterm <cynth::ast::node::Not>             node_not
%nterm <cynth::ast::node::Application>     node_application
%nterm <cynth::ast::node::Conversion>      node_conversion
%nterm <cynth::ast::node::Subscript>       node_subscript
%nterm <cynth::ast::node::ExprIf>          node_expr_if

/* [statements] */
%nterm <cynth::ast::node::Definition>      node_definition
%nterm <cynth::ast::node::Assignment>      node_assignment
%nterm <cynth::ast::node::FunctionDef>     node_function_def
%nterm <cynth::ast::node::TypeDef>         node_type_def
%nterm <cynth::ast::node::Return>          node_return
%nterm <cynth::ast::node::If>              node_if
%nterm <cynth::ast::node::When>            node_when

/* [temporary structures] */
%nterm <cynth::component_vector<cynth::ast::category::Type>>        type_list
%nterm <cynth::component_vector<cynth::ast::category::Declaration>> decl_list
%nterm <cynth::component_vector<cynth::ast::category::ArrayElem>>   array_elem_list
%nterm <cynth::component_vector<cynth::ast::category::Expression>>  expr_list
%nterm <cynth::component_vector<cynth::ast::category::Statement>>   stmt_list

%%

start:
    %empty {
        result = {};
    } |
    stmt_list[list] {
        result = {$list};
    } |
    stmt_list[list] SEMI {
        result = {$list};
    }

/* [categories] */

cat_declaration:
    node_declaration { $$ = $1; } |
    paren_decl       { $$ = $1; }

cat_array_elem:
    node_range_to    { $$ = $1; } |
    node_range_to_by { $$ = $1; } |
    node_spread      { $$ = $1; } |
    cat_expression   { $$ = $1; }

cat_type:
    node_auto          { $$ = $1; } |
    node_type_name     { $$ = $1; } |
    node_function_type { $$ = $1; } |
    node_array_type    { $$ = $1; } |
    node_buffer_type   { $$ = $1; } |
    node_type_decl     { $$ = $1; } |
    node_const_type    { $$ = $1; } |
    node_in_type       { $$ = $1; } |
    node_out_type      { $$ = $1; } |
    paren_type         { $$ = $1; }

cat_expression:
    expr_or    { $$ = $1; } |
    expr_right { $$ = $1; }

cat_statement:
    pure           { $$ = $1; } |
    cat_expression { $$ = $1; }

/* [syntactic categories] */

pure:
    node_declaration  { $$ = $1; } |
    node_definition   { $$ = $1; } |
    node_assignment   { $$ = $1; } |
    node_type_def     { $$ = $1; } |
    node_function_def { $$ = $1; } |
    node_return       { $$ = $1; } |
    node_if           { $$ = $1; } |
    node_when         { $$ = $1; }

expr_or:
    node_or  { $$ = $1; } |
    expr_and { $$ = $1; }

expr_and:
    node_and { $$ = $1; } |
    expr_eq  { $$ = $1; }

expr_eq:
    node_eq  { $$ = $1; } |
    node_ne  { $$ = $1; } |
    expr_ord { $$ = $1; }

expr_ord:
    node_ge  { $$ = $1; } |
    node_le  { $$ = $1; } |
    node_gt  { $$ = $1; } |
    node_lt  { $$ = $1; } |
    expr_add { $$ = $1; }

expr_add:
    node_add { $$ = $1; } |
    node_sub { $$ = $1; } |
    expr_mul { $$ = $1; }

expr_mul:
    node_mul { $$ = $1; } |
    node_div { $$ = $1; } |
    node_mod { $$ = $1; } |
    expr_pow { $$ = $1; }

expr_pow:
    node_pow { $$ = $1; } |
    expr_pre { $$ = $1; }

expr_pre:
    node_minus { $$ = $1; } |
    node_plus  { $$ = $1; } |
    node_not   { $$ = $1; } |
    expr_post  { $$ = $1; }

expr_post:
    node_application { $$ = $1; } |
    node_conversion  { $$ = $1; } |
    node_subscript   { $$ = $1; } |
    expr_atom        { $$ = $1; }

expr_atom:
    node_name   { $$ = $1; } |
    node_bool   { $$ = $1; } |
    node_int    { $$ = $1; } |
    node_float  { $$ = $1; } |
    node_string { $$ = $1; } |
    node_block  { $$ = $1; } |
    node_array  { $$ = $1; } |
    paren_expr  { $$ = $1; }

expr_right:
    node_expr_if  { $$ = $1; } |
    node_function { $$ = $1; }

/* [types] */

paren_type:
    OPAREN cat_type[single] CPAREN {
        $$ = $single;
    } |
    OPAREN type_list[list] CPAREN {
        $$ = cynth::ast::node::TupleType{$list};
    } |
    OPAREN type_list[list] COMMA CPAREN {
        $$ = cynth::ast::node::TupleType{$list};
    }

void_type:
    OPAREN CPAREN {
        $$ = cynth::ast::node::TupleType{};
    }

node_auto:
    AUTO {
        $$ = {};
    }

node_type_name:
    TYPENAME[name] {
        $$ = {$name};
    }

node_const_type:
    cat_type[type] CONST {
        $$ = {.type = $type};
    }

node_in_type:
    cat_type[type] IN {
        $$ = {.type = $type};
    }

node_out_type:
    cat_type[type] OUT {
        $$ = {.type = $type};
    }

node_function_type:
    cat_type[out] paren_type[in] {
        $$ = {.output = $out, .input = $in};
    } |
    void_type[out] paren_type[in] {
        $$ = {.output = $out, .input = $in};
    } |
    cat_type[out] void_type[in] {
        $$ = {.output = $out, .input = $in};
    } |
    void_type[out] void_type[in] {
        $$ = {.output = $out, .input = $in};
    }

node_array_type:
    cat_type[type] OBRACK cat_expression[size] CBRACK {
        $$ = {.type = $type, .size = cynth::ast::category::Pattern{$size}};
    } |
    cat_type[type] OBRACK AUTO CBRACK {
        $$ = {.type = $type, .size = cynth::optional_component<cynth::ast::category::Pattern>{}};
    } |
    cat_type[type] OBRACK CBRACK {
        $$ = {.type = $type, .size = cynth::optional_component<cynth::ast::category::Pattern>{}};
    } |
    cat_type[type] OBRACK cat_declaration[size_decl] CBRACK {
        $$ = {.type = $type, .size = cynth::ast::category::Pattern{$size_decl}};
    }

node_buffer_type:
    BUFFER OBRACK cat_expression[size] CBRACK {
        $$ = {.size = $size};
    }

node_type_decl:
    TYPE node_type_name[name] {
        $$ = {$name};
    }

/* [declarations] */

paren_decl:
    OPAREN cat_declaration[single] CPAREN {
        $$ = $single;
    } |
    OPAREN decl_list[list] CPAREN {
        $$ = cynth::ast::node::TupleDecl{$list};
    } |
    OPAREN decl_list[list] COMMA CPAREN {
        $$ = cynth::ast::node::TupleDecl{$list};
    }

void_decl:
    OPAREN CPAREN {
        $$ = cynth::ast::node::TupleDecl{};
    }

node_declaration:
    cat_type[type] node_name[name] {
        $$ = {.name = $name, .type = $type};
    }

/* [array elements] */

node_range_to:
    cat_expression[from] TO cat_expression[to] {
        $$ = {.from = $from, .to = $to};
    }

node_range_to_by:
    cat_expression[from] TO cat_expression[to] BY cat_expression[by] {
        $$ = {.from = $from, .to = $to, .by = $by};
    }

node_spread:
    ELIP cat_expression[container] {
        $$ = {$container};
    }

/** [expressions] */

paren_expr:
    OPAREN cat_expression[single] CPAREN {
        $$ = $single;
    } |
    OPAREN expr_list[list] CPAREN {
        $$ = cynth::ast::node::Tuple{$list};
    } |
    OPAREN expr_list[list] COMMA CPAREN {
        $$ = cynth::ast::node::Tuple{$list};
    }

void:
    OPAREN CPAREN {
        $$ = cynth::ast::node::Tuple{};
    }

node_name:
    NAME[name] {
        $$ = {$name};
    }

node_block:
    OBRACE CBRACE {
        $$ = {};
    } |
    OBRACE stmt_list[list] CBRACE {
        $$ = {$list};
    } |
    OBRACE stmt_list[list] SEMI CBRACE {
        $$ = {$list};
    }

/* (literals) */

node_bool:
    TRUE {
        $$ = {true};
    } |
    FALSE {
        $$ = {false};
    }

node_int:
    INT {
        $$ = {cynth::util::stoi($1)};
    }

node_float:
    FLOAT {
        $$ = {std::stof($1)};
    }

node_string:
    STRING {
        $$ = {cynth::util::trim($1)};
    }

node_function:
    cat_type[out] FN paren_decl[in] cat_expression[body] {
        $$ = {.output = $out, .input = $in, .body = $body};
    } |
    void_type[out] FN paren_decl[in] cat_expression[body] {
        $$ = {.output = $out, .input = $in, .body = $body};
    } |
    cat_type[out] FN void_decl[in] cat_expression[body] {
        $$ = {.output = $out, .input = $in, .body = $body};
    } |
    void_type[out] FN void_decl[in] cat_expression[body] {
        $$ = {.output = $out, .input = $in, .body = $body};
    }

node_array:
    OBRACK CBRACK {
        $$ = {};
    } |
    OBRACK array_elem_list[list] CBRACK {
        $$ = {$list};
    } |
    OBRACK array_elem_list[list] SEMI CBRACK {
        $$ = {$list};
    }

/* (operators) */

node_or:
    expr_or[lhs] OR expr_and[rhs] {
        $$ = {$lhs, $rhs};
    }

node_and:
    expr_and[lhs] AND expr_eq[rhs] {
        $$ = {$lhs, $rhs};
    }

node_eq:
    expr_eq[lhs] EQ expr_ord[rhs] {
        $$ = {$lhs, $rhs};
    }

node_ne:
    expr_eq[lhs] NE expr_ord[rhs] {
        $$ = {$lhs, $rhs};
    }

node_ge:
    expr_ord[lhs] GE expr_add[rhs] {
        $$ = {$lhs, $rhs};
    }

node_le:
    expr_ord[lhs] LE expr_add[rhs] {
        $$ = {$lhs, $rhs};
    }

node_gt:
    expr_ord[lhs] GT expr_add[rhs] {
        $$ = {$lhs, $rhs};
    }

node_lt:
    expr_ord[lhs] LT expr_add[rhs] {
        $$ = {$lhs, $rhs};
    }

node_add:
    expr_add[lhs] ADD expr_mul[rhs] {
        $$ = {$lhs, $rhs};
    }

node_sub:
    expr_add[lhs] SUB expr_mul[rhs] {
        $$ = {$lhs, $rhs};
    }

node_mul:
    expr_mul[lhs] MUL expr_pow[rhs] {
        $$ = {$lhs, $rhs};
    }

node_div:
    expr_mul[lhs] DIV expr_pow[rhs] {
        $$ = {$lhs, $rhs};
    }

node_mod:
    expr_mul[lhs] MOD expr_pow[rhs] {
        $$ = {$lhs, $rhs};
    }

node_pow:
    expr_pre[lhs] POW expr_pow[rhs] {
        $$ = {$lhs, $rhs};
    }

node_minus:
    SUB expr_pre[arg] {
        $$ = {$arg};
    }

node_plus:
    ADD expr_pre[arg] {
        $$ = {$arg};
    }

node_not:
    NOT expr_pre[arg] {
        $$ = {$arg};
    }

node_application:
    expr_post[function] paren_expr[arguments] {
        $$ = {.function = $function, .arguments = $arguments};
    } |
    expr_post[function] void[arguments] {
        $$ = {.function = $function, .arguments = $arguments};
    }

node_conversion:
    cat_type[type] paren_expr[argument] {
        $$ = {.type = $type, .argument = $argument};
    }

node_subscript:
    expr_post[container] OBRACK array_elem_list[location] CBRACK {
        $$ = {.container = $container, .location = $location};
    }

node_expr_if:
    IF paren_expr[cond] cat_expression[pos] ELSE cat_expression[neg] {
        $$ = {.condition = $cond, .positive_branch = $pos, .negative_branch = $neg};
    }

/* [statements] */

node_definition:
    cat_declaration[target] ASSGN cat_expression[val] {
        $$ = {.target = $target, .value = $val};
    }

node_assignment:
    cat_expression[target] ASSGN cat_expression[val] {
        $$ = {.target = $target, .value = $val};
    }

node_type_def:
    TYPE node_type_name[target] ASSGN cat_type[type] {
        $$ = {.target = $target, .type = $type};
    }

node_function_def:
    cat_type[out] node_name[name] paren_decl[in] cat_expression[body] {
        $$ = {.output = $out, .input = $in, .name = $name, .body = $body};
    } |
    void_type[out] node_name[name] paren_decl[in] cat_expression[body] {
        $$ = {.output = $out, .input = $in, .name = $name, .body = $body};
    } |
    cat_type[out] node_name[name] void_decl[in] cat_expression[body] {
        $$ = {.output = $out, .input = $in, .name = $name, .body = $body};
    } |
    void_type[out] node_name[name] void_decl[in] cat_expression[body] {
        $$ = {.output = $out, .input = $in, .name = $name, .body = $body};
    }

node_return:
    RETURN cat_expression[val] {
        $$ = {$val};
    } |
    RETURN void[val] {
        $$ = {$val};
    } |
    RETURN {
        $$ = {cynth::ast::category::Expression{cynth::ast::node::Tuple{}}};
    }

node_if:
    IF paren_expr[cond] pure[pos] ELSE pure[neg] {
        $$ = {.condition = $cond, .positive_branch = $pos, .negative_branch = $neg};
    }

node_when:
    WHEN paren_expr[cond] cat_statement[pos] {
        $$ = {.condition = $cond, .branch = $pos};
    }

/* [temporary structures] */

array_elem_list:
    cat_array_elem[first] {
        $$ = {$first};
    } |
    array_elem_list[rest] COMMA cat_array_elem[next] {
        $$ = cynth::util::push_back($next, $rest);
    }

stmt_list:
    cat_statement[first] {
        $$ = {$first};
    } |
    stmt_list[rest] SEMI cat_statement[next] {
        $$ = cynth::util::push_back($next, $rest);
    }

type_list:
    cat_type[first] COMMA cat_type[second] {
        $$ = {$first, $second};
    } |
    type_list[rest] COMMA cat_type[next] {
        $$ = cynth::util::push_back($next, $rest);
    }

expr_list:
    cat_expression[first] COMMA cat_expression[second] {
        $$ = {$first, $second};
    } |
    expr_list[rest] COMMA cat_expression[next] {
        $$ = cynth::util::push_back($next, $rest);
    }

decl_list:
    cat_declaration[first] COMMA cat_declaration[second] {
        $$ = {$first, $second};
    } |
    decl_list[rest] COMMA cat_declaration[next] {
        $$ = cynth::util::push_back($next, $rest);
    }

%%

void yy::parser::error (std::string const & msg) {
    // TODO: There's a syntax error every time for some reason.
    //std::cerr << "parser error: " << msg << '\n';
}
