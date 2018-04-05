#include "il_factor_super_impl.h"
#include <stdio.h>
#include <assert.h>
#include "../../vm/enviroment.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/type_impl.h"

void il_factor_super_dump(il_factor_super * self, int depth) {
	text_putindent(depth);
	text_printf("super");
	text_putline();
}

void il_factor_super_generate(il_factor_super * self, enviroment * env, il_context* cache) {
	opcode_buf_add(env->buf, op_super);
}

void il_factor_super_load(il_factor_super * self, enviroment * env, il_context* cache, il_ehandler * eh) {
}

generic_type* il_factor_super_eval(il_factor_super * self, enviroment * env, il_context* cache) {
	type* t = ((type*)vector_top(cache->type_vec));
	assert(t->tag == type_class);
	return t->u.class_->super_class->core_type->u.class_->parent->generic_self;
}

void il_factor_super_delete(il_factor_super * self) {
}
