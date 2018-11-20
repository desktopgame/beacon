#include "il_factor_double_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/TYPE_IMPL.h"
#include "../../util/mem.h"
#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

ILFactor * WrapILDouble(ILDouble * self) {
	ILFactor* ret = NewILFactor(ILFACTOR_DOUBLE_T);
	ret->Kind.Double = self;
	return ret;
}

ILDouble * NewILDouble(double d) {
	ILDouble* ret = (ILDouble*)MEM_MALLOC(sizeof(ILDouble));
	ret->Value = d;
	return ret;
}

void GenerateILDouble(ILDouble * self, bc_Enviroment* env, CallContext* cctx) {
	int index = bc_AddCDoubleEnviroment(env, self->Value);
	bc_AddOpcodeBuf(env->Bytecode, OP_DCONST);
	bc_AddOpcodeBuf(env->Bytecode, index);
}

void LoadILDouble(ILDouble * self, bc_Enviroment * env, CallContext* cctx) {
}

bc_GenericType* EvalILDouble(ILDouble * self, bc_Enviroment * env, CallContext* cctx) {
	return BC_GENERIC_DOUBLE;
}

char* ILDoubleToString(ILDouble* self, bc_Enviroment* env) {
	bc_Buffer* sb = bc_NewBuffer();
	char block[32] = {0};
	int res = sprintf(block, "%lf", self->Value);
	assert(res >= 0);
	bc_AppendsBuffer(sb, block);
	return bc_ReleaseBuffer(sb);
}

void DeleteILDouble(ILDouble * self) {
	MEM_FREE(self);
}