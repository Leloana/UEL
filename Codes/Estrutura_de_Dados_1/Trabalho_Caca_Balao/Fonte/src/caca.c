#include "caca.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "FuncLeituras.h"

typedef struct caca{

    char type;
    int ID;
    char state;
    int disparos;
    Lista ID_figuras;
    Texto forma;

}_caca;

void killCaca(Caca S){
    _caca* aux = (_caca*) S;
    Executa_ListaFormas(aux->ID_figuras);
    
    free(aux);
}

Caca set_caca(Texto texto){
    _caca* aux = malloc(sizeof(_caca));
    aux->type = 'S';
    aux->disparos = 0;
    int ID = get_text_ID(texto);
    aux->ID = ID;
    aux->forma = texto;
    aux->ID_figuras = createLst(-1);
    aux->state = 'a';

    return aux;
}

int get_caca_Disparos(Caca S){
    _caca* aux = (_caca*) S;
    return aux->disparos;
}

void set_caca_Disparos(Caca S, int Dis){
    _caca* aux = (_caca*) S;
    aux->disparos = Dis;
}

char get_caca_type(Caca S){
    _caca* aux = (_caca*) S;
    return aux->type;
}

Texto get_caca_Forma(Caca S){
    _caca* aux = (_caca*) S;
    return aux->forma;
}

int get_caca_ID(Caca S){
    _caca* aux = (_caca*) S;
    return aux->ID;
}

void addIDs(Caca S, Forma figura){
    _caca* aux = (_caca*) S;
    insertLst(aux->ID_figuras,figura);
}

bool iscaca(Forma forma){
    if(get_type(forma) == 'T' && strcmp(get_text_texto(forma),"|-T-|") == 0)return true;
    else return false;
}

Lista ReturnID(Caca S){
    _caca* aux = (_caca*)S;
    return aux->ID_figuras;
}

void set_caca_ID(Caca S, int ID){
    _caca* aux = (_caca*)S;
    aux->ID = ID;
}

void set_caca_state(Caca S, char state){
    _caca* aux = (_caca*) S;
    aux->forma = criaTexto(0,0,0,"none","none","m","|-T-|");
    aux->state = state;
}

char get_caca_state(Caca S){
    _caca* aux = (_caca*) S;
    return aux->state;
}