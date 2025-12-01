#include "ast.h"
#include <stdint.h>
#include "MIPS.h"
#include "hash.h"
#include "sintatico.tab.h"


Resultado *criaResultado(int type, int pointer, int value) {
    Resultado *newResult = calloc(1, sizeof(Resultado));
    newResult->typeVar = type;
    newResult->pointer = pointer;
    newResult->assign = value;
    newResult->registerType = -1;
    newResult->registerNumber = -1;
    return newResult;
}

Program *criaProgram(void **hash, void *functionsList, void *main) {
    Program *newProg = calloc(1, sizeof(Program));
    newProg->hashTable = hash;
    newProg->functionsList = functionsList;
    newProg->main = main;
    return newProg;
}

Funcao *criaFuncao(void **hash, int returnType, int pointer, char *name, void *commandList, void *next) {
    Funcao *newFunc = calloc(1, sizeof(Funcao));
    newFunc->hashTable = hash;
    newFunc->returnType = returnType;
    newFunc->pointer = pointer;
    newFunc->name = name;
    newFunc->commandList = commandList;
    newFunc->next = next;
    return newFunc;
}

ExpParam *criaExpParam(Expression *exp, ExpParam *next) {
    ExpParam *newExpParam = calloc(1, sizeof(ExpParam));
    newExpParam->exp = exp;
    newExpParam->next = next;
    return newExpParam;
}

Expression *criaExpression(int type, int operator, void * left, void *right) {
    Expression *newExp = calloc(1, sizeof(Expression));
    newExp->type = type;
    newExp->operator= operator;
    newExp->left = left;
    newExp->right = right;
    newExp->dimension = NULL;
    newExp->ternaryCondition = NULL;
    return newExp;
}

int countDims(void *d) {
    Dims *dimen = d;
    if (!dimen) return 0;
    int count = 1;
    Dims *aux = dimen;
    while (aux->next) {
        count++;
        aux = aux->next;
    }
    return count;
}

Dims *criaDims(int size) {
    Dims *newDim = calloc(1, sizeof(Dims));
    newDim->size = size;
    return newDim;
}


Dims *criaDimsWithExp(Expression *exp) {
    Dims *newDim = calloc(1, sizeof(Dims));
    newDim->exp = exp;
    return newDim;
}

Command *criaDoWhileStatement(Expression *condition, void *then, void *next) {
    Command *newDoWhile = calloc(1, sizeof(Command));
    newDoWhile->type = DO_WHILE;
    newDoWhile->condition = condition;
    newDoWhile->then = then;
    newDoWhile->next = next;
    return newDoWhile;
}

Command *criaIfStatement(Expression *condition, void *then, void *elseStatement, void *next) {
    Command *newIf = calloc(1, sizeof(Command));
    newIf->type = IF;
    newIf->condition = condition;
    newIf->then = then;
    newIf->elseStatement = elseStatement;
    newIf->next = next;
    return newIf;
}

Command *criaWhileStatement(Expression *condition, void *then, void *next) {
    Command *newWhile = calloc(1, sizeof(Command));
    newWhile->type = WHILE;
    newWhile->condition = condition;
    newWhile->then = then;
    newWhile->next = next;
    return newWhile;
}

Command *criaForStatement(Expression *init, Expression *condition, Expression *increment, void *then, void *next) {
    Command *newFor = calloc(1, sizeof(Command));
    newFor->type = FOR;
    newFor->init = init;
    newFor->condition = condition;
    newFor->increment = increment;
    newFor->then = then;
    newFor->next = next;
    return newFor;
}

Command *criaPrintStatement(char *string, Expression *auxPrint, void *next) {
    Command *newPrint = calloc(1, sizeof(Command));
    newPrint->type = PRINTF;
    newPrint->string = string;
    newPrint->auxPrint = auxPrint;
    newPrint->next = next;
    return newPrint;
}

Command *criaScanStatement(char *string, char *identifier, void *next) {
    Command *newScan = calloc(1, sizeof(Command));
    newScan->type = SCANF;
    newScan->string = string;
    newScan->identifier = identifier;
    newScan->next = next;
    return newScan;
}

Command *criaExitStatement(Expression *expression, void *next) {
    Command *newExit = calloc(1, sizeof(Command));
    newExit->type = EXIT;
    newExit->condition = expression;
    newExit->next = next;
    return newExit;
}

Command *criaCommandExpression(Expression *expression, void *next) {
    Command *newCommand = calloc(1, sizeof(Command));
    newCommand->type = LISTA_EXP_COMANDO;
    newCommand->condition = expression;
    newCommand->next = next;
    // printf("commandExpression %p %p\n", expression, newCommand);
    return newCommand;
}

Command *criaReturnStatement(Expression *expression, void *next) {
    Command *newReturn = calloc(1, sizeof(Command));
    newReturn->type = RETURN;
    newReturn->condition = expression;
    newReturn->next = next;
    return newReturn;
}

void freeAST(Program *program) {
    if (!program) return;
    freeHash(program->hashTable);

    Funcao *functions = program->functionsList;
    while (functions) {
        Funcao *functions2 = functions->next;
        Command *cmd = functions->commandList;
        while (cmd) {
            Command *cmd2 = cmd->next;
            if (cmd->condition) {
                free(cmd->condition);
            }
            if (cmd->init) {
                free(cmd->init);
            }
            if (cmd->increment) {
                free(cmd->increment);
            }
            if (cmd->auxPrint) {
                free(cmd->auxPrint);
            }
            free(cmd);
            cmd = cmd2;
        }
        freeHash(functions->hashTable);
        if (functions->name) free(functions->name);
        free(functions);
        functions = functions2;
    }
    free(program);
}

void setDimsExpression(Expression *expression, Dims *dimension) {
    if (!expression) return;
    if (!expression->dimension) {
        expression->dimension = dimension;
    } else {
        Dims *aux = expression->dimension;
        while (aux->next) aux = aux->next;
        aux->next = dimension;
    }
}
