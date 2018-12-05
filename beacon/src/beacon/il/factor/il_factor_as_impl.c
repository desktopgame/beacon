#include "il_factor_as_impl.h"
#include <assert.h>
#include <stdio.h>
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"

bc_ILFactor* bc_WrapILAs(bc_ILAs* self) {
        bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_AS_T);
        ret->Kind.As = self;
        return ret;
}

bc_ILAs* bc_NewILAs() {
        bc_ILAs* ret = (bc_ILAs*)MEM_MALLOC(sizeof(bc_ILAs));
        ret->Source = NULL;
        ret->GCache = bc_NewGenericCache();
        ret->GType = NULL;
        ret->Mode = CAST_UNKNOWN_T;
        return ret;
}

void bc_GenerateILAs(bc_ILAs* self, bc_Enviroment* env, bc_CallContext* cctx) {
        bc_GenerateILFactor(self->Source, env, cctx);
        bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
        bc_GenerateGenericType(self->GType, env);
        if (self->Mode == CAST_DOWN_T) {
                bc_AddOpcodeBuf(env->Bytecode, OP_DOWN_AS);
        } else {
                bc_AddOpcodeBuf(env->Bytecode, OP_UP_AS);
        }
}

void bc_LoadILAs(bc_ILAs* self, bc_Enviroment* env, bc_CallContext* cctx) {
        if (self->GType != NULL) {
                return;
        }
        bc_LoadILFactor(self->Source, env, cctx);
        self->GType = bc_ResolveImportManager(bc_GetNamespaceByContext(cctx),
                                              self->GCache, cctx);
        bc_GenericType* a = bc_EvalILFactor(self->Source, env, cctx);
        //キャスト元がインターフェイスなら常にアップキャスト
        if (self->GType->CoreType != NULL &&
            bc_GENERIC2TYPE(self->GType)->Tag == TYPE_INTERFACE_T) {
                self->Mode = CAST_UP_T;
                return;
        }
        //キャスト先がインターフェイスなら常にアップキャスト
        if (a->CoreType != NULL &&
            bc_GENERIC2TYPE(a)->Tag == TYPE_INTERFACE_T) {
                self->Mode = CAST_DOWN_T;
                return;
        }
        //キャスト先がオブジェクトなら常にアップキャスト
        if (self->GType->CoreType != NULL &&
            self->GType->CoreType == BC_TYPE_OBJECT) {
                self->Mode = CAST_UP_T;
                return;
        }
        int downTo = bc_CdistanceGenericType(self->GType, a);
        int upTo = bc_CdistanceGenericType(a, self->GType);
        //ダウンキャスト
        if (downTo >= 0) {
                self->Mode = CAST_UP_T;
                //アップキャスト
        } else if (upTo >= 0) {
                self->Mode = CAST_DOWN_T;
                //それ以外
        } else {
                bc_Panic(BCERROR_CAST_NOT_COMPATIBLE_T,
                         bc_Ref2Str(bc_GetTypeName(a->CoreType)),
                         bc_Ref2Str(bc_GetTypeName(self->GType->CoreType)));
        }
}

bc_GenericType* bc_EvalILAs(bc_ILAs* self, bc_Enviroment* env,
                            bc_CallContext* cctx) {
        bc_LoadILAs(self, env, cctx);
        return self->GType;
}

void bc_DeleteILAs(bc_ILAs* self) {
        bc_DeleteGenericCache(self->GCache);
        bc_DeleteILFactor(self->Source);
        MEM_FREE(self);
}

char* bc_ILAsToString(bc_ILAs* self, bc_Enviroment* env) {
        bc_Buffer* sb = bc_NewBuffer();
        char* factstr = bc_ILFactorToString(self->Source, env);
        char* to = bc_GenericCacheToString(self->GCache);
        bc_AppendfBuffer(sb, "%s as %s", factstr, to);
        MEM_FREE(factstr);
        MEM_FREE(to);
        return bc_ReleaseBuffer(sb);
}