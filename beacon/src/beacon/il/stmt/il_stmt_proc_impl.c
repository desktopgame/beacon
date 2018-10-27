#include "il_stmt_proc_impl.h"
#include "../../vm/enviroment.h"
#include <stdlib.h>
#include "../../util/mem.h"

ILStatement * WrapILProc(ILStatement_proc * self) {
	ILStatement* ret = ILStatement_new(ILSTMT_PROC_T);
	ret->u.proc_ = self;
	return ret;
}

ILStatement_proc * NewILProc() {
	ILStatement_proc* ret = (ILStatement_proc*)MEM_MALLOC(sizeof(ILStatement_proc));
	ret->factor = NULL;
	return ret;
}

void GenerateILProc(ILStatement_proc * self, Enviroment * env, CallContext* cctx) {
	GenerateILFactor(self->factor, env, cctx);
}

void LoadILProc(ILStatement_proc * self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->factor, env, cctx);
}

void DeleteILProc(ILStatement_proc * self) {
	DeleteILFactor(self->factor);
	MEM_FREE(self);
}
