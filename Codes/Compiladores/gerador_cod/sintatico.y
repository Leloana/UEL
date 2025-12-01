%{
#include "MIPS.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
extern int yylex();
void yyerror();

int isFuncOrArray = -1;
int pointerCount = 0;
int paramCount = 0;
void **listaHash = NULL;
void **currentHash = NULL;
Funcao *functionList = NULL;
Program *AST = NULL; // Arvore que define o programa

%}

%union {
    void *param;
    void *posfixa;
    Expression *expr;
    Dims *dim;
    Command *cmd;
    Program *prog;
    Funcao *func;
    int sinalAux;
    struct {
        int line;
        int col;
        char *valor;
        int type;
    } token;
}

%token MyEOF
%token <token> VALUE
%token <token> TYPE
%token <token> INT
%token <token> CHAR
%token <token> RETURN_TYPE
%token <token> GLOBAL
%token <token> VARIABLE
%token <token> CONSTANT
%token <token> PARAMETER
%token <token> IF
%token <token> PRINTF
%token <token> SCANF
%token <token> FUNCTION
%token <token> FOR
%token <token> EXIT
%token <token> END_FUNCTION
%token <token> VOID
%token <token> RETURN
%token <token> DO_WHILE
%token <token> WHILE

%token <token> REMAINDER
%token <token> INC
%token <token> ASSIGN
%token <token> EQUAL
%token <token> PLUS
%token <token> MINUS
%token <token> MULTIPLY
%token <token> DIVIDE
%token <token> LOGICAL_OR
%token <token> NOT
%token <token> TERNARY_CONDITIONAL
%token <token> COLON
%token <token> R_SHIFT
%token <token> BITWISE_NOT
%token <token> NOT_EQUAL
%token <token> GREATER_THAN
%token <token> BITWISE_AND
%token <token> MINUS_ASSIGN
%token <token> LESS_EQUAL
%token <token> DEC
%token <token> LOGICAL_AND
%token <token> BITWISE_OR
%token <token> BITWISE_XOR
%token <token> LESS_THAN
%token <token> GREATER_EQUAL
%token <token> L_SHIFT
%token <token> ADD_ASSIGN

%token <token> L_SQUARE_BRACKET
%token <token> COMMA
%token <token> R_PAREN
%token <token> R_SQUARE_BRACKET
%token <token> SEMICOLON
%token <token> L_PAREN

%token <token> NUM_INT
%token <token> CHARACTER
%token <token> ID
%token <token> STRING

%type <expr> Primaria
%type <token> SemicolonDeSchrodinger
%type <token> Ops
%type <token> VarType
%type <sinalAux> Sinal 
%type <dim> ArrayCheck
%type <dim> ArrayCall
%type <param> Parameters
%type <posfixa> PosFixa
%type <param> FuncaoCall
%type <param> ParamExpression
%type <cmd> Comandos
%type <cmd> ListaComandos
%type <cmd> AuxElse
%type <expr> Expression 
%type <expr> TernaryExpr 
%type <expr> BinaryExpr 
%type <expr> UnaryExpr
%type <expr> AuxReturn
%type <expr> AuxPrint
%type CasosLocais
%type Pointers

%start ASTinicio

%%

ASTinicio: Casos MyEOF     {
                                Program *ast = criaProgram(listaHash, functionList, NULL);
                                AST = ast;
                                return 0;
                                } 
    ;

Casos: CasoDefine Casos  { }
    | CasoVarGlobal Casos      { } 
    | CasoFuncao Casos         { } 
    |                                   { } 
    ;

CasoDefine: CONSTANT COLON ID VALUE COLON Sinal NUM_INT  {
                                                            int valor = atoi($7.valor);
                                                            if ($6 == MINUS) {
                                                                valor *= -1;
                                                            }
                                                            void *node = insertHash(listaHash, $3.valor, INT, 0);
                                                            setKind(node, VAR);
                                                            setIsConstant(node);
                                                            setAssign(node, valor); 
                                                            setDefineIntVariable($3.valor, valor);
                                                            } 
    ;

