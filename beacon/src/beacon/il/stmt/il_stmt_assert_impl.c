#include "il_stmt_assert_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../il_factor_impl.h"
#include <assert.h>

il_stmt* il_stmt_wrap_assert(il_stmt_assert* self) {
	il_stmt* ret = il_stmt_new(ilstmt_assert_T);
	ret->u.bcassert_ = self;
	self->parent = ret;
	return ret;
}

il_stmt_assert* il_stmt_assert_new() {
	il_stmt_assert* ret = (il_stmt_assert*)MEM_MALLOC(sizeof(il_stmt_assert));
	ret->condition = NULL;
	ret->message = NULL;
	ret->parent = NULL;
	return ret;
}

void il_stmt_assert_generate(il_stmt_assert* self, enviroment* env, call_context* cctx) {
	//https://code.i-harness.com/ja/q/2a1650
	label* gt = opcode_buf_label(env->buf, 0);
	il_factor_generate(self->condition, env, cctx);
	opcode_buf_add(env->buf, op_goto_if_true);
	opcode_buf_add(env->buf, gt);

	il_factor_generate(self->message, env, cctx);
	opcode_buf_add(env->buf, op_new_instance);
	opcode_buf_add(env->buf, namespace_get_type(namespace_lang(), InternString("Exception"))->absolute_index);
	opcode_buf_add(env->buf, 0);
	opcode_buf_add(env->buf, op_throw);
	gt->cursor = opcode_buf_nop(env->buf);
}

void il_stmt_assert_load(il_stmt_assert* self, enviroment* env, call_context* cctx) {
	il_factor_load(self->condition, env, cctx);
	if(self->message == NULL) {
		char* str = il_factor_tostr(self->condition, env);
		il_factor_string* ilstr = il_factor_string_new(InternString(str));
		self->message = il_factor_wrap_string(ilstr);
		assert(ilstr->valuev != 0);
		MEM_FREE(str);
		self->message->lineno = self->parent->lineno;
	}
	il_factor_load(self->message, env, cctx);
}

void il_stmt_assert_delete(il_stmt_assert* self) {
	il_factor_delete(self->condition);
	il_factor_delete(self->message);
	MEM_FREE(self);
}