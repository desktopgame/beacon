#include "il_stmt_proc_impl.h"
#include "../../vm/enviroment.h"
#include <stdlib.h>
#include "../../util/mem.h"

bc_ILStatement * bc_WrapILProc(bc_ILProc * self) {
	bc_ILStatement* ret = bc_NewILStatement(ILSTMT_PROC_T);
	ret->Kind.Proc = self;
	return ret;
}

bc_ILProc * bc_NewILProc() {
	bc_ILProc* ret = (bc_ILProc*)MEM_MALLOC(sizeof(bc_ILProc));
	ret->Factor = NULL;
	return ret;
}

void bc_GenerateILProc(bc_ILProc * self, bc_Enviroment * env, bc_CallContext* cctx) {
	bc_GenerateILFactor(self->Factor, env, cctx);
}

void bc_LoadILProc(bc_ILProc * self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_LoadILFactor(self->Factor, env, cctx);
}

void bc_DeleteILProc(bc_ILProc * self) {
	bc_DeleteILFactor(self->Factor);
	MEM_FREE(self);
}
