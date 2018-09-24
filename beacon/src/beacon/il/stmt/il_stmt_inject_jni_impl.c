#include "il_stmt_inject_jni_impl.h"
#include "../../util/mem.h"
#include "../../util/io.h"
#include "../../vm/symbol_entry.h"

il_stmt* il_stmt_wrap_inject_jni(il_stmt_inject_jni* self) {
	il_stmt* ret = il_stmt_new(ilstmt_inject_jni_T);
	ret->u.inject_jni = self;
	//JNIに関しては後からソースの先頭に付け加えられるので必ず0
	ret->lineno = 0;
	return ret;
}

il_stmt_inject_jni* il_stmt_inject_jni_new(string_view namev) {
	il_stmt_inject_jni* ret = (il_stmt_inject_jni*)MEM_MALLOC(sizeof(il_stmt_inject_jni));
	ret->namev = namev;
	ret->fact = NULL;
	ret->se = NULL;
	return ret;
}

void il_stmt_inject_jni_generate(il_stmt_inject_jni* self, enviroment* env, call_context* cctx) {
	il_factor_generate(self->fact, env, cctx);
	opcode_buf_add(env->buf, op_store);
	opcode_buf_add(env->buf, self->se->index);
}

void il_stmt_inject_jni_load(il_stmt_inject_jni * self, enviroment* env, call_context* cctx) {
	if(self->se != NULL) {
		return;
	}
	self->fact->lineno = 0;
	il_factor_load(self->fact, env, cctx);
	generic_type* gtype = il_factor_eval(self->fact, env, cctx);
	self->se = symbol_table_entry(env->sym_table, gtype, self->namev);
}

void il_stmt_inject_jni_delete(il_stmt_inject_jni* self) {
	il_factor_delete(self->fact);
	MEM_FREE(self);
}