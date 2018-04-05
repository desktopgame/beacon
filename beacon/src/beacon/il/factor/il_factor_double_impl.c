#include "il_factor_double_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../util/mem.h"

il_factor * il_factor_wrap_double(il_factor_double * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_double;
	ret->u.double_ = self;
	return ret;
}

il_factor_double * il_factor_double_new(double d) {
	il_factor_double* ret = (il_factor_double*)MEM_MALLOC(sizeof(il_factor_double));
	ret->value = d;
	return ret;
}

void il_factor_double_dump(il_factor_double * self, int depth) {
	text_putindent(depth);
	text_printf("Dobule %f", self->value);
	text_putline();
}

void il_factor_double_generate(il_factor_double * self, enviroment* env, il_context* ilctx) {
	int index = enviroment_add_constant_double(env, self->value);
	opcode_buf_add(env->buf, op_dconst);
	opcode_buf_add(env->buf, index);
}

void il_factor_double_load(il_factor_double * self, enviroment * env, il_context* ilctx, il_ehandler * eh) {
}

generic_type* il_factor_double_eval(il_factor_double * self, enviroment * env, il_context* ilctx) {
	return CL_DOUBLE->generic_self;
}

void il_factor_double_delete(il_factor_double * self) {
	MEM_FREE(self);
}

il_factor_double* il_factor_cast_double(il_factor* fact) {
	assert(fact->type == ilfactor_double);
	return fact->u.double_;
}