#include "il_factor_null_impl.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

static generic_type* gSelf = NULL;

void GenerateILNull(void * empty, Enviroment * env, call_context* cctx) {
	AddOpcodeBuf(env->Bytecode, OP_NULL);
}

void LoadILNull(void * empty, Enviroment * env, call_context* cctx) {
}

generic_type* EvalILNull(void * empty, Enviroment * env, call_context* cctx) {
	if(gSelf == NULL) {
		gSelf =  generic_NewType(TYPE_NULL);
	}
	return gSelf;
}

char* ILNullToString(void* empty, Enviroment* env) {
	return Strdup("null");
}