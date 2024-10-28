%{
#include <stdio.h>

FILE *yyin;
int current_file_index = 1; // Começa com 1 para ignorar o nome do programa
int num_files;
char **file_names;

int linhasTotais = 0;
int linhasVazias = 0;
int LinhasComentadas = 0;
int pontoVirgula = 0;
int diretivas = 0;
int linhasNormais = 0;

int inicioComent = 0;
int commentMono = 0;
int pulalinha = 0;
%}

%option noyywrap

%%

"#include"|"#define" {
    diretivas++;
}
"/*"    {
    pulalinha = 0;
    inicioComent = 1;
}

"*/"    {
    inicioComent = 0;
    LinhasComentadas++;
}
"//"    {
    if(!commentMono && !inicioComent){
        LinhasComentadas ++;
        commentMono = 1;
    }
}
^\n     {
    commentMono = 0;
    linhasVazias++;
    linhasTotais ++;
    if(inicioComent)LinhasComentadas++;
    pulalinha = 1;
}
\n      {
    commentMono = 0;
    if(inicioComent)LinhasComentadas++;
    else linhasNormais ++;
    linhasTotais ++;
    pulalinha = 1;
}
;       {pontoVirgula++;}
.       {}

<<EOF>>         {
    linhasTotais++;
    if(inicioComent )LinhasComentadas++;
    else linhasNormais ++;
    return 0;
    }
%%

int main(int argc, char **argv) {
    printf("%-8s%-8s%-10s%-9s%-8s%-8s\n", 
           "total", "blank", "lines w","nb,nc", "semi-", "preproc.");
    printf("%-8s%-8s%-10s%-9s%-8s%-9s%-8s\n", 
           "lines", "lines", "comments", "lines", "colons", "direct.", "file");
    printf("------+--------+--------+--------+--------+--------+----\n");
    
    int i;
    if(argc < 2) { /* just read stdin */
        yylex();
        printf("%-10d%-10d%-10d%-10d%-10d%-2d%-8s\n", linhasTotais, linhasVazias, LinhasComentadas, linhasNormais, pontoVirgula, diretivas,  argv[i]);
        return 0;
    }
    for(i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");

        if(!f) {
            perror(argv[i]);
            return (1);
        }
        yyrestart(f);
        yylex();
        fclose(f);
        printf("%-10d%-10d%-10d%-10d%-10d%-2d%-8s\n", linhasTotais, linhasVazias, LinhasComentadas, linhasNormais, pontoVirgula, diretivas,  argv[i]);


        linhasTotais = 0;
        linhasVazias = 0;
        LinhasComentadas = 0;
        linhasNormais = 0;
        pontoVirgula = 0;
        diretivas = 0;
    }
    return 0;
}
