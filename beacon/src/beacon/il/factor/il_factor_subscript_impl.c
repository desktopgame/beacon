#include "il_factor_subscript_impl.h"
#include "../../util/mem.h"
#include "../../util/io.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/operator_overload.h"

ILFactor* WrapILSubscript(ILSubscript* self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_SUBSCRIPT_T);
	ret->u.subscript = self;
	return ret;
}

ILSubscript* MallocILSubscript(const char* filename, int lineno) {
	ILSubscript* ret = mem_malloc(sizeof(ILSubscript), filename, lineno);
	ret->Receiver = NULL;
	ret->Position = NULL;
	ret->OperatorIndex = -1;
	ret->Operator = NULL;
	return ret;
}

void GenerateILSubscript(ILSubscript* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->Position, env, cctx);
	GenerateILFactor(self->Receiver, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
}

void LoadILSubscript(ILSubscript* self, Enviroment* env, CallContext* cctx) {
	if(self->OperatorIndex != -1) {
		return;
	}
	LoadILFactor(self->Receiver, env, cctx);
	LoadILFactor(self->Position, env, cctx);
	GenericType* receiver_gtype = EvalILFactor(self->Receiver, env, cctx);
	GenericType* arg_gtype = EvalILFactor(self->Position, env, cctx);
	Vector* args = NewVector();
	PushVector(args, arg_gtype);
	int temp = -1;
	self->Operator = GFindOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(receiver_gtype)), OPERATOR_SUB_SCRIPT_GET_T, args, env, cctx, &temp);
	self->OperatorIndex = temp;
	DeleteVector(args, VectorDeleterOfNull);
}

GenericType* EvalILSubscript(ILSubscript* self, Enviroment* env, CallContext* cctx) {
	return ApplyGenericType(self->Operator->ReturnGType, cctx);
}

char* ILSubscriptToString(ILSubscript* self, Enviroment* env) {
	Buffer* buf = NewBuffer();
	char* src = ILFactorToString(self->Receiver, env);
	char* pos = ILFactorToString(self->Position, env);
	AppendsBuffer(buf, src);
	AppendBuffer(buf, '[');
	AppendsBuffer(buf, pos);
	AppendBuffer(buf, ']');
	MEM_FREE(src);
	MEM_FREE(pos);
	return ReleaseBuffer(buf);
}

void DeleteILSubscript(ILSubscript* self) {
	DeleteILFactor(self->Receiver);
	DeleteILFactor(self->Position);
	MEM_FREE(self);
}