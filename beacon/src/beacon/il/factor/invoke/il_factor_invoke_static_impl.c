#include "il_factor_invoke_static_impl.h"
#include "../../../env/generic_type.h"
#include "../../../env/type/class_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/vector.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_type_argument.h"

// proto
static void resolve_non_default(bc_ILInvokeStatic* self, bc_Enviroment* env,
                                bc_CallContext* cctx);
static void resolve_default(bc_ILInvokeStatic* self, bc_Enviroment* env,
                            bc_CallContext* cctx);
static void ILInvokeStatic_check(bc_ILInvokeStatic* self, bc_Enviroment* env,
                                 bc_CallContext* cctx);
static void ILInvokeStatic_args_delete(bc_VectorItem item);
static void ILInvokeStatic_typeargs_delete(bc_VectorItem item);

bc_ILInvokeStatic* bc_NewILInvokeStatic(bc_StringView namev) {
        bc_ILInvokeStatic* ret =
            (bc_ILInvokeStatic*)MEM_MALLOC(sizeof(bc_ILInvokeStatic));
        ret->Arguments = NULL;
        ret->FQCN = NULL;
        ret->TypeArgs = NULL;
        ret->Name = namev;
        ret->Method = NULL;
        ret->Index = -1;
        ret->Resolved = NULL;
        return ret;
}

void bc_GenerateILInvokeStatic(bc_ILInvokeStatic* self, bc_Enviroment* env,
                               bc_CallContext* cctx) {
        for (int i = 0; i < self->TypeArgs->Length; i++) {
                bc_ILTypeArgument* e =
                    (bc_ILTypeArgument*)bc_AtVector(self->TypeArgs, i);
                assert(e->GType != NULL);
                bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
                bc_GenerateGenericType(e->GType, env);
        }
        for (int i = 0; i < self->Arguments->Length; i++) {
                bc_ILArgument* e =
                    (bc_ILArgument*)bc_AtVector(self->Arguments, i);
                bc_GenerateILFactor(e->Factor, env, cctx);
                if (bc_GetLastPanic()) {
                        return;
                }
        }
        bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)OP_INVOKESTATIC);
        bc_AddOpcodeBuf(
            env->Bytecode,
            (bc_VectorItem)BC_MEMBER_TYPE(self->Method)->AbsoluteIndex);
        bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)self->Index);
}

void bc_LoadILInvokeStatic(bc_ILInvokeStatic* self, bc_Enviroment* env,
                           bc_CallContext* cctx) {
        ILInvokeStatic_check(self, env, cctx);
}

bc_GenericType* bc_EvalILInvokeStatic(bc_ILInvokeStatic* self,
                                      bc_Enviroment* env,
                                      bc_CallContext* cctx) {
        ILInvokeStatic_check(self, env, cctx);
        //メソッドを解決できなかった場合
        if (bc_GetLastPanic()) {
                return NULL;
        }
        bc_GenericType* rgtp = self->Method->ReturnGType;
        if (rgtp->Tag != GENERIC_TYPE_TAG_NONE_T) {
                resolve_non_default(self, env, cctx);
                return self->Resolved;
        } else {
                resolve_default(self, env, cctx);
                return self->Resolved;
        }
        return NULL;
}

char* bc_ILInvokeStaticToString(bc_ILInvokeStatic* self, bc_Enviroment* env) {
        bc_Buffer* sb = bc_NewBuffer();
        char* name = bc_FQCNCacheToString(self->FQCN);
        bc_AppendsBuffer(sb, name);
        bc_AppendBuffer(sb, '.');
        bc_AppendsBuffer(sb, bc_Ref2Str(self->Name));
        bc_ILTypeArgsToString(sb, self->TypeArgs, env);
        bc_ILArgsToString(sb, self->Arguments, env);
        MEM_FREE(name);
        return bc_ReleaseBuffer(sb);
}

