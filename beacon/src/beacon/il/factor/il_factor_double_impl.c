#include "il_factor_double_impl.h"
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

il_factor * il_factor_wrap_double(il_factor_double * self) {
	il_factor* ret = il_factor_new(ilfactor_double_T);
	ret->u.double_ = self;
	return ret;
}

il_factor_double * il_factor_double_new(double d) {
	il_factor_double* ret = (il_factor_double*)MEM_MALLOC(sizeof(il_factor_double));
	ret->value = d;
	return ret;
}

void il_factor_double_dump(il_factor_double * self, int depth) {
	io_printi(depth);
	printf("Dobule %f", self->value);
	io_println();
}

void il_factor_double_generate(il_factor_double * self, enviroment* env, call_context* cctx) {
	int index = enviroment_add_constant_double(env, self->value);
	opcode_buf_add(env->buf, op_dconst);
	opcode_buf_add(env->buf, index);
}

void il_factor_double_load(il_factor_double * self, enviroment * env, call_context* cctx) {
}

generic_type* il_factor_double_eval(il_factor_double * self, enviroment * env, call_context* cctx) {
	return GENERIC_DOUBLE;
}

char* il_factor_double_tostr(il_factor_double* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	char block[32] = {0};
	int res = sprintf(block, "%lf", self->value);
	assert(res >= 0);
	string_buffer_appends(sb, block);
	return string_buffer_release(sb);
}

void il_factor_double_delete(il_factor_double * self) {
	MEM_FREE(self);
}

il_factor_double* il_factor_cast_double_T(il_factor* fact) {
	assert(fact->type == ilfactor_double_T);
	return fact->u.double_;
}