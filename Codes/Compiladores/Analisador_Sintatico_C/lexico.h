#ifndef _LEXICO_H
#define _LEXICO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "pilha.h"

#define N_ALF 91              // Tamanho do alfabeto de entrada
#define N_FINAL 167            // Número total de estados finais
#define MAX_INPUT 131072       // Tamanho máximo do input de código

/*
 Função erroLexico
 
 Descrição:
 Esta função é chamada quando ocorre um erro léxico durante o processo de análise léxica.
 Ela exibe uma mensagem de erro informando a palavra que causou o erro, a linha e a coluna 
 onde ocorreu, e o token que estava sendo processado.
 
 Parâmetros:
 - palavra: A palavra que causou o erro.
 - lin: A linha onde o erro ocorreu.
 - col: A coluna onde o erro ocorreu.
 - token: O token que estava sendo analisado.
 - changeToken: Flag para indicar se o token precisa ser alterado.
 - flagLexico: Flag que indica se o erro léxico foi encontrado.
 - pilhaSintatico: Pilha utilizada pelo analisador sintático (interface entre análise léxica e sintática).
 */
void erroLexico(void *pilhaSintatico, char *palavra, int lin, int col, bool *changeToken, bool *flagLexico, char *token);

/*
 Função charIndex
 
 Descrição:
 Esta função recebe um caractere de entrada e retorna o índice correspondente desse caractere
 no alfabeto utilizado pelo analisador léxico.
 
 Parâmetros:
 - alfabeto: O conjunto de caracteres aceitos pela linguagem.
 - input: O caractere de entrada.
 
 Retorno:
 - O índice do caractere no alfabeto ou -1 se o caractere não for encontrado.
 */
int charIndex(char *alfabeto, char input);

/*
 Função isFinalState
 
 Descrição:
 Verifica se o estado atual é um estado final, ou seja, um estado de aceitação de tokens.
 
 Parâmetros:
 - estadosF: Um array contendo os estados finais da máquina de estados.
 - estadoAtual: O estado atual da análise.
 
 Retorno:
 - Retorna true se o estado atual for um estado final; caso contrário, false.
 */
bool isFinalState(int *estadosF, int estadoAtual);

/*
 Função reiniciaVar
 
 Descrição:
 Esta função reseta várias variáveis que controlam o fluxo da análise léxica.
 É usada quando o analisador precisa recomeçar a leitura de um novo token.
 
 Parâmetros:
 - cursor: Ponteiro para o cursor que percorre a entrada.
 - newCursor: O novo valor para o cursor.
 - cursorInicio: Ponteiro para o início do token sendo analisado.
 - final: Ponteiro para a variável que armazena a posição final do token.
 - estadoAtual: Ponteiro para o estado atual da análise léxica.
 */
void reiniciaVar(int *cursor, int newCursor, int *cursorInicio, int *final, int *estadoAtual);

/*
 Função reiniciaVar
 
 Descrição:
 Esta função pega o proximo token da string maior tokens.
 
 Parâmetros:
 - tokens: Linha de tokens da entrada.
 - atual: Numero do token atual.
 */
char* getNewToken(char* tokens, int atual);
#endif
