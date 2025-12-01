#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "checkPassword.h"

#define PASSWORD_LENGTH 12

void find_password_segment(int start) {
    char attempt[4] = {0}; // String de 3 caracteres + '\0'
    for (int i = 33; i <= 126; i++) {
        for (int j = 33; j <= 126; j++) {
            for (int k = 33; k <= 126; k++) {
                attempt[0] = i;
                attempt[1] = j;
                attempt[2] = k;
                if (checkPassword(attempt, start) == 0) {
                    printf("Processo %d com pai %d encontrou %d-%d: %s\n", getpid(),getppid(), start, start + 2, attempt);
                    return;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int use_fork = 0;

    // Verificar argumento de linha de comando
    if (argc > 1 && strcmp(argv[1], "-f") == 0) {
        use_fork = 1;
    }

    if (use_fork) {
        pid_t pids[4];
        int segments[4] = {0, 3, 6, 9};

        // Criar 4 processos filhos
        for (int i = 0; i < 4; i++) {
            pids[i] = fork();
            if (pids[i] == 0) { // Código do processo filho
                find_password_segment(segments[i]);
                exit(0);
            }
        }

        // Processo pai espera todos os filhos terminarem
        for (int i = 0; i < 4; i++) {
            wait(NULL);
        }

    } else {
        // Sem fork, verificar sequencialmente
        find_password_segment(0);
        find_password_segment(3);
        find_password_segment(6);
        find_password_segment(9);
    }

    return 0;
}
