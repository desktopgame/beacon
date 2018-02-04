#include "il_factor_null_impl.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

void il_factor_null_dump(void * empty, int depth) {
	text_putindent(depth);
	printf("null");
	text_putline();
}

void il_factor_null_generate(void * empty, enviroment * env) {
	opcode_buf_add(env->buf, op_null);
}

void il_factor_null_load(void * empty, enviroment * env, il_ehandler * eh) {
}

type * il_factor_null_eval(void * empty, enviroment * env) {
	return CL_NULL;
}
