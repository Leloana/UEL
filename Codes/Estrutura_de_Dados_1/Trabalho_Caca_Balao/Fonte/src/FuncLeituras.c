#include "FuncLeituras.h"
#include "caca.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define pi 3.14159265359

void LinhaMove(FILE* txt,Lista lista,int ID,double X,double Y){
    Forma guarda_forma = acha_ID(lista, ID);//procura figura do id inserido
    if(guarda_forma == NULL)return;
    fprintf(txt,"\n[*] mv %d %lf %lf", ID,X,Y);//reporta o comando ao relatorio
    reporta_figura(txt,guarda_forma);
    fprintf(txt,"\nCOORDENADA INICIAL = (%lf,%lf)", get_x(guarda_forma), get_y(guarda_forma));
    mvForma(guarda_forma, X,Y);//forma soma as coordenadas antigas às inseridas
    fprintf(txt,"\nCOORDENADA FINAL = (%lf,%lf)\n\n", get_x(guarda_forma), get_y(guarda_forma));
}

void LinhaRotaciona(FILE* txt, Lista lista,int ID,double rot){
    Forma guarda_forma = acha_ID(lista,ID);
    if(guarda_forma == NULL)return;
    fprintf(txt,"\n[*] g %d %lf", ID , rot);
    reporta_figura(txt,guarda_forma);
    if(get_type(guarda_forma) == 'T')set_text_rot(guarda_forma,rot);
        else if(get_type(guarda_forma) == 'R')set_ret_rot(guarda_forma,rot);
        else if(get_type(guarda_forma) == 'L')set_lin_rot(guarda_forma,rot);
        else if(get_type(guarda_forma) == 'C')set_circ_rot(guarda_forma,rot);
        fprintf(txt,"\n\n");
}

void FocoFoto(Lista Baloes, int ID, double raio, double profundidade, double altura){
    if(isEmptyLst(Baloes))return;//caso nao tenha baloes na lista funcao nao ocorre
    else{
    Balao guarda_forma = acha_ID(Baloes,ID);//seta as informaçoes da camera do balao
    if(guarda_forma == NULL)return;
    set_balao_raio(guarda_forma,raio);
    set_balao_prof(guarda_forma,profundidade);
    set_balao_alt(guarda_forma,altura);
    }
}

void LinhaTiraFoto(FILE* txt, Lista Baloes,Lista lista,Lista decoracoes,int ID,int camera){
    if(isEmptyLst(Baloes))return;
    else{
    Balao guarda_forma = acha_ID(Baloes,ID);//acha o balao que vai fotografar
    if(guarda_forma == NULL)return;
    Lista foto = createLst(-1);//cria a lista que sera a foto
    double ancoraX = (get_text_x(get_balao_forma(guarda_forma)) - get_balao_raio(guarda_forma));//acha a ancora da foto
    double ancoraY = (get_text_y(get_balao_forma(guarda_forma))+ get_balao_prof(guarda_forma));
    Retangulo Borda = criaRect(-10,ancoraX,ancoraY, (2*get_balao_raio(guarda_forma)),get_balao_alt(guarda_forma),"red","none");
    insertLst(foto,Borda);//coloca retangulo que representa a area da foto na lista foto
    Iterador S = createIterator(lista,false);//Iterador para checar banco de dados
    fprintf(txt,"\n[*] tf %d %d", ID, camera);
    reporta_figura(txt, get_balao_forma(guarda_forma));

    fprintf(txt,"\nraio = %lf profundidade = %lf altura = %lf\n",get_balao_raio(guarda_forma),get_balao_prof(guarda_forma),get_balao_alt(guarda_forma));
    while(!isIteratorEmpty(lista,S)){
        Forma figura = getIteratorNext(lista,S);
            if(reconhece_area(guarda_forma,figura)){/*procura figuras do banco de dados que estao na foto,
                                                    é feita uma copia das figuras fotografadas e inseridas na lista foto*/
                fprintf(txt,"ID: %d x relativo: %lf y relativo: %lf \n", get_ID(figura), dx_Forma(Borda,figura), dy_Forma(Borda,figura));
                if(get_type(figura)== 'L'){
                Linha L = criaLinha(get_ID(figura),get_lin_x1(figura),get_lin_y1(figura),get_lin_x2(figura),get_lin_y2(figura),get_lin_corp(figura));
                insertLst(foto,(Linha)L);
                 }
                if(get_type(figura)== 'C'){
                 Circulo C = criaCirc(get_ID(figura),get_circ_cx(figura),get_circ_cy(figura),get_circ_r(figura),get_circ_corb(figura),get_circ_corp(figura));
                insertLst(foto,(Circulo)C);
                }
                if(get_type(figura)== 'T'){
                Texto T = criaTexto(get_ID(figura),get_text_x(figura),get_text_y(figura),get_text_corb(figura),get_text_corp(figura),get_text_charAnc(figura),get_text_texto(figura));
                    insertLst(foto,(Texto)T);
                }
                if(get_type(figura)== 'R'){
                    Retangulo R = criaRect(get_ID(figura),get_ret_x(figura),get_ret_y(figura),get_ret_larg(figura),get_ret_alt(figura),get_ret_corb(figura),get_ret_corp(figura));
                    insertLst(foto,(Retangulo)R);
                }       
            }
    }
    //lente é usada na lista decoraçoes para demarcar onde foram tiradas as fotos
    Retangulo lente = criaRect(-1, ancoraX,ancoraY, (2*get_balao_raio(guarda_forma)),get_balao_alt(guarda_forma),"red","none");
    set_ret_dasharray(lente,5);//borda pontilhada
    insertLst(decoracoes,lente);//lente é inserida na lista decoraçoes
    insert_foto(guarda_forma,camera,foto);//a foto é inserida na lista do balao
    fprintf(txt,"\n\n");
    killIterator(lista,S);
    }
}

