#ifndef FUNCS_H
#define FUNCS_H

typedef enum token {
    PLUS = 1,
    MUL,
    L_PAREN,
    R_PAREN,
    EOL,
    ID,
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

int nextToken(int matriz[][43]);

char* tokenClass(int token) ;

void advance(int *token,int matriz[][43]);

void printError(char* tokenEsperado, int *status,int *token,int matriz[][43]) ;

void eat(int t,int *tokenAtual, int *status,int matriz[][43]);

void T(int *tokenAtual, int *status,int matriz[][43]);
void T_Quote(int *tokenAtual, int *status,int matriz[][43]);

void E(int *tokenAtual, int *status,int matriz[][43]);
void E_Quote(int *tokenAtual, int *status,int matriz[][43]);

void F(int *tokenAtual, int *status,int matriz[][43]);

parsingStatus S(int *tokenAtual, int *status,int matriz[][43]);


#endif