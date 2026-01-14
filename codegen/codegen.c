/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include "reader.h"
#include "codegen.h"  

#define CODE_SIZE 10000
extern SymTab* symtab;

extern Object* readiFunction;
extern Object* readcFunction;
extern Object* writeiProcedure;
extern Object* writecProcedure;
extern Object* writelnProcedure;

CodeBlock* codeBlock;

void genVariableAddress(Object* var) {
  // TODO
  int level = computeNestedLevel(var->varAttrs->scope);
  int offset = var->varAttrs->localOffset;
  genLA(level, offset);
}

void genVariableValue(Object* var) {
  // TODO
  int level = computeNestedLevel(var->varAttrs->scope);
  int offset = var->varAttrs->localOffset;
  genLV(level, offset);
}

int isPredefinedFunction(Object* func) {
  return ((func == readiFunction) || (func == readcFunction));
}

int isPredefinedProcedure(Object* proc) {
  return ((proc == writeiProcedure) || (proc == writecProcedure) || (proc == writelnProcedure));
}

void genPredefinedProcedureCall(Object* proc) {
  if (proc == writeiProcedure)
    genWRI();
  else if (proc == writecProcedure)
    genWRC();
  else if (proc == writelnProcedure)
    genWLN();
}

void genPredefinedFunctionCall(Object* func) {
  if (func == readiFunction)
    genRI();
  else if (func == readcFunction)
    genRC();
}

void genLA(int level, int offset) {
  emitLA(codeBlock, level, offset);
}

void genLV(int level, int offset) {
  emitLV(codeBlock, level, offset);
}

void genLC(WORD constant) {
  emitLC(codeBlock, constant);
}

void genLI(void) {
  emitLI(codeBlock);
}

void genINT(int delta) {
  emitINT(codeBlock,delta);
}

void genDCT(int delta) {
  emitDCT(codeBlock,delta);
}

Instruction* genJ(CodeAddress label) {
  Instruction* inst = codeBlock->code + codeBlock->codeSize;
  emitJ(codeBlock,label);
  return inst;
}

Instruction* genFJ(CodeAddress label) {
  Instruction* inst = codeBlock->code + codeBlock->codeSize;
  emitFJ(codeBlock, label);
  return inst;
}

void genHL(void) {
  emitHL(codeBlock);
}

void genST(void) {
  emitST(codeBlock);
}

void genCALL(int level, CodeAddress label) {
  emitCALL(codeBlock, level, label);
}

void genEP(void) {
  emitEP(codeBlock);
}

void genEF(void) {
  emitEF(codeBlock);
}

void genRC(void) {
  emitRC(codeBlock);
}

void genRI(void) {
  emitRI(codeBlock);
}

void genWRC(void) {
  emitWRC(codeBlock);
}

void genWRI(void) {
  emitWRI(codeBlock);
}

void genWLN(void) {
  emitWLN(codeBlock);
}

void genAD(void) {
  emitAD(codeBlock);
}

void genSB(void) {
  emitSB(codeBlock);
}

void genML(void) {
  emitML(codeBlock);
}

void genDV(void) {
  emitDV(codeBlock);
}

void genNEG(void) {
  emitNEG(codeBlock);
}

void genCV(void) {
  emitCV(codeBlock);
}

void genEQ(void) {
  emitEQ(codeBlock);
}

void genNE(void) {
  emitNE(codeBlock);
}

void genGT(void) {
  emitGT(codeBlock);
}

void genGE(void) {
  emitGE(codeBlock);
}

void genLT(void) {
  emitLT(codeBlock);
}

void genLE(void) {
  emitLE(codeBlock);
}

void updateJ(Instruction* jmp, CodeAddress label) {
  jmp->q = label;
}

void updateFJ(Instruction* jmp, CodeAddress label) {
  jmp->q = label;
}

CodeAddress getCurrentCodeAddress(void) {
  return codeBlock->codeSize;
}


void initCodeBuffer(void) {
  codeBlock = createCodeBlock(CODE_SIZE);
}

void printCodeBuffer(void) {
  printCodeBlock(codeBlock);
}

void cleanCodeBuffer(void) {
  freeCodeBlock(codeBlock);
}

int serialize(char* fileName) {
  FILE* f;

  f = fopen(fileName, "wb");
  if (f == NULL) return IO_ERROR;
  saveCode(codeBlock, f);
  fclose(f);
  return IO_SUCCESS;
}

// Hàm tính mức lồng nhau của Scope
int computeNestedLevel(Scope* scope) {
  int level = 0;
  Scope* tmp = symtab->currentScope;
  while (tmp != scope) {
    tmp = tmp->outer;
    level++;
  }
  return level;
}

void genParameterAddress(Object* param) {
  int level = computeNestedLevel(param->paramAttrs->scope);
  int offset = param->paramAttrs->localOffset;
  // Nếu là tham chiếu (VAR param), giá trị trong stack chính là địa chỉ
  if (param->paramAttrs->kind == PARAM_REFERENCE)
    genLV(level, offset);
  else
    genLA(level, offset);
}

void genParameterValue(Object* param) {
  int level = computeNestedLevel(param->paramAttrs->scope);
  int offset = param->paramAttrs->localOffset;
  genLV(level, offset);
  // Nếu là tham chiếu, cần lấy thêm giá trị tại địa chỉ đó (Indirect)
  if (param->paramAttrs->kind == PARAM_REFERENCE)
    genLI();
}

void genReturnValueAddress(Object* func) {
  int level = computeNestedLevel(func->funcAttrs->scope);
  // Giá trị trả về luôn nằm ở offset 0 trong Frame
  genLA(level, 0);
}

void genReturnValueValue(Object* func) {
  int level = computeNestedLevel(func->funcAttrs->scope);
  genLV(level, 0);
}

void genProcedureCall(Object* proc) {
  // Level của lệnh CALL là khoảng cách đến scope chứa procedure đó
  int level = computeNestedLevel(proc->procAttrs->scope->outer);
  genCALL(level, proc->procAttrs->codeAddress);
}

void genFunctionCall(Object* func) {
  int level = computeNestedLevel(func->funcAttrs->scope->outer);
  genCALL(level, func->funcAttrs->codeAddress);
}
