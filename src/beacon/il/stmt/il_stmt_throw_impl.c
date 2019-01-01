#include "il_stmt_throw_impl.h"
#include <stdio.h>
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"

bc_ILStatement* bc_WrapILThrow(bc_ILThrow* self) {
        bc_ILStatement* ret = bc_NewILStatement(ILSTMT_THROW_T);
        ret->Kind.Throw = self;
        return ret;
}

bc_ILThrow* bc_NewILThrow() {
        bc_ILThrow* ret = (bc_ILThrow*)MEM_MALLOC(sizeof(bc_ILThrow));
        ret->Factor = NULL;
        return ret;
}

void bc_GenerateILThrow(bc_ILThrow* self, bc_Enviroment* env,
                        bc_CallContext* cctx) {
        bc_GenerateILFactor(self->Factor, env, cctx);
        bc_AddOpcodeBuf(env->Bytecode, OP_THROW);
}

void bc_LoadILThrow(bc_ILThrow* self, bc_Enviroment* env,
                    bc_CallContext* cctx) {
        bc_LoadILFactor(self->Factor, env, cctx);
        bc_GenericType* tgt = bc_EvalILFactor(self->Factor, env, cctx);
        if (bc_CdistanceGenericType(BC_GENERIC_EXCEPTION, tgt) < 0) {
                if (tgt->CoreType != NULL) {
                        bc_Panic(BCERROR_THROWN_NOT_EXCEPTION_TYPE_T,
                                 bc_Ref2Str(bc_GetTypeName(tgt->CoreType)));
                }
        }
}

void bc_DeleteILThrow(bc_ILThrow* self) {
        bc_DeleteILFactor(self->Factor);
        MEM_FREE(self);
}