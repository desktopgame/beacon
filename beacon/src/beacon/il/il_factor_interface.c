#include "il_factor_interface.h"
#include <assert.h>
#include <stdio.h>
#include "../env/class_loader.h"
#include "../env/type_interface.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../vm/enviroment.h"
#include "il_argument.h"
#include "il_factor_impl.h"
#include "il_type_argument.h"

bc_ILFactor* bc_MallocILFactor(bc_ILFactorType type, const char* filename,
                               int lineno) {
        bc_ILFactor* ret = bc_MXMalloc(sizeof(bc_ILFactor), filename, lineno);
        ret->Type = type;
        ret->Lineno = -1;
        return ret;
}

void bc_GenerateILFactor(bc_ILFactor* self, bc_Enviroment* env,
                         bc_CallContext* cctx) {
        if (bc_GetLastPanic()) {
                return;
        }
        bc_SetPanicFile(env->ContextRef->FileName);
        bc_SetPanicLine(self->Lineno);
        switch (self->Type) {
                case ILFACTOR_INT_T:
                        bc_GenerateILInt(self->Kind.Int, env, cctx);
                        break;
                case ILFACTOR_DOUBLE_T:
                        bc_GenerateILDouble(self->Kind.Double, env, cctx);
                        break;
                case ILFACTOR_CHAR_T:
                        bc_GenerateILChar(self->Kind.Char, env, cctx);
                        break;
                case ILFACTOR_STRING_T:
                        bc_GenerateILString(self->Kind.String, env, cctx);
                        break;
                case ILFACTOR_VARIABLE_T:
                        bc_GenerateILVariable(self->Kind.Variable, env, cctx);
                        break;
                case ILFACTOR_UNARY_OP_T:
                        bc_GenerateILUnaryOp(self->Kind.UnaryOp, env, cctx);
                        break;
                case ILFACTOR_BINARY_OP_T:
                        bc_GenerateILBinaryOp(self->Kind.BinaryOp, env, cctx);
                        break;
                case ILFACTOR_ASSIGN_T:
                        bc_GenerateILAssignOp(self->Kind.AssignOp, env, cctx);
                        break;
                case ILFACTOR_THIS_T:
                        bc_GenerateILThis(self->Kind.This, env, cctx);
                        break;
                case ILFACTOR_SUPER_T:
                        bc_GenerateILSuper(self->Kind.Super, env, cctx);
                        break;
                case ILFACTOR_NEW_INSTANCE_T:
                        bc_GenerateILNewInstance(self->Kind.NewInstance, env,
                                                 cctx);
                        break;
                case ILFACTOR_BOOL_T:
                        bc_GenerateILBool(self->Kind.Bool, env, cctx);
                        break;
                case ILFACTOR_NULL_T:
                        bc_GenerateILNull(NULL, env, cctx);
                        break;
                case ILFACTOR_AS_T:
                        bc_GenerateILAs(self->Kind.As, env, cctx);
                        break;
                case ILFACTOR_CALL_OP_T:
                        bc_GenerateILCallOp(self->Kind.Call, env, cctx);
                        break;
                case ILFACTOR_MEMBER_OP_T:
                        bc_GenerateILMemberOp(self->Kind.MemberOp, env, cctx);
                        break;
                case ILFACTOR_INSTANCEOF_T:
                        bc_GenerateILInstanceOf(self->Kind.InstanceOf, env,
                                                cctx);
                        break;
                case ILFACTOR_EXPLICIT_UNARY_OP_T:
                        bc_GenerateILExplicitUnaryOp(self->Kind.ExpUnaryOp, env,
                                                     cctx);
                        break;
                case ILFACTOR_EXPLICIT_BINARY_OP_T:
                        bc_GenerateILExplicitBinaryOp(self->Kind.ExpBinaryOp,
                                                      env, cctx);
                        break;
                case ILFACTOR_PROPERTY_T:
                        bc_GenerateILPropertyAccess(self->Kind.PropertyAccess,
                                                    env, cctx);
                        break;
                case ILFACTOR_SUBSCRIPT_T:
                        bc_GenerateILSubscript(self->Kind.Subscript, env, cctx);
                        break;
                default:
                        break;
        }
        assert(self->Lineno >= 0);
        bc_AddRangeEnviroment(env, self->Lineno);
}

