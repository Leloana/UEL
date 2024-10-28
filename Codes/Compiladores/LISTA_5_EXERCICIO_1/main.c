#include "main.h"

int main(void) {
    int edges[9][38] = {
        //{+,-,0-9,a-z}
        /*Estado 0*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*Estado 1*/ {3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        /*Estado 2*/ {0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        /*Estado 3*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*Estado 4*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*Estado 5*/ {0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*Estado 6*/ {7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*Estado 7*/ {0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        /*Estado 8*/ {0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    char buffer[256];
    int buffer_pos = 0;
    int state_atual = 1;
    FILE* arq = stdin; 
    char c = '\0';

     while (true) {
        c = fgetc(arq);
        bool first = false;
        while(c == '\n'){// Se quebrar linha, devo ignora-lo e checar se palavra ate agora é valida
            if(buffer_pos > 0){
                buffer[buffer_pos] = '\0';
                if (isFinalState(state_atual)) {
                        printf("%s\n", buffer);
                    } else {
                        printf("ERRO\n");
                }
                buffer_pos = 0;
                state_atual = 1;
                memset(buffer, '\0', strlen(buffer));
            }
            c = fgetc(arq);
            if(c == EOF){
                break;
            }
        }
        if(c == EOF)break;
        int char_index = charIndex(c);
                    // If the character is invalid, print ERRO
        if ( char_index == -1 || edges[state_atual][char_index] == 0) {
            first = true;
            if(state_atual == 1 && edges[state_atual][char_index]== 0){
                fseek(arq, 1, SEEK_CUR);
                first = false;
            }
            // Token complete or invalid character found
            buffer[buffer_pos] = '\0'; // Null-terminate the buffer

            if (buffer_pos > 0) {
                
                if (isFinalState(state_atual)) {
                    printf("%s\n", buffer);
                } else {
                    printf("ERRO\n");
                }
            }
            // Reset buffer and state
            buffer_pos = 0;
            state_atual = 1;
            memset(buffer, '\0', strlen(buffer));
            fseek(arq, -1, SEEK_CUR);

            if (char_index == -1 ) {
                if(first) fseek(arq, 1, SEEK_CUR);
                printf("ERRO\n", c);   
                first = false;
            }
        } else {
            // Valid character, update state and buffer
            buffer[buffer_pos++] = c;
            state_atual = edges[state_atual][char_index];
        }  
    }
    if(buffer_pos > 0){
        buffer[buffer_pos] = '\0';
        if (isFinalState(state_atual)) {
                printf("%s\n", buffer);
            } else {
                printf("ERRO\n");
        }
        state_atual = 1;
    }
    return 0;
}