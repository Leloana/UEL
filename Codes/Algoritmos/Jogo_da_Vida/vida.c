#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define TAM 30

void life(int **quadro);
int main (int argc, char *argv[])
{
    int **celula = malloc(TAM * sizeof(int*));

    for (int i = 0; i < TAM; i++) {
        *(celula + i) = malloc(TAM * sizeof(int));//aloca memória para matriz
    }

    FILE * quadro = fopen("quadro.txt", "r"); 

    for(int i=0; i<TAM; i++){
        for(int j=0; j<TAM;j++){
            fscanf(quadro,"%d", (*(celula + i) + j));
        }
    }
    fclose(quadro);

    for(int vezes = 0; vezes < atoi(argv[1]); vezes++){
    printf("\n======================================== GERACAO %d ===================================\n", vezes+1);
     for(int i=0; i<TAM; i++){
        printf("\n");
        for(int j=0; j<TAM;j++){
            printf(" %d ", *(*(celula + i) + j));//printa quadro
        }
    }
    printf("\n\n\n");
    sleep(1);
    life(celula);//faz mudanças necessárias no quadro
    }


    return 0;
}



void life(int **quadro)
{
    int i,j,k,t;
    
    int **aux = malloc(TAM * sizeof(int*));

    for (int i = 0; i < TAM; i++) {
        *(aux + i) = malloc(TAM * sizeof(int));
    }//ponteiro auxiliar,é usada como "mapa",afim de modificar o quadro sem perder dados do anterior

    for(int i=0; i<TAM; i++){
            for(int j=0; j<TAM;j++){
                *(*(aux + i) + j) = *(*(quadro + i) + j);// auxiliar recebe quadro
            }

    }

    for(i = 0; i < TAM; i++){
        for(j = 0; j < TAM; j++){

            int Vizinhos_vivos = 0;//guarda quantidade de celulas vizinhas vivas(1)

            //analisa vizinhos de cada celula
            for(k = -1 ; k < 2 ; k++){
                for(t= -1 ; t < 2 ; t++){ 
                    
                    if(k!=0 || t!=0){//caso ambos forem 0, estaria analisando a própria celula e não as vizinhas

                        if((i + k) >= 0 && (i + k) < TAM && (j + t) >= 0 && (j + t) < TAM){//verifica se está dentro do quadro
                            if(*(* (aux + i + k) + j + t) == 1) Vizinhos_vivos++;

                        }
                    }
                }
            }
            if(*(* (aux + i ) + j ) == 1){
                if(Vizinhos_vivos < 2 || Vizinhos_vivos > 3 ) (*(* (quadro + i) + j)) = 0;// analisa condiçoes de vida das células
            }

            else{
                if (Vizinhos_vivos == 3) (*(* (quadro + i) + j)) = 1;
            }
            

        }
    }

}
