%skeleton "lalr1.cc"
%require "3.7.1"
%defines

%define api.token.raw
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <iostream>
    #include <cctype>
    #include <cstring>
    #include <vector>
    #include <stack>

    #include "_ast.hpp"

    using namespace std;

    void yyerror     (const char *error);
    int  yylex       ();
    void clear_stack ();
  
    int vars ['Z' - 'A' + 1];

    stack<Expression *> nodes;
%}

%token IDENT NUMBER

%union {
    Expression * exp;   // For the expressions. Since it is a pointer, no problem.
    int          value; // For the lexical analyser. NUMBER tokens
    char         ident; // For the lexical analyser. IDENT tokens
}

/* Lets inform Bison about the type of each terminal and non-terminal */
%type <exp>   exp
%type <value> NUMBER
%type <ident> IDENT

/* Precedence information to resolve ambiguity */
%right '='
%left  '+'
%left  '*'

%%

prompt:
    exp '\n' { 
        if ($1) {
            cout << $1->value () << endl;
            clear_stack();
        }
    } |
    prompt exp '\n' {
        if ($2) {
            cout << $2->value () << endl;
            clear_stack();
        }
    } |
    error '\n' {
        clear_stack();
    };

exp:
    exp '+' exp {
        $$ = new Plus{$1, $3};
        nodes.pop();
        nodes.pop();
        nodes.push($$);
    } |
    exp '*' exp {
         $$ = new Times{$1, $3};
         nodes.pop();
         nodes.pop();
         nodes.push($$);
    } |
    IDENT {
        $$ = new Ident{&vars[$1 - 'A']};
        nodes.push($$);
    } |
    NUMBER {
        $$ = new Number{$1};
        nodes.push($$);
    } |
    IDENT '=' exp {
        vars[$1 - 'A'] = $3->value();
        $$ = $3;
        nodes.push($$);
    };

%%

int main () {
    memset(vars, 0, sizeof(vars));
    return yyparse();
}

void yyerror (char const * error) {
    cout << error << endl;
}

{
    {'+', token::Add,     {'=', token::AddAsgn}},
    {'-', token::Sub,     {'=', token::SubAsgn}},
    {'*', token::Mult,    {'=', token::MultAsgn}},
    {'/', token::Div,     {'=', token::DivAsgn}},
    {'%', token::Mod,     {'=', token::ModAsgn}},
    {'^', token::Pow,     {'=', token::PowAsgn}},
    {'=', token::Asgn,    {'=', token::Eq}},
    {'!', token::Not,     {'=', token::Ne}},
    {'<', token::Lt,      {'=', token::Le}},
    {'>', token::Gt,      {'=', token::Ge}},
    {'&', token::Unknown, {'&', token::And}},
    {'|', token::Pipe,    {'|', token::Or}},                       // Pipe reserved for later.
    {':', token::Colon,   {':', token::Scope}},                    // Colon and Scope reserved for later.
    {'.', token::Dot,     {'.', token::Dot2, {'.', token::Dot3}}}, // Dot* reserved for later.
    {';', token::Sep},
    {',', token::Comma},
    {'(', token::OParen},
    {')', token::CParen},
    {'[', token::OBrack},
    {']', token::CBrack},
    {'{', token::OBrace},
    {'}', token::CBrace}
}

{
    {"if",     keyword::If},
    {"else",   keyword::Else},
    {"when",   keyword::When},
    {"while",  keyword::While},
    {"for",    keyword::For},
    {"in",     keyword::In},
    {"type",   keyword::Type},
    {"buffer", keyword::Buffer},
    {"return", keyword::Return},
    {"true",   keyword::True},
    {"false",  keyword::False}, // Keyword or value?
    {"false",  keyword::False}, // Keyword or value?
    {"to",     keyword::To},    // To reserved for later
    {"by",     keyword::By}     // By reserved for later
}

int yylex () {
    char ch;
    do {
        ch = cin.peek();
        if (isalpha(ch)) {
            cin.get();
            yylval.ident = ch;
            return IDENT;
        } else if (isdigit(ch)) {
            int value = 0;
            while (!cin.eof() && isdigit(ch)) {
                cin.get();
                value = value * 10 + ch - '0';
                ch = cin.peek();
            }
            yylval.value = value;
            return NUMBER;
        } else if (ch == '+' || ch == '\n' || ch == '*' || ch == '=') {
            cin.get();
            return ch;
        } else
            cin.get();
    } while (!cin.eof());
    return -1;
}

void clear_stack () {
    while (!nodes.empty()) {
        delete nodes.top();
        nodes.pop();
    }
}
