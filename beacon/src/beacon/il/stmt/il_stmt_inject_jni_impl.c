#include "il_stmt_inject_jni_impl.h"
#include "../../util/mem.h"
#include "../../util/io.h"
#include "../../vm/symbol_entry.h"

ILStatement* WrapILInjectJNI(ILInjectJNI* self) {
	ILStatement* ret = NewILStatement(ILSTMT_INJECT_JNI_T);
	ret->Kind.InjectJNI = self;
	//JNIに関しては後からソースの先頭に付け加えられるので必ず0
	ret->Lineno = 0;
	return ret;
}

ILInjectJNI* NewILInjectJNI(StringView namev) {
	ILInjectJNI* ret = (ILInjectJNI*)MEM_MALLOC(sizeof(ILInjectJNI));
	ret->Name = namev;
	ret->Value = NULL;
	ret->Symbol = NULL;
	return ret;
}

void GenerateILInjectJNI(ILInjectJNI* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->Value, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_STORE);
	AddOpcodeBuf(env->Bytecode, self->Symbol->Index);
}

void LoadILInjectJNI(ILInjectJNI * self, Enviroment* env, CallContext* cctx) {
	if(self->Symbol != NULL) {
		return;
	}
	self->Value->Lineno = 0;
	LoadILFactor(self->Value, env, cctx);
	bc_GenericType* gtype = EvalILFactor(self->Value, env, cctx);
	self->Symbol = EntrySymbolTable(env->Symboles, gtype, self->Name);
}

void DeleteILInjectJni(ILInjectJNI* self) {
	DeleteILFactor(self->Value);
	MEM_FREE(self);
}