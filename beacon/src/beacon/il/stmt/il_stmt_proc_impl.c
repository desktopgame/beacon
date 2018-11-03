#include "il_stmt_proc_impl.h"
#include "../../vm/enviroment.h"
#include <stdlib.h>
#include "../../util/mem.h"

ILStatement * WrapILProc(ILProc * self) {
	ILStatement* ret = NewILStatement(ILSTMT_PROC_T);
	ret->Kind.Proc = self;
	return ret;
}

ILProc * NewILProc() {
	ILProc* ret = (ILProc*)MEM_MALLOC(sizeof(ILProc));
	ret->Factor = NULL;
	return ret;
}

void GenerateILProc(ILProc * self, Enviroment * env, CallContext* cctx) {
	GenerateILFactor(self->Factor, env, cctx);
}

void LoadILProc(ILProc * self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->Factor, env, cctx);
}

void DeleteILProc(ILProc * self) {
	DeleteILFactor(self->Factor);
	MEM_FREE(self);
}
