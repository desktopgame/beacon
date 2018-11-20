#include "il_factor_interface.h"
#include "il_factor_impl.h"
#include "il_argument.h"
#include "il_type_argument.h"
#include "../util/text.h"
#include "../vm/enviroment.h"
#include "../env/type_interface.h"
#include "../env/class_loader.h"
#include "../util/mem.h"
#include <stdio.h>
#include <assert.h>

ILFactor* MallocILFactor(ILFactorType type, const char* filename, int lineno) {
	ILFactor* ret = bc_MXMalloc(sizeof(ILFactor), filename, lineno);
	ret->Type = type;
	ret->Lineno = -1;
	return ret;
}

void GenerateILFactor(ILFactor * self, bc_Enviroment* env, CallContext* cctx) {
	if(bc_GetLastPanic()) {
		return;
	}
	bc_SetPanicFile(env->ContextRef->FileName);
	bc_SetPanicLine(self->Lineno);
	switch (self->Type) {
		case ILFACTOR_INT_T:
			GenerateILInt(self->Kind.Int, env, cctx);
			break;
		case ILFACTOR_DOUBLE_T:
			GenerateILDouble(self->Kind.Double, env, cctx);
			break;
		case ILFACTOR_CHAR_T:
			GenerateILChar(self->Kind.Char, env, cctx);
			break;
		case ILFACTOR_STRING_T:
			GenerateILString(self->Kind.String, env, cctx);
			break;
		case ILFACTOR_VARIABLE_T:
			GenerateILVariable(self->Kind.Variable, env, cctx);
			break;
		case ILFACTOR_UNARY_OP_T:
			GenerateILUnaryOp(self->Kind.UnaryOp, env, cctx);
			break;
		case ILFACTOR_BINARY_OP_T:
			GenerateILBinaryOp(self->Kind.BinaryOp, env, cctx);
			break;
		case ILFACTOR_ASSIGN_T:
			GenerateILAssignOp(self->Kind.AssignOp, env, cctx);
			break;
		case ILFACTOR_THIS_T:
			GenerateILThis(self->Kind.This, env, cctx);
			break;
		case ILFACTOR_SUPER_T:
			GenerateILSuper(self->Kind.Super, env, cctx);
			break;
		case ILFACTOR_NEW_INSTANCE_T:
			GenerateILNewInstance(self->Kind.NewInstance, env, cctx);
			break;
		case ILFACTOR_BOOL_T:
			GenerateILBool(self->Kind.Bool, env, cctx);
			break;
		case ILFACTOR_NULL_T:
			GenerateILNull(NULL, env, cctx);
			break;
		case ILFACTOR_AS_T:
			GenerateILAs(self->Kind.As, env, cctx);
			break;
		case ILFACTOR_CALL_OP_T:
			GenerateILCallOp(self->Kind.Call, env, cctx);
			break;
		case ILFACTOR_MEMBER_OP_T:
			GenerateILMemberOp(self->Kind.MemberOp, env, cctx);
			break;
		case ILFACTOR_INSTANCEOF_T:
			GenerateILInstanceOf(self->Kind.InstanceOf, env, cctx);
			break;
		case ILFACTOR_EXPLICIT_UNARY_OP_T:
			GenerateILExplicitUnaryOp(self->Kind.ExpUnaryOp, env, cctx);
			break;
		case ILFACTOR_EXPLICIT_BINARY_OP_T:
			GenerateILExplicitBinaryOp(self->Kind.ExpBinaryOp, env, cctx);
			break;
		case ILFACTOR_PROPERTY_T:
			GenerateILPropertyAccess(self->Kind.PropertyAccess, env, cctx);
			break;
		case ILFACTOR_SUBSCRIPT_T:
			GenerateILSubscript(self->Kind.Subscript, env, cctx);
			break;
		default:
			break;
	}
	assert(self->Lineno >= 0);
	bc_AddRangeEnviroment(env, self->Lineno);
}

