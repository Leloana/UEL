#include "main.h"

int main(void) {
    int edges[14][41] = {
        /*{-,.,0-9,a-z,' ','\n', other}*/
        /*Estado 0*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0},
        /*Estado 1*/ {9, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,12,13,13},
        /*Estado 2*/ {0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0,0,0},
        /*Estado 3*/ {0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0,0,0},
        /*Estado 4*/ {0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0,0,0},
        /*Estado 5*/ {0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0},
        /*Estado 6*/ {0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0},
        /*Estado 7*/ {0, 8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0},
        /*Estado 8*/ {0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0},
        /*Estado 9*/ {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0},
        /*Estado 10*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0,11,0},
        /*Estado 11*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0},
        /*Estado 12*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,0,0},
        /*Estado 13*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0},
    };

    char buffer[256];
    int buffer_pos = 0;
    int state_atual = 1;
    FILE* arq = stdin; 
    char c = '\0';
     while (true) {
        c = fgetc(arq);
        if(c == EOF)break;
        bool first = false;
        int char_index = charIndex(c);
        //SE O ESTADO ATUAL NAO FOR COMENTARIO ENTAO DEVO IGNORAR OS \n
        if(state_atual != 10){
            while(c == '\n'){
                c = fgetc(arq);
                if(c == EOF)break;
            }
            if(c == EOF)break;
        }
        //OS CRITERIOS DE PARADA SAO CARACTERES DESCONHECIDOS E O FIM DE UM CAMIMNHO
        if ( char_index == 40 || edges[state_atual][char_index] == 0) {
            first = true;
            //CHECA SE É A PRIMEIRA VEZ QUE ESTA ANALISANDO UM CARACTERE OU NAO
            if(state_atual == 1 && edges[state_atual][char_index] == 0 ){
                fseek(arq, 1, SEEK_CUR);
                first = false;
            }
            // Token complete or invalid character found
            buffer[buffer_pos] = '\0'; // Null-terminate the buffer

            if (buffer_pos > 0) {
                if (isFinalState(state_atual)) {
                    if(state_atual == 11)buffer[buffer_pos-1] = '\0';
                    if(state_atual != 12)printf("%s", buffer);
                    wich_state(state_atual);
                } else {
                    printf("error\n");
                }
            }
            // Reset buffer and state 
            buffer_pos = 0;
            state_atual = 1;
            fseek(arq, -1, SEEK_CUR);
            memset(buffer, '\0', strlen(buffer));

            // If the character is invalid, print ERRO
            if (char_index == 40) {
                if(first) fseek(arq, 1, SEEK_CUR);
                printf("%c", c);
                wich_state(edges[state_atual][char_index]);
                first = false;
            }
        } else {
            // Valid character, update state and buffer         
            buffer[buffer_pos] = c;
            buffer_pos ++;
            state_atual = edges[state_atual][char_index];
        }     
    }
    buffer[buffer_pos] = '\0';//Finaliza buffer
    if (isFinalState(state_atual)) {//Checa se estado atual é final
        if(state_atual == 11)buffer[buffer_pos-1] = '\0';
        if(state_atual != 12)printf("%s", buffer);
            wich_state(state_atual);
    } else {
            printf("error\n");
    }
    state_atual = 1;
    return 0;
}