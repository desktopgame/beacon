#include "il_factor_null_impl.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

static bc_GenericType* gSelf = NULL;

void GenerateILNull(void * empty, bc_Enviroment * env, bc_CallContext* cctx) {
	bc_AddOpcodeBuf(env->Bytecode, OP_NULL);
}

void LoadILNull(void * empty, bc_Enviroment * env, bc_CallContext* cctx) {
}

bc_GenericType* EvalILNull(void * empty, bc_Enviroment * env, bc_CallContext* cctx) {
	if(gSelf == NULL) {
		gSelf =  bc_NewGenericType(BC_TYPE_NULL);
	}
	return gSelf;
}

char* ILNullToString(void* empty, bc_Enviroment* env) {
	return bc_Strdup("null");
}