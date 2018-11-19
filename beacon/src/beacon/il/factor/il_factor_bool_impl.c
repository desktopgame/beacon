#include "il_factor_bool_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include "../../env/TYPE_IMPL.h"

ILFactor * WrapILBool(ILBool * self) {
	ILFactor* ret = NewILFactor(ILFACTOR_BOOL_T);
	ret->Kind.Bool = self;
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

bc_GenericType* EvalILBool(ILBool * self, Enviroment * env, CallContext* cctx) {
	return BC_GENERIC_BOOL;
}

char* ILBoolToString(ILBool* self, Enviroment* env) {
	return bc_Strdup(self->Value ? "true" : "false");
}

void DeleteILBool(ILBool * self) {
	MEM_FREE(self);
}