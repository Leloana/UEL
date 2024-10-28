#include "pilha.h"

// Função que inicializa a pilha, alocando memória e retornando o ponteiro para a pilha vazia
void *inicializaPilha() {
    Pilha *p = calloc(1, sizeof(Pilha));  // Aloca a pilha e zera seus campos
    return p;  // Retorna o ponteiro para a pilha inicializada
}

// Função que insere um nó na pilha com os valores fornecidos
void insertNode(Pilha *p, int valor, int lin, int col, char *token) {  
    Node *aux = calloc(1, sizeof(Node));  // Aloca memória para um novo nó e zera seus campos
    aux->col = col;      // Define a coluna associada ao nó
    aux->lin = lin;      // Define a linha associada ao nó
    aux->valor = valor;  // Define o valor do nó

    // Se o valor não for 19 e o token começar com '/', ajusta o ponteiro da string para ignorar o '/'
    if(valor != 19 && token[0] == '/') token++;

    // Aloca espaço para armazenar o token Node nó
    aux->token = calloc(strlen(token) + 1, sizeof(char));
    // Copia o conteúdo do token fornecido para o campo do nó
    strcpy(aux->token, token);

    // Se a pilha estiver vazia, o novo nó será o topo
    if(!p->topo) {
        p->topo = aux;  // O novo nó é o topo da pilha
    } else {
        // Caso contrário, insere o novo nó Node final da pilha
        Node *aux2 = p->topo;  // Inicializa auxiliar com o topo da pilha
        // Percorre a pilha até encontrar o último nó
        while(aux2->prox) {
            aux2 = aux2->prox;
        }
        // O próximo nó do último nó agora será o novo nó
        aux2->prox = aux;
    }
}

// Função que remove o nó do topo da pilha
void removeNode(Pilha *p) {  
    if(!p->topo) {  // Verifica se a pilha está vazia
        return;  // Se estiver vazia, não faz nada
    } else {
        Node *aux = p->topo;  // Armazena o nó do topo da pilha em um auxiliar
        p->topo = aux->prox;  // Atualiza o topo da pilha para o próximo nó
        if(aux->token)free(aux->token);  // Se o nó tiver um token associado
              // Libera a memória do token
        free(aux);  // Libera a memória do nó removido
    }
}

// Função que retorna o valor armazenado Node topo da pilha
int getNode(Pilha *p) {
    if(!p->topo)return -1;  // Verifica se a pilha está vazia
    // Retorna -1 se estiver vazia
    return p->topo->valor;  // Retorna o valor do nó Node topo da pilha
}

// Função que retorna a linha associada ao nó Node topo da pilha
int getLinha(Pilha *p) {
    if(!p->topo) return -1;  // Verifica se a pilha está vazia
         // Retorna -1 se estiver vazia
    return p->topo->lin;  // Retorna a linha do nó Node topo da pilha
}

// Função que retorna a coluna associada ao nó Node topo da pilha
int getColuna(Pilha *p) {
    if(!p->topo)return -1;  // Verifica se a pilha está vazia
    // Retorna -1 se estiver vazia
    return p->topo->col;  // Retorna a coluna do nó Node topo da pilha
}

// Função que retorna o token associado ao nó Node topo da pilha
char *getToken(Pilha *p) {
    if(!p->topo) return NULL;  // Verifica se a pilha está vazia
    // Retorna NULL se estiver vazia
    return p->topo->token;  // Retorna o token do nó Node topo da pilha
}

// Função que imprime os valores da pilha a partir do topo
void printPilha(Pilha *p) {
    Node *aux = p->topo;  // Inicializa auxiliar com o topo da pilha
    // Percorre a pilha do topo até o final (NULL)
    while(aux != NULL) {
        printf("%d ", aux->valor);  // Imprime o valor do nó atual
        aux = aux->prox;  // Avança para o próximo nó
    }
    printf("\n");  // Quebra de linha após a impressão dos valores
}

// Função que libera a memória de todos os nós da pilha
void freePilha(Pilha *p) {
    Node *aux = p->topo;  // Inicializa auxiliar com o topo da pilha
    // Percorre a pilha liberando memória nó por nó
    while(aux != NULL) {
        Node *remove = aux->prox;  // Armazena o próximo nó antes de liberar o atual
        if(aux) {  // Verifica se o nó atual é válido
            if(aux->token)free(aux->token);  // Se o nó tiver um token
            // Libera a memória do token
            free(aux);  // Libera a memória do nó atual
        }
        aux = remove;  // Avança para o próximo nó
    }
    if(p)free(p);  // Verifica se a pilha é válida
    // Libera a memória da estrutura da pilha
}
