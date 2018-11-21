#include "il_factor_char_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/TYPE_IMPL.h"
#include "../../util/mem.h"

bc_ILFactor * WrapILChar(ILChar * self) {
	bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_CHAR_T);
	ret->Kind.Char = self;
	return ret;
}

ILChar * NewILChar(char c) {
	ILChar* ret = (ILChar*)MEM_MALLOC(sizeof(ILChar));
	ret->Value = c;
	return ret;
}

void GenerateILChar(ILChar * self, bc_Enviroment * env, bc_CallContext* cctx) {
	int index = bc_AddCCharEnviroment(env, self->Value);
	bc_AddOpcodeBuf(env->Bytecode, OP_CCONST);
	bc_AddOpcodeBuf(env->Bytecode, index);
}

void LoadILChar(ILChar * self, bc_Enviroment * env, bc_CallContext* cctx) {
}

bc_GenericType* EvalILChar(ILChar * self, bc_Enviroment * env, bc_CallContext* cctx) {
	return BC_GENERIC_CHAR;
}

char* ILCharToString(ILChar* self, bc_Enviroment* env) {
	bc_Buffer* sb = bc_NewBuffer();
	bc_AppendBuffer(sb, '\'');
	bc_AppendBuffer(sb, self->Value);
	bc_AppendBuffer(sb, '\'');
	return bc_ReleaseBuffer(sb);
}

void DeleteILChar(ILChar * self) {
	MEM_FREE(self);
}