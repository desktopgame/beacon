#include "il_stmt_inject_jni_impl.h"
#include "../../util/mem.h"
#include "../../util/io.h"
#include "../../vm/symbol_entry.h"

bc_ILStatement* bc_WrapILInjectJNI(bc_ILInjectJNI* self) {
	bc_ILStatement* ret = bc_NewILStatement(ILSTMT_INJECT_JNI_T);
	ret->Kind.InjectJNI = self;
	//JNIに関しては後からソースの先頭に付け加えられるので必ず0
	ret->Lineno = 0;
	return ret;
}

bc_ILInjectJNI* bc_NewILInjectJNI(bc_StringView namev) {
	bc_ILInjectJNI* ret = (bc_ILInjectJNI*)MEM_MALLOC(sizeof(bc_ILInjectJNI));
	ret->Name = namev;
	ret->Value = NULL;
	ret->Symbol = NULL;
	return ret;
}

void bc_GenerateILInjectJNI(bc_ILInjectJNI* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_GenerateILFactor(self->Value, env, cctx);
	bc_AddOpcodeBuf(env->Bytecode, OP_STORE);
	bc_AddOpcodeBuf(env->Bytecode, self->Symbol->Index);
}

void bc_LoadILInjectJNI(bc_ILInjectJNI * self, bc_Enviroment* env, bc_CallContext* cctx) {
	if(self->Symbol != NULL) {
		return;
	}
	self->Value->Lineno = 0;
	bc_LoadILFactor(self->Value, env, cctx);
	bc_GenericType* gtype = bc_EvalILFactor(self->Value, env, cctx);
	self->Symbol = bc_EntrySymbolTable(env->Symboles, gtype, self->Name);
}

void bc_DeleteILInjectJni(bc_ILInjectJNI* self) {
	bc_DeleteILFactor(self->Value);
	MEM_FREE(self);
}