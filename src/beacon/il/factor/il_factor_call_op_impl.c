#include "il_factor_call_op_impl.h"
#include <assert.h>
#include <string.h>
#include "../../env/namespace.h"
#include "../../env/type/class_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../il_argument.h"
#include "../il_factor_impl.h"
#include "../il_type_argument.h"

// proto
static void check_call_type(bc_ILCallOp* self, bc_Enviroment* env,
                            bc_CallContext* cctx);
static void check_call_namebase(bc_ILCallOp* self, bc_ILMemberOp* ilmem,
                                bc_Enviroment* env, bc_CallContext* cctx);
static void check_call_static(bc_ILCallOp* self, bc_ILMemberOp* ilmem,
                              bc_Enviroment* env, bc_CallContext* cctx);
static void check_call_instance(bc_ILCallOp* self, bc_ILMemberOp* ilmem,
                                bc_ILVariable* ilvar, bc_Enviroment* env,
                                bc_CallContext* cctx);
static void check_call_bound(bc_ILCallOp* self, bc_Enviroment* env);
static void check_member_access(bc_ILCallOp* self, bc_Enviroment* env,
                                bc_CallContext* cctx);
static void check_subscript_access(bc_ILCallOp* self, bc_Enviroment* env,
                                   bc_CallContext* cctx);

static void delete_argument(bc_VectorItem item);
static void delete_type_argument(bc_VectorItem item);

bc_ILFactor* bc_WrapCallOp(bc_ILCallOp* self) {
        bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_CALL_OP_T);
        ret->Kind.Call = self;
        self->Parent = ret;
        return ret;
}

bc_ILCallOp* bc_NewILCallOp() {
        bc_ILCallOp* ret = (bc_ILCallOp*)MEM_MALLOC(sizeof(bc_ILCallOp));
        ret->Receiver = NULL;
        ret->Arguments = bc_NewVector();
        ret->Type = ILCALL_TYPE_UNDEFINED_T;
        return ret;
}

void bc_LoadCallOp(bc_ILCallOp* self, bc_Enviroment* env,
                   bc_CallContext* cctx) {
        // argumentlistはサブクラスに渡しちゃってる
        // LoadILFactor(self->Receiver, env, ilctx, eh);
        check_call_type(self, env, cctx);
        if (self->Type == ILCALL_TYPE_INVOKE_T) {
                bc_LoadILInvoke(self->Kind.Invoke, env, cctx);
        } else if (self->Type == ILCALL_TYPE_INVOKE_STATIC_T) {
                bc_LoadILInvokeStatic(self->Kind.InvokeStatic, env, cctx);
        } else if (self->Type == ILCALL_TYPE_INVOKE_BOUND_T) {
                bc_LoadILInvokeBound(self->Kind.InvokeBound, env, cctx);
        }
}

bc_GenericType* bc_EvalILCallOp(bc_ILCallOp* self, bc_Enviroment* env,
                                bc_CallContext* cctx) {
        check_call_type(self, env, cctx);
        bc_GenericType* ret = NULL;
        if (self->Type == ILCALL_TYPE_INVOKE_T) {
                ret = bc_EvalILInvoke(self->Kind.Invoke, env, cctx);
        } else if (self->Type == ILCALL_TYPE_INVOKE_STATIC_T) {
                ret = bc_EvalILInvokeStatic(self->Kind.InvokeStatic, env, cctx);
        } else if (self->Type == ILCALL_TYPE_INVOKE_BOUND_T) {
                ret = bc_EvalILInvokeBound(self->Kind.InvokeBound, env, cctx);
        }
        if (bc_GetLastPanic()) {
                return ret;
        }
        return ret;
}

char* bc_ILCallOpToString(bc_ILCallOp* self, bc_Enviroment* env) {
        //	LoadCallOp(self, env);
        if (self->Type == ILCALL_TYPE_INVOKE_T) {
                return bc_ILInvokeToString(self->Kind.Invoke, env);
        } else if (self->Type == ILCALL_TYPE_INVOKE_BOUND_T) {
                return bc_ILInvokeBoundToString(self->Kind.InvokeBound, env);
        } else if (self->Type == ILCALL_TYPE_INVOKE_STATIC_T) {
                return bc_ILInvokeStaticToString(self->Kind.InvokeStatic, env);
        }
        return NULL;
}

