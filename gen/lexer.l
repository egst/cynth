%{

#include "parser.hpp"

#define YY_DECL yy::parser::symbol_type yy::yylex ()

using namespace yy;

%}

%option noyywrap

blank    [ \t\r]
endl     \n
comment  ("//"|#).*
name     [a-z][a-zA-Z0-9_]*
typeName [A-Z][a-zA-Z0-9_]*
int      [0-9]+([eE][+-]?[0-9]+)?
float    ([0-9]+\.[0-9]*|\.[0-9]+)([eE][+-]?[0-9]+)?
string   (\"([^"\\]|\\.)*\"|'([^'\\]|\\.)*')
return   (?i:return)
if       (?i:if)
else     (?i:else)
when     (?i:when)
while    (?i:while)
for      (?i:for)
in       (?i:in)
out      (?i:out)
to       (?i:to)
by       (?i:by)
type     (?i:type)
buffer   (?i:buffer)
fn       (?i:fn)
true     (?i:true)
false    (?i:false)
const    (?i:const)
void     (?i:void)

%%

{blank}+
{endl}+
{comment}

{return}   return parser::make_RETURN();
{if}       return parser::make_IF();
{else}     return parser::make_ELSE();
{when}     return parser::make_WHEN();
{while}    return parser::make_WHILE();
{for}      return parser::make_FOR();
{in}       return parser::make_IN();
{out}      return parser::make_OUT();
{to}       return parser::make_TO();
{by}       return parser::make_BY();
{type}     return parser::make_TYPE();
{buffer}   return parser::make_BUFFER();
{fn}       return parser::make_FN();
{true}     return parser::make_TRUE();
{false}    return parser::make_FALSE();
{const}    return parser::make_CONST();
{void}     return parser::make_VOID();

{name}     return parser::make_NAME(yytext);
{typeName} return parser::make_TYPENAME(yytext);

{int}      return parser::make_INT(yytext);
{float}    return parser::make_FLOAT(yytext);
{string}   return parser::make_STRING(yytext);

"("        return parser::make_OPAREN();
")"        return parser::make_CPAREN();
"["        return parser::make_OBRACK();
"]"        return parser::make_CBRACK();
"{"        return parser::make_OBRACE();
"}"        return parser::make_CBRACE();
"+"        return parser::make_ADD();
"-"        return parser::make_SUB();
"*"        return parser::make_MUL();
"/"        return parser::make_DIV();
"%"        return parser::make_MOD();
"**"       return parser::make_POW();
"!"        return parser::make_NOT();
"&&"       return parser::make_AND();
"||"       return parser::make_OR();
"="        return parser::make_ASSGN();
 /*
"+="       return parser::make_ADDASSGN();
"-="       return parser::make_SUBASSGN();
"*="       return parser::make_MULTASSGN();
"/="       return parser::make_DIVASSGN();
"%="       return parser::make_MODASSGN();
"^="       return parser::make_OWASSGN();
"&="       return parser::make_ANDASSGN();
"|="       return parser::make_ORASSGN();
*/
"=="       return parser::make_EQ();
"!="       return parser::make_NE();
">="       return parser::make_GE();
"<="       return parser::make_LE();
">"        return parser::make_GT();
"<"        return parser::make_LT();
","        return parser::make_COMMA();
 /*
"."        return parser::make_DOT();
".."       return parser::make_DOT2();
*/
"..."      return parser::make_ELIP();
 /*
":"        return parser::make_COLON();
"::"       return parser::make_COL2();
*/
";"        return parser::make_SEMI();
"$"        return parser::make_AUTO();

.          return parser::make_ILLEGAL();
