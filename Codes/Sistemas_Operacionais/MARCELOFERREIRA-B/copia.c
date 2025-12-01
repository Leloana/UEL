#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo origem> <arquivo destino>\n", argv[0]);
        return 1;
    }

    FILE *arquivoOrigem = fopen(argv[1], "rb");
    if (!arquivoOrigem) {
        perror("Erro ao abrir o arquivo origem");
        return 1;
    }

    FILE *arquivoDestino = fopen(argv[2], "wb");
    if (!arquivoDestino) {
        perror("Erro ao criar o arquivo destino");
        fclose(arquivoOrigem);
        return 1;
    }

    char buffer[1024];
    size_t bytesLidos;

    while ((bytesLidos = fread(buffer, 1, sizeof(buffer), arquivoOrigem)) > 0) {
        fwrite(buffer, 1, bytesLidos, arquivoDestino);
    }

    fclose(arquivoOrigem);
    fclose(arquivoDestino);

    printf("Cópia concluída com sucesso.\n");
    return 0;
}
