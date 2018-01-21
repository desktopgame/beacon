#include "il_factor_this_impl.h"
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include <assert.h>

void il_factor_this_dump(il_factor_this * self, int depth) {
	text_putindent(depth);
	printf("this");
	text_putline();
}

void il_factor_this_generate(il_factor_this * self, enviroment * env) {
	opcode_buf_add(env->buf, op_this);
}

void il_factor_this_load(il_factor_this * self, enviroment * env, il_ehandler * eh) {
}

type * il_factor_this_eval(il_factor_this * self, enviroment * env) {
	assert(env->type_vec->length > 0);
	type* ret = (type*)vector_top(env->type_vec);
	return ret;
}

void il_factor_this_delete(il_factor_this * self) {
}