double dx_Forma(Retangulo Borda, Forma analise){
    double x1 = get_ret_x(Borda);
    double dx = 0.0;
    //o dx retornado é a x posicao da ancora da forma analise em relacao a ancora do retanguo borda
    if(get_type(analise) == 'T')dx = get_text_x(analise)-x1;
    else if(get_type(analise) == 'C')dx = get_circ_cx(analise)-x1;
    else if(get_type(analise) == 'R')dx = get_ret_x(analise)-x1;
    else if(get_type(analise) == 'L')dx = get_lin_x1(analise)-x1;

    return dx;
}

double dy_Forma(Retangulo Borda, Forma analise){
    double y1 = get_ret_y(Borda);
    double dy = 0.0;
   //o dy retornado é a y posicao da ancora da forma analise em relacao a ancora do retanguo borda
    if(get_type(analise) == 'T')dy = get_text_y(analise)-y1;
    else if(get_type(analise) == 'C')dy = get_circ_cy(analise)-y1;
    else if(get_type(analise) == 'R')dy = get_ret_y(analise)-y1;
    else if(get_type(analise) == 'L')dy = get_lin_y1(analise)-y1;

    return dy;
}

void ReportaFotos(FILE* txt, Lista Baloes,int ID, char* nome, int camera,char* info){
    if(!isEmptyLst(Baloes)){
    Balao guarda_forma = acha_ID(Baloes,ID);//acha o balao que tera as fotos reportadas
    if(guarda_forma == NULL)return;
    if(guarda_forma){
    int foto_atual = 0;/*como todas as fotos da camera serao reveladas devemos guardar o numero de
                         fotos ja reveladas para conseguir posicionar as fotos uma ao lado da outra*/
    char nomesvg[100];
    Nome_arq_svg(nomesvg,info,nome);
    ArqSvg Arq_foto = abreEscritaSvg(nomesvg);//abre arquivo em que as fotos serao "reveladas"
    fprintf(txt,"\n[*] df %d %d %s\n", ID, camera, nome);//reporta açao
    fprintf(txt,"Balao de ID: %d \nCamera %d \n",get_balao_ID(guarda_forma),camera);
    double posic_foto = 0;
    while(!isQueueEmpty(get_Camera(guarda_forma,camera))){//enquanto nao esvaziar a camera
        Lista Foto = get_foto(guarda_forma,camera);//lista foto recebe a foto da fila camera
        Iterador K = createIterator(Foto,false);
        Posic P = getFirstLst(Foto);//primeiro elemento de toda foto é o retangulo de borda da foto
        double x = get_ret_x(getLst(Foto,P));//consegue a ancora da foto para realizar calculos de posicao
        double y = get_ret_y(getLst(Foto,P));
        double ponto_x = 15.0 + foto_atual * (15.0 + get_ret_larg(getLst(Foto, P))) + posic_foto;
        posic_foto += distanciaEntreFotos(Foto) - (get_ret_larg(getLst(Foto,P))+get_ret_x(getLst(Foto,P)));
        double ponto_y = 15.0;//calculos de posicao para fotos ficarem bem posicionadas
        double dx = (-1) * (x - ponto_x);
        double dy = (-1) * (y - ponto_y);
        while(!isIteratorEmpty(Foto,K)){
            Forma figura = getIteratorNext(Foto,K);
            if (get_type(figura) == 'L') {//ajeita posicoes das formas(linha é excessao pois deve transladar)
                set_lin_x1(figura, get_lin_x1(figura) + dx);
                set_lin_x2(figura, get_lin_x2(figura) + dx);
                set_lin_y1(figura, get_lin_y1(figura) + dy);
                set_lin_y2(figura, get_lin_y2(figura) + dy);
            }
            else{
                set_x(figura,get_x(figura)+dx);
                set_y(figura,get_y(figura)+dy);
            }
            escreveGeralSvg(Arq_foto,figura);//escreve a figura ja posicionada no .svg
        }
        fprintf(txt,"pontuacao da foto %d = %lf\n",foto_atual,avalia(Foto));
        foto_atual++;
        killIterator(Foto,K);
        Executa_ListaFormas(Foto);//free personalizado na lista
    }
    fprintf(txt,"\n");
    fechaSvg(Arq_foto);
    }
    }
}

