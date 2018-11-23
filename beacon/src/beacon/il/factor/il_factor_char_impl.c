#include "il_factor_char_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/TYPE_IMPL.h"
#include "../../util/mem.h"

bc_ILFactor * bc_WrapILChar(bc_ILChar * self) {
	bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_CHAR_T);
	ret->Kind.Char = self;
	return ret;
}

bc_ILChar * bc_NewILChar(char c) {
	bc_ILChar* ret = (bc_ILChar*)MEM_MALLOC(sizeof(bc_ILChar));
	ret->Value = c;
	return ret;
}

void bc_GenerateILChar(bc_ILChar * self, bc_Enviroment * env, bc_CallContext* cctx) {
	int index = bc_AddCCharEnviroment(env, self->Value);
	bc_AddOpcodeBuf(env->Bytecode, OP_CCONST);
	bc_AddOpcodeBuf(env->Bytecode, index);
}

void bc_LoadILChar(bc_ILChar * self, bc_Enviroment * env, bc_CallContext* cctx) {
}

bc_GenericType* bc_EvalILChar(bc_ILChar * self, bc_Enviroment * env, bc_CallContext* cctx) {
	return BC_GENERIC_CHAR;
}

char* bc_ILCharToString(bc_ILChar* self, bc_Enviroment* env) {
	bc_Buffer* sb = bc_NewBuffer();
	bc_AppendBuffer(sb, '\'');
	bc_AppendBuffer(sb, self->Value);
	bc_AppendBuffer(sb, '\'');
	return bc_ReleaseBuffer(sb);
}

void bc_DeleteILChar(bc_ILChar * self) {
	MEM_FREE(self);
}