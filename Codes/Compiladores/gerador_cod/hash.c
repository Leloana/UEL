#include "hash.h"
#include "ast.h"

extern int countDims(void *dimensions);

void **criaHash() {
    void **hashTable = calloc(HASH_SIZE, sizeof(HashNode));
    if (!hashTable) {
        printf("Erro ao alocar memoria para hash\n");
        exit(1);
    }
    return hashTable;
}

int hash(char *value) {
    int hash = 0;
    for (size_t i = 0; i < strlen(value); i++)
        hash += value[i] * (i + 1);
    return hash % HASH_SIZE;
}

void *insertHash(void **hashTable, char *varId, int currentType, int pointer) {
    int index = hash(varId);
    HashNode *aux = calloc(1, sizeof(HashNode));
    aux->typeVar = currentType;
    aux->varId = calloc(strlen(varId) + 1, sizeof(char));
    strcpy(aux->varId, varId);
    aux->pointer = pointer;
    aux->assign = 1;
    aux->sRegister = -1;

    HashNode *head = (HashNode *)hashTable[index];
    if (!head) {
        hashTable[index] = aux;
    } else {
        while (head->next)
            head = head->next;
        head->next = aux;
    }
    return aux;
}


void setIsGlobal(void *node) {
    HashNode *aux = node;
    aux->isGlobal = 1;
}

void setIsConstant(void *node) {
    HashNode *aux = node;
    aux->isConstant = 1;
}
void setParam(void *node, Param *p) {
    HashNode *aux = node;
    aux->param = p;
}

void setQntdParams(void *node, int qntdParams) {
    HashNode *aux = node;
    aux->qntdParams = qntdParams;
}



void setAssign(void *node, int assign) {
    HashNode *aux = node;
    aux->assign = assign;
}

void setDimss(void *node, void *dimensions) {
    HashNode *aux = node;
    aux->dimensions = dimensions;
    int qntdDimen = countDims(dimensions);
    aux->qntdDimen = qntdDimen;
    if (qntdDimen > 0) {
        aux->kind = VECTOR;
    } else {
        aux->kind = VAR;
    }
}

void setKind(void *node, int kind) {
    HashNode *aux = node;
    // printf("setting kind %s = %d %p\n", aux->varId, kind, node);
    aux->kind = kind;
}

void setHashExpr(void *node, void *hashExpr) {
    HashNode *aux = node;
    aux->hashExpr = hashExpr;
}

void setSRegisterInHash(void *node, int sRegister) {
    HashNode *aux = node;
    aux->sRegister = sRegister;
}

int lookForValueInHash(void **hashTable, char *varId, int currentType) {
    if (!hashTable) return 0;
    int index = hash(varId);
    int ocorrencias = 0;
    HashNode *head = (HashNode *)hashTable[index];
    // printf("\nlooking for varId: %s in %p\n", varId, hashTable);
    while (head) {
        if (!strcmp(varId, head->varId)) {  // existe outro daquele identificador na hash
            ocorrencias++;
            if (ocorrencias == 1) continue;      // se for o primeiro, continua
            if (currentType == head->typeVar) {  // se for do mesmo tipo
                freeHash(hashTable);
                exit(1);
            } else {  // se for de tipo diferente
                freeHash(hashTable);
                exit(1);
            }
        }
        head = head->next;
    }
    return 0;
}

int getSRegisterFromHash(void *node) {
    HashNode *aux = node;
    return aux->sRegister;
}


Param *criaParam(int type, char *identifier, int pointer, void *next) {
    Param *newParam = calloc(1, sizeof(Param));
    newParam->type = type;
    newParam->identifier = identifier;
    newParam->pointer = pointer;
    newParam->next = next;
    return newParam;
}

HashNode *getIdentifierNode(void **hashTable, char *id) {
    if (!hashTable) return NULL;
    int index = hash(id);
    HashNode *head = (HashNode *)hashTable[index];
    while (head) {
        // printf("head->value: %s %d\n", head->value, head->typeVar);
        if (!strcmp(id, head->varId)) return head;
        head = head->next;
    }
    return NULL;
}

char *getExactType(int type, int pointer) {
    char newType[50];
    switch (type) {
        case 275:  // int
        case 309:  // num_int
            strcpy(newType, "int");
            break;
        case 276:  // char
        case 313:  // character
            strcpy(newType, "char");
            break;
        case 277:  // void
            strcpy(newType, "void");
            break;
        case 312:  // string
            strcpy(newType, "char*");
            break;
        default:
            break;
    }
    for (int i = 0; i < pointer; i++) strcat(newType, "*");
    char *aux = calloc(strlen(newType) + 1, sizeof(char));
    strcpy(aux, newType);
    return aux;
}

void printProgram(void *AST) {
    void **hash = NULL;
    if (AST) {
        Program *ast = (Program *)AST;
        printf("AST %p\n", ast);
        hash = ast->hashTable;
    }
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *node = (HashNode *)hash[i];
        while (node) {
            printf("%d Global hash %s %d\n", i, node->varId, node->typeVar);
            node = node->next;
        }
    }

    printf("\n");
    Funcao *func = (Funcao *)((Program*)AST)->functionsList;
    while (func) {
        printf("Funcao %s %d hash %p\n", func->name, func->returnType, func->hashTable);

        for (int i = 0; i < HASH_SIZE; i++) {
            HashNode *node = (HashNode *)func->hashTable[i];
            while (node) {
                printf("%d Local hash var %s %d\n", i, node->varId, node->typeVar);
                node = node->next;
            }
        }
        printf("\n");
        Command *cmd = (Command *)func->commandList;
        while (cmd) {
            printf("Command %d\n", cmd->type);
            cmd = cmd->next;
        }
        printf("\n");
        func = func->next;
    }
}

void freeHash(void **hashTable) {
    if (!hashTable) return;
    for (int i = 0; i < HASH_SIZE; i++) {
        if (!hashTable[i]) continue;
        HashNode *head = hashTable[i];
        while (head) {
            HashNode *aux = head->next;
            if (head->param) {
                Param *p = head->param;
                while (p) {
                    Param *auxP = p->next;
                    free(p);
                    p = auxP;
                }
            }
            if (head->varId) free(head->varId);
            head->varId = NULL;
            free(head);
            head = aux;
        }
        hashTable[i] = NULL;
    }
    free(hashTable);
    hashTable = NULL;
}