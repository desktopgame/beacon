#include "il_factor_bool_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include "../../env/TYPE_IMPL.h"

ILFactor * WrapILBool(ILFactor_bool * self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_BOOL_T);
	ret->u.bool_ = self;
	return ret;
}

ILFactor_bool * NewILBool(bool b) {
	ILFactor_bool* ret = (ILFactor_bool*)MEM_MALLOC(sizeof(ILFactor_bool));
	ret->a = b;
	return ret;
}

void GenerateILBool(ILFactor_bool * self, Enviroment * env, CallContext* cctx) {
	if (self->a) {
		AddOpcodeBuf(env->Bytecode, OP_TRUE);
	} else {
		AddOpcodeBuf(env->Bytecode, OP_FALSE);
	}
}

GenericType* EvalILBool(ILFactor_bool * self, Enviroment * env, CallContext* cctx) {
	return GENERIC_BOOL;
}

char* ILBoolToString(ILFactor_bool* self, Enviroment* env) {
	return Strdup(self->a ? "true" : "false");
}

void DeleteILBool(ILFactor_bool * self) {
	MEM_FREE(self);
}