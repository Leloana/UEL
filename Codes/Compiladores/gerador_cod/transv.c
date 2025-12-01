#include "transv.h"

int *tRegsAlive = NULL;

void escreveAST(Command *expr, void **hashTable, void **localHash, Program *programa, Funcao *funcAtual) {
    // printf(">> AST Comando %d %p %d\n", expr ? expr->type : -1, expr, expr->visited);
    if (!expr || expr->visited) return;
    expr->visited = 1;

    // printf("escreveAST %d %p %p\n",expr->type, expr, expr->next);
    // Para cada comando percorrer seus blocos de comandos e expressoes relacionadas recursivamente
    // Atencao as expressoes condicionais das estruturas, qua NAO PODEM ter expressoes de retorno tipo void
    Command *t = NULL;
    switch (expr->type) {
        case PRINTF:
            if (expr->auxPrint) {
                Expression *next = expr->auxPrint;
                Resultado *toPrint = NULL;
                char *restOfString = NULL;
                char *saidaSemTipo = calloc(strlen(expr->string) + 1, sizeof(char));
                strcpy(saidaSemTipo, expr->string + 1);  // copy the 7 string without the "
                while (next) {
                    toPrint = eval(next, hashTable, localHash, programa);
                    next = next->nextExpr;
                    if (toPrint) {
                        if (toPrint->auxIdNode) {
                            if (((HashNode *)toPrint->auxIdNode)->kind == VECTOR) {
                                toPrint->registerNumber = escreveLoadFromArray(toPrint->registerNumber);
                                toPrint->registerType = 0;
                            }
                        }
                    }

                    int escreveing = 0;
                    char *formatSpecifier = strstr(saidaSemTipo, "%d");  // pointer to the first occurrence of %d
                    if (formatSpecifier) {
                        escreveing = INT;
                    } else {
                        formatSpecifier = strstr(saidaSemTipo, "%s");
                        if (formatSpecifier) {
                            escreveing = STRING;
                        } else {
                            formatSpecifier = strstr(saidaSemTipo, "%c");
                            if (formatSpecifier) {
                                escreveing = CHAR;
                            }
                        }
                    }
                    if (restOfString) free(restOfString);
                    restOfString = calloc(strlen(formatSpecifier) + 1, sizeof(char));
                    strcpy(restOfString, formatSpecifier + 2);
                    restOfString[strlen(restOfString)] = '\0';
                    if (formatSpecifier != NULL) *formatSpecifier = '\0';  // Null-terminate the string at the format specifier
                    escreveString(saidaSemTipo, abs((int)((intptr_t)toPrint)));
                    if (escreveing == INT) escreveInteger(toPrint->registerType, toPrint->registerNumber);
                    else if (escreveing == CHAR) escreveCharacter(toPrint->registerType, toPrint->registerNumber);
                    else if (escreveing == STRING) escreveStringVar(toPrint->registerType, toPrint->registerNumber);
                    free(saidaSemTipo);
                    saidaSemTipo = calloc(strlen(restOfString) + 1, sizeof(char));
                    strcpy(saidaSemTipo, restOfString);
                }
                if (strlen(restOfString) > 0) {
                    restOfString[strlen(restOfString) - 1] = '\0';
                    // printf("4.rest %s\n", restOfString);
                    escreveString(restOfString, rand() % 67282);
                }
                if (restOfString) free(restOfString);
                if (saidaSemTipo) free(saidaSemTipo);

            } else {
                // remove the " " from the string
                // printf("2.String original %s\n", expr->string);
                char *fixedString = calloc(strlen(expr->string) - 1, sizeof(char));
                strncpy(fixedString, expr->string + 1, strlen(expr->string) - 2);
                fixedString[strlen(expr->string) - 2] = '\0';  // Null-terminate the string
                escreveString(fixedString, abs((int)((intptr_t)expr->string)));
                free(fixedString);
            }
            break;

        case DO_WHILE:
        case WHILE:
            int whileLine = abs((int)((intptr_t)expr));
            if (expr->type == WHILE)
                escreveJump("while_teste_", whileLine);
            escreveLabel("while_corpo_", whileLine);
            t = expr->then;
            while (t) {
                escreveAST(t, hashTable, localHash, programa, funcAtual);
                t = t->next;
            }
            escreveLabel("while_teste_", whileLine);
            Resultado *whileResult = NULL;
            whileResult = eval(expr->condition, hashTable, localHash, programa);
            escreveWhile(whileResult->registerType, whileResult->registerNumber, whileLine);
            break;

        case IF:
            Resultado *ifResult = eval(expr->condition, hashTable, localHash, programa);
            // printf("ifs %p\n", expr);

            int ifLine = abs((int)((intptr_t)expr->then));
            int elseLine = -1;
            if (expr->elseStatement) {
                elseLine = abs((int)((intptr_t)expr->elseStatement));
            } else {
                elseLine = ifLine;
            }
            escreveIf(ifResult->registerType, ifResult->registerNumber, elseLine);
            t = expr->then;
            while (t) {
                escreveAST(t, hashTable, localHash, programa, funcAtual);
                t = t->next;
            }
            escreveJump("exit_if_", ifLine);
            escreveLabel("else_", elseLine);
            Command *t2 = expr->elseStatement;
            while (t2) {
                escreveAST(t2, hashTable, localHash, programa, funcAtual);
                t2 = t2->next;
            }
            escreveLabel("exit_if_", ifLine);
            break;


        case FOR:
            int forLine = abs((int)((intptr_t)expr));
            eval(expr->init, hashTable, localHash, programa);
            escreveJump("for_teste_", forLine);
            escreveLabel("for_corpo_", forLine);
            t = expr->then;
            while (t) {
                escreveAST(t, hashTable, localHash, programa, funcAtual);
                t = t->next;
            }
            eval(expr->increment, hashTable, localHash, programa);
            escreveLabel("for_teste_", forLine);
            Resultado *forResult = NULL;
            forResult = eval(expr->condition, hashTable, localHash, programa);
            escreveFor(forResult->registerType, forResult->registerNumber, forLine);
            break;

        case RETURN:
            if (funcAtual->returnType == VOID && funcAtual->pointer == 0) {
                if (expr->condition) printf("Erro: Função %s não pode retornar valor\n", funcAtual->name);
                if (strcmp(funcAtual->name, "main")) {  // doesnot escreve jr $ra for main
                    loadFromStack();
                    loadTRegisters(tRegsAlive);
                    // free(tRegsAlive);
                    escreveReturn();
                }
            } else {
                if (!expr->condition) printf("Erro: Função %s deve retornar valor\n", funcAtual->name);
                Resultado *returnAux = eval(expr->condition, hashTable, localHash, programa);
                if (returnAux->auxIdNode) {
                    // printf("\n>>>>> varId %s %d\n", ((HashNode*)returnAux->auxIdNode)->varId, ((HashNode*)returnAux->auxIdNode)->sRegister);
                    if (((HashNode *)returnAux->auxIdNode)->sRegister == -1) {
                        int null = escreveConstant(0);
                        int s = escreveAssignment(0, null);
                        setSRegisterInHash((HashNode *)returnAux->auxIdNode, s);
                        returnAux->registerType = 1;
                        returnAux->registerNumber = s;
                    }
                }
                escreveReturnToV0(returnAux->registerType, returnAux->registerNumber);
                if (strcmp(funcAtual->name, "main")) {
                    loadFromStack();
                    loadTRegisters(tRegsAlive);
                    // free(tRegsAlive);
                    escreveReturn();
                }  // doesnot escreve jr $ra for main
            }
            break;
        
        case SCANF:
            HashNode *node = getIdentifierNode(localHash, expr->identifier);
            if (!node) node = getIdentifierNode(hashTable, expr->identifier);
            if (!node) printf("Erro: Variável %s não declarada no scanf\n", expr->identifier);

            int sReg = escreveScanInt(node->sRegister, node->varId, node->isGlobal);
            node->sRegister = sReg;
            break;

        case EXIT:
            if (expr->condition) {
                Resultado *status = eval(expr->condition, hashTable, localHash, programa);
                printf("\t# exit with status %d", status->assign);
                escreveExit();
            }
            break;

        case LISTA_EXP_COMANDO:
            // printf("expr %p %p (%d)\n", expr, expr->condition, expr->condition->type);
            eval(expr->condition, hashTable, localHash, programa);
            escreveAST(expr->next, hashTable, localHash, programa, funcAtual);
            break;

        default:
            printf("Erro: Comando desconhecido!\n");
            break;
    }
}

