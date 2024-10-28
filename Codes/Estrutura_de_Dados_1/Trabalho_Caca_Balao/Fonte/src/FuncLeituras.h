#ifndef FUNC_LEIT_
#define FUNC_LEIT_

#include "balao2.h"
#include <stdio.h>

/*reporta os dados da figura "guarda_forma"*/
void reporta_figura(FILE* txt,void* guarda_forma);

/*Analisa a area da camera atual do Balao, acessando seus dados pelo balao B,
caso a forma "analise" esteja dentro da foto, retorna verdadeiro*/
bool reconhece_area(Balao B, Forma analise);

/*Procura na lista o ID indicado por "ID", caso encontre retorna a figura,
caso contrario retorna NULL*/
void* acha_ID(Lista lista, int ID);

/*Le a linha do arquivo Qry sinalizada com "mv", ao fazer isso busca na lista
a forma indicada por "ID" ao encontrar a forma SOMA ao x e ao y de sua ancora
os valores X e Y*/
void LinhaMove(FILE* txt,Lista lista,int ID,double X,double Y);

/*Le a linha do arquivo Qry sinalizada com "g", ao fazer isso busca na lista
a forma indicada por "ID" ao encontrar a forma SOMA a sua rotaçao atual o valor "rot" */
void LinhaRotaciona(FILE* txt, Lista lista,int ID,double rot);

/*Le a linha do arquivo Qry sinalizada com "tf",ao fazer isso roda toda a lista "lista" analisando
com a funcao reconhece_area se a forma da lista esta ou nao na area da foto do balao*/
void LinhaTiraFoto(FILE* txt, Lista Baloes,Lista lista,Lista decoracoes,int ID,int camera);

/*Faz os calculos procurando o valor relativo do y da figura em relacao a borda da foto
em que ele esta, os calculos sao feitos em relaçao a ancora do "retangulo borda", retornando 
o y relativo(dy)*/
double dy_Forma(Retangulo Borda, Forma analise);

/*Faz os calculos procurando o valor relativo do x da figura em relacao a borda da foto
em que ele esta, os calculos sao feitos em relaçao a ancora do "retangulo borda", retornando 
o x relativo(dx)*/
double dx_Forma(Retangulo Borda, Forma analise);

/*Le a linha do arquivo Qry sinalizada com "df", ao fazer isso,escreve as fotos da camera
numero "camera", balao de ID escolhido as fotos sao posicionasuma ao lado da outra com uma
distancia definida pela distancia da maior figura à direita,todas as fotos sao "reveladas"
 no mesmo arquivo de nome info-nome.svg*/
void ReportaFotos(FILE* txt, Lista Baloes,int ID, char* nome, int camera,char* info);

/*Le a linha do arquivo Qry sinalizada com "b?", ao fazer isso reporta todos os baloes
 indicando seu ID,suas informaçoes base, e quantasfotos tem em cada um notificando
  exatamente a camera em que elas fotam tiradas*/
void Report_Baloes(FILE* txt,Lista Baloes);

/*Le a linha do arquivo Qry sinalizada com "c?", ao fazer issoreporta todos os cacas
 indicando seu ID,suas informaçoes base, quantos disparos foram efetuados por ele,e
  o ID das figuras que ele atingiu*/
void Report_Cacas(FILE* txt, Lista Cacas);

/*Le a linha do arquivo Qry sinalizada com "ff", ao fazer isso define o foco da foto(profundidade,
altura,raio) da camera atual do balao sinalizado por "ID" */
void FocoFoto(Lista Baloes, int ID, double raio, double profundidade, double altura);

/*Reposiciona a coordenada de todos os elementos de uma foto levando como base 
a ancora da borda da foto*/
double distanciaEntreFotos(Lista foto);

/*Verifica por meio de calculos se a forma "analisa" esta dentro do disparo do caça, que tem
dimensoes raio,cy,cx, caso a forma esteja dentro do circulo do disparo, retorna verdadeiro*/
bool areaDisparo(double cx, double cy, double raio,Forma analisa);

/*Funcao para checar se linha foi destruida pelo disparo, ela sera usada para checar se o retangulo
foi atingido tambem, caso seja atingida pelo disparo, retorna verdadeiro*/
bool Linha_Destruida(double x1, double y1, double x2, double y2, double raio, double cx, double cy);

/*Roda toda a lista "fotos" copiando todos seus elementos e os inserindo na lista "Banco_Dados",
a cor da borda e do preenchimento das formas sao invertidas no processo, e seu ID é resetado para j,
conforme a lista é clonada deve se somar +1(*aumento) ao j para nao repetir IDs*/
void clonaFotos(Lista Banco_Dados,Lista fotos, double x, int j,int* aumento);

/**Le a linha do arquivo Qry sinalizada com "d", ao fazer isso Caca sinalizado por "ID" faz um disparo
  de dimensoes capac(define raio do disparo), dist(distancia do disparo em relacao ao caça), j é o valor
  que as formas clonadas(caso acerte balao com fotos) receberao, dx é o valor que deve-se somar no x da 
  ancora das fotos clonadas.É reportado no txt: informacoes das figuras atingidas*/
void DisparoCaca(FILE* txt,FILE* banco,Lista Baloes,Lista Cacas, Lista lista,Lista decoracoes,int ID,char* capac,double dist,int j,double dx);

/*Navega pela lista buscando a forma sinalizada por "ID", ao encontrar remove esta forma da lista*/
void eliminaLista(int ID,Lista lista);

/*Roda toda a lista e da free personalizado em todas suas formas, ao final do processo ele da killlst*/
void Executa_ListaFormas(Lista executada);

/*Ajeita nome que terá as fotos, recebe é o nome final, patho é o path de saida e sfx é o sufixo adicionado
ficando na forma pathorecebesfx.svg*/
char* Nome_arq_svg(char recebe[], char* patho,char* sfx);

#endif