CasoVarGlobal: GLOBAL VARIABLE COLON ID TYPE COLON VarType { pointerCount = 0; } Pointers ArrayCheck {
                                                                // printf("CasoVarGlobal global var\n");
                                                                void *node = insertHash(listaHash, $4.valor, $7.type, pointerCount);
                                                                if (!$10) {
                                                                    setKind(node, VAR);
                                                                } else {
                                                                    setKind(node, VECTOR);
                                                                }
                                                                setDimss(node, $10);
                                                                setIsGlobal(node);
                                                                } 
    ;



Sinal : PLUS    { $$ = PLUS; }
    | MINUS     { $$ = MINUS; }
    |           { $$ = PLUS; } 
    ; 

CasoFuncao: FUNCTION COLON ID { currentHash = criaHash(); } RETURN_TYPE COLON VarType { pointerCount = 0; } Pointers { paramCount = 0; } Parameters CasosLocais ListaComandos END_FUNCTION {
                                Funcao *func = criaFuncao(currentHash, $7.type, pointerCount, $3.valor, $13, NULL);
                                if (functionList) {
                                    Funcao *aux = functionList;
                                    while (aux->next) {
                                        aux = aux->next;
                                    }
                                    aux->next = func;
                                } else {
                                    functionList = func;
                                }
                                
                                // printf("Funcoes %s %p | %p -> %p \n", $3.valor, func, functionList, functionList->next);
                                void *node = insertHash(listaHash, $3.valor, $7.type, pointerCount);
                                setKind(node, FUNCTIONN);
                                setQntdParams(node, paramCount);
                                setParam(node, $11);
                                currentHash = NULL;
                            } 
    ;

CasosLocais: VARIABLE COLON ID TYPE COLON VarType { pointerCount = 0; } Pointers ArrayCheck CasosLocais {
        void *node = insertHash(currentHash, $3.valor, $6.type, pointerCount);
        if (!$9) {
            setKind(node, VAR);
        } else {
            setKind(node, VECTOR);
        }
        setDimss(node, $9);
    }
    | { } 
    ; 

ArrayCheck: L_SQUARE_BRACKET NUM_INT R_SQUARE_BRACKET ArrayCheck {
                                                                Dims *dim = criaDims(atoi($2.valor));
                                                                dim->next = $4;
                                                                $$ = dim;
                                                                }
    | { $$ = NULL; } 
    ;

Expression: BinaryExpr  { $$ = $1; }
    | TernaryExpr       { $$ = $1; }
    | UnaryExpr         { $$ = $1; } 
    | Primaria          { $$ = $1; } 
    | FuncaoCall        { $$ = $1; } 
    ;

TernaryExpr: TERNARY_CONDITIONAL L_PAREN Expression COMMA Expression COMMA Expression {
        Expression *ternary = criaExpression(TERNARY, TERNARY_CONDITIONAL, $5, $7);
        ternary->ternaryCondition = $3;
        $$ = ternary;
    } ;

BinaryExpr: Ops L_PAREN Expression COMMA Expression R_PAREN {
                                    Expression *bop = criaExpression(BOP, $1.type, $3, $5);
                                    // printf("bop %d, %d (%p)\n", $1.type, $1.line, bop);
                                    $$ = bop;
                                    } 
    ;

UnaryExpr: Ops L_PAREN Expression R_PAREN {
                                        // printf("uop %d, %d\n", $1.type, $1.line);
                                        Expression *uop = criaExpression(UOP, $1.type, $3, NULL);
                                        uop->preOrPost = 1;
                                        $$ = uop;
                                        } 
    | L_PAREN Expression R_PAREN INC {
                                    // printf("uop %d\n", $4.type);
                                    Expression *uop = criaExpression(UOP, INC, $2, NULL);
                                    uop->preOrPost = 2;
                                    $$ = uop;
                                    } 
    | L_PAREN Expression R_PAREN DEC {
                                    // printf("uop %d\n", $4.type);
                                    Expression *uop = criaExpression(UOP, DEC, $2, NULL);
                                    uop->preOrPost = 2;
                                    $$ = uop;
                                    } 
    ;

