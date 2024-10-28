%{
#include "dcmat.tab.h"
%}

%%

[0-9]+"."[0-9]+        { yylval.dval = atof(yytext); return REAL; }
[0-9]+                  { yylval.ival = atoi(yytext); return INT; }
"pi"|"PI"               { return PI; }
"e"|"E"                 { return E; }
"quit"                  { return QUIT; }
"plot"                  { return PLOT; }
"integrate"             { return INTEGRATE; }
"sum"                   { return SUM; }
[a-zA-Z][a-zA-Z0-9]*    { yylval.sval = strdup(yytext); return IDENTIFIER; }
":="                    { return ASSIGN; }
"+"                     { return PLUS; }
"-"                     { return MINUS; }
"*"                     { return TIMES; }
"/"                     { return DIVIDE; }
"^"                     { return POWER; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
":"                     { return COLON; }
","                     { return COMMA; }
\n                      { return '\n'; }
[ \t]+                  { /* Ignora espaços em branco */ }
.                       { printf("Token inválido: %s\n", yytext); }

%%

int yywrap() { return 1; }
