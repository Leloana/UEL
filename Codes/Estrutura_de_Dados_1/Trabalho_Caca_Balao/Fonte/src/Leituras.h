#ifndef LEGEO_H
#define LEGEO_H

#include "FuncLeituras.h"

/*Le arquivo Qry e baseado em seus comandos faz modificaçoes na lista "lista"
cada funçao reporta o que fez no arquivo txt e caso necessario, escreve as modificaçoes
feitas no arquivo banco, namefoto é necessario para gerar nome de fotos bem segmentados*/
void LerQry(FILE* qry,FILE* txt,FILE* banco, Lista lista,char* nameFoto);

/*Le cada linha de um arquivo de texto qualquer retornando um char** de cada palavra
de cada linha do arquivo.Deve ser repetido ate que o arquivo se esgote*/
char** LeituraLinha(FILE *arq, char* palavras[],int *n);

/*Le arquivo Geo e baseado em seus comandos gera objetos formas que sao inseridos
na lista "geral", há tambem um comando(ts) que nao gera forma, porem muda a fonte dos
seguintes textos*/
void LerGeo(FILE* geo,Lista geral);

Lista cria_lista_Baloes(Lista lista, Lista baloes);

Lista cria_lista_Cacas(Lista lista, Lista cacas);

#endif