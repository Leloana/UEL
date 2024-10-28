%option noyywrap
%option yylineno

%{

#include <sintatico.tab.h>
extern YYSTYPE yylval;

int EOF_flag = 0;
int changeToken = 0;
int yycolumn = 1;

void guardaTok() {
    yylval.token.valor = strdup(yytext);
    yylval.token.col = yycolumn;
    yylval.token.lin = yylineno;
    yycolumn += strlen(yytext);
}

%}

%%

<<EOF>> { EOF_flag = 1; return 0; }

"$"     { return EOL; }
"int"   { guardaTok(); return INT; } 
"char"  { guardaTok(); return CHAR; }
"float" { guardaTok(); return FLOAT; }
","     { guardaTok(); return COMMA; }
" "     { yycolumn++; }
\n      { yycolumn = 1; }
[a-z]+  { guardaTok(); return ID; }

.     { if(changeToken) printf("\n");
        printf("error:lexical:%d:%d: %s", yylineno, yycolumn, yytext);
        yycolumn += strlen(yytext);
        exit(1);
}

%%