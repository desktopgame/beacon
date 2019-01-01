#include "il_factor_float_impl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../env/TYPE_IMPL.h"
#include "../../env/namespace.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#if defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif

bc_ILFactor* bc_WrapILFloat(bc_ILFloat* self) {
        bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_FLOAT_T);
        ret->Kind.Float = self;
        return ret;
}

bc_ILFloat* bc_NewILFloat(float f) {
        bc_ILFloat* ret = (bc_ILFloat*)MEM_MALLOC(sizeof(bc_ILFloat));
        ret->Value = f;
        return ret;
}

void bc_GenerateILFloat(bc_ILFloat* self, bc_Enviroment* env,
                        bc_CallContext* cctx) {
        int index = bc_AddCFloatEnviroment(env, self->Value);
        bc_AddOpcodeBuf(env->Bytecode, OP_FCONST);
        bc_AddOpcodeBuf(env->Bytecode, index);
}

void bc_LoadILFloat(bc_ILFloat* self, bc_Enviroment* env,
                    bc_CallContext* cctx) {}

bc_GenericType* bc_EvalILFloat(bc_ILFloat* self, bc_Enviroment* env,
                               bc_CallContext* cctx) {
        return BC_GENERIC_FLOAT;
}

char* bc_ILFloatToString(bc_ILFloat* self, bc_Enviroment* env) {
        bc_Buffer* sb = bc_NewBuffer();
        char block[32] = {0};
        int res = sprintf(block, "%lf", self->Value);
        assert(res >= 0);
        bc_AppendsBuffer(sb, block);
        return bc_ReleaseBuffer(sb);
}

void bc_DeleteILFloat(bc_ILFloat* self) { MEM_FREE(self); }