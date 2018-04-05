#include "il_factor_null_impl.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

void il_factor_null_dump(void * empty, int depth) {
	text_putindent(depth);
	text_printf("null");
	text_putline();
}

void il_factor_null_generate(void * empty, enviroment * env, il_context* ilctx) {
	opcode_buf_add(env->buf, op_null);
}

void il_factor_null_load(void * empty, enviroment * env, il_context* ilctx, il_ehandler * eh) {
}

generic_type* il_factor_null_eval(void * empty, enviroment * env, il_context* ilctx) {
	return CL_NULL->generic_self;
}
