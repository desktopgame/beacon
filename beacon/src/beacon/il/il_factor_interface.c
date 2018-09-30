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

il_factor* MallocILFactor(il_factor_type type, const char* filename, int lineno) {
	il_factor* ret = mem_malloc(sizeof(il_factor), filename, lineno);
	ret->type = type;
	ret->lineno = -1;
	return ret;
}

void GenerateILFactor(il_factor * self, enviroment* env, call_context* cctx) {
	if(GetLastBCError()) {
		return;
	}
	SetBCErrorFile(env->context_ref->filename);
	SetBCErrorLine(self->lineno);
	switch (self->type) {
		case ILFACTOR_INT_T:
			GenerateILInt(self->u.int_, env, cctx);
			break;
		case ILFACTOR_DOUBLE_T:
			il_factor_double_generate(self->u.double_, env, cctx);
			break;
		case ILFACTOR_CHAR_T:
			GenerateILChar(self->u.char_, env, cctx);
			break;
		case ILFACTOR_STRING_T:
			il_factor_string_generate(self->u.string_, env, cctx);
			break;
		case ILFACTOR_VARIABLE_T:
			il_factor_variable_generate(self->u.variable_, env, cctx);
			break;
		case ILFACTOR_UNARY_OP_T:
			il_factor_unary_op_generate(self->u.unary_, env, cctx);
			break;
		case ILFACTOR_BINARY_OP_T:
			il_factor_binary_op_generate(self->u.binary_, env, cctx);
			break;
		case ILFACTOR_ASSIGN_T:
			il_factor_assign_op_generate(self->u.assign_, env, cctx);
			break;
		case ILFACTOR_THIS_T:
			il_factor_this_generate(self->u.this_, env, cctx);
			break;
		case ILFACTOR_SUPER_T:
			il_factor_super_generate(self->u.super_, env, cctx);
			break;
		case ILFACTOR_NEW_INSTANCE_T:
			il_factor_new_instance_generate(self->u.new_instance_, env, cctx);
			break;
		case ILFACTOR_BOOL_T:
			GenerateILBool(self->u.bool_, env, cctx);
			break;
		case ILFACTOR_NULL_T:
			il_factor_null_generate(NULL, env, cctx);
			break;
		case ILFACTOR_AS_T:
			GenerateILAs(self->u.as_, env, cctx);
			break;
		case ILFACTOR_CALL_OP_T:
			il_factor_call_op_generate(self->u.call_, env, cctx);
			break;
		case ILFACTOR_MEMBER_OP_T:
			il_factor_member_op_generate(self->u.member_, env, cctx);
			break;
		case ILFACTOR_INSTANCEOF_T:
			il_factor_instanceof_generate(self->u.instanceof_, env, cctx);
			break;
		case ILFACTOR_EXPLICIT_UNARY_OP_T:
			il_factor_explicit_unary_op_generate(self->u.exp_unary_op, env, cctx);
			break;
		case ILFACTOR_EXPLICIT_BINARY_OP_T:
			il_factor_explicit_binary_op_generate(self->u.exp_binary_op, env, cctx);
			break;
		case ILFACTOR_PROPERTY_T:
			il_factor_property_generate(self->u.prop, env, cctx);
			break;
		case ILFACTOR_SUBSCRIPT_T:
			il_factor_subscript_generate(self->u.subscript, env, cctx);
			break;
		default:
			break;
	}
	assert(self->lineno >= 0);
	AddRangeEnviroment(env, self->lineno);
}