void bc_GenerateILCallOp(bc_ILCallOp* self, bc_Enviroment* env,
                         bc_CallContext* cctx) {
        bc_LoadCallOp(self, env, cctx);
        if (self->Type == ILCALL_TYPE_INVOKE_T) {
                return bc_GenerateILInvoke(self->Kind.Invoke, env, cctx);
        } else if (self->Type == ILCALL_TYPE_INVOKE_STATIC_T) {
                return bc_GenerateILInvokeStatic(self->Kind.InvokeStatic, env,
                                                 cctx);
        } else if (self->Type == ILCALL_TYPE_INVOKE_BOUND_T) {
                return bc_GenerateILInvokeBound(self->Kind.InvokeBound, env,
                                                cctx);
        }
}

void bc_DeleteILCallOp(bc_ILCallOp* self) {
        bc_DeleteILFactor(self->Receiver);
        if (self->Type == ILCALL_TYPE_INVOKE_T) {
                bc_DeleteILInvoke(self->Kind.Invoke);
        } else if (self->Type == ILCALL_TYPE_INVOKE_STATIC_T) {
                bc_DeleteILInvokeStatic(self->Kind.InvokeStatic);
        } else if (self->Type == ILCALL_TYPE_INVOKE_BOUND_T) {
                bc_DeleteILInvokeBound(self->Kind.InvokeBound);
        }
        bc_DeleteVector(self->Arguments, delete_argument);
        MEM_FREE(self);
}

// private
static void check_call_type(bc_ILCallOp* self, bc_Enviroment* env,
                            bc_CallContext* cctx) {
        if (self->Type != ILCALL_TYPE_UNDEFINED_T) {
                return;
        }
        bc_ILFactor* receiver = self->Receiver;
        // hoge() foo() Namespace::Class() の場合
        if (receiver->Type == ILFACTOR_VARIABLE_T) {
                check_call_bound(self, env);
                // hoge().hoge() Namespace::Class.foo() の場合
        } else if (receiver->Type == ILFACTOR_MEMBER_OP_T) {
                check_member_access(self, env, cctx);
                // a()() の場合
        } else if (receiver->Type == ILFACTOR_CALL_OP_T) {
                check_subscript_access(self, env, cctx);
        }
        assert(self->Type != ILCALL_TYPE_UNDEFINED_T);
}

static void check_call_bound(bc_ILCallOp* self, bc_Enviroment* env) {
        bc_ILFactor* receiver = self->Receiver;
        bc_ILVariable* ilvar = receiver->Kind.Variable;
        bc_ILInvokeBound* bnd = bc_NewILInvokeBound(ilvar->FQCN->Name);
        assert(ilvar->FQCN->Scope->Length == 0);
        //入れ替え
        bnd->Arguments = self->Arguments;
        bnd->TypeArgs = ilvar->TypeArgs;
        self->Arguments = NULL;
        ilvar->TypeArgs = NULL;
        self->Kind.InvokeBound = bnd;
        self->Type = ILCALL_TYPE_INVOKE_BOUND_T;
}

static void check_member_access(bc_ILCallOp* self, bc_Enviroment* env,
                                bc_CallContext* cctx) {
        bc_ILFactor* receiver = self->Receiver;
        bc_ILMemberOp* ilmem = receiver->Kind.MemberOp;
        // hoge.foo
        if (ilmem->Source->Type == ILFACTOR_VARIABLE_T) {
                check_call_namebase(self, ilmem, env, cctx);
        } else {
                check_call_static(self, ilmem, env, cctx);
        }
}

