#include "il_factor_int_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/type_impl.h"
#include "../../util/mem.h"

il_factor * il_factor_wrap_int(il_factor_int * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_int;
	ret->u.int_ = self;
	return ret;
}

il_factor_int * il_factor_int_new(int32_t i) {
	il_factor_int* ret = (il_factor_int*)MEM_MALLOC(sizeof(il_factor_int));
	ret->value = i;
	return ret;
}

void il_factor_int_dump(il_factor_int * self, int depth) {
	text_putindent(depth);
	text_printf("Int %d", self->value);
	text_putline();
}

void il_factor_int_generate(il_factor_int * self, enviroment* env, il_context* ilctx) {
	int index = enviroment_add_constant_int(env, self->value);
	opcode_buf_add(env->buf, op_iconst);
	opcode_buf_add(env->buf, index);
}

void il_factor_int_load(il_factor_int * self, enviroment * env, il_context* ilctx, il_ehandler * eh) {
}

generic_type* il_factor_int_eval(il_factor_int * self, enviroment * env, il_context* ilctx) {
	return GEN_INT;
}

void il_factor_int_delete(il_factor_int * self) {
	MEM_FREE(self);
}

il_factor_int* il_factor_cast_int(il_factor* fact) {
	assert(fact->type == ilfactor_int);
	return fact->u.int_;
}