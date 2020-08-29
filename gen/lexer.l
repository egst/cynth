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
integer  [0-9]+([eE][+-]?[0-9]+)?
decimal  ([0-9]+\.[0-9]*|\.[0-9]+)([eE][+-]?[0-9]+)?
string   (\"([^"\\]|\\.)*\"|'([^'\\]|\\.)*')
return   (?i:return)
if       (?i:if)
else     (?i:else)
when     (?i:when)
while    (?i:while)
for      (?i:for)
in       (?i:in)
to       (?i:to)
by       (?i:by)
type     (?i:type)
buffer   (?i:buffer)

%%

{blank}+
{endl}+
{comment}

{return}   return parser::make_RETURN();
{if}       return parser::make_IF();
{else}     return parser::make_ELSE();
{when}     return parser::make_WHEN();
 /*
{while}    return parser::make_WHILE();
{for}      return parser::make_FOR();
{in}       return parser::make_IN();
{to}       return parser::make_TO();
{by}       return parser::make_BY();
*/
{type}     return parser::make_TYPE();
 /*
{buffer}   return parser::make_BUFFER();
*/

{name}     return parser::make_NAME(yytext);
{typeName} return parser::make_TYPENAME(yytext);

{integer}  return parser::make_INTEGER(yytext);
{decimal}  return parser::make_DECIMAL(yytext);
{string}   return parser::make_STRING(yytext);

"("        return parser::make_OPAREN();
")"        return parser::make_CPAREN();
 /*
"["        return parser::make_OBRACK();
"]"        return parser::make_CBRACK();
*/
"{"        return parser::make_OBRACE();
"}"        return parser::make_CBRACE();
 /*
"+"        return parser::make_ADD();
"-"        return parser::make_SUB();
"*"        return parser::make_MULT();
"/"        return parser::make_DIV();
"%"        return parser::make_MOD();
"^"        return parser::make_POW();
"!"        return parser::make_NOT();
"&&"       return parser::make_AND();
"||"       return parser::make_NOT();
*/
"="        return parser::make_ASGN();
 /*
"+="       return parser::make_ADDASGN();
"-="       return parser::make_SUBASGN();
"*="       return parser::make_MULTASGN();
"/="       return parser::make_DIVASGN();
"%="       return parser::make_MODASGN();
"^="       return parser::make_OWASGN();
"&="       return parser::make_ANDASGN();
"|="       return parser::make_ORASGN();
"=="       return parser::make_EQ();
"!="       return parser::make_NE();
">="       return parser::make_GE();
"<="       return parser::make_LE();
">"        return parser::make_GT();
"<"        return parser::make_LT();
*/
","        return parser::make_COMMA();
 /*
":"        return parser::make_COLON();
*/
";"        return parser::make_SEMI();
"$"        return parser::make_AUTO();
