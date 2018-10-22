#include "il_factor_bool_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include "../../env/TYPE_IMPL.h"

il_factor * WrapILBool(il_factor_bool * self) {
	il_factor* ret = il_factor_new(ILFACTOR_BOOL_T);
	ret->u.bool_ = self;
	return ret;
}

il_factor_bool * NewILBool(bool b) {
	il_factor_bool* ret = (il_factor_bool*)MEM_MALLOC(sizeof(il_factor_bool));
	ret->a = b;
	return ret;
}

void GenerateILBool(il_factor_bool * self, Enviroment * env, CallContext* cctx) {
	if (self->a) {
		AddOpcodeBuf(env->Bytecode, OP_TRUE);
	} else {
		AddOpcodeBuf(env->Bytecode, OP_FALSE);
	}
}

generic_type* EvalILBool(il_factor_bool * self, Enviroment * env, CallContext* cctx) {
	return GENERIC_BOOL;
}

char* ILBoolToString(il_factor_bool* self, Enviroment* env) {
	return Strdup(self->a ? "true" : "false");
}

void DeleteILBool(il_factor_bool * self) {
	MEM_FREE(self);
}