double distanciaEntreFotos(Lista foto){
    double maior_Forma = -1.00;
    Iterador K = createIterator(foto, false);
    while (!isIteratorEmpty(foto, K)){/*procura qual é a maior figura a direita da foto
                                        e modifica o x da ancora da foto baseado nisso*/
        Forma figura = getIteratorNext(foto, K);
        if (get_type(figura) == 'C'){
            if (get_circ_cx(figura) + get_circ_r(figura) > maior_Forma)maior_Forma = get_circ_cx(figura) + get_circ_r(figura);
        }
        else if (get_type(figura) == 'L'){
            if (get_lin_x2(figura) > maior_Forma)maior_Forma = get_lin_x2(figura);
        }
        else if (get_type(figura) == 'R'){
            if (get_ret_x(figura) + get_ret_larg(figura) > maior_Forma)maior_Forma = get_ret_x(figura) + get_ret_larg(figura);
        }
        else if (get_type(figura) == 'T'){
            if (get_text_x(figura) > maior_Forma)maior_Forma = get_text_x(figura);
        }
    }
    return maior_Forma;
}

void Report_Baloes(FILE* txt,Lista Baloes){
    Iterador D = createIterator(Baloes,false);
    fprintf(txt,"\n[*] b?");
    if(!isEmptyLst(Baloes)){
    while(!isIteratorEmpty(Baloes,D)){//Roda a lista de baloes
        Balao B = getIteratorNext(Baloes,D);
        if(get_balao_state(B)=='d');
        else{
        Texto figura = get_balao_forma(B);
        reporta_figura(txt,figura);//reporta o texto do balao
       for(int i=0;i<10;i++){
            Fila camera =  get_Camera(B,i);
            fprintf(txt,"\nCamera %d tem %d fotos",i,tamQueue(camera));//reporta a quantidade de fotos da camera i
        }
        fprintf(txt,"\n");
        }
    }
    }
    fprintf(txt,"\n\n");
    killIterator(Baloes,D);
}

void Report_Cacas(FILE* txt, Lista Cacas){
    Iterador D = createIterator(Cacas,false);
    fprintf(txt,"\n[*] c?");
    if(!isEmptyLst(Cacas)){
    while(!isIteratorEmpty(Cacas,D)){//roda lista de caças
        Caca S = getIteratorNext(Cacas,D);
        if(get_caca_state(S) != 'd'){
        Texto figura = get_caca_Forma(S);
        reporta_figura(txt,figura);
        fprintf(txt,"\nCaca deu %d disparos\nIDs Atingidos:", get_caca_Disparos(S));//roda lista de ids e revela eles
        if(isEmptyLst(ReturnID(S)))fprintf(txt,"\nCaca nao destruiu nada\n");
        else{ 
        Lista ID_int = ReturnID(S);
        Iterador Roda = createIterator(ID_int,false);
        while(!isIteratorEmpty(ID_int,Roda)){
            fprintf(txt,"\nID:%d", get_ID(getIteratorNext(ID_int,Roda)));
        }
        killIterator(ID_int,Roda);
        fprintf(txt,"\n");
        }
        }
    }
    }
    fprintf(txt,"\n\n");
    killIterator(Cacas,D);
}

