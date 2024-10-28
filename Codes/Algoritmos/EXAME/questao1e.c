//        QUESTAO 1 EXAME
//MARCELO FERREIRA DE ALMEIDA
//PALAVRAS : ROCK, POSTURA,SALVE,OITO,COMIDA,SAKURAY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void acha(char *palavra,char **quadro);

int main(void)
{
    char **palavras;
    char *procura;
    procura = malloc(sizeof(char));

    printf("PALAVRA A PROCURAR :");
        scanf(" %s", procura);

    printf("\n");

    palavras = malloc(sizeof(char*));

    for (int i = 0; i < 31; i++) {
        *(palavras + i) = malloc(30 * sizeof(char));//aloca memória para matriz
    }

    FILE *quadro = fopen("caca.txt", "r");
    for(int k=0; k<30;k++)
        for(int m=0; m<30; m++){
            fscanf(quadro," %c", *(palavras+k)+m);
        }
    fclose(quadro);

    printf("%s", procura);
    for(int k=0; k<30;k++){
        printf("\n");
        for(int m=0; m<30; m++){
            printf(" %c ", *(*(palavras+k)+m));
        }
    }
    acha(procura, palavras);
    return 0;
}

void acha(char *palavra,char **quadro)
{

    for(int k=0;k<30;k++){
        for(int m=0; m<30;m++){
            if(*(*(quadro+k)+m) == *palavra){
                //PALAVRA PARA FRENTE
                if(*(*(quadro+k)+(m+1)) == *(palavra+1)){
                    int guarda, encontrada = 1;
                    for(guarda =0; guarda<strlen(palavra); guarda ++){
                        if(*(*(quadro+k)+(m+guarda)) != *(palavra+guarda)) encontrada = 0;
                        }
                    if(encontrada == 1) printf("\nACHEI \nPRIMEIRA LETRA EM %d:%d \n", k+1,m+1);
                    if(encontrada) break;
                }
                //PALAVRA PARA BAIXO
                else if(*(*(quadro+k+1)+m) == *(palavra+1)){

                    int guarda, encontrada = 1;
                    for(guarda = 0; guarda<strlen(palavra); guarda ++){
                        if(*(*(quadro+(k+guarda))+m) != *(palavra+guarda)) encontrada = 0;
                        }
                    if(encontrada == 1) printf("\nACHEI \nPRIMEIRA LETRA EM %d:%d \n", k+1,m+1);
                    if(encontrada) break;
                    }
                //PALAVRA PARA CIMA
                else if(*(*(quadro+(k-1))+m) == *(palavra+1)){
                    int guarda, encontrada = 1;
                    for(guarda = 0; guarda<strlen(palavra); guarda ++){
                        if(*(*(quadro+(k-guarda))+m) != *(palavra+guarda)) encontrada = 0;
                        }
                    if(encontrada == 1) printf("\nACHEI \nPRIMEIRA LETRA EM %d:%d \n", k+1,m+1);
                    if(encontrada) break;
                    }
                //PALAVRA PARA TRÁS
                else if(*(*(quadro+k)+(m-1)) == *(palavra+1)){
                    int guarda, encontrada = 1;
                    for(guarda = 0; guarda<strlen(palavra); guarda ++){
                        if(*(*(quadro+k)+(m-guarda)) != *(palavra+guarda)) encontrada = 0;
                        }
                    if(encontrada == 1) printf("\nACHEI \nPRIMEIRA LETRA EM %d:%d \n", k+1,m+1);
                    if(encontrada) break;
                    }
                //PALAVRA PARA CIMA - DIAGONAL  - DIREITA
                else if(*(*(quadro+k-1)+(m+1)) == *(palavra+1)){
                    int guarda, encontrada = 1;
                    for(guarda = 0; guarda<strlen(palavra); guarda ++){
                        if(*(*(quadro+(k-guarda))+(m+guarda)) != *(palavra+guarda)) encontrada = 0;
                        }
                    if(encontrada == 1) printf("\nACHEI \nPRIMEIRA LETRA EM %d:%d \n", k+1,m+1);
                    if(encontrada) break;
                    }
                //PALAVRA PARA CIMA - DIAGONAL  - ESQUERDA
                else if(*(*(quadro+k-1)+(m-1)) == *(palavra+1)){
                    int guarda, encontrada = 1;
                    for(guarda = 0; guarda<strlen(palavra); guarda ++){
                        if(*(*(quadro+(k-guarda))+(m-guarda)) != *(palavra+guarda)) encontrada = 0;
                        }
                    if(encontrada == 1) printf("\nACHEI \nPRIMEIRA LETRA EM %d:%d \n", k+1,m+1);
                    if(encontrada) break;
                    }
                //PALAVRA PARA BAIXO - DIAGONAL  - DIREITA
                else if(*(*(quadro+k+1)+(m+1)) == *(palavra+1)){
                    int guarda, encontrada = 1;
                    for(guarda = 0; guarda<strlen(palavra); guarda ++){
                        if(*(*(quadro+(k+guarda))+(m+guarda)) != *(palavra+guarda)) encontrada = 0;
                        }
                    if(encontrada == 1) printf("\nACHEI \nPRIMEIRA LETRA EM %d:%d \n", k+1,m+1);
                    if(encontrada) break;
                    }
                //PALAVRA PARA BAIXO - DIAGONAL  - ESQUERDA
                else if(*(*(quadro+k+1)+(m-1)) == *(palavra+1)){
                    int guarda, encontrada = 1;
                    for(guarda = 0; guarda<strlen(palavra); guarda ++){
                        if(*(*(quadro+(k+guarda))+(m-guarda)) != *(palavra+guarda)) encontrada = 0;
                        }
                    if(encontrada == 1) printf("\nACHEI \nPRIMEIRA LETRA EM %d:%d \n", k+1,m+1);
                    if(encontrada) break;
                    }
                }
             
            }
        }
}
