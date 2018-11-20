#include "il_stmt_assert_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../il_factor_impl.h"
#include <assert.h>

ILStatement* WrapILAssert(ILAssert* self) {
	ILStatement* ret = NewILStatement(ILSTMT_ASSERT_T);
	ret->Kind.Assert = self;
	self->Parent = ret;
	return ret;
}

ILAssert* NewILAssert() {
	ILAssert* ret = (ILAssert*)MEM_MALLOC(sizeof(ILAssert));
	ret->Condition = NULL;
	ret->Message = NULL;
	ret->Parent = NULL;
	return ret;
}

void GenerateILAssert(ILAssert* self, bc_Enviroment* env, CallContext* cctx) {
	//https://code.i-harness.com/ja/q/2a1650
	bc_Label* gt = bc_AddLabelOpcodeBuf(env->Bytecode, 0);
	GenerateILFactor(self->Condition, env, cctx);
	bc_AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_TRUE);
	bc_AddOpcodeBuf(env->Bytecode, gt);

	GenerateILFactor(self->Message, env, cctx);
	bc_AddOpcodeBuf(env->Bytecode, OP_NEW_INSTANCE);
	bc_AddOpcodeBuf(env->Bytecode, bc_FindTypeFromNamespace(bc_GetLangNamespace(), bc_InternString("Exception"))->AbsoluteIndex);
	bc_AddOpcodeBuf(env->Bytecode, 0);
	bc_AddOpcodeBuf(env->Bytecode, OP_THROW);
	gt->Cursor = bc_AddNOPOpcodeBuf(env->Bytecode);
}

void LoadILAssert(ILAssert* self, bc_Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->Condition, env, cctx);
	if(self->Message == NULL) {
		char* str = ILFactorToString(self->Condition, env);
		ILString* ilstr = NewILString(bc_InternString(str));
		self->Message = WrapILString(ilstr);
		assert(ilstr->Value != 0);
		MEM_FREE(str);
		self->Message->Lineno = self->Parent->Lineno;
	}
	LoadILFactor(self->Message, env, cctx);
}

void DeleteILAssert(ILAssert* self) {
	DeleteILFactor(self->Condition);
	DeleteILFactor(self->Message);
	MEM_FREE(self);
}