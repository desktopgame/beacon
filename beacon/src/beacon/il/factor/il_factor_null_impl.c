#include "il_factor_null_impl.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

static generic_type* gSelf = NULL;

void il_factor_null_dump(void * empty, int depth) {
	text_putindent(depth);
	text_printf("null");
	text_putline();
}

void il_factor_null_generate(void * empty, enviroment * env, il_context* ilctx) {
	opcode_buf_add(env->buf, op_null);
}

void il_factor_null_load(void * empty, enviroment * env, il_context* ilctx) {
}

generic_type* il_factor_null_eval(void * empty, enviroment * env, il_context* ilctx) {
	if(gSelf == NULL) {
		gSelf =  generic_type_new(CL_NULL);
	}
	return gSelf;
}

char* il_factor_null_tostr(void* empty, enviroment* env, il_context* ilctx) {
	return text_strdup("null");
}