void bc_LoadILFactor(bc_ILFactor* self, bc_Enviroment* env,
                     bc_CallContext* cctx) {
        if (bc_GetLastPanic()) {
                return;
        }
        bc_SetPanicFile(env->ContextRef->FileName);
        bc_SetPanicLine(self->Lineno);
        switch (self->Type) {
                case ILFACTOR_INT_T:
                        bc_LoadILInt(self->Kind.Int, env, cctx);
                        break;
                case ILFACTOR_DOUBLE_T:
                        bc_LoadILDouble(self->Kind.Double, env, cctx);
                        break;
                case ILFACTOR_CHAR_T:
                        bc_LoadILChar(self->Kind.Char, env, cctx);
                        break;
                case ILFACTOR_STRING_T:
                        bc_LoadILString(self->Kind.String, env, cctx);
                        break;
                case ILFACTOR_VARIABLE_T:
                        bc_LoadILVariable(self->Kind.Variable, env, cctx);
                        break;
                case ILFACTOR_UNARY_OP_T:
                        bc_LoadILUnaryOp(self->Kind.UnaryOp, env, cctx);
                        break;
                case ILFACTOR_BINARY_OP_T:
                        bc_LoadILBinaryOp(self->Kind.BinaryOp, env, cctx);
                        break;
                case ILFACTOR_ASSIGN_T:
                        bc_LoadILAssignOp(self->Kind.AssignOp, env, cctx);
                        break;
                case ILFACTOR_THIS_T:
                        bc_LoadILThis(self->Kind.This, env, cctx);
                        break;
                case ILFACTOR_SUPER_T:
                        bc_LoadILSuper(self->Kind.Super, env, cctx);
                        break;
                case ILFACTOR_NEW_INSTANCE_T:
                        bc_LoadILNewInstance(self->Kind.NewInstance, env, cctx);
                        break;
                case ILFACTOR_BOOL_T:
                        // ILBool_load(self->Kind.Bool, depth);
                        break;
                case ILFACTOR_NULL_T:
                        bc_LoadILNull(NULL, env, cctx);
                        break;
                case ILFACTOR_AS_T:
                        bc_LoadILAs(self->Kind.As, env, cctx);
                        break;
                case ILFACTOR_CALL_OP_T:
                        bc_LoadCallOp(self->Kind.Call, env, cctx);
                        break;
                case ILFACTOR_MEMBER_OP_T:
                        bc_LoadILMemberOp(self->Kind.MemberOp, env, cctx);
                        break;
                case ILFACTOR_INSTANCEOF_T:
                        bc_LoadILInstanceOf(self->Kind.InstanceOf, env, cctx);
                        break;
                case ILFACTOR_EXPLICIT_UNARY_OP_T:
                        bc_LoadILExplicitUnaryOp(self->Kind.ExpUnaryOp, env,
                                                 cctx);
                        break;
                case ILFACTOR_EXPLICIT_BINARY_OP_T:
                        bc_LoadILExplicitBinaryOp(self->Kind.ExpBinaryOp, env,
                                                  cctx);
                        break;
                case ILFACTOR_PROPERTY_T:
                        bc_LoadILProperty(self->Kind.PropertyAccess, env, cctx);
                        break;
                case ILFACTOR_SUBSCRIPT_T:
                        bc_LoadILSubscript(self->Kind.Subscript, env, cctx);
                        break;
                default:
                        break;
        }
}

