#include "il_stmt_proc_impl.h"
#include <stdlib.h>

il_stmt * il_stmt_wrap_proc(il_stmt_proc * self) {
	il_stmt* ret = (il_stmt*)malloc(sizeof(il_stmt));
	ret->type = stmt_proc;
	ret->u.proc_ = self;
	return ret;
}

il_stmt_proc * il_stmt_proc_new() {
	il_stmt_proc* ret = (il_stmt_proc*)malloc(sizeof(il_stmt_proc));
	ret->factor = NULL;
	return ret;
}

void il_stmt_proc_dump(il_stmt_proc * self, int depth) {
	il_factor_dump(self->factor, depth);
}

void il_stmt_proc_delete(il_stmt_proc * self) {
	il_factor_delete(self->factor);
	free(self);
}
