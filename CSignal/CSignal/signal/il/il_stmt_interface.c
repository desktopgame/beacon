#include "il_stmt_interface.h"
#include "il_stmt_impl.h"
#include "../util/logger.h"
#include "../env/class.h"
#include "../vm/enviroment.h"
#include "../util/mem.h"

void il_stmt_dump(il_stmt * self, int depth) {
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
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			break;
	}
	MEM_FREE(self);
}