void DisparoCaca(FILE* txt,FILE* banco,Lista Baloes,Lista Cacas, Lista lista,Lista decoracoes,int ID,char* capac,double dist,int j,double dx){
    Caca Destroyer = acha_ID(Cacas, ID);
    if(Destroyer == NULL)return;
    Texto guarda_forma = get_caca_Forma(Destroyer);//guarda forma do caça pois sera usado em contas
    double raio = 0;
    if(strcmp(capac,"A")==0)raio = 10.00;//ajeita o tamanho do tiro
    else if(strcmp(capac,"B")==0)raio = 15.00;
    else if(strcmp(capac,"C")==0)raio = 30.00;
    double cx = (sin(-get_text_rot(guarda_forma)* pi/180 )* dist) + get_text_x(guarda_forma);//calcula a posicao do tiro do caca
    double cy = (cos(-get_text_rot(guarda_forma)* pi/180)* dist) + get_text_y(guarda_forma);
    escreveCirculoSvg(banco,criaCirc(-100,cx,cy,raio,"black","red"));
    fprintf(txt,"\n[*] d %d %s %lf %d %lf\nFiguras atingidas",ID,capac,dist,j,dx);
    Iterador K = createIterator(lista,false);
    Lista Clonagens = createLst(-1);
    while(!isIteratorEmpty(lista,K)){
    Forma analisa = getIteratorNext(lista,K);
        if(areaDisparo(cx,cy,raio,analisa)){
            addIDs(Destroyer,analisa);
            escreveTextoSvg(banco,criaTexto(-1,get_x(analisa),get_y(analisa),"#FF0000","#FF0000","m","x"));//COLOCA X ONDE DESTRUIU
            reporta_figura(txt,analisa);
            if(isBaloon(analisa)){
                Balao Atingido = acha_ID(Baloes,get_ID(analisa));
                for(int cam = 0; cam < 10; cam++){
                    Fila Camera_atual = get_Camera(Atingido,cam);//passa pelas 10 cameras do balao
                    while(!isQueueEmpty(Camera_atual)){
                        Lista Pictures = get_foto(Atingido,cam);//pega as fotos ate a camera esvaziar
                        Iterador W = createIterator(Pictures,false);
                        while(!isIteratorEmpty(Pictures,W))insertLst(Clonagens,getIteratorNext(Pictures,W));
                    }
                }
                set_balao_state(Atingido, 'd');
            }
            else if(iscaca(analisa)){
                Caca Destruido = acha_ID(Cacas,get_ID(analisa));
                set_caca_state(Destruido, 'd');
            }
            eliminaLista(get_ID(analisa),lista);
        }
    }
    int aumento = 0;
    if(!isEmptyLst(Clonagens))clonaFotos(lista,Clonagens,dx,j,&aumento);
    Executa_ListaFormas(Clonagens);
    fprintf(txt,"\n\n");
    set_caca_Disparos(Destroyer,get_caca_Disparos(Destroyer)+1);
    killIterator(lista,K);
}

void eliminaLista(int ID,Lista lista){
    Posic P = getFirstLst(lista);
    void* nova = getLst(lista,P);
    int elimina = get_ID(nova);

    while(elimina != ID){
        P = getNextLst(lista,P);//recebo proxima posicao
        nova = getLst(lista,P);//guardo elemento da lista
        elimina = get_ID(nova);//elimina recebe novo ID
    }
    removeLst(lista,P);
}

void clonaFotos(Lista Banco_Dados,Lista fotos, double x, int j,int* aumento){
    Iterador K = createIterator(fotos,false);
    while(!isIteratorEmpty(fotos,K)){
        Forma figura = getIteratorNext(fotos,K);
        if(get_ID(figura)>= 0){
        if(get_type(figura)== 'L'){
            Linha L = criaLinha(j+(*aumento),get_lin_x1(figura)+x,get_lin_y1(figura),get_lin_x2(figura)+x,get_lin_y2(figura),get_lin_corp(figura));
            insertLst(Banco_Dados,(Linha)L);
        }
        else if(get_type(figura)== 'C'){
            Circulo C = criaCirc(j+(*aumento),get_circ_cx(figura)+x,get_circ_cy(figura),get_circ_r(figura),get_circ_corp(figura),get_circ_corb(figura));
            insertLst(Banco_Dados,(Circulo)C);
        }
        else if(get_type(figura)== 'T'){
            Texto T = criaTexto(j+(*aumento),get_text_x(figura)+x,get_text_y(figura),get_text_corp(figura),get_text_corb(figura),get_text_charAnc(figura),get_text_texto(figura));
            insertLst(Banco_Dados,(Texto)T);
        }
        else if(get_type(figura)== 'R'){
            Retangulo R = criaRect(j+(*aumento),get_ret_x(figura)+x,get_ret_y(figura),get_ret_larg(figura),get_ret_alt(figura),get_ret_corp(figura),get_ret_corb(figura));
            insertLst(Banco_Dados,(Retangulo)R);
        }
        (*aumento)++;
        }
    }
    killIterator(fotos,K);
}

