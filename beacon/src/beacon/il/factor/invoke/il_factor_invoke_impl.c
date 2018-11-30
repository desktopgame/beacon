#include "il_factor_invoke_impl.h"
#include <stdio.h>
#include <string.h>
#include "../../../env/class_loader.h"
#include "../../../env/generic_type.h"
#include "../../../env/method.h"
#include "../../../env/operator_overload.h"
#include "../../../env/type/class_impl.h"
#include "../../../env/type_interface.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_factor_impl.h"
#include "../../il_type_argument.h"

// proto
static void resolve_virtual(bc_ILInvoke* self, bc_Enviroment* env,
                            bc_CallContext* cctx);
static void resolve_apply(bc_ILInvoke* self, bc_Enviroment* env,
                          bc_CallContext* cctx);
static void delete_args(bc_VectorItem item);
static void find_method(bc_ILInvoke* self, bc_Enviroment* env,
                        bc_CallContext* cctx);
static bc_GenericType* get_return_gtype(bc_ILInvoke* self);
static void generate_method(bc_ILInvoke* self, bc_Enviroment* env,
                            bc_CallContext* cctx);
static void generate_subscript(bc_ILInvoke* self, bc_Enviroment* env,
                               bc_CallContext* cctx);

bc_ILInvoke* bc_NewILInvoke(bc_StringView namev) {
        bc_ILInvoke* ret = (bc_ILInvoke*)MEM_MALLOC(sizeof(bc_ILInvoke));
        ret->args = NULL;
        ret->receiver = NULL;
        ret->type_args = NULL;
        ret->index = -1;
        ret->tag = INSTANCE_INVOKE_UNDEFINED_T;
        ret->namev = namev;
        ret->resolved = NULL;
        return ret;
}

void bc_GenerateILInvoke(bc_ILInvoke* self, bc_Enviroment* env,
                         bc_CallContext* cctx) {
        generate_method(self, env, cctx);
        generate_subscript(self, env, cctx);
}

void bc_LoadILInvoke(bc_ILInvoke* self, bc_Enviroment* env,
                     bc_CallContext* cctx) {
        if (self->index != -1) {
                return;
        }
        bc_CallFrame* cfr =
            bc_PushCallFrame(cctx, bc_EvalILFactor(self->receiver, env, cctx),
                             self->args, self->type_args);
        bc_LoadILFactor(self->receiver, env, cctx);
        find_method(self, env, cctx);
        bc_PopCallFrame(cctx);
}

bc_GenericType* bc_EvalILInvoke(bc_ILInvoke* self, bc_Enviroment* env,
                                bc_CallContext* cctx) {
        find_method(self, env, cctx);
        if (bc_GetLastPanic()) {
                return NULL;
        }
        bc_GenericType* rgtp = get_return_gtype(self);
        bc_GenericType* ret = NULL;
        bc_GenericType* receivergType =
            bc_EvalILFactor(self->receiver, env, cctx);
        //内側に型変数が含まれているかもしれないので、
        //それをここで展開する。
        bc_CallFrame* cfr =
            bc_PushCallFrame(cctx, receivergType, self->args, self->type_args);
        //戻り値がジェネリックなら...Tなど
        if (rgtp->Tag != GENERIC_TYPE_TAG_NONE_T) {
                resolve_virtual(self, env, cctx);
                ret = self->resolved;
                //戻り値がジェネリックでないなら...List[T]など
        } else {
                resolve_apply(self, env, cctx);
                ret = self->resolved;
        }
        bc_PopCallFrame(cctx);
        return ret;
}

char* bc_ILInvokeToString(bc_ILInvoke* self, bc_Enviroment* env) {
        bc_Buffer* sb = bc_NewBuffer();
        char* invstr = bc_ILFactorToString(self->receiver, env);
        bc_AppendsBuffer(sb, invstr);
        bc_AppendBuffer(sb, '.');
        bc_AppendsBuffer(sb, bc_Ref2Str(self->namev));
        bc_ILTypeArgsToString(sb, self->type_args, env);
        bc_ILArgsToString(sb, self->type_args, env);
        MEM_FREE(invstr);
        return bc_ReleaseBuffer(sb);
}

