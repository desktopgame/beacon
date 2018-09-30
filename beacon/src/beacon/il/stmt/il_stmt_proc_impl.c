#include "il_stmt_proc_impl.h"
#include "../../vm/enviroment.h"
#include <stdlib.h>
#include "../../util/mem.h"

il_stmt * WrapILProc(il_stmt_proc * self) {
	il_stmt* ret = il_stmt_new(ILSTMT_PROC_T);
	ret->u.proc_ = self;
	return ret;
}

il_stmt_proc * NewILProc() {
	il_stmt_proc* ret = (il_stmt_proc*)MEM_MALLOC(sizeof(il_stmt_proc));
	ret->factor = NULL;
	return ret;
}

void GenerateILProc(il_stmt_proc * self, enviroment * env, call_context* cctx) {
	GenerateILFactor(self->factor, env, cctx);
}

void LoadILProc(il_stmt_proc * self, struct enviroment* env, call_context* cctx) {
	LoadILFactor(self->factor, env, cctx);
}

void DeleteILProc(il_stmt_proc * self) {
	DeleteILFactor(self->factor);
	MEM_FREE(self);
}
