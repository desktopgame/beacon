#include "il_stmt_interface.h"
#include "il_stmt_impl.h"
#include "../util/logger.h"
#include "../env/type_interface.h"
#include "../vm/enviroment.h"
#include "../util/mem.h"

void il_stmt_dump(il_stmt * self, int depth) {
	printf("<%d> ", self->lineno);
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
		default:
			//ERROR("ステートメントをダンプ出来ませんでした。");
			break;
	}
}

void il_stmt_generate(il_stmt * self, struct enviroment* env) {
	switch (self->type) {
		case ilstmt_if:
			il_stmt_if_generate(self->u.if_, env);
			//il_stmt_if_delete(self->u.if_);
			break;
		case ilstmt_proc:
			il_stmt_proc_generate(self->u.proc_, env);
			//il_stmt_proc_delete(self->u.proc_);
			break;
		case ilstmt_variable_decl:
			il_stmt_variable_decl_generate(self->u.variable_decl, env);
			break;
		case ilstmt_variable_init:
			il_stmt_variable_init_generate(self->u.variable_init, env);
			break;
		case ilstmt_return:
			il_stmt_return_generate(self->u.return_, env);
			break;
		case ilstmt_while:
			il_stmt_while_generate(self->u.while_, env);
			break;
		case ilstmt_break:
			il_stmt_break_generate(NULL, env);
			break;
		case ilstmt_continue:
			il_stmt_continue_generate(NULL, env);
			break;
		case ilstmt_inferenced_type_init:
			il_stmt_inferenced_type_init_generate(self->u.inferenced_type_init, env);
			break;
		case ilstmt_try:
			il_stmt_try_generate(self->u.try_, env);
			break;
		case ilstmt_throw:
			il_stmt_throw_generate(self->u.throw_, env);
			break;
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			break;
	}
	enviroment_add_range(env, self->lineno);
}

void il_stmt_load(il_stmt * self, enviroment* env, il_ehandler * eh) {
	switch (self->type) {
		case ilstmt_if:
			il_stmt_if_load(self->u.if_, env, eh);
			break;
		case ilstmt_proc:
			il_stmt_proc_load(self->u.proc_, env, eh);
			break;
		case ilstmt_variable_decl:
			il_stmt_variable_decl_load(self->u.variable_decl, env, eh);
			break;
		case ilstmt_variable_init:
			il_stmt_variable_init_load(self->u.variable_init, env, eh);
			break;
		case ilstmt_return:
			il_stmt_return_load(self->u.return_, env, eh);
			break;
		case ilstmt_while:
			//il_stmt_while_delete(self->u.while_);
			break;
		case ilstmt_break:
			il_stmt_break_load(NULL, env, eh);
			break;
		case ilstmt_continue:
			il_stmt_continue_load(NULL, env, eh);
			break;
		case ilstmt_inferenced_type_init:
			il_stmt_inferenced_type_init_load(self->u.inferenced_type_init, env, eh);
			break;
		case ilstmt_try:
			il_stmt_try_load(self->u.try_, env, eh);
			break;
		case ilstmt_throw:
			il_stmt_throw_load(self->u.throw_, env, eh);
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
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			{ int x = 0; }
			break;
	}
	MEM_FREE(self);
}
