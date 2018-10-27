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

ILFactor * WrapILDouble(ILFactor_double * self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_DOUBLE_T);
	ret->u.double_ = self;
	return ret;
}

ILFactor_double * NewILDouble(double d) {
	ILFactor_double* ret = (ILFactor_double*)MEM_MALLOC(sizeof(ILFactor_double));
	ret->value = d;
	return ret;
}

void GenerateILDouble(ILFactor_double * self, Enviroment* env, CallContext* cctx) {
	int index = AddCDoubleEnviroment(env, self->value);
	AddOpcodeBuf(env->Bytecode, OP_DCONST);
	AddOpcodeBuf(env->Bytecode, index);
}

void LoadILDouble(ILFactor_double * self, Enviroment * env, CallContext* cctx) {
}

GenericType* EvalILDouble(ILFactor_double * self, Enviroment * env, CallContext* cctx) {
	return GENERIC_DOUBLE;
}

char* ILDoubleToString(ILFactor_double* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	char block[32] = {0};
	int res = sprintf(block, "%lf", self->value);
	assert(res >= 0);
	AppendsBuffer(sb, block);
	return ReleaseBuffer(sb);
}

void DeleteILDouble(ILFactor_double * self) {
	MEM_FREE(self);
}