void bc_DeleteILInvoke(bc_ILInvoke* self) {
        bc_DeleteVector(self->args, delete_args);
        bc_DeleteVector(self->type_args, bc_VectorDeleterOfNull);
        bc_DeleteILFactor(self->receiver);
        // generic_DeleteType(self->resolved);
        MEM_FREE(self);
}

bc_OperatorOverload* bc_FindSetILInvoke(bc_ILInvoke* self, bc_ILFactor* value,
                                        bc_Enviroment* env,
                                        bc_CallContext* cctx, int* outIndex) {
        assert(self->tag == INSTANCE_INVOKE_SUBSCRIPT_T);
        bc_Vector* args = bc_NewVector();
        bc_PushVector(args,
                      ((bc_ILArgument*)bc_AtVector(self->args, 0))->Factor);
        bc_PushVector(args, value);
        bc_OperatorOverload* opov = bc_ILFindOperatorOverloadClass(
            BC_TYPE2CLASS(BC_MEMBER_TYPE(self->u.opov)),
            OPERATOR_SUB_SCRIPT_SET_T, args, env, cctx, outIndex);
        bc_DeleteVector(args, bc_VectorDeleterOfNull);
        return opov;
}
// private
static void delete_args(bc_VectorItem item) {
        bc_ILArgument* e = (bc_ILArgument*)item;
        bc_DeleteILArgument(e);
}

static void generate_method(bc_ILInvoke* self, bc_Enviroment* env,
                            bc_CallContext* cctx) {
        assert(self->tag != INSTANCE_INVOKE_UNDEFINED_T);
        if (self->tag != INSTANCE_INVOKE_METHOD_T) {
                return;
        }
        for (int i = 0; i < self->type_args->Length; i++) {
                bc_ILTypeArgument* e =
                    (bc_ILTypeArgument*)bc_AtVector(self->type_args, i);
                assert(e->GType != NULL);
                bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
                bc_GenerateGenericType(e->GType, env);
        }
        for (int i = 0; i < self->args->Length; i++) {
                bc_ILArgument* e = (bc_ILArgument*)bc_AtVector(self->args, i);
                bc_GenerateILFactor(e->Factor, env, cctx);
        }
        bc_GenerateILFactor(self->receiver, env, cctx);
        if (BC_MEMBER_TYPE(self->u.m)->Tag == TYPE_INTERFACE_T) {
                bc_AddOpcodeBuf(env->Bytecode,
                                (bc_VectorItem)OP_INVOKEINTERFACE);
                bc_AddOpcodeBuf(
                    env->Bytecode,
                    (bc_VectorItem)BC_MEMBER_TYPE(self->u.m)->AbsoluteIndex);
                bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)self->index);
        } else {
                assert(!bc_IsStaticModifier(BC_MEMBER_MODIFIER(self->u.m)));
                if (BC_MEMBER_ACCESS(self->u.m) == ACCESS_PRIVATE_T) {
                        bc_AddOpcodeBuf(env->Bytecode,
                                        (bc_VectorItem)OP_INVOKESPECIAL);
                        bc_AddOpcodeBuf(env->Bytecode,
                                        (bc_VectorItem)self->index);
                } else {
                        bc_AddOpcodeBuf(env->Bytecode,
                                        (bc_VectorItem)OP_INVOKEVIRTUAL);
                        bc_AddOpcodeBuf(env->Bytecode,
                                        (bc_VectorItem)self->index);
                }
        }
}

