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
ILFactor * WrapILInt(ILInt * self) {
	ILFactor* ret = NewILFactor(ILFACTOR_INT_T);
	ret->Kind.Int = self;
	return ret;
}

ILInt * MallocILInt(int32_t i, const char* filename, int lineno) {
	ILInt* ret = (ILInt*)bc_MXMalloc(sizeof(ILInt), filename, lineno);
	ret->Value = i;
	ret->Count = 0;
	return ret;
}

void GenerateILInt(ILInt * self, Enviroment* env, CallContext* cctx) {
	assert(self->Count == 0);
	int index = AddCIntEnviroment(env, self->Value);
	AddOpcodeBuf(env->Bytecode, OP_ICONST);
	AddOpcodeBuf(env->Bytecode, index);
	self->Count++;
}

void LoadILInt(ILInt * self, Enviroment * env, CallContext* cctx) {
}

bc_GenericType* EvalILInt(ILInt * self, Enviroment * env, CallContext* cctx) {
	return BC_GENERIC_INT;
}

char* ILIntToString(ILInt* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	char block[32];
	int res = sprintf(block, "%d", self->Value);
	assert(res >= 0);
	AppendsBuffer(sb, block);
	return ReleaseBuffer(sb);
}

void DeleteILInt(ILInt * self) {
	MEM_FREE(self);
}