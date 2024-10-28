//      QUESTAO 3
// MARCELO FERREIRA DE ALMEIDA
#include <stdio.h>
#include <stdlib.h>

struct cel{
    int valor;
    struct cel *proximo;
};
typedef struct cel celula;
struct L{
    celula *inicio;
    celula *fim;
    int tamanho;
};
typedef struct L Lista;


void cria(Lista *lista);
void escreve(Lista *lista);
void InsereFim(Lista *lista, int valor);
void trocaNo(Lista *lista, int posicao);

void main() {

    Lista cabeca;
    int quantia;
    cria(&cabeca);
    printf("\nQUANTOS ELEMENTOS DESEJA INSERIR?\n");
        scanf("%d", &quantia);
    printf("\n");
    for(int i=0; i<quantia;i++)InsereFim(&cabeca,i);
    printf("\n LISTA INICIAL: ");
    
    escreve(&cabeca);

    printf("\n APOS MUDANCAS: ");
    for(int i=1; i<quantia; i = i+2)trocaNo(&cabeca, i);
    escreve(&cabeca);

}
//troca nos
void trocaNo(Lista *lista, int posicao) {  
    celula *aux = lista->inicio;
    celula *aux2 = lista->inicio;

    if (lista->inicio == NULL) { 
        printf("Lista vazia!!\n");
        return;
    }

    else if (lista->tamanho == 1) return; //Confere se a lista tem so uma célula

    if (posicao == lista->tamanho) return; //ve se lista tem continuidade

    if (posicao == 1 ) { //Troca da primeira célula com a segunda
        lista->inicio = aux->proximo;
        aux->proximo = lista->inicio->proximo;
        lista->inicio->proximo = aux;
    }
    else if(posicao == 2){
        lista->inicio = aux->proximo;
        aux->proximo = lista->inicio->proximo;
        lista->inicio->proximo = aux;
    }
    else { //Troca da célula de posição = posição (parâmetro) com a próxima
        for (int i=0;i<posicao-1;i++) aux = aux->proximo;
        for (int i=0;i<posicao-2;i++) aux2 = aux2->proximo;
        aux2->proximo = aux->proximo;
        aux->proximo = aux2->proximo->proximo;
        aux2->proximo->proximo = aux;
    }
}

void cria(Lista *lista) { //Função responsável por criar a lista

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho++;
}

void escreve(Lista *lista) { //Função responsável por escrever a lista

    celula *aux = lista->inicio;

    while (aux != NULL) {
        printf("%d ",aux->valor);
        aux = aux->proximo;
    }
    printf("\n");
}

void InsereFim(Lista *lista, int valor) { 

    celula *aux = malloc(sizeof(celula));//aloca memoria
    aux->valor = valor;

    if (lista->inicio == NULL) { 
        lista->inicio = aux;
        lista->fim = aux;
        lista->fim->proximo = NULL;
    }
    else {
        lista->fim->proximo = aux;
        lista->fim = aux;
        lista->fim->proximo = NULL;
    }
    lista->tamanho++;
}
