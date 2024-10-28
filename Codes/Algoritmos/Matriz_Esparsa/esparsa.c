#include <stdio.h>
#include <stdlib.h>
#define TAM 15

struct cel{//Lista unica q armazena todas as informações
  int conteudo;
  int i;
  int j;
  struct cel *prox;
};
typedef struct cel celula;


void insere(celula **pointer, int i, int j, int valor);
void insereinicio(celula **X,int i,int j,int valor);
void inserefim(celula ** ini,int i,int j, int valor);

void escrevematriz(int **matriz);
void escreve(celula * X);

int somaprincipal(celula *pointer);
celula *somamatriz(celula *A, celula *B);
celula  *multiplicaMatriz(celula *A, celula *B);

int main(void)
{
  celula *matrizA;// ponteiro inicial de A
  matrizA = NULL;
  int arq[TAM][TAM];
  FILE *quadro = fopen("matrizA.txt", "r");

  for(int k=0; k<TAM; k++){// Le o arquivo em uma matriz auxiliar
    for (int m=0; m<TAM; m++){
        fscanf(quadro," %d", &arq[k][m]);
        if(arq[k][m]!=0)insere(&matrizA, k, m, arq[k][m]);// caso o elemento da matriz seja 0 ele entra na lista
    }
  }
  printf("\n      MATRIZ A CONDENSADA   \n");
  escreve(matrizA);

  printf("\nSOMA ABAIXO DA DIAGONAL PRINCIPAL = %d \n", somaprincipal(matrizA));

  printf("\n      MATRIZ A COMPLETA   \n");
  for(int i=0; i<TAM; i++){//escreve a matriz incluindo os zeros
      printf("\n");
      for(int j=0; j<TAM; j++){
        printf(" %d ", arq[i][j]);
      }
    }
  fclose(quadro);

  celula *matrizB;//mesmo processo passa pela A
  matrizB = NULL;
  int arq2[TAM][TAM];
  FILE *quadro2 = fopen("matrizB.txt", "r");

  for(int k=0; k<TAM; k++){
    for (int m=0; m<TAM; m++){
        fscanf(quadro2," %d", &arq2[k][m]);
        if(arq2[k][m]!=0)insere(&matrizB, k, m, arq2[k][m]);
    }
  }
  printf("\n\n      MATRIZ B CONDENSADA\n");
  escreve(matrizB);

  printf("\nSOMA ABAIXO DA DIAGONAL PRINCIPAL = %d\n", somaprincipal(matrizB));

  printf("\n      MATRIZ B COMPLETA\n");
  for(int i=0; i<TAM; i++){
      printf("\n");
      for(int j=0; j<TAM; j++){
        printf(" %d ", arq2[i][j]);
      }
    }
  fclose(quadro);

  celula *soma;
  printf("\n\n      MATRIZ ESPARSA A+B\n\n");
  soma = somamatriz(matrizA,matrizB);
  escreve(soma);

  celula *multiplica;
  printf("\n\n      MATRIZ ESPARSA A*B\n\n");
  multiplica = multiplicaMatriz(matrizA,matrizB);
  escreve(multiplica);
  return 0;
}

celula *multiplicaMatriz(celula *A, celula *B)
{
  celula *C;
  C = NULL;

  int produto=0;
  int matrizA[TAM][TAM], matrizB[TAM][TAM], matrizC[TAM][TAM];
  //Para a multiplicação das matrizes usei a mesma ideia de antes de utilizar matrizes comuns como auliares
  for(int k=0; k<TAM; k++){
    for(int m=0; m<TAM; m++){
        if(A!=NULL){
          if(A->i==k && A->j==m){
            matrizA[k][m] = A->conteudo;//aqui caso o conteúdo da lista em relação à coordenada indicada, o valor é guardado
            A = A->prox;
          }
          else matrizA[k][m] = 0;// caso contrário ele armazena o valor zero para faciliar os cálculos de multiplicação
        }
        else matrizA[k][m] = 0; 
    }
  }
  for(int k=0; k<TAM; k++){
    for(int m=0; m<TAM; m++){
        if(B!=NULL){
          if(B->i==k && B->j==m){
            matrizB[k][m] = B->conteudo;// o mesmo feito em A
            B = B->prox;
          }
          else matrizB[k][m] = 0;
        }
        else matrizB[k][m] = 0;
    }
  }
  for(int k=0; k<TAM; k++){
    for(int m=0; m<TAM; m++){
      for(int aux=0; aux<TAM; aux++){
         produto += matrizA[k][aux]*matrizB[aux][m];// esta operação que multiplica as matrizes gerando uma nova
      }
         matrizC[k][m] = produto;
         produto = 0;
    }
  }
  for(int k=0; k<TAM; k++){
    for(int m=0; m<TAM; m++){
      if(matrizC[k][m]!=0)insere(&C, k, m, matrizC[k][m]);// cria lista com a matriz feita de A*B
    }
  }
  return C;
}
int somaprincipal(celula *pointer)
{
  int soma=0;
  if(pointer==NULL) return 0;
  while(pointer!=NULL){
  if(pointer->i > pointer->j)// se a linha do elemento for menor que a coluna ele será somado
  {
    soma += pointer->conteudo;
  }
    pointer = pointer->prox;
  }
  return soma;
}
celula *somamatriz(celula *A, celula *B)
{
  celula *C;
  C = NULL;

  for(int k=0; k<TAM;k++){
    for(int m=0; m<TAM; m++){
            int soma = 0;
            if(A!=NULL){
                if(A->i == k && A->j == m){//checa se o elemento possui as mesmas coordenadas que as necessárias para a soma
                   soma += A->conteudo;
                   A = A->prox;
                }
            }
            if(B!=NULL){
                if(B->i == k && B->j == m){// o mesmo que ocorreu em A
                  soma += B->conteudo;
                  B = B->prox;
                }
            }
        if(soma != 0)insere(&C, k, m,soma);// a soma é inserida numa nova lista (A+B)
    }
  }
  return C;
}
void insere(celula **pointer, int i, int j, int valor)
{
    if(*pointer == NULL) insereinicio(pointer, i,j, valor);//caso o ponteiro esteja vazio, é necessário inserir o primeiro elemento
    else inserefim(pointer, i , j, valor);
}
void escreve(celula * X)
{
    if(X == NULL) printf("\nA LISTA ESTA VAZIA!!!\n");// checa se a lista possui elementos
    else {
        while(X!=NULL){
                printf("conteudo = %d  posicao = %d:%d\n",X->conteudo, X->i, X->j);//escreve o conteudo e a posiçao
                X= X->prox;
        }
    }
}
void insereinicio(celula **X,int i,int j,int valor)
{
    celula *aux = malloc(sizeof(celula));//funções básicas de listas encadeadas
    aux -> conteudo = valor;
    aux->i = i;
    aux ->j = j;


    aux->prox = (*X);
    (*X) = aux;
    
}
void inserefim(celula ** ini,int i,int j, int valor)
{
    celula *fimaux;
    fimaux = *ini;//funções básicas de listas encadeadas

    while(fimaux->prox!=NULL) fimaux = fimaux->prox;

    celula *aux = malloc(sizeof(celula));
    aux->conteudo = valor;
    aux ->i = i;
    aux ->j = j;

    aux->prox = NULL;
    fimaux->prox = aux;
}