void LoadILFactor(ILFactor * self, bc_Enviroment * env, CallContext* cctx) {
	if(bc_GetLastPanic()) {
		return;
	}
	bc_SetPanicFile(env->ContextRef->FileName);
	bc_SetPanicLine(self->Lineno);
	switch (self->Type) {
		case ILFACTOR_INT_T:
			LoadILInt(self->Kind.Int, env, cctx);
			break;
		case ILFACTOR_DOUBLE_T:
			LoadILDouble(self->Kind.Double, env, cctx);
			break;
		case ILFACTOR_CHAR_T:
			LoadILChar(self->Kind.Char, env, cctx);
			break;
		case ILFACTOR_STRING_T:
			LoadILString(self->Kind.String, env, cctx);
			break;
		case ILFACTOR_VARIABLE_T:
			LoadILVariable(self->Kind.Variable, env, cctx);
			break;
		case ILFACTOR_UNARY_OP_T:
			LoadILUnaryOp(self->Kind.UnaryOp, env, cctx);
			break;
		case ILFACTOR_BINARY_OP_T:
			LoadILBinaryOp(self->Kind.BinaryOp, env, cctx);
			break;
		case ILFACTOR_ASSIGN_T:
			LoadILAssignOp(self->Kind.AssignOp, env, cctx);
			break;
		case ILFACTOR_THIS_T:
			LoadILThis(self->Kind.This, env, cctx);
			break;
		case ILFACTOR_SUPER_T:
			LoadILSuper(self->Kind.Super, env, cctx);
			break;
		case ILFACTOR_NEW_INSTANCE_T:
			LoadILNewInstance(self->Kind.NewInstance, env, cctx);
			break;
		case ILFACTOR_BOOL_T:
			//ILBool_load(self->Kind.Bool, depth);
			break;
		case ILFACTOR_NULL_T:
			LoadILNull(NULL, env, cctx);
			break;
		case ILFACTOR_AS_T:
			LoadILAs(self->Kind.As, env, cctx);
			break;
		case ILFACTOR_CALL_OP_T:
			LoadCallOp(self->Kind.Call, env, cctx);
			break;
		case ILFACTOR_MEMBER_OP_T:
			LoadILMemberOp(self->Kind.MemberOp, env, cctx);
			break;
		case ILFACTOR_INSTANCEOF_T:
			LoadILInstanceOf(self->Kind.InstanceOf, env, cctx);
			break;
		case ILFACTOR_EXPLICIT_UNARY_OP_T:
			LoadILExplicitUnaryOp(self->Kind.ExpUnaryOp, env, cctx);
			break;
		case ILFACTOR_EXPLICIT_BINARY_OP_T:
			LoadILExplicitBinaryOp(self->Kind.ExpBinaryOp, env, cctx);
			break;
		case ILFACTOR_PROPERTY_T:
			LoadILProperty(self->Kind.PropertyAccess, env, cctx);
			break;
		case ILFACTOR_SUBSCRIPT_T:
			LoadILSubscript(self->Kind.Subscript, env, cctx);
			break;
		default:
			break;
	}
}

