#include "il_factor_long_impl.h"
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
bc_ILFactor* bc_WrapILLong(bc_ILLong* self) {
        bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_LONG_T);
        ret->Kind.Long = self;
        return ret;
}

bc_ILLong* bc_MallocILLong(short s, const char* filename, int lineno) {
        bc_ILLong* ret =
            (bc_ILLong*)bc_MXMalloc(sizeof(bc_ILLong), filename, lineno);
        ret->Value = s;
        ret->Count = 0;
        return ret;
}

void bc_GenerateILLong(bc_ILLong* self, bc_Enviroment* env,
                       bc_CallContext* cctx) {
        assert(self->Count == 0);
        int index = bc_AddCLongEnviroment(env, self->Value);
        bc_AddOpcodeBuf(env->Bytecode, OP_LCONST);
        bc_AddOpcodeBuf(env->Bytecode, index);
        self->Count++;
}

void bc_LoadILLong(bc_ILLong* self, bc_Enviroment* env, bc_CallContext* cctx) {}

bc_GenericType* bc_EvalILLong(bc_ILLong* self, bc_Enviroment* env,
                              bc_CallContext* cctx) {
        return BC_GENERIC_SHORT;
}

char* bc_ILLongToString(bc_ILLong* self, bc_Enviroment* env) {
        bc_Buffer* sb = bc_NewBuffer();
        char block[32];
        int res = sprintf(block, "%ld", self->Value);
        assert(res >= 0);
        bc_AppendsBuffer(sb, block);
        return bc_ReleaseBuffer(sb);
}

void bc_DeleteILLong(bc_ILLong* self) { MEM_FREE(self); }