Ops: PLUS                           { $$ = yylval.token; } 
    | MULTIPLY                      { $$ = yylval.token; } 
    | BITWISE_OR                    { $$ = yylval.token; }
    | BITWISE_AND                   { $$ = yylval.token; }
    | LOGICAL_OR                    { $$ = yylval.token; }
    | LESS_THAN                     { $$ = yylval.token; }
    | GREATER_EQUAL                 { $$ = yylval.token; }
    | LOGICAL_AND                   { $$ = yylval.token; }
    | LESS_EQUAL                    { $$ = yylval.token; }
    | GREATER_THAN                  { $$ = yylval.token; }
    | BITWISE_XOR                   { $$ = yylval.token; }
    | MINUS                         { $$ = yylval.token; } 
    | DIVIDE                        { $$ = yylval.token; }
    | R_SHIFT                       { $$ = yylval.token; }
    | EQUAL                         { $$ = yylval.token; }
    | REMAINDER                     { $$ = yylval.token; } 
    | INC                           { $$ = yylval.token; }
    | NOT_EQUAL                     { $$ = yylval.token; }
    | DEC                           { $$ = yylval.token; }
    | ADD_ASSIGN                    { $$ = yylval.token; }
    | ASSIGN                        { $$ = yylval.token; }
    | NOT                           { $$ = yylval.token; }
    | MINUS_ASSIGN                  { $$ = yylval.token; }
    | BITWISE_NOT                   { $$ = yylval.token; }
    | L_SHIFT                       { $$ = yylval.token; }
    ;

Primaria: NUM_INT {
        Expression *expr = criaExpression(PRIMARIA, INT, NULL, NULL);
        expr->assign = atoi($1.valor);
        // printf("primaria %p %d\n", expr, expr->assign);
        $$ = expr;
    }
    | CHARACTER     {
                    Expression *expr = criaExpression(PRIMARIA, CHAR, NULL, NULL);
                    if ($1.valor[1] == '\\') {
                        switch ($1.valor[2]) {
                            case 'n':
                                expr->assign = '\n';
                                break;
                            case 't':
                                expr->assign = '\t';
                                break;
                            case 'r':
                                expr->assign = '\r';
                                break;
                            case '0':
                                expr->assign = '\0';
                                break;
                            case '\\':
                                expr->assign = '\\';
                                break;
                            case '\'':
                                expr->assign = '\'';
                                break;
                            case '\"':
                                expr->assign = '\"';
                                break;
                        }
                    } else {
                        expr->assign = $1.valor[1];
                    }
                    $$ = expr;
                    }
    | STRING        {
                    Expression *expr = criaExpression(PRIMARIA, STRING, NULL, NULL);
                    strcpy(expr->string, $1.valor);
                    $$ = expr;
                }
    | ID PosFixa {
                Expression *expr = criaExpression(PRIMARIA, ID, NULL, NULL);
                strcpy(expr->identifier, $1.valor);
                if (isFuncOrArray == 1) {
                    // printf("pos fixa %s [%p]  \n", $1.valor, $2);
                    expr->type = ARRAY_CALL;
                    setDimsExpression(expr, ((Dims*)$2));
                
                } else if (isFuncOrArray == 2) {
                    // printf("pos fixa %s (%p)  \n", $1.valor, $2);
                    expr->type = FUNCTION_CALL;
                    expr->param = (ExpParam*)$2;
                }
                isFuncOrArray = -1;
                $$ = expr;
            } 
    ;

PosFixa: ArrayCall  { isFuncOrArray = 1; $$ = $1; }
    | FuncaoCall    { isFuncOrArray = 2; $$ = $1; }
    |               { isFuncOrArray = 0; $$ = NULL; }

ArrayCall: L_SQUARE_BRACKET Expression R_SQUARE_BRACKET {
        Dims *dim = criaDimsWithExp($2);
        // Expression *expr = criaExpression(ARRAY_CALL, ID, NULL, NULL);
        $$ = dim;
    } 
    ;

VarType: INT                            { $$ = yylval.token; }
    | CHAR                              { $$ = yylval.token; }
    | VOID                              { $$ = yylval.token; } 
    ;

FuncaoCall: L_PAREN ParamExpression R_PAREN {$$ = $2;};

ParamExpression: Expression ParamExpression {
                                            ExpParam *aux = criaExpParam($1, $2);
                                            $$ = aux;
                                        }
    | COMMA Expression ParamExpression {
                                            ExpParam *aux = criaExpParam($2, $3);
                                            $$ = aux;
                                        }
    | { $$ = NULL; } 
    ;

