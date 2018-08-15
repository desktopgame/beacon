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

il_factor* il_factor_malloc(il_factor_type type, const char* filename, int lineno) {
	il_factor* ret = mem_malloc(sizeof(il_factor), filename, lineno);
	ret->type = type;
	ret->lineno = -1;
	return ret;
}

void il_factor_dump(il_factor * self, int depth) {
	il_print_layout_form(self->lineno);
	switch (self->type) {
		case ilfactor_int:
			il_factor_int_dump(self->u.int_, depth);
			break;
		case ilfactor_double:
			il_factor_double_dump(self->u.double_, depth);
			break;
		case ilfactor_char:
			il_factor_char_dump(self->u.char_, depth);
			break;
		case ilfactor_string:
			il_factor_string_dump(self->u.string_, depth);
			break;
		case ilfactor_variable:
			il_factor_variable_dump(self->u.variable_, depth);
			break;
		case ilfactor_unary_op:
			il_factor_unary_op_dump(self->u.unary_, depth);
			break;
		case ilfactor_binary_op:
			il_factor_binary_op_dump(self->u.binary_, depth);
			break;
		case ilfactor_assign_op:
			il_factor_assign_op_dump(self->u.assign_, depth);
			break;
		case ilfactor_this:
			il_factor_this_dump(self->u.this_, depth);
			break;
		case ilfactor_super:
			il_factor_super_dump(self->u.super_, depth);
			break;
		case ilfactor_new_instance:
			il_factor_new_instance_dump(self->u.new_instance_, depth);
			break;
		case ilfactor_cast:
			il_factor_cast_dump(self->u.cast_, depth);
			break;
		case ilfactor_bool:
			il_factor_bool_dump(self->u.bool_, depth);
			break;
		case ilfactor_null:
			il_factor_null_dump(NULL, depth);
			break;
		case ilfactor_as:
			il_factor_as_dump(self->u.as_, depth);
			break;
		case ilfactor_inc:
			il_factor_inc_dump(self->u.inc_, depth);
			break;
		case ilfactor_dec:
			il_factor_dec_dump(self->u.dec_, depth);
			break;
		case ilfactor_call_op:
			il_factor_call_op_dump(self->u.call_, depth);
			break;
		case ilfactor_member_op:
			il_factor_member_op_dump(self->u.member_, depth);
			break;
		case ilfactor_instanceof:
			il_factor_instanceof_dump(self->u.instanceof_, depth);
			break;
		case ilfactor_explicit_unary_op:
			il_factor_explicit_unary_op_dump(self->u.exp_unary_op, depth);
			break;
		case ilfactor_explicit_binary_op:
			il_factor_explicit_binary_op_dump(self->u.exp_binary_op, depth);
			break;
		case ilfactor_lambda:
			il_factor_lambda_dump(self->u.lambda_, depth);
			break;
		case ilfactor_property:
			il_factor_property_dump(self->u.prop, depth);
			break;
		case ilfactor_subscript:
			il_factor_subscript_dump(self->u.subscript, depth);
			break;
		default:
			break;
	}
}

void il_factor_generate(il_factor * self, enviroment* env, call_context* cctx) {
	if(bc_error_last()) {
		return;
	}
	switch (self->type) {
		case ilfactor_int:
			il_factor_int_generate(self->u.int_, env, cctx);
			break;
		case ilfactor_double:
			il_factor_double_generate(self->u.double_, env, cctx);
			break;
		case ilfactor_char:
			il_factor_char_generate(self->u.char_, env, cctx);
			break;
		case ilfactor_string:
			il_factor_string_generate(self->u.string_, env, cctx);
			break;
		case ilfactor_variable:
			il_factor_variable_generate(self->u.variable_, env, cctx);
			break;
		case ilfactor_unary_op:
			il_factor_unary_op_generate(self->u.unary_, env, cctx);
			break;
		case ilfactor_binary_op:
			il_factor_binary_op_generate(self->u.binary_, env, cctx);
			break;
		case ilfactor_assign_op:
			il_factor_assign_op_generate(self->u.assign_, env, cctx);
			break;
		case ilfactor_this:
			il_factor_this_generate(self->u.this_, env, cctx);
			break;
		case ilfactor_super:
			il_factor_super_generate(self->u.super_, env, cctx);
			break;
		case ilfactor_new_instance:
			il_factor_new_instance_generate(self->u.new_instance_, env, cctx);
			break;
		case ilfactor_cast:
			il_factor_cast_generate(self->u.cast_, env, cctx);
			break;
		case ilfactor_bool:
			il_factor_bool_generate(self->u.bool_, env, cctx);
			break;
		case ilfactor_null:
			il_factor_null_generate(NULL, env, cctx);
			break;
		case ilfactor_as:
			il_factor_as_generate(self->u.as_, env, cctx);
			break;
		case ilfactor_inc:
			il_factor_inc_generate(self->u.inc_, env, cctx);
			break;
		case ilfactor_dec:
			il_factor_dec_generate(self->u.dec_, env, cctx);
			break;
		case ilfactor_call_op:
			il_factor_call_op_generate(self->u.call_, env, cctx);
			break;
		case ilfactor_member_op:
			il_factor_member_op_generate(self->u.member_, env, cctx);
			break;
		case ilfactor_instanceof:
			il_factor_instanceof_generate(self->u.instanceof_, env, cctx);
			break;
		case ilfactor_explicit_unary_op:
			il_factor_explicit_unary_op_generate(self->u.exp_unary_op, env, cctx);
			break;
		case ilfactor_explicit_binary_op:
			il_factor_explicit_binary_op_generate(self->u.exp_binary_op, env, cctx);
			break;
		case ilfactor_lambda:
			il_factor_lambda_generate(self->u.lambda_, env, cctx);
			break;
		case ilfactor_property:
			il_factor_property_generate(self->u.prop, env, cctx);
			break;
		case ilfactor_subscript:
			il_factor_subscript_generate(self->u.subscript, env, cctx);
			break;
		default:
			break;
	}
	assert(self->lineno >= 0);
	enviroment_add_range(env, self->lineno);
}

