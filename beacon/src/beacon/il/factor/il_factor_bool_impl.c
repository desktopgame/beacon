#include "il_factor_bool_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include "../../env/TYPE_IMPL.h"

ILFactor * WrapILBool(ILBool * self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_BOOL_T);
	ret->u.bool_ = self;
	return ret;
}

ILBool * NewILBool(bool b) {
	ILBool* ret = (ILBool*)MEM_MALLOC(sizeof(ILBool));
	ret->Value = b;
	return ret;
}

void GenerateILBool(ILBool * self, Enviroment * env, CallContext* cctx) {
	if (self->Value) {
		AddOpcodeBuf(env->Bytecode, OP_TRUE);
	} else {
		AddOpcodeBuf(env->Bytecode, OP_FALSE);
	}
}

GenericType* EvalILBool(ILBool * self, Enviroment * env, CallContext* cctx) {
	return GENERIC_BOOL;
}

char* ILBoolToString(ILBool* self, Enviroment* env) {
	return Strdup(self->Value ? "true" : "false");
}

void DeleteILBool(ILBool * self) {
	MEM_FREE(self);
}