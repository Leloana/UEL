#include "eval.h"

int inAtrib = 0;

Resultado *eval(Expression *expr, void **listaHash, void **localHash, Program *program) {
    if (!expr) return NULL;

    Resultado *left = NULL;
    Resultado *right = NULL;
    Resultado *result = NULL;
    HashNode *hashNode = NULL;
    HashNode *hashNodeTemp = NULL;
    HashNode *auxIdNode = NULL;
    int leftType, rightType;
    int leftReg, rightReg;
    int tReg, regS;  // auxiliares

    switch (expr->type) {
        case PRIMARIA:  // tipo 1 de expr

            switch (expr->operator) {
                case INT:
                case CHAR:
                    result = criaResultado(expr->type, expr->pointer, expr->assign);
                    int regT = escreveConstant(result->assign);
                    result->registerType = 0;
                    result->registerNumber = regT;
                    return result;
                    break;

                case STRING:
                    result = criaResultado(STRING, 0, 0);
                    strcpy(result->str, expr->string);
                    // printf("1. string na ast %s \n", result->str);
                    return result;
                    break;

                case ID:
                    hashNode = getIdentifierNode(localHash, expr->identifier);
                    if (!hashNode) hashNode = getIdentifierNode(listaHash, expr->identifier);
                    if (!hashNode) printf("Erro: Variável %s não declarada\n", expr->identifier);

                    if (hashNode->typeVar == VOID) {
                        result = criaResultado(VOID, hashNode->pointer, hashNode->assign);
                        if (hashNode->kind == VECTOR) result->pointer = 1;
                        result->auxIdNode = hashNode;
                        if (hashNode->isConstant || hashNode->isGlobal) {
                            if (!inAtrib && hashNode->kind != VECTOR) {
                                result->registerNumber = escreveLoadIntGlobal(hashNode->varId);
                                result->registerType = 0;
                            }
                        } else {
                            if (hashNode->pointer > 0) {
                                result->registerType = 1;
                                result->registerNumber = hashNode->sRegister;
                            }
                        }
                        return result;

                    } else if (hashNode->typeVar == INT || (hashNode->typeVar == CHAR && hashNode->pointer == 0)) {
                        result = criaResultado(hashNode->typeVar, hashNode->pointer, hashNode->assign);
                        if (hashNode->kind == VECTOR) result->pointer = 1;
                        result->auxIdNode = hashNode;
                        if (hashNode->isConstant || hashNode->isGlobal) {
                            if (!inAtrib && hashNode->kind != VECTOR) {
                                result->registerNumber = escreveLoadIntGlobal(hashNode->varId);
                                result->registerType = 0;
                            }
                        } else {
                            result->registerType = 1;
                            result->registerNumber = hashNode->sRegister;
                        }
                        return result;
                        break;

                    } else if (hashNode->typeVar == CHAR && hashNode->pointer == 1) {
                        result = criaResultado(CHAR, 1, 0);
                        strcpy(result->str, expr->string);
                        result->auxIdNode = hashNode;
                        result->registerType = 1;
                        result->registerNumber = hashNode->sRegister;
                        return result;
                        break;
                    }
                    break;

                default:
                    printf("Erro: Expressao primaria desconhecida\n");
                    break;
            }

        __attribute__((fallthrough));
        
        case BOP:  // tipo 2 de expr
            if (expr->left->operator== ASSIGN) inAtrib = 1;
            left = eval(expr->left, listaHash, localHash, program);
            if (expr->left->operator== ASSIGN) inAtrib = 0;
            right = eval(expr->right, listaHash, localHash, program);

            leftType = left->registerType;
            leftReg = left->registerNumber;
            rightType = right->registerType;
            rightReg = right->registerNumber;
            
            switch (expr->operator) {
                case ASSIGN:
                    result = criaResultado(left->typeVar, left->pointer, right->assign);

                    if ((left->typeVar == INT || left->typeVar == VOID) && left->pointer == 1 && right->pointer == 1) {
                        // printf("error:minhacabecafritou:\n");
                        int s = escreveAssignAddress(left->registerType, left->registerNumber, ((HashNode *)left->auxIdNode)->varId);
                        setSRegisterInHash(((HashNode *)left->auxIdNode), s);
                        result->registerType = 1;
                        result->registerNumber = s;
                        return result;
                    }

                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }

                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        // printf("VECTOR ASSIGN $ t %d \n", left->registerNumber);
                        escreveStoreIntoArray(left->registerNumber, rightType, rightReg);
                        result->registerType = 0;
                        regS = left->registerNumber;

                    } else if (left->auxIdNode && ((HashNode *)left->auxIdNode)->isGlobal) {
                        // printf("STORING INTO GLOBAL VARIABLE = \n");
                        freeRegister(left->registerType, left->registerNumber);
                        escreveStoreIntGlobal(rightType, rightReg, ((HashNode *)left->auxIdNode)->varId);
                        result->registerType = 0;

                    } else {
                        if (((HashNode *)left->auxIdNode)->sRegister == -1) {
                            // printf("%s sem sRegister\n", ((HashNode *)left->auxIdNode)->varId);
                            if (left->typeVar == CHAR && left->pointer == 1) {
                                right->str[strlen(right->str) - 1] = '\0';
                                char aux[strlen(right->str) - 1];
                                strcpy(aux, right->str + 1);
                                for (size_t i = 0; i < strlen(right->str); i++) {
                                    right->str[i] = '\0';
                                }
                                strcpy(right->str, aux);
                                regS = escreveDeclareString(((HashNode *)left->auxIdNode)->varId, right->str);
                                result->registerType = 1;
                                result->registerNumber = regS;
                                ((HashNode *)left->auxIdNode)->sRegister = regS;
                                strcpy(((HashNode *)left->auxIdNode)->string, right->str);

                            } else {
                                if (expr->left->type == UOP) {
                                    escreveStoreInAddress(left->registerType, left->registerNumber, rightType, rightReg);

                                } else {
                                    regS = escreveAssignment(rightType, rightReg);
                                    ((HashNode *)left->auxIdNode)->sRegister = regS;
                                }
                            }

                        } else {
                            if (left->typeVar == CHAR && left->pointer == 1) {
                                // right->str[strlen(right->str) - 1] = '\0';
                                // strcpy(right->str, right->str + 1);
                                // regS = escreveDeclareString(((HashNode *)left->auxIdNode)->varId, right->str);
                                result->registerType = 1;
                                result->registerNumber = ((HashNode *)left->auxIdNode)->sRegister;
                                strcpy(((HashNode *)left->auxIdNode)->string, right->str);

                            } else {
                                if (expr->left->type == UOP) {
                                    escreveStoreInAddress(left->registerType, left->registerNumber, rightType, rightReg);

                                } else {
                                    regS = left->registerNumber;
                                    escreveAssignmentToReg(rightType, rightReg, regS);
                                }
                            }
                        }
                        result->registerType = 1;
                    }
                    result->registerNumber = regS;
                    hashNodeTemp = getIdentifierNode(localHash, expr->identifier);
                    if (!hashNodeTemp) hashNodeTemp = getIdentifierNode(listaHash, expr->identifier);
                    if (hashNodeTemp) setAssign(hashNodeTemp, result->assign);
                    hashNodeTemp = NULL;
                    return result;
                    break;

                case ADD_ASSIGN:
                    result = criaResultado(left->typeVar, left->pointer, left->assign + right->assign);
                    tReg = escreveArithmeticsOps(left->registerType, left->registerNumber, right->registerType, right->registerNumber, "add");

                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->isGlobal) {
                        // printf("STORING INTO GLOBAL VARIABLE += \n");
                        freeRegister(left->registerType, left->registerNumber);
                        escreveStoreIntGlobal(0, tReg, ((HashNode *)left->auxIdNode)->varId);
                        result->registerType = 0;
                        result->registerNumber = left->registerNumber;

                    } else {
                        escreveAssignmentToReg(0, tReg, left->registerNumber);
                        result->registerNumber = left->registerNumber;
                        result->registerType = left->registerType;
                    }
                    hashNodeTemp = getIdentifierNode(localHash, expr->identifier);
                    if (!hashNodeTemp) hashNodeTemp = getIdentifierNode(listaHash, expr->identifier);
                    if (hashNodeTemp) setAssign(hashNodeTemp, result->assign);
                    hashNodeTemp = NULL;
                    return result;
                    break;

                case MINUS_ASSIGN:
                    result = criaResultado(left->typeVar, left->pointer, left->assign - right->assign);
                    tReg = escreveArithmeticsOps(left->registerType, left->registerNumber, right->registerType, right->registerNumber, "sub");

                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->isGlobal) {
                        // printf("STORING INTO GLOBAL VARIABLE -= \n");
                        freeRegister(left->registerType, left->registerNumber);
                        escreveStoreIntGlobal(0, tReg, ((HashNode *)left->auxIdNode)->varId);
                        result->registerType = 0;
                        result->registerNumber = left->registerNumber;

                    } else {
                        escreveAssignmentToReg(0, tReg, left->registerNumber);
                        result->registerNumber = left->registerNumber;
                        result->registerType = left->registerType;
                    }
                    hashNodeTemp = getIdentifierNode(localHash, expr->left->identifier);
                    if (!hashNodeTemp) hashNodeTemp = getIdentifierNode(listaHash, expr->left->identifier);
                    if (hashNodeTemp) setAssign(hashNodeTemp, result->assign);
                    hashNodeTemp = NULL;
                    return result;
                    break;

                case PLUS:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(left->typeVar, left->pointer, left->assign + right->assign);
                    tReg = escreveArithmeticsOps(leftType, leftReg, rightType, rightReg, "add");
                    if (left->typeVar == CHAR && left->pointer == 1) strcpy(result->str, ((HashNode *)left->auxIdNode)->string + right->assign);
                    if (right->typeVar == CHAR && right->pointer == 1) strcpy(result->str, ((HashNode *)right->auxIdNode)->string + left->assign);
                    result->registerType = 0;
                    result->registerNumber = tReg;
                    return result;
                    break;

                case MINUS:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(left->typeVar, left->pointer, left->assign - right->assign);
                    int tReg = escreveArithmeticsOps(leftType, leftReg, rightType, rightReg, "sub");
                    result->registerType = 0;
                    result->registerNumber = tReg;
                    return result;
                    break;

                case MULTIPLY:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(left->typeVar, left->pointer, left->assign * right->assign);
                    tReg = escreveArithmeticsOps(leftType, leftReg, rightType, rightReg, "mul");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case DIVIDE:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(left->typeVar, left->pointer, left->assign / right->assign);
                    tReg = escreveDivisionOps(leftType, leftReg, rightType, rightReg, "mflo");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case REMAINDER:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(left->typeVar, left->pointer, left->assign % right->assign);
                    tReg = escreveDivisionOps(leftType, leftReg, rightType, rightReg, "mfhi");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case BITWISE_OR:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(left->typeVar, left->pointer, left->assign | right->assign);
                    tReg = escreveBitwiseOps(leftType, leftReg, rightType, rightReg, "or");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case BITWISE_AND:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(left->typeVar, left->pointer, left->assign & right->assign);
                    tReg = escreveBitwiseOps(leftType, leftReg, rightType, rightReg, "and");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case BITWISE_XOR:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(left->typeVar, left->pointer, left->assign ^ right->assign);
                    tReg = escreveBitwiseOps(leftType, leftReg, rightType, rightReg, "xor");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case LOGICAL_AND:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(INT, 0, left->assign && right->assign);
                    tReg = escreveLogicalAnd(leftType, leftReg, rightType, rightReg, abs((int)((intptr_t)expr)));
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case LOGICAL_OR:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(INT, 0, left->assign || right->assign);
                    tReg = escreveLogicalOr(leftType, leftReg, rightType, rightReg, abs((int)((intptr_t)expr)));
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case LESS_THAN:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(INT, 0, left->assign < right->assign);
                    tReg = escreveRelationalOps(leftType, leftReg, rightType, rightReg, "slt");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case LESS_EQUAL:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(INT, 0, left->assign <= right->assign);
                    tReg = escreveRelationalOps(leftType, leftReg, rightType, rightReg, "sle");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case GREATER_THAN:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(INT, 0, left->assign > right->assign);
                    tReg = escreveRelationalOps(leftType, leftReg, rightType, rightReg, "sgt");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case GREATER_EQUAL:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(INT, 0, left->assign >= right->assign);
                    tReg = escreveRelationalOps(leftType, leftReg, rightType, rightReg, "sge");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case EQUAL:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(INT, 0, left->assign == right->assign);
                    tReg = escreveRelationalOps(leftType, leftReg, rightType, rightReg, "seq");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case NOT_EQUAL:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(INT, 0, left->assign != right->assign);
                    tReg = escreveRelationalOps(leftType, leftReg, rightType, rightReg, "sne");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case R_SHIFT:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(left->typeVar, left->pointer, left->assign >> right->assign);
                    tReg = escreveBitwiseOps(leftType, leftReg, rightType, rightReg, "srlv");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case L_SHIFT:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                        rightReg = escreveLoadFromArray(right->registerNumber);
                        rightType = 0;
                    }
                    result = criaResultado(left->typeVar, left->pointer, left->assign << right->assign);
                    tReg = escreveBitwiseOps(leftType, leftReg, rightType, rightReg, "sllv");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                default:
                    printf("Erro: Operador binario desconhecido\n");
                    exit(1);
                    break;
            }
            break;

        case UOP:  // tipo 3 de expr
            left = eval(expr->left, listaHash, localHash, program);
            leftType = left->registerType;
            leftReg = left->registerNumber;

            switch (expr->operator) {
                case INC:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }

                    if (expr->preOrPost == 1) {
                        // printf("pre incremento\n");
                        result = criaResultado(left->typeVar, left->pointer, ++(left->assign));
                        tReg = escrevePreIncrements(left->registerType, left->registerNumber, "addi");
                        result->registerType = left->registerType;
                        result->registerNumber = tReg;

                    } else if (expr->preOrPost == 2) {
                        // printf("pos incremento\n");
                        int originalValue = left->assign;
                        left->assign++;
                        result = criaResultado(left->typeVar, left->pointer, originalValue);
                        tReg = escrevePostIncrements(left->registerType, left->registerNumber, "addi");
                        result->registerType = 0;  // como o que deve ser retornado é o valor original, nao tem registrador $s
                        result->registerNumber = tReg;
                    }

                    hashNodeTemp = getIdentifierNode(localHash, expr->identifier);
                    if (!hashNodeTemp) hashNodeTemp = getIdentifierNode(listaHash, expr->identifier);
                    if (hashNodeTemp) setAssign(hashNodeTemp, result->assign);
                    hashNodeTemp = NULL;
                    return result;
                    break;

                case DEC:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    if (expr->preOrPost == 1) {
                        // printf("pre decremento\n");
                        result = criaResultado(left->typeVar, left->pointer, --(left->assign));
                        tReg = escrevePreIncrements(left->registerType, left->registerNumber, "subi");
                        result->registerType = left->registerType;
                        result->registerNumber = tReg;

                    } else if (expr->preOrPost == 2) {
                        // printf("pos decremento\n");
                        int originalValue = left->assign;
                        left->assign--;
                        result = criaResultado(left->typeVar, left->pointer, originalValue);
                        tReg = escrevePostIncrements(left->registerType, left->registerNumber, "subi");
                        result->registerType = 0;  // como o que deve ser retornado é o valor original, nao tem registrador $s
                        result->registerNumber = tReg;
                    }

                    hashNodeTemp = getIdentifierNode(localHash, expr->identifier);
                    if (!hashNodeTemp) hashNodeTemp = getIdentifierNode(listaHash, expr->identifier);
                    if (hashNodeTemp) setAssign(hashNodeTemp, result->assign);
                    hashNodeTemp = NULL;
                    return result;
                    break;

                case BITWISE_NOT:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    result = criaResultado(left->typeVar, left->pointer, ~left->assign);
                    tReg = escreveBitwiseNot(leftType, leftReg);
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case PLUS:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    result = criaResultado(left->typeVar, left->pointer, +left->assign);
                    tReg = escreveUnaryPlusMinus(leftType, leftReg, "add");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case MINUS:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    result = criaResultado(left->typeVar, left->pointer, -left->assign);
                    tReg = escreveUnaryPlusMinus(leftType, leftReg, "sub");
                    result->registerNumber = tReg;
                    result->registerType = 0;
                    return result;
                    break;

                case NOT:
                    if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                        leftReg = escreveLoadFromArray(left->registerNumber);
                        leftType = 0;
                    }
                    result = criaResultado(left->typeVar, left->pointer, !(left->assign));
                    tReg = escreveLogicalNot(left->registerType, left->registerNumber);
                    result->registerType = 0;
                    result->registerNumber = tReg;
                    break;

                case MULTIPLY:
                    // printf("acesso de pointer %s %d %d\n", ((HashNode*)left->auxIdNode)->varId, left->registerType, left->registerNumber);
                    if (left->typeVar == CHAR && left->pointer == 1) {
                        result = criaResultado(CHAR, 0, *(((HashNode *)left->auxIdNode)->string));
                        int t = escreveLoadByte(left->registerType, left->registerNumber);
                        result->registerType = 0;
                        result->registerNumber = t;

                    } else if (left->typeVar == INT && left->pointer == 1) {
                        // fprintf("\t # aqui %s %d %d\n", ((HashNode *)left->auxIdNode)->varId, left->registerType, left->registerNumber);
                        result = criaResultado(INT, 0, 0);
                        int i = escreveConstant(0);
                        if (left->registerNumber == -1) {
                            left->registerNumber = escreveAssignAddress(left->registerType, left->registerNumber, ((HashNode *)left->auxIdNode)->varId);
                            setSRegisterInHash(((HashNode *)left->auxIdNode), left->registerNumber);
                        }
                        int posic = escreveAccessIndexArray(left->registerType, left->registerNumber, ((HashNode *)left->auxIdNode)->varId, 0, i, ((HashNode *)left->auxIdNode)->isGlobal);
                        result->registerType = 0;
                        if (inAtrib) {
                            result->registerNumber = posic;
                        } else {
                            result->registerNumber = escreveLoadFromArray(posic);
                        }

                    } else {
                        result = criaResultado(left->typeVar, 0, *(&left->assign));
                    }
                    result->auxIdNode = left->auxIdNode;
                    return result;
                    break;

                default:
                    printf("Erro: Operador unario desconhecido\n");
                    exit(1);
                    break;
            }

            break;

        case TERNARY:
            left = eval(expr->left, listaHash, localHash, program);
            right = eval(expr->right, listaHash, localHash, program);

            Resultado *condition = eval(expr->ternaryCondition, listaHash, localHash, program);
            escreveTernary(condition->registerType, condition->registerNumber, abs((int)((intptr_t)condition)));
            escreveLabel("true_ternary_", abs((int)((intptr_t)condition)));
            left = eval(expr->left, listaHash, localHash, program);
            escreveJump("end_ternary_", abs((int)((intptr_t)condition)));
            escreveLabel("false_ternary_", abs((int)((intptr_t)condition)));
            right = eval(expr->right, listaHash, localHash, program);
            escreveLabel("end_ternary_", abs((int)((intptr_t)condition)));

            leftType = left->registerType;
            leftReg = left->registerNumber;
            rightType = right->registerType;
            rightReg = right->registerNumber;

            if (left->auxIdNode && ((HashNode *)left->auxIdNode)->kind == VECTOR) {
                leftReg = escreveLoadFromArray(left->registerNumber);
                leftType = 0;
            }
            if (right->auxIdNode && ((HashNode *)right->auxIdNode)->kind == VECTOR) {
                rightReg = escreveLoadFromArray(right->registerNumber);
                rightType = 0;
            }
            // printf("left reg %d %d right reg %d %d\n", leftType, leftReg, rightType, rightReg);
            if (condition->assign) {
                result = criaResultado(left->typeVar, left->pointer, left->assign);
                result->registerNumber = left->registerNumber;
                result->registerType = left->registerType;
                if (rightType == 0) freeRegister(rightType, rightReg);

            } else {
                result = criaResultado(right->typeVar, right->pointer, right->assign);
                result->registerNumber = right->registerNumber;
                result->registerType = right->registerType;
                if (leftType == 0) freeRegister(leftType, leftReg);
            }
            return result;
            break;

        case ARRAY_CALL:
            auxIdNode = getIdentifierNode(localHash, expr->identifier);
            if (!auxIdNode) auxIdNode = getIdentifierNode(listaHash, expr->identifier);

            int posic = -1;
            int qntdDimenRecebidas = 0;
            Dims *dimenRecebidas = expr->dimension;
            Dims *dimenEsperada = auxIdNode->dimensions;
            Resultado *dimenResult = NULL;

            int mipsIndex = escreveConstant(1);
            while (dimenRecebidas) {
                qntdDimenRecebidas++;

                dimenResult = eval(dimenRecebidas->exp, listaHash, localHash, program);
                mipsIndex = escreveArithmeticsOps(0, mipsIndex, dimenResult->registerType, dimenResult->registerNumber, "mul");
                dimenEsperada = dimenEsperada->next;
                dimenRecebidas = dimenRecebidas->next;
                // printf("Array no reg $ s %d\n", ((HashNode*)left->auxIdNode)->sRegister);
                // printf("Indice do vetor %s [%d] || reg $ %c %d\n", ((HashNode*)left->auxIdNode)->varId, dimenResult->assign, dimenResult->registerType == 0 ? 't' : 's', dimenResult->registerNumber);
            }

            // printf(" -----| posiccc %s %d %d (%d %d)\n", auxIdNode->varId, auxIdNode->sRegister, auxIdNode->isGlobal, dimenResult->registerType, dimenResult->registerNumber);
            posic = escreveAccessIndexArray(1, auxIdNode->sRegister, auxIdNode->varId, 0, mipsIndex, auxIdNode->isGlobal);
            result = criaResultado(auxIdNode->typeVar, 0, 0);
            result->registerType = 0;
            result->registerNumber = posic;
            result->auxIdNode = auxIdNode;
            return result;

            break;

        case FUNCTION_CALL:
            auxIdNode = getIdentifierNode(listaHash, expr->identifier);
            ExpParam *auxParamRecebido = expr->param;
            int qntdParamRecebido = 0;
            while (auxParamRecebido) {
                qntdParamRecebido++;
                auxParamRecebido = auxParamRecebido->next;
            }

            Param *auxParam = auxIdNode->param;
            auxParamRecebido = expr->param;
            Resultado *resultParam = NULL;

            int i = 1;
            int j = qntdParamRecebido - 1;
            while (auxParamRecebido && auxParam) {
                resultParam = eval(auxParamRecebido->exp, listaHash, localHash, program);
                if (resultParam->auxIdNode && ((HashNode *)resultParam->auxIdNode)->kind == VECTOR) {
                    // printf("result do param %p %d %d\n", resultParam->auxIdNode, ((HashNode*)resultParam->auxIdNode)->kind, ((HashNode*)resultParam->auxIdNode)->typeVar);
                    resultParam->registerNumber = escreveLoadFromArray(resultParam->registerNumber);
                }
                escreveSetParamInRegister(j, resultParam->registerType, resultParam->registerNumber, auxParam->identifier);
                // printf("%s param %d %d %d %s ($ %d %d)\n",auxIdNode->varId, j, resultParam->typeVar, resultParam->assign, auxParam->identifier, resultParam->registerType, resultParam->registerNumber);
                j = j - 1;

                auxParam = auxParam->next;
                auxParamRecebido = auxParamRecebido->next;
                i++;
            }
            result = criaResultado(auxIdNode->typeVar, auxIdNode->pointer, 0);
            // printf("result function call %s %p %d %d = %d\n", auxIdNode->varId, result, result->typeVar, result->pointer, 0);

            escreveCallFuncao(auxIdNode->varId);
            int r = escreveLoadReturnFromV0();
            result->registerType = 0;
            result->registerNumber = r;
            result->auxIdNode = auxIdNode;
            return result;

            break;

        default:
            printf("Erro: Tipo de expressão desconhecido\n");
            break;
    }

    return 0;
}