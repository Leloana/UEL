#include "funcs.h"

int charIndex(char c) {
//  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  +  *  (  )  $
    if(c>= '0' && c<= '9') return c - 48;
    else if(c >= 'a' && c <= 'z' ) return c - (97-10); 
    else if(c == '+') return 36;
    else if(c == '*') return 37;
    else if(c == '(') return 38; 
    else if(c == ')') return 39; 
    else if(c == '$') return 40; 
    else if(c == '\n') return 41;
    
    else return -1; // outro
}

bool isFinalState(int state) {
    if(state == 2 || state == 3 ||state == 4 ||state == 5 ||state == 6 ||state == 7 || state == 8) return true;
    else return false;  
}

Token getToken(int estadoFinal) {
    if(estadoFinal == 2)return PLUS;
    else if(estadoFinal == 3)return MUL;
    else if(estadoFinal == 4)return L_PAREN;
    else if(estadoFinal == 5)return R_PAREN;
    else if(estadoFinal == 6)return EOL;
    else if(estadoFinal == 7)return ID;
    else if(estadoFinal == 8)return NEW_LINE;

    else return 0;
}

int nextToken(int matriz[][43]) {//Pega proximo token
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
        case PLUS:
            return "+";
        case MUL:
            return "*";
        case L_PAREN:
            return "(";
        case R_PAREN:
            return ")";
        case EOL:
            return "$";
        case ID:
            return "id";
        default:
            return "error";
    }
}

void advance(int *token,int matriz[][43]) {//Pega proximo token
    *token = nextToken(matriz);
}

void printError(char* tokenEsperado, int *status,int *token,int matriz[][43]) {
    printf("ERRO SINTATICO EM: %s ESPERADO: %s", tokenClass(*token), tokenEsperado);
    *status = REJECTED;

    while(*token != NEW_LINE && *token != 0)*token = nextToken(matriz);
}

void eat(int t,int *tokenAtual, int *status,int matriz[][43]){
    if(*tokenAtual == NEW_LINE || *tokenAtual == 0) {
        if(*status == ACCEPTED) {
            *status = INCOMPLETE;
            return;
        }
    }
    else if(*tokenAtual == t) advance(tokenAtual, matriz); 
    else printError(tokenClass(t), status, tokenAtual, matriz);
}

void T(int *tokenAtual, int *status,int matriz[][43]) {
    if(*tokenAtual == NEW_LINE || *tokenAtual == 0) {
        if(*status == ACCEPTED) 
            *status = INCOMPLETE;
        return;
    }
    switch(*tokenAtual) {
        case ID:

        case L_PAREN:
            F(tokenAtual, status,matriz);T_Quote(tokenAtual, status,matriz);
            break;
        default:
            printError("id, (", status, tokenAtual, matriz);
    }
}

void T_Quote(int *tokenAtual, int *status,int matriz[][43]) {
    if(*tokenAtual == NEW_LINE || *tokenAtual == 0) {
        if(*status == ACCEPTED) 
            *status = INCOMPLETE;
        return;
    }
    switch(*tokenAtual) {
        case PLUS:

        case R_PAREN:

        case EOL:
            // remove T'
            break;

        case MUL:
            eat(MUL, tokenAtual, status,matriz);F(tokenAtual, status,matriz);T_Quote(tokenAtual, status,matriz);
            break;
        default:
            printError("+, *, ), $", status, tokenAtual, matriz);
    }
}

void F(int *tokenAtual, int *status,int matriz[][43]) {
    if(*tokenAtual == NEW_LINE || *tokenAtual == 0) {
        if(*status == ACCEPTED) 
            *status = INCOMPLETE;
        return;
    }
    switch(*tokenAtual) {
        case ID:
                eat(ID, tokenAtual, status, matriz);
                break;

        case L_PAREN:
            eat(L_PAREN, tokenAtual, status, matriz);E(tokenAtual, status,matriz);eat(R_PAREN, tokenAtual, status, matriz);
            break;
        default:
            printError("id, (", status, tokenAtual, matriz);
    }
}

void E(int *tokenAtual, int *status,int matriz[][43]) {
    if(*tokenAtual == NEW_LINE || *tokenAtual == 0) {
        if(*status == ACCEPTED) 
            *status = INCOMPLETE;
        return;
    }
    switch(*tokenAtual) {
     case ID:

        case L_PAREN:
            T(tokenAtual, status,matriz);E_Quote(tokenAtual, status,matriz);
            break;
        default:
            printError("id, (", status, tokenAtual, matriz);
    }
}

void E_Quote(int *tokenAtual, int *status,int matriz[][43]) {
    if(*tokenAtual == NEW_LINE || *tokenAtual == 0) {
        if(*status == ACCEPTED) 
            *status = INCOMPLETE;
        return;
    }
    switch(*tokenAtual) {
        case PLUS:
            eat(PLUS, tokenAtual, status, matriz);T(tokenAtual, status, matriz);E_Quote(tokenAtual, status, matriz);
            break;
        case R_PAREN:

        case EOL:
            break;
        default:
            printError("id, (", status, tokenAtual, matriz);
    }
}

parsingStatus S(int *tokenAtual, int *status,int matriz[][43]) {
    if(*tokenAtual == NEW_LINE || *tokenAtual == 0) {
        if(*status == ACCEPTED) 
            *status = INCOMPLETE;
        return *status;
    }
    switch(*tokenAtual) {
        case ID:

        case L_PAREN:
            E(tokenAtual, status, matriz);eat(EOL, tokenAtual, status, matriz);
            break;
        default:
            printError("id, (", status, tokenAtual, matriz);
    }
    return *status;
}