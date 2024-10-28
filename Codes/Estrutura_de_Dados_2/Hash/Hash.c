#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"

#define TAM 100
//Calculo que define a posicao do elemento na hash pela DOBRA
int hashPosic(int value){
    int valor = value;
    char CHAVE[7];
    sprintf(CHAVE,"%d", valor);//Converte valor para string
    int tam = strlen(CHAVE);
    int num[6];//Guarda o tamanho da string

    if(tam > 6){//caso tenha mais que 6 de tamanho
        printf("\n!TAMANHO INVALIDO, INSIRA UM ELEMENTO DE ATE 6 DIGITOS!\n");
        return -1 ;
    }
    
    //TRANSFERE DIGITO PARA VETOR
    if(tam == 6){//caso o digito tenha o tamanho maximo
        for (int i = 0 ; i < tam; i++) {
            num[5 - i] = valor % 10;
            valor /= 10;
        }
    }
    else{//caso contrario
        for (int i = 0 ; i < (6 - tam); i++) {
            num[i] = 0;
        }
        int aux = tam - 1;
        for (int i = (6 - tam) ; i < 6 ; i++) {
            num[(6 - tam) + aux] = valor % 10;
            valor /= 10;
            aux--;
        } 
    }
    
    printf("\nVETOR FORMADO = {");
    for (int i = 0 ; i < 5; i++) {//Escreve o vetor formado pela separação dos valores
        printf("%d, ",num[i]);
    }
    printf("%d}", num[5]);

    int dobra1[4];
    if((num[0]%10) + (num[3]%10) >= 10){//se a soma do segundo digito subir 1
        dobra1[1] = num[0] + num[3] - 10;
    }
    else dobra1[1] = num[0] + num[3];

    if((num[1]%10) + (num[2]%10) >= 10){//se a soma do segundo digito subir 1
        dobra1[0] = num[1] + num[2] - 10;
    }
    else dobra1[0] = num[1] + num[2];
 
    dobra1[2] = num[4];
    dobra1[3] = num[5];

    printf("\nDobra 1 = {%d, %d, %d, %d}",dobra1[0],dobra1[1],dobra1[2],dobra1[3]);

    int dobra2[2];

    if((dobra1[0]%10) + (dobra1[3]%10) >= 10){//se a soma do segundo digito subir 1
        dobra2[1] = dobra1[0] + dobra1[3] - 10;
    }
    else dobra2[1] = dobra1[0] + dobra1[3];

    if((dobra1[1]%10) + (dobra1[2]%10) >= 10){//se a soma do segundo digito subir 1   
        dobra2[0] = dobra1[1] + dobra1[2] - 10;
    }
    else dobra2[0] = dobra1[1] + dobra1[2];  

    printf("\nDobra 2 = {%d, %d}",dobra2[0],dobra2[1]);


    int dobraFinal = 0;
    char Digito1[10];
    char Digito2[10];
    char Resultado[20];

    sprintf(Digito1,"%d", dobra2[0]);//Transforma em string
    sprintf(Digito2,"%d", dobra2[1]);//Transforma em string

    strcpy(Resultado,Digito1);
    strcat(Resultado,Digito2);

    dobraFinal = atoi(Resultado);//Dobra final recebe resultado numerico

    return dobraFinal;
}
//Deleta o valor dado por "value"
bool deleteValue(Lista hash[], int value){
    int posic = hashPosic(value);//Primeiro busca a posicao do valor

    if(!hash[posic]){
        printf("\n\n!NUMERO NAO ENCONTRADO!");
        return false;
    }
    
    Lista aux = hash[posic];//Lista pointer auxiliar
    int num = 0;
    Posic deletPointer = getFirstLst(aux);//deletPointer recebe a cabeca da lista
    num = getLst(aux, deletPointer);

    while(num != value ){
        deletPointer = getNextLst(aux, deletPointer);//deletPointer recebe o proximo ponteiro em relacao a ele mesmo   
        if (deletPointer == NULL)break; 
        num = getLst(aux, deletPointer);
    }

    if (deletPointer == NULL){
        printf("\n\n!NUMERO NAO ENCONTRADO!");
        return false;
    }
    
    removeLst(aux, deletPointer);//Remove da lista
    if(isEmptyLst(aux)){//Caso a lista esteja vazia deve remover a memoria alocada
        free(aux);
        hash[posic] = NULL ;
    }
    return true;
}
//Escreve TODOS os elementos da posicao "posic" da tabela hash
void printPosic(Lista hash[], int posic){
    printf("\nESCREVENDO LISTA [%d]:\n", posic);
    if(hash[posic] == NULL){
        printf("\nNAO HA VALORES NESTE SETOR");
        return;
    }
    
    Lista aux = hash[posic];//Lista pointer para a lista da posicao "posic"
    Iterador K = createIterator(aux,false);//Iterador caminha na lista

    printf("\nLISTA[%d] = ", posic);
    while (!isIteratorEmpty(aux,K)){//Enquanto o iterador nao terminar de percorrer a lista
        printf(" %d ", (int)getIteratorNext(aux,K));//escreve os valores 
    }
}

