#include "paths.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* concatPathNome(char* Path, char* nome){
    char* caminho = calloc(256,sizeof(char));
    strcpy(caminho,Path);
    return strcat(caminho,nome);
}

void argumentos (char **pathEntry,char **arqGeo,char **pathExit,char **arqQry,int argc,char **argv){
    int i=1;
    while(i<argc){
        //path da entrada
        if(strcmp("-e",argv[i])==0 && (i+1)!=argc){
            i++;
            *pathEntry=argv[i];
        }
        //arquivo .geo
        if(strcmp("-f",argv[i])==0 && (i+1)!=argc){
            i++;
            *arqGeo=argv[i];
        }
        //path da saida
        if(strcmp("-o",argv[i])==0 && (i+1)!=argc){
            i++;
            *pathExit=argv[i];
        }
        //arquivo de consulta
        if(strcmp("-q",argv[i])==0 && (i+1)!=argc){
            i++;
            *arqQry=argv[i];
        }
        i++;
    }
}

char* AjeitaNomeFotos(char* patho,char* nomeGeo, char* nomeQry){
    char* Geo = calloc(256,sizeof(char));
    strcpy(Geo,nomeGeo);
    strtok(Geo,".");
    Geo = concatPathNome(patho,Geo);//aqui tenho patho/nomeGeo
    strcat(Geo,"-");
    char* Qry = calloc(256,sizeof(char));
    strcpy(Qry,nomeQry);
    strtok(Qry,".");//tenho nomeQry
    strcat(Geo,Qry);
    strcat(Geo,"-");

    return Geo;
}

char* ajeitaNomes(char* nomeGeo, char* nomeQry){
    char* nome = calloc(256,sizeof(char));//gera auxiliar para nao modificar a original
    strcpy(nome,nomeGeo);
    strtok(nome,".");//seleciona apenas parte antes do ponto
    if(strcmp(nomeQry, "") == 0)return nome;
    strcat(nome,"-");//add -
    char* Qry = calloc(256,sizeof(char));
    strcpy(Qry,nomeQry);
    strtok(Qry,".");
    strcat(nome,Qry);

    return nome;
}