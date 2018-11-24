#include "il_factor_null_impl.h"
#include <stdio.h>
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../util/text.h"

static bc_GenericType* gSelf = NULL;

void bc_GenerateILNull(void* empty, bc_Enviroment* env, bc_CallContext* cctx) {
        bc_AddOpcodeBuf(env->Bytecode, OP_NULL);
}

void bc_LoadILNull(void* empty, bc_Enviroment* env, bc_CallContext* cctx) {}

bc_GenericType* bc_EvalILNull(void* empty, bc_Enviroment* env,
                              bc_CallContext* cctx) {
        if (gSelf == NULL) {
                gSelf = bc_NewGenericType(BC_TYPE_NULL);
        }
        return gSelf;
}

char* bc_ILNullToString(void* empty, bc_Enviroment* env) {
        return bc_Strdup("null");
}