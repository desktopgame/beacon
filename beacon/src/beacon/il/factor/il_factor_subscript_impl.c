#include "il_factor_subscript_impl.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/operator_overload.h"
#include "../../util/io.h"
#include "../../util/mem.h"

bc_ILFactor* bc_WrapILSubscript(bc_ILSubscript* self) {
        bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_SUBSCRIPT_T);
        ret->Kind.Subscript = self;
        return ret;
}

bc_ILSubscript* bc_MallocILSubscript(const char* filename, int lineno) {
        bc_ILSubscript* ret =
            bc_MXMalloc(sizeof(bc_ILSubscript), filename, lineno);
        ret->Receiver = NULL;
        ret->Position = NULL;
        ret->OperatorIndex = -1;
        ret->Operator = NULL;
        return ret;
}

void bc_GenerateILSubscript(bc_ILSubscript* self, bc_Enviroment* env,
                            bc_CallContext* cctx) {
        bc_GenerateILFactor(self->Position, env, cctx);
        bc_GenerateILFactor(self->Receiver, env, cctx);
        bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
        bc_AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
}

void bc_LoadILSubscript(bc_ILSubscript* self, bc_Enviroment* env,
                        bc_CallContext* cctx) {
        if (self->OperatorIndex != -1) {
                return;
        }
        bc_LoadILFactor(self->Receiver, env, cctx);
        bc_LoadILFactor(self->Position, env, cctx);
        bc_GenericType* receiver_gtype =
            bc_EvalILFactor(self->Receiver, env, cctx);
        bc_GenericType* arg_gtype = bc_EvalILFactor(self->Position, env, cctx);
        bc_Vector* args = bc_NewVector();
        bc_PushVector(args, arg_gtype);
        int temp = -1;
        self->Operator = bc_GFindOperatorOverloadClass(
            BC_TYPE2CLASS(bc_GENERIC2TYPE(receiver_gtype)),
            OPERATOR_SUB_SCRIPT_GET_T, args, env, cctx, &temp);
        self->OperatorIndex = temp;
        bc_DeleteVector(args, bc_VectorDeleterOfNull);
}

bc_GenericType* bc_EvalILSubscript(bc_ILSubscript* self, bc_Enviroment* env,
                                   bc_CallContext* cctx) {
        return bc_ApplyGenericType(self->Operator->ReturnGType, cctx);
}

char* bc_ILSubscriptToString(bc_ILSubscript* self, bc_Enviroment* env) {
        bc_Buffer* buf = bc_NewBuffer();
        char* src = bc_ILFactorToString(self->Receiver, env);
        char* pos = bc_ILFactorToString(self->Position, env);
        bc_AppendsBuffer(buf, src);
        bc_AppendBuffer(buf, '[');
        bc_AppendsBuffer(buf, pos);
        bc_AppendBuffer(buf, ']');
        MEM_FREE(src);
        MEM_FREE(pos);
        return bc_ReleaseBuffer(buf);
}

void bc_DeleteILSubscript(bc_ILSubscript* self) {
        bc_DeleteILFactor(self->Receiver);
        bc_DeleteILFactor(self->Position);
        MEM_FREE(self);
}