#include "il_factor_string_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../env/TYPE_IMPL.h"
#include "../../util/mem.h"

ILFactor * WrapILString(ILString * self) {
	ILFactor* ret = NewILFactor(ILFACTOR_STRING_T);
	ret->Kind.String = self;
	return ret;
}

ILString * NewILString(StringView valuev) {
	ILString* ret = (ILString*)MEM_MALLOC(sizeof(ILString));
	ret->Value = valuev;
	return ret;
}

void GenerateILString(ILString * self, bc_Enviroment* env, CallContext* cctx) {
	int index = bc_AddCStringEnviroment(env, self->Value);
	bc_AddOpcodeBuf(env->Bytecode, (VectorItem)OP_SCONST);
	bc_AddOpcodeBuf(env->Bytecode, (VectorItem)index);
}

void LoadILString(ILString * self, bc_Enviroment * env, CallContext* cctx) {
}

bc_GenericType* EvalILString(ILString * self, bc_Enviroment * env, CallContext* cctx) {
//	assert(TYPE_STRING->GenericSelf->CoreType != NULL);
	return BC_GENERIC_STRING;
}

char* ILStringToString(ILString* self, bc_Enviroment* env) {
	return bc_Strdup(Ref2Str(self->Value));
}

void DeleteILString(ILString * self) {
	MEM_FREE(self);
}