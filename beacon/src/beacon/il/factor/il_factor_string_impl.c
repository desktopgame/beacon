#include "il_factor_string_impl.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../env/TYPE_IMPL.h"
#include "../../env/type_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"

bc_ILFactor* bc_WrapILString(bc_ILString* self) {
        bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_STRING_T);
        ret->Kind.String = self;
        return ret;
}

bc_ILString* bc_NewILString(bc_StringView valuev) {
        bc_ILString* ret = (bc_ILString*)MEM_MALLOC(sizeof(bc_ILString));
        ret->Value = valuev;
        return ret;
}

void bc_GenerateILString(bc_ILString* self, bc_Enviroment* env,
                         bc_CallContext* cctx) {
        int index = bc_AddCStringEnviroment(env, self->Value);
        bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_SCONST);
        bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)index);
}

void bc_LoadILString(bc_ILString* self, bc_Enviroment* env,
                     bc_CallContext* cctx) {}

bc_GenericType* bc_EvalILString(bc_ILString* self, bc_Enviroment* env,
                                bc_CallContext* cctx) {
        //	assert(TYPE_STRING->GenericSelf->CoreType != NULL);
        return BC_GENERIC_STRING;
}

char* bc_ILStringToString(bc_ILString* self, bc_Enviroment* env) {
        return bc_Strdup(bc_Ref2Str(self->Value));
}

void bc_DeleteILString(bc_ILString* self) { MEM_FREE(self); }