void LoadILFactor(il_factor * self, enviroment * env, call_context* cctx) {
	if(GetLastBCError()) {
		return;
	}
	SetBCErrorFile(env->context_ref->filename);
	SetBCErrorLine(self->lineno);
	switch (self->type) {
		case ILFACTOR_INT_T:
			LoadILInt(self->u.int_, env, cctx);
			break;
		case ILFACTOR_DOUBLE_T:
			LoadILDouble(self->u.double_, env, cctx);
			break;
		case ILFACTOR_CHAR_T:
			LoadILChar(self->u.char_, env, cctx);
			break;
		case ILFACTOR_STRING_T:
			LoadILString(self->u.string_, env, cctx);
			break;
		case ILFACTOR_VARIABLE_T:
			il_factor_variable_load(self->u.variable_, env, cctx);
			break;
		case ILFACTOR_UNARY_OP_T:
			il_factor_unary_OP_LOAD(self->u.unary_, env, cctx);
			break;
		case ILFACTOR_BINARY_OP_T:
			il_factor_binary_OP_LOAD(self->u.binary_, env, cctx);
			break;
		case ILFACTOR_ASSIGN_T:
			il_factor_assign_OP_LOAD(self->u.assign_, env, cctx);
			break;
		case ILFACTOR_THIS_T:
			LoadILThis(self->u.this_, env, cctx);
			break;
		case ILFACTOR_SUPER_T:
			LoadILSuper(self->u.super_, env, cctx);
			break;
		case ILFACTOR_NEW_INSTANCE_T:
			il_factor_new_instance_load(self->u.new_instance_, env, cctx);
			break;
		case ILFACTOR_BOOL_T:
			//il_factor_bool_load(self->u.bool_, depth);
			break;
		case ILFACTOR_NULL_T:
			LoadILNull(NULL, env, cctx);
			break;
		case ILFACTOR_AS_T:
			LoadILAs(self->u.as_, env, cctx);
			break;
		case ILFACTOR_CALL_OP_T:
			LoadCallOp(self->u.call_, env, cctx);
			break;
		case ILFACTOR_MEMBER_OP_T:
			il_factor_member_OP_LOAD(self->u.member_, env, cctx);
			break;
		case ILFACTOR_INSTANCEOF_T:
			il_factor_instanceof_load(self->u.instanceof_, env, cctx);
			break;
		case ILFACTOR_EXPLICIT_UNARY_OP_T:
			il_factor_explicit_unary_OP_LOAD(self->u.exp_unary_op, env, cctx);
			break;
		case ILFACTOR_EXPLICIT_BINARY_OP_T:
			il_factor_explicit_binary_OP_LOAD(self->u.exp_binary_op, env, cctx);
			break;
		case ILFACTOR_PROPERTY_T:
			LoadILProperty(self->u.prop, env, cctx);
			break;
		case ILFACTOR_SUBSCRIPT_T:
			il_factor_subscript_load(self->u.subscript, env, cctx);
			break;
		default:
			break;
	}
}