void il_factor_load(il_factor * self, enviroment * env, call_context* cctx) {
	if(bc_error_last()) {
		return;
	}
	assert(self->lineno >= 0);
	bc_error_file(env->context_ref->filename);
	bc_error_line(self->lineno);
	switch (self->type) {
		case ilfactor_int:
			il_factor_int_load(self->u.int_, env, cctx);
			break;
		case ilfactor_double:
			il_factor_double_load(self->u.double_, env, cctx);
			break;
		case ilfactor_char:
			il_factor_char_load(self->u.char_, env, cctx);
			break;
		case ilfactor_string:
			il_factor_string_load(self->u.string_, env, cctx);
			break;
		case ilfactor_variable:
			il_factor_variable_load(self->u.variable_, env, cctx);
			break;
		case ilfactor_unary_op:
			il_factor_unary_op_load(self->u.unary_, env, cctx);
			break;
		case ilfactor_binary_op:
			il_factor_binary_op_load(self->u.binary_, env, cctx);
			break;
		case ilfactor_assign_op:
			il_factor_assign_op_load(self->u.assign_, env, cctx);
			break;
		case ilfactor_this:
			il_factor_this_load(self->u.this_, env, cctx);
			break;
		case ilfactor_super:
			il_factor_super_load(self->u.super_, env, cctx);
			break;
		case ilfactor_new_instance:
			il_factor_new_instance_load(self->u.new_instance_, env, cctx);
			break;
		case ilfactor_cast:
			il_factor_cast_load(self->u.cast_, env, cctx);
			break;
		case ilfactor_bool:
			//il_factor_bool_load(self->u.bool_, depth);
			break;
		case ilfactor_null:
			il_factor_null_load(NULL, env, cctx);
			break;
		case ilfactor_as:
			il_factor_as_load(self->u.as_, env, cctx);
			break;
		case ilfactor_inc:
			il_factor_inc_load(self->u.inc_, env, cctx);
			break;
		case ilfactor_dec:
			il_factor_dec_load(self->u.dec_, env, cctx);
			break;
		case ilfactor_call_op:
			il_factor_call_op_load(self->u.call_, env, cctx);
			break;
		case ilfactor_member_op:
			il_factor_member_op_load(self->u.member_, env, cctx);
			break;
		case ilfactor_instanceof:
			il_factor_instanceof_load(self->u.instanceof_, env, cctx);
			break;
		case ilfactor_explicit_unary_op:
			il_factor_explicit_unary_op_load(self->u.exp_unary_op, env, cctx);
			break;
		case ilfactor_explicit_binary_op:
			il_factor_explicit_binary_op_load(self->u.exp_binary_op, env, cctx);
			break;
		case ilfactor_lambda:
			il_factor_lambda_load(self->u.lambda_, env, cctx);
			break;
		case ilfactor_property:
			il_factor_property_load(self->u.prop, env, cctx);
			break;
		case ilfactor_subscript:
			il_factor_subscript_load(self->u.subscript, env, cctx);
			break;
		default:
			break;
	}
}

