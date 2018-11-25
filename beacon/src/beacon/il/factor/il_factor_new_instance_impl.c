#include "il_factor_new_instance_impl.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../env/TYPE_IMPL.h"
#include "../../env/class_loader.h"
#include "../../env/constructor.h"
#include "../../env/import_manager.h"
#include "../../env/type_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../il_argument.h"
#include "../il_type_argument.h"

// proto
static void DeleteILNewInstance_typearg(bc_VectorItem item);
static void ILNewInstance_find(bc_ILNewInstance* self, bc_Enviroment* env,
                               bc_CallContext* cctx);
static void il_Factor_new_instace_delete_arg(bc_VectorItem item);

bc_ILFactor* bc_WrapILNewInstance(bc_ILNewInstance* self) {
        bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_NEW_INSTANCE_T);
        ret->Kind.NewInstance = self;
        return ret;
}

bc_ILNewInstance* bc_NewILNewInstance() {
        bc_ILNewInstance* ret =
            (bc_ILNewInstance*)MEM_MALLOC(sizeof(bc_ILNewInstance));
        ret->FQCNCache = bc_NewFQCNCache();
        ret->TypeArgs = bc_NewVector();
        ret->Arguments = bc_NewVector();
        ret->Constructor = NULL;
        ret->ConstructorIndex = -1;
        ret->InstanceGType = NULL;
        return ret;
}

void bc_GenerateILNewInstance(bc_ILNewInstance* self, bc_Enviroment* env,
                              bc_CallContext* cctx) {
        ILNewInstance_find(self, env, cctx);
        for (int i = 0; i < self->TypeArgs->Length; i++) {
                bc_ILTypeArgument* e =
                    (bc_ILTypeArgument*)bc_AtVector(self->TypeArgs, i);
                assert(e->GType != NULL);
                bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
                bc_GenerateGenericType(e->GType, env);
        }
        //実引数を全てスタックへ
        for (int i = 0; i < self->Arguments->Length; i++) {
                bc_ILArgument* ilarg =
                    (bc_ILArgument*)bc_AtVector(self->Arguments, i);
                bc_GenerateILFactor(ilarg->Factor, env, cctx);
                if (bc_GetLastPanic()) {
                        return;
                }
        }
        //クラスとコンストラクタのインデックスをプッシュ
        bc_AddOpcodeBuf(env->Bytecode, OP_NEW_INSTANCE);
        bc_AddOpcodeBuf(env->Bytecode,
                        BC_MEMBER_TYPE(self->Constructor)->AbsoluteIndex);
        bc_AddOpcodeBuf(env->Bytecode, self->ConstructorIndex);
}

void bc_LoadILNewInstance(bc_ILNewInstance* self, bc_Enviroment* env,
                          bc_CallContext* cctx) {
        ILNewInstance_find(self, env, cctx);
        if (bc_GetLastPanic()) {
                return;
        }
        //抽象クラスはインスタンス化できない
        if (bc_IsAbstractType(BC_MEMBER_TYPE(self->Constructor))) {
                bc_Panic(BCERROR_CONSTRUCT_ABSTRACT_TYPE_T,
                         bc_Ref2Str(bc_GetTypeName(
                             BC_MEMBER_TYPE(self->Constructor))));
        }
}

bc_GenericType* bc_EvalILNewInstance(bc_ILNewInstance* self, bc_Enviroment* env,
                                     bc_CallContext* cctx) {
        ILNewInstance_find(self, env, cctx);
        if (bc_GetLastPanic()) {
                return NULL;
        }
        //型引数がないのでそのまま
        if (self->TypeArgs->Length == 0) {
                bc_GenericType* ret =
                    bc_RefGenericType(BC_MEMBER_TYPE(self->Constructor));
                return ret;
        }
        // FQCNCache typename_group
        if (self->InstanceGType == NULL) {
                bc_Namespace* scope = NULL;
                bc_GenericType* a =
                    bc_NewGenericType(BC_MEMBER_TYPE(self->Constructor));
                for (int i = 0; i < self->TypeArgs->Length; i++) {
                        bc_ILTypeArgument* e =
                            (bc_ILTypeArgument*)bc_AtVector(self->TypeArgs, i);
                        bc_GenericType* arg = bc_ResolveImportManager(
                            bc_GetNamespaceCContext(cctx), e->GCache, cctx);
                        bc_AddArgsGenericType(a, arg);
                }
                self->InstanceGType = a;
        }
        return self->InstanceGType;
}

char* bc_ILNewInstanceToString(bc_ILNewInstance* self, bc_Enviroment* env) {
        bc_Buffer* sb = bc_NewBuffer();
        bc_AppendsBuffer(sb, "new ");
        char* type = bc_FQCNCacheToString(self->FQCNCache);
        bc_AppendsBuffer(sb, type);
        bc_ILTypeArgsToString(sb, self->TypeArgs, env);
        bc_ILArgsToString(sb, self->Arguments, env);
        MEM_FREE(type);
        return bc_ReleaseBuffer(sb);
}

void bc_DeleteILNewInstance(bc_ILNewInstance* self) {
        bc_DeleteVector(self->Arguments, il_Factor_new_instace_delete_arg);
        bc_DeleteVector(self->TypeArgs, DeleteILNewInstance_typearg);
        bc_DeleteFQCNCache(self->FQCNCache);
        MEM_FREE(self);
}

// private
static void DeleteILNewInstance_typearg(bc_VectorItem item) {
        bc_ILTypeArgument* e = (bc_ILTypeArgument*)item;
        bc_DeleteILTypeArgument(e);
}

static void ILNewInstance_find(bc_ILNewInstance* self, bc_Enviroment* env,
                               bc_CallContext* cctx) {
        if (self->ConstructorIndex != -1) {
                return;
        }
#if defined(DEBUG)
        const char* namea = bc_Ref2Str(self->FQCNCache->Name);
        if (self->FQCNCache->Name == bc_InternString("Vector")) {
                int a = 0;
        }
#endif
        //コンストラクタで生成するオブジェクトの肩を取得
        bc_Type* ty = bc_GetEvalTypeCContext(cctx, self->FQCNCache);
        if (ty == NULL) {
                bc_Panic(BCERROR_NEW_INSTANCE_UNDEFINED_CLASS_T,
                         bc_Ref2Str(self->FQCNCache->Name));
                return;
        }
        //使用するコンストラクタを取得
        bc_Class* cls = BC_TYPE2CLASS(ty);
        int temp = -1;
        bc_CallFrame* cfr = bc_PushCallFrame(cctx, cls->Parent->GenericSelf,
                                             NULL, self->TypeArgs);
        bc_ResolveILTypeArgument(self->TypeArgs, cctx);
        self->Constructor =
            bc_ILFindConstructorClass(cls, self->Arguments, env, cctx, &temp);
        self->ConstructorIndex = temp;
        bc_PopCallFrame(cctx);
        if (temp == -1) {
                bc_Panic(BCERROR_NEW_INSTANCE_UNDEFINED_CTOR_T,
                         bc_Ref2Str(cls->Name));
        }
}

static void il_Factor_new_instace_delete_arg(bc_VectorItem item) {
        bc_ILArgument* e = (bc_ILArgument*)item;
        bc_DeleteILArgument(e);
}