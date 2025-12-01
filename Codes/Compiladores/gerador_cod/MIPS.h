#ifndef _MIPS_H_
#define _MIPS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicio();

// Arithmetic operations
int escreveConstant(int value);
int escreveArithmeticsOps(int leftType, int leftReg, int rightType, int rightReg, char *op);
int escreveDivisionOps(int leftType, int leftReg, int rightType, int rightReg, char *op);
int escrevePreIncrements(int leftType, int leftReg, char *op);
int escrevePostIncrements(int leftType, int leftReg, char *op);

// Assigns
int escreveAssignment(int rightType, int rightReg);
void escreveAssignmentToReg(int rightType, int rightReg, int leftReg);
int escreveDeclareString(char *name, char *value);
int escreveAssignAddress(int leftType, int leftReg, char *name);
void escreveStoreInAddress(int leftType, int leftReg, int rightType, int rightReg);

// Unary operations (+, -, ~) + logical not (!) + bitwise ops (&, |, ^) + shifts (<<, >>)
int escreveUnaryPlusMinus(int leftType, int leftReg, char *op);
int escreveBitwiseNot(int leftType, int leftReg);
int escreveBitwiseOps(int leftType, int leftReg, int rightType, int rightReg, char *op);
int escreveLogicalNot(int leftType, int leftReg);

// Relational expressions
int escreveRelationalOps(int leftType, int leftReg, int rightType, int rightReg, char *op);

// Control structures
int escreveLogicalAnd(int leftType, int leftReg, int rightType, int rightReg, int labelID);
int escreveLogicalOr(int leftType, int leftReg, int rightType, int rightReg, int labelID);
void escreveIf(int conditionType, int conditionReg, int labelID);
void escreveWhile(int conditionType, int conditionReg, int labelID);
void escreveFor(int conditionType, int conditionReg, int labelID);
void escreveTernary(int conditionType, int conditionReg, int labelID);

// Labels and jumps
void escreveJump(char *label, int labelID);
void escreveLabel(char *label, int labelID);
void escreveFuncaos(char *name);

// Global variables and declarations
void escreveGlobalVariableInMemory(int size, char *name);
void setDefineIntVariable(char *name, int value);
void escreveDefines();
// void escreveGlobalCharVariable(char *name, char value);
void setGlobalVarAssign(char *name, int value);
void escreveGlobalVarAssign();
int escreveLoadIntGlobal(char *name);
void escreveStoreIntGlobal(int type, int reg, char *name);

// Arrays
int escreveDeclareArray(char *name, int size, int isGlobal);
int escreveAccessIndexArray(int arrayType, int arrayReg, char *name, int indexType, int indexReg, int isGlobal);
void escreveStoreIntoArray(int posic, int rightType, int rightReg);
int escreveLoadFromArray(int posic);
int escreveLoadByte(int type, int reg);

// Output escreve
void escreveInteger(int regType, int RegNumber);
void escreveCharacter(int regType, int RegNumber);
void escreveStringVar(int type, int value);
void escreveString(char *value, int stringID1);

// Input scan
int escreveScanInt(int sReg, char *name, int isGlobal);

// Funcao call
void escreveCallFuncao(char *name);
void escreveSetParamInRegister(int aReg, int rightType, int rightReg, char *var);
void escreveFuncaoParams(char *name, int params);
void escreveReturn();
void escreveReturnToV0(int type, int reg);
int escreveLoadReturnFromV0();

// Stack
void storeGlobalsInStack(int *globals);
// void loadGlobalsFromStack(int *globals);
void storeInStack();
void loadFromStack();
void storeTRegisters(int *regs);
void loadTRegisters(int *regs);
void freeRegister(int type, int number);
void inicio();
void escreveExit();

#endif