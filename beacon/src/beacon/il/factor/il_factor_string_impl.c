#include "il_factor_string_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../env/TYPE_IMPL.h"
#include "../../util/mem.h"

bc_ILFactor * WrapILString(ILString * self) {
	bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_STRING_T);
	ret->Kind.String = self;
	return ret;
}

ILString * NewILString(bc_StringView valuev) {
	ILString* ret = (ILString*)MEM_MALLOC(sizeof(ILString));
	ret->Value = valuev;
	return ret;
}

void GenerateILString(ILString * self, bc_Enviroment* env, bc_CallContext* cctx) {
	int index = bc_AddCStringEnviroment(env, self->Value);
	bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_SCONST);
	bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)index);
}

void LoadILString(ILString * self, bc_Enviroment * env, bc_CallContext* cctx) {
}

bc_GenericType* EvalILString(ILString * self, bc_Enviroment * env, bc_CallContext* cctx) {
//	assert(TYPE_STRING->GenericSelf->CoreType != NULL);
	return BC_GENERIC_STRING;
}

char* ILStringToString(ILString* self, bc_Enviroment* env) {
	return bc_Strdup(bc_Ref2Str(self->Value));
}

void DeleteILString(ILString * self) {
	MEM_FREE(self);
}