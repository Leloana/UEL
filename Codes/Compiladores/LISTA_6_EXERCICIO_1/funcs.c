#include "funcs.h"


int charIndex(char c) {
    /*{+,-,0-9,h,e,r,i,s,c,a,t}*/
    if (c == '+') return 0;
    if (c == '-') return 1;
    if (c >= '0' && c <= '9') return c-46;
    if(c == 'h') return 12;
    if(c == 'e') return 13;
    if(c == 'r') return 14;
    if(c == 'i') return 15;
    if(c == 's') return 16;
    if(c == 'c') return 17;
    if(c == 'a') return 18;
    if(c == 't') return 19;

    return -1; // Invalid character
}

int isFinalState(int state) {
    if(state == 17 || state == 18 || state == 19 || state == 3 || state == 22 || state == 10 || state == 8 || state == 6 || state == 13 || state == 15 || state == 14 || state == 16){
        return true;
    }
    else return false;
}

bool endFile(int c, FILE* arq, bool erro) {
    int i = 0;
    int next = c;
    while (next == '\n' || next == ' ') {
        next = fgetc(arq);
        i++;
    }
    if (next == EOF) return true;
    else fseek(arq, -i, SEEK_CUR);

    if (next != EOF && erro) printf("\n");

    return false;
}

void wich_state(int num){
    if(num == 17 )printf("MAIS"); 
    else if(num == 18 )printf("MENOS"); 
    else if(num == 19 )printf("INTEIRO"); 
    else if(num == 22 )printf("REAL"); 
    else if(num == 3 )printf("ELE"); 
    else if(num == 10 )printf("DELA"); 
    else if(num == 6 )printf("ELA"); 
    else if(num == 8 )printf("DELE"); 
    else if(num == 13 )printf("GATO"); 
    else if(num == 15 )printf("GATOS"); 
    else if(num == 14 )printf("CARRO");
    else if(num == 16 )printf("CARROS"); 
}

