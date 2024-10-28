#include "Header.h"

int main(int argc, char** argv){
    char *Path_Entrada, *Path_Saida, *nomeGeo, *nomeQry = "",*nomeBanco;
    char *relatorio;
    argumentos(&Path_Entrada,&nomeGeo,&Path_Saida,&nomeQry,argc,argv);
    if(Path_Entrada[strlen(Path_Entrada)-1]!='/')strcat(Path_Entrada,"/");
    if(Path_Saida[strlen(Path_Saida)-1]!='/')strcat(Path_Saida,"/");
    char* aux = calloc(256,sizeof(char));
    if (strcmp(nomeQry, "") != 0) {
        strcpy(aux,nomeQry);
        aux = strchr(aux,'/');
        if(aux[0] == '/') memmove(aux, aux + 1, strlen(aux));
    }
  

    char* geral = ajeitaNomes(nomeGeo,aux);

    nomeGeo = concatPathNome(Path_Entrada,nomeGeo);
    FILE* arq_geo = fopen(nomeGeo,"r");
    nomeBanco = concatPathNome(Path_Saida,geral);
    strcat(nomeBanco,".svg");
    ArqSvg banco_de_dados= abreEscritaSvg(nomeBanco);
    Lista banco = createLst(-1);
    LerGeo(arq_geo,banco);

    if (strcmp(nomeQry,"") != 0){
        char* nomeRelatorio,*nomeFotos;

        nomeQry = concatPathNome(Path_Entrada,nomeQry);
        FILE* arq_qry = fopen(nomeQry,"r");

        nomeRelatorio = concatPathNome(Path_Saida,geral);
        strcat(nomeRelatorio,".txt");
        FILE* arq_txt = fopen(nomeRelatorio,"w");

        nomeFotos = concatPathNome(Path_Saida,geral);
        LerQry(arq_qry,arq_txt,banco_de_dados,banco,nomeFotos);
        fclose(arq_qry);
        fclose(arq_txt);

    }
    fold(banco,escreveGeralSvg,banco_de_dados);
    fechaSvg(banco_de_dados);
    Executa_ListaFormas(banco); 
    

    return 0;
}