#include "il_factor_double_impl.h"
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

il_factor * WrapILDouble(il_factor_double * self) {
	il_factor* ret = il_factor_new(ILFACTOR_DOUBLE_T);
	ret->u.double_ = self;
	return ret;
}

il_factor_double * NewILDouble(double d) {
	il_factor_double* ret = (il_factor_double*)MEM_MALLOC(sizeof(il_factor_double));
	ret->value = d;
	return ret;
}

void il_factor_double_generate(il_factor_double * self, enviroment* env, call_context* cctx) {
	int index = AddCDoubleEnviroment(env, self->value);
	AddOpcodeBuf(env->buf, OP_DCONST);
	AddOpcodeBuf(env->buf, index);
}

void LoadILDouble(il_factor_double * self, enviroment * env, call_context* cctx) {
}

generic_type* EvalILDouble(il_factor_double * self, enviroment * env, call_context* cctx) {
	return GENERIC_DOUBLE;
}

char* ILDoubleToString(il_factor_double* self, enviroment* env) {
	string_buffer* sb = NewBuffer();
	char block[32] = {0};
	int res = sprintf(block, "%lf", self->value);
	assert(res >= 0);
	AppendsBuffer(sb, block);
	return ReleaseBuffer(sb);
}

void il_factor_double_delete(il_factor_double * self) {
	MEM_FREE(self);
}