bool areaDisparo(double cx, double cy, double raio,Forma analisa){
        if(get_type(analisa) == 'R'){
            double x1r = get_ret_x(analisa);
            double y1r =get_ret_y(analisa);
            double x2r = get_ret_x(analisa) + get_ret_larg(analisa);
            double y2r = get_ret_y(analisa) + get_ret_alt(analisa);

            if (Linha_Destruida(x1r, y1r, x1r, y2r, raio, cx, cy)) return true;
            else if (Linha_Destruida(x2r, y1r, x2r, y2r, raio, cx, cy)) return true;
            else if (Linha_Destruida(x1r, y1r, x2r, y1r, raio, cx, cy)) return true;
            else if (Linha_Destruida(x1r, y2r, x2r, y2r, raio, cx, cy)) return true;
            else if (cx >= x1r && cx <= x2r && cy >= y1r && cy <= y2r) return true;
            else return false; 
        }
        else if(get_type(analisa) == 'C'){
            if(sqrt(pow(cx-get_circ_cx(analisa),2)+pow(cy-get_circ_cy(analisa),2)) >= raio+get_circ_r(analisa))return false;
            else return true;
        }
        else if(get_type(analisa) == 'L'){
            double x1 = get_lin_x1(analisa);
            double x2 = get_lin_x2(analisa);
            double y1 = get_lin_y1(analisa);
            double y2 = get_lin_y2(analisa);
            return Linha_Destruida(x1,y1,x2,y2,raio,cx,cy);
        }
        else if(get_type(analisa) == 'T'){
            if(sqrt(pow(cx-get_text_x(analisa),2)+pow(cy-get_text_y(analisa),2)) >= raio)return false;
            else return true;
        }
        else{
            printf(" FORMA DESCONHECIDA AO DISPARAR");
            return false;
        }
}

bool Linha_Destruida(double x1, double y1, double x2, double y2, double raio, double cx, double cy){
    double comp = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    double sen = (x2 - x1)/raio;
    double coss = (y2 - y1)/raio;

    for (double i=0; i<=comp; i = i + comp/100) {
        double lx = x1 + (i * sen);
        double ly = y1 + (i * coss);
        if (sqrt(pow(lx - cx, 2) + pow(ly - cy, 2)) <= raio) return true;
    }
    return false;
}