static void check_call_namebase(bc_ILCallOp* self, bc_ILMemberOp* ilmem,
                                bc_Enviroment* env, bc_CallContext* cctx) {
        bc_ILVariable* ilvar = ilmem->Source->Kind.Variable;
        // Namespace::Class.foo()
        if (ilvar->FQCN->Scope->Length > 0) {
                check_call_instance(self, ilmem, ilvar, env, cctx);
                return;
        }
        // hoge.foo()
#if defined(DEBUG)
        const char* clname = bc_Ref2Str(ilvar->FQCN->Name);
#endif
        bc_Namespace* cur = bc_GetNamespaceByContext(cctx);
        bc_Class* ctype = bc_FindClassFromNamespace(cur, ilvar->FQCN->Name);
        if (ctype == NULL) {
                ctype = bc_FindClassFromNamespace(bc_GetLangNamespace(NULL),
                                                  ilvar->FQCN->Name);
        }
        if (ctype != NULL) {
                check_call_instance(self, ilmem, ilvar, env, cctx);
        } else {
                check_call_static(self, ilmem, env, cctx);
        }
}

static void check_call_static(bc_ILCallOp* self, bc_ILMemberOp* ilmem,
                              bc_Enviroment* env, bc_CallContext* cctx) {
        //入れ替える
        bc_ILInvoke* iv = bc_NewILInvoke(ilmem->Name);
        iv->args = self->Arguments;
        iv->receiver = ilmem->Source;
        iv->type_args = ilmem->TypeArgs;
        ilmem->Source = NULL;
        ilmem->TypeArgs = NULL;
        self->Type = ILCALL_TYPE_INVOKE_T;
        self->Kind.Invoke = iv;
        self->Arguments = NULL;
}

static void check_call_instance(bc_ILCallOp* self, bc_ILMemberOp* ilmem,
                                bc_ILVariable* ilvar, bc_Enviroment* env,
                                bc_CallContext* cctx) {
        bc_ILInvokeStatic* st = bc_NewILInvokeStatic(ilmem->Name);
        self->Type = ILCALL_TYPE_INVOKE_STATIC_T;
        self->Kind.InvokeStatic = st;
        //入れ替える
        st->TypeArgs = ilmem->TypeArgs;
        st->Arguments = self->Arguments;
        st->FQCN = ilvar->FQCN;
        self->Arguments = NULL;
        ilmem->TypeArgs = NULL;
        ilvar->FQCN = NULL;
}

static void check_subscript_access(bc_ILCallOp* self, bc_Enviroment* env,
                                   bc_CallContext* cctx) {
        bc_ILFactor* receiver = self->Receiver;
        bc_ILCallOp* call_left = receiver->Kind.Call;
        bc_ILInvoke* iv = bc_NewILInvoke(BC_ZERO_VIEW);
        bc_GenericType* receiver_gtype = bc_EvalILFactor(receiver, env, cctx);
        bc_Class* receiver_cl = BC_TYPE2CLASS(bc_GENERIC2TYPE(receiver_gtype));
        //オペレータオーバーロードを検索
        int temp;
#if defined(_MSC_VER)
        bc_GenericType** gargs =
            MEM_MALLOC(sizeof(bc_GenericType*) * self->Arguments->Length);
#else
        bc_GenericType* gargs[self->Arguments->Length];
#endif
        bc_CevaluateArguments(self->Arguments, gargs, env, cctx);
        iv->u.opov = bc_ResolveOperatorOverload(
            receiver_cl, OPERATOR_SUB_SCRIPT_GET_T, self->Arguments->Length,
            gargs, cctx, &temp);
        iv->index = temp;
        assert(temp != -1);
        //入れ替える
        iv->args = self->Arguments;
        iv->type_args = bc_NewVector();
        iv->receiver = receiver;
        iv->tag = INSTANCE_INVOKE_SUBSCRIPT_T;
        self->Receiver = NULL;
        self->Arguments = NULL;
        self->Type = ILCALL_TYPE_INVOKE_T;
        self->Kind.Invoke = iv;
#if defined(_MSC_VER)
        MEM_FREE(gargs);
#endif
}

static void delete_argument(bc_VectorItem item) {
        bc_ILArgument* e = (bc_ILArgument*)item;
        bc_DeleteILArgument(e);
}

static void delete_type_argument(bc_VectorItem item) {
        bc_ILTypeArgument* e = (bc_ILTypeArgument*)item;
        bc_DeleteILTypeArgument(e);
}