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

bc_ILFactor * bc_WrapILDouble(bc_ILDouble * self) {
	bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_DOUBLE_T);
	ret->Kind.Double = self;
	return ret;
}

bc_ILDouble * bc_NewILDouble(double d) {
	bc_ILDouble* ret = (bc_ILDouble*)MEM_MALLOC(sizeof(bc_ILDouble));
	ret->Value = d;
	return ret;
}

void bc_GenerateILDouble(bc_ILDouble * self, bc_Enviroment* env, bc_CallContext* cctx) {
	int index = bc_AddCDoubleEnviroment(env, self->Value);
	bc_AddOpcodeBuf(env->Bytecode, OP_DCONST);
	bc_AddOpcodeBuf(env->Bytecode, index);
}

void bc_LoadILDouble(bc_ILDouble * self, bc_Enviroment * env, bc_CallContext* cctx) {
}

bc_GenericType* bc_EvalILDouble(bc_ILDouble * self, bc_Enviroment * env, bc_CallContext* cctx) {
	return BC_GENERIC_DOUBLE;
}

char* bc_ILDoubleToString(bc_ILDouble* self, bc_Enviroment* env) {
	bc_Buffer* sb = bc_NewBuffer();
	char block[32] = {0};
	int res = sprintf(block, "%lf", self->Value);
	assert(res >= 0);
	bc_AppendsBuffer(sb, block);
	return bc_ReleaseBuffer(sb);
}

void bc_DeleteILDouble(bc_ILDouble * self) {
	MEM_FREE(self);
}