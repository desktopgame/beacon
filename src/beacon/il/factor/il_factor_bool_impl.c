#include "il_factor_bool_impl.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"

bc_ILFactor* bc_WrapILBool(bc_ILBool* self) {
        bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_BOOL_T);
        ret->Kind.Bool = self;
        return ret;
}

bc_ILBool* bc_NewILBool(bool b) {
        bc_ILBool* ret = (bc_ILBool*)MEM_MALLOC(sizeof(bc_ILBool));
        ret->Value = b;
        return ret;
}

void bc_GenerateILBool(bc_ILBool* self, bc_Enviroment* env,
                       bc_CallContext* cctx) {
        if (self->Value) {
                bc_AddOpcodeBuf(env->Bytecode, OP_TRUE);
        } else {
                bc_AddOpcodeBuf(env->Bytecode, OP_FALSE);
        }
}

bc_GenericType* bc_EvalILBool(bc_ILBool* self, bc_Enviroment* env,
                              bc_CallContext* cctx) {
        assert(BC_GENERIC_BOOL != NULL);
        return BC_GENERIC_BOOL;
}

char* bc_ILBoolToString(bc_ILBool* self, bc_Enviroment* env) {
        return bc_Strdup(self->Value ? "true" : "false");
}

void bc_DeleteILBool(bc_ILBool* self) { MEM_FREE(self); }