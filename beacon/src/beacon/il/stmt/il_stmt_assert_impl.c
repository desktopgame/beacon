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

void GenerateILAssert(ILAssert* self, Enviroment* env, CallContext* cctx) {
	//https://code.i-harness.com/ja/q/2a1650
	Label* gt = AddLabelOpcodeBuf(env->Bytecode, 0);
	GenerateILFactor(self->Condition, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_TRUE);
	AddOpcodeBuf(env->Bytecode, gt);

	GenerateILFactor(self->Message, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_NEW_INSTANCE);
	AddOpcodeBuf(env->Bytecode, bc_FindTypeFromNamespace(bc_GetLangNamespace(), InternString("Exception"))->AbsoluteIndex);
	AddOpcodeBuf(env->Bytecode, 0);
	AddOpcodeBuf(env->Bytecode, OP_THROW);
	gt->Cursor = AddNOPOpcodeBuf(env->Bytecode);
}

void LoadILAssert(ILAssert* self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->Condition, env, cctx);
	if(self->Message == NULL) {
		char* str = ILFactorToString(self->Condition, env);
		ILString* ilstr = NewILString(InternString(str));
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