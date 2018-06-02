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

void il_factor_null_generate(void * empty, enviroment * env) {
	opcode_buf_add(env->buf, op_null);
}

void il_factor_null_load(void * empty, enviroment * env) {
}

generic_type* il_factor_null_eval(void * empty, enviroment * env) {
	if(gSelf == NULL) {
		gSelf =  generic_type_new(TYPE_NULL);
	}
	return gSelf;
}

char* il_factor_null_tostr(void* empty, enviroment* env) {
	return text_strdup("null");
}