void bc_DeleteILInvokeStatic(bc_ILInvokeStatic* self) {
        bc_DeleteVector(self->Arguments, ILInvokeStatic_args_delete);
        bc_DeleteVector(self->TypeArgs, ILInvokeStatic_typeargs_delete);
        bc_DeleteFQCNCache(self->FQCN);
        MEM_FREE(self);
}
// private
// FIXME:ILInvokeからのコピペ
static void resolve_non_default(bc_ILInvokeStatic* self, bc_Enviroment* env,
                                bc_CallContext* cctx) {
        if (self->Resolved != NULL) {
                return;
        }
        bc_GenericType* rgtp = self->Method->ReturnGType;
        bc_GenericType* instanced_type = (bc_GenericType*)bc_AtVector(
            self->TypeArgs, rgtp->VirtualTypeIndex);
        self->Resolved = bc_NewGenericType(instanced_type->CoreType);
        self->Resolved->Tag = GENERIC_TYPE_TAG_METHOD_T;
        self->Resolved->VirtualTypeIndex = rgtp->VirtualTypeIndex;
}

static void resolve_default(bc_ILInvokeStatic* self, bc_Enviroment* env,
                            bc_CallContext* cctx) {
        if (self->Resolved != NULL) {
                return;
        }
        bc_CallFrame* cfr =
            bc_PushCallContext(cctx, NULL, self->Arguments, self->TypeArgs);
        /*
    cfr->Kind.StaticInvoke.Args = self->Arguments;
    cfr->Kind.StaticInvoke.TypeArgs = self->TypeArgs;
    */
        bc_GenericType* rgtp = self->Method->ReturnGType;
        self->Resolved = bc_ApplyGenericType(rgtp, cctx);
        bc_PopCallContext(cctx);
}

static void ILInvokeStatic_check(bc_ILInvokeStatic* self, bc_Enviroment* env,
                                 bc_CallContext* cctx) {
        bc_Type* ty = bc_GetEvalTypeCContext(cctx, self->FQCN);
        if (ty == NULL) {
                bc_Panic(BCERROR_UNDEFINED_TYPE_STATIC_INVOKE_T,
                         bc_Ref2Str(self->FQCN->Name), bc_Ref2Str(self->Name));
                return;
        }
        bc_Class* cls = BC_TYPE2CLASS(ty);
#if defined(DEBUG)
        const char* classname = bc_Ref2Str(cls->Name);
        const char* methodname = bc_Ref2Str(self->Name);
#endif
        int temp = -1;
        bc_ResolveILTypeArgument(self->TypeArgs, cctx);
        //環境を設定
        //メソッドを検索
        for (int i = 0; i < self->Arguments->Length; i++) {
                bc_ILArgument* ilarg = bc_AtVector(self->Arguments, i);
                bc_LoadILFactor(ilarg->Factor, env, cctx);
        }
        bc_CallFrame* cfr =
            bc_PushCallContext(cctx, NULL, self->Arguments, self->TypeArgs);
        /*
    cfr->Kind.StaticInvoke.Args = self->Arguments;
    cfr->Kind.StaticInvoke.TypeArgs = self->TypeArgs;*/
        self->Method = bc_ILFindSMethodClass(cls, self->Name, self->Arguments,
                                             env, cctx, &temp);
        self->Index = temp;
        //メソッドが見つからない
        if (temp == -1 || self->Method == NULL) {
                bc_Panic(BCERROR_INVOKE_STATIC_UNDEFINED_METHOD_T,
                         bc_Ref2Str(cls->Name), bc_Ref2Str(self->Name));
        }
        bc_PopCallContext(cctx);
}

static void ILInvokeStatic_args_delete(bc_VectorItem item) {
        bc_ILArgument* e = (bc_ILArgument*)item;
        bc_DeleteILArgument(e);
}

static void ILInvokeStatic_typeargs_delete(bc_VectorItem item) {
        bc_ILTypeArgument* e = (bc_ILTypeArgument*)item;
        bc_DeleteILTypeArgument(e);
}