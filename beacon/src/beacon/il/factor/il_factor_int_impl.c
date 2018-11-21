#include "il_factor_int_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/TYPE_IMPL.h"
#include "../../util/mem.h"
#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif
bc_ILFactor * WrapILInt(ILInt * self) {
	bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_INT_T);
	ret->Kind.Int = self;
	return ret;
}

ILInt * MallocILInt(int32_t i, const char* filename, int lineno) {
	ILInt* ret = (ILInt*)bc_MXMalloc(sizeof(ILInt), filename, lineno);
	ret->Value = i;
	ret->Count = 0;
	return ret;
}

void GenerateILInt(ILInt * self, bc_Enviroment* env, bc_CallContext* cctx) {
	assert(self->Count == 0);
	int index = bc_AddCIntEnviroment(env, self->Value);
	bc_AddOpcodeBuf(env->Bytecode, OP_ICONST);
	bc_AddOpcodeBuf(env->Bytecode, index);
	self->Count++;
}

void LoadILInt(ILInt * self, bc_Enviroment * env, bc_CallContext* cctx) {
}

bc_GenericType* EvalILInt(ILInt * self, bc_Enviroment * env, bc_CallContext* cctx) {
	return BC_GENERIC_INT;
}

char* ILIntToString(ILInt* self, bc_Enviroment* env) {
	bc_Buffer* sb = bc_NewBuffer();
	char block[32];
	int res = sprintf(block, "%d", self->Value);
	assert(res >= 0);
	bc_AppendsBuffer(sb, block);
	return bc_ReleaseBuffer(sb);
}

void DeleteILInt(ILInt * self) {
	MEM_FREE(self);
}