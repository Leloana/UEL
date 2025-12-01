#ifndef _EVAL_H_
#define _EVAL_H_


#include <stdint.h>
#include "ast.h"
#include "MIPS.h"
#include "hash.h"
#include "sintatico.tab.h"

Resultado *eval(Expression *expr, void **listaHash, void **localHash, Program *program);

#endif