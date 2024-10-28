#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
/*Retorna o valor do index de cada caractere*/
int charIndex(char c);
/*Retorna se aquele estado é ou nao estado final*/
int isFinalState(int state);

void wich_state(int num);

bool endFile(int caracterAtual, FILE* arq, bool erro) ;

#endif