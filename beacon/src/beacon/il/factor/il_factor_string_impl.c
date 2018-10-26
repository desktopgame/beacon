#include "il_factor_string_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../env/TYPE_IMPL.h"
#include "../../util/mem.h"

il_factor * WrapILString(il_factor_string * self) {
	il_factor* ret = il_factor_new(ILFACTOR_STRING_T);
	ret->u.string_ = self;
	return ret;
}

il_factor_string * NewILString(StringView valuev) {
	il_factor_string* ret = (il_factor_string*)MEM_MALLOC(sizeof(il_factor_string));
	ret->valuev = valuev;
	return ret;
}

void GenerateILString(il_factor_string * self, Enviroment* env, CallContext* cctx) {
	int index = AddCStringEnviroment(env, self->valuev);
	AddOpcodeBuf(env->Bytecode, (VectorItem)OP_SCONST);
	AddOpcodeBuf(env->Bytecode, (VectorItem)index);
}

void LoadILString(il_factor_string * self, Enviroment * env, CallContext* cctx) {
}

GenericType* EvalILString(il_factor_string * self, Enviroment * env, CallContext* cctx) {
//	assert(TYPE_STRING->generic_self->core_type != NULL);
	return GENERIC_STRING;
}

char* ILStringToString(il_factor_string* self, Enviroment* env) {
	return Strdup(Ref2Str(self->valuev));
}

void DeleteILString(il_factor_string * self) {
	MEM_FREE(self);
}