bc_GenericType* bc_EvalILFactor(bc_ILFactor* self, bc_Enviroment* env,
                                bc_CallContext* cctx) {
        if (bc_GetLastPanic()) {
                return NULL;
        }
        bc_SetPanicFile(env->ContextRef->FileName);
        bc_SetPanicLine(self->Lineno);
        bc_GenericType* ret = NULL;
        switch (self->Type) {
                case ILFACTOR_INT_T:
                        ret = bc_EvalILInt(self->Kind.Int, env, cctx);
                        break;
                case ILFACTOR_DOUBLE_T:
                        ret = bc_EvalILDouble(self->Kind.Double, env, cctx);
                        break;
                case ILFACTOR_CHAR_T:
                        ret = bc_EvalILChar(self->Kind.Char, env, cctx);
                        break;
                case ILFACTOR_STRING_T:
                        ret = bc_EvalILString(self->Kind.String, env, cctx);
                        break;
                case ILFACTOR_VARIABLE_T:
                        ret = bc_EvalILVariable(self->Kind.Variable, env, cctx);
                        break;
                case ILFACTOR_UNARY_OP_T:
                        ret = bc_EvalILUnaryOp(self->Kind.UnaryOp, env, cctx);
                        break;
                case ILFACTOR_BINARY_OP_T:
                        ret = bc_EvalILBinaryOp(self->Kind.BinaryOp, env, cctx);
                        break;
                case ILFACTOR_ASSIGN_T:
                        ret = bc_EvalILAssignOp(self->Kind.AssignOp, env, cctx);
                        break;
                case ILFACTOR_THIS_T:
                        ret = bc_EvalILThis(self->Kind.This, env, cctx);
                        break;
                case ILFACTOR_SUPER_T:
                        ret = bc_EvalILSuper(self->Kind.Super, env, cctx);
                        break;
                case ILFACTOR_NEW_INSTANCE_T:
                        ret = bc_EvalILNewInstance(self->Kind.NewInstance, env,
                                                   cctx);
                        break;
                case ILFACTOR_BOOL_T:
                        ret = bc_EvalILBool(self->Kind.Bool, env, cctx);
                        break;
                case ILFACTOR_NULL_T:
                        ret = bc_EvalILNull(NULL, env, cctx);
                        break;
                case ILFACTOR_AS_T:
                        ret = bc_EvalILAs(self->Kind.As, env, cctx);
                        break;
                case ILFACTOR_CALL_OP_T:
                        ret = bc_EvalILCallOp(self->Kind.Call, env, cctx);
                        break;
                case ILFACTOR_MEMBER_OP_T:
                        ret = bc_EvalILMemberOp(self->Kind.MemberOp, env, cctx);
                        break;
                case ILFACTOR_INSTANCEOF_T:
                        ret = bc_EvalILInstanceOf(self->Kind.InstanceOf, env,
                                                  cctx);
                        break;
                case ILFACTOR_EXPLICIT_UNARY_OP_T:
                        ret = bc_EvalILExplicitUnaryOp(self->Kind.ExpUnaryOp,
                                                       env, cctx);
                        break;
                case ILFACTOR_EXPLICIT_BINARY_OP_T:
                        ret = bc_EvalILExplicitBinaryOp(self->Kind.ExpBinaryOp,
                                                        env, cctx);
                        break;
                case ILFACTOR_PROPERTY_T:
                        ret = bc_EvalILProperty(self->Kind.PropertyAccess, env,
                                                cctx);
                        break;
                case ILFACTOR_SUBSCRIPT_T:
                        ret =
                            bc_EvalILSubscript(self->Kind.Subscript, env, cctx);
                        break;
                default:
                        assert(false);
                        break;
        }
        // assert(ret != NULL);
        return ret;
}

char* bc_ILFactorToString(bc_ILFactor* self, bc_Enviroment* env) {
        if (bc_GetLastPanic()) {
                return NULL;
        }
        switch (self->Type) {
                case ILFACTOR_INT_T:
                        return bc_ILIntToString(self->Kind.Int, env);
                case ILFACTOR_DOUBLE_T:
                        return bc_ILDoubleToString(self->Kind.Double, env);
                case ILFACTOR_CHAR_T:
                        return bc_ILCharToString(self->Kind.Char, env);
                case ILFACTOR_STRING_T:
                        return bc_ILStringToString(self->Kind.String, env);
                case ILFACTOR_VARIABLE_T:
                        return bc_ILVariableToString(self->Kind.Variable, env);
                case ILFACTOR_UNARY_OP_T:
                        return bc_ILUnaryOpToString(self->Kind.UnaryOp, env);
                case ILFACTOR_BINARY_OP_T:
                        return bc_ILBinaryOpToString(self->Kind.BinaryOp, env);
                case ILFACTOR_ASSIGN_T:
                        return NULL;
                case ILFACTOR_THIS_T:
                        return bc_ILThisToString(self->Kind.This, env);
                case ILFACTOR_SUPER_T:
                        return bc_ILSuperToString(self->Kind.Super, env);
                case ILFACTOR_NEW_INSTANCE_T:
                        return bc_ILNewInstanceToString(self->Kind.NewInstance,
                                                        env);
                case ILFACTOR_BOOL_T:
                        return bc_ILBoolToString(self->Kind.Bool, env);
                case ILFACTOR_NULL_T:
                        return bc_ILNullToString(self->Kind.Null, env);
                case ILFACTOR_AS_T:
                        return bc_ILAsToString(self->Kind.As, env);
                case ILFACTOR_CALL_OP_T:
                        return bc_ILCallOpToString(self->Kind.Call, env);
                case ILFACTOR_MEMBER_OP_T:
                        return bc_ILMemberOpToString(self->Kind.MemberOp, env);
                case ILFACTOR_INSTANCEOF_T:
                        return bc_ILInstanceOfToString(self->Kind.InstanceOf,
                                                       env);
                //あとで
                case ILFACTOR_EXPLICIT_UNARY_OP_T:
                        return NULL;
                case ILFACTOR_EXPLICIT_BINARY_OP_T:
                        return NULL;
                case ILFACTOR_PROPERTY_T:
                        return bc_ILPropertyToString(self->Kind.PropertyAccess,
                                                     env);
                case ILFACTOR_SUBSCRIPT_T:
                        return bc_ILSubscriptToString(self->Kind.Subscript,
                                                      env);
                default:
                        break;
        }
}

