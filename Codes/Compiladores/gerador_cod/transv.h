#ifndef _TRANSV_H_
#define _TRANSV_H_

#include <stdint.h>
#include "ast.h"
#include "MIPS.h"
#include "hash.h"
#include "sintatico.tab.h"

void escreveAST(Command *command, void **listaHash, void **localHash, Program *program, Funcao *currentFuncao);
void procuraVar(void **listaHash, void **localHash, Program *program);
int percorreAST(Program *program) ;

#endif