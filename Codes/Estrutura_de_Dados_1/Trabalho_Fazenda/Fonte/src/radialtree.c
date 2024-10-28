#include "radialtree.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "formas.h"
#include "aplicacoes.h"
#include <string.h>
#include "arqsvg.h"



typedef struct node{
    
    Info data;
    Node* galhos;
    bool removido;
    double x;
    double y;

}_node;

typedef struct tree{

    _node* raiz;
    int setores;
    double degradacao;
    int celulas;
    int degeneradas;

}_rTree;

RadialTree newRadialTree(int numSetores, double fd){
    _rTree* aux = calloc(1, sizeof(_rTree));

    aux->setores = numSetores;
    aux->degradacao = fd;
    aux->celulas = 0;
    aux->degeneradas = 0;
    aux->raiz = NULL;

    return aux;
}

Node insertRadialT(RadialTree t, double x, double y, Info i){
    _rTree* Tree = (_rTree*)t;
    _node* raiz = Tree->raiz;
    Tree->celulas ++;
    
    if(raiz == NULL){//Checo se arvore possui algum node
        _node* aux = calloc(1,sizeof(_node));//Crio novo node
        aux->x = x;
        aux->y = y;
        aux->data = i;
        aux->removido = false;
        aux->galhos = calloc(Tree->setores,sizeof(Node));//seto todos os setores do node para nulo
        for (int i=0; i<Tree->setores; i++) aux->galhos[i] = NULL;
        Tree->raiz = aux;//faço a arvore receber seu primeiro node
        return aux;
    }
    else {//Caso arvore ja tenha seu primeiro node é preciso checar em qual setor deste node o proximo se encontra
        int setor = Setor(Tree->setores,raiz->x,raiz->y,x,y);//checa qual setor esta

        _rTree aux;//cria arvore auxiliar(serve para funcionar a recursão)
        aux.setores = Tree->setores;
        aux.raiz = raiz->galhos[setor];//raiz da arvore auxiliar recebe o node que queremos colocar o novo node
        raiz->galhos[setor] = insertRadialT(&aux,x,y,i);
        return raiz;
    }
}

Node getNodeRadialT(RadialTree t, double x, double y, double epsilon){
    _rTree* Tree = (_rTree*)t;
    _node* aux = Tree->raiz;

    if (aux == NULL){

    printf("\nERRO: Node %lf %lf nao encontrado!!\n", x,y);
    return NULL;
    }

    else if(fabs(aux->x - x) < epsilon && fabs(aux->y - y) < epsilon) return aux;
    else{
        int setor = Setor(Tree->setores, aux->x, aux->y, x, y);

        _rTree radial_aux;
        radial_aux.setores = Tree->setores;
        radial_aux.degradacao = Tree->degradacao;
        radial_aux.raiz = aux->galhos[setor];

        return getNodeRadialT(&radial_aux, x, y, epsilon);
    }
}

void removeNoRadialT(RadialTree t, Node n){
    _rTree* Tree = (_rTree*)t;

    if(n != NULL){
    _node* aux = (_node*) n;
    aux->removido = true;

    Tree->degeneradas++;
        if((double)Tree->degeneradas/Tree->celulas >= (double)Tree->degradacao){
            Tree = (_rTree*)ReorganizaRadialT(Tree);
        }

    }
    else printf("REMOCAO INTERROMPIDA!!!");
}

