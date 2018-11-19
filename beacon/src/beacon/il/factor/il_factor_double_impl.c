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

void GenerateILDouble(ILDouble * self, Enviroment* env, CallContext* cctx) {
	int index = AddCDoubleEnviroment(env, self->Value);
	AddOpcodeBuf(env->Bytecode, OP_DCONST);
	AddOpcodeBuf(env->Bytecode, index);
}

void LoadILDouble(ILDouble * self, Enviroment * env, CallContext* cctx) {
}

bc_GenericType* EvalILDouble(ILDouble * self, Enviroment * env, CallContext* cctx) {
	return BC_GENERIC_DOUBLE;
}

char* ILDoubleToString(ILDouble* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	char block[32] = {0};
	int res = sprintf(block, "%lf", self->Value);
	assert(res >= 0);
	AppendsBuffer(sb, block);
	return ReleaseBuffer(sb);
}

void DeleteILDouble(ILDouble * self) {
	MEM_FREE(self);
}