generic_type* il_factor_eval(il_factor * self, enviroment * env, call_context* cctx) {
	if(bc_error_last()) {
		return NULL;
	}
	bc_error_file(env->context_ref->filename);
	bc_error_line(self->lineno);
	generic_type* ret = NULL;
	switch (self->type) {
		case ilfactor_int:
			ret = il_factor_int_eval(self->u.int_, env, cctx);
			break;
		case ilfactor_double:
			ret = il_factor_double_eval(self->u.double_, env, cctx);
			break;
		case ilfactor_char:
			ret = il_factor_char_eval(self->u.char_, env, cctx);
			break;
		case ilfactor_string:
			ret = il_factor_string_eval(self->u.string_, env, cctx);
			break;
		case ilfactor_variable:
			ret = il_factor_variable_eval(self->u.variable_, env, cctx);
			break;
		case ilfactor_unary_op:
			ret = il_factor_unary_op_eval(self->u.unary_, env, cctx);
			break;
		case ilfactor_binary_op:
			ret = il_factor_binary_op_eval(self->u.binary_, env, cctx);
			break;
		case ilfactor_assign_op:
			ret = il_factor_assign_op_eval(self->u.assign_, env, cctx);
			break;
		case ilfactor_this:
			ret = il_factor_this_eval(self->u.this_, env, cctx);
			break;
		case ilfactor_super:
			ret = il_factor_super_eval(self->u.super_, env, cctx);
			break;
		case ilfactor_new_instance:
			ret = il_factor_new_instance_eval(self->u.new_instance_, env, cctx);
			break;
		case ilfactor_cast:
			ret = il_factor_cast_eval(self->u.cast_, env, cctx);
			break;
		case ilfactor_bool:
			ret = il_factor_bool_eval(self->u.bool_,env, cctx);
			break;
		case ilfactor_null:
			ret = il_factor_null_eval(NULL, env, cctx);
			break;
		case ilfactor_as:
			ret = il_factor_as_eval(self->u.as_, env, cctx);
			break;
		case ilfactor_inc:
			ret = il_factor_inc_eval(self->u.inc_, env, cctx);
			break;
		case ilfactor_dec:
			ret = il_factor_dec_eval(self->u.dec_, env, cctx);
			break;
		case ilfactor_call_op:
			ret = il_factor_call_op_eval(self->u.call_, env, cctx);
			break;
		case ilfactor_member_op:
			ret = il_factor_member_op_eval(self->u.member_, env, cctx);
			break;
		case ilfactor_instanceof:
			ret = il_factor_instanceof_eval(self->u.instanceof_, env, cctx);
			break;
		case ilfactor_explicit_unary_op:
			ret = il_factor_explicit_unary_op_eval(self->u.exp_unary_op, env, cctx);
			break;
		case ilfactor_explicit_binary_op:
			ret = il_factor_explicit_binary_op_eval(self->u.exp_binary_op, env, cctx);
			break;
		case ilfactor_lambda:
			ret = il_factor_lambda_eval(self->u.lambda_, env, cctx);
			break;
		case ilfactor_property:
			ret = il_factor_property_eval(self->u.prop, env, cctx);
			break;
		case ilfactor_subscript:
			ret = il_factor_subscript_eval(self->u.subscript, env, cctx);
			break;
		default:
			assert(false);
			break;
	}
	//assert(ret != NULL);
	return ret;
}

char* il_factor_tostr(il_factor* self, enviroment* env) {
	if(bc_error_last()) {
		return NULL;
	}
	switch (self->type) {
		case ilfactor_int:
			return il_factor_int_tostr(self->u.int_, env);
		case ilfactor_double:
			return il_factor_double_tostr(self->u.double_, env);
		case ilfactor_char:
			return il_factor_char_tostr(self->u.char_, env);
		case ilfactor_string:
			return il_factor_string_tostr(self->u.string_, env);
		case ilfactor_variable:
			return il_factor_variable_tostr(self->u.variable_, env);
		case ilfactor_unary_op:
			return il_factor_unary_op_tostr(self->u.unary_, env);
		case ilfactor_binary_op:
			return il_factor_binary_op_tostr(self->u.binary_, env);
		case ilfactor_assign_op:
			return NULL;
		case ilfactor_this:
			return il_factor_this_tostr(self->u.this_, env);
		case ilfactor_super:
			return il_factor_super_tostr(self->u.super_, env);
		case ilfactor_new_instance:
			return il_factor_new_instance_tostr(self->u.new_instance_, env);
		case ilfactor_cast:
			return il_factor_cast_tostr(self->u.cast_, env);
		case ilfactor_bool:
			return il_factor_bool_tostr(self->u.bool_, env);
		case ilfactor_null:
			return il_factor_null_tostr(self->u.null_, env);
		case ilfactor_as:
			return il_factor_as_tostr(self->u.as_, env);
		case ilfactor_inc:
			return il_factor_inc_tostr(self->u.inc_, env);
		case ilfactor_dec:
			return il_factor_dec_tostr(self->u.dec_, env);
		case ilfactor_call_op:
			return il_factor_call_op_to_str(self->u.call_, env);
		case ilfactor_member_op:
			return il_factor_member_op_tostr(self->u.member_, env);
		case ilfactor_instanceof:
			return il_factor_instanceof_tostr(self->u.instanceof_, env);
		//あとで
		case ilfactor_explicit_unary_op:
			return NULL;
		case ilfactor_explicit_binary_op:
			return NULL;
		case ilfactor_lambda:
			return il_factor_lambda_tostr(self->u.lambda_, env);
		case ilfactor_property:
			return il_factor_property_tostr(self->u.prop, env);
		case ilfactor_subscript:
			return il_factor_subscript_tostr(self->u.subscript, env);
		default:
			break;
	}
}

