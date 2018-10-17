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
il_factor * WrapILInt(il_factor_int * self) {
	il_factor* ret = il_factor_new(ILFACTOR_INT_T);
	ret->u.int_ = self;
	return ret;
}

il_factor_int * MallocILInt(int32_t i, const char* filename, int lineno) {
	il_factor_int* ret = (il_factor_int*)mem_malloc(sizeof(il_factor_int), filename, lineno);
	ret->value = i;
	ret->count = 0;
	return ret;
}

void GenerateILInt(il_factor_int * self, enviroment* env, call_context* cctx) {
	assert(self->count == 0);
	int index = AddCIntEnviroment(env, self->value);
	AddOpcodeBuf(env->buf, OP_ICONST);
	AddOpcodeBuf(env->buf, index);
	self->count++;
}

void LoadILInt(il_factor_int * self, enviroment * env, call_context* cctx) {
}

generic_type* EvalILInt(il_factor_int * self, enviroment * env, call_context* cctx) {
	return GENERIC_INT;
}

char* ILIntToString(il_factor_int* self, enviroment* env) {
	StringBuffer* sb = NewBuffer();
	char block[32];
	int res = sprintf(block, "%d", self->value);
	assert(res >= 0);
	AppendsBuffer(sb, block);
	return ReleaseBuffer(sb);
}

void DeleteILInt(il_factor_int * self) {
	MEM_FREE(self);
}