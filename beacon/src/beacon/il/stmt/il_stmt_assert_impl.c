#include "il_stmt_assert_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"

il_stmt* il_stmt_wrap_assert(il_stmt_assert* self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt));
	ret->type = ilstmt_assert;
	ret->u.bcassert_ = self;
	return ret;
}

il_stmt_assert* il_stmt_assert_new() {
	il_stmt_assert* ret = (il_stmt_assert*)MEM_MALLOC(sizeof(il_stmt_assert));
	ret->condition = NULL;
	ret->message = NULL;
	return ret;
}

void il_stmt_assert_dump(il_stmt_assert* self, int depth) {
	text_putindent(depth);
	text_printf("assert");
	text_putline();
	il_factor_dump(self->condition, depth + 1);
	il_factor_dump(self->message, depth + 1);
}

void il_stmt_assert_generate(il_stmt_assert* self, enviroment* env, il_context* ilctx) {
	//https://code.i-harness.com/ja/q/2a1650
	label* gt = opcode_buf_label(env->buf, 0);
	il_factor_generate(self->condition, env, ilctx);
	opcode_buf_add(env->buf, op_goto_if_true);
	opcode_buf_add(env->buf, gt);

	il_factor_generate(self->message, env, ilctx);
	opcode_buf_add(env->buf, op_new_instance);
	opcode_buf_add(env->buf, namespace_get_type(namespace_lang(), "Exception")->absolute_index);
	opcode_buf_add(env->buf, 0);
	opcode_buf_add(env->buf, op_throw);
	gt->cursor = opcode_buf_nop(env->buf);
}

void il_stmt_assert_load(il_stmt_assert* self, enviroment* env, il_context* ilctx, il_ehandler* eh) {
	il_factor_load(self->condition, env, ilctx, eh);
	il_factor_load(self->message, env, ilctx, eh);
}

void il_stmt_assert_delete(il_stmt_assert* self) {
	il_factor_delete(self->condition);
	il_factor_delete(self->message);
	MEM_FREE(self);
}