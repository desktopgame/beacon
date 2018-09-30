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

void il_factor_char_generate(il_factor_char * self, enviroment * env, call_context* cctx) {
	int index = AddCCharEnviroment(env, self->value);
	AddOpcodeBuf(env->buf, OP_CCONST);
	AddOpcodeBuf(env->buf, index);
}

void LoadILChar(il_factor_char * self, enviroment * env, call_context* cctx) {
}

generic_type* EvalILChar(il_factor_char * self, enviroment * env, call_context* cctx) {
	return GENERIC_CHAR;
}

char* ILCharToString(il_factor_char* self, enviroment* env) {
	string_buffer* sb = NewBuffer();
	AppendBuffer(sb, '\'');
	AppendBuffer(sb, self->value);
	AppendBuffer(sb, '\'');
	return ReleaseBuffer(sb);
}

void DeleteILChar(il_factor_char * self) {
	MEM_FREE(self);
}