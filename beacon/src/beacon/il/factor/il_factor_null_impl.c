#include "il_factor_null_impl.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

static generic_type* gSelf = NULL;

void GenerateILNull(void * empty, enviroment * env, call_context* cctx) {
	AddOpcodeBuf(env->buf, OP_NULL);
}

void LoadILNull(void * empty, enviroment * env, call_context* cctx) {
}

generic_type* EvalILNull(void * empty, enviroment * env, call_context* cctx) {
	if(gSelf == NULL) {
		gSelf =  generic_NewType(TYPE_NULL);
	}
	return gSelf;
}

char* ILNullToString(void* empty, enviroment* env) {
	return Strdup("null");
}