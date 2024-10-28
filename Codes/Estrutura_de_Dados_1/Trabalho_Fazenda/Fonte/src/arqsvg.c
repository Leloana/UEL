#include "arqsvg.h"
#include <stdio.h>
#include "formas.h"

ArqSvg abreEscritaSvg(char *fn){
    FILE* arquivo = fopen(fn,"w");
    // <?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<svg viewBox=\"-110 -110 600 500\" xmlns=\"http://www.w3.org/2000/svg\">
    fprintf(arquivo,"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100%%\" height=\"100%%\" viewBox=\"0 0 4000 4000\">");
    return arquivo;
}

void fechaSvg(ArqSvg fsvg){
    fprintf(fsvg,"\n</svg>");
    fclose(fsvg);
}

void escreveCirculoSvg(ArqSvg fsvg,Circulo C){
    if(C == NULL)return;
    fprintf(fsvg,"\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" transform = \"rotate (%lf %lf %lf)\" fill=\"%s\" />",
                                                 get_circ_cx(C), get_circ_cy(C), get_circ_r(C),get_circ_corb(C),get_circ_rot(C),get_circ_cx(C),get_circ_cy(C), get_circ_corp(C));
}

void escreveRetanguloSvg(ArqSvg fsvg, Retangulo R){
    if(R == NULL)return;
    fprintf(fsvg,"\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" transform = \"rotate (%lf %lf %lf)\" style=\"fill:%s;stroke:%s\" stroke-dasharray=\"%lf\" />",
                                                     get_ret_x(R), get_ret_y(R), get_ret_larg(R), get_ret_alt(R),get_ret_rot(R),get_ret_x(R), get_ret_y(R), get_ret_corp(R), get_ret_corb(R),get_ret_dasharray(R));
}

void escreveLinhaSvg(ArqSvg fsvg,Linha L){
    if(L == NULL)return;
    fprintf(fsvg,"\n\t<line x1=\"%lf\" x2=\"%lf\" y1=\"%lf\" y2=\"%lf\" transform = \"rotate (%lf %lf %lf)\" style=\"stroke:%s\" />",
                                            get_lin_x1(L), get_lin_x2(L), get_lin_y1(L), get_lin_y2(L),get_lin_rot(L),get_lin_x1(L), get_lin_y1(L), get_lin_corp(L));
}

void escreveTextoSvg(ArqSvg fsvg,Texto T){
    if(T == NULL)return;
    fprintf(fsvg,"\n\t<text x=\"%lf\" y=\"%lf\" font-family=\"%s\" font-size=\"%s\" font-weight=\"%s\" fill=\"%s\" stroke=\"%s\" text-anchor = \"%s\" dominant-baseline=\"%s\" transform = \"rotate (%lf %lf %lf)\" >%s</text>",
                                     get_text_x(T), get_text_y(T),get_text_Family(T),get_text_Size(T),get_text_Weight(T), get_text_corp(T),get_text_corb(T),get_text_ancora(T),get_text_ancora(T), get_text_rot(T),get_text_x(T), get_text_y(T), get_text_texto(T));
}

void escreveGeralSvgLista(ArqSvg fsvg,Forma forma){
    if(get_type(forma) == 'R')escreveRetanguloSvg(fsvg, forma);
    else if(get_type(forma) == 'C')escreveCirculoSvg(fsvg, forma);
    else if(get_type(forma) == 'T')escreveTextoSvg(fsvg, forma);
    else if(get_type(forma) == 'L')escreveLinhaSvg(fsvg, forma);
}

void escreveGeralSvgArvore(Horta hortalica,double x, double y, void* svg){
    Forma Figura = get_HortaFigura(hortalica);

    if(get_type(Figura) == 'C')escreveCirculoSvg(svg,Figura);
    else if(get_type(Figura) == 'R')escreveRetanguloSvg(svg,Figura);
    else if(get_type(Figura) == 'T')escreveTextoSvg(svg,Figura);
    else if(get_type(Figura) == 'L')escreveLinhaSvg(svg,Figura);
}