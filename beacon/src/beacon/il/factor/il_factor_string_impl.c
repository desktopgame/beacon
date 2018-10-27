#include "il_factor_string_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../env/TYPE_IMPL.h"
#include "../../util/mem.h"

ILFactor * WrapILString(ILFactor_string * self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_STRING_T);
	ret->u.string_ = self;
	return ret;
}

ILFactor_string * NewILString(StringView valuev) {
	ILFactor_string* ret = (ILFactor_string*)MEM_MALLOC(sizeof(ILFactor_string));
	ret->valuev = valuev;
	return ret;
}

void GenerateILString(ILFactor_string * self, Enviroment* env, CallContext* cctx) {
	int index = AddCStringEnviroment(env, self->valuev);
	AddOpcodeBuf(env->Bytecode, (VectorItem)OP_SCONST);
	AddOpcodeBuf(env->Bytecode, (VectorItem)index);
}

void LoadILString(ILFactor_string * self, Enviroment * env, CallContext* cctx) {
}

GenericType* EvalILString(ILFactor_string * self, Enviroment * env, CallContext* cctx) {
//	assert(TYPE_STRING->generic_self->CoreType != NULL);
	return GENERIC_STRING;
}

char* ILStringToString(ILFactor_string* self, Enviroment* env) {
	return Strdup(Ref2Str(self->valuev));
}

void DeleteILString(ILFactor_string * self) {
	MEM_FREE(self);
}