void bc_ILArgsToString(bc_Buffer* sb, bc_Vector* args, bc_Enviroment* env) {
        if (args->Length > 0) {
                bc_AppendBuffer(sb, '(');
        }
        for (int i = 0; i < args->Length; i++) {
                bc_ILArgument* e = (bc_ILArgument*)bc_AtVector(args, i);
                char* str = bc_ILFactorToString(e->Factor, env);
                bc_AppendsBuffer(sb, str);
                if (i != (args->Length)) {
                        bc_AppendsBuffer(sb, ", ");
                }
                MEM_FREE(str);
        }
        if (args->Length > 0) {
                bc_AppendBuffer(sb, ')');
        }
}

void bc_ILTypeArgsToString(bc_Buffer* sb, bc_Vector* type_args,
                           bc_Enviroment* env) {
        if (type_args->Length > 0) {
                bc_AppendsBuffer(sb, "<|");
        }
        for (int i = 0; i < type_args->Length; i++) {
                bc_ILTypeArgument* e =
                    (bc_ILTypeArgument*)bc_AtVector(type_args, i);
                char* str = bc_GenericCacheToString(e->GCache);
                bc_AppendsBuffer(sb, str);
                if (i != (type_args->Length - 1)) {
                        bc_AppendsBuffer(sb, ", ");
                }
                MEM_FREE(str);
        }
        if (type_args->Length > 0) {
                bc_AppendsBuffer(sb, "|>");
        }
}

void bc_DeleteILFactor(bc_ILFactor* self) {
        if (self == NULL) {
                return;
        }
        switch (self->Type) {
                case ILFACTOR_INT_T:
                        bc_DeleteILInt(self->Kind.Int);
                        break;
                case ILFACTOR_DOUBLE_T:
                        bc_DeleteILDouble(self->Kind.Double);
                        break;
                case ILFACTOR_CHAR_T:
                        bc_DeleteILChar(self->Kind.Char);
                        break;
                case ILFACTOR_STRING_T:
                        bc_DeleteILString(self->Kind.String);
                        break;
                case ILFACTOR_VARIABLE_T:
                        bc_DeleteILVariable(self->Kind.Variable);
                        break;
                case ILFACTOR_UNARY_OP_T:
                        bc_DeleteILUnaryOp(self->Kind.UnaryOp);
                        break;
                case ILFACTOR_BINARY_OP_T:
                        bc_DeleteILBinaryOp(self->Kind.BinaryOp);
                        break;
                case ILFACTOR_ASSIGN_T:
                        bc_DeleteILAssignOp(self->Kind.AssignOp);
                        break;
                case ILFACTOR_THIS_T:
                        bc_DeleteILThis(self->Kind.This);
                        break;
                case ILFACTOR_SUPER_T:
                        bc_DeleteILSuper(self->Kind.Super);
                        break;
                case ILFACTOR_NEW_INSTANCE_T:
                        bc_DeleteILNewInstance(self->Kind.NewInstance);
                        break;
                case ILFACTOR_BOOL_T:
                        bc_DeleteILBool(self->Kind.Bool);
                        break;
                case ILFACTOR_NULL_T:
                        break;
                case ILFACTOR_AS_T:
                        bc_DeleteILAs(self->Kind.As);
                        break;
                case ILFACTOR_CALL_OP_T:
                        bc_DeleteILCallOp(self->Kind.Call);
                        break;
                case ILFACTOR_MEMBER_OP_T:
                        bc_DeleteILMemberOp(self->Kind.MemberOp);
                        break;
                case ILFACTOR_INSTANCEOF_T:
                        bc_DeleteILInstanceOf(self->Kind.InstanceOf);
                        break;
                case ILFACTOR_EXPLICIT_UNARY_OP_T:
                        bc_DeleteILExplicitUnaryOp(self->Kind.ExpUnaryOp);
                        break;
                case ILFACTOR_EXPLICIT_BINARY_OP_T:
                        bc_DeleteILExplicitBinaryOp(self->Kind.ExpBinaryOp);
                        break;
                case ILFACTOR_PROPERTY_T:
                        bc_DeleteILPropertyAccess(self->Kind.PropertyAccess);
                        break;
                case ILFACTOR_SUBSCRIPT_T:
                        bc_DeleteILSubscript(self->Kind.Subscript);
                        break;
                default:
                        break;
        }
        MEM_FREE(self);
}
