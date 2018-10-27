#include "il_stmt_inject_jni_impl.h"
#include "../../util/mem.h"
#include "../../util/io.h"
#include "../../vm/symbol_entry.h"

ILStatement* WrapILInjectJNI(ILStatement_inject_jni* self) {
	ILStatement* ret = ILStatement_new(ILSTMT_INJECT_JNI_T);
	ret->u.inject_jni = self;
	//JNIに関しては後からソースの先頭に付け加えられるので必ず0
	ret->lineno = 0;
	return ret;
}

ILStatement_inject_jni* NewILInjectJNI(StringView namev) {
	ILStatement_inject_jni* ret = (ILStatement_inject_jni*)MEM_MALLOC(sizeof(ILStatement_inject_jni));
	ret->namev = namev;
	ret->fact = NULL;
	ret->se = NULL;
	return ret;
}

void GenerateILInjectJNI(ILStatement_inject_jni* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->fact, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_STORE);
	AddOpcodeBuf(env->Bytecode, self->se->Index);
}

void LoadILInjectJNI(ILStatement_inject_jni * self, Enviroment* env, CallContext* cctx) {
	if(self->se != NULL) {
		return;
	}
	self->fact->lineno = 0;
	LoadILFactor(self->fact, env, cctx);
	GenericType* gtype = EvalILFactor(self->fact, env, cctx);
	self->se = EntrySymbolTable(env->Symboles, gtype, self->namev);
}

void DeleteILInjectJni(ILStatement_inject_jni* self) {
	DeleteILFactor(self->fact);
	MEM_FREE(self);
}