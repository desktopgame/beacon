#include "il_factor_interface.h"
#include "il_factor_impl.h"
#include "il_argument.h"
#include "il_type_argument.h"
#include "../util/text.h"
#include "../vm/enviroment.h"
#include "../env/type_interface.h"
#include "../util/mem.h"
#include <stdio.h>
#include <assert.h>

void il_factor_dump(il_factor * self, int depth) {
	il_print_layout_form(self->lineno);
	switch (self->type) {
		case ilfactor_int:
			il_factor_int_dump(self->u.int_, depth);
			break;
		case ilfactor_double:
			il_factor_double_dump(self->u.double_, depth);
			break;
		case ilfactor_cquote:
			il_factor_char_dump(self->u.char_, depth);
			break;
		case ilfactor_squote:
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
		default:
			break;
	}
}

void il_factor_generate(il_factor * self, enviroment* env, il_context* ilctx) {
	if(il_error_panic()) {
		return;
	}
	switch (self->type) {
		case ilfactor_int:
			il_factor_int_generate(self->u.int_, env, ilctx);
			break;
		case ilfactor_double:
			il_factor_double_generate(self->u.double_, env, ilctx);
			break;
		case ilfactor_cquote:
			il_factor_char_generate(self->u.char_, env, ilctx);
			break;
		case ilfactor_squote:
			il_factor_string_generate(self->u.string_, env, ilctx);
			break;
		case ilfactor_variable:
			il_factor_variable_generate(self->u.variable_, env, ilctx);
			break;
		case ilfactor_unary_op:
			il_factor_unary_op_generate(self->u.unary_, env, ilctx);
			break;
		case ilfactor_binary_op:
			il_factor_binary_op_generate(self->u.binary_, env, ilctx);
			break;
		case ilfactor_this:
			il_factor_this_generate(self->u.this_, env, ilctx);
			break;
		case ilfactor_super:
			il_factor_super_generate(self->u.super_, env, ilctx);
			break;
		case ilfactor_new_instance:
			il_factor_new_instance_generate(self->u.new_instance_, env, ilctx);
			break;
		case ilfactor_cast:
			il_factor_cast_generate(self->u.cast_, env, ilctx);
			break;
		case ilfactor_bool:
			il_factor_bool_generate(self->u.bool_, env, ilctx);
			break;
		case ilfactor_null:
			il_factor_null_generate(NULL, env, ilctx);
			break;
		case ilfactor_as:
			il_factor_as_generate(self->u.as_, env, ilctx);
			break;
		case ilfactor_inc:
			il_factor_inc_generate(self->u.inc_, env, ilctx);
			break;
		case ilfactor_dec:
			il_factor_dec_generate(self->u.dec_, env, ilctx);
			break;
		case ilfactor_call_op:
			il_factor_call_op_generate(self->u.call_, env, ilctx);
			break;
		case ilfactor_member_op:
			il_factor_member_op_generate(self->u.member_, env, ilctx);
			break;
		default:
			break;
	}
	enviroment_add_range(env, self->lineno);
}

void il_factor_load(il_factor * self, enviroment * env, il_context* ilctx) {
	if(il_error_panic()) {
		return;
	}
	switch (self->type) {
		case ilfactor_int:
			il_factor_int_load(self->u.int_, env, ilctx);
			break;
		case ilfactor_double:
			il_factor_double_load(self->u.double_, env, ilctx);
			break;
		case ilfactor_cquote:
			il_factor_char_load(self->u.char_, env, ilctx);
			break;
		case ilfactor_squote:
			il_factor_string_load(self->u.string_, env, ilctx);
			break;
		case ilfactor_variable:
			il_factor_variable_load(self->u.variable_, env, ilctx);
			break;
		case ilfactor_unary_op:
			il_factor_unary_op_load(self->u.unary_, env, ilctx);
			break;
		case ilfactor_binary_op:
			il_factor_binary_op_load(self->u.binary_, env, ilctx);
			break;
		case ilfactor_this:
			il_factor_this_load(self->u.this_, env, ilctx);
			break;
		case ilfactor_super:
			il_factor_super_load(self->u.super_, env, ilctx);
			break;
		case ilfactor_new_instance:
			il_factor_new_instance_load(self->u.new_instance_, env, ilctx);
			break;
		case ilfactor_cast:
			il_factor_cast_load(self->u.cast_, env, ilctx);
			break;
		case ilfactor_bool:
			//il_factor_bool_load(self->u.bool_, depth);
			break;
		case ilfactor_null:
			il_factor_null_load(NULL, env, ilctx);
			break;
		case ilfactor_as:
			il_factor_as_load(self->u.as_, env, ilctx);
			break;
		case ilfactor_inc:
			il_factor_inc_load(self->u.inc_, env, ilctx);
			break;
		case ilfactor_dec:
			il_factor_dec_load(self->u.dec_, env, ilctx);
			break;
		case ilfactor_call_op:
			il_factor_call_op_load(self->u.call_, env, ilctx);
			break;
		case ilfactor_member_op:
			il_factor_member_op_load(self->u.member_, env, ilctx);
			break;
		default:
			break;
	}
}

