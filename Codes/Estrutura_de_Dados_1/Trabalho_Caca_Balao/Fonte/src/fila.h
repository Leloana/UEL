#ifndef FILA_
#define FILA_

#include <stdbool.h>

typedef void* data;
typedef void* Fila;
// cria uma fila circular estatica com 15 espaços
Fila createQueue();
// checa se a fila esta vazia
bool isQueueEmpty(Fila X);
// checa se a fila esta cheia
bool isQueueFull(Fila X);
// insere no final da fila aumentando seu tamanho em 1
void insertQueue(Fila X, data elemento);
// remove do começo da fila diminuindo seu tamanho em 1
data getDataQueue(Fila X);
//retorna i tamanho da lista
int tamQueue(Fila F);

#endif