//  QUESTAO 3
// MARCELO FERREIRA DE ALMEIDA

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define linhas 15
#define colunas 15

void escreve(char m[linhas][colunas]);
int verifica(char m[linhas][colunas]);
int numeroGotas(char m[linhas][colunas]);

int main()
{
    int i, qpassos, j, aux1, aux2, diferenca = 1;
    char agua, M[linhas][colunas];

    for (i = 0; i < linhas; i++){
        for (j = 0; j < colunas; j++){
            if (i == 0)
                *(*(M + i) + j) = 45;
            else if (i == (linhas - 1))
                *(*(M + i) + j) = 43;
            else if ((j == 0) || (j == (colunas - 1)))
                *(*(M + i) + j) = 124;
            else
                *(*(M + i) + j) = 48;
        }
    }

    FILE *arq;
    arq = fopen("gotas.txt", "r");
    if (arq == NULL)
    {
        printf("ARQUIVO INVALIDO");
        exit(EXIT_SUCCESS);
    }

    for (i = 0; i < (linhas * colunas); i++){// le arquivo da chuva
        for (j = 0; j < 3; j++){
            if (j == 0)
                fscanf(arq, "%d", &aux1);
            else if (j == 1)
                fscanf(arq, "%d", &aux2);
            else
                fscanf(arq, "%c", &agua);
        }

        if ((aux1 == 0) && (aux2 == 0))
            break;
        else if ((aux1 < linhas - 1) && (aux2 < colunas - 1) && (aux1 > 0) && (aux2 > 0))
            M[aux1][aux2] = agua;
    }
    fscanf(arq, "%d", &qpassos);
    fclose (arq);

    printf("FIM\n");
    escreve(M);

    for (int qtdGer = 0; qtdGer < qpassos && diferenca != 0; qtdGer++){
        for (i = (linhas - 2); i >= 0; i--){
            for (j = (colunas - 2); j >=0; j--){
                if ((*(*(M + i) + j) == 71) || (*(*(M + i) + j) == 103)){
                    *(*(M + i) + j) = 48;
                    if (i + 1 < (linhas - 1))
                        *(*(M + i + 1) + j) = 71;
                }
                else if ((*(*(M + i) + j) == 80) || (*(*(M + i) + j) == 112)){
                    *(*(M + i) + j) = 48;
                    if (i + 2 < (linhas - 1))
                        *(*(M + i + 2) + j) = 80;

                    if ((M[i+1][j] == 71) || (*(*(M + i) + j) == 103))
                        *(*(M + i + 1) + j) = 48;
                }
            }
        }
        sleep (1);
        escreve(M);
        diferenca = verifica(M);
    }
    if (diferenca == 0)
        printf("\nFIM");
    printf("\nGOTAS NA JANELA: %d", numeroGotas(M));

    return 0;
}
int numeroGotas(char m[linhas][colunas])// checa numro de gotar no vidro
{
    int i, j, Gotas = 0;

    for (i = 0; i < linhas; i++){
        for (j = 0; j < colunas; j++){
            if ((*(*(m + i) + j) == 71) || (*(*(m + i) + j) == 80)){
                Gotas++;
                break;
            }
        }
    }
    return Gotas;
}

void escreve(char m[linhas][colunas])// printa a chuva
{
    int i, j;

    printf("\n");
    for (i = 0; i < linhas; i++){
        for (j = 0; j < colunas; j++){
            if (*(*(m + i) + j) == 48)
                printf("  ");
            else if (*(*(m + i) + j) == 103)
                printf("G ");
            else if (*(*(m + i) + j) == 112)
                printf("P ");
            else
                printf("%c ", *(*(m + i) + j));
        }
        printf("\n");
    }
}

int verifica(char m[linhas][colunas])
{
    int i, j, diferenca = 0;

    for (i = 0; i < linhas; i++){
        for (j = 0; j < colunas; j++){
            if ((*(*(m + i) + j) == 71) || (*(*(m + i) + j) == 80)){
                diferenca = 1;
                break;
            }
            else
                diferenca = 0;
        }
        if (diferenca == 1)
            break;
    }
    return diferenca;
}