void procuraVar(void **hashTable, void **localHash, Program *programa) {
    if (!localHash) return;
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *node = (HashNode *)localHash[i];
        Resultado *atrib = NULL;
        while (node) {
            // printf("evaluanting hash %s %d %d \n", node->varId, node->kind, node->isGlobal);
            if (node->kind == FUNCTION || node->isConstant) {
                node = node->next;
                continue;
            }
            if (localHash == hashTable) {  // save globals to memory
                node->isGlobal = 1;
                int size = 0;
                if (node->kind == VAR) {
                    if (node->typeVar == NUM_INT || node->typeVar == INT || node->typeVar == VOID || node->pointer > 0)
                        size = 32;
                    else
                        size = 8;
                    escreveGlobalVariableInMemory(size, node->varId);
                }
            }

            if (node->kind == VECTOR) {
                Dims *d = node->dimensions;
                int size = 0;
                while (d) {
                    size = size + d->size;
                    d = d->next;
                }
                // printf(">>>| size of %s = %d\n", node->varId, size);
                int s = escreveDeclareArray(node->varId, size, node->isGlobal);
                setSRegisterInHash(node, s);
            }

            if (node->hashExpr) {
                // printf(">>>>>>>>>>>>>> this noda has atrib expr %p %s = %p %d\n", node, node->varId, node->hashExpr, ((Expression*)node->hashExpr)->type);
                atrib = eval(node->hashExpr, hashTable, localHash, programa);
                // printf("<<<<<<<<<<<<<< retornou %d %d %d %s\n\n", atrib->typeVar, atrib->pointer, atrib->assign, atrib->str);

                int assignType, assignPointer = atrib->pointer;
                // printf("\nassignType %d %d\n", atrib->typeVar, atrib->assign);
                if (atrib->typeVar == CHAR) {
                    assignType = CHAR;
                } else if (atrib->typeVar == INT) {
                    assignType = INT;
                } else if (atrib->typeVar == STRING) {
                    assignType = CHAR;
                    assignPointer = 1;
                } else {
                    assignType = VOID;
                }

                if (hashTable == localHash) {  // globals must be stored and loaded in and not to $s register
                    // printf("nao to sabendo carregar variaveis globais ja inicializas :D %s = %d\n", node->varId, atrib->assign);
                    setGlobalVarAssign(node->varId, atrib->assign);

                } else {
                    if (assignType == CHAR && assignPointer == 1) {  // string
                        atrib->str[strlen(atrib->str) - 1] = '\0';
                        strcpy(atrib->str, atrib->str + 1);
                        int regS = escreveDeclareString(node->varId, atrib->str);
                        setSRegisterInHash(node, regS);
                        strcpy(node->string, atrib->str);

                    } else {
                        int regS = escreveAssignment(atrib->registerType, atrib->registerNumber);
                        setSRegisterInHash(node, regS);
                        setAssign(node, atrib->assign);
                    }
                }
            }
            node = node->next;
        }
    }
}

