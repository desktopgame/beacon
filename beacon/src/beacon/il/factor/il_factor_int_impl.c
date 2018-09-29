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
il_factor * il_factor_wrap_int(il_factor_int * self) {
	il_factor* ret = il_factor_new(ILFACTOR_INT_T);
	ret->u.int_ = self;
	return ret;
}

il_factor_int * il_factor_int_malloc(int32_t i, const char* filename, int lineno) {
	il_factor_int* ret = (il_factor_int*)mem_malloc(sizeof(il_factor_int), filename, lineno);
	ret->value = i;
	ret->count = 0;
	return ret;
}

void il_factor_int_generate(il_factor_int * self, enviroment* env, call_context* cctx) {
	assert(self->count == 0);
	int index = enviroment_add_constant_int(env, self->value);
	AddOpcodeBuf(env->buf, OP_ICONST);
	AddOpcodeBuf(env->buf, index);
	self->count++;
}

void il_factor_int_load(il_factor_int * self, enviroment * env, call_context* cctx) {
}

generic_type* il_factor_int_eval(il_factor_int * self, enviroment * env, call_context* cctx) {
	return GENERIC_INT;
}

char* il_factor_int_tostr(il_factor_int* self, enviroment* env) {
	string_buffer* sb = NewBuffer();
	char block[32];
	int res = sprintf(block, "%d", self->value);
	assert(res >= 0);
	AppendsBuffer(sb, block);
	return ReleaseBuffer(sb);
}

void il_factor_int_delete(il_factor_int * self) {
	MEM_FREE(self);
}