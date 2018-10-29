#include "il_stmt_inject_jni_impl.h"
#include "../../util/mem.h"
#include "../../util/io.h"
#include "../../vm/symbol_entry.h"

ILStatement* WrapILInjectJNI(ILInjectJNI* self) {
	ILStatement* ret = ILStatement_new(ILSTMT_INJECT_JNI_T);
	ret->u.inject_jni = self;
	//JNIに関しては後からソースの先頭に付け加えられるので必ず0
	ret->lineno = 0;
	return ret;
}

ILInjectJNI* NewILInjectJNI(StringView namev) {
	ILInjectJNI* ret = (ILInjectJNI*)MEM_MALLOC(sizeof(ILInjectJNI));
	ret->namev = namev;
	ret->fact = NULL;
	ret->se = NULL;
	return ret;
}

void GenerateILInjectJNI(ILInjectJNI* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->fact, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_STORE);
	AddOpcodeBuf(env->Bytecode, self->se->Index);
}

void LoadILInjectJNI(ILInjectJNI * self, Enviroment* env, CallContext* cctx) {
	if(self->se != NULL) {
		return;
	}
	self->fact->lineno = 0;
	LoadILFactor(self->fact, env, cctx);
	GenericType* gtype = EvalILFactor(self->fact, env, cctx);
	self->se = EntrySymbolTable(env->Symboles, gtype, self->namev);
}

void DeleteILInjectJni(ILInjectJNI* self) {
	DeleteILFactor(self->fact);
	MEM_FREE(self);
}