generic_type* EvalILFactor(il_factor * self, enviroment * env, call_context* cctx) {
	if(GetLastBCError()) {
		return NULL;
	}
	SetBCErrorFile(env->context_ref->filename);
	SetBCErrorLine(self->lineno);
	generic_type* ret = NULL;
	switch (self->type) {
		case ILFACTOR_INT_T:
			ret = EvalILInt(self->u.int_, env, cctx);
			break;
		case ILFACTOR_DOUBLE_T:
			ret = EvalILDouble(self->u.double_, env, cctx);
			break;
		case ILFACTOR_CHAR_T:
			ret = EvalILChar(self->u.char_, env, cctx);
			break;
		case ILFACTOR_STRING_T:
			ret = EvalILString(self->u.string_, env, cctx);
			break;
		case ILFACTOR_VARIABLE_T:
			ret = il_factor_variable_eval(self->u.variable_, env, cctx);
			break;
		case ILFACTOR_UNARY_OP_T:
			ret = il_factor_unary_op_eval(self->u.unary_, env, cctx);
			break;
		case ILFACTOR_BINARY_OP_T:
			ret = il_factor_binary_op_eval(self->u.binary_, env, cctx);
			break;
		case ILFACTOR_ASSIGN_T:
			ret = il_factor_assign_op_eval(self->u.assign_, env, cctx);
			break;
		case ILFACTOR_THIS_T:
			ret = EvalILThis(self->u.this_, env, cctx);
			break;
		case ILFACTOR_SUPER_T:
			ret = EvalILSuper(self->u.super_, env, cctx);
			break;
		case ILFACTOR_NEW_INSTANCE_T:
			ret = il_factor_new_instance_eval(self->u.new_instance_, env, cctx);
			break;
		case ILFACTOR_BOOL_T:
			ret = EvalILBool(self->u.bool_,env, cctx);
			break;
		case ILFACTOR_NULL_T:
			ret = EvalILNull(NULL, env, cctx);
			break;
		case ILFACTOR_AS_T:
			ret = EvalILAs(self->u.as_, env, cctx);
			break;
		case ILFACTOR_CALL_OP_T:
			ret = EvalILCallOp(self->u.call_, env, cctx);
			break;
		case ILFACTOR_MEMBER_OP_T:
			ret = il_factor_member_op_eval(self->u.member_, env, cctx);
			break;
		case ILFACTOR_INSTANCEOF_T:
			ret = il_factor_instanceof_eval(self->u.instanceof_, env, cctx);
			break;
		case ILFACTOR_EXPLICIT_UNARY_OP_T:
			ret = il_factor_explicit_unary_op_eval(self->u.exp_unary_op, env, cctx);
			break;
		case ILFACTOR_EXPLICIT_BINARY_OP_T:
			ret = il_factor_explicit_binary_op_eval(self->u.exp_binary_op, env, cctx);
			break;
		case ILFACTOR_PROPERTY_T:
			ret = il_factor_property_eval(self->u.prop, env, cctx);
			break;
		case ILFACTOR_SUBSCRIPT_T:
			ret = il_factor_subscript_eval(self->u.subscript, env, cctx);
			break;
		default:
			assert(false);
			break;
	}
	//assert(ret != NULL);
	return ret;
}

char* ILFactorToString(il_factor* self, enviroment* env) {
	if(GetLastBCError()) {
		return NULL;
	}
	switch (self->type) {
		case ILFACTOR_INT_T:
			return ILIntToString(self->u.int_, env);
		case ILFACTOR_DOUBLE_T:
			return ILDoubleToString(self->u.double_, env);
		case ILFACTOR_CHAR_T:
			return ILCharToString(self->u.char_, env);
		case ILFACTOR_STRING_T:
			return ILStringToString(self->u.string_, env);
		case ILFACTOR_VARIABLE_T:
			return il_factor_variable_tostr(self->u.variable_, env);
		case ILFACTOR_UNARY_OP_T:
			return il_factor_unary_op_tostr(self->u.unary_, env);
		case ILFACTOR_BINARY_OP_T:
			return il_factor_binary_op_tostr(self->u.binary_, env);
		case ILFACTOR_ASSIGN_T:
			return NULL;
		case ILFACTOR_THIS_T:
			return ILThisToString(self->u.this_, env);
		case ILFACTOR_SUPER_T:
			return ILSuperToString(self->u.super_, env);
		case ILFACTOR_NEW_INSTANCE_T:
			return il_factor_new_instance_tostr(self->u.new_instance_, env);
		case ILFACTOR_BOOL_T:
			return ILBoolToString(self->u.bool_, env);
		case ILFACTOR_NULL_T:
			return ILNullToString(self->u.null_, env);
		case ILFACTOR_AS_T:
			return ILAsToString(self->u.as_, env);
		case ILFACTOR_CALL_OP_T:
			return il_factor_call_op_to_str(self->u.call_, env);
		case ILFACTOR_MEMBER_OP_T:
			return il_factor_member_op_tostr(self->u.member_, env);
		case ILFACTOR_INSTANCEOF_T:
			return il_factor_instanceof_tostr(self->u.instanceof_, env);
		//あとで
		case ILFACTOR_EXPLICIT_UNARY_OP_T:
			return NULL;
		case ILFACTOR_EXPLICIT_BINARY_OP_T:
			return NULL;
		case ILFACTOR_PROPERTY_T:
			return il_factor_property_tostr(self->u.prop, env);
		case ILFACTOR_SUBSCRIPT_T:
			return il_factor_subscript_tostr(self->u.subscript, env);
		default:
			break;
	}
}

