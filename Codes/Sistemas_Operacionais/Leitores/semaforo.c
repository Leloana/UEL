#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t recurso;         // Controle do acesso ao recurso
sem_t mutexCount;           // Controle para atualizar a contagem dos leitores
int contador_leitores = 0;

void* leitor(void* arg) {
    int id = *(int*)arg;
    // Bloqueia para incrementar a contagem de leitores
    sem_wait(&mutexCount);
    contador_leitores++;
    if (contador_leitores == 1) {  // Primeiro leitor bloqueia o recurso para escritores
        sem_wait(&recurso);
    }
    sem_post(&mutexCount);              // Libera o controle da contagem de leitores
    // Leitura do recurso
    printf("Leitor %d está lendo.\n", id);
    // Bloqueia para decrementar a contagem de leitores
    sem_wait(&mutexCount);
    contador_leitores--;
    if (contador_leitores == 0) {  // Último leitor libera o recurso
        sem_post(&recurso);
    }
    sem_post(&mutexCount);              // Libera o controle da contagem de leitores
    return NULL;
}

void* escritor(void* arg) {
    int id = *(int*)arg;
    // Escritor bloqueia o recurso
    sem_wait(&recurso);
    // Escrita no recurso
    printf("Escritor %d está escrevendo.\n", id);
    sem_post(&recurso);            // Escritor libera o recurso
    return NULL;
}

int main() {
    pthread_t leitores[5], escritores[5];
    int ids[5];
    
    sem_init(&recurso, 0, 1);
    sem_init(&mutexCount, 0, 1);

    for (int i = 0; i < 5; i++) {
        ids[i] = i + 1;
        pthread_create(&leitores[i], NULL, leitor, &ids[i]);
        pthread_create(&escritores[i], NULL, escritor, &ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(leitores[i], NULL);
        pthread_join(escritores[i], NULL);
    }

    sem_destroy(&recurso);
    sem_destroy(&mutexCount);
    return 0;
}