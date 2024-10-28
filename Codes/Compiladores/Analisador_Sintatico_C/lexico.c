#include "lexico.h"

char* getNewToken(char* tokens, int atual){
    char* aux = calloc(strlen(tokens), sizeof(char));
    *aux = tokens[atual+1];
    return aux;
}

void erroLexico(void *pilhaSintatico, char *palavra, int lin, int col, bool *changeToken, bool *flagLexico, char *token){
    if(*flagLexico) return;  // Verifica se já houve um erro léxico
    if(palavra[col] == 10 || palavra[col] == 32)return;  // Ignora espaços e quebras de linha

    if(*changeToken) printf("\n");  // Imprime nova linha se necessário

    // Exibe mensagem de erro léxico
    printf("ERRO LEXICO. Linha: %d Coluna: %d -> '%c'", lin, col + 1, palavra[col]);
    
    freePilha(pilhaSintatico);  // Libera recursos da pilha sintática
    free(palavra);  // Libera memória da palavra
    free(token);    // Libera memória do token
    *changeToken = true;  // Marca que o token foi alterado
    *flagLexico = true;  // Marca que houve erro léxico
    exit(1);  // Encerra o programa
}

int charIndex(char *tokens, char palavra) {
    // Procura o índice do caractere 'palavra' no array 'tokens'
    for(int i = 0; i < N_ALF; i++) {
        if(tokens[i] == palavra) return i;  // Retorna índice encontrado
    }
    return -1;  // Caso não encontre o caractere
}

bool isFinalState(int *estadosF, int estadoAtual) {
    // Verifica se o estadoAtual é um estado final
    for(int i = 0; i < N_FINAL; i++){  
        if(estadosF[i] == estadoAtual) return true;  // Retorna true se encontrar
    }
    return false;  // Retorna false se não for um estado final
}

void reiniciaVar(int *indice, int newCursor, int *cursorInicio, int *final, int *estadoAtual) {
    *indice = newCursor;  // Atualiza o cursor
    *cursorInicio = *indice;  // Reseta o cursor de início
    *final = -1;  // Reseta a posição final do token
    *estadoAtual = 1;  // Reseta o estado para o inicial
}
