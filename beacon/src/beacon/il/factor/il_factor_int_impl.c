#include "il_factor_int_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/type_impl.h"
#include "../../util/mem.h"
#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif
il_factor * il_factor_wrap_int(il_factor_int * self) {
	il_factor* ret = il_factor_new(ilfactor_int_T);
	ret->u.int_ = self;
	return ret;
}

il_factor_int * il_factor_int_malloc(int32_t i, const char* filename, int lineno) {
	il_factor_int* ret = (il_factor_int*)mem_malloc(sizeof(il_factor_int), filename, lineno);
	ret->value = i;
	ret->count = 0;
	return ret;
}

void il_factor_int_dump(il_factor_int * self, int depth) {
	io_printi(depth);
	printf("Int %d", self->value);
	io_println();
}

void il_factor_int_generate(il_factor_int * self, enviroment* env, call_context* cctx) {
	assert(self->count == 0);
	int index = enviroment_add_constant_int(env, self->value);
	opcode_buf_add(env->buf, op_iconst);
	opcode_buf_add(env->buf, index);
	self->count++;
}

void il_factor_int_load(il_factor_int * self, enviroment * env, call_context* cctx) {
}

generic_type* il_factor_int_eval(il_factor_int * self, enviroment * env, call_context* cctx) {
	return GENERIC_INT;
}

char* il_factor_int_tostr(il_factor_int* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	char block[32];
	int res = sprintf(block, "%d", self->value);
	assert(res >= 0);
	string_buffer_appends(sb, block);
	return string_buffer_release(sb);
}

void il_factor_int_delete(il_factor_int * self) {
	MEM_FREE(self);
}

il_factor_int* il_factor_cast_int_T(il_factor* fact) {
	assert(fact->type == ilfactor_int_T);
	return fact->u.int_;
}