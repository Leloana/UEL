#include "Leituras.h"
#include "caca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** LeituraLinha(FILE *arq, char* palavras[],int *n)
{
    char linha[100];
    char *token;
    const char *delim = " \t\n";
    int i = 0;
    *n = i;
    // lê uma linha do arquivo
    if (fgets(linha, 100, arq) != NULL)
    {
        // separa a primeira palavra da linha
        token = strtok(linha, delim);
        // enquanto houver palavras na linha
        while (token != NULL)
        {
            // aloca memória para armazenar a palavra
            palavras[i] = (char *)malloc(strlen(token) + 1);
            // copia a palavra para a variável
            strcpy(palavras[i], token);
            // incrementa o contador de palavras
            i++;
            // separa a próxima palavra da linha
            token = strtok(NULL, delim);
        }
        // atualiza o número de palavras na linha
        *n = i;
    }
    else
    {
        // atualiza o número de palavras na linha
        *n = 0;
    }
    return palavras;
}

void LerGeo(FILE* geo,Lista geral){
    char* palavras[100];
    int n;
    char family[50] = "sans (sans-serif)";//seta padrao de ts
    char weight[50] = "normal";//caso a func ts seja chamada o valor setado muda
    char size[50] = "16px";
    if(geo == NULL)printf(" ERRO AO ABRIR ARQUIVO GEO\n");
    else{
        char ** aux ;
        while(!feof(geo)){//enquanto nao acabar o geo as figuras sao geradas
            aux = LeituraLinha(geo,palavras,&n);//le a linha do geo
            if(strcmp(aux[0],"l") == 0){
                Linha L = criaLinha(atoi(aux[1]),strtod(aux[2],NULL),strtod(aux[3],NULL),strtod(aux[4],NULL),strtod(aux[5],NULL), aux[6]);
                insertLst(geral,(Linha)L);
                for(int i = 0 ; i < 7;i++)free(aux[i]);//da free nas palavras da linha
            }
            else if(strcmp(aux[0],"r") == 0){
                Retangulo R = criaRect(atoi(aux[1]),strtod(aux[2],NULL),strtod(aux[3],NULL),strtod(aux[4],NULL),strtod(aux[5],NULL),aux[6],aux[7]);
                insertLst(geral,(Retangulo)R);
                for(int i = 0 ; i < 8;i++)free(aux[i]);
            }
            else if(strcmp(aux[0],"c") == 0){
                Circulo C = criaCirc(atoi(aux[1]),strtod(aux[2],NULL),strtod(aux[3],NULL),strtod(aux[4],NULL),aux[5],aux[6]);
                insertLst(geral,(Circulo)C);
                for(int i = 0 ; i < 7;i++)free(aux[i]);
            }
            else if(strcmp(aux[0],"ts")==0){
                strncpy(family,aux[1],50);
                strncpy(weight,aux[2],50);
                strncpy(size,aux[3],50);
                for(int i = 0 ; i < 4;i++)free(aux[i]);
            }
            else if(strcmp(aux[0],"t") == 0){
                Texto T = criaTexto(atoi(aux[1]),strtod(aux[2],NULL),strtod(aux[3],NULL),aux[4],aux[5],aux[6], aux[7]);
                set_text_Style(T, family,weight,size);
                insertLst(geral, (Texto)T);
                for(int i = 0 ; i < 8;i++)free(aux[i]);
            }
		else break;//caso tenha um comando desconhecido no .geo o processo acaba
        }
        // free(aux);
    }
}

void LerQry(FILE* qry,FILE* txt,FILE* banco, Lista lista,char* nameFoto){
    char* palavras[100];
    int n;
    Lista decoracoes = createLst(-1);//guarda as decoraçoes (x de destruicao e borda de fotos)
    if(qry == NULL)printf(" ERRO AO ABRIR ARQUIVO QRY\n");
    else{
        Lista Baloes_ = filter(lista,isBaloon);
        Lista Cacas_ = filter(lista,iscaca);
        Lista Baloes = map(Baloes_,set_Balao);//Inicia todos os baloes
        Lista Cacas = map(Cacas_,set_caca);
        char ** aux = NULL;
        while(!feof(qry)){//enquanto nao acabar arquivo .qry o banco de dados é manipulado
            aux = LeituraLinha(qry, palavras,&n);
            if(strcmp(aux[0], "mv") == 0){
                LinhaMove(txt,lista,atoi(aux[1]),strtod(aux[2],NULL),strtod(aux[3],NULL));
                for(int i = 0;i < 3;i++)free(aux[i]);
            }
            else if(strcmp(aux[0], "g") == 0){
                LinhaRotaciona(txt,lista,atoi(aux[1]),strtod(aux[2],NULL));
                for(int i = 0;i < 3;i++)free(aux[i]);
            }
            else if(strcmp(aux[0], "ff") == 0){
                FocoFoto(Baloes,atoi(aux[1]),strtod(aux[2],NULL),strtod(aux[3],NULL),strtod(aux[4],NULL));
                for(int i = 0;i < 5;i++)free(aux[i]);
            }
            else if(strcmp(aux[0], "tf") == 0){
                LinhaTiraFoto(txt,Baloes,lista,decoracoes,atoi(aux[1]),atoi(aux[2]));
                for(int i = 0;i < 3;i++)free(aux[i]);
            }
            else if(strcmp(aux[0], "df") == 0){
                ReportaFotos(txt,Baloes,atoi(aux[1]),aux[3],atoi(aux[2]),nameFoto);
                for(int i = 0;i < 3;i++)free(aux[i]);
            }
            else if(strcmp(aux[0], "d") == 0){
                DisparoCaca(txt,banco,Baloes,Cacas,lista,decoracoes,atoi(aux[1]),aux[2],strtod(aux[3],NULL),atoi(aux[4]), strtod(aux[5],NULL));
                for(int i = 0;i < 6;i++)free(aux[i]);
            }
            else if(strcmp(aux[0], "b?") == 0){
                Report_Baloes(txt,Baloes);
                free(aux[0]);
            }
            else if(strcmp(aux[0], "c?") == 0){
                Report_Cacas(txt,Cacas);
                free(aux[0]);
            }
            else return;
    // free(aux);
    }
    if(!isEmptyLst(decoracoes)){//caso a lista decoraçoes nao tenha nada nao faz isso
        fold(decoracoes,escreveGeralSvg,banco);//escreve as decoracoes no banco de dados
        Executa_ListaFormas(decoracoes);//da free personalizado e kiilst
    }
    Executa_ListaFormas(Baloes);
    Executa_ListaFormas(Cacas);
    }
}