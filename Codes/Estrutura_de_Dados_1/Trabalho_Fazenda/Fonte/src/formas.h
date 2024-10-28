#ifndef FORMAS_H
#define FORMAS_H

/*Essa header é feita para facilitar o acesso a varias formas diferentes(Circulos, retangulos...)por funçoes mais gerais
que primeiro buscam o tipo da forma, e depois retornam a função desejada, essa header tambem contem as funçoes
para ter acesso a Horta(informação guardada pelos nodes da arvore radial)*/

#include <stdio.h>


typedef void* Forma;

//'T' = texto, 'C' = circulo, 'R' = retangulo, 'L' = linha
char get_type(void* point);
// move a forma para (x+dx:y+dy)
void mvForma(Forma forma, double dx, double dy);
// retorna o id da forma generalizada
int get_ID(void* forma);
// retorna a cor do preenchimento da forma generalizada
char* get_corp(Forma forma);
// retorna a cor da borda da forma generalizada
char* get_corb(Forma forma);
// retorna o x da forma generalizada
double get_x(Forma forma);
// retorna o y da forma generalizada
double get_y(Forma forma);
//seta o x da forma generalizada
void set_x(Forma forma, double x);
//seta cor da borda da forma generalizada
void set_corb(Forma forma, char* corb);
//seta cor do preenchimento da forma generalizada
void set_corp(Forma forma, char* corp);
//seta o ID da forma generalizada
void set_ID(Forma forma, int ID);
//seta coordenada y da ancora da forma
void set_y(Forma forma, double y);
//Elimina forma
void killForma(void* forma);
/*reporta os dados da figura "guarda_forma"*/
void reporta_figura(void* txt,void* guarda_forma);

typedef void* Horta;
//Inicia uma nova hortalica setando seu peso, tipo e seu geo
Horta criaHortalica(Forma figura);
//seta a nova posição da hortalica
void set_HortX(Horta hortalica, double value);
// seta a nova posição da hortalica
void set_HortY(Horta hortalica,double value);
//da fre personalizado na hortalica
void killHorta(Horta hortalica);
//retorna o y da hortalica
double get_HortY(Horta hortalica);
//retorna o x da hortalica
double get_HortX(Horta hortalica);
//seta a % de praga da hortalica
void set_HortPraga(Horta hortalica,double newPrag);
//retorna a % de praga da hortalica
double get_HortPraga(Horta hortalica);
//Retorna a % de adubo da hortalica
double get_HortAdubo(Horta hortalica);
//seta a % de adubo da hortalica
void set_HortAdubo(Horta hortalica,double newPrag);
/*S = MORANGO(strawberrie)
O = CEBOLA(onion)
C = CENOURA(carrot)
P = ABOBORA (pumpkim)
R = REPOlLHO(repolho)
G = MATO(grass)*/
char get_HortType(Horta hortalica);
//retorna o geo da hortalica
Forma get_HortaFigura(Horta hortalica);
//seta a distancia da hortalica em relaçao ao centro relativo da arvore
void set_HortaD(Horta hortalica, double Dist);
//retorna a distancia da hortalica em relaçao ao centro relativo da arvore
double get_HortaD(Horta hortalica);
//retorna o peso da hortalica 
double get_HortaPeso(Horta hortalica);

double get_HortaP_Atual(Horta hortalica);

void set_HortaP_Atual(Horta hortalica,double newP_Atual);

//retorna true caso a forma analisada seja uma colheitadeira, false caso contrario
bool IsColheitadeira(Forma forma);

#endif