int percorreAST(Program *programa) {
    if (!programa) return -1;

    // Percorra as funções na lista de funções
    inicio();
    printf("\n.data\n");
    escreveDefines();
    procuraVar(programa->hashTable, programa->hashTable, programa);  // loading global variables (defines not include)
    printf(".text\n\n");

    Funcao *funcAtual = programa->functionsList;
    while (funcAtual != NULL) {
        for (int i = 0; i < 10; i++) freeRegister(0, i);
        for (int i = 0; i < 8; i++) freeRegister(1, i);
        HashNode *funcNode = getIdentifierNode(programa->hashTable, funcAtual->name);
        escreveFuncaos(funcAtual->name);
        if (strcmp(funcAtual->name, "main")) {  // if not in main save context
            tRegsAlive = calloc(10, sizeof(int));
            storeTRegisters(tRegsAlive);
            storeInStack();
        } else {
            escreveGlobalVarAssign();
        }
        // printf("Funcao: %s (%d) %p has hash %p\n", funcAtual->name, funcNode->qntdParams, funcAtual, funcAtual->hashTable);
        escreveFuncaoParams(funcAtual->name, funcNode->qntdParams);
        procuraVar(programa->hashTable, funcAtual->hashTable, programa);
        // Percorra os comandos na função
        Command *expr = funcAtual->commandList;
        while (expr != NULL) {
            // printf(">>>>>>> %p %d %s\n", expr, expr->type, funcAtual->name);
            escreveAST(expr, programa->hashTable, funcAtual->hashTable, programa, funcAtual);
            expr = expr->next;
        }
        if (strcmp(funcAtual->name, "main")) {  // does not escreve jr $ra return for main
            loadFromStack();
            loadTRegisters(tRegsAlive);
            free(tRegsAlive);
            escreveReturn();
        }
        funcAtual = funcAtual->next;
    }
    return 0;
}

