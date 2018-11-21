#include "il_stmt_proc_impl.h"
#include "../../vm/enviroment.h"
#include <stdlib.h>
#include "../../util/mem.h"

bc_ILStatement * WrapILProc(ILProc * self) {
	bc_ILStatement* ret = bc_NewILStatement(ILSTMT_PROC_T);
	ret->Kind.Proc = self;
	return ret;
}

ILProc * NewILProc() {
	ILProc* ret = (ILProc*)MEM_MALLOC(sizeof(ILProc));
	ret->Factor = NULL;
	return ret;
}

void GenerateILProc(ILProc * self, bc_Enviroment * env, bc_CallContext* cctx) {
	bc_GenerateILFactor(self->Factor, env, cctx);
}

void LoadILProc(ILProc * self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_LoadILFactor(self->Factor, env, cctx);
}

void DeleteILProc(ILProc * self) {
	bc_DeleteILFactor(self->Factor);
	MEM_FREE(self);
}
