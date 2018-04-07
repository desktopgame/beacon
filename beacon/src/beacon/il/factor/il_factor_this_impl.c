#include "il_factor_this_impl.h"
#include <stdio.h>
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include <assert.h>

il_factor_this* il_factor_this_new() {
	il_factor_this* ret = (il_factor_this*)MEM_MALLOC(sizeof(il_factor_this));
	ret->resolved = NULL;
	return ret;
}

void il_factor_this_dump(il_factor_this * self, int depth) {
	text_putindent(depth);
	text_printf("this");
	text_putline();
}

void il_factor_this_generate(il_factor_this * self, enviroment * env, il_context* ilctx) {
	opcode_buf_add(env->buf, op_this);
}

void il_factor_this_load(il_factor_this * self, enviroment * env, il_context* ilctx, il_ehandler * eh) {
}

generic_type* il_factor_this_eval(il_factor_this * self, enviroment * env, il_context* ilctx) {
	if(self->resolved == NULL) {
		assert(ilctx->type_vec->length > 0);
		type* ret = (type*)vector_top(ilctx->type_vec);
		self->resolved = generic_type_make(ret);
	}
	return self->resolved;
}

void il_factor_this_delete(il_factor_this * self) {
	generic_type_delete(self->resolved);
	MEM_FREE(self);
}
