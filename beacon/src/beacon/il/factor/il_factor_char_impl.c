#include "il_factor_char_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/TYPE_IMPL.h"
#include "../../util/mem.h"

ILFactor * WrapILChar(ILFactor_char * self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_CHAR_T);
	ret->u.char_ = self;
	return ret;
}

ILFactor_char * NewILChar(char c) {
	ILFactor_char* ret = (ILFactor_char*)MEM_MALLOC(sizeof(ILFactor_char));
	ret->value = c;
	return ret;
}

void GenerateILChar(ILFactor_char * self, Enviroment * env, CallContext* cctx) {
	int index = AddCCharEnviroment(env, self->value);
	AddOpcodeBuf(env->Bytecode, OP_CCONST);
	AddOpcodeBuf(env->Bytecode, index);
}

void LoadILChar(ILFactor_char * self, Enviroment * env, CallContext* cctx) {
}

GenericType* EvalILChar(ILFactor_char * self, Enviroment * env, CallContext* cctx) {
	return GENERIC_CHAR;
}

char* ILCharToString(ILFactor_char* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	AppendBuffer(sb, '\'');
	AppendBuffer(sb, self->value);
	AppendBuffer(sb, '\'');
	return ReleaseBuffer(sb);
}

void DeleteILChar(ILFactor_char * self) {
	MEM_FREE(self);
}