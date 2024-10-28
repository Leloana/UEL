//          QUESTAO 2
// MARCELO FERREIRA DE ALMEIDA
#include <stdio.h>
#include <stdlib.h>

void rotaciona(int **A, int N);

int main(void)
{
    int N = 4;//tamanho da matriz do exemplo 4x4 em prova

    int **matriz = malloc(N * sizeof(int*));

    for (int i = 0; i < N; i++) {
        *(matriz + i) = malloc(N * sizeof(int));//aloca memória para matriz
    }
    FILE * quadro = fopen("questao2.txt", "r");
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            fscanf(quadro," %d", (*(matriz+i)+j));
        }
    }
    fclose(quadro);
    rotaciona(matriz, N);
    return 0;
}

void rotaciona(int **A, int N)
{
    int **matriz = malloc(N * sizeof(int*));/*crio matriz auxliar, será usada apenas para alocar a transposta
    e não a matriz rotacionada, esta será armazenada diretamente na matriz original*/

    for (int i = 0; i < N; i++) {
        *(matriz + i) = malloc(N * sizeof(int));//aloca memória para matriz
    }

    for(int i=0; i<N; i++){
        for(int j=0; j< N; j++){
            *(*(matriz+j)+i) = *(*(A+i)+j);//Tira a transposta da matriz
        }
    }
    for(int k=0; k < N; k++){
      for(int i=0; i < N; i++){
        *(*(A+i)+k) = *(*(matriz+i)+(N-1)-k);//Inverte as colunas da transposta
      }//A matriz original é diretamente modificada
    }
     for (int i = 0; i < N; i = i + 1){
      printf("\n");
      for (int j = 0; j < N; j = j + 1) {
        printf(" %d ", *(*(A+i)+j));
      }
    }
}