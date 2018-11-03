#include "il_factor_char_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/TYPE_IMPL.h"
#include "../../util/mem.h"

ILFactor * WrapILChar(ILChar * self) {
	ILFactor* ret = NewILFactor(ILFACTOR_CHAR_T);
	ret->Kind.Char = self;
	return ret;
}

ILChar * NewILChar(char c) {
	ILChar* ret = (ILChar*)MEM_MALLOC(sizeof(ILChar));
	ret->Value = c;
	return ret;
}

void GenerateILChar(ILChar * self, Enviroment * env, CallContext* cctx) {
	int index = AddCCharEnviroment(env, self->Value);
	AddOpcodeBuf(env->Bytecode, OP_CCONST);
	AddOpcodeBuf(env->Bytecode, index);
}

void LoadILChar(ILChar * self, Enviroment * env, CallContext* cctx) {
}

GenericType* EvalILChar(ILChar * self, Enviroment * env, CallContext* cctx) {
	return GENERIC_CHAR;
}

char* ILCharToString(ILChar* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	AppendBuffer(sb, '\'');
	AppendBuffer(sb, self->Value);
	AppendBuffer(sb, '\'');
	return ReleaseBuffer(sb);
}

void DeleteILChar(ILChar * self) {
	MEM_FREE(self);
}