RadialTree ReorganizaRadialT(RadialTree t){
    _rTree* Tree = (_rTree*)t;
   
    double centro[2];
    CentroRadialTree(Tree, centro); //Definindo centro ficticio do retangulo
    Lista Hortas = createLst(-1);
    visitaProfundidadeRadialT(Tree,ListaDeHort,Hortas);
    int num = lengthLst(Hortas);

    Iterador K = createIterator(Hortas,false); //Definindo Atualizando a distancia entre os nos e esse ponto

    
    Horta VetorArvore[num]; //Vetor do conteudo da arvore
    int L = 0;
    while(!isIteratorEmpty(Hortas,K)){
        Horta hort = getIteratorNext(Hortas,K);
        AtualizaDistancia(hort,get_x(get_HortaFigura(hort)),get_y(get_HortaFigura(hort)),centro);
        VetorArvore[L] = hort;
        L++;
    }
    qsort(VetorArvore, num, sizeof(Horta), OrdenaDistancia); //Ordenando o vetor com base na funcao OrdenaDistancia

    RadialTree ArvoreAux = newRadialTree(Tree->setores,Tree->degradacao); //Criando arvore auxiliar
    for (int i=0; i < num; i++) {
        insertRadialT(ArvoreAux,get_HortX(VetorArvore[i]), get_HortY(VetorArvore[i]), VetorArvore[i]); //Preenchendo arvore auxiliar
    }
    return ArvoreAux;
}

Info getInfoRadialT(Node n){
    if(n == NULL)return NULL;
    _node* aux = (_node*) n;
    return aux->data;
}

bool getNodesDentroRegiaoRadialT(RadialTree t, double x1, double y1, double x2, double y2, Lista L){
    _rTree* Tree = (_rTree*)t;
    _node* raiz = Tree->raiz;
    
//usando visita em profundidade
    if(raiz != NULL){
        if(DentroRegiaoRet(raiz->x,raiz->y,x1,y1,x2,y2) && !raiz->removido){
            insertLst(L,raiz);
        }
        for(int i=0;i<Tree->setores;i++){
        //SE O RETANGULO ESTIVER NESTE SETOR CONTINUE SE NAO VOLTA O LOOP
            // if(ChecaRetSetor(raiz->x,raiz->y,x1,y1,x2,y2,Tree->setores,i)){

                _rTree aux;
                aux.raiz = raiz->galhos[i];
                aux.setores = Tree->setores;
                getNodesDentroRegiaoRadialT(&aux,x1,y1,x2,y2,L);
            // }
        }
    }
    if(!isEmptyLst(L))return true;
    else return false;
}

bool getInfosDentroRegiaoRadialT(RadialTree t, double x1, double y1, double x2, double y2,FdentroDeRegiao f, Lista L){
    _rTree* Tree = (_rTree*)t;
    _node* raiz = Tree->raiz;
    
//usando visita em profundidade
    if(raiz != NULL){
        if(!raiz->removido && f(raiz->data,x1,x2,y1,y2)){
            // printf("Objeto encontrado no Setor!! %lf %lf \n", raiz->x,raiz->y);
            insertLst(L,raiz->data);
        }
        printf(" \n ");
        for(int i=0;i<Tree->setores ;i++){
        //SE O RETANGULO ESTIVER NESTE SETOR CONTINUE SE NAO VOLTA O LOOP
        if(ChecaRetSetor(raiz->x,raiz->y,x1,y1,x2,y2,Tree->setores,i)){
            printf("\n ");

            _rTree aux;
            aux.raiz = raiz->galhos[i];
            aux.setores = Tree->setores;
            getInfosDentroRegiaoRadialT(&aux,x1,y1,x2,y2,f,L);
        }
        }
    }
    if(!isEmptyLst(L))return true;
    else return false;
}

bool getInfosAtingidoPontoRadialT(RadialTree t, double x, double y, FpontoInternoAInfo f, Lista L){
     _rTree* Tree = (_rTree*)t;
    _node* raiz = Tree->raiz;

   if(raiz != NULL){
        if(f(raiz->data,x,y)  && !raiz->removido){
            insertLst(L,raiz->data);
            return true;
        }
         for(int i=0;i<Tree->setores;i++){

        _rTree aux;
        aux.raiz = raiz->galhos[i];
        aux.setores = Tree->setores;
        getInfosAtingidoPontoRadialT(&aux, x, y, f,L);
        }
   }
   if(!isEmptyLst(L))return true;
    else return false;
    
}

