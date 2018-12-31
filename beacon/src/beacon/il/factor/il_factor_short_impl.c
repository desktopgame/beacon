#include "il_factor_short_impl.h"
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
bc_ILFactor* bc_WrapILShort(bc_ILShort* self) {
        bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_SHORT_T);
        ret->Kind.Short = self;
        return ret;
}

bc_ILShort* bc_MallocILShort(short s, const char* filename, int lineno) {
        bc_ILShort* ret =
            (bc_ILShort*)bc_MXMalloc(sizeof(bc_ILShort), filename, lineno);
        ret->Value = s;
        ret->Count = 0;
        return ret;
}

void bc_GenerateILShort(bc_ILShort* self, bc_Enviroment* env,
                        bc_CallContext* cctx) {
        assert(self->Count == 0);
        int index = bc_AddCShortEnviroment(env, self->Value);
        bc_AddOpcodeBuf(env->Bytecode, OP_ICONST);
        bc_AddOpcodeBuf(env->Bytecode, index);
        self->Count++;
}

void bc_LoadILShort(bc_ILShort* self, bc_Enviroment* env,
                    bc_CallContext* cctx) {}

bc_GenericType* bc_EvalILShort(bc_ILShort* self, bc_Enviroment* env,
                               bc_CallContext* cctx) {
        return BC_GENERIC_SHORT;
}

char* bc_ILShortToString(bc_ILShort* self, bc_Enviroment* env) {
        bc_Buffer* sb = bc_NewBuffer();
        char block[32];
        int res = sprintf(block, "%d", self->Value);
        assert(res >= 0);
        bc_AppendsBuffer(sb, block);
        return bc_ReleaseBuffer(sb);
}

void bc_DeleteILShort(bc_ILShort* self) { MEM_FREE(self); }