#include "funcs.h"

int charIndex(char c) {
    // + - 0 1 2 3 4 5 6 7 8 9 = ; d e f g h i t n l s b p r \n O
    if(c == '+') return 0;
    else if(c == '-') return 1;
    else if(c >= '0' && c <= '9') return (1 + (c - 47));
    else if(c == '=') return 12;
    else if(c == ';') return 13;
    else if(c >= 'd' && c <= 'i') return (13 + (c - 99));  
    else if(c == 't') return 20;
    else if(c == 'n') return 21;
    else if(c == 'l') return 22;
    else if(c == 's') return 23;
    else if(c == 'b') return 24;
    else if(c == 'p') return 25;
    else if(c == 'r') return 26;
    else if(c == '\n') return 27;
    // else if(c == ' ') return 28;
    else return -1; // outro
}

bool isFinalState(int state) {
    if(state == 19 || state == 20 ||state == 21 ||state == 22 ||state == 23 ||state == 24 ||
    state == 25 ||state == 26 || state == 27 || state == 28) return true;
    else return false;  
}

Token getToken(int estadoFinal) {
    if(estadoFinal == 19)return IF;
    else if(estadoFinal == 20)return THEN;
    else if(estadoFinal == 21)return ELSE;
    else if(estadoFinal == 22)return END;
    else if(estadoFinal == 23)return BEGIN;
    else if(estadoFinal == 24)return PRINT;
    else if(estadoFinal == 25)return SEMICOL;
    else if(estadoFinal == 26)return EQ;
    else if(estadoFinal == 27)return NUM;
    else if(estadoFinal == 28)return NEW_LINE;
    else return 0;
}

int nextToken(int matriz[][29]) {//Pega proximo token
    int estadofinal = 0;
    int estadoAtual = 1;
    int cursorFinal = 0;
    int cursorAtual = 0;
    char c;

    while(1) { 
        if(fread(&c, 1, 1, stdin) != 1) { 
            if(cursorAtual == 0)return 0; // chegou ao final
            // reajusta cursor
            int offset = cursorAtual - cursorFinal;
            if(cursorFinal == 0)offset--; // lexema nao reconhecido    
            fseek(stdin, -offset, SEEK_CUR);//Cursor vai ate ultimo token reconhecido
            return getToken(estadofinal);
        }
        cursorAtual++;//Se ler um caracter cursos avança
        estadoAtual = matriz[estadoAtual][charIndex(c)];//Pega proximo estado
        
        if(estadoAtual == 0) { // transacao invalida
            // reajusta cursor ate ultimo token reconhecido
            int offset = cursorAtual - cursorFinal;
            if(cursorFinal == 0) { // token nao reconhecido
                if(cursorAtual == 1 && (c == ' ')) return nextToken(matriz); // ignora 1 caracter ' ' 
                else  offset--;
            } 
            fseek(stdin, -offset, SEEK_CUR);
            return getToken(estadofinal);
        }
        else if(isFinalState(estadoAtual)){ // lexema reconhecido
            estadofinal = estadoAtual;
            cursorFinal = cursorAtual;
        }
    }
}

char* tokenClass(int token) {//Pega valor de string dos tokens 
    switch(token) {
        case 1:
            return "if";
        case 2:
            return "then";
        case 3:
            return "else";
        case 4:
            return "end";
        case 5:
            return "begin";
        case 6:
            return "print";
        case 7:
            return ";";
        case 8:
            return "=";
        case 9:
            return "num";
        default:
            return "error";
    }
}

void advance(int *token,int matriz[][29]) {//Pega proximo token
    *token = nextToken(matriz);
}

void printError(int tokenLido, char* tokenEsperado, int *status,int *token,int matriz[][29]) {

    printf("ERRO SINTATICO EM: %s ESPERADO: %s", tokenClass(tokenLido), tokenEsperado);
    *status = REJECTED;

    while(*token != NEW_LINE && *token != 0)*token = nextToken(matriz);
}

void eat(int t,int *tokenAtual, int *status,int matriz[][29]){
    if(*tokenAtual == NEW_LINE || *tokenAtual == 0) {
    if(*status == ACCEPTED) 
        *status = INCOMPLETE;
        return;
    }
    else if(*tokenAtual == t) advance(tokenAtual, matriz); 
    else printError(*tokenAtual, tokenClass(t), status, tokenAtual, matriz);
}

void L(int *tokenAtual, int *status,int matriz[][29]) {
    if(*tokenAtual == NEW_LINE || *tokenAtual == 0) {
        if(*status == ACCEPTED) 
            *status = INCOMPLETE;
        return;
    }
    switch(*tokenAtual) {
        case END: eat(END, tokenAtual,status,matriz); break;
        case SEMICOL: eat(SEMICOL,tokenAtual,status,matriz); S(tokenAtual,status,matriz); L(tokenAtual,status, matriz); break;
        default: 
            printError(*tokenAtual, "end, ;", status, tokenAtual, matriz); 
    }
}

void E(int *tokenAtual, int *status,int matriz[][29]) {
    if(*tokenAtual == NEW_LINE || *tokenAtual == 0) {
        if(*status == ACCEPTED) 
            *status = INCOMPLETE;
        return;
    }
    eat(NUM, tokenAtual,status,matriz); eat(EQ, tokenAtual,status,matriz); eat(NUM, tokenAtual,status,matriz); 
}

parsingStatus S(int *tokenAtual, int *status,int matriz[][29]) {
    if(*tokenAtual == NEW_LINE || *tokenAtual == 0) {
        if(*status == ACCEPTED) 
            *status = INCOMPLETE;
        return *status;
    }
    switch(*tokenAtual) {
        case IF: eat(IF, tokenAtual,status,matriz); E(tokenAtual,status,matriz); eat(THEN,tokenAtual,status,matriz); S(tokenAtual,status,matriz); eat(ELSE,tokenAtual,status,matriz); S(tokenAtual,status,matriz); break;
        case BEGIN: eat(BEGIN, tokenAtual,status,matriz); S(tokenAtual,status,matriz); L(tokenAtual,status,matriz); break;
        case PRINT: eat(PRINT, tokenAtual,status,matriz); E(tokenAtual,status,matriz); break;
        default:
            printError(*tokenAtual, "if, begin, print", status, tokenAtual, matriz);
    }
    return *status;
}