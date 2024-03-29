%code requires {

    #include <string>

    #include "esl/string.hpp"
    #include "esl/containers.hpp"

    #include "config.hpp"
    #include "syn/all.hpp"

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
%parse-param { std::pair<cynth::syn::node::Block &, bool &> result }

%token <std::string> NAME
%token <std::string> TYPENAME
%token <std::string> INT
%token <std::string> FLOAT
%token <std::string> STRING
%token IF
%token ELSE
%token WHEN
%token FOR
%token WHILE
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
%token VOID
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
%token <std::string> ILLEGAL

/**
 *  Naming convention:
 *  Non-terminals representing an AST node or category directly are prefixed with `node_` or `cat_` respectively.
 *  Oter non-terminals have no such prefix. Such terminals include:
 *  * Temporary structures that will form a part of an AST node. E.g. expr_list, stmt_list.
 *  * Purely syntactic categories. E.g. pure, expr_or.
 *  * Elements that may be represented by a single AST node as well as the tuple equivalent thereof depending on the number of elements. E.g. paren_expr, paren_type.
 *  * Elements representing a node with specific properties. E.g. void, void_type.
 */

%nterm <int> start

/* [categories] */
%nterm <cynth::syn::category::Type>             cat_type
%nterm <cynth::syn::category::Declaration>      cat_declaration
%nterm <cynth::syn::category::RangeDeclaration> cat_range_decl
%nterm <cynth::syn::category::ArrayElement>     cat_array_elem
%nterm <cynth::syn::category::Expression>       cat_expression
%nterm <cynth::syn::category::Statement>        cat_statement

/* [syntactic categories] */
%nterm <cynth::syn::category::Statement>   pure
%nterm <cynth::syn::category::Expression>  expr_or
%nterm <cynth::syn::category::Expression>  expr_and
%nterm <cynth::syn::category::Expression>  expr_eq
%nterm <cynth::syn::category::Expression>  expr_ord
%nterm <cynth::syn::category::Expression>  expr_add
%nterm <cynth::syn::category::Expression>  expr_mul
%nterm <cynth::syn::category::Expression>  expr_pow
%nterm <cynth::syn::category::Expression>  expr_pre
%nterm <cynth::syn::category::Expression>  expr_post
%nterm <cynth::syn::category::Expression>  expr_atom
%nterm <cynth::syn::category::Expression>  expr_or_right
%nterm <cynth::syn::category::Expression>  expr_and_right
%nterm <cynth::syn::category::Expression>  expr_eq_right
%nterm <cynth::syn::category::Expression>  expr_ord_right
%nterm <cynth::syn::category::Expression>  expr_add_right
%nterm <cynth::syn::category::Expression>  expr_mul_right
%nterm <cynth::syn::category::Expression>  expr_pow_right
%nterm <cynth::syn::category::Expression>  expr_pre_right
%nterm <cynth::syn::category::Expression>  expr_right
%nterm <cynth::syn::category::Expression>  expr_assgn_target

/* [types] */
%nterm <cynth::syn::category::Type>        paren_type
%nterm <cynth::syn::category::Type>        void_type
%nterm <cynth::syn::node::Auto>            node_auto
%nterm <cynth::syn::node::TypeName>        node_type_name
%nterm <cynth::syn::node::ConstType>       node_const_type
%nterm <cynth::syn::node::InType>          node_in_type
%nterm <cynth::syn::node::OutType>         node_out_type
%nterm <cynth::syn::node::FunctionType>    node_function_type
%nterm <cynth::syn::node::ArrayType>       node_array_type
%nterm <cynth::syn::node::BufferType>      node_buffer_type
/*
%nterm <cynth::syn::node::TypeDecl>        node_type_decl
*/

/* [declarations] */
%nterm <cynth::syn::category::Declaration>      paren_decl
%nterm <cynth::syn::category::RangeDeclaration> paren_range_decl
%nterm <cynth::syn::category::Declaration>      void_decl
%nterm <cynth::syn::node::Declaration>          node_declaration
%nterm <cynth::syn::node::RangeDecl>            node_range_decl

/* [array elements] */
%nterm <cynth::syn::node::RangeTo>         node_range_to
%nterm <cynth::syn::node::RangeToBy>       node_range_to_by
%nterm <cynth::syn::node::Spread>          node_spread

/* [expressions] */
%nterm <cynth::syn::category::Expression>  paren_expr
/*
%nterm <cynth::syn::category::Expression>  paren_assgn_target
*/
%nterm <cynth::syn::category::Expression>  void
%nterm <cynth::syn::node::Name>            node_name
%nterm <cynth::syn::node::Block>           node_block
/* (literals) */
%nterm <cynth::syn::node::Bool>            node_bool
%nterm <cynth::syn::node::Int>             node_int
%nterm <cynth::syn::node::Float>           node_float
%nterm <cynth::syn::node::String>          node_string
%nterm <cynth::syn::node::Function>        node_function
%nterm <cynth::syn::node::Array>           node_array
/* (operators) */
%nterm <cynth::syn::node::Or>              node_or
%nterm <cynth::syn::node::And>             node_and
%nterm <cynth::syn::node::Eq>              node_eq
%nterm <cynth::syn::node::Ne>              node_ne
%nterm <cynth::syn::node::Ge>              node_ge
%nterm <cynth::syn::node::Le>              node_le
%nterm <cynth::syn::node::Gt>              node_gt
%nterm <cynth::syn::node::Lt>              node_lt
%nterm <cynth::syn::node::Add>             node_add
%nterm <cynth::syn::node::Sub>             node_sub
%nterm <cynth::syn::node::Mul>             node_mul
%nterm <cynth::syn::node::Div>             node_div
%nterm <cynth::syn::node::Mod>             node_mod
%nterm <cynth::syn::node::Pow>             node_pow
%nterm <cynth::syn::node::Plus>            node_plus
%nterm <cynth::syn::node::Minus>           node_minus
%nterm <cynth::syn::node::Not>             node_not
%nterm <cynth::syn::node::Or>              node_or_right
%nterm <cynth::syn::node::And>             node_and_right
%nterm <cynth::syn::node::Eq>              node_eq_right
%nterm <cynth::syn::node::Ne>              node_ne_right
%nterm <cynth::syn::node::Ge>              node_ge_right
%nterm <cynth::syn::node::Le>              node_le_right
%nterm <cynth::syn::node::Gt>              node_gt_right
%nterm <cynth::syn::node::Lt>              node_lt_right
%nterm <cynth::syn::node::Add>             node_add_right
%nterm <cynth::syn::node::Sub>             node_sub_right
%nterm <cynth::syn::node::Mul>             node_mul_right
%nterm <cynth::syn::node::Div>             node_div_right
%nterm <cynth::syn::node::Mod>             node_mod_right
%nterm <cynth::syn::node::Pow>             node_pow_right
%nterm <cynth::syn::node::Plus>            node_plus_right
%nterm <cynth::syn::node::Minus>           node_minus_right
%nterm <cynth::syn::node::Not>             node_not_right
%nterm <cynth::syn::node::Application>     node_application
%nterm <cynth::syn::node::Conversion>      node_conversion
%nterm <cynth::syn::node::Subscript>       node_subscript
%nterm <cynth::syn::node::ExprIf>          node_expr_if
%nterm <cynth::syn::node::ExprFor>         node_expr_for

/* [statements] */
%nterm <cynth::syn::node::Definition>      node_definition
%nterm <cynth::syn::node::Assignment>      node_assignment
%nterm <cynth::syn::node::FunDef>          node_function_def
%nterm <cynth::syn::node::TypeDef>         node_type_def
%nterm <cynth::syn::node::Return>          node_return
%nterm <cynth::syn::node::If>              node_if
%nterm <cynth::syn::node::When>            node_when
%nterm <cynth::syn::node::For>             node_for
%nterm <cynth::syn::node::While>           node_while

/* [temporary structures] */
%nterm <esl::component_vector<cynth::syn::category::Type>>             type_list
%nterm <esl::component_vector<cynth::syn::category::Declaration>>      decl_list
%nterm <esl::component_vector<cynth::syn::category::RangeDeclaration>> range_decl_list
%nterm <esl::component_vector<cynth::syn::category::ArrayElement>>     array_elem_list
%nterm <esl::component_vector<cynth::syn::category::Expression>>       expr_list
%nterm <esl::component_vector<cynth::syn::category::Statement>>        stmt_list

%%

start:
    %empty {
        result.first  = {};
        result.second = true;
    } |
    stmt_list[list] {
        result.first  = {$list};
        result.second = true;
    } |
    stmt_list[list] SEMI {
        result.first  = {$list};
        result.second = true;
    } |
    ILLEGAL[token] {
        result.first  = {};
        result.second = true;
        std::cout << "invalid token:" << $token << '\n';
    } |
    error {
        result.first  = {};
        result.second = false;
    }

/* [categories] */

cat_declaration:
    node_declaration { $$ = $1; } |
    paren_decl       { $$ = $1; }

cat_range_decl:
    node_range_decl  { $$ = $1; } |
    paren_range_decl { $$ = $1; }

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
    /*
    node_type_decl     { $$ = $1; } |
    */
    node_const_type    { $$ = $1; } |
    node_in_type       { $$ = $1; } |
    node_out_type      { $$ = $1; } |
    paren_type         { $$ = $1; }

cat_expression:
    expr_or       { $$ = $1; } |
    expr_or_right { $$ = $1; }

cat_statement:
    pure           { $$ = $1; } |
    cat_expression { $$ = $1; }

/* [syntactic categories] */

pure:
    cat_declaration   { $$ = $1; } |
    node_definition   { $$ = $1; } |
    node_assignment   { $$ = $1; } |
    node_type_def     { $$ = $1; } |
    node_function_def { $$ = $1; } |
    node_return       { $$ = $1; } |
    node_if           { $$ = $1; } |
    node_for          { $$ = $1; } |
    node_while        { $$ = $1; } |
    node_when         { $$ = $1; }

expr_or:
    node_or  { $$ = $1; } |
    expr_and { $$ = $1; }

expr_or_right:
    node_or_right  { $$ = $1; } |
    expr_and_right { $$ = $1; }

expr_and:
    node_and { $$ = $1; } |
    expr_eq  { $$ = $1; }

expr_and_right:
    node_and_right { $$ = $1; } |
    expr_eq_right  { $$ = $1; }

expr_eq:
    node_eq  { $$ = $1; } |
    node_ne  { $$ = $1; } |
    expr_ord { $$ = $1; }

expr_eq_right:
    node_eq_right  { $$ = $1; } |
    node_ne_right  { $$ = $1; } |
    expr_ord_right { $$ = $1; }

expr_ord:
    node_ge  { $$ = $1; } |
    node_le  { $$ = $1; } |
    node_gt  { $$ = $1; } |
    node_lt  { $$ = $1; } |
    expr_add { $$ = $1; }

expr_ord_right:
    node_ge_right  { $$ = $1; } |
    node_le_right  { $$ = $1; } |
    node_gt_right  { $$ = $1; } |
    node_lt_right  { $$ = $1; } |
    expr_add_right { $$ = $1; }

expr_add:
    node_add { $$ = $1; } |
    node_sub { $$ = $1; } |
    expr_mul { $$ = $1; }

expr_add_right:
    node_add_right { $$ = $1; } |
    node_sub_right { $$ = $1; } |
    expr_mul_right { $$ = $1; }

expr_mul:
    node_mul { $$ = $1; } |
    node_div { $$ = $1; } |
    node_mod { $$ = $1; } |
    expr_pow { $$ = $1; }

expr_mul_right:
    node_mul_right { $$ = $1; } |
    node_div_right { $$ = $1; } |
    node_mod_right { $$ = $1; } |
    expr_pow_right { $$ = $1; }

expr_pow:
    node_pow { $$ = $1; } |
    expr_pre { $$ = $1; }

expr_pow_right:
    node_pow_right { $$ = $1; } |
    expr_pre_right { $$ = $1; }

expr_pre:
    node_minus { $$ = $1; } |
    node_plus  { $$ = $1; } |
    node_not   { $$ = $1; } |
    expr_post  { $$ = $1; }

expr_pre_right:
    node_minus_right { $$ = $1; } |
    node_plus_right  { $$ = $1; } |
    node_not_right   { $$ = $1; } |
    expr_right       { $$ = $1; }

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
    node_expr_if     { $$ = $1; } |
    node_expr_for    { $$ = $1; } |
    node_function    { $$ = $1; }

expr_assgn_target:
    expr_post { $$ = $1; }

/* [types] */

paren_type:
    OPAREN cat_type[single] CPAREN {
        $$ = $single;
    } |
    OPAREN type_list[list] CPAREN {
        $$ = cynth::syn::node::TupleType{$list};
    } |
    OPAREN type_list[list] COMMA CPAREN {
        $$ = cynth::syn::node::TupleType{$list};
    }

void_type:
    OPAREN CPAREN {
        $$ = cynth::syn::node::TupleType{};
    } |
    VOID {
        $$ = cynth::syn::node::TupleType{};
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
        $$ = {.type = $type, .size = cynth::syn::category::Pattern{$size}};
    } |
    cat_type[type] OBRACK AUTO CBRACK {
        $$ = {.type = $type, .size = esl::optional_component<cynth::syn::category::Pattern>{}};
    } |
    cat_type[type] OBRACK CBRACK {
        $$ = {.type = $type, .size = esl::optional_component<cynth::syn::category::Pattern>{}};
    } |
    cat_type[type] OBRACK cat_declaration[size_decl] CBRACK {
        $$ = {.type = $type, .size = cynth::syn::category::Pattern{$size_decl}};
    }

node_buffer_type:
    BUFFER OBRACK cat_expression[size] CBRACK {
        $$ = {.size = $size};
    }

/*
node_type_decl:
    TYPE node_type_name[name] {
        $$ = {$name};
    }
*/

/* [declarations] */

paren_range_decl:
    OPAREN cat_range_decl[single] CPAREN {
        $$ = $single;
    } |
    OPAREN range_decl_list[list] CPAREN {
        $$ = cynth::syn::node::TupleRangeDecl{$list};
    } |
    OPAREN range_decl_list[list] COMMA CPAREN {
        $$ = cynth::syn::node::TupleRangeDecl{$list};
    }

paren_decl:
    OPAREN cat_declaration[single] CPAREN {
        $$ = $single;
    } |
    OPAREN decl_list[list] CPAREN {
        $$ = cynth::syn::node::TupleDecl{$list};
    } |
    OPAREN decl_list[list] COMMA CPAREN {
        $$ = cynth::syn::node::TupleDecl{$list};
    }

void_decl:
    OPAREN CPAREN {
        $$ = cynth::syn::node::TupleDecl{};
    }

node_declaration:
    cat_type[type] node_name[name] {
        $$ = {.name = $name, .type = $type};
    }

node_range_decl:
    cat_declaration[decl] IN cat_expression[range] {
        $$ = {.declaration = $decl, .range = $range};
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
        $$ = cynth::syn::node::Tuple{$list};
    } |
    OPAREN expr_list[list] COMMA CPAREN {
        $$ = cynth::syn::node::Tuple{$list};
    }

void:
    OPAREN CPAREN {
        $$ = cynth::syn::node::Tuple{};
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
        $$ = {esl::stoi<cynth::Integral>($1)};
    }

node_float:
    FLOAT {
        $$ = {std::stof($1)};
    }

node_string:
    STRING {
        $$ = {esl::trim($1)};
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
    OBRACK array_elem_list[list] COMMA CBRACK {
        $$ = {$list};
    }

/* (operators) */

node_or:
    expr_or[lhs] OR expr_and[rhs] {
        $$ = {$lhs, $rhs};
    }

node_or_right:
    expr_or[lhs] OR expr_and_right[rhs] {
        $$ = {$lhs, $rhs};
    }

node_and:
    expr_and[lhs] AND expr_eq[rhs] {
        $$ = {$lhs, $rhs};
    }

node_and_right:
    expr_and[lhs] AND expr_eq_right[rhs] {
        $$ = {$lhs, $rhs};
    }

node_eq:
    expr_eq[lhs] EQ expr_ord[rhs] {
        $$ = {$lhs, $rhs};
    }

node_eq_right:
    expr_eq[lhs] EQ expr_ord_right[rhs] {
        $$ = {$lhs, $rhs};
    }

node_ne:
    expr_eq[lhs] NE expr_ord[rhs] {
        $$ = {$lhs, $rhs};
    }

node_ne_right:
    expr_eq[lhs] NE expr_ord_right[rhs] {
        $$ = {$lhs, $rhs};
    }

node_ge:
    expr_ord[lhs] GE expr_add[rhs] {
        $$ = {$lhs, $rhs};
    }

node_ge_right:
    expr_ord[lhs] GE expr_add_right[rhs] {
        $$ = {$lhs, $rhs};
    }

node_le:
    expr_ord[lhs] LE expr_add[rhs] {
        $$ = {$lhs, $rhs};
    }

node_le_right:
    expr_ord[lhs] LE expr_add_right[rhs] {
        $$ = {$lhs, $rhs};
    }

node_gt:
    expr_ord[lhs] GT expr_add[rhs] {
        $$ = {$lhs, $rhs};
    }

node_gt_right:
    expr_ord[lhs] GT expr_add_right[rhs] {
        $$ = {$lhs, $rhs};
    }

node_lt:
    expr_ord[lhs] LT expr_add[rhs] {
        $$ = {$lhs, $rhs};
    }

node_lt_right:
    expr_ord[lhs] LT expr_add_right[rhs] {
        $$ = {$lhs, $rhs};
    }

node_add:
    expr_add[lhs] ADD expr_mul[rhs] {
        $$ = {$lhs, $rhs};
    }

node_add_right:
    expr_add[lhs] ADD expr_mul_right[rhs] {
        $$ = {$lhs, $rhs};
    }

node_sub:
    expr_add[lhs] SUB expr_mul[rhs] {
        $$ = {$lhs, $rhs};
    }

node_sub_right:
    expr_add[lhs] SUB expr_mul_right[rhs] {
        $$ = {$lhs, $rhs};
    }

node_mul:
    expr_mul[lhs] MUL expr_pow[rhs] {
        $$ = {$lhs, $rhs};
    }

node_mul_right:
    expr_mul[lhs] MUL expr_pow_right[rhs] {
        $$ = {$lhs, $rhs};
    }

node_div:
    expr_mul[lhs] DIV expr_pow[rhs] {
        $$ = {$lhs, $rhs};
    }

node_div_right:
    expr_mul[lhs] DIV expr_pow_right[rhs] {
        $$ = {$lhs, $rhs};
    }

node_mod:
    expr_mul[lhs] MOD expr_pow[rhs] {
        $$ = {$lhs, $rhs};
    }

node_mod_right:
    expr_mul[lhs] MOD expr_pow_right[rhs] {
        $$ = {$lhs, $rhs};
    }

node_pow:
    expr_pre[lhs] POW expr_pow[rhs] {
        $$ = {$lhs, $rhs};
    }

node_pow_right:
    expr_pre[lhs] POW expr_pow_right[rhs] {
        $$ = {$lhs, $rhs};
    }

node_minus:
    SUB expr_pre[arg] {
        $$ = {$arg};
    }

node_minus_right:
    SUB expr_right[arg] {
        $$ = {$arg};
    }

node_plus:
    ADD expr_pre[arg] {
        $$ = {$arg};
    }

node_plus_right:
    ADD expr_right[arg] {
        $$ = {$arg};
    }

node_not:
    NOT expr_pre[arg] {
        $$ = {$arg};
    }

node_not_right:
    NOT expr_right[arg] {
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
    } |
    expr_post[container] OBRACK CBRACK {
        $$ = {.container = $container, .location = {}};
    }

node_expr_if:
    IF paren_expr[cond] cat_expression[pos] ELSE cat_expression[neg] {
        $$ = {.condition = $cond, .positiveBranch = $pos, .negativeBranch = $neg};
    }

node_expr_for:
    FOR paren_range_decl[decl] cat_expression[body] {
        $$ = {.declarations = $decl, .body = $body};
    }

/* [statements] */

node_definition:
    cat_declaration[target] ASSGN cat_expression[val] {
        $$ = {.target = $target, .value = $val};
    }

node_assignment:
    expr_assgn_target[target] ASSGN cat_expression[val] {
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
        $$ = {cynth::syn::category::Expression{cynth::syn::node::Tuple{}}};
    }

node_if:
    IF paren_expr[cond] pure[pos] ELSE pure[neg] {
        $$ = {.condition = $cond, .positiveBranch = $pos, .negativeBranch = $neg};
    } |
    IF paren_expr[cond] pure[pos] SEMI ELSE pure[neg] {
        $$ = {.condition = $cond, .positiveBranch = $pos, .negativeBranch = $neg};
    } |
    IF paren_expr[cond] cat_expression[pos] ELSE pure[neg] {
        $$ = {.condition = $cond, .positiveBranch = cynth::syn::category::Statement{$pos}, .negativeBranch = $neg};
    } |
    IF paren_expr[cond] cat_expression[pos] SEMI ELSE pure[neg] {
        $$ = {.condition = $cond, .positiveBranch = cynth::syn::category::Statement{$pos}, .negativeBranch = $neg};
    } |
    IF paren_expr[cond] pure[pos] ELSE cat_expression[neg] {
        $$ = {.condition = $cond, .positiveBranch = $pos, .negativeBranch = cynth::syn::category::Statement{$neg}};
    } |
    IF paren_expr[cond] pure[pos] SEMI ELSE cat_expression[neg] {
        $$ = {.condition = $cond, .positiveBranch = $pos, .negativeBranch = cynth::syn::category::Statement{$neg}};
    }

node_when:
    WHEN paren_expr[cond] cat_statement[pos] {
        $$ = {.condition = $cond, .branch = $pos};
    }

node_for:
    FOR paren_range_decl[decl] pure[body] {
        $$ = {.declarations = $decl, .body = $body};
    };

node_while:
    WHILE paren_expr[cond] cat_statement[body] {
        $$ = {.condition = $cond, .body = $body};
    };

/* [temporary structures] */

array_elem_list:
    cat_array_elem[first] {
        $$ = {$first};
    } |
    array_elem_list[rest] COMMA cat_array_elem[next] {
        $$ = esl::push_back($next, $rest);
    }

stmt_list:
    cat_statement[first] {
        $$ = {$first};
    } |
    stmt_list[rest] SEMI cat_statement[next] {
        $$ = esl::push_back($next, $rest);
    }

type_list:
    cat_type[first] COMMA cat_type[second] {
        $$ = {$first, $second};
    } |
    type_list[rest] COMMA cat_type[next] {
        $$ = esl::push_back($next, $rest);
    }

expr_list:
    cat_expression[first] COMMA cat_expression[second] {
        $$ = {$first, $second};
    } |
    expr_list[rest] COMMA cat_expression[next] {
        $$ = esl::push_back($next, $rest);
    }

decl_list:
    cat_declaration[first] COMMA cat_declaration[second] {
        $$ = {$first, $second};
    } |
    decl_list[rest] COMMA cat_declaration[next] {
        $$ = esl::push_back($next, $rest);
    }

range_decl_list:
    cat_range_decl[first] COMMA cat_range_decl[second] {
        $$ = {$first, $second};
    } |
    range_decl_list[rest] COMMA cat_range_decl[next] {
        $$ = esl::push_back($next, $rest);
    }

%%

void yy::parser::error (std::string const & msg) {
    std::cerr << "parser error: " << msg << '\n';
}
