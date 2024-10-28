#include "funcs.h"

int charIndex(char c) {
    if (c == '-') return 0;
    if (c == '.') return 1;
    if (c >= '0' && c <= '9') return c-46;
    if (c >= 'a' && c <= 'z') return c - 'a' + 12;
    if (c == ' ') return 38;
    if(c == '\n')return 39;
    return 40; // Invalid character
}

int isFinalState(int state) {
    if(state == 2 || state == 3 || state == 4|| state == 5|| state == 6|| state == 7|| state == 8|| state == 9 || state == 11 || state == 12 || state == 13){
        return true;
    }
    else return false;
}

void wich_state(int num){
    if(num == 2 ||num == 4)printf(" ID\n"); 
    else if(num == 3 )printf(" IF\n"); 
    else if(num == 5 ||num == 9 ||num == 13)printf(" error\n"); 
    else if(num == 6 ||num == 8 )printf(" REAL\n"); 
    else if(num == 7 )printf(" NUM\n"); 
    else if(num == 11 )printf(" comment\n"); 
    else if(num == 12 )printf("white space\n"); 
}