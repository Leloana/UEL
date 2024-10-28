#ifndef PATHS_H
#define PATHS_H
//coleta os argumentos do argv e os separa entre os char**
void argumentos (char **pathEntry,char **arqGeo,char **pathExit,char **arqQry,int argc,char **argv);
//concatena nome usando auxiliar
char* concatPathNome(char* Path, char* nome);
//concatena chars resultado = pathonomeGeo-nomeQry
char* AjeitaNomeFotos(char* patho,char* nomeGeo, char* nomeQry);
//concatena chars resultado = nomeGeo-nomeQry
char* ajeitaNomes(char* nomeGeo, char* nomeQry);

#endif