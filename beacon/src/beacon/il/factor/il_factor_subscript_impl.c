#include "il_factor_subscript_impl.h"
#include "../../util/mem.h"
#include "../../util/io.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/operator_overload.h"

il_factor* WrapILSubscript(il_factor_subscript* self) {
	il_factor* ret = il_factor_new(ILFACTOR_SUBSCRIPT_T);
	ret->u.subscript = self;
	return ret;
}

il_factor_subscript* MallocILSubscript(const char* filename, int lineno) {
	il_factor_subscript* ret = mem_malloc(sizeof(il_factor_subscript), filename, lineno);
	ret->receiver = NULL;
	ret->pos = NULL;
	ret->operator_index = -1;
	ret->opov = NULL;
	return ret;
}

void GenerateILSubscript(il_factor_subscript* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->pos, env, cctx);
	GenerateILFactor(self->receiver, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, self->operator_index);
}

void LoadILSubscript(il_factor_subscript* self, Enviroment* env, CallContext* cctx) {
	if(self->operator_index != -1) {
		return;
	}
	LoadILFactor(self->receiver, env, cctx);
	LoadILFactor(self->pos, env, cctx);
	generic_type* receiver_gtype = EvalILFactor(self->receiver, env, cctx);
	generic_type* arg_gtype = EvalILFactor(self->pos, env, cctx);
	Vector* args = NewVector();
	PushVector(args, arg_gtype);
	int temp = -1;
	self->opov = GFindOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(receiver_gtype)), OPERATOR_SUB_SCRIPT_GET_T, args, env, cctx, &temp);
	self->operator_index = temp;
	DeleteVector(args, VectorDeleterOfNull);
}

generic_type* EvalILSubscript(il_factor_subscript* self, Enviroment* env, CallContext* cctx) {
	return ApplyGenericType(self->opov->ReturnGType, cctx);
}

char* ILSubscriptToString(il_factor_subscript* self, Enviroment* env) {
	Buffer* buf = NewBuffer();
	char* src = ILFactorToString(self->receiver, env);
	char* pos = ILFactorToString(self->pos, env);
	AppendsBuffer(buf, src);
	AppendBuffer(buf, '[');
	AppendsBuffer(buf, pos);
	AppendBuffer(buf, ']');
	MEM_FREE(src);
	MEM_FREE(pos);
	return ReleaseBuffer(buf);
}

void DeleteILSubscript(il_factor_subscript* self) {
	DeleteILFactor(self->receiver);
	DeleteILFactor(self->pos);
	MEM_FREE(self);
}