bc_GenericType* EvalILFactor(ILFactor * self, bc_Enviroment * env, CallContext* cctx) {
	if(bc_GetLastPanic()) {
		return NULL;
	}
	bc_SetPanicFile(env->ContextRef->FileName);
	bc_SetPanicLine(self->Lineno);
	bc_GenericType* ret = NULL;
	switch (self->Type) {
		case ILFACTOR_INT_T:
			ret = EvalILInt(self->Kind.Int, env, cctx);
			break;
		case ILFACTOR_DOUBLE_T:
			ret = EvalILDouble(self->Kind.Double, env, cctx);
			break;
		case ILFACTOR_CHAR_T:
			ret = EvalILChar(self->Kind.Char, env, cctx);
			break;
		case ILFACTOR_STRING_T:
			ret = EvalILString(self->Kind.String, env, cctx);
			break;
		case ILFACTOR_VARIABLE_T:
			ret = EvalILVariable(self->Kind.Variable, env, cctx);
			break;
		case ILFACTOR_UNARY_OP_T:
			ret = EvalILUnaryOp(self->Kind.UnaryOp, env, cctx);
			break;
		case ILFACTOR_BINARY_OP_T:
			ret = EvalILBinaryOp(self->Kind.BinaryOp, env, cctx);
			break;
		case ILFACTOR_ASSIGN_T:
			ret = EvalILAssignOp(self->Kind.AssignOp, env, cctx);
			break;
		case ILFACTOR_THIS_T:
			ret = EvalILThis(self->Kind.This, env, cctx);
			break;
		case ILFACTOR_SUPER_T:
			ret = EvalILSuper(self->Kind.Super, env, cctx);
			break;
		case ILFACTOR_NEW_INSTANCE_T:
			ret = EvalILNewInstance(self->Kind.NewInstance, env, cctx);
			break;
		case ILFACTOR_BOOL_T:
			ret = EvalILBool(self->Kind.Bool,env, cctx);
			break;
		case ILFACTOR_NULL_T:
			ret = EvalILNull(NULL, env, cctx);
			break;
		case ILFACTOR_AS_T:
			ret = EvalILAs(self->Kind.As, env, cctx);
			break;
		case ILFACTOR_CALL_OP_T:
			ret = EvalILCallOp(self->Kind.Call, env, cctx);
			break;
		case ILFACTOR_MEMBER_OP_T:
			ret = EvalILMemberOp(self->Kind.MemberOp, env, cctx);
			break;
		case ILFACTOR_INSTANCEOF_T:
			ret = EvalILInstanceOf(self->Kind.InstanceOf, env, cctx);
			break;
		case ILFACTOR_EXPLICIT_UNARY_OP_T:
			ret = EvalILExplicitUnaryOp(self->Kind.ExpUnaryOp, env, cctx);
			break;
		case ILFACTOR_EXPLICIT_BINARY_OP_T:
			ret = EvalILExplicitBinaryOp(self->Kind.ExpBinaryOp, env, cctx);
			break;
		case ILFACTOR_PROPERTY_T:
			ret = EvalILProperty(self->Kind.PropertyAccess, env, cctx);
			break;
		case ILFACTOR_SUBSCRIPT_T:
			ret = EvalILSubscript(self->Kind.Subscript, env, cctx);
			break;
		default:
			assert(false);
			break;
	}
	//assert(ret != NULL);
	return ret;
}

char* ILFactorToString(ILFactor* self, bc_Enviroment* env) {
	if(bc_GetLastPanic()) {
		return NULL;
	}
	switch (self->Type) {
		case ILFACTOR_INT_T:
			return ILIntToString(self->Kind.Int, env);
		case ILFACTOR_DOUBLE_T:
			return ILDoubleToString(self->Kind.Double, env);
		case ILFACTOR_CHAR_T:
			return ILCharToString(self->Kind.Char, env);
		case ILFACTOR_STRING_T:
			return ILStringToString(self->Kind.String, env);
		case ILFACTOR_VARIABLE_T:
			return ILVariableToString(self->Kind.Variable, env);
		case ILFACTOR_UNARY_OP_T:
			return ILUnaryOpToString(self->Kind.UnaryOp, env);
		case ILFACTOR_BINARY_OP_T:
			return ILBinaryOpToString(self->Kind.BinaryOp, env);
		case ILFACTOR_ASSIGN_T:
			return NULL;
		case ILFACTOR_THIS_T:
			return ILThisToString(self->Kind.This, env);
		case ILFACTOR_SUPER_T:
			return ILSuperToString(self->Kind.Super, env);
		case ILFACTOR_NEW_INSTANCE_T:
			return ILNewInstanceToString(self->Kind.NewInstance, env);
		case ILFACTOR_BOOL_T:
			return ILBoolToString(self->Kind.Bool, env);
		case ILFACTOR_NULL_T:
			return ILNullToString(self->Kind.Null, env);
		case ILFACTOR_AS_T:
			return ILAsToString(self->Kind.As, env);
		case ILFACTOR_CALL_OP_T:
			return ILCallOpToString(self->Kind.Call, env);
		case ILFACTOR_MEMBER_OP_T:
			return ILMemberOpToString(self->Kind.MemberOp, env);
		case ILFACTOR_INSTANCEOF_T:
			return ILInstanceOfToString(self->Kind.InstanceOf, env);
		//あとで
		case ILFACTOR_EXPLICIT_UNARY_OP_T:
			return NULL;
		case ILFACTOR_EXPLICIT_BINARY_OP_T:
			return NULL;
		case ILFACTOR_PROPERTY_T:
			return ILPropertyToString(self->Kind.PropertyAccess, env);
		case ILFACTOR_SUBSCRIPT_T:
			return ILSubscriptToString(self->Kind.Subscript, env);
		default:
			break;
	}
}

