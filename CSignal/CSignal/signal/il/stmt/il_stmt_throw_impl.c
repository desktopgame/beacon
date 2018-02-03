#include "il_stmt_throw_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include <stdio.h>

il_stmt* il_stmt_wrap_throw(il_stmt_throw* self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt));
	ret->type = ilstmt_throw;
	ret->u.throw_ = self;
	return ret;
}

il_stmt_throw* il_stmt_throw_new() {
	il_stmt_throw* ret = (il_stmt_throw*)MEM_MALLOC(sizeof(il_stmt_throw));
	ret->fact = NULL;
	return ret;
}

void il_stmt_throw_dump(il_stmt_throw* self, int depth) {
	text_putindent(depth);
	printf("throw");
	text_putline();
	il_factor_dump(self->fact, depth + 1);
}

void il_stmt_throw_generate(il_stmt_throw* self, enviroment* env) {
	il_factor_generate(self->fact, env);
	opcode_buf_add(env->buf, op_throw);
}

void il_stmt_throw_load(il_stmt_throw* self, enviroment* env, il_ehandler* eh) {
	il_factor_load(self->fact, env, eh);
}

void il_stmt_throw_delete(il_stmt_throw* self) {
	il_factor_delete(self->fact);
	MEM_FREE(self);
}