int main(void){
    Lista vetor[TAM] = {0};
    int Inseridos[100] = {0};
    int quantia = 0;

    int removidos[100] = {0};
    int quantiaRem = 0;

    int num;
    // int num = calloc(1,sizeof(int));

    int input = 0;
    printf("\n=====================TABELA HASH====================\n");
    printf("\n\t\t[0]INSERIR UM VALOR\n");
    printf("\n\t\t[1]REMOVER UM VALOR\n");
    printf("\n\t\t[2]ESCREVER LISTA\n");
    printf("\n\t\t[3]SAIR\n");
    printf("\n======================================================\n");
    printf("\nACAO = ");
    
    scanf("%d", &input);

    while(input != 3){//Display de opcoes
        if(input == 0){// 0 = inserir
            printf("\nDIGITE A CHAVE = ");
            
            scanf("%d", &num);
            
            int posic = hashPosic(num);

            if(posic > 0){//Caso a posicao seja positiva insere
                if(vetor[posic] == NULL){
                    Lista new = createLst(-1);//Cria lista naquela posicao caso nao tenha
                    vetor[posic] = new;
                }

                Lista aux = vetor[posic];

                printf("\n\nPOSICAO = {%d}\n",posic);

                insertLst(aux,num);//Insere o novo valor no final da lista

                Inseridos[quantia] = (int)num;
                quantia++;

                printf("\nINSERIDO COM SUCESSO!!");
            }
        }
        else if(input == 1){// 1 = remover
            printf("\nVALORES INSERIDOS: ");//Escreve o que ja foi inserido para ajudar na remocao
            for(int i = 0; i < quantia; i ++){
                printf(" %d ", Inseridos[i]);
            }
            printf("\nVALORES REMOVIDOS: ");//Escreve o que foi removido para ajudar na remocao
            for(int i = 0; i < quantiaRem; i ++){
                printf(" %d ", removidos[i]);
            }

            int removido = 0;
            printf("\nVALOR A REMOVER = ");
            scanf("%d", &removido);

            if(deleteValue(vetor, removido)){
            removidos[quantiaRem] = removido;
            quantiaRem ++;
            printf("\n\nREMOCAO CONCLUIDA");
            }
        }

        else if(input == 2){// 2 = escrever
            int posicao = 0;
            printf("\nPOSICAO DA LISTA = ");
            scanf("%d", &posicao);
            printPosic(vetor, posicao);
            printf("\n\nESCRITA CONCLUIDA");
        }
        printf("\n======================================================\n");
        printf("\nACAO = ");
        scanf("%d", &input);
    }

    for(int i = 0; i < TAM; i++)killLst(vetor[i]);//Libera memoria

    return 0;
}