void visitaProfundidadeRadialT(RadialTree t, FvisitaNo f, void *aux){
     _rTree* Tree = (_rTree*)t;
    _node* raiz = Tree->raiz;

    
    if(raiz!=NULL){
        
    if(!raiz->removido)f(raiz->data,get_x(get_HortaFigura(raiz->data)),get_y(get_HortaFigura(raiz->data)),aux);

    for(int i=0;i<Tree->setores;i++){
        if(raiz->galhos[i]!=NULL){
        _rTree Taux;
        Taux.raiz = raiz->galhos[i];
        Taux.setores = Tree->setores;
        visitaProfundidadeRadialT(&Taux,f,aux);
        }
    }
    }

}

void visitaLarguraRadialT(RadialTree t, FvisitaNo f, void *aux) {
    _rTree* tree = (_rTree*)t;

    if(tree->raiz!= NULL){
    _node* fila[100]; 
    int comeco = 0;
    int fim = 0;

    fila[fim++] = tree->raiz;

    while (comeco < fim) {
        int tamanhoAtual = fim - comeco;
        
        for (int i = 0; i < tamanhoAtual; i++) {
            _node* noAtual = fila[comeco++];
            if (!(noAtual->removido)) f(noAtual->data, noAtual->x, noAtual->y, aux); //Invoca a funcao f em todos os nos da arvore, exceto nos que foram marcados como removidos
 
            for (int j = 0; j < tree->setores; j++) {
                if (noAtual->galhos[j] != NULL)
                    fila[fim++] = noAtual->galhos[j];
            }
        }
    }
    }
}

Node procuraNoRadialT(RadialTree t, FsearchNo f, void *aux){
    _rTree* Tree = (_rTree*)t;
    _node* raiz = Tree->raiz;

    if (raiz == NULL){
    return NULL;
    }

    else if(f(raiz->data,raiz->x,raiz->y,aux)) return raiz;
    else{
    for(int i=0;i<Tree->setores;i++){
        if(raiz->galhos[i]!=NULL){
            _rTree Taux;
            Taux.raiz = raiz->galhos[i];
            Taux.setores = Tree->setores;
            return procuraNoRadialT(&Taux,f,aux);
            }
        }
    }
}

bool printDotRadialTree(RadialTree t, char *fn) {

    _rTree* arvore = (_rTree*)t;
    _node* node = arvore->raiz;
    if (node == NULL) return false;

    FILE* dot = fopen(fn, "a+");
    if (dot == NULL) return false;
    for (int i=0; i<arvore->setores; i++) {
        char PaiRemovido[5] = "", FilhoRemovido[5] = "";
        if (node->galhos[i] != NULL) {
            _node* galhoaux = (_node*)node->galhos[i];

            if (node->removido) strncpy(PaiRemovido, "*", 5);
            if (galhoaux->removido) strncpy(FilhoRemovido, "*", 5); 
            fprintf (dot, "\t\"%d_%d %s\" -> \"%d_%d %s\";\n", (int)get_HortX(node->data), (int)get_HortY(node->data), PaiRemovido,
                        (int)get_HortX(galhoaux->data), (int)get_HortY(galhoaux->data), FilhoRemovido);
            if (node->removido) fprintf (dot, "\t\"%d_%d %s\" [style=filled, fillcolor=red, fontcolor=black];\n", 
                                    (int)get_HortX(node->data), (int)get_HortY(node->data), PaiRemovido);
        }
    }
    for (int i=0; i<arvore->setores; i++) {
        if (node->galhos[i] != NULL) {
            _rTree radial_aux;
            radial_aux.setores = arvore->setores;
            radial_aux.raiz = node->galhos[i];

            printDotRadialTree(&radial_aux, fn);
        }
    }
    fclose(dot);
    return true;
}



void killRadialTree(RadialTree t){
    _rTree* Tree = (_rTree*)t;
    _node* raiz = Tree->raiz;

    
    if (raiz == NULL) {
        return;
    }

    for(int i=0;i<Tree->setores;i++){
        if(raiz->galhos[i]!=NULL){
        _rTree Taux;
            
        Taux.raiz = raiz->galhos[i];
        Taux.setores = Tree->setores;
        killRadialTree(&Taux);
        }
    }
    if(raiz->data != NULL)(raiz->data);
    free(raiz);
}