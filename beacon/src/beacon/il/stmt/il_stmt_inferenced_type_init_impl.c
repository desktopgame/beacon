#include "il_stmt_inferenced_type_init_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/symbol_entry.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>
#include <string.h>

ILStatement * WrapILInferencedTypeInit(ILInferencedTypeInit * self) {
	ILStatement* ret = ILStatement_new(ILSTMT_INFERENCED_TYPE_INIT_T);
	ret->u.inferenced_type_init = self;
	return ret;
}

ILInferencedTypeInit * NewILInferencedTypeInit(StringView namev) {
	ILInferencedTypeInit* ret = (ILInferencedTypeInit*)MEM_MALLOC(sizeof(ILInferencedTypeInit));
	ret->namev = namev;
	ret->fact = NULL;
	return ret;
}

void GenerateILInferencedTypeInit(ILInferencedTypeInit * self, Enviroment * env, CallContext* cctx) {
	//右辺の方で宣言する
	GenerateILFactor(self->fact, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_STORE);
	AddOpcodeBuf(env->Bytecode, self->sym->Index);
}

void LoadILInferencedTypeInit(ILInferencedTypeInit * self, Enviroment * env, CallContext* cctx) {
	//代入するオブジェクトを計算
	LoadILFactor(self->fact, env, cctx);
	GenericType* gtp = EvalILFactor(self->fact, env, cctx);
	BC_ERROR();
	//voidは代入できない
	if(gtp->CoreType != NULL &&
	   gtp->CoreType == TYPE_VOID) {
		   ThrowBCError(BCERROR_VOID_ASSIGN_T);
		return;
	}
	//変数を登録
	if(IsContainsSymbol(env->Symboles, self->namev)) {
		ThrowBCError(BCERROR_OVERWRAP_VARIABLE_NAME_T,
			Ref2Str(self->namev)
		);
	}
	SymbolEntry* e = EntrySymbolTable(
		env->Symboles,
		gtp,
		self->namev
	);
	self->sym = e;
}

void DeleteILInferencedTypeInit(ILInferencedTypeInit * self) {
	DeleteILFactor(self->fact);
	MEM_FREE(self);
}
