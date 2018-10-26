#include "il_factor_char_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/TYPE_IMPL.h"
#include "../../util/mem.h"

il_factor * WrapILChar(il_factor_char * self) {
	il_factor* ret = il_factor_new(ILFACTOR_CHAR_T);
	ret->u.char_ = self;
	return ret;
}

il_factor_char * NewILChar(char c) {
	il_factor_char* ret = (il_factor_char*)MEM_MALLOC(sizeof(il_factor_char));
	ret->value = c;
	return ret;
}

void GenerateILChar(il_factor_char * self, Enviroment * env, CallContext* cctx) {
	int index = AddCCharEnviroment(env, self->value);
	AddOpcodeBuf(env->Bytecode, OP_CCONST);
	AddOpcodeBuf(env->Bytecode, index);
}

void LoadILChar(il_factor_char * self, Enviroment * env, CallContext* cctx) {
}

GenericType* EvalILChar(il_factor_char * self, Enviroment * env, CallContext* cctx) {
	return GENERIC_CHAR;
}

char* ILCharToString(il_factor_char* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	AppendBuffer(sb, '\'');
	AppendBuffer(sb, self->value);
	AppendBuffer(sb, '\'');
	return ReleaseBuffer(sb);
}

void DeleteILChar(il_factor_char * self) {
	MEM_FREE(self);
}