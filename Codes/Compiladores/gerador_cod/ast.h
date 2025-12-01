#ifndef _AST_H_
#define _AST_H_

#include <stdio.h>
#include <stdlib.h>

enum expressionTypes {
    BOP = 1001,
    UOP,
    // LISTA_EXP,
    TERNARY,
    ARRAY_CALL,
    FUNCTION_CALL,
    PRIMARIA
};
#define LISTA_EXP_COMANDO 9802


typedef struct function {
    void **hashTable;
    void *declarations;
    int returnType;
    int pointer;
    char *name;
    void *commandList;
    void *next;
} Funcao;
typedef struct program {
    void **hashTable;  // declarations
    void *functionsList;
    void *definesExps;
    void *dimensionsExps;
    void *main;  // start of the program, wont be used here
} Program;

typedef struct expParam {
    int type;
    int pointer;
    void *exp;
    char *identifier;
    struct expParam *next;
} ExpParam;

typedef struct dimension {
    int size;
    void *exp;
    struct dimension *next;
} Dims;

typedef struct expression {
    int type;
    int pointer;
    int operator;
    int assign;
    int preOrPost; // 1 = pre, 2 = post
    Dims *dimension;
    ExpParam *param;
    char identifier[256];
    char string[512];
    int isHeadOfList;

    struct expression *nextExpr;

    struct expression *ternaryCondition;
    struct expression *left;
    struct expression *right;
} Expression;

typedef struct command {
    int type;
    Expression *condition;
    void *then;
    void *next;

    // if else
    void *elseStatement;

    // for
    Expression *init;
    Expression *increment;

    // print, scan
    char *string;
    Expression *auxPrint;
    char *identifier;

    int visited;
} Command;

typedef struct Resultado {
    int typeVar;
    int pointer;
    int assign;
    char str[256];

    int registerType;  // 0 = t, 1 = s
    int registerNumber;

    void *auxIdNode;
} Resultado;

Program *criaProgram(void **hash, void *functionsList, void *main);

Funcao *criaFuncao(void **hash, int returnType, int pointer, char *name, void *commandList, void *next);

ExpParam *criaExpParam(Expression *exp, ExpParam *next);

Dims *criaDims(int size);

int countDims(void *d);

Dims *criaDimsWithExp(Expression *exp);

void setDimsExpression(Expression *expression, Dims *dimension);

Expression *criaExpression(int type, int operator, void *left, void *right);

Command *criaIfStatement(Expression *condition, void *then, void *elseStatement, void *next);

Command *criaElseStatement(void *then, void *next);

Command *criaDoWhileStatement(Expression *condition, void *then, void *next);

Command *criaWhileStatement(Expression *condition, void *then, void *next);

Command *criaForStatement(Expression *init, Expression *condition, Expression *increment, void *then, void *next);

Command *criaPrintStatement(char *string, Expression *auxPrint, void *next);

Command *criaScanStatement(char *string, char *identifier, void *next);

Command *criaReturnStatement(Expression *expression, void *next);

Command *criaExitStatement(Expression *expression, void *next);

Command *criaCommandExpression(Expression *expression, void *next);

Resultado *criaResultado(int type, int pointer, int value);

Resultado *eval(Expression *expression, void **listaHash, void **localHash, Program *program);

int percorreAST(Program *program);

void freeAST(Program *program);

#endif