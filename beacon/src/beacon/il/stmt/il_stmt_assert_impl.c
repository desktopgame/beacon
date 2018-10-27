#include "il_stmt_assert_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../il_factor_impl.h"
#include <assert.h>

ILStatement* WrapILAssert(ILStatement_assert* self) {
	ILStatement* ret = ILStatement_new(ILSTMT_ASSERT_T);
	ret->u.bcassert_ = self;
	self->parent = ret;
	return ret;
}

ILStatement_assert* NewILAssert() {
	ILStatement_assert* ret = (ILStatement_assert*)MEM_MALLOC(sizeof(ILStatement_assert));
	ret->condition = NULL;
	ret->message = NULL;
	ret->parent = NULL;
	return ret;
}

void GenerateILAssert(ILStatement_assert* self, Enviroment* env, CallContext* cctx) {
	//https://code.i-harness.com/ja/q/2a1650
	Label* gt = AddLabelOpcodeBuf(env->Bytecode, 0);
	GenerateILFactor(self->condition, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_GOTO_IF_TRUE);
	AddOpcodeBuf(env->Bytecode, gt);

	GenerateILFactor(self->message, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_NEW_INSTANCE);
	AddOpcodeBuf(env->Bytecode, FindTypeFromNamespace(GetLangNamespace(), InternString("Exception"))->absolute_index);
	AddOpcodeBuf(env->Bytecode, 0);
	AddOpcodeBuf(env->Bytecode, OP_THROW);
	gt->Cursor = AddNOPOpcodeBuf(env->Bytecode);
}

void LoadILAssert(ILStatement_assert* self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->condition, env, cctx);
	if(self->message == NULL) {
		char* str = ILFactorToString(self->condition, env);
		ILFactor_string* ilstr = NewILString(InternString(str));
		self->message = WrapILString(ilstr);
		assert(ilstr->valuev != 0);
		MEM_FREE(str);
		self->message->lineno = self->parent->lineno;
	}
	LoadILFactor(self->message, env, cctx);
}

void DeleteILAssert(ILStatement_assert* self) {
	DeleteILFactor(self->condition);
	DeleteILFactor(self->message);
	MEM_FREE(self);
}