void il_factor_args_tostr(string_buffer* sb, vector* args, enviroment* env) {
	if(args->length > 0) {
		string_buffer_append(sb, '(');
	}
	for(int i=0; i<args->length; i++) {
		il_argument* e = (il_argument*)vector_at(args, i);
		char* str = il_factor_tostr(e->factor, env);
		string_buffer_appends(sb, str);
		if(i != (args->length)) {
			string_buffer_appends(sb, ", ");
		}
		MEM_FREE(str);
	}
	if(args->length > 0) {
		string_buffer_append(sb, ')');
	}
}

void il_factor_type_args_tostr(string_buffer* sb, vector* type_args, enviroment* env) {
	if(type_args->length > 0) {
		string_buffer_appends(sb, "<|");
	}
	for(int i=0; i<type_args->length; i++) {
		il_type_argument* e = (il_type_argument*)vector_at(type_args, i);
		char* str = generic_cache_tostr(e->gcache);
		string_buffer_appends(sb, str);
		if(i != (type_args->length - 1)) {
			string_buffer_appends(sb, ", ");
		}
		MEM_FREE(str);
	}
	if(type_args->length > 0) {
		string_buffer_appends(sb, "|>");
	}
}

void il_factor_delete(il_factor * self) {
	if (self == NULL) {
		return;
	}
	switch (self->type) {
		case ilfactor_int:
			il_factor_int_delete(self->u.int_);
			break;
		case ilfactor_double:
			il_factor_double_delete(self->u.double_);
			break;
		case ilfactor_char:
			il_factor_char_delete(self->u.char_);
			break;
		case ilfactor_string:
			il_factor_string_delete(self->u.string_);
			break;
		case ilfactor_variable:
			il_factor_variable_delete(self->u.variable_);
			break;
		case ilfactor_unary_op:
			il_factor_unary_op_delete(self->u.unary_);
			break;
		case ilfactor_binary_op:
			il_factor_binary_op_delete(self->u.binary_);
			break;
		case ilfactor_assign_op:
			il_factor_assign_op_delete(self->u.assign_);
			break;
		case ilfactor_this:
			il_factor_this_delete(self->u.this_);
			break;
		case ilfactor_super:
			il_factor_super_delete(self->u.super_);
			break;
		case ilfactor_new_instance:
			il_factor_new_instance_delete(self->u.new_instance_);
			break;
		case ilfactor_cast:
			il_factor_cast_delete(self->u.cast_);
			break;
		case ilfactor_bool:
			il_factor_bool_delete(self->u.bool_);
			break;
		case ilfactor_null:
			break;
		case ilfactor_as:
			il_factor_as_delete(self->u.as_);
			break;
		case ilfactor_inc:
			il_factor_inc_delete(self->u.inc_);
			break;
		case ilfactor_dec:
			il_factor_dec_delete(self->u.dec_);
			break;
		case ilfactor_call_op:
			il_factor_call_op_delete(self->u.call_);
			break;
		case ilfactor_member_op:
			il_factor_member_op_delete(self->u.member_);
			break;
		case ilfactor_instanceof:
			il_factor_instanceof_delete(self->u.instanceof_);
			break;
		case ilfactor_explicit_unary_op:
			il_factor_explicit_unary_op_delete(self->u.exp_unary_op);
			break;
		case ilfactor_explicit_binary_op:
			il_factor_explicit_binary_op_delete(self->u.exp_binary_op);
			break;
		case ilfactor_lambda:
			il_factor_lambda_delete(self->u.lambda_);
			break;
		case ilfactor_property:
			il_factor_property_delete(self->u.prop);
			break;
		case ilfactor_subscript:
			il_factor_subscript_delete(self->u.subscript);
			break;
		default:
			break;
	}
	MEM_FREE(self);
}
