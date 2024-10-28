#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>  // Biblioteca para entrada e saída
#include <stdlib.h> // Biblioteca para alocação de memória e funções de sistema
#include <string.h> // Biblioteca para manipulação de strings
#include "pilha.h"  // Header file que define a estrutura da pilha e suas funções
#include "sintatico.h"  // Header file que contém funções relacionadas à análise sintática

typedef struct no {
    int valor;        // Valor armazenado no nó (pode representar o estado do analisador)
    int lin;          // Linha associada ao token armazenado no nó
    int col;          // Coluna associada ao token armazenado no nó
    char *token;      // Token armazenado no nó
    struct no *prox;  // Ponteiro para o próximo nó na pilha
} Node;

typedef struct {
    Node *topo;  // Ponteiro para o topo da pilha (nó mais recentemente inserido)
} Pilha;

/*
 * Nome da função: inicializaPilha
 *
 * Descrição:
 * Inicializa uma pilha alocando a memória para a estrutura e configurando seu topo como NULL.
 *
 * Parâmetros:
 * - Não possui parâmetros de entrada.
 *
 * Retorno:
 * - Um ponteiro genérico (void*) para a pilha recém-inicializada.
 */
void *inicializaPilha();

/*
 * Nome da função: insertNode
 *
 * Descrição:
 * Insere um novo nó na pilha contendo o valor, linha, coluna e token fornecidos. O novo nó se
 * tornará o novo topo da pilha.
 *
 * Parâmetros:
 * - p: ponteiro para a estrutura de pilha onde o nó será inserido.
 * - valor: o valor a ser armazenado no nó (normalmente representa o estado do analisador).
 * - lin: a linha associada ao token armazenado no nó.
 * - col: a coluna associada ao token armazenado no nó.
 * - token: uma string que contém o token a ser armazenado no nó.
 */
void insertNode(Pilha *p, int valor, int lin, int col, char *token);

/*
 * Nome da função: removeNode
 *
 * Descrição:
 * Remove o nó que está no topo da pilha, atualizando o ponteiro do topo para o próximo nó na
 * pilha e liberando a memória do nó removido.
 *
 * Parâmetros:
 * - p: ponteiro para a estrutura de pilha de onde o nó do topo será removido.
 */
void removeNode(Pilha *p);

/*
 * Nome da função: getNode
 *
 * Descrição:
 * Retorna o valor armazenado no nó que está no topo da pilha.
 *
 * Parâmetros:
 * - p: ponteiro para a estrutura de pilha de onde o valor do topo será retornado.
 *
 * Retorno:
 * - O valor armazenado no topo da pilha.
 */
int getNode(Pilha *p);

/*
 * Nome da função: getLinha
 *
 * Descrição:
 * Retorna a linha associada ao nó que está no topo da pilha.
 *
 * Parâmetros:
 * - p: ponteiro para a estrutura de pilha de onde a linha do topo será retornada.
 *
 * Retorno:
 * - A linha associada ao nó do topo da pilha.
 */
int getLinha(Pilha *p);

/*
 * Nome da função: getColuna
 *
 * Descrição:
 * Retorna a coluna associada ao nó que está no topo da pilha.
 *
 * Parâmetros:
 * - p: ponteiro para a estrutura de pilha de onde a coluna do topo será retornada.
 *
 * Retorno:
 * - A coluna associada ao nó do topo da pilha.
 */
int getColuna(Pilha *p);

/*
 * Nome da função: getToken
 *
 * Descrição:
 * Retorna o token armazenado no nó que está no topo da pilha.
 *
 * Parâmetros:
 * - p: ponteiro para a estrutura de pilha de onde o token do topo será retornado.
 *
 * Retorno:
 * - Uma string contendo o token armazenado no topo da pilha.
 */
char *getToken(Pilha *p);

/*
 * Nome da função: printPilha
 *
 * Descrição:
 * Imprime o conteúdo da pilha a partir do topo até a base, exibindo o valor, linha, coluna e
 * token de cada nó.
 *
 * Parâmetros:
 * - p: ponteiro para a estrutura de pilha que será impressa.
 */
void printPilha(Pilha *p);

/*
 * Nome da função: freePilha
 *
 * Descrição:
 * Libera a memória de todos os nós da pilha, removendo cada um até que a pilha esteja vazia.
 *
 * Parâmetros:
 * - p: ponteiro para a estrutura de pilha que será liberada.
 */
void freePilha(Pilha *p);

#endif
