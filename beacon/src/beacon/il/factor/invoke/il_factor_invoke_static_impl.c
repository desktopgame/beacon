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
static void find_method(bc_ILInvokeStatic* self, bc_Enviroment* env,
                        bc_CallContext* cctx);
static void delete_args(bc_VectorItem item);
static void delete_typeargs(bc_VectorItem item);

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
        find_method(self, env, cctx);
}

bc_GenericType* bc_EvalILInvokeStatic(bc_ILInvokeStatic* self,
                                      bc_Enviroment* env,
                                      bc_CallContext* cctx) {
        find_method(self, env, cctx);
        //メソッドを解決できなかった場合
        if (bc_GetLastPanic()) {
                return NULL;
        }
        if (self->Resolved != NULL) {
                return self->Resolved;
        }
        bc_CallFrame* cfr =
            bc_PushCallFrame(cctx, NULL, self->Arguments, self->TypeArgs);
        bc_GenericType* rgtp = self->Method->ReturnGType;
        self->Resolved = bc_CapplyGenericType(rgtp, cctx);
        bc_PopCallFrame(cctx);
        return self->Resolved;
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
        bc_DeleteVector(self->Arguments, delete_args);
        bc_DeleteVector(self->TypeArgs, delete_typeargs);
        bc_DeleteFQCNCache(self->FQCN);
        MEM_FREE(self);
}
// private
static void delete_args(bc_VectorItem item) {
        bc_ILArgument* e = (bc_ILArgument*)item;
        bc_DeleteILArgument(e);
}

static void delete_typeargs(bc_VectorItem item) {
        bc_ILTypeArgument* e = (bc_ILTypeArgument*)item;
        bc_DeleteILTypeArgument(e);
}

// FIXME:ILInvokeからのコピペ
static void find_method(bc_ILInvokeStatic* self, bc_Enviroment* env,
                        bc_CallContext* cctx) {
        bc_Type* ty = bc_ResolveContext(cctx, self->FQCN);
        if (ty == NULL) {
                bc_Panic(BCERROR_UNDEFINED_TYPE_STATIC_INVOKE_T,
                         bc_Ref2Str(self->FQCN->Name), bc_Ref2Str(self->Name));
                return;
        }
        bc_Class* cls = BC_TYPE2CLASS(ty);
        int temp = -1;
        bc_ResolveILTypeArgument(self->TypeArgs, cctx);
        //環境を設定
        //メソッドを検索
        for (int i = 0; i < self->Arguments->Length; i++) {
                bc_ILArgument* ilarg = bc_AtVector(self->Arguments, i);
                bc_LoadILFactor(ilarg->Factor, env, cctx);
        }
        bc_CallFrame* cfr =
            bc_PushCallFrame(cctx, NULL, self->Arguments, self->TypeArgs);
        bc_GenericType* gargs[self->Arguments->Length];
        bc_EvaluateArguments(self->Arguments, gargs, env, cctx);
        if (bc_GetLastPanic()) {
                bc_PopCallFrame(cctx);
                return;
        }
        bc_SearchOption opt = cls->Parent == bc_GetTypeByContext(cctx)
                                  ? MATCH_ALL
                                  : MATCH_PUBLIC_ONLY;
        if (temp == -1) {
                self->Method = bc_FindMethod(cls->StaticMethods, self->Name,
                                             self->Arguments->Length, gargs,
                                             self->TypeArgs, opt, cctx, &temp);
        }
        self->Index = temp;
        //メソッドが見つからない
        if (temp == -1 || self->Method == NULL) {
                bc_Panic(BCERROR_INVOKE_STATIC_UNDEFINED_METHOD_T,
                         bc_Ref2Str(cls->Name), bc_Ref2Str(self->Name));
        }
        bc_PopCallFrame(cctx);
}