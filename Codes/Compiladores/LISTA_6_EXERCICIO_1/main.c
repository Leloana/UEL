#include "main.h"

int main(void) {
    // Matriz de transições do autômato
    int edges[23][20] = {
        /*{+,-,0-9,h,e,r,i,s,c,a,t}*/
        /*Estado 0*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        /*Estado 1*/ {17,18,19,19,19,19,19,19,19,19,19,19,2,0,0,0,4,11,0,0},
        /*Estado 2*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,7,0,0,0,0},
        /*Estado 3*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0},
        /*Estado 4*/ {0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0},
        /*Estado 5*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0},
        /*Estado 6*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        /*Estado 7*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0},
        /*Estado 8*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        /*Estado 9*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0},
        /*Estado 10*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        /*Estado 11*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0},
        /*Estado 12*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,14,0,0,0,0,13},
        /*Estado 13*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,0,0,0},
        /*Estado 14*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,0},
        /*Estado 15*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        /*Estado 16*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        /*Estado 17*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        /*Estado 18*/ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        /*Estado 19*/ {0,0,19,19,19,19,19,19,19,19,19,19,0,20,0,0,0,0,0,0},
        /*Estado 20*/ {21,21,22,22,22,22,22,22,22,22,22,22,0,0,0,0,0,0,0,0},
        /*Estado 21*/ {0,0,22,22,22,22,22,22,22,22,22,22,0,0,0,0,0,0,0,0},
        /*Estado 22*/ {0,0,22,22,22,22,22,22,22,22,22,22,0,0,0,0,0,0,0,0}
    };

    // Buffer para armazenar a sequência de caracteres
    char buffer[256];
    int buffer_pos = 0;
    int state_atual = 1;
    FILE* arq = stdin; 
    char c = '\0';
    bool erro = false;
    int pathFollowed[1024];

    while (true) {
        c = fgetc(arq);  // Lê um caractere do arquivo
        if (buffer_pos == 0 && c == EOF) break;  // Termina se o arquivo estiver vazio no início
        endFile(c, arq, erro);  // Função auxiliar para verificar o fim do arquivo
        erro = false;
        bool check = true;

        int char_index = 1000;
        if (c != EOF) char_index = charIndex(c);  // Converte o caractere em um índice da matriz de transições

        if (char_index == -1 || edges[state_atual][char_index] == 0 || c == EOF) {
            // Se o caractere não for reconhecido, ou não houver transição, ou for fim do arquivo
            buffer[buffer_pos] = '\0';
            pathFollowed[buffer_pos] = -1;

            if (buffer_pos > 0) {
                if (isFinalState(state_atual)) {
                    // Se o estado atual for um estado final, imprime a sequência reconhecida
                    check = true;
                    wich_state(state_atual);  // Função auxiliar para imprimir o estado
                    if (c != EOF && state_atual != 19 && state_atual != 22) printf("\n");
                    if ((state_atual == 19 || state_atual == 22) && !endFile(c, arq, erro)) printf(" %s\n", buffer);
                    if ((state_atual == 19 || state_atual == 22) && endFile(c, arq, erro)) printf(" %s", buffer);
                    if (c == EOF) break;
                } else {
                    // Se o estado atual não for um estado final, retrocede e tenta outra transição
                    while (!isFinalState(pathFollowed[buffer_pos - 1])) {
                        buffer_pos--;
                        buffer[buffer_pos] = '\0';
                        if (buffer_pos <= 0) break;
                        fseek(arq, -1, SEEK_CUR);  // Retrocede no arquivo
                    }
                    if (buffer_pos > 0 && isFinalState(pathFollowed[buffer_pos - 1])) {
                        // Se encontrar um estado final durante a retrocessão, imprime a sequência reconhecida
                        state_atual = pathFollowed[buffer_pos - 1];
                        wich_state(state_atual);
                        if (state_atual != 19 && state_atual != 22) printf("\n");
                        if (state_atual == 19 || state_atual == 22) printf(" %s\n", buffer);
                        check = false;
                    } else {
                        // Se não encontrar um estado final, imprime erro
                        printf("ERRO\n");
                        buffer_pos = -1;
                        if (c == '\n' || c == ' ') check = false;
                    }
                }
            }
            fseek(arq, -1, SEEK_CUR);  // Retrocede no arquivo
            if (char_index == -1 || buffer_pos == 0) {
                if (check) fseek(arq, 1, SEEK_CUR);
                if (c != '\n' && c != ' ') {
                    printf("ERRO");
                    erro = true;
                }
            }
            buffer_pos = 0;
            state_atual = 1;
        } else {
            // Se houver transição, atualiza o estado e o buffer
            state_atual = edges[state_atual][char_index];
            pathFollowed[buffer_pos] = state_atual;
            buffer[buffer_pos++] = c;
        }
    }
    return 0;
}
