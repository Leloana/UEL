#ifndef _HASH_H_
#define _HASH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HASH_SIZE 269

/*
./gerador < entradas_gerador/quicksort.txt > saidas_gerador/quicksort.asm 
./gerador < entradas_gerador/fatorial.txt > saidas_gerador/fatorial.asm 
./gerador < entradas_gerador/triangulo.txt > saidas_gerador/triangulo.asm 
./gerador < entradas_gerador/comparacao.txt > saidas_gerador/comparacao.asm 
*/

#define VAR 1
#define FUNCTIONN 2
#define VECTOR 3

typedef struct node {
    int typeVar;
    int pointer;
    char *varId;
    int assign;
    char string[256];
    int isConstant;
    int isGlobal;
    void *dimensions;
    void *param;
    int kind;
    int qntdParams;
    int qntdDimen;

    void *hashExpr;
    int lineAssign, columnAssign;

    int sRegister;

    struct node *next;
} HashNode;

typedef struct param {
    int type;
    int pointer;
    int kindParam;
    char *identifier;
    struct param *next;
} Param;

void **criaHash();

int hash(char *value);

void setSRegisterInHash(void *node, int sRegister);
int getSRegisterFromHash(void *node);
char *getExactType(int type, int pointer);
void *insertHash(void **hashTable, char *varId, int currentType, int pointer);
void setIsConstant(void *node);
void freeHash(void **hashTable);
int lookForValueInHash(void **hashTable, char *varId, int currentType);
void setQntdParams(void *node, int qntdParams);
void setParam(void *node, Param *p);
void setAssign(void *node, int assign);
void printProgram(void *AST);
Param *criaParam(int type, char *identifier, int pointer, void *next);
void setDimss(void *node, void *dimensions);
void setIsGlobal(void *node);
void setKind(void *node, int kind);
void setHashExpr(void *node, void *hashExpr);
HashNode *getIdentifierNode(void **hashTable, char *id);

#endif