void ILArgsToString(bc_Buffer* sb, bc_Vector* args, bc_Enviroment* env) {
	if(args->Length > 0) {
		bc_AppendBuffer(sb, '(');
	}
	for(int i=0; i<args->Length; i++) {
		ILArgument* e = (ILArgument*)bc_AtVector(args, i);
		char* str = ILFactorToString(e->Factor, env);
		bc_AppendsBuffer(sb, str);
		if(i != (args->Length)) {
			bc_AppendsBuffer(sb, ", ");
		}
		MEM_FREE(str);
	}
	if(args->Length > 0) {
		bc_AppendBuffer(sb, ')');
	}
}

void ILTypeArgsToString(bc_Buffer* sb, bc_Vector* type_args, bc_Enviroment* env) {
	if(type_args->Length > 0) {
		bc_AppendsBuffer(sb, "<|");
	}
	for(int i=0; i<type_args->Length; i++) {
		ILTypeArgument* e = (ILTypeArgument*)bc_AtVector(type_args, i);
		char* str = bc_GenericCacheToString(e->GCache);
		bc_AppendsBuffer(sb, str);
		if(i != (type_args->Length - 1)) {
			bc_AppendsBuffer(sb, ", ");
		}
		MEM_FREE(str);
	}
	if(type_args->Length > 0) {
		bc_AppendsBuffer(sb, "|>");
	}
}

void DeleteILFactor(ILFactor * self) {
	if (self == NULL) {
		return;
	}
	switch (self->Type) {
		case ILFACTOR_INT_T:
			DeleteILInt(self->Kind.Int);
			break;
		case ILFACTOR_DOUBLE_T:
			DeleteILDouble(self->Kind.Double);
			break;
		case ILFACTOR_CHAR_T:
			DeleteILChar(self->Kind.Char);
			break;
		case ILFACTOR_STRING_T:
			DeleteILString(self->Kind.String);
			break;
		case ILFACTOR_VARIABLE_T:
			DeleteILVariable(self->Kind.Variable);
			break;
		case ILFACTOR_UNARY_OP_T:
			DeleteILUnaryOp(self->Kind.UnaryOp);
			break;
		case ILFACTOR_BINARY_OP_T:
			DeleteILBinaryOp(self->Kind.BinaryOp);
			break;
		case ILFACTOR_ASSIGN_T:
			DeleteILAssignOp(self->Kind.AssignOp);
			break;
		case ILFACTOR_THIS_T:
			DeleteILThis(self->Kind.This);
			break;
		case ILFACTOR_SUPER_T:
			DeleteILSuper(self->Kind.Super);
			break;
		case ILFACTOR_NEW_INSTANCE_T:
			DeleteILNewInstance(self->Kind.NewInstance);
			break;
		case ILFACTOR_BOOL_T:
			DeleteILBool(self->Kind.Bool);
			break;
		case ILFACTOR_NULL_T:
			break;
		case ILFACTOR_AS_T:
			DeleteILAs(self->Kind.As);
			break;
		case ILFACTOR_CALL_OP_T:
			DeleteILCallOp(self->Kind.Call);
			break;
		case ILFACTOR_MEMBER_OP_T:
			DeleteILMemberOp(self->Kind.MemberOp);
			break;
		case ILFACTOR_INSTANCEOF_T:
			DeleteILInstanceOf(self->Kind.InstanceOf);
			break;
		case ILFACTOR_EXPLICIT_UNARY_OP_T:
			DeleteILExplicitUnaryOp(self->Kind.ExpUnaryOp);
			break;
		case ILFACTOR_EXPLICIT_BINARY_OP_T:
			DeleteILExplicitBinaryOp(self->Kind.ExpBinaryOp);
			break;
		case ILFACTOR_PROPERTY_T:
			DeleteILPropertyAccess(self->Kind.PropertyAccess);
			break;
		case ILFACTOR_SUBSCRIPT_T:
			DeleteILSubscript(self->Kind.Subscript);
			break;
		default:
			break;
	}
	MEM_FREE(self);
}