void ILArgsToString(string_buffer* sb, Vector* args, enviroment* env) {
	if(args->length > 0) {
		AppendBuffer(sb, '(');
	}
	for(int i=0; i<args->length; i++) {
		il_argument* e = (il_argument*)AtVector(args, i);
		char* str = ILFactorToString(e->factor, env);
		AppendsBuffer(sb, str);
		if(i != (args->length)) {
			AppendsBuffer(sb, ", ");
		}
		MEM_FREE(str);
	}
	if(args->length > 0) {
		AppendBuffer(sb, ')');
	}
}

void il_factor_type_args_tostr(string_buffer* sb, Vector* type_args, enviroment* env) {
	if(type_args->length > 0) {
		AppendsBuffer(sb, "<|");
	}
	for(int i=0; i<type_args->length; i++) {
		il_type_argument* e = (il_type_argument*)AtVector(type_args, i);
		char* str = generic_cache_tostr(e->gcache);
		AppendsBuffer(sb, str);
		if(i != (type_args->length - 1)) {
			AppendsBuffer(sb, ", ");
		}
		MEM_FREE(str);
	}
	if(type_args->length > 0) {
		AppendsBuffer(sb, "|>");
	}
}

void DeleteILFactor(il_factor * self) {
	if (self == NULL) {
		return;
	}
	switch (self->type) {
		case ILFACTOR_INT_T:
			DeleteILInt(self->u.int_);
			break;
		case ILFACTOR_DOUBLE_T:
			DeleteILDouble(self->u.double_);
			break;
		case ILFACTOR_CHAR_T:
			DeleteILChar(self->u.char_);
			break;
		case ILFACTOR_STRING_T:
			il_factor_string_delete(self->u.string_);
			break;
		case ILFACTOR_VARIABLE_T:
			il_factor_variable_delete(self->u.variable_);
			break;
		case ILFACTOR_UNARY_OP_T:
			il_factor_unary_op_delete(self->u.unary_);
			break;
		case ILFACTOR_BINARY_OP_T:
			il_factor_binary_op_delete(self->u.binary_);
			break;
		case ILFACTOR_ASSIGN_T:
			il_factor_assign_op_delete(self->u.assign_);
			break;
		case ILFACTOR_THIS_T:
			DeleteILThis(self->u.this_);
			break;
		case ILFACTOR_SUPER_T:
			DeleteILSuper(self->u.super_);
			break;
		case ILFACTOR_NEW_INSTANCE_T:
			il_factor_new_instance_delete(self->u.new_instance_);
			break;
		case ILFACTOR_BOOL_T:
			DeleteILBool(self->u.bool_);
			break;
		case ILFACTOR_NULL_T:
			break;
		case ILFACTOR_AS_T:
			DeleteILAs(self->u.as_);
			break;
		case ILFACTOR_CALL_OP_T:
			il_factor_call_op_delete(self->u.call_);
			break;
		case ILFACTOR_MEMBER_OP_T:
			il_factor_member_op_delete(self->u.member_);
			break;
		case ILFACTOR_INSTANCEOF_T:
			il_factor_instanceof_delete(self->u.instanceof_);
			break;
		case ILFACTOR_EXPLICIT_UNARY_OP_T:
			il_factor_explicit_unary_op_delete(self->u.exp_unary_op);
			break;
		case ILFACTOR_EXPLICIT_BINARY_OP_T:
			il_factor_explicit_binary_op_delete(self->u.exp_binary_op);
			break;
		case ILFACTOR_PROPERTY_T:
			il_factor_property_delete(self->u.prop);
			break;
		case ILFACTOR_SUBSCRIPT_T:
			il_factor_subscript_delete(self->u.subscript);
			break;
		default:
			break;
	}
	MEM_FREE(self);
}
