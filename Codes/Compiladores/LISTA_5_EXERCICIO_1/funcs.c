#include "funcs.h"

int charIndex(char c) {
    if (c == '+') return 0;
    if (c == '-') return 1;
    if (c >= '0' && c <= '9') return c-47;
    if (c >= 'a' && c <= 'z') return c - 'a' + 12;
    return -1; // Invalid character
}

int isFinalState(int state) {
    if(state == 2 || state == 3 || state == 4|| state == 5|| state == 8){
        return true;
    }
    else return false;
}


