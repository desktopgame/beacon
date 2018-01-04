#include "il_factor_super_impl.h"
#include <stdio.h>
#include "../../vm/enviroment.h"
#include "../../util/text.h"
#include "../../env/class.h"

void il_factor_super_dump(il_factor_super * self, int depth) {
	text_putindent(depth);
	printf("super");
	text_putline();
}

void il_factor_super_generate(il_factor_super * self, enviroment * env) {
	opcode_buf_add(env->buf, op_super);
}

void il_factor_super_load(il_factor_super * self, enviroment * env, il_ehandler * eh) {
}

class_ * il_factor_super_eval(il_factor_super * self, enviroment * env) {
	return ((class_*)vector_top(env->class_vec))->super_class;
}

void il_factor_super_delete(il_factor_super * self) {
}
