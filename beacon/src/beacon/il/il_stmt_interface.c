#include "il_stmt_interface.h"
#include "il_stmt_impl.h"
#include "../env/class_loader.h"
#include "../env/type_interface.h"
#include "../vm/enviroment.h"
#include "../util/mem.h"
#include "il_print_layout.h"

il_stmt* il_stmt_malloc(il_stmt_type type, const char* filename, int lineno) {
	il_stmt* ret = mem_malloc(sizeof(il_stmt), filename, lineno);
	ret->type = type;
	ret->lineno = -1;
	return ret;
}

void il_stmt_dump(il_stmt * self, int depth) {
	il_print_layout_form(self->lineno);
	switch (self->type) {
		case ilstmt_if:
			il_stmt_if_dump(self->u.if_, depth);
			break;
		case ilstmt_proc:
			il_stmt_proc_dump(self->u.proc_, depth);
			break;
		case ilstmt_variable_decl:
			il_stmt_variable_decl_dump(self->u.variable_decl, depth);
			break;
		case ilstmt_variable_init:
			il_stmt_variable_init_dump(self->u.variable_init, depth);
			break;
		case ilstmt_return:
			il_stmt_return_dump(self->u.return_, depth);
			break;
		case ilstmt_while:
			il_stmt_while_dump(self->u.while_, depth);
			break;
		case ilstmt_break:
			il_stmt_break_dump(NULL, depth);
			break;
		case ilstmt_continue:
			il_stmt_continue_dump(NULL, depth);
			break;
		case ilstmt_inferenced_type_init:
			il_stmt_inferenced_type_init_dump(self->u.inferenced_type_init, depth);
			break;
		case ilstmt_try:
			il_stmt_try_dump(self->u.try_, depth);
			break;
		case ilstmt_throw:
			il_stmt_throw_dump(self->u.throw_, depth);
			break;
		case ilstmt_assert:
			il_stmt_assert_dump(self->u.bcassert_, depth);
			break;
		case ilstmt_defer:
			il_stmt_defer_dump(self->u.defer_, depth);
			break;
		default:
			//ERROR("ステートメントをダンプ出来ませんでした。");
			break;
	}
}

void il_stmt_generate(il_stmt * self, struct enviroment* env, call_context* cctx) {
	if(il_error_panic()) {
		return;
	}
	switch (self->type) {
		case ilstmt_if:
			il_stmt_if_generate(self->u.if_, env, cctx);
			//il_stmt_if_delete(self->u.if_);
			break;
		case ilstmt_proc:
			il_stmt_proc_generate(self->u.proc_, env, cctx);
			//il_stmt_proc_delete(self->u.proc_);
			break;
		case ilstmt_variable_decl:
			il_stmt_variable_decl_generate(self->u.variable_decl, env, cctx);
			break;
		case ilstmt_variable_init:
			il_stmt_variable_init_generate(self->u.variable_init, env, cctx);
			break;
		case ilstmt_return:
			il_stmt_return_generate(self->u.return_, env, cctx);
			break;
		case ilstmt_while:
			il_stmt_while_generate(self->u.while_, env, cctx);
			break;
		case ilstmt_break:
			il_stmt_break_generate(NULL, env, cctx);
			break;
		case ilstmt_continue:
			il_stmt_continue_generate(NULL, env, cctx);
			break;
		case ilstmt_inferenced_type_init:
			il_stmt_inferenced_type_init_generate(self->u.inferenced_type_init, env, cctx);
			break;
		case ilstmt_try:
			il_stmt_try_generate(self->u.try_, env, cctx);
			break;
		case ilstmt_throw:
			il_stmt_throw_generate(self->u.throw_, env, cctx);
			break;
		case ilstmt_assert:
			il_stmt_assert_generate(self->u.bcassert_, env, cctx);
			break;
		case ilstmt_defer:
			il_stmt_defer_generate(self->u.defer_, env, cctx);
			break;
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			break;
	}
	enviroment_add_range(env, self->lineno);
}

void il_stmt_load(il_stmt * self, enviroment* env, call_context* cctx) {
	if(il_error_panic()) {
		return;
	}
	assert(self->lineno >= 0);
	il_error_file(env->context_ref->filename);
	il_error_line(self->lineno);
	switch (self->type) {
		case ilstmt_if:
			il_stmt_if_load(self->u.if_, env, cctx);
			break;
		case ilstmt_proc:
			il_stmt_proc_load(self->u.proc_, env, cctx);
			break;
		case ilstmt_variable_decl:
			il_stmt_variable_decl_load(self->u.variable_decl, env, cctx);
			break;
		case ilstmt_variable_init:
			il_stmt_variable_init_load(self->u.variable_init, env, cctx);
			break;
		case ilstmt_return:
			il_stmt_return_load(self->u.return_, env, cctx);
			break;
		case ilstmt_while:
			il_stmt_while_load(self->u.while_, env, cctx);
			break;
		case ilstmt_break:
			il_stmt_break_load(NULL, env, cctx);
			break;
		case ilstmt_continue:
			il_stmt_continue_load(NULL, env, cctx);
			break;
		case ilstmt_inferenced_type_init:
			il_stmt_inferenced_type_init_load(self->u.inferenced_type_init, env, cctx);
			break;
		case ilstmt_try:
			il_stmt_try_load(self->u.try_, env, cctx);
			break;
		case ilstmt_throw:
			il_stmt_throw_load(self->u.throw_, env, cctx);
			break;
		case ilstmt_assert:
			il_stmt_assert_load(self->u.bcassert_, env, cctx);
			break;
		case ilstmt_defer:
			il_stmt_defer_load(self->u.defer_, env, cctx);
			break;
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			break;
	}
}

void il_stmt_delete(il_stmt * self) {
	switch (self->type) {
		case ilstmt_if:
			il_stmt_if_delete(self->u.if_);
			break;
		case ilstmt_proc:
			il_stmt_proc_delete(self->u.proc_);
			break;
		case ilstmt_variable_decl:
			il_stmt_variable_decl_delete(self->u.variable_decl);
			break;
		case ilstmt_variable_init:
			il_stmt_variable_init_delete(self->u.variable_init);
			break;
		case ilstmt_return:
			il_stmt_return_delete(self->u.return_);
			break;
		case ilstmt_while:
			il_stmt_while_delete(self->u.while_);
			break;
		case ilstmt_break:
			il_stmt_break_delete(NULL);
			break;
		case ilstmt_continue:
			il_stmt_continue_delete(NULL);
			break;
		case ilstmt_inferenced_type_init:
			il_stmt_inferenced_type_init_delete(self->u.inferenced_type_init);
			break;
		case ilstmt_try:
			il_stmt_try_delete(self->u.try_);
			break;
		case ilstmt_throw:
			il_stmt_throw_delete(self->u.throw_);
			break;
		case ilstmt_assert:
			il_stmt_assert_delete(self->u.bcassert_);
			break;
		case ilstmt_defer:
			il_stmt_defer_delete(self->u.defer_);
			break;
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			{ int x = 0; }
			break;
	}
	MEM_FREE(self);
}
