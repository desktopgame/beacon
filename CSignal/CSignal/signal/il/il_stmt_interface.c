#include "il_stmt_interface.h"
#include "il_stmt_impl.h"
#include "../util/logger.h"

void il_stmt_dump(il_stmt * self, int depth) {
	switch (self->type) {
		case ilstmt_if:
			il_stmt_if_dump(self->u.if_, depth);
			break;
		case ilstmt_proc:
			il_stmt_proc_dump(self->u.proc_, depth);
			break;
		default:
			//ERROR("ステートメントをダンプ出来ませんでした。");
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
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			break;
	}
	free(self);
}