Parameters: PARAMETER COLON ID TYPE COLON VarType { pointerCount = 0; } Pointers ArrayCheck Parameters {
        // printf("Parmetro ID %s type %d\n", $3.valor, $6.type);
        void *node = insertHash(currentHash, $3.valor, $6.type, pointerCount);
        paramCount++;
        setQntdParams(node, paramCount);
        setSRegisterInHash(node, paramCount-1);
        Param *param = criaParam($6.type, $3.valor, pointerCount, $10);
        if (!$9) {
            setKind(node, VAR);
            param->kindParam = VAR;
        } else {
            setKind(node, VECTOR);
            param->kindParam = VECTOR;
        }
        setDimss(node, $9);
        param->next = $10;
        $$ = param;
    }
    | { $$ = NULL; } 
    ;

ListaComandos: Comandos SemicolonDeSchrodinger ListaComandos {       
        Command *cmd = $1;
        while (cmd->next != NULL) {
            cmd = cmd->next;
        }
        cmd->next = $3;
        $$ = $1;
    }
    | { $$ = NULL; } 
    ;
    
Comandos: IF L_PAREN Expression COMMA Comandos AuxElse R_PAREN SemicolonDeSchrodinger Comandos {
        Command *cmd = criaIfStatement($3, $5, $6, $9);
        $$ = cmd;
    }
    | DO_WHILE L_PAREN Comandos COMMA Expression R_PAREN SemicolonDeSchrodinger Comandos {
        Command *cmd = criaDoWhileStatement($5, $3, $8);
        $$ = cmd;
    }
    | WHILE L_PAREN Expression COMMA Comandos R_PAREN SemicolonDeSchrodinger Comandos {
        Command *cmd = criaWhileStatement($3, $5, $8);
        $$ = cmd;
    }
    | FOR L_PAREN Expression COMMA Expression COMMA Expression COMMA Comandos R_PAREN SemicolonDeSchrodinger Comandos {
        Command *cmd = criaForStatement($3, $5, $7, $9, $12);
        $$ = cmd;
    }
    | PRINTF L_PAREN STRING AuxPrint R_PAREN SemicolonDeSchrodinger Comandos {
        Command *cmd = criaPrintStatement($3.valor, $4, $7);
        $$ = cmd;
    }
    | SCANF L_PAREN STRING COMMA BITWISE_AND L_PAREN ID R_PAREN R_PAREN SemicolonDeSchrodinger Comandos {
        Command *cmd = criaScanStatement($3.valor, $7.valor, $11);
        $$ = cmd;
    }
    | RETURN L_PAREN AuxReturn R_PAREN Comandos {
        Command *cmd = criaReturnStatement($3, $5);
        $$ = cmd;
    }
    | EXIT L_PAREN Expression R_PAREN Comandos {
        Command *cmd = criaExitStatement($3, $5);
        $$ = cmd;
    } 
    | Expression SemicolonDeSchrodinger Comandos {
        Command *cmd = criaCommandExpression($1, $3);
        $$ = cmd;
    } 
    | { $$ = NULL; }
    ;

AuxReturn: Expression { $$ = $1; }
    | { $$ = NULL; } ;

SemicolonDeSchrodinger: SEMICOLON { }
    | { } ;

Pointers: MULTIPLY Pointers { pointerCount++; }
    | { } 
    ;

AuxElse: COMMA Comandos { $$ = $2; }
    | { $$ = NULL; } 
    ;

AuxPrint: COMMA Expression AuxPrint {
        $2->nextExpr = $3;
        $$ = $2;
    }
    | { $$ = NULL; } 
    ;

%%

void yyerror() {
    printf("Erro na gramatica %d [ %s ]:%d:%d \n", yychar, yylval.token.valor, yylval.token.line, yylval.token.col);
}

int main(void) {
    listaHash = criaHash();
    yyparse();

    if (AST) {
        /* printProgram(AST); */
        Program *ast = (Program*)AST;
        percorreAST(ast);
        escreveExit();
    } else {
        printf("AST NULL\n");
        exit(1);
    }
    return 0;
}