%option noyywrap
%option yylineno

%{

#include <stdlib.h>
#include <string.h>
#include <sintatico.tab.h>

extern YYSTYPE yylval;
extern int erroSintatico;

int EOF_flag = 0;
int yycolumn = 1;
int erroLexico = 0;
int changeToken = 0;
int ignoraLin = 0;
char denied[256] = "";

void guardaTok(int tokenTipo) {
    yylval.token.valor = strdup(yytext);
    yylval.token.col = yycolumn;
    yylval.token.lin = yylineno;
    ignoraLin = 1;
    yycolumn += strlen(yytext);
    yylval.token.tipo = tokenTipo;
}

void errorLexic() {
    if(strlen(denied) < 1) 
        return;
    if(changeToken) 
        printf("\n");
    printf("Caractere(s) invalido(s) -> [%s]", denied);
    changeToken = 1;
    for(int i = 0; i < 256; i++) 
        denied[i] = '\0'; 
    // erroLexico = 0;
}

%}

%%

<<EOF>> { 
    EOF_flag = 1;      
    if(erroLexico) {
        errorLexic();
        return ERRO;
    } 
    return EOL; }

\n {
    yycolumn = 1; 
    if(erroLexico) {
        errorLexic();
        return ERRO; 
    }
    return EOL; }

[ \t]  { yycolumn += strlen(yytext); }

(([0-9]+"."[0-9]*)|([0-9]*"."[0-9]+)) { guardaTok(REAL); return REAL; }

[0-9]+ { guardaTok(INT); return INT; }
"+"    { guardaTok(ADD); return ADD; }
"-"    { guardaTok(SUB); return SUB; }
"*"    { guardaTok(MUL); return MUL; }
"/"    { guardaTok(DIV); return DIV; }
"^"    { guardaTok(POW); return POW; }
"%"    { guardaTok(MOD); return MOD; }
"("    { guardaTok(L_PAREN); return L_PAREN; }
")"    { guardaTok(R_PAREN); return R_PAREN; }
"sen"  { guardaTok(SEN); return SEN; }
"cos"  { guardaTok(COS); return COS; }
"tan"  { guardaTok(TAN); return TAN; }
"abs"  { guardaTok(ABS); return ABS; }
([a-zA-Z]+[a-zA-Z0-9]*) { guardaTok(ID); return ID; }

. { 
    erroLexico = 1; 
    if(strlen(denied) != 0) 
        denied[strlen(denied)] = ','; 
    denied[strlen(denied)] = yytext[0];
    yycolumn += strlen(yytext);
    ignoraLin = 1;
}

%%