#include "il_factor_this_impl.h"
#include <stdio.h>
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../call_context.h"
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

void il_factor_this_generate(il_factor_this * self, enviroment * env, call_context* cctx) {
	opcode_buf_add(env->buf, op_this);
}

void il_factor_this_load(il_factor_this * self, enviroment * env, call_context* cctx) {
}

generic_type* il_factor_this_eval(il_factor_this * self, enviroment * env, call_context* cctx) {
	return call_context_type(cctx)->generic_self;
}

char* il_factor_this_tostr(il_factor_this* self, enviroment* env) {
	return text_strdup("this");
}

void il_factor_this_delete(il_factor_this * self) {
	MEM_FREE(self);
}
