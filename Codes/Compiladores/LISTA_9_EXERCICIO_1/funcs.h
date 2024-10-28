#ifndef FUNCS_H
#define FUNCS_H

typedef enum token {
    IF = 1,
    THEN,
    ELSE,
    END,
    BEGIN,
    PRINT,
    SEMICOL,
    EQ,
    NUM,
    NEW_LINE
} Token;

typedef enum {
   ACCEPTED = 1,
   REJECTED,
   INCOMPLETE
} parsingStatus;

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

/*Retorna o valor do index de cada caractere*/
int charIndex(char c);
/*Retorna se aquele estado é ou nao estado final*/
bool isFinalState(int state);

bool endFile(int caracterAtual, FILE* arq, bool erro) ;

Token getToken(int estadoFinal);

int nextToken(int matriz[][29]);

char* tokenClass(int token) ;

void advance(int *token,int matriz[][29]);

void printError(int tokenLido, char* tokenEsperado, int *status,int *token,int matriz[][29]) ;

void eat(int t,int *tokenAtual, int *status,int matriz[][29]);

void L(int *tokenAtual, int *status,int matriz[][29]);

void E(int *tokenAtual, int *status,int matriz[][29]);

parsingStatus S(int *tokenAtual, int *status,int matriz[][29]);

#endif