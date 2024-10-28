%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dcmat.h"

int yylex();
void yyerror(const char *s);
%}

%union {
    int ival;
    double dval;
    char *sval;
}

%token <ival> INT
%token <dval> REAL
%token <sval> IDENTIFIER
%token PI E QUIT PLOT INTEGRATE SUM PLUS MINUS TIMES DIVIDE POWER
%token LPAREN RPAREN ASSIGN COLON COMMA

%type <dval> expr
%type <sval> command line

%left PLUS MINUS
%left TIMES DIVIDE
%right POWER
%nonassoc NEG

%%

input:
    /* Entrada vazia */
    | input line
;

line:
    expr '\n'            { printf("Resultado: %f\n", $1); }
    | command '\n'
;

command:
    QUIT                 { printf("Saindo do programa.\n"); exit(0); }
    | IDENTIFIER ASSIGN expr   { set_var_value($1, $3); }
    | PLOT expr          { plot_function(example_function, -10, 10); }  // Plota de -10 a 10 para exemplo
    | INTEGRATE LPAREN expr COLON expr RPAREN ',' expr
                        { printf("Integral: %f\n", calculate_integral($3, $5, example_function)); }
    | SUM LPAREN IDENTIFIER COMMA expr COLON expr COMMA expr RPAREN
        { printf("Soma: %f\n", sum_function($3, $5, example_function)); }
    ;

expr:
    INT                 { $$ = $1; }
    | REAL               { $$ = $1; }
    | PI                 { $$ = M_PI; }
    | E                  { $$ = M_E; }
    | IDENTIFIER         { $$ = get_var_value($1); }
    | expr PLUS expr     { $$ = $1 + $3; }
    | expr MINUS expr    { $$ = $1 - $3; }
    | expr TIMES expr    { $$ = $1 * $3; }
    | expr DIVIDE expr   { $$ = $1 / $3; }
    | expr POWER expr    { $$ = pow($1, $3); }
    | MINUS expr %prec NEG { $$ = -$2; }
    | LPAREN expr RPAREN { $$ = $2; }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro de sintaxe: %s\n", s);
}
