%{

#include <stdio.h>
#include <string.h>
extern int EOF_flag;
extern int yylex();
extern int changeToken;
extern int yychar;
extern int ignoraLin;
extern int erroLexico;
int erroToken;
int erroFimLinha = 0;
int erroSintatico = 0;
void yyerror(void *s);
%}

%union {
    struct {
        char *valor;
        int col;
        int lin;
        int tipo;
    } token;
}

%token EOL
%token ADD
%token SUB
%token MUL
%token DIV
%token POW
%token MOD
%token L_PAREN
%token R_PAREN
%token SEN
%token COS
%token TAN
%token ABS
%token ID
%token REAL
%token INT
%token ERRO

%start Start

%left '+' '-'
%left '*' '/'
%right '^'

%%

/* 
Start -> Exp EOL
Exp -> Fator
Exp -> Exp ADD Fator
Exp -> Exp SUB Fator
Fator -> Termo
Fator -> Fator MUL Termo
Fator -> Fator DIV Termo
Fator -> Fator POW Termo
Fator -> Fator MOD Termo
Termo -> L_PAREN Exp R_PAREN
Termo -> SEN L_PAREN Exp R_PAREN
Termo -> COS L_PAREN Exp R_PAREN
Termo -> TAN L_PAREN Exp R_PAREN
Termo -> ABS L_PAREN Exp R_PAREN
Termo -> ID
Termo -> INT
Termo -> REAL

*/

Start: Exp EOL  { erroSintatico = 0; return 0; }
    | Exp ERRO  { erroFimLinha = 1; return 0; }
    | error     { if(erroSintatico == 2) return 0; erroSintatico = 1; erroToken = yychar; return 0; }
;

Exp: Fator { }
    | Exp ADD Fator { } 
    | Exp SUB Fator { }
;

Fator: Termo { }
    | Fator MUL Termo { }
    | Fator DIV Termo { }
    | Fator POW Termo { }
    | Fator MOD Termo { } 
;

Termo: L_PAREN Exp R_PAREN { } 
    | ID    { }
    | INT   { }
    | REAL  { }
    | ADD Termo { }
    | SUB Termo { }
    | SEN L_PAREN Exp R_PAREN { }
    | COS L_PAREN Exp R_PAREN { }
    | TAN L_PAREN Exp R_PAREN { }
    | ABS L_PAREN Exp R_PAREN { } 
;

%%

void yyerror(void *s) {}

void resetaFlag() {
    erroFimLinha = 0; 
    erroLexico = 0;
    erroSintatico = 0;
    ignoraLin = 0;
}

int main(int argc, char* argv[]) {
    while(!EOF_flag) {
        yyparse();
        if(erroSintatico == 2) {
            if(yychar == EOL) 
                resetaFlag();
            continue;
        }
        if(erroLexico && !erroFimLinha) // erro lexico e nao acabou a linha
            continue;  
        if(erroFimLinha) { // erro lexico e acabou a linha
            resetaFlag();
            continue;
        }

        if(changeToken) 
            printf("\n");

        if(!ignoraLin) {
            resetaFlag();
            continue;
        }

        if(erroSintatico == 1) {
            if(erroToken == 0 || erroToken == EOL || erroToken == YYEMPTY) {  // linha acabou subitamente
                printf("A expressao terminou de forma inesperada. %d ", erroToken);
            } else {  // erro sintatico no meio da linha
                printf("Erro sinatico na coluna [%d][%d]: %s", yylval.token.lin, yylval.token.col, yylval.token.valor);
            }
            erroSintatico = 2;
        } else if(erroSintatico == 0) {
            printf("EXPRESSAO CORRETA");
            resetaFlag();     
        }
        changeToken = 1; 
    } 

    return 0;
}