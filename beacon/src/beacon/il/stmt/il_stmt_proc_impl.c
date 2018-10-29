#include "il_stmt_proc_impl.h"
#include "../../vm/enviroment.h"
#include <stdlib.h>
#include "../../util/mem.h"

ILStatement * WrapILProc(ILProc * self) {
	ILStatement* ret = ILStatement_new(ILSTMT_PROC_T);
	ret->u.proc_ = self;
	return ret;
}

ILProc * NewILProc() {
	ILProc* ret = (ILProc*)MEM_MALLOC(sizeof(ILProc));
	ret->factor = NULL;
	return ret;
}

void GenerateILProc(ILProc * self, Enviroment * env, CallContext* cctx) {
	GenerateILFactor(self->factor, env, cctx);
}

void LoadILProc(ILProc * self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->factor, env, cctx);
}

void DeleteILProc(ILProc * self) {
	DeleteILFactor(self->factor);
	MEM_FREE(self);
}
