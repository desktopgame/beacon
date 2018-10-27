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
ILFactor * WrapILInt(ILFactor_int * self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_INT_T);
	ret->u.int_ = self;
	return ret;
}

ILFactor_int * MallocILInt(int32_t i, const char* filename, int lineno) {
	ILFactor_int* ret = (ILFactor_int*)mem_malloc(sizeof(ILFactor_int), filename, lineno);
	ret->value = i;
	ret->count = 0;
	return ret;
}

void GenerateILInt(ILFactor_int * self, Enviroment* env, CallContext* cctx) {
	assert(self->count == 0);
	int index = AddCIntEnviroment(env, self->value);
	AddOpcodeBuf(env->Bytecode, OP_ICONST);
	AddOpcodeBuf(env->Bytecode, index);
	self->count++;
}

void LoadILInt(ILFactor_int * self, Enviroment * env, CallContext* cctx) {
}

GenericType* EvalILInt(ILFactor_int * self, Enviroment * env, CallContext* cctx) {
	return GENERIC_INT;
}

char* ILIntToString(ILFactor_int* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	char block[32];
	int res = sprintf(block, "%d", self->value);
	assert(res >= 0);
	AppendsBuffer(sb, block);
	return ReleaseBuffer(sb);
}

void DeleteILInt(ILFactor_int * self) {
	MEM_FREE(self);
}