generic_type* il_factor_eval(il_factor * self, enviroment * env, il_context* ilctx) {
	if(il_error_panic()) {
		return NULL;
	}
	generic_type* ret = NULL;
	switch (self->type) {
		case ilfactor_int:
			ret = il_factor_int_eval(self->u.int_, env, ilctx);
			break;
		case ilfactor_double:
			ret = il_factor_double_eval(self->u.double_, env, ilctx);
			break;
		case ilfactor_cquote:
			ret = il_factor_char_eval(self->u.char_, env, ilctx);
			break;
		case ilfactor_squote:
			ret = il_factor_string_eval(self->u.string_, env, ilctx);
			break;
		case ilfactor_variable:
			ret = il_factor_variable_eval(self->u.variable_, env, ilctx);
			break;
		case ilfactor_unary_op:
			ret = il_factor_unary_op_eval(self->u.unary_, env, ilctx);
			break;
		case ilfactor_binary_op:
			ret = il_factor_binary_op_eval(self->u.binary_, env, ilctx);
			break;
		case ilfactor_this:
			ret = il_factor_this_eval(self->u.this_, env, ilctx);
			break;
		case ilfactor_super:
			ret = il_factor_super_eval(self->u.super_, env, ilctx);
			break;
		case ilfactor_new_instance:
			ret = il_factor_new_instance_eval(self->u.new_instance_, env, ilctx);
			break;
		case ilfactor_cast:
			ret = il_factor_cast_eval(self->u.cast_, env, ilctx);
			break;
		case ilfactor_bool:
			ret = il_factor_bool_eval(self->u.bool_,env, ilctx);
			break;
		case ilfactor_null:
			ret = il_factor_null_eval(NULL, env, ilctx);
			break;
		case ilfactor_as:
			ret = il_factor_as_eval(self->u.as_, env, ilctx);
			break;
		case ilfactor_inc:
			ret = il_factor_inc_eval(self->u.inc_, env, ilctx);
			break;
		case ilfactor_dec:
			ret = il_factor_dec_eval(self->u.dec_, env, ilctx);
			break;
		case ilfactor_call_op:
			ret = il_factor_call_op_eval(self->u.call_, env, ilctx);
			break;
		case ilfactor_member_op:
			ret = il_factor_member_op_eval(self->u.call_, env, ilctx);
			break;
		default:
			break;
	}
	assert((ret != NULL || il_error_panic()));
	return ret;
}

char* il_factor_tostr(il_factor* self, enviroment* env, il_context* ilctx) {
	if(il_error_panic()) {
		return NULL;
	}
	switch (self->type) {
		case ilfactor_int:
			return il_factor_int_tostr(self->u.int_, env, ilctx);
		case ilfactor_double:
			return il_factor_double_tostr(self->u.double_, env, ilctx);
		case ilfactor_cquote:
			return il_factor_char_tostr(self->u.char_, env, ilctx);
		case ilfactor_squote:
			return il_factor_string_tostr(self->u.string_, env, ilctx);
		case ilfactor_variable:
			return il_factor_variable_tostr(self->u.variable_, env, ilctx);
		case ilfactor_unary_op:
			return il_factor_unary_op_tostr(self->u.unary_, env, ilctx);
		case ilfactor_binary_op:
			return il_factor_binary_op_tostr(self->u.binary_, env, ilctx);
		case ilfactor_this:
			return il_factor_this_tostr(self->u.this_, env, ilctx);
		case ilfactor_super:
			return il_factor_super_tostr(self->u.super_, env, ilctx);
		case ilfactor_new_instance:
			return il_factor_new_instance_tostr(self->u.new_instance_, env, ilctx);
		case ilfactor_cast:
			return il_factor_cast_tostr(self->u.cast_, env, ilctx);
		case ilfactor_bool:
			return il_factor_bool_tostr(self->u.bool_, env, ilctx);
		case ilfactor_null:
			return il_factor_null_tostr(self->u.null_, env, ilctx);
		case ilfactor_as:
			return il_factor_as_tostr(self->u.as_, env, ilctx);
		case ilfactor_inc:
			return il_factor_inc_tostr(self->u.inc_, env,ilctx);
		case ilfactor_dec:
			return il_factor_dec_tostr(self->u.dec_, env, ilctx);
		case ilfactor_call_op:
			return il_factor_call_op_to_str(self->u.call_, env, ilctx);
		case ilfactor_member_op:
			return il_factor_member_op_tostr(self->u.member_, env, ilctx);
		default:
			break;
	}
}

void il_factor_args_tostr(string_buffer* sb, vector* args, enviroment* env, il_context* ilctx) {
	if(args->length > 0) {
		string_buffer_append(sb, '(');
	}
	for(int i=0; i<args->length; i++) {
		il_argument* e = (il_argument*)vector_at(args, i);
		char* str = il_factor_tostr(e->factor, env, ilctx);
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

void il_factor_type_args_tostr(string_buffer* sb, vector* type_args, enviroment* env, il_context* ilctx) {
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
		case ilfactor_cquote:
			il_factor_char_delete(self->u.char_);
			break;
		case ilfactor_squote:
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
		default:
			break;
	}
	MEM_FREE(self);
}
