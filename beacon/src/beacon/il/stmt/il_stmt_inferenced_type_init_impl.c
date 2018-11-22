#include "il_stmt_inferenced_type_init_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/symbol_entry.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>
#include <string.h>

bc_ILStatement * bc_WrapILInferencedTypeInit(bc_ILInferencedTypeInit * self) {
	bc_ILStatement* ret = bc_NewILStatement(ILSTMT_INFERENCED_TYPE_INIT_T);
	ret->Kind.InferencedTypeInit = self;
	return ret;
}

bc_ILInferencedTypeInit * bc_NewILInferencedTypeInit(bc_StringView namev) {
	bc_ILInferencedTypeInit* ret = (bc_ILInferencedTypeInit*)MEM_MALLOC(sizeof(bc_ILInferencedTypeInit));
	ret->Name = namev;
	ret->Value = NULL;
	return ret;
}

void bc_GenerateILInferencedTypeInit(bc_ILInferencedTypeInit * self, bc_Enviroment * env, bc_CallContext* cctx) {
	//右辺の方で宣言する
	bc_GenerateILFactor(self->Value, env, cctx);
	bc_AddOpcodeBuf(env->Bytecode, OP_STORE);
	bc_AddOpcodeBuf(env->Bytecode, self->Symbol->Index);
}

void bc_LoadILInferencedTypeInit(bc_ILInferencedTypeInit * self, bc_Enviroment * env, bc_CallContext* cctx) {
	//代入するオブジェクトを計算
	bc_LoadILFactor(self->Value, env, cctx);
	bc_GenericType* gtp = bc_EvalILFactor(self->Value, env, cctx);
	BC_ERROR();
	//voidは代入できない
	if(gtp->CoreType != NULL &&
	   gtp->CoreType == BC_TYPE_VOID) {
		   bc_Panic(BCERROR_VOID_ASSIGN_T);
		return;
	}
	//変数を登録
	if(bc_IsContainsSymbol(env->Symboles, self->Name)) {
		bc_Panic(BCERROR_OVERWRAP_VARIABLE_NAME_T,
			bc_Ref2Str(self->Name)
		);
	}
	bc_SymbolEntry* e = bc_EntrySymbolTable(
		env->Symboles,
		gtp,
		self->Name
	);
	self->Symbol = e;
}

void bc_DeleteILInferencedTypeInit(bc_ILInferencedTypeInit * self) {
	bc_DeleteILFactor(self->Value);
	MEM_FREE(self);
}
