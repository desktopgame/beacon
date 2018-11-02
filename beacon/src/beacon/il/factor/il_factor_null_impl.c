#include "il_factor_null_impl.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

static GenericType* gSelf = NULL;

void GenerateILNull(void * empty, Enviroment * env, CallContext* cctx) {
	AddOpcodeBuf(env->Bytecode, OP_NULL);
}

void LoadILNull(void * empty, Enviroment * env, CallContext* cctx) {
}

GenericType* EvalILNull(void * empty, Enviroment * env, CallContext* cctx) {
	if(gSelf == NULL) {
		gSelf =  NewGenericType(TYPE_NULL);
	}
	return gSelf;
}

char* ILNullToString(void* empty, Enviroment* env) {
	return Strdup("null");
}