bool reconhece_area(Balao B, Forma analise){
    double x1,x2,y1,y2;
    Texto aux = get_balao_forma(B);

    x1 = get_text_x(aux) - get_balao_raio(B);//vertices da esquerda (cima/baixo)
    x2 = get_text_x(aux) + get_balao_raio(B);//vertices da direita (cima/baixo)
    y1 = get_text_y(aux) + get_balao_prof(B);//vertices de cima (esquerda/direita)
    y2 = get_text_y(aux) + get_balao_prof(B) + get_balao_alt(B);//vertices de baixo (esquerda/direita)
    if(get_type(analise) == 'T'){
        if(get_text_x(analise) >= x2||get_text_x(analise) <= x1 
        ||get_text_y(analise) <= y1 ||get_text_y(analise) >= y2)return false;
        else return true;
    }
    if(get_type(analise) == 'R'){
        double xR2,yR2;
        xR2 = get_ret_x(analise) + get_ret_larg(analise);
        yR2 = get_ret_y(analise) + get_ret_alt(analise);
        if(xR2 <= x1||get_ret_x(analise) >= x2
        ||yR2 <= y1||get_ret_y(analise) >= y2)return false;
         else return true;
    }
    if(get_type(analise) == 'L'){
        double x1L = get_lin_x1(analise);
        double x2L = get_lin_x2(analise);
        double y1L = get_lin_y1(analise);
        double y2L = get_lin_y2(analise);
        double tamanhoLin = sqrt(pow(x1L-x2L,2)+pow(y1L-y2L,2));
        double seno = (x2L-x1L)/tamanhoLin;
        double cosseno = (y2L-y1L)/tamanhoLin;
        bool Dentro = false;
        for(double aux=0;aux <= tamanhoLin; aux += tamanhoLin/200){
            double dx = aux*seno;
            double dy = aux*cosseno;
            double ponto_x = x1L+dx;
            double ponto_y = y1L+dy;
            if(x1 <= ponto_x && ponto_x <= x2 && y1 <= ponto_y && ponto_y <= y2){
                Dentro = true;
                break;
            }
        }
        if(Dentro)return true;
        else return false;
    }
    if(get_type(analise) == 'C'){
        if((get_circ_cy(analise) - y2) >= get_circ_r(analise)||(y1 - get_circ_cy(analise)) >= get_circ_r(analise)
        ||(get_circ_cx(analise) - x2) >= get_circ_r(analise)||(x1 - get_circ_cx(analise))>= get_circ_r(analise))
        return false;
        else return true;
    }
     else{
        printf(" FORMA DESCONHECIDA");
        return false;
    }
}

void reporta_figura(FILE* txt,void* guarda_forma){
    if(guarda_forma == NULL)return;
    if(get_type(guarda_forma) == 'T'){
                fprintf(txt,"\nTexto ID=%d x= %lf y= %lf corp= %s corb= %s rotacao= %lf ancora= %s texto= %s",get_text_ID(guarda_forma),
                                get_text_x(guarda_forma),get_text_y(guarda_forma),get_text_corp(guarda_forma),
                                get_text_corb(guarda_forma),get_text_rot(guarda_forma), get_text_ancora(guarda_forma), get_text_texto(guarda_forma));
                }
                
                else if(get_type(guarda_forma) == 'R'){
                    fprintf(txt,"\nRetangulo ID=%d x= %lf y= %lf altura= %lf largura=%lf rotacao= %lf corp= %s corb = %s",get_ret_ID(guarda_forma),
                                get_ret_x(guarda_forma),get_ret_y(guarda_forma),get_ret_alt(guarda_forma),get_ret_larg(guarda_forma),
                                get_ret_rot(guarda_forma), get_ret_corp(guarda_forma), get_ret_corb(guarda_forma));
                }

                else if(get_type(guarda_forma) == 'L'){
                    fprintf(txt,"\nLinha ID=%d x1= %lf y1= %lf x2= %lf y2=%lf rotaçao= %lf corp= %s",get_lin_ID(guarda_forma),
                                get_lin_x1(guarda_forma),get_lin_y1(guarda_forma),get_lin_x2(guarda_forma),
                                get_lin_y2(guarda_forma),get_lin_rot(guarda_forma), get_lin_corp(guarda_forma));
                }
                else if(get_type(guarda_forma) == 'C'){
                    fprintf(txt,"\nCirculo ID=%d cx= %lf cy= %lf r= %lf rotacao= %lf corp= %s corb = %s",get_circ_ID(guarda_forma),
                                get_circ_cx(guarda_forma),get_circ_cy(guarda_forma),get_circ_r(guarda_forma),
                                get_circ_rot(guarda_forma), get_circ_corp(guarda_forma), get_circ_corb(guarda_forma));
                }
                else printf("FORMA NAO IDENTIFICADA PARA REPORTAR\n");
}

void* acha_ID(Lista lista, int ID){
    Iterador K = createIterator(lista,false);
    void* figura = getIteratorNext(lista,K);

    while(ID != get_ID(figura)){
        figura = getIteratorNext(lista,K);
        if(isIteratorEmpty(lista,K))break;
    }
    killIterator(lista,K);
    if(ID == get_ID(figura))return figura;
    else return NULL;
}

void Executa_ListaFormas(Lista executada){
    Iterador apaga = createIterator(executada,false);
    while(!isIteratorEmpty(executada,apaga))killForma(getIteratorNext(executada,apaga));
    killIterator(executada,apaga);
    killLst(executada);
}

char* Nome_arq_svg(char recebe[], char* patho,char* sfx) {
   strcpy(recebe,patho);
   strcat(recebe,sfx);
   strcat(recebe,".svg");
}