#include "il_stmt_inferenced_type_init_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/symbol_entry.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>
#include <string.h>

ILStatement * WrapILInferencedTypeInit(ILInferencedTypeInit * self) {
	ILStatement* ret = NewILStatement(ILSTMT_INFERENCED_TYPE_INIT_T);
	ret->Kind.InferencedTypeInit = self;
	return ret;
}

ILInferencedTypeInit * NewILInferencedTypeInit(StringView namev) {
	ILInferencedTypeInit* ret = (ILInferencedTypeInit*)MEM_MALLOC(sizeof(ILInferencedTypeInit));
	ret->Name = namev;
	ret->Value = NULL;
	return ret;
}

void GenerateILInferencedTypeInit(ILInferencedTypeInit * self, Enviroment * env, CallContext* cctx) {
	//右辺の方で宣言する
	GenerateILFactor(self->Value, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_STORE);
	AddOpcodeBuf(env->Bytecode, self->Symbol->Index);
}

void LoadILInferencedTypeInit(ILInferencedTypeInit * self, Enviroment * env, CallContext* cctx) {
	//代入するオブジェクトを計算
	LoadILFactor(self->Value, env, cctx);
	bc_GenericType* gtp = EvalILFactor(self->Value, env, cctx);
	BC_ERROR();
	//voidは代入できない
	if(gtp->CoreType != NULL &&
	   gtp->CoreType == BC_TYPE_VOID) {
		   bc_Panic(BCERROR_VOID_ASSIGN_T);
		return;
	}
	//変数を登録
	if(IsContainsSymbol(env->Symboles, self->Name)) {
		bc_Panic(BCERROR_OVERWRAP_VARIABLE_NAME_T,
			Ref2Str(self->Name)
		);
	}
	SymbolEntry* e = EntrySymbolTable(
		env->Symboles,
		gtp,
		self->Name
	);
	self->Symbol = e;
}

void DeleteILInferencedTypeInit(ILInferencedTypeInit * self) {
	DeleteILFactor(self->Value);
	MEM_FREE(self);
}