static void generate_subscript(bc_ILInvoke* self, bc_Enviroment* env,
                               bc_CallContext* cctx) {
        assert(self->tag != INSTANCE_INVOKE_UNDEFINED_T);
        if (self->tag != INSTANCE_INVOKE_SUBSCRIPT_T) {
                return;
        }
        for (int i = 0; i < self->type_args->Length; i++) {
                bc_ILTypeArgument* e =
                    (bc_ILTypeArgument*)bc_AtVector(self->type_args, i);
                assert(e->GType != NULL);
                bc_AddOpcodeBuf(env->Bytecode, OP_GENERIC_ADD);
                bc_GenerateGenericType(e->GType, env);
        }
        for (int i = 0; i < self->args->Length; i++) {
                bc_ILArgument* e = (bc_ILArgument*)bc_AtVector(self->args, i);
                bc_GenerateILFactor(e->Factor, env, cctx);
        }
        bc_GenerateILFactor(self->receiver, env, cctx);
        bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
        bc_AddOpcodeBuf(env->Bytecode, self->index);
}

static bc_GenericType* get_return_gtype(bc_ILInvoke* self) {
        assert(self->tag != INSTANCE_INVOKE_UNDEFINED_T);
        return self->tag == INSTANCE_INVOKE_METHOD_T
                   ? self->u.m->ReturnGType
                   : self->u.opov->ReturnGType;
}

static void find_method(bc_ILInvoke* self, bc_Enviroment* env,
                        bc_CallContext* cctx) {
        //レシーバの読み込み
        bc_LoadILFactor(self->receiver, env, cctx);
        if (bc_GetLastPanic()) {
                return;
        }
        if (self->receiver->Type == ILFACTOR_VARIABLE_T) {
                bc_ILVariable* ilvar = self->receiver->Kind.Variable;
                assert(ilvar->Type != ILVARIABLE_TYPE_STATIC_T);
        }
        //レシーバの型を評価
        bc_GenericType* gtype = bc_EvalILFactor(self->receiver, env, cctx);
        if (bc_GetLastPanic()) {
                return;
        }
        bc_ResolveILTypeArgument(self->type_args, cctx);
        bc_Type* ctype = gtype->CoreType;

        //ジェネリックな変数に対しても
        // Objectクラスのメソッドは呼び出せる
        if (ctype == NULL) {
                ctype = BC_TYPE_OBJECT;
        }
        //メソッドを検索
        assert(ctype != NULL);
        int temp = -1;
        self->tag = INSTANCE_INVOKE_METHOD_T;
        self->u.m = bc_ILFindMethodType(ctype, self->namev, self->args, env,
                                        cctx, &temp);
        self->index = temp;
        if (temp != -1) {
                return;
        }
        //メソッドが見つからなかったら
        // subscript(添字アクセス)として解決する
        if (self->args->Length != 1) {
                // hoge(1) = 0;
                //の形式なら引数は一つのはず
                bc_Panic(BCERROR_INVOKE_INSTANCE_UNDEFINED_METHOD_T,
                         bc_Ref2Str(bc_GetTypeName(ctype)),
                         bc_Ref2Str(self->namev));
                return;
        }
        self->tag = INSTANCE_INVOKE_SUBSCRIPT_T;
        self->u.opov = bc_ArgFindOperatorOverloadClass(
            BC_TYPE2CLASS(ctype), OPERATOR_SUB_SCRIPT_GET_T, self->args, env,
            cctx, &temp);
        self->index = temp;
        if (temp == -1) {
                bc_Panic(BCERROR_INVOKE_INSTANCE_UNDEFINED_METHOD_T,
                         bc_Ref2Str(bc_GetTypeName(ctype)),
                         bc_Ref2Str(self->namev));
                return;
        }
}

static void resolve_virtual(bc_ILInvoke* self, bc_Enviroment* env,
                            bc_CallContext* cctx) {
        if (self->resolved != NULL) {
                return;
        }
        bc_GenericType* rgtp = get_return_gtype(self);
        self->resolved = bc_CapplyGenericType(rgtp, cctx);
}

static void resolve_apply(bc_ILInvoke* self, bc_Enviroment* env,
                          bc_CallContext* cctx) {
        if (self->resolved != NULL) {
                return;
        }
        bc_GenericType* rgtp = get_return_gtype(self);
        self->resolved = bc_CapplyGenericType(rgtp, cctx);
}
