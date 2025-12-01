%option noyywrap
%option yylineno

%{
#include "ast.h"
#include "sintatico.tab.h"
extern YYSTYPE yylval;

int yycolumn = 1; // Contado de colunas

void tokenInfo(int type) {
    yylval.token.valor = strdup(yytext);
    yylval.token.type = type;
    yylval.token.line = yylineno;
    yylval.token.col = yycolumn;
    yycolumn += yyleng;
}
%}

%option noinput nounput

%%

<<EOF>>                     { return MyEOF; }
"AST -->"                   { }
"RETURN_TYPE"               { tokenInfo(RETURN_TYPE); return RETURN_TYPE; }
"RETURN"                    { tokenInfo(RETURN); return RETURN; }
"void"                      { tokenInfo(VOID); return VOID; }
"FOR"                       { tokenInfo(FOR); return FOR; }
"DO_WHILE"                  { tokenInfo(DO_WHILE); return DO_WHILE; }
"IF"                        { tokenInfo(IF); return IF; }
"TYPE"                      { tokenInfo(TYPE); return TYPE; }
"CONSTANT"                  { tokenInfo(CONSTANT); return CONSTANT; }
"PARAMETER"                 { tokenInfo(PARAMETER); return PARAMETER; }
"VALUE"                     { tokenInfo(VALUE); return VALUE; }
"char"                      { tokenInfo(CHAR); return CHAR; }
"VARIABLE"                  { tokenInfo(VARIABLE); return VARIABLE; }
"int"                       {  tokenInfo(INT); return INT; } 
"GLOBAL"                    { tokenInfo(GLOBAL); return GLOBAL; }
"FUNCTION"                  { tokenInfo(FUNCTION); return FUNCTION; }
"END_FUNCTION"              { tokenInfo(END_FUNCTION); return END_FUNCTION; }
"WHILE"                     { tokenInfo(WHILE); return WHILE; }
"EXIT"                      { tokenInfo(EXIT); return EXIT; }
"PRINTF"                    { tokenInfo(PRINTF); return PRINTF; }
"SCANF"                     { tokenInfo(SCANF); return SCANF; }
"*"                         { tokenInfo(MULTIPLY); return MULTIPLY; }
"/"                         { tokenInfo(DIVIDE); return DIVIDE; }
"-"                         { tokenInfo(MINUS); return MINUS; }
"+"                         { tokenInfo(PLUS); return PLUS; }
"%"                         { tokenInfo(REMAINDER); return REMAINDER; }
"--"                        { tokenInfo(DEC); return DEC; }
"++"                        { tokenInfo(INC); return INC; }
"&"                         { tokenInfo(BITWISE_AND); return BITWISE_AND; }
"|"                         { tokenInfo(BITWISE_OR); return BITWISE_OR; }
"~"                         { tokenInfo(BITWISE_NOT); return BITWISE_NOT; }
"^"                         { tokenInfo(BITWISE_XOR); return BITWISE_XOR; }
"!"                         { tokenInfo(NOT); return NOT; }
"&&"                        { tokenInfo(LOGICAL_AND); return LOGICAL_AND; }
"||"                        { tokenInfo(LOGICAL_OR); return LOGICAL_OR; }
"!="                        { tokenInfo(NOT_EQUAL); return NOT_EQUAL; }
"<"                         { tokenInfo(LESS_THAN); return LESS_THAN; }
">"                         { tokenInfo(GREATER_THAN); return GREATER_THAN; }
">="                        { tokenInfo(GREATER_EQUAL); return GREATER_EQUAL; }
"=="                        { tokenInfo(EQUAL); return EQUAL; }
">>"                        { tokenInfo(R_SHIFT); return R_SHIFT; }
"-="                        { tokenInfo(MINUS_ASSIGN); return MINUS_ASSIGN; }
"+="                        { tokenInfo(ADD_ASSIGN); return ADD_ASSIGN; }
"<<"                        { tokenInfo(L_SHIFT); return L_SHIFT; }
"="                         { tokenInfo(ASSIGN); return ASSIGN; }
"<="                        { tokenInfo(LESS_EQUAL); return LESS_EQUAL; }
","                         { tokenInfo(COMMA); return COMMA; }
"?"                         { tokenInfo(TERNARY_CONDITIONAL); return TERNARY_CONDITIONAL; }
";"                         { tokenInfo(SEMICOLON); return SEMICOLON; }
":"                         { tokenInfo(COLON); return COLON; }
"("                         { tokenInfo(L_PAREN); return L_PAREN; }
")"                         { tokenInfo(R_PAREN); return R_PAREN; }
"["                         { tokenInfo(L_SQUARE_BRACKET); return L_SQUARE_BRACKET; }
"]"                         { tokenInfo(R_SQUARE_BRACKET); return R_SQUARE_BRACKET; }
\"([^\\\"]|\\.)*\"          { tokenInfo(STRING); return STRING; }
" "                         { yycolumn += yyleng;}
\n                          { yycolumn = 1;}
\t                          { yycolumn += 4; }
(_*[a-zA-Z][a-zA-Z0-9_]*)   { tokenInfo(ID); return ID; }
"'"(\\.|[^\\']){1}"'"       { tokenInfo(CHARACTER); return CHARACTER; }
[0-9]+                      { tokenInfo(NUM_INT); return NUM_INT; }
.                           { printf("Caracter do segredo '%s' [%d][%d] \n", yytext, yylineno, yycolumn); }

%%