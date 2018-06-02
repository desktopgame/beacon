#include "il_stmt_proc_impl.h"
#include "../../vm/enviroment.h"
#include <stdlib.h>
#include "../../util/mem.h"

il_stmt * il_stmt_wrap_proc(il_stmt_proc * self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt));
	ret->type = ilstmt_proc;
	ret->u.proc_ = self;
	return ret;
}

il_stmt_proc * il_stmt_proc_new() {
	il_stmt_proc* ret = (il_stmt_proc*)MEM_MALLOC(sizeof(il_stmt_proc));
	ret->factor = NULL;
	return ret;
}

void il_stmt_proc_dump(il_stmt_proc * self, int depth) {
	il_factor_dump(self->factor, depth);
}

void il_stmt_proc_generate(il_stmt_proc * self, enviroment * env) {
	il_factor_generate(self->factor, env);
}

void il_stmt_proc_load(il_stmt_proc * self, struct enviroment* env) {
	il_factor_load(self->factor, env);
}

void il_stmt_proc_delete(il_stmt_proc * self) {
	il_factor_delete(self->factor);
	MEM_FREE(self);
}
