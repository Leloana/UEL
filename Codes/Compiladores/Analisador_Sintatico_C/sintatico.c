#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintatico.h"

int token; // token global
bool changeToken = false;

void parser(void *tokens, char *input) {
    token = getNode(tokens);
    if(token == -1) { // erro
        if(changeToken) printf("\n");
        printf("ERRO PILHA VAZIA");
        changeToken = true;
        exit(0);
    }
    defineID();
    S(tokens, input);  // simbolo inicial
}

void eat(void *tokens, int tokenAnalisado, char *input) {
    if(tokenAnalisado == token) {  // token aceito, remove da pilha
        removeNode(tokens);
        token = getNode(tokens);
        defineID();
    } else {
        int col = getColuna(tokens) - strlen(getToken(tokens)) + 1;
        printf("ERRO DE SINTAXE. Linha: %d Coluna: %d -> '%s'", getLinha(tokens), col, getToken(tokens));
        freePilha(tokens);
        free(input);
        exit(1);
    }
}

void erroSintaxe(void *tokens) {
    int col = getColuna(tokens) - strlen(getToken(tokens)) + 1;
    printf("ERRO DE SINTAXE. Linha: %d Coluna: %d -> '%s'", getLinha(tokens), col, getToken(tokens));
}

void defineID() {
    if(token != -1 && token != 1 && token != EOF_TOKEN) {
        if(token >= NUM_INT && token <= DIVISAO) return;                // reservado
        if(token >= DIFERENTE && token <= ATRIBUICAO) return;           // reservado
        if(token >= PROCEDIMENTO && token <= COMENTARIO_BLOCO) return;  // reservado
        if(token == ALGORITMO || token == ATE || token == INICIO || token == IMPRIMA || token == FIM || 
        token == FUNCAO || token == FACA || token == FALSO || token == VARIAVEIS || token == VETOR) return;
        if(token == VERDADEIRO || token == INTEIRO || token == REAL || token == REPITA || token == SE || 
        token == SENAO || token == E || token == ENTAO || token == ENQUANTO || token == DE || token == DIV) return;
        if(token == OU || token == NAO || token == TIPO || token == LEIA || token == LOGICO || 
        token == MATRIZ || token == CARACTERE || token == PARA || token == PASSO || token == PROCEDIMENTO)  return;
        token = ID;
    }
}
void S(void *tokens, char *input) {
    switch(token) {
        case ALGORITMO:
            identifyPROGRAMA(tokens, input);
            eat(tokens, EOF_TOKEN, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void identifyPROGRAMA(void *tokens, char *input) {
    switch(token) {
        case ALGORITMO:
            eat(tokens, ALGORITMO, input);
            eat(tokens, ID, input);
            eat(tokens, PONTO_VIRGULA, input);
            identifyBLOCOS(tokens, input);
            identifyFuncao(tokens, input);
            identifyBlocoCOMANDOS(tokens, input);
            eat(tokens, PONTO, input);
            break;

        case EOF_TOKEN:
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}

void identifyFuncao(void *tokens, char *input) {
    switch(token) {
        case INICIO:
            break;

        case FUNCAO:
            declareFuncao(tokens, input);
            identifyFuncao(tokens, input);
            break;

        case PROCEDIMENTO:
            identifyPocedimento(tokens, input);
            identifyFuncao(tokens, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void identifyPocedimento(void *tokens, char *input) {
    switch(token) {
        case PROCEDIMENTO:
            eat(tokens, PROCEDIMENTO, input);
            eat(tokens, ID, input);
            identifyPARAMETROS(tokens, input);
            eat(tokens, PONTO_VIRGULA, input);
            declarePARAMETROS(tokens, input);
            identifyBLOCOS(tokens, input);
            identifyBlocoCOMANDOS(tokens, input);
            eat(tokens, PONTO_VIRGULA, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}

void declareFuncao(void *tokens, char *input) {
    switch(token) {
        case FUNCAO:
            eat(tokens, FUNCAO, input);
            eat(tokens, ID, input);
            identifyPARAMETROS(tokens, input);
            eat(tokens, DOIS_PONTOS, input);
            basicTIPO(tokens, input);
            eat(tokens, PONTO_VIRGULA, input);
            declarePARAMETROS(tokens, input);
            identifyBLOCOS(tokens, input);
            identifyBlocoCOMANDOS(tokens, input);
            eat(tokens, PONTO_VIRGULA, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void identifyPARAMETROS(void *tokens, char *input) {
    switch(token) {
        case PONTO_VIRGULA:
        case DOIS_PONTOS:
            break;

        case ABRE_PARENTESES:
            eat(tokens, ABRE_PARENTESES, input);
            declareID(tokens, input);
            eat(tokens, FECHA_PARENTESES, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void declarePARAMETROS(void *tokens, char *input) {
    switch(token) {
        case PROCEDIMENTO:
        case FUNCAO:
        case VARIAVEIS:
        case INICIO:
            break;

        case ID:
        case TIPO:
        case INTEIRO:
        case REAL:
        case CARACTERE:
        case LOGICO:
            declaring(tokens, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void identifyBLOCOS(void *tokens, char *input) {
    switch(token) {
        case PROCEDIMENTO:
        case FUNCAO:
        case INICIO:
        case EOF_TOKEN:
            break;

        case VARIAVEIS:
            eat(tokens, VARIAVEIS, input);
            declaring(tokens, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void declaring(void *tokens, char *input) {
    switch(token) {
        case ID:
        case INTEIRO:
        case REAL:
        case CARACTERE:
        case LOGICO:
            declareVAR(tokens, input);
            declaringDash(tokens, input);
            break;

        case TIPO:
            declareTIPO(tokens, input);
            declaringDash(tokens, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void declaringDash(void *tokens, char *input) {
    switch(token) {
        case ID:
        case TIPO:
        case INTEIRO:
        case REAL:
        case CARACTERE:
        case LOGICO:
            declaring(tokens, input);
            break;

        case PROCEDIMENTO:
        case FUNCAO:
        case VARIAVEIS:
        case INICIO:
        case EOF_TOKEN:
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void declareTIPO(void *tokens, char *input) {
    switch(token) {
        case TIPO:
            eat(tokens, TIPO, input);
            eat(tokens, ID, input);
            eat(tokens, IGUAL, input);
            identifyVETOR(tokens, input);
            eat(tokens, ABRE_COLCHETE, input);
            identifyDIMENSION(tokens, input);
            eat(tokens, FECHA_COLCHETE, input);
            basicTIPO(tokens, input);
            eat(tokens, PONTO_VIRGULA, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void declareVAR(void *tokens, char *input) {
    switch(token) {
        case ID:
        case INTEIRO:
        case REAL:
        case CARACTERE:
        case LOGICO:
            basicTIPO(tokens, input);
            eat(tokens, DOIS_PONTOS, input);
            declareID(tokens, input);
            eat(tokens, PONTO_VIRGULA, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void declareID(void *tokens, char *input) {
    switch(token) {
        case ID:
            eat(tokens, ID, input);
            declareIDDash(tokens, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void declareIDDash(void *tokens, char *input) {
    switch(token) {
        case VIRGULA:
        eat(tokens, VIRGULA, input);
        declareID(tokens, input);
        break;

        case PONTO_VIRGULA:
        case FECHA_PARENTESES:
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void identifyVETOR(void *tokens, char *input) {
    switch(token) {
        case MATRIZ:
            eat(tokens, MATRIZ, input);
            break;

        case VETOR:
            eat(tokens, VETOR, input);
            break;


        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void identifyDIMENSION(void *tokens, char *input) {
    switch(token) {
        case NUM_INT:
            eat(tokens, NUM_INT, input);
            eat(tokens, DOIS_PONTOS, input);
            eat(tokens, NUM_INT, input);
            dimensionDash(tokens, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void dimensionDash(void *tokens, char *input) {
    switch(token) {
        case VIRGULA:
            eat(tokens, VIRGULA, input);
            identifyDIMENSION(tokens, input);
            break;

        case FECHA_COLCHETE:
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void basicTIPO(void *tokens, char *input) {
    switch(token) {
        case CARACTERE:
            eat(tokens, CARACTERE, input);
            break;

        case REAL:
            eat(tokens, REAL, input);
            break;

        case ID:
            eat(tokens, ID, input);
            break;

        case INTEIRO:
            eat(tokens, INTEIRO, input);
            break;

        case LOGICO:
            eat(tokens, LOGICO, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void identifyBlocoCOMANDOS(void *tokens, char *input) {
    switch(token) {
        case INICIO:
            eat(tokens, INICIO, input);
            identifyListaCOMANDOS(tokens, input);
            eat(tokens, FIM, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void identifyListaCOMANDOS(void *tokens, char *input) {
    switch(token) {
        case ID:
        case SE:
        case ENQUANTO:
        case PARA:
        case REPITA:
        case LEIA:
        case IMPRIMA:
            Comandos(tokens, input);
            eat(tokens, PONTO_VIRGULA, input);
            listaComandosDash(tokens, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void listaComandosDash(void *tokens, char *input) {
    switch(token) {
        case ID:
        case SE:
        case ENQUANTO:
        case PARA:
        case REPITA:
        case LEIA:
        case IMPRIMA:
            identifyListaCOMANDOS(tokens, input);
            break;

        case FIM:
        case SENAO:
        case ATE:
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void Comandos(void *tokens, char *input) {
    switch(token) {
        case SE:
            eat(tokens, SE, input);
            identifyEXPRESSAO(tokens, input);
            eat(tokens, ENTAO, input);
            identifyListaCOMANDOS(tokens, input);
            comandosDash2(tokens, input);
            break;
        
        case ID:
            eat(tokens, ID, input);
            comandosDash1(tokens, input);
            break;

        case PARA:
            eat(tokens, PARA, input);
            eat(tokens, ID, input);
            eat(tokens, DE, input);
            identifyEXPRESSAO(tokens, input);
            eat(tokens, ATE, input);
            identifyEXPRESSAO(tokens, input);
            comandosDash3(tokens, input);
            break;

        case ENQUANTO:
            eat(tokens, ENQUANTO, input);
            identifyEXPRESSAO(tokens, input);
            eat(tokens, FACA, input);
            identifyListaCOMANDOS(tokens, input);
            eat(tokens, FIM, input);
            eat(tokens, ENQUANTO, input);
            break;

        case REPITA:
            eat(tokens, REPITA, input);
            identifyListaCOMANDOS(tokens, input);
            eat(tokens, ATE, input);
            identifyEXPRESSAO(tokens, input);
            break;
        
        case IMPRIMA:
            eat(tokens, IMPRIMA, input);
            eat(tokens, ABRE_PARENTESES, input);
            ExprIter(tokens, input);
            eat(tokens, FECHA_PARENTESES, input);
            break;

        case LEIA:
            eat(tokens, LEIA, input);
            eat(tokens, ABRE_PARENTESES, input);
            Variavel(tokens, input);
            eat(tokens, FECHA_PARENTESES, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void comandosDash1(void *tokens, char *input) {
    switch(token) {
        case ATRIBUICAO:
            eat(tokens, ATRIBUICAO, input);
            identifyEXPRESSAO(tokens, input);
            break;

        case PONTO_VIRGULA:
            break;
        
        case ABRE_COLCHETE:
            eat(tokens, ABRE_COLCHETE, input);
            ExprIter(tokens, input);
            eat(tokens, FECHA_COLCHETE, input);
            eat(tokens, ATRIBUICAO, input);
            identifyEXPRESSAO(tokens, input);
            break;
 
        case ABRE_PARENTESES:
            eat(tokens, ABRE_PARENTESES, input);
            ExprIter(tokens, input);
            eat(tokens, FECHA_PARENTESES, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void comandosDash2(void *tokens, char *input) {
    switch(token) {
        case SENAO:
            eat(tokens, SENAO, input);
            identifyListaCOMANDOS(tokens, input);
            eat(tokens, FIM, input);
            eat(tokens, SE, input);
            break;

        case FIM:
            eat(tokens, FIM, input);
            eat(tokens, SE, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void comandosDash3(void *tokens, char *input) {
    switch(token) {
        case FACA:
            eat(tokens, FACA, input);
            identifyListaCOMANDOS(tokens, input);
            eat(tokens, FIM, input);
            eat(tokens, PARA, input);
            break;

        case PASSO:
            eat(tokens, PASSO, input);
            identifyEXPRESSAO(tokens, input);
            eat(tokens, FACA, input);
            identifyListaCOMANDOS(tokens, input);
            eat(tokens, FIM, input);
            eat(tokens, PARA, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void identifyEXPRESSAO(void *tokens, char *input) {
    switch(token) {
        case ID:
        case NUM_INT:
        case NUM_REAL:
        case NAO:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case ABRE_PARENTESES:
        case MAIS:
        case MENOS:
            simpleEXPRESSAO(tokens, input);
            expressaoDash(tokens, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void expressaoDash(void *tokens, char *input) {
    switch(token) {
        case PONTO_VIRGULA:
        case FECHA_PARENTESES:
        case FECHA_COLCHETE:
        case VIRGULA:
        case ENTAO:
        case FACA:
        case ATE:
        case PASSO:
            break;

        case IGUAL:
        case DIFERENTE:
        case MENOR:
        case MENOR_IGUAL:
        case MAIOR:
        case MAIOR_IGUAL:
            OperadorRelacional(tokens, input);
            simpleEXPRESSAO(tokens, input);
            expressaoDash(tokens, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void simpleEXPRESSAO(void *tokens, char *input) {
    switch(token) {
        case MAIS:
        case MENOS:
            OperadorAritmetico(tokens, input);
            Termo(tokens, input);
            simpleEXPRESSAODash(tokens, input);
            break;

        case ID:
        case NUM_INT:
        case NUM_REAL:
        case NAO:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case ABRE_PARENTESES:
            Termo(tokens, input);
            simpleEXPRESSAODash(tokens, input);
            break;


        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void simpleEXPRESSAODash(void *tokens, char *input) {
    switch(token) {
        case PONTO_VIRGULA:
        case FECHA_PARENTESES:
        case FECHA_COLCHETE:
        case VIRGULA:
        case IGUAL:
        case DIFERENTE:
        case MENOR:
        case MENOR_IGUAL:
        case MAIOR:
        case MAIOR_IGUAL:
        case ENTAO:
        case FACA:
        case ATE:
        case PASSO:
            break;

        case OU:
            eat(tokens, OU, input);
            Termo(tokens, input);
            simpleEXPRESSAODash(tokens, input);
            break;

        case MAIS:
        case MENOS:
            OperadorAritmetico(tokens, input);
            Termo(tokens, input);
            simpleEXPRESSAODash(tokens, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void OperadorRelacional(void *tokens, char *input) {
    switch(token) {
        case MAIOR_IGUAL:
            eat(tokens, MAIOR_IGUAL, input);
            break;

        case MENOR:
            eat(tokens, MENOR, input);
            break;

        case MENOR_IGUAL:
            eat(tokens, MENOR_IGUAL, input);
            break;

        case IGUAL:
            eat(tokens, IGUAL, input);
            break;

        case DIFERENTE:
            eat(tokens, DIFERENTE, input);
            break;

        case MAIOR:
            eat(tokens, MAIOR, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void OperadorAritmetico(void *tokens, char *input) {
    switch(token) {
        case MAIS:
            eat(tokens, MAIS, input);
            break;

        case MENOS:
            eat(tokens, MENOS, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void Termo(void *tokens, char *input) {
    switch(token) {
        case ID:
        case NUM_INT:
        case NUM_REAL:
        case NAO:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case ABRE_PARENTESES:
            Fator(tokens, input);
            termoDash(tokens, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void termoDash(void *tokens, char *input) {
    switch(token) {
        case PONTO_VIRGULA:
        case FECHA_PARENTESES:
        case FECHA_COLCHETE:
        case VIRGULA:
        case IGUAL:
        case DIFERENTE:
        case MAIOR:
        case MAIOR_IGUAL:
        case MENOR:
        case MENOR_IGUAL:
        case MAIS:
        case MENOS:
        case OU:
        case ENTAO:
        case FACA:
        case ATE:
        case PASSO:
            break;

        case DIV:
            eat(tokens, DIV, input);
            Fator(tokens, input);
            termoDash(tokens, input);
            break;

        case E:
            eat(tokens, E, input);
            Fator(tokens, input);
            termoDash(tokens, input);
            break;

        case VEZES:
            eat(tokens, VEZES, input);
            Fator(tokens, input);
            termoDash(tokens, input);
            break;

        case DIVISAO:
            eat(tokens, DIVISAO, input);
            Fator(tokens, input);
            termoDash(tokens, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void Fator(void *tokens, char *input) {
    switch(token) {
        case VERDADEIRO:
            eat(tokens, VERDADEIRO, input);
            break;

        case ABRE_PARENTESES:
            eat(tokens, ABRE_PARENTESES, input);
            identifyEXPRESSAO(tokens, input);
            eat(tokens, FECHA_PARENTESES, input);
            break;

        case ID:
            eat(tokens, ID, input);
            fatorDash(tokens, input);
            break;

        case NUM_INT:
            eat(tokens, NUM_INT, input);
            break;

        case FALSO:
            eat(tokens, FALSO, input);
            break;

        case STRING:
            eat(tokens, STRING, input);
            break;

        case NAO:
            eat(tokens, NAO, input);
            Fator(tokens, input);
            break;

        case NUM_REAL:
            eat(tokens, NUM_REAL, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void fatorDash(void *tokens, char *input) {
    switch(token) {
        case PONTO_VIRGULA:
        case FECHA_PARENTESES:
        case FECHA_COLCHETE:
        case VIRGULA:
        case IGUAL:
        case DIFERENTE:
        case MAIOR:
        case MAIOR_IGUAL:
        case MENOR:
        case MENOR_IGUAL:
        case MAIS:
        case MENOS:
        case OU:
        case VEZES:
        case DIVISAO:
        case DIV:
        case E:
        case ENTAO:
        case FACA:
        case ATE:
        case PASSO:
            break;

        case ABRE_COLCHETE:
            eat(tokens, ABRE_COLCHETE, input);
            ExprIter(tokens, input);
            eat(tokens, FECHA_COLCHETE, input);
            break;

        case ABRE_PARENTESES:
            eat(tokens, ABRE_PARENTESES, input);
            ExprIter(tokens, input);
            eat(tokens, FECHA_PARENTESES, input);
            break;


        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void Variavel(void *tokens, char *input) {
    switch(token) {
        case ID:
            eat(tokens, ID, input);
            variavelDash(tokens, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void variavelDash(void *tokens, char *input) {
    switch(token) {
        case FECHA_PARENTESES:
        // case ATRIBUICAO:
            break;

        case ABRE_COLCHETE:
            eat(tokens, ABRE_COLCHETE, input);
            ExprIter(tokens, input);
            eat(tokens, FECHA_COLCHETE, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void ExprIter(void *tokens, char *input) {
    switch(token) {
        case ID:
        case NUM_INT:
        case NUM_REAL:
        case NAO:
        case VERDADEIRO:
        case FALSO:
        case STRING:
        case MAIS:
        case MENOS:
        case ABRE_PARENTESES:
            identifyEXPRESSAO(tokens, input);
            exprIterDash(tokens, input);
            break;

        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}
void exprIterDash(void *tokens, char *input) {
    switch(token) {
        case VIRGULA:
            eat(tokens, VIRGULA, input);
            ExprIter(tokens, input);
            break;

        case FECHA_PARENTESES:
        case FECHA_COLCHETE:
            break;


        default:
            erroSintaxe(tokens);
            freePilha(tokens);
            free(input);
            exit(1);
            break;
    }
}