#include "il_factor_this_impl.h"
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"

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
	return (type*)vector_top(env->class_vec);
}

void il